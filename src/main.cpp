#include <cstring>

#include "XPLMPlugin.h"
#include "XPLMDataAccess.h"
//#include "XPLMUtilities.h"

#include "StatusWindow.h"
#include "XCopilot.h"

void configureForAircraft();

PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
	strcpy(outName, "X-Copilot");
	strcpy(outSig, "Owentar");
	strcpy(outDesc, "A plug-in to...");

	// command = XPLMCreateCommand("xcopilot/record_voice_command", "Record voice command.");

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
}

PLUGIN_API int XPluginEnable(void)
{
    XCopilot::getInstance()->enable();
	return 1;
}

PLUGIN_API void XPluginDisable(void)
{
    XCopilot::getInstance()->disable();
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam)
{
    if (inMsg == XPLM_MSG_PLANE_LOADED)
    {
        configureForAircraft();
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
    XCopilot::getInstance()->configureForAircraft(author, desc, icao);
}
