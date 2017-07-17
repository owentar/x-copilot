#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#define STATUSWINDOW_HEIGHT 50
#define STATUSWINDOW_MARGIN 20
#define STATUSWINDOW_TOP 80

#include "XPLMDisplay.h"
#include "XPWidgetDefs.h"

#include <string>

class StatusWindow
{
    public:
        static StatusWindow* getInstance();
        void show(const std::string& message);
        void hide();

    private:
        class Dimensions {
        public:
            Dimensions(int height = STATUSWINDOW_HEIGHT, int left = STATUSWINDOW_MARGIN, int top = STATUSWINDOW_TOP) :
                height{height}, left{left}, top{top}, bottom{top - height} {
                width = getScreenWidth();
                right = left - width;
            }
            int getWidth() const { return width; }
            int getHeight() const { return height; }
            int getLeft() const { return left; }
            int getRight() const { return right; }
            int getTop() const { return top; }
            int getBottom() const { return bottom; }
        private:
            int getScreenWidth() {
                int width;
                XPLMGetScreenSize(&width, nullptr);
                return width;
            }

            int width;
            int height;
            int left;
            int right;
            int top;
            int bottom;
        };

        StatusWindow();
        virtual ~StatusWindow();
        static float flightLoopCallback(float elapsedMe, float elapsedSim, int counter, void* refcon);

        static StatusWindow* instance;
        std::string message;
        Dimensions dimensions;
        XPWidgetID widgetId;
        XPWidgetID messageWidgetId;
};

#endif // STATUSWINDOW_H
