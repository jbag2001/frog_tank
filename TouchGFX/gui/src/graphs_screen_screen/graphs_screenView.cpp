#include <gui/graphs_screen_screen/graphs_screenView.hpp>
#include <touchgfx/Color.hpp>

graphs_screenView::graphs_screenView()
{

}

void graphs_screenView::setupScreen()
{
    graphs_screenViewBase::setupScreen();

    isHotZone = presenter->getGraphZone();
    isTempDisp = presenter->getGraphType();

    updateGraph();

}

void graphs_screenView::tearDownScreen()
{
    graphs_screenViewBase::tearDownScreen();
}


void graphs_screenView::updateGraph() {
	setTitle();
	setYLabel();
	setXLabel();
	updateButtons();

	int* data = presenter->getGraphData(isTempDisp, isHotZone, graphTime);
	int num_data = presenter->getGraphNumData(graphTime);

	if (graphTime == LIVE) {
		live_graph.clear();

		// Keep these constant since this is a live/dynamic graph
		live_graph.setGraphRangeX(0, 60); // Last 60 seconds of data
		live_graph.setGraphRangeY(30, 100); // Temp/hum should not fall out of this range

		// Add existing data points
		for (int i = 0; i < num_data; i++)
			live_graph.addDataPoint(data[i]);

		live_graph.setVisible(true);
		graph.setVisible(false);
		live_graph.invalidate();
	}
	else {
		graph.clear();

		// Min/max values for axis ranges
		int y_min = num_data > 0 ? data[0] : 0;
		int y_max = num_data > 0 ? data[0] : 0;

		for (int i = 0; i < num_data; i++) {
			if (y_min >= data[i])
				y_min = data[i];
			if (y_max <= data[i])
				y_max = data[i];
		}

		if (y_min == 0 || y_max == 0) { // Values never changed, set them to a decent range
			y_min = 70;
			y_max = 90;
		}
		else { // Add some padding to make it look nice
			y_min -= 2;
			y_max += 2;
		}

		graph.setGraphRangeX(0, num_data > 10 ? num_data : 10);
		graph.setGraphRangeY(y_min, y_max);

		for (int i = 0; i < num_data; i++)
			graph.addDataPoint(i, data[i]);

		live_graph.setVisible(false);
		graph.setVisible(true);
		graph.invalidate();
	}
}

void graphs_screenView::updateLiveGraph() {
	if (graphTime == LIVE) { // Only update if the live data screen is active
		int* data = presenter->getGraphData(isTempDisp, isHotZone, graphTime);
		int num_data = presenter->getGraphNumData(graphTime);

		live_graph.addDataPoint(data[num_data - 1]);
	}
}

void graphs_screenView::setTitle() {
	graph_title_hot_temp.setVisible(isHotZone && isTempDisp);
	graph_title_hot_hum.setVisible(isHotZone && !isTempDisp);
	graph_title_cold_temp.setVisible(!isHotZone && isTempDisp);
	graph_title_cold_hum.setVisible(!isHotZone && !isTempDisp);

	graph_title_hot_temp.invalidate();
	graph_title_hot_hum.invalidate();
	graph_title_cold_temp.invalidate();
	graph_title_cold_hum.invalidate();
}

void graphs_screenView::setYLabel() {
	temp_label.setVisible(isTempDisp);
	hum_label.setVisible(!isTempDisp);

	temp_label.invalidate();
	hum_label.invalidate();
}

void graphs_screenView::setXLabel() {
	time_hour_label.setVisible(graphTime == HOUR);
	time_day_label.setVisible(graphTime == DAY);
	time_month_label.setVisible(graphTime == MONTH);
	time_live_label.setVisible(graphTime == LIVE);

	time_hour_label.invalidate();
	time_day_label.invalidate();
	time_month_label.invalidate();
	time_live_label.invalidate();
}

void graphs_screenView::updateButtons() {
    hour_bg.setColor(touchgfx::Color::getColorFromRGB(240, 240, 240));
    day_bg.setColor(touchgfx::Color::getColorFromRGB(240, 240, 240));
    month_bg.setColor(touchgfx::Color::getColorFromRGB(240, 240, 240));
    live_bg.setColor(touchgfx::Color::getColorFromRGB(240, 240, 240));

	switch (graphTime) {
		case HOUR:
		    hour_bg.setColor(touchgfx::Color::getColorFromRGB(57, 167, 206));
			break;
		case DAY:
		    day_bg.setColor(touchgfx::Color::getColorFromRGB(57, 167, 206));
			break;
		case MONTH:
		    month_bg.setColor(touchgfx::Color::getColorFromRGB(57, 167, 206));
			break;
		case LIVE:
		    live_bg.setColor(touchgfx::Color::getColorFromRGB(57, 167, 206));
			break;
			break;
	}

	hour_bg.invalidate();
	day_bg.invalidate();
	month_bg.invalidate();
	live_bg.invalidate();
}

void graphs_screenView::graphLive() {
	graphTime = LIVE;
	updateGraph();
}

void graphs_screenView::graphHour() {
	graphTime = HOUR;
    updateGraph();
}

void graphs_screenView::graphDay() {
	graphTime = DAY;
    updateGraph();
}

void graphs_screenView::graphMonth() {
	graphTime = MONTH;
    updateGraph();
}
