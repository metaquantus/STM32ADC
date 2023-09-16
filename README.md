# STM32ADC
An Arduino library to use the advanced capabilities of the STM32 MCUs analog to digital converters. 

This library supports the stm32duino Arduino core and it access the ADC through the STM32 HAL libraries. 

The standard Arduino function, analogRead, is implemented by initializing and configuring the ADC, starting and polling a conversion and later deinitializing the hardware. This happens every in every call. Configuration of some parameters of ADC is done via C preprocessor define macros. 

The purpose of this library is to offer a dynamic way of configuring the ADC and support for other modes of operations like continuous conversion, interrupt, scan and DMA modes.

>[!IMPORTANT]
>Use of the Arduino `analogRead`` function while using this library will
>interfere with proper operation of the library.



