#include <gui/home_screen_screen/home_screenView.hpp>
#include <gui/home_screen_screen/home_screenPresenter.hpp>

home_screenPresenter::home_screenPresenter(home_screenView& v)
    : view(v)
{

}

void home_screenPresenter::activate()
{
	updateIcons();
	updateFlags();

}

void home_screenPresenter::deactivate()
{

}

void home_screenPresenter::updateIcons()
{
	view.updateMistIcon(getMistEn(), getIsMisting());
	view.updateHeatIcon(getHeatEn(), getIsHeating());
}

void home_screenPresenter::updateReadings()
{
	view.updateReadings(
		getWarmTemp(),
		getWarmHum(),
		getColdTemp(),
		getColdHum()
	);
}

void home_screenPresenter::updateFlags()
{
	view.updateAlertsIcon(getFlagAny());
}
