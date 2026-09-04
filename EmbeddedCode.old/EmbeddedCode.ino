// HW Pins
#define I2cSda 22 
#define I2cScl 23
#define BmsInt 6            // BQ25895 Interrupt
#define BmsOtg 21           // BQ25895 OTG enable
#define BmsCe 16            // BQ25895 Charge enable
#define BuckPwrOK 3         // MP8715 Buck Power OK flag
#define MuxS0 11
#define MuxS1 10
#define MuxS2 9
#define MuxS3 8
#define MuxResEn 18         // Base resistor MUX enable
#define MuxResOut 0         // Base resistor value
#define MuxNeoPixelEn 15    // Base NeoPixel MUX enable
#define MuxNeoPixelOut 19   // Base NeoPixel signal
#define HelixNeoPixel 20    // Helix NeoPixel signal
#define TouchButton 2       // Main control touch button
#define BackboardButton 7   // Hidden "factory reset" button
#define LightSensor 1       // TEMT6000 readout
#define GyroInt 17          // MPU6050 Interrupt
#define AudioPlayer 5       // DFPlayer Mini TX
#define FanControl 4        // built-in fan Switch (HIGH-LOW)

// Default values
#define I2cFreq 100000
#define DnaBaseCount 13 // includes 12 in helix + 1 bonus in foundation
#define HelixNeoPixelCount 40