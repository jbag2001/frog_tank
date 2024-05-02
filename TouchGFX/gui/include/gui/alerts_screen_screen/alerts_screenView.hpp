#ifndef ALERTS_SCREENVIEW_HPP
#define ALERTS_SCREENVIEW_HPP

#include <gui_generated/alerts_screen_screen/alerts_screenViewBase.hpp>
#include <gui/alerts_screen_screen/alerts_screenPresenter.hpp>

class alerts_screenView : public alerts_screenViewBase
{
public:
    alerts_screenView();
    virtual ~alerts_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // ALERTS_SCREENVIEW_HPP
