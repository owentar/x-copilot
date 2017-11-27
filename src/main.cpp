#include <cstring>
#include <memory>
#include <utility>

#include "XPLMPlugin.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"

#include "StatusWindow.h"
#include "XCopilot.h"
#include "Recognizer.h"
#include "Microphone.h"
#include "PocketsphinxWrapper.h"

XCopilot* xCopilot;
void configureForAircraft();
float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon);

PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
	strcpy(outName, "X-Copilot");
	strcpy(outSig, "Owentar");
	strcpy(outDesc, "Recognize voice commands");

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
}

PLUGIN_API int XPluginEnable(void)
{
    std::unique_ptr<Pocketsphinx> pocketsphinx = std::make_unique<Pocketsphinx>();
    std::unique_ptr<Microphone> microphone;
    std::unique_ptr<Recognizer> recognizer = std::make_unique<Recognizer>(std::move(pocketsphinx), std::move(microphone));
    xCopilot = new XCopilot(std::move(recognizer));
    xCopilot->enable();
    XPLMRegisterFlightLoopCallback(flightLoopCallback, 1, 0);
	return 1;
}

PLUGIN_API void XPluginDisable(void)
{
    xCopilot->disable();
    delete xCopilot;
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam)
{
    /*
    if (inMsg == XPLM_MSG_PLANE_LOADED)
    {
        configureForAircraft();
    }
    */
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
    xCopilot->configureForAircraft(author, desc, icao);
}

float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    xCopilot->executePendingCommands();
    return 1;
}
