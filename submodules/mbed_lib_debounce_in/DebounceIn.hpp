/**
 *******************************************************************************
 * @file        DebounceIn.hpp
 * @brief       Class for handling debouncing on interrupt pin
 * @author      ocecelja
 * @version     v01.0.0
 * @copyright   free to use
 *******************************************************************************
 */

#include "mbed.h"
#include "LowPowerTimer.h"

#ifndef MBED_APP_NRF52840_BLE_GARAGE_DOOR_TX_DEBOUNCEIN_HPP
#define MBED_APP_NRF52840_BLE_GARAGE_DOOR_TX_DEBOUNCEIN_HPP

class DebounceIn {
private:
    LowPowerTimeout timer;
    InterruptIn interruptPin;
    uint16_t debounceTimeoutInMs;

    void registerIntCallback();
    void deregisterIntCallback();

    void onIntFall();
    void onIntRise();

    void isrFall();
    void isrRise();

    Callback<void()> fallCallback;
    Callback<void()> riseCallback;

public:
    DebounceIn(PinName _interruptIn, uint16_t _debounceTimeoutInMs = 50);

    ~DebounceIn();

    void fall(Callback<void()> func);
    void rise(Callback<void()> func);
};


#endif //MBED_APP_NRF52840_BLE_GARAGE_DOOR_TX_DEBOUNCEIN_HPP
