#ifndef ALERTS_SCREENPRESENTER_HPP
#define ALERTS_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class alerts_screenView;

class alerts_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    alerts_screenPresenter(alerts_screenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~alerts_screenPresenter() {}

private:
    alerts_screenPresenter();

    alerts_screenView& view;
};

#endif // ALERTS_SCREENPRESENTER_HPP
