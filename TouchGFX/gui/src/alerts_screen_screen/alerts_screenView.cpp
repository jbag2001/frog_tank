#include <gui/alerts_screen_screen/alerts_screenView.hpp>
#include <string>

alerts_screenView::alerts_screenView()
{

}

void alerts_screenView::setupScreen()
{
    alerts_screenViewBase::setupScreen();

    char alertString[ALERT_TEXT_SIZE] = "";

    bool f_i2c = presenter->getFlagI2C();
    bool f_warm = presenter->getFlagWarm();
    bool f_cold = presenter->getFlagCold();
    bool f_mist = presenter->getFlagMist();

    if (f_i2c && false) {
    	const char *temp = "GENERAL SENSOR ERROR - The sensors have completely stopped working. Try rebooting the system. \n\n";
    	strcat(alertString, temp);
    }
    else {
    	if (f_warm) {
			const char *temp = "WARM ZONE SENSOR ERROR - The warm zone sensor is not responding. Make sure it is plugged and enable the heating to clear this alert. \n\n";
			strcat(alertString, temp);
		}

    	if (f_cold) {
			const char *temp = "COLD ZONE SENSOR ERROR - The cold zone sensor is not responding. Make sure it is plugged and enable the misting to clear this alert. \n\n";
			strcat(alertString, temp);
		}
    }

    if (f_mist) {
    	const char *temp = "MISTING ISSUE - Check that the mister is plugged in and the reservoir is not empty. Enable the mister to clear this alert once the issue is resolved.";
    	strcat(alertString, temp);
    }

    Unicode::strncpy(alert_textBuffer, alertString, ALERT_TEXT_SIZE);
    alert_text.invalidate();
}

void alerts_screenView::tearDownScreen()
{
    alerts_screenViewBase::tearDownScreen();
}
