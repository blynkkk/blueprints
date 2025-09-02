// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates

#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
// #define BLYNK_DEBUG

#define APP_DEBUG

#define USE_XC01_R5

#include <Arduino.h>
#include <Wire.h>
#include "BlynkEdgent.h"
#include "RGBLed.h"

// Virtual pins on Blynk side
#define VPIN_TEMP V0
#define VPIN_HUM V1
#define VPIN_LUM V2

#define VPIN_I1 V3
#define VPIN_I2 V4
#define VPIN_I3 V5
#define VPIN_I4 V6

#define VPIN_O1 V7
#define VPIN_O2 V8
#define VPIN_O3 V9
#define VPIN_O4 V10

#define VPIN_RGB V11
#define VPIN_BUTTON V12
#define VPIN_BRIGHTNESS V13
#define VPIN_ANIMATION_SPEED V14

#define VPIN_POT V15

#define VPIN_AN1 V16
#define VPIN_AN2 V17
#define VPIN_AN3 V18

// XNODE I2C configuration
#define XN01_TW_ADD 0x01
#define XN02_TW_ADD 0x02
#define XN03_TW_ADD 0x03
#define XN04_TW_ADD 0x04

// This function creates the rgb led object. It's used to control RGB animations
RGBLed rgb_animation;

// This function creates the timer object. It's part of Blynk library
BlynkTimer timer;

int rgb_animation_speed = 1000; // Default animation speed

// updateAndSend XN01 - Digital Input's data
void updateAndSendXN01()
{
  static uint8_t prev_input = 0;
  uint8_t current_input = 0;

  Wire.beginTransmission(XN01_TW_ADD);
  Wire.write(XN01_TW_ADD);
  if (Wire.endTransmission() != 0)
    return;

  if (Wire.requestFrom(XN01_TW_ADD, 1) != 1)
    return;

  current_input = Wire.read();

  // Only send data to Blynk if something has changed
  if (prev_input == current_input)
    return;

  // Bit mask and shift of the first four inputs
  if ((0x01 & prev_input) != (0x01 & current_input))
    Blynk.virtualWrite(VPIN_I1, (current_input & 0x01));
  if ((0x02 & prev_input) != (0x02 & current_input))
    Blynk.virtualWrite(VPIN_I2, ((current_input & 0x02) >> 1));
  if ((0x04 & prev_input) != (0x04 & current_input))
    Blynk.virtualWrite(VPIN_I3, ((current_input & 0x04) >> 2));
  if ((0x08 & prev_input) != (0x08 & current_input))
    Blynk.virtualWrite(VPIN_I4, ((current_input & 0x08) >> 3));

  prev_input = current_input;

  return;
}

// Write to XN02 - Digital Outputs
bool writeXN02(uint8_t output, uint8_t state)
{
  static uint8_t outputs = 0;

  if (output < 1 || output > 8)
    return false;

  Wire.beginTransmission(XN02_TW_ADD);
  if (Wire.endTransmission() != 0)
    return false;

  outputs &= ~(1 << (output - 1));

  outputs |= (state << (output - 1));

  Wire.beginTransmission(XN02_TW_ADD);
  Wire.write(0x01);
  Wire.write(outputs);
  if (Wire.endTransmission() != 0)
    return false;

  return true;
}

// updateAndSend XN03 - Analog Inputs/Outputs Potentiometer
void updateAndSendXN03()
{
  static uint8_t prev_pot_position = 0;
  static uint8_t prev_i1_value = 0;
  static uint8_t prev_i2_value = 0;
  static uint8_t prev_i3_value = 0;

  uint8_t adc_values[4] = {0};

  for ( uint8_t i = 0; i < 4; i++ ){
    Wire.beginTransmission(XN03_TW_ADD);
    if (Wire.endTransmission() != 0)
      return;

    Wire.beginTransmission(XN03_TW_ADD);
    Wire.write(0x10 + i);
    if (Wire.endTransmission() != 0)
      return;

    if (Wire.requestFrom(XN03_TW_ADD, 1) != 1)
      return;

    adc_values[i] = Wire.read();
  }

  // Only send data to Blynk if the values
  // have changed more than 2%
  if (abs((int)prev_pot_position - (int)adc_values[0]) > 2) {
    prev_pot_position = adc_values[0];
    Blynk.virtualWrite(VPIN_POT, prev_pot_position);
  }

  if (abs((int)prev_i1_value - (int)adc_values[1]) > 2) {
    prev_i1_value = adc_values[1];
    Blynk.virtualWrite(VPIN_AN1, prev_i1_value);
  }

  if (abs((int)prev_i2_value - (int)adc_values[2]) > 2) {
    prev_i2_value = adc_values[2];
    Blynk.virtualWrite(VPIN_AN2, prev_i2_value);
  }

  if (abs((int)prev_i3_value - (int)adc_values[3]) > 2) {
    prev_i3_value = adc_values[3];
    Blynk.virtualWrite(VPIN_AN3, prev_i3_value);
  }

  return;
}

// Write to XN03 - Analog Inputs/Outputs RGB Led
void writeRgbXN03(int red, int green, int blue)
{

  Wire.beginTransmission(XN03_TW_ADD);
  if (Wire.endTransmission() != 0)
  {
    return;
  }

  Wire.beginTransmission(XN03_TW_ADD);
  Wire.write(0x01);
  Wire.write((uint8_t)red);
  Wire.write((uint8_t)green);
  Wire.write((uint8_t)blue);
  Wire.endTransmission();
}

// updateAndSend XN03 - Analog Inputs/Outputs Potentiometer
void updateAndSendXN04()
{
  static float prev_temp = 0, prev_hum = 0, prev_lum = 0;
  float temp, hum, lum;

  uint8_t rx_bytes[2];

  Wire.beginTransmission(XN04_TW_ADD);
  Wire.write(0x01);
  if (Wire.endTransmission() != 0)
    return;

  if (Wire.requestFrom(XN04_TW_ADD, 0x02) < 2)
    return;

  Wire.readBytes(rx_bytes, 2);

  // Divide by 100 to obtain °C
  temp = ((rx_bytes[0] << 8) | (rx_bytes[1])) / 100.0f;

  Wire.beginTransmission(XN04_TW_ADD);
  Wire.write(0x02);
  if (Wire.endTransmission() != 0)
    return;

  if (Wire.requestFrom(XN04_TW_ADD, 0x02) < 2)
    return;

  Wire.readBytes(rx_bytes, 2);

  // Divide by 100 to obtain %
  hum = ((rx_bytes[0] << 8) | (rx_bytes[1])) / 100.0f;

  Wire.beginTransmission(XN04_TW_ADD);
  Wire.write(0x03);
  if (Wire.endTransmission() != 0)
    return;

  if (Wire.requestFrom(XN04_TW_ADD, 0x02) < 2)
    return;

  Wire.readBytes(rx_bytes, 2);

  lum = (rx_bytes[0] << 8) | (rx_bytes[1]);

  // Only send data to Blynk if temperature
  // has changed by at least 0.5°C
  if (abs(temp - prev_temp) > 0.5f)
  {
    prev_temp = temp;
    Blynk.virtualWrite(VPIN_TEMP, temp);
  }

  // Only send data to Blynk if humidity
  // has changed by at least 0.8%
  if (abs(hum - prev_hum) > 0.8f)
  {
    prev_hum = hum;
    Blynk.virtualWrite(VPIN_HUM, hum);
  }

  // Only send data to Blynk if ambient light
  // has changed by at least 6 lux
  if (abs(lum - prev_lum) > 6.0f)
  {
    prev_lum = lum;
    Blynk.virtualWrite(VPIN_LUM, lum);
  }
}

void updateAndSendData()
{
  updateAndSendXN01();
  updateAndSendXN03();
  updateAndSendXN04();
}

// Datastream to control XN02 - O1 signal
BLYNK_WRITE(VPIN_O1)
{
  int state = param.asInt();

  if (state > 1 || state < 0)
    return;

  writeXN02(1, state);
  return;
}

// Datastream to control XN02 - O2 signal
BLYNK_WRITE(VPIN_O2)
{
  int state = param.asInt();

  if (state > 1 || state < 0)
    return;

  writeXN02(2, state);
  return;
}

// Datastream to control XN02 - O3 signal
BLYNK_WRITE(VPIN_O3)
{
  int state = param.asInt();

  if (state > 1 || state < 0)
    return;

  writeXN02(3, state);
  return;
}

// Datastream to control XN02 - O4 signal
BLYNK_WRITE(VPIN_O4)
{
  int state = param.asInt();

  if (state > 1 || state < 0)
    return;

  writeXN02(4, state);
  return;
}

// Datastream to control XN03 RGB Led
BLYNK_WRITE(VPIN_RGB)
{
  // Array to store the RGB animation steps (colors)
  RGB_t colors[RGB_ANIMATION_BUFFER_SIZE];

  // Blynk RGB widget data
  uint8_t rgb_light_control_mode = 0; // 0 = mode unknown, 1 = Color, 2 = White, 3 = Animation
  uint8_t animation_fade_strobe = 0;  // 0 = mode unknown, 1 = strobe, 2 = fade
  RGB_t rgb_color_white_mode;
  uint8_t animation_pattern_count = 0; // either 3 or 2 when known
  RGB_t rgb_animation_left;
  RGB_t rgb_animation_right;
  RGB_t rgb_animation_top;

  byte param_items_count = 0;
  for (auto i = param.begin(); i < param.end(); ++i)
  {
    if (param_items_count == 3)
    {
      String button_mode = i.asString();
      if (button_mode == "true")
      {
        rgb_light_control_mode = 1; // Color Mode
      }
      else if (button_mode == "false")
      {
        rgb_light_control_mode = 2; // White Mode
      }
    }
    if (param_items_count == 4)
    {
      rgb_light_control_mode = 3; // Animation mode
      int fade_strobe = param[4].asInt();
      if (fade_strobe == 0)
      {
        animation_fade_strobe = 2; // fade
      }
      else if (fade_strobe == 1)
      {
        animation_fade_strobe = 1; // strobe
      }
      else
      {
        animation_fade_strobe = 0;
      }
    }
    param_items_count++;
  }

  rgb_color_white_mode.r = param[0].asInt();
  rgb_color_white_mode.g = param[1].asInt();
  rgb_color_white_mode.b = param[2].asInt();

  if (param_items_count > 4)
  {
    rgb_animation_left.r = param[5].asInt();
    rgb_animation_left.g = param[6].asInt();
    rgb_animation_left.b = param[7].asInt();
  }
  if (param_items_count == 11)
  {
    animation_pattern_count = 2;
    rgb_animation_top.r = 0;
    rgb_animation_top.g = 0;
    rgb_animation_top.b = 0;
    rgb_animation_right.r = param[8].asInt();
    rgb_animation_right.g = param[9].asInt();
    rgb_animation_right.b = param[10].asInt();
  }
  else if (param_items_count == 14)
  {
    animation_pattern_count = 3;
    rgb_animation_top.r = param[8].asInt();
    rgb_animation_top.g = param[9].asInt();
    rgb_animation_top.b = param[10].asInt();
    rgb_animation_right.r = param[11].asInt();
    rgb_animation_right.g = param[12].asInt();
    rgb_animation_right.b = param[13].asInt();
  }
  else
  {
    animation_pattern_count = 0;
  }

  switch (rgb_light_control_mode)
  {
  case 0:
    // button mode unknown
    rgb_animation.off();
    break;
  case 1:
    // Color Mode
    rgb_animation.setColor(rgb_color_white_mode);
    break;
  case 2:
    // White Mode
    rgb_animation.setColor(rgb_color_white_mode);
    break;
  case 3:
    if (animation_pattern_count == 0)
    {
      if ((rgb_animation_left == RGBLed::RED) && (rgb_animation_right == RGBLed::BLACK))
      {
        // Special case: Rainbow
        colors[0] = RGBLed::RED;
        colors[1] = RGBLed::YELLOW;
        colors[2] = RGBLed::GREEN;
        colors[3] = RGBLed::CYAN;
        colors[4] = RGBLed::BLUE;
        colors[5] = RGBLed::MAGENTA;
        animation_pattern_count = 6;
      }
    }
    else if (animation_pattern_count == 2)
    {
      colors[0] = rgb_animation_left;
      colors[1] = rgb_animation_right;
      animation_pattern_count = 2;
    }
    else if (animation_pattern_count == 3)
    {
      colors[0] = rgb_animation_left;
      colors[1] = rgb_animation_top;
      colors[2] = rgb_animation_right;
      animation_pattern_count = 3;
    }
    if (animation_fade_strobe == 1)
    {
      rgb_animation.strobe(colors, animation_pattern_count, rgb_animation_speed);
    }
    if (animation_fade_strobe == 2)
    {
      rgb_animation.crossFade(colors, animation_pattern_count, rgb_animation_speed);
    }

  }
}

BLYNK_WRITE(VPIN_BUTTON)
{
  int btn_state = param.asInt();

  if (btn_state == 0)
  {
    rgb_animation.off();
  }
  else
  {
    rgb_animation.on();
  }
}

BLYNK_WRITE(VPIN_ANIMATION_SPEED)
{
  int animation_speed = param.asInt();

  if (animation_speed < 0 || animation_speed > 10000)
    return;

  rgb_animation_speed = 10100 - animation_speed;

  rgb_animation.setDuration(rgb_animation_speed);
}

BLYNK_WRITE(VPIN_BRIGHTNESS)
{
  int brightness = param.asInt();

  if (brightness < 0 || brightness > 100)
    return;

  rgb_animation.brightness(brightness);
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(
      VPIN_O1,
      VPIN_O2,
      VPIN_O3,
      VPIN_O4,
      VPIN_RGB,
      VPIN_BUTTON,
      VPIN_BRIGHTNESS,
      VPIN_ANIMATION_SPEED);
}

void setup()
{
  // Debug console. Make sure to match your serial monitor config
  Serial.begin(115200);

  // I2C Bus for serial communication with XNODEs, remember to
  // set the pins to use the mikroBUS pinout
  Wire.setPins(MIKROBUS_SDA, MIKROBUS_SCL);
  Wire.begin();

  // Start the rgb animation object
  if (rgb_animation.begin(writeRgbXN03))
  {
    rgb_animation.off();
  }

  delay(100);

  BlynkEdgent.begin();
  timer.setInterval(500UL, updateAndSendData);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}