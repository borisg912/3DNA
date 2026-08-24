#include <Adafruit_NeoPixel.h>

// HW Pins
#define I2cSda 22
#define I2cScl 23
#define BmsInt 6
#define BmsOtg 21
#define BmsCe 16
#define BuckPwrOK 3
#define MuxS0 11
#define MuxS1 10
#define MuxS2 9
#define MuxS3 8
#define MuxResEn 18
#define MuxResOut 0
#define MuxNeoPixelEn 15
#define MuxNeoPixelOut 19
#define HelixNeoPixel 20
#define TouchButton 2
#define BackboardButton 7
#define LightSensor 1
#define GyroInt 17
#define AudioPlayer 5
#define FanControl 4

// Default values
#define DnaBaseCount 13 // includes 12 in helix + 1 bonus in foundation
#define HelixNeoPixelCount 0

void setup() {
  pinMode(MuxS0, OUTPUT); pinMode(MuxS1, OUTPUT);
  pinMode(MuxS2, OUTPUT); pinMode(MuxS3, OUTPUT);
  pinMode(MuxNeoPixelEn, OUTPUT); pinMode(MuxResEn, OUTPUT);
  pinMode(MuxNeoPixelOut, OUTPUT); pinMode(MuxResOut, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  
}
