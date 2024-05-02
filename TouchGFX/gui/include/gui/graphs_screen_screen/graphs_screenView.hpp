#ifndef GRAPHS_SCREENVIEW_HPP
#define GRAPHS_SCREENVIEW_HPP

#include <gui_generated/graphs_screen_screen/graphs_screenViewBase.hpp>
#include <gui/graphs_screen_screen/graphs_screenPresenter.hpp>

class graphs_screenView : public graphs_screenViewBase
{
public:
    graphs_screenView();
    virtual ~graphs_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateGraph();
    virtual void updateLiveGraph();

    virtual void setTitle();
    virtual void setYLabel();
    virtual void setXLabel();
    virtual void updateButtons();

    virtual void graphLive();
    virtual void graphHour();
    virtual void graphDay();
    virtual void graphMonth();
protected:
    bool isHotZone; // Hot or cold to display
    bool isTempDisp; // Temp or hum to display

    // Type of historical data to display
    enum graphTime {
    	HOUR = 0,
		DAY = 1,
		MONTH = 2,
		LIVE = 3
    };
    graphTime graphTime = LIVE; // Default to day
};

#endif // GRAPHS_SCREENVIEW_HPP
