#ifndef CLOCK_SCREENVIEW_HPP
#define CLOCK_SCREENVIEW_HPP

#include <gui_generated/clock_screen_screen/clock_screenViewBase.hpp>
#include <gui/clock_screen_screen/clock_screenPresenter.hpp>

class clock_screenView : public clock_screenViewBase
{
public:
    clock_screenView();
    virtual ~clock_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Hour Buttons
    virtual void lowHour();
    virtual void incHour();

    // Min Buttons
    virtual void lowMin();
    virtual void incMin();

    // Sliders
    virtual void hourChange(int val);
    virtual void minChange(int val);

    // Save Values
    virtual void updateTime();

protected:
    void setHourLabel(int val);
    void setMinLabel(int val);
    int hour;
    int min;
};

#endif // CLOCK_SCREENVIEW_HPP
