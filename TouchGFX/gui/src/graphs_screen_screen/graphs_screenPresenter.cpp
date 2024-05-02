#include <gui/graphs_screen_screen/graphs_screenView.hpp>
#include <gui/graphs_screen_screen/graphs_screenPresenter.hpp>

graphs_screenPresenter::graphs_screenPresenter(graphs_screenView& v)
    : view(v)
{

}

void graphs_screenPresenter::activate()
{

}

void graphs_screenPresenter::deactivate()
{

}

void graphs_screenPresenter::updateLiveGraph() {
	view.updateLiveGraph();
}
