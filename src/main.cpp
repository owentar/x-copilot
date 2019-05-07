#include <cstring>
#include <memory>
#include <utility>

#include <boost/format.hpp>

#include "XPLMPlugin.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"

#include "CommandsConfigReader.h"
#include "Logger.h"
#include "Recognizer.h"
#include "StatusWindow.h"
#include "XCopilot.h"
#include "XPlaneDataRefSDK.h"
#include "CommandsProvider.h"
#if IBM
#include "WinRecognizer.h"
#else
#include "UnixRecognizer.h"
#endif

using namespace xcopilot;
using boost::format;

XPlaneDataRefSDK* xplaneSDK;
XCopilot* xCopilot;
void configureForAircraft();
float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon);

void setupLogging() {
    Logger::configureFileLogger(Logger::level::debug);
}

bool isUserAirplane(const long planeNum) {
    return planeNum == 0;
}

PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
	strcpy(outName, "X-Copilot");
	strcpy(outSig, "Owentar");
	strcpy(outDesc, "Recognize voice commands");

    setupLogging();

    xplaneSDK = new XPlaneDataRefSDK();
#ifdef IBM
    std::unique_ptr<Recognizer> recognizer = std::make_unique<WinRecognizer>();
#else
    std::unique_ptr<Recognizer> recognizer = std::make_unique<UnixRecognizer>();
#endif
    xCopilot = new XCopilot(std::move(recognizer));
    XPLMRegisterFlightLoopCallback(flightLoopCallback, 1, 0);

    return 1;
}

PLUGIN_API void	XPluginStop(void)
{
    delete xplaneSDK;
    delete xCopilot;
}

PLUGIN_API int XPluginEnable(void)
{
    xCopilot->enable();
	return 1;
}

PLUGIN_API void XPluginDisable(void)
{
    xCopilot->disable();
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam)
{
    if (inMsg == XPLM_MSG_PLANE_LOADED)
    {
        auto planeNum = reinterpret_cast<long>(inParam);
        if (isUserAirplane(planeNum)) {
            configureForAircraft();
        }
    }
}

void configureForAircraft()
{
    auto authorID = XPLMFindDataRef("sim/aircraft/view/acf_author");
    auto ICAOID = XPLMFindDataRef("sim/aircraft/view/acf_ICAO");
    auto descID = XPLMFindDataRef("sim/aircraft/view/acf_descrip");
    char author[500];
    char icao[40];
    char desc[260];
    XPLMGetDatab(authorID, author, 0, 500);
    XPLMGetDatab(ICAOID, icao, 0, 40);
    XPLMGetDatab(descID, desc, 0, 260);
    CommandsProvider commandsProvider{xplaneSDK};
    auto commands = commandsProvider.getCommandsForAircraft(author, icao, desc);
    Logger::getInstance()->debug(format("Loading configuration for aircraft (%1%, %2%, %3%)") % author % desc % icao);
    xCopilot->configureForAircraft(commands);
}

float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    auto pendingCommands = xCopilot->getPendingCommands();
    Logger::getInstance()->debug(format("Executing %1% pending commands") % pendingCommands.size());
    std::for_each(pendingCommands.begin(), pendingCommands.end(), [](const CommandExecutor& commandExecutor)
    {
        StatusWindow::getInstance()->show("Command recognized");
        commandExecutor.execute();
    });
    return 2;
}
