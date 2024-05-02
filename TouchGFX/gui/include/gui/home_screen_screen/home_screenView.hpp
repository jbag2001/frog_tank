#ifndef HOME_SCREENVIEW_HPP
#define HOME_SCREENVIEW_HPP

#include <gui_generated/home_screen_screen/home_screenViewBase.hpp>
#include <gui/home_screen_screen/home_screenPresenter.hpp>

class home_screenView : public home_screenViewBase
{
public:
    home_screenView();
    virtual ~home_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateClock(int hour, int min);
    virtual void updateMistIcon(bool disabled, bool misting);
    virtual void updateHeatIcon(bool disabled, bool heating);
    virtual void updateReadings(int hotTemp, int hotHum, int coldTemp, int coldHum);

    // Inherited button listeners
    virtual void set_hot_temp();
    virtual void set_hot_hum();
    virtual void set_cold_temp();
    virtual void set_cold_hum();
protected:
};

#endif // HOME_SCREENVIEW_HPP
