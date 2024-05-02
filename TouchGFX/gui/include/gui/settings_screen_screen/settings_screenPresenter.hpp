#ifndef SETTINGS_SCREENPRESENTER_HPP
#define SETTINGS_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class settings_screenView;

class settings_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    settings_screenPresenter(settings_screenView& v);

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

    virtual ~settings_screenPresenter() {}

    // Misting Get/Set
    bool getMistEn() { return model->getMistEn(); }
    void setMistEn(bool mistEn) { model->setMistEn(mistEn); }
    int getHumSet() { return model->getHumSet(); }
    void setHumSet(int humSet) { model->setHumSet(humSet); }

    // Heating Get/Set
    bool getHeatEn() { return model->getHeatEn(); }
    void setHeatEn(bool heatEn) { model->setHeatEn(heatEn); }
    int getTempSet() { return model->getTempSet(); }
    void setTempSet(int tempSet) { model->setTempSet(tempSet); }

private:
    settings_screenPresenter();

    settings_screenView& view;
};

#endif // SETTINGS_SCREENPRESENTER_HPP
