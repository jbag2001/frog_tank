#include <gui/clock_screen_screen/clock_screenView.hpp>

clock_screenView::clock_screenView()
{

}

void clock_screenView::setupScreen()
{
    clock_screenViewBase::setupScreen();
    hour = presenter->getHour();
    min = presenter->getMin();

    hour_slider.setValue(hour);
    minute_slider.setValue(min);
}

void clock_screenView::tearDownScreen()
{
    clock_screenViewBase::tearDownScreen();
}

void clock_screenView::lowHour()
{
	int curVal = hour_slider.getValue();
	if (--curVal >= hour_slider.getMinValue())
		hour_slider.setValue(curVal);
}

void clock_screenView::incHour()
{
	int curVal = hour_slider.getValue();
	if (++curVal <= hour_slider.getMaxValue())
		hour_slider.setValue(curVal);
}

void clock_screenView::lowMin()
{
	int curVal = minute_slider.getValue();
	if (--curVal >= minute_slider.getMinValue())
		minute_slider.setValue(curVal);
}

void clock_screenView::incMin()
{
	int curVal = minute_slider.getValue();
	if (++curVal <= minute_slider.getMaxValue())
		minute_slider.setValue(curVal);
}

void clock_screenView::hourChange(int val) {
	hour = val;
	setHourLabel(val);
}

void clock_screenView::minChange(int val) {
	min = val;
	setMinLabel(val);
}

void clock_screenView::updateTime() {
	presenter->saveHour(hour);
	presenter->saveMin(min);
}

void clock_screenView::setHourLabel(int val) {
	Unicode::snprintf(hour_textBuffer, HOUR_TEXT_SIZE, "%d", val);
    hour_text.invalidateContent();
}

void clock_screenView::setMinLabel(int val) {
    Unicode::snprintf(min_textBuffer, MIN_TEXT_SIZE, "%d", val);
    min_text.invalidateContent();
}
