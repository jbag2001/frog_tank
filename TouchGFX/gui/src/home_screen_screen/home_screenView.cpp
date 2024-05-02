#include <gui/home_screen_screen/home_screenView.hpp>

home_screenView::home_screenView()
{

}

void home_screenView::setupScreen()
{
    home_screenViewBase::setupScreen();

    updateReadings(
    	presenter->getWarmTemp(),
		presenter->getWarmHum(),
		presenter->getColdTemp(),
		presenter->getColdHum()
    );
}

void home_screenView::tearDownScreen()
{
    home_screenViewBase::tearDownScreen();
}

void home_screenView::updateClock(int hour, int min) {
	dg_clk.setTime24Hour(hour, min, 0);
}

void home_screenView::updateMistIcon(bool enabled, bool misting) {
	mist_disb_line.setVisible(!enabled);
	mist_disb_circ.setVisible(!enabled);
	mist_circ.setVisible(enabled & misting);

	mist_disb_line.invalidate();
	mist_disb_circ.invalidate();
	mist_circ.invalidate();
}

void home_screenView::updateHeatIcon(bool enabled, bool heating) {
	heat_disb_line.setVisible(!enabled);
	heat_disb_circ.setVisible(!enabled);
	heat_circ.setVisible(enabled & heating);

	heat_disb_line.invalidate();
	heat_disb_circ.invalidate();
	heat_circ.invalidate();
}

void home_screenView::updateReadings(int hotTemp, int hotHum, int coldTemp, int coldHum) {
	Unicode::snprintf(hot_temp_dispBuffer, HOT_TEMP_DISP_SIZE, "%d", hotTemp);
	Unicode::snprintf(hot_hum_dispBuffer, HOT_HUM_DISP_SIZE, "%d", hotHum);
	Unicode::snprintf(cold_temp_dispBuffer, COLD_TEMP_DISP_SIZE, "%d", coldTemp);
	Unicode::snprintf(cold_hum_dispBuffer, COLD_HUM_DISP_SIZE, "%d", coldHum);

	hot_temp_disp.invalidateContent();
	hot_hum_disp.invalidateContent();
	cold_temp_disp.invalidateContent();
	cold_hum_disp.invalidateContent();
}

void home_screenView::set_hot_temp() {
	presenter->setGraphType(true);
	presenter->setGraphZone(true);
}

void home_screenView::set_hot_hum() {
	presenter->setGraphType(false);
	presenter->setGraphZone(true);
}

void home_screenView::set_cold_temp() {
	presenter->setGraphType(true);
	presenter->setGraphZone(false);
}

void home_screenView::set_cold_hum() {
	presenter->setGraphType(false);
	presenter->setGraphZone(false);
}

