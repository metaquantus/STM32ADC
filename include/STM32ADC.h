#ifndef STM32ADC_H
#define STM32ADC_H

#include "Arduino.h"
#include "analog.h"

class STM32ADC {

public:
    STM32ADC(uint32_t ulPin, int resolution = 12, uint32_t cprescaler = ADC_CLOCK_SYNC_PCLK_DIV4, uint32_t stime = ADC_SAMPLETIME_3CYCLES, bool contConvMode = false, bool useInt = false) :
        _ulPin(ulPin), _clockPrescaler(cprescaler), _samplingTime(stime), _useInterrupt(useInt)
    {
        setResolution(resolution);
        setContinuousConvMode(contConvMode);
        _instance = this;
    }
    void useInterrupt(bool i) {
        _useInterrupt = i;
    }
    void setResolution(int r);
    void setSamplingTime(uint32_t st) {
        _samplingTime = st;
    }
    void setClockPrescaler(uint32_t cp) {
        _clockPrescaler = cp;
    }
    void setContinuousConvMode(bool m) {
        _continuousConvMode = m ? ENABLE : DISABLE;
    }
    void setContinuousConvMode(FunctionalState st) {
        _continuousConvMode = st;
    }
    bool begin();
    virtual uint32_t getValue();
    uint32_t getInterrupts();

    static void onADCInterrupt() {
        if ( _instance ) {
            _instance->onInterrupt();
        }
    }

protected:
    uint32_t _ulPin;
    uint32_t _channel = ADC_CHANNEL_0;
    uint32_t _resolution = ADC_RESOLUTION_12B;
    uint32_t _clockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
    uint32_t _samplingTime = ADC_SAMPLETIME_480CYCLES;
    FunctionalState _continuousConvMode = ENABLE;
    bool _useInterrupt = true;
    static STM32ADC* _instance;

    virtual void onInterrupt() {}
};


#endif