#include "StatusWindow.h"

#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPLMProcessing.h"

#define STATUSWINDOW_TITLE "X-Copilot"
#define STATUSWINDOW_TIMER 8

StatusWindow::StatusWindow()
{
    widgetId = XPCreateWidget(dimensions.getLeft(), dimensions.getTop(), dimensions.getRight(), dimensions.getBottom(), 0, STATUSWINDOW_TITLE, 1, 0, xpWidgetClass_MainWindow);
    XPSetWidgetProperty(widgetId, xpProperty_MainWindowType, xpMainWindowStyle_Translucent);
    XPSetWidgetProperty(widgetId, xpProperty_MainWindowHasCloseBoxes, 0);

    messageWidgetId = XPCreateWidget(dimensions.getLeft(), dimensions.getTop()-20, dimensions.getRight(), dimensions.getBottom(), 1, "Recording...", 0, widgetId, xpWidgetClass_TextField);
    XPSetWidgetProperty(messageWidgetId, xpProperty_TextFieldType, xpTextTranslucent);
    XPSetWidgetProperty(messageWidgetId, xpProperty_Enabled, 0);

    XPLMRegisterFlightLoopCallback(StatusWindow::flightLoopCallback, 0, this);
}

StatusWindow::~StatusWindow()
{
    XPLMUnregisterFlightLoopCallback(StatusWindow::flightLoopCallback, this);
}

void StatusWindow::show(const std::string& message)
{
    this->message = message;
    XPShowWidget(widgetId);
    XPBringRootWidgetToFront(widgetId);
    XPSetWidgetDescriptor(messageWidgetId, message.c_str());
    XPLMSetFlightLoopCallbackInterval(StatusWindow::flightLoopCallback, STATUSWINDOW_TIMER, 1, 0);
}

void StatusWindow::hide()
{
    XPHideWidget(widgetId);
}

float StatusWindow::flightLoopCallback(float elapsedMe, float elapsedSim, int counter, void* refStatusWindow)
{
    StatusWindow* statusWindow = static_cast<StatusWindow*>(refStatusWindow);
    statusWindow->hide();
    return 0;
}
