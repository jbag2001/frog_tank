#ifndef MODEL_HPP
#define MODEL_HPP
#include <stdint.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    // Gets/Sets of clock vars
    void saveHour(int saveHour) { hour = saveHour; }
    void saveMin(int saveMin) { min = saveMin; }
    int getHour() { return hour; }
    int getMin() { return min; }

    // Gets/Sets of Hum vars
    bool getIsMisting() { return isMisting; }
    bool getMistEn() { return mistEn; }
    void setMistEn(bool mistEnVal) { mistEn = mistEnVal; }
    int getHumSet() { return humSet; }
    void setHumSet(int humSetVal) { humSet = humSetVal; }
    int getWarmHum() { return warmHumVal; }
    int getColdHum() { return coldHumVal; }

    // Gets/Sets of Temp vars
    bool getIsHeating() { return isHeating; }
    bool getHeatEn() { return heatEn; }
    void setHeatEn(bool heatEnVal) { heatEn = heatEnVal; }
    int getTempSet() { return tempSet; }
    void setTempSet(int tempSetVal) { tempSet = tempSetVal; }
    int getWarmTemp() { return warmTempVal; }
    int getColdTemp() { return coldTempVal; }

    // Gets for graph stuff
    bool getGraphType() { return graphType; }
    bool getGraphZone() { return graphZone; }
    void setGraphType(bool isTemp) { graphType = isTemp; }
    void setGraphZone(bool isHot) { graphZone = isHot; }
    int* getGraphData(bool isTemp, bool isHot, int timeType);
    int getGraphNumData(int timeType);

    void tick();
protected:
    ModelListener* modelListener;

    virtual void initGPIOs();
    virtual void mistGPIO();
    virtual void heatGPIO();

    virtual void initI2C();
    virtual void sensorLogic(int tickTim);
    virtual void sensorSelect(bool zoneSelect);
    virtual void sensorPrime();
    virtual void sensorRead(bool zoneSelect);

    // I2C Regs
    const uint8_t sensorAddr = 0x44;
    const uint8_t muxAddr = 0x70;
    bool errorI2C;
    bool errorMux;

    // Clock Vars
    int hour;
    int min;
    int sec;
    int tickTim;

    // Misting Vars
    bool isMisting; // State if mister is misting
    bool mistEn; // User set state of mister
    int humSet; // User set value of humidity level
    int warmHumVal; // Current humidity reading at warm zone
    int coldHumVal; // Current humidity reading at cold zone

    // Misting Clocking Vars
    int secsMisting; // Seconds misting has been on
    int secsSinceMisting; // Seconds since misting was last on
    int numTimesMisting; // Number of times misting has happened sequentially

    // Heating Vars
    bool isHeating; // State if heater is heating
    bool heatEn; // User set state of heater
    int tempSet; // User set value of temp level
    int warmTempVal; // Current temp reading at warm zone
    int coldTempVal; // Current temp reading at cold zone

    // Heating Clocking
    int secsHeating; // Seconds heating has been on

    // Bits for when we select a historical graph
    bool graphType; // true = temp, false = hum
    bool graphZone; // true = hot, false = cold

    // Last min data for graphs screen
    int num_secs; // Number of data points stored
    int hot_temp_secs[60];
    int cold_temp_secs[60];
    int hot_hum_secs[60];
    int cold_hum_secs[60];

    // Last hour data for graphs screen
    int num_mins; // Number of data points stored
    int hot_temp_mins[60];
    int cold_temp_mins[60];
    int hot_hum_mins[60];
    int cold_hum_mins[60];

    // Last day data for graphs screen
    int num_hours; // Number of data points stored
    int hot_temp_hours[24];
    int cold_temp_hours[24];
    int hot_hum_hours[24];
    int cold_hum_hours[24];

    // Last month data for graphs screen
    int num_days; // Number of data points stored
    int hot_temp_days[30];
    int cold_temp_days[30];
    int hot_hum_days[30];
    int cold_hum_days[30];
};

#endif // MODEL_HPP
