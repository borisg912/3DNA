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
#define AudioPlayer 5
#define FanControl 4
#define GyroInt 17

// Default values
#define DnaBaseCount 13 // includes 12 in helix + 1 bonus in foundation
#define HelixNeoPixelCount 20


// Electrical constants
const float VREF = 3.0f;
const uint16_t ADC_MAX = 4095;
const float R_DIVIDER_OHMS = 10000.0f;  // Fixed 10k resistor to 3V in the divider

// Channel/base layout
const uint8_t BASE_CHANNEL_COUNT = 16;
const uint8_t HELIX_PIXEL_COUNT = 1;  // one active pixel path selected per MUX channel
const uint8_t DEFAULT_BRIGHTNESS = 50;

Adafruit_NeoPixel helixPixels(HELIX_PIXEL_COUNT, PIN_NEOPIXEL_DATA, NEO_GRB + NEO_KHZ800);

enum DnaBase : uint8_t {
  BASE_UNKNOWN = 0,
  BASE_A,
  BASE_T,
  BASE_C,
  BASE_G
};

struct ResistorBaseMap {
  float minOhms;
  float maxOhms;
  DnaBase base;
};

// TODO: Replace with your exact measured resistor windows (with tolerance)
const ResistorBaseMap RESISTOR_MAP[] = {
  {900.0f, 1100.0f, BASE_A},
  {1800.0f, 2200.0f, BASE_T},
  {2700.0f, 3300.0f, BASE_C},
  {3900.0f, 4700.0f, BASE_G},
};

const uint8_t RESISTOR_MAP_COUNT = sizeof(RESISTOR_MAP) / sizeof(RESISTOR_MAP[0]);

void setMuxChannel(uint8_t channel) {
  digitalWrite(PIN_MUX_S0, (channel & 0x01) ? HIGH : LOW);
  digitalWrite(PIN_MUX_S1, (channel & 0x02) ? HIGH : LOW);
  digitalWrite(PIN_MUX_S2, (channel & 0x04) ? HIGH : LOW);
  digitalWrite(PIN_MUX_S3, (channel & 0x08) ? HIGH : LOW);
}

float readBaseResistanceOhms(uint8_t channel) {
  setMuxChannel(channel);
  delayMicroseconds(50);

  uint16_t adc = analogRead(PIN_RESISTOR_ADC);
  if (adc == 0 || adc >= ADC_MAX) {
    return -1.0f;
  }

  float vOut = (static_cast<float>(adc) / static_cast<float>(ADC_MAX)) * VREF;
  if (vOut <= 0.0f || vOut >= VREF) {
    return -1.0f;
  }

  // Voltage divider: Vout = Vref * (Rbase / (Rdivider + Rbase))
  // => Rbase = Rdivider * Vout / (Vref - Vout)
  return R_DIVIDER_OHMS * vOut / (VREF - vOut);
}

DnaBase baseFromResistance(float resistanceOhms) {
  if (resistanceOhms <= 0.0f) {
    return BASE_UNKNOWN;
  }

  for (uint8_t i = 0; i < RESISTOR_MAP_COUNT; ++i) {
    if (resistanceOhms >= RESISTOR_MAP[i].minOhms && resistanceOhms <= RESISTOR_MAP[i].maxOhms) {
      return RESISTOR_MAP[i].base;
    }
  }
  return BASE_UNKNOWN;
}

bool isValidPair(DnaBase left, DnaBase right) {
  if (left == BASE_A && right == BASE_T) return true;
  if (left == BASE_T && right == BASE_A) return true;
  if (left == BASE_C && right == BASE_G) return true;
  if (left == BASE_G && right == BASE_C) return true;
  return false;
}

void setBrightness(uint8_t brightness) {
  helixPixels.setBrightness(brightness);
  helixPixels.show();
}

void setBaseColor(uint8_t channel, uint8_t r, uint8_t g, uint8_t b) {
  setMuxChannel(channel);
  helixPixels.setPixelColor(0, helixPixels.Color(r, g, b));
  helixPixels.show();
}

void setAllBasesColor(uint8_t r, uint8_t g, uint8_t b, uint16_t holdMs = 10) {
  for (uint8_t ch = 0; ch < BASE_CHANNEL_COUNT; ++ch) {
    setBaseColor(ch, r, g, b);
    delay(holdMs);
  }
}

void evaluatePairAndLight(uint8_t channelA, uint8_t channelB) {
  float rA = readBaseResistanceOhms(channelA);
  float rB = readBaseResistanceOhms(channelB);

  DnaBase baseA = baseFromResistance(rA);
  DnaBase baseB = baseFromResistance(rB);

  bool valid = isValidPair(baseA, baseB);
  if (valid) {
    setBaseColor(channelA, 0, 200, 0);
    setBaseColor(channelB, 0, 200, 0);
  } else {
    setBaseColor(channelA, 200, 0, 0);
    setBaseColor(channelB, 200, 0, 0);
  }
}

void setup() {
  pinMode(PIN_MUX_S0, OUTPUT);
  pinMode(PIN_MUX_S1, OUTPUT);
  pinMode(PIN_MUX_S2, OUTPUT);
  pinMode(PIN_MUX_S3, OUTPUT);
  pinMode(PIN_RESISTOR_ADC, INPUT);

  Serial.begin(115200);
  analogReadResolution(12);

  helixPixels.begin();
  helixPixels.clear();
  helixPixels.show();
  setBrightness(DEFAULT_BRIGHTNESS);

  // Startup indicator
  setAllBasesColor(0, 0, 30, 8);
  setAllBasesColor(0, 0, 0, 2);
}

void loop() {
  // Pair channels in adjacent slots: (0,1), (2,3), ...
  for (uint8_t ch = 0; ch < BASE_CHANNEL_COUNT; ch += 2) {
    evaluatePairAndLight(ch, ch + 1);
    delay(20);
  }

  delay(120);
}
