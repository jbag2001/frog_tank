#ifndef CLOCK_SCREENPRESENTER_HPP
#define CLOCK_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class clock_screenView;

class clock_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    clock_screenPresenter(clock_screenView& v);

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

    virtual ~clock_screenPresenter() {}

    void saveHour(int hour) { model->saveHour(hour); }
    void saveMin(int min) { model->saveMin(min); }
    int getHour() { return model->getHour(); }
    int getMin() { return model->getMin(); }

private:
    clock_screenPresenter();

    clock_screenView& view;
};

#endif // CLOCK_SCREENPRESENTER_HPP
