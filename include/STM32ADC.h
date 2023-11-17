#ifndef STM32ADC_H
#define STM32ADC_H

#include <Arduino.h>
#include <analog.h>

#define STM32ADC_MAX_CHANNELS 16

class STM32ADC {

public:
    STM32ADC(int resolution = 12, uint32_t cprescaler = ADC_CLOCK_SYNC_PCLK_DIV8, bool contConvMode = true, bool useInt = true) :
        _clockPrescaler(cprescaler), _useInterrupt(useInt), _connected(false), _started(false)
    {
        setResolution(resolution);
        setContinuousConvMode(contConvMode);
        _instance = this;
    }
    // following functions to be called before begin()

    void useInterrupt(bool i) {
        _useInterrupt = i;
    }
    void setResolution(int r);

    void setClockPrescaler(uint32_t cp) {
        _clockPrescaler = cp;
    }
    void setContinuousConvMode(bool m) {
        _continuousConvMode = m ? ENABLE : DISABLE;
    }
    void setContinuousConvMode(FunctionalState st) {
        _continuousConvMode = st;
    }

    // adds a new conversion channel by Pin name, use pseudo-pins ATEMP, AVREF, or AVBAT for internal channels.
    // returns the rank (logical channel number) for this channel or -1 if no more channels available (max 16 conversions)
    // Each channel can have different sampling time
    // In MCUs with more than one ADC, all channels must belong to the same ADC unit. 
    int addChannel(uint32_t _ulPin, uint32_t stime);

    // initializes the ADC hardware & channels
    bool begin();
    // this indicates ADC was configured and is being used
    bool isConnected() {
        return _connected;
    }
    bool end();
    // start conversion if in interrupt mode
    void start();

    // gets the conversion value for the given channel rank (logical channel nummber)
    virtual uint32_t getValue(int rank);
    // for debugging
    uint32_t getInterrupts();

    static void onADCInterrupt() {
        if ( _instance ) {
            _instance->onInterrupt();
        }
    }

    static void onADCError() {
        if ( _instance ) {
            _instance->onError();
        }
    }

protected:
    uint32_t _ulPins[STM32ADC_MAX_CHANNELS];
    int _channels; // number of channels to convert, max 16
    uint16_t _dmaBuf[STM32ADC_MAX_CHANNELS]; // DMA data buffer for conversion
    uint32_t _resolution = ADC_RESOLUTION_12B;
    uint32_t _clockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
    uint32_t _samplingTimes[STM32ADC_MAX_CHANNELS]; // e.g. ADC_SAMPLETIME_480CYCLES, each channel has its own sampletime
    FunctionalState _continuousConvMode = ENABLE;
    bool _useInterrupt = true;
    bool _connected = false;
    bool _started = false;

    static STM32ADC* _instance;

    virtual void onInterrupt() {}
    virtual void onError() {}

};


#endif
