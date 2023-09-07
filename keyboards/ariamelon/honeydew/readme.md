# Honeydew

~60% 63-key QMK-compatible unsplit ergonomic keyboard.

* Keyboard Maintainer: [Ariamelon](https://github.com/Ariamelon)
* Hardware Availability: [Ariamelon](https://github.com/Ariamelon/Honeydew/)

Make example for this keyboard (after setting up your build environment):

    make ariamelon/honeydew:default

Flashing example for this keyboard:

    make ariamelon/honeydew:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader by holding down the reset button on the bottom of the keyboard.

## Changelog
* 07/09/2023: Added V3 support. Moved some of the RP2040-specific settings to the individual version folders. 
* 04/07/2023: Moved some RGB matrix settings to info.json. Changed ADC EMA alpha definition and EMA equation. 
* 01/07/2023: Separated V2 USBPD and ADC functions into different files. Added exponential moving average to ADC functionality to get better accuracy. Renamed adc_values to adc_values_t for better clarity.
* 30/06/2023: Updated V2 ADC code to not use floats.
* 28/06/2023: Modified V2 USB PD code to work like tzarc's. Added working ADC implementation. Started adding QP support.
* 26/06/2023: Fixed V2 matrix code (thanks elpekenin and drfaustroll!). Fixed RGB.
* 25/06/2023: Initial dev firmware uploaded.
