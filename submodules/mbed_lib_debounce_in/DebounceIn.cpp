#include "DebounceIn.hpp"

DebounceIn::DebounceIn(PinName _interruptIn, uint16_t _debounceTimeoutInMs) : interruptPin(_interruptIn) {

    debounceTimeoutInMs = _debounceTimeoutInMs;

    registerIntCallback();
}

DebounceIn::~DebounceIn() {
    timer.detach();
}

void DebounceIn::onIntFall() {
    deregisterIntCallback();
    timer.attach(callback(this, &DebounceIn::isrFall), debounceTimeoutInMs / 1000.0);
}

void DebounceIn::onIntRise() {
    deregisterIntCallback();
    timer.attach(callback(this, &DebounceIn::isrRise), debounceTimeoutInMs / 1000.0);
}

void DebounceIn::isrFall() {
if (interruptPin.read() == 0 && fallCallback) {
        fallCallback();
    }
    registerIntCallback();
}

void DebounceIn::isrRise() {
    if (interruptPin.read() == 1 && riseCallback) {
        riseCallback();
    }
    registerIntCallback();
}

void DebounceIn::registerIntCallback() {
    interruptPin.fall(callback(this, &DebounceIn::onIntFall));
    interruptPin.rise(callback(this, &DebounceIn::onIntRise));
}

void DebounceIn::deregisterIntCallback() {
    interruptPin.fall(NULL);
    interruptPin.rise(NULL);
}

void DebounceIn::fall(Callback<void()> func) {
    fallCallback = func;
}

void DebounceIn::rise(Callback<void()> func) {
    riseCallback = func;
}

