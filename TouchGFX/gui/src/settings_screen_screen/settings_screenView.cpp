#include <gui/settings_screen_screen/settings_screenView.hpp>
#include "stm32f7xx_hal.h"

static int tempVal;
static int humVal;
static bool heatOn;
static bool mistOn;

settings_screenView::settings_screenView()
{

}

void settings_screenView::setupScreen()
{
    settings_screenViewBase::setupScreen();

    mistOn = presenter->getMistEn();
    humVal = presenter->getHumSet();

    heatOn = presenter->getHeatEn();
    tempVal = presenter->getTempSet();

    heat_toggle.forceState(heatOn);
    mist_toggle.forceState(mistOn);

    temp_slider.setValue(tempVal);
    hum_slider.setValue(humVal);
}

void settings_screenView::tearDownScreen()
{
    settings_screenViewBase::tearDownScreen();

    presenter->setMistEn(mistOn);
    presenter->setHumSet(humVal);

    presenter->setHeatEn(heatOn);
    presenter->setTempSet(tempVal);
}

void settings_screenView::toggleHeating()
{
	// This code bellow is just for testing buttons
	//	if (heat_toggle.getState())
	//		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);
	//	else
	//		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_RESET);
	heatOn = heat_toggle.getState();
}

void settings_screenView::toggleMisting()
{
	mistOn = mist_toggle.getState();
}

void settings_screenView::lowTemp()
{
	int curVal = temp_slider.getValue();
	if (--curVal >= temp_slider.getMinValue())
		temp_slider.setValue(curVal);
}

void settings_screenView::incTemp()
{
	int curVal = temp_slider.getValue();
	if (++curVal <= temp_slider.getMaxValue())
		temp_slider.setValue(curVal);
}

void settings_screenView::lowHum()
{
	int curVal = hum_slider.getValue();
	if (--curVal >= hum_slider.getMinValue())
		hum_slider.setValue(curVal);
}

void settings_screenView::incHum()
{
	int curVal = hum_slider.getValue();
	if (++curVal <= hum_slider.getMaxValue())
		hum_slider.setValue(curVal);
}

void settings_screenView::tempChange(int val)
{
	tempVal = val;
	setTempLabel(val);
}

void settings_screenView::humChange(int val)
{
	humVal = val;
	setHumLabel(val);
}

void settings_screenView::setTempLabel(int val) {
    Unicode::snprintf(temp_valBuffer, TEMP_VAL_SIZE, "%d", val);
    temp_val.invalidateContent();
}

void settings_screenView::setHumLabel(int val) {
    Unicode::snprintf(hum_valBuffer, HUM_VAL_SIZE, "%d", val);
    hum_val.invalidateContent();
}
