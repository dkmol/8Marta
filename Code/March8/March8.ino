//https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
//http://forum.amperka.ru/threads/Переключение-между-режимами-на-ws2812b.7574/
#include <Adafruit_NeoPixel.h>

#define   LEDS_PIN             6
#define   ANALOG_PIN_RANDOM    A1

#define   LEDS_MODULES      2
#define   PIXEL_IN_MODULE   8
#define   PIXEL_NUM         (LEDS_MODULES * PIXEL_IN_MODULE)

#define   BACKGROUND_COLOUR ((uint32_t) 0x00020000)

#define   PALE2_COLOUR ((uint32_t) 0x00030106)
#define   PALE1_COLOUR ((uint32_t) 0x00180830)

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel LEDS = Adafruit_NeoPixel(PIXEL_NUM, LEDS_PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  LEDS.begin();
  for (byte i = 0; i < PIXEL_NUM; i++)
    LEDS.setPixelColor(i, BACKGROUND_COLOUR);
  LEDS.show();
}
//-----------------------------------
void loop()
{

  for (byte i = 0; i < 3; i++)
    spotLight();

  for (byte i = 0; i < 3; i++)
    cometLight();

  for (byte i = 0; i < 3; i++)
    flash();

  for (byte i = 0; i < 3; i++)
    snake();

  for (byte i = 0; i < 10; i++)
    LEDS_4();

}
//-----------------------------------
void spotLight()
{
  const unsigned int ShowDelay = 50;

  for (byte i = 0; i < PIXEL_NUM; i++)
    LEDS.setPixelColor(i, BACKGROUND_COLOUR);
  LEDS.show();

  for (byte i = 0; i < PIXEL_NUM; i++)
  {
    LEDS.setPixelColor(i, 150, 58, 255); //цвет R, G, B
    LEDS.show();
    delay(ShowDelay);
    LEDS.setPixelColor(i, BACKGROUND_COLOUR);
  }
}
//-----------------------------------
void cometLight()
{
  const unsigned int ShowDelay = 75;

  for (byte i = 0; i < (PIXEL_NUM / 2); i++)
  {
    LEDS.setPixelColor(i, 150, 58, 255); //цвет R, G, B
    if (i >= 1)
      LEDS.setPixelColor(i - 1, PALE1_COLOUR); //цвет R, G, B
    else
    {
      LEDS.setPixelColor(PIXEL_IN_MODULE, PALE1_COLOUR); //цвет R, G, B
      LEDS.setPixelColor(PIXEL_IN_MODULE + 1, PALE2_COLOUR);
    }
    if (i >= 2)
      LEDS.setPixelColor(i - 2, PALE2_COLOUR); //цвет R, G, B
    else
      LEDS.setPixelColor(PIXEL_IN_MODULE, PALE2_COLOUR);

    LEDS.show();
    delay(ShowDelay);
    LEDS.setPixelColor(i, BACKGROUND_COLOUR);
    if (i >= 1)
      LEDS.setPixelColor(i - 1, BACKGROUND_COLOUR); //цвет R, G, B
    else
    {
      LEDS.setPixelColor(PIXEL_IN_MODULE, BACKGROUND_COLOUR); //цвет R, G, B
      LEDS.setPixelColor(PIXEL_IN_MODULE + 1, BACKGROUND_COLOUR);
    }
    if (i >= 2)
      LEDS.setPixelColor(i - 2, BACKGROUND_COLOUR); //цвет R, G, B
    else
      LEDS.setPixelColor(PIXEL_IN_MODULE, BACKGROUND_COLOUR);
  }

  for (byte i = (PIXEL_NUM - 1); i >= (PIXEL_NUM / 2); i--)
  {
    LEDS.setPixelColor(i, 150, 58, 255); //цвет R, G, B
    if (i <= (PIXEL_NUM - 2))
      LEDS.setPixelColor(i + 1, PALE1_COLOUR); //цвет R, G, B
    else
    {
      LEDS.setPixelColor(7, PALE1_COLOUR); //цвет R, G, B
      LEDS.setPixelColor(6, PALE2_COLOUR);
    }
    if (i <= (PIXEL_NUM - 3))
      LEDS.setPixelColor(i + 2, PALE2_COLOUR); //цвет R, G, B
    else
      LEDS.setPixelColor(7, PALE2_COLOUR);

    LEDS.show();
    delay(ShowDelay);
    LEDS.setPixelColor(i, BACKGROUND_COLOUR);
    if (i <= (PIXEL_NUM - 2))
      LEDS.setPixelColor(i + 1, BACKGROUND_COLOUR); //цвет R, G, B
    else
    {
      LEDS.setPixelColor(7, BACKGROUND_COLOUR); //цвет R, G, B
      LEDS.setPixelColor(6, BACKGROUND_COLOUR);
    }
    if (i <= (PIXEL_NUM - 3))
      LEDS.setPixelColor(i + 2, BACKGROUND_COLOUR); //цвет R, G, B
    else
      LEDS.setPixelColor(7, BACKGROUND_COLOUR);
  }
}
//----------------------------------------
void flash()
{
  const unsigned int ShowDelay = 50;//100;
  const unsigned int PauseDelay = 50;//100;
  byte RandomPixel;
  int32_t RandomColour;

  randomSeed(analogRead(ANALOG_PIN_RANDOM));

  for (byte i = 0; i < PIXEL_NUM; i++)
    LEDS.setPixelColor(i, 0, 0, 0);
  LEDS.show();

  for (byte j = 0; j < 21; j++)//количество произвольных вспышек 21
  {
    RandomColour = random(0xFFFFFF);
    RandomPixel = random(PIXEL_NUM);

    LEDS.setPixelColor(RandomPixel, RandomColour);
    LEDS.show();
    delay(ShowDelay);
    LEDS.setPixelColor(RandomPixel, 0, 0, 0);
    LEDS.show();
    delay(PauseDelay);
  }

  //delay(1000);
}

void snake()
{
  const unsigned int ShowDelay = 50;//100;
  int32_t RandomColour;

  RandomColour = random(0xFFFFFF);

  for (byte i = 0; i < PIXEL_NUM / 2; i++)
  {
    LEDS.setPixelColor(i, RandomColour);
    LEDS.show();
    delay(ShowDelay);
  }

  for (byte i = (PIXEL_NUM - 1); i >= (PIXEL_NUM / 2); i--)
  {
    LEDS.setPixelColor(i, RandomColour);
    LEDS.show();
    delay(ShowDelay);
  }

  for (byte i = 0; i < PIXEL_NUM / 2; i++)
  {
    LEDS.setPixelColor(i, 0);
    LEDS.show();
    delay(ShowDelay);
  }

  for (byte i = (PIXEL_NUM - 1); i >= (PIXEL_NUM / 2); i--)
  {
    LEDS.setPixelColor(i, 0);
    LEDS.show();
    delay(ShowDelay);
  }

}
//---------------------------------------
void LEDS_4()
{
  for (uint16_t j = 0; j < 256 * 1; j++) //стоит 1 цикл радуги
  {
    for (uint16_t i = 0; i < PIXEL_NUM; i++)
    {
      LEDS.setPixelColor(i, Wheel(((i * 256 / PIXEL_NUM) + j) & 255));
    }

    LEDS.show();
    delay(3);
  }
  /*
      for(byte i=0; i< PIXEL_NUM; i++)
      {
        LEDS.setPixelColor(i, 0);
      }
      LEDS.show();
  */
}

//----------------------------------------
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return LEDS.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return LEDS.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return LEDS.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}





