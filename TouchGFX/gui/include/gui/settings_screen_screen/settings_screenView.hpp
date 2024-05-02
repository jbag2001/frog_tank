#ifndef SETTINGS_SCREENVIEW_HPP
#define SETTINGS_SCREENVIEW_HPP

#include <gui_generated/settings_screen_screen/settings_screenViewBase.hpp>
#include <gui/settings_screen_screen/settings_screenPresenter.hpp>

class settings_screenView : public settings_screenViewBase
{
public:
    settings_screenView();
    virtual ~settings_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Toggle Buttons
    virtual void toggleHeating();
    virtual void toggleMisting();

    // Temperature Controls
    virtual void lowTemp();
    virtual void incTemp();
    virtual void tempChange(int val);

    // Humidity Controls
    virtual void lowHum();
    virtual void incHum();
    virtual void humChange(int val);

protected:
    void setTempLabel(int val);
    void setHumLabel(int val);
};

#endif // SETTINGS_SCREENVIEW_HPP
