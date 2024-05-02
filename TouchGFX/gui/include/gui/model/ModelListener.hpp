#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    /**
     * Gets called every clock update by the Model class.
     * Implement in screens that use the clock.
     */
    virtual void updateClock() {}

    /**
     * Gets called when there is a misting/heating icon change needed.
     * Currently implemented in Home screen only.
     */
    virtual void updateIcons() {}

    /**
     * Gets called when new readings are done.
     * Currently implemented in Home screen only.
     */
    virtual void updateReadings() {}

    /**
     * Gets called in the graphs screen.
     * Used for displaying new live readings.
     */
    virtual void updateLiveGraph() {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
