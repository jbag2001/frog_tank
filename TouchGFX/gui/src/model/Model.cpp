#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <stdint.h>
#include "stm32f7xx_hal.h"
#include "math.h"

static I2C_HandleTypeDef hi2c1;

Model::Model() : modelListener(0)
{
	// Clock Inits
	tickTim = 0;
	hour = 0;
	min = 0;
	sec = 0;

	// Mist Inits
    isMisting = false;
    mistEn = false;
    humSet = 70;
    warmHumVal = 0;
    coldHumVal = 0;

	secsMisting = 0;
	secsSinceMisting = 0;

	// Heat Inits
    isHeating = false;
    heatEn = false;
    tempSet = 75;
    warmTempVal = 0;
    coldTempVal = 0;

	secsHeating = 0;

    errorI2C = false;
    errorMux = false;

	initGPIOs();
	initI2C();
}

/**
 * Main loop running in the background of all screens.
 * Runs 60 times (ticks) in a second.
 */
void Model::tick()
{
	// Tells us each time any of the clocking values change
	// This is useful for updating graphing data and misting/heating element things
	int secChange = false;
	int minChange = false;
	int hourChange = false;
	int dayChange = false;

	// Handles clock timer
	if (tickTim++ == 59) { // 60 ticks in a second (60 fps)
		if (sec++ == 59) {
			if (min++ == 59) {
				if (hour++ == 23) {
					hour = 0;
					dayChange = true;
				}

				min = 0;
				hourChange = true;
			}

			sec = 0;
			minChange = true;
		}

		tickTim = 0;
		secChange = true;
	}

	// Handles sensor reading logic
	sensorLogic(tickTim);

	// Misting logic
	if (mistEn) {
		if (coldHumVal >= 0) { // Make sure the sensor is working

			// Humidity falls below the threshold
			// We're doing -10 because at 3s misting the humidity level rises around 20%
			// This just averages the humidity levels to the set value
			if (coldHumVal < humSet - 10) {
				if (isMisting) { // We are currently misting
					if (secChange) secsMisting++;
					if (secsMisting >= 3) { // Only mist for 3 seconds
						isMisting = false;
						secsMisting = 0;
						numTimesMisting++;
					}
				}
				else { // Waiting for the next cycle of misting to start
					if (secChange) secsSinceMisting++;
					if (secsSinceMisting >= 120) { // Wait 120 seconds until we mist again
						secsSinceMisting = 0;

						// We've misted X number of times and still haven't reached the threshold
						if (numTimesMisting >= 4) {
							mistEn = false;
							// TODO put alert here
						}
						else {
							isMisting = true;
						}
					}
				}
			}
			else { // Humidity levels are just right :)
				isMisting = false;
				numTimesMisting = 0;
				secsMisting = 0;
				secsSinceMisting = 115; // Set this high so system doesn't wait 2 mins before misting again
			}
		}
		else {
			// TODO Popup an alert here, commented out for testing
			mistEn = false;
		}

	}
	else {
		isMisting = false;
		secsMisting = 0;
		secsSinceMisting = 0;
		numTimesMisting = 0;
	}

	// Heating logic
	if (heatEn) {
		if(warmTempVal >= 0) { // Quick check that the sensors are working
			if (isHeating) {
				if (warmTempVal > tempSet)
					isHeating = false;
			}
			else if (warmTempVal < tempSet) {
				isHeating = true;
			}
		}
		else {
			// TODO Popup an alert here, commented out for testing
			// heatEn = false;
		}
	}
	else {
		isHeating = false;
		secsHeating = 0;
	}

	// Logic for managing seconds data for graphs
	if (secChange) {
		if (num_secs == 60) { // Shift data if max length is reached
			for (int i = 1; i < 60; i++) {
				hot_temp_secs[i-1] = hot_temp_secs[i];
				hot_hum_secs[i-1] = hot_hum_secs[i];
				cold_temp_secs[i-1] = cold_temp_secs[i];
				cold_hum_secs[i-1] = cold_hum_secs[i];
			}
		}
		else
			num_secs++;

		// Update last value to be latest reading
		hot_temp_secs[num_secs - 1] = warmTempVal;
		hot_hum_secs[num_secs - 1] = warmHumVal;
		cold_temp_secs[num_secs - 1] = coldTempVal;
		cold_hum_secs[num_secs - 1] = coldHumVal;
	}

	// Logic for managing minutes data for graphs
	if (minChange) {
		if (num_mins == 60) { // Shift data if max length is reached
			for (int i = 1; i < 60; i++) {
				hot_temp_mins[i-1] = hot_temp_mins[i];
				hot_hum_mins[i-1] = hot_hum_mins[i];
				cold_temp_mins[i-1] = cold_temp_mins[i];
				cold_hum_mins[i-1] = cold_hum_mins[i];
			}
		}
		else
			num_mins++;

		// Update last value to be latest reading
		long warmTempSum = 0;
		long warmHumSum = 0;
		long coldTempSum = 0;
		long coldHumSum = 0;

		// We don't have to worry about dividing by zero
		// Because there should always at least be one data point

		for (int i = 0; i < num_secs; i++) {
			warmTempSum += hot_temp_secs[i];
			warmHumSum += hot_hum_secs[i];
			coldTempSum += cold_temp_secs[i];
			coldHumSum += cold_hum_secs[i];
		}

		hot_temp_mins[num_mins - 1] = warmTempSum / num_secs;
		hot_hum_mins[num_mins - 1] = warmHumSum / num_secs;
		cold_temp_mins[num_mins - 1] = coldTempSum / num_secs;
		cold_hum_mins[num_mins - 1] = coldHumSum / num_secs;
	}

	// Logic for managing hours data for graphs
	if (hourChange) {
		if (num_hours == 24) { // Shift data if max length is reached
			for (int i = 1; i < 24; i++) {
				hot_temp_hours[i-1] = hot_temp_hours[i];
				hot_hum_hours[i-1] = hot_hum_hours[i];
				cold_temp_hours[i-1] = cold_temp_hours[i];
				cold_hum_hours[i-1] = cold_hum_hours[i];
			}
		}
		else
			num_hours++;

		// Update last value to be latest reading
		long warmTempSum = 0;
		long warmHumSum = 0;
		long coldTempSum = 0;
		long coldHumSum = 0;

		// We don't have to worry about dividing by zero
		// Because there should always at least be one data point

		for (int i = 0; i < num_mins; i++) {
			warmTempSum += hot_temp_mins[i];
			warmHumSum += hot_hum_mins[i];
			coldTempSum += cold_temp_mins[i];
			coldHumSum += cold_hum_mins[i];
		}

		hot_temp_hours[num_hours - 1] = warmTempSum / num_mins;
		hot_hum_hours[num_hours - 1] = warmHumSum / num_mins;
		cold_temp_hours[num_hours - 1] = coldTempSum / num_mins;
		cold_hum_hours[num_hours - 1] = coldHumSum / num_mins;
	}

	// Logic for managing days data for graphs
	if (dayChange) {
		if (num_days == 30) { // Shift data if max length is reached
			for (int i = 1; i < 30; i++) {
				hot_temp_days[i-1] = hot_temp_days[i];
				hot_hum_days[i-1] = hot_hum_days[i];
				cold_temp_days[i-1] = cold_temp_days[i];
				cold_hum_days[i-1] = cold_hum_days[i];
			}
		}
		else
			num_days++;

		// Update last value to be latest reading
		long warmTempSum = 0;
		long warmHumSum = 0;
		long coldTempSum = 0;
		long coldHumSum = 0;

		// We don't have to worry about dividing by zero
		// Because there should always at least be one data point

		for (int i = 0; i < num_hours; i++) {
			warmTempSum += hot_temp_hours[i];
			warmHumSum += hot_hum_hours[i];
			coldTempSum += cold_temp_hours[i];
			coldHumSum += cold_hum_hours[i];
		}

		hot_temp_days[num_days - 1] = warmTempSum / num_hours;
		hot_hum_days[num_days - 1] = warmHumSum / num_hours;
		cold_temp_days[num_days - 1] = coldTempSum / num_hours;
		cold_hum_days[num_days - 1] = coldHumSum / num_hours;
	}



	// Update UI in a per second basis
	if (secChange) {
		// Update GPIOs here so they don't get stuck in a random if-statement
		mistGPIO();
		heatGPIO();

		modelListener->updateLiveGraph();
		modelListener->updateClock();
		modelListener->updateIcons();
		modelListener->updateReadings();
	}
}

/**
 * Handles the logic of reading from the sensors.
 * This is time based to ensure proper timing of read and write of the mux and sensors.
 * @param tick - Tick of the 60 fps timer
 */
void Model::sensorLogic(int tick) {
	switch (tick) {
		// HOT ZONE SENSOR LOGIC
		case 0: sensorSelect(true); // Selects the hot zone sensor.
			break;
		case 10: sensorPrime(); // Primes selected sensor.
			break;
		case 20: sensorRead(true); // Reads sensor data.
			break;

		// COLD ZONE SENSOR LOGIC
		case 30: sensorSelect(false); // Selects the cold zone sensor.
			break;
		case 40: sensorPrime(); // Primes selected sensor.
			break;
		case 50: sensorRead(false); // Reads sensor data.
			break;
	}
}

/**
 * Initializes the I2C module of the CPU.
 */
void Model::initI2C() {
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x20404768;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
		errorI2C = true;

	// Configure Analogue filter
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
		errorI2C = true;

	//Configure Digital filter
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
		errorI2C = true;
}

/**
 * Switches the i2c mux to a selected sensor.
 * @param zoneSelect - true: hot zone, false: cold zone
 */
void Model::sensorSelect(bool zoneSelect) {
	uint8_t data[1];

	if (zoneSelect) data[0] = 0x01;
	else data[0] = 0x02;


	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c1, muxAddr<<1, data, 1, 50);

	if (ret != HAL_OK)
		errorMux = true;
}

/**
 * Primes the sensor that a read request of the data will be sent.
 */
void Model::sensorPrime() {
	uint8_t data[2] = {0x24, 0x16};
	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c1, sensorAddr<<1, data, 2, 50);

	if (ret != HAL_OK)
		errorI2C = true;
}

/**
 * Primes the sensor that a read request of the data will be sent.
 * @param zoneSelect - true: hot zone, false: cold zone
 */
void Model::sensorRead(bool zoneSelect) {
	uint8_t data[6];
	HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(&hi2c1, (sensorAddr<<1) | 0x01, data, 6, 50);

	if (ret == HAL_OK) {
		// Return data is split into different bytes, this is defiend in the sensor datasheet
		uint16_t readTemp = (data[0]<<8) | data[1];
		uint16_t readHum = (data[3]<<8) | data[4];

		// These calculations are defined in the sensor datasheet
		int tempVal = -49 + 315 * ((double)readTemp / (-1 + pow(2,16)));
		int humVal = 100 * ((double)readHum / (-1 + pow(2,16)));

		if (zoneSelect) { // Warm sensor is selected
			warmTempVal = tempVal;
			warmHumVal = humVal;
		}
		else { // Cold sensor is selected
			coldTempVal = tempVal;
			coldHumVal = humVal;
		}
	}
	else {
		errorI2C = true;
	}
}

/**
 * Initialize GPIO pins for heating/misting
 */
void Model::initGPIOs() {
	__HAL_RCC_GPIOG_CLK_ENABLE();

	// General settings for a GPIO output pin
	GPIO_InitTypeDef settings;
	settings.Mode = GPIO_MODE_OUTPUT_PP;
	settings.Pull = GPIO_PULLUP;
	settings.Speed = GPIO_SPEED_FAST;

	// Init PG7
	settings.Pin = (GPIO_PIN_7);
	HAL_GPIO_Init(GPIOG, &settings);

	// Init PI0
	settings.Pin = (GPIO_PIN_0);
	HAL_GPIO_Init(GPIOI, &settings);

	// Init pins at high to disable mister and heating
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
}

/**
 * Sets the GPIO state of the mister
 */
void Model::mistGPIO () {
	if (isMisting)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
}

/**
 * Sets the GPIO state of the heater
 */
void Model::heatGPIO () {
	if (isHeating)
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
}

int* Model::getGraphData(bool isTemp, bool isHot, int timeType) {
	if (timeType == 0) { // Last hour data
		if (isHot && isTemp)
			return hot_temp_mins;
		else if (isHot && !isTemp)
			return hot_hum_mins;
		else if (!isHot && isTemp)
			return cold_temp_mins;
		else if (!isHot && !isTemp)
			return cold_hum_mins;
	}
	else if (timeType == 1) { // Last day data
		if (isHot && isTemp)
			return hot_temp_hours;
		else if (isHot && !isTemp)
			return hot_hum_hours;
		else if (!isHot && isTemp)
			return cold_temp_hours;
		else if (!isHot && !isTemp)
			return cold_hum_hours;
	}
	else if (timeType == 2) { // Last month data
		if (isHot && isTemp)
			return hot_temp_days;
		else if (isHot && !isTemp)
			return hot_hum_days;
		else if (!isHot && isTemp)
			return cold_temp_days;
		else if (!isHot && !isTemp)
			return cold_hum_days;
	}
	else if (timeType == 3) { // Live data type
		if (isHot && isTemp)
			return hot_temp_secs;
		else if (isHot && !isTemp)
			return hot_hum_secs;
		else if (!isHot && isTemp)
			return cold_temp_secs;
		else if (!isHot && !isTemp)
			return cold_hum_secs;
	}

	return {};
}

int Model::getGraphNumData(int timeType) {
	if (timeType == 0)
		return num_mins;
	else if (timeType == 1)
		return num_hours;
	else if (timeType == 2)
	 	return num_days;
	else if (timeType == 3)
		return num_secs;

	return 0;
}
