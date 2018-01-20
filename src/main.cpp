#include <cstring>
#include <memory>
#include <utility>

#include <boost/format.hpp>

#include "XPLMPlugin.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"

#include "StatusWindow.h"
#include "XCopilot.h"
#include "Recognizer.h"
#include "Microphone.h"
#include "PocketsphinxWrapper.h"
#include "XPlaneDataRefSDK.h"
#include "Logger.h"

using namespace xcopilot;
using boost::format;

XPlaneDataRefSDK* xplaneSDK;
XCopilot* xCopilot;
Command* command1;
Command* command2;
void configureForAircraft();
float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon);

void setupLogging() {
    Logger::configureFileLogger(Logger::Level::DEBUG);
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
    std::unique_ptr<Pocketsphinx> pocketsphinx = std::make_unique<Pocketsphinx>();
    std::unique_ptr<Microphone> microphone = std::make_unique<Microphone>();
    std::unique_ptr<Recognizer> recognizer = std::make_unique<Recognizer>(std::move(pocketsphinx), std::move(microphone));
    xCopilot = new XCopilot(std::move(recognizer));
    XPLMRegisterFlightLoopCallback(flightLoopCallback, 1, 0);

    return 1;
}

PLUGIN_API void	XPluginStop(void)
{
    delete command1;
    delete command2;
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
    Logger::getInstance()->debug(format("Loading configuration for aircraft (%1%, %2%, %3%)") % author % desc % icao);
    command1 = new Command("SET ALTITUDE", CommandType::FLOAT, "^set altitude ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){3,5})$", {"sim/cockpit2/autopilot/altitude_dial_ft"}, xplaneSDK);
    command2 = new Command("SET ALTIMETER", CommandType::FLOAT, "^set altimeter ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){4})", {"sim/cockpit2/gauges/actuators/barometer_setting_in_hg_pilot", "sim/cockpit2/gauges/actuators/barometer_setting_in_hg_copilot"}, xplaneSDK);
    xCopilot->configureForAircraft({command1, command2});
}

float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    xCopilot->executePendingCommands();
    return 2;
}
