#ifndef HOME_SCREENPRESENTER_HPP
#define HOME_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class home_screenView;

class home_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    home_screenPresenter(home_screenView& v);

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

    virtual ~home_screenPresenter() {}

    virtual void updateIcons();
    virtual void updateReadings();
    virtual void updateFlags();

    // Alerts Gets
    bool getFlagWarm() { return model->getFlagWarm(); };
    bool getFlagCold() { return model->getFlagCold(); };
    bool getFlagI2C() { return model->getFlagI2C(); };
    bool getFlagMist() { return model->getFlagMist(); };
    bool getFlagAny() { return model->getFlagAny(); };

    // Mist Gets
    bool getIsMisting() { return model->getIsMisting(); }
    bool getMistEn() { return model->getMistEn(); }
    int getWarmHum() { return model->getWarmHum(); }
    int getColdHum() { return model->getColdHum(); }

    // Heat Gets
    bool getIsHeating() { return model->getIsHeating(); }
    bool getHeatEn() { return model->getHeatEn(); }
    int getWarmTemp() { return model->getWarmTemp(); }
    int getColdTemp() { return model->getColdTemp(); }

    // Graphs Sets
    void setGraphType(bool isTemp) { model->setGraphType(isTemp); }
    void setGraphZone(bool isHot) { model->setGraphZone(isHot); }

private:
    home_screenPresenter();

    home_screenView& view;
};

#endif // HOME_SCREENPRESENTER_HPP
