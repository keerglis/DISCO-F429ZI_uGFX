#include "mbed.h"
#include "gfx.h"

//don't use I2C3, SPI5, SDRAM - it is for LCD!

//Ticker tick;

static GHandle ghButton1;
static GListener gl;

DigitalOut led_green(LED1);



static void createWidgets(void)
{
	GWidgetInit wi;

	// Apply some default values for GWIN
	gwinWidgetClearInit(&wi);
	wi.g.show = TRUE;

    wi.g.width = 150; wi.g.height = 20; wi.g.x = 10, wi.g.y = 10;
    wi.text = "ON";
    ghButton1 = gwinButtonCreate(0, &wi);
}


int main()
{
	GEvent* pe;


	gfxInit();

	// Set the widget defaults
	gwinSetDefaultFont(gdispOpenFont("UI2"));
	gwinSetDefaultStyle(&WhiteWidgetStyle, FALSE);
	gdispClear(White);

	// create the widget
	createWidgets();

	// We want to listen for widget events
	geventListenerInit(&gl);
	gwinAttachListener(&gl);


    while(1)
    {
    	// Get an Event
    	pe = geventEventWait(&gl, TIME_INFINITE);

        switch(pe->type) {
            case GEVENT_GWIN_BUTTON:
                if (((GEventGWinButton*)pe)->gwin == ghButton1) {
                    if (strcmp(gwinGetText(ghButton1), "ON") == 0)
                    {
                        // Our button has been pressed
                        led_green=1;
                        gwinSetText(ghButton1, "OFF", TRUE);
                    }
                    else if (strcmp(gwinGetText(ghButton1), "OFF") == 0)
                    {
                        // Our button has been pressed
                    	led_green=0;
                        gwinSetText(ghButton1, "ON", TRUE);
                    }
                }
                break;

            default:
                break;
        }
    }
}


