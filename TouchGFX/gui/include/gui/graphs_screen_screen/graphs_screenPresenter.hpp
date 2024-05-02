#ifndef GRAPHS_SCREENPRESENTER_HPP
#define GRAPHS_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class graphs_screenView;

class graphs_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    graphs_screenPresenter(graphs_screenView& v);

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

    virtual ~graphs_screenPresenter() {}

    // Inherited function to update the live graph
    virtual void updateLiveGraph();

    // Gets/sets
    bool getGraphType() { return model->getGraphType(); }
    bool getGraphZone() { return model->getGraphZone(); }
    int* getGraphData(bool isTemp, bool isHot, int timeType) { return model->getGraphData(isTemp, isHot, timeType); }
    int getGraphNumData(int timeType) { return model->getGraphNumData(timeType); }

private:
    graphs_screenPresenter();

    graphs_screenView& view;
};

#endif // GRAPHS_SCREENPRESENTER_HPP
