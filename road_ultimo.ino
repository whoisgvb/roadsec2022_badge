#include <SPI.h>
#include <TFT_eSPI.h>
#include <Button2.h>

#define BUTTON_1  38
#define BUTTON_2  37
#define BUTTON_3  39


TFT_eSPI tft = TFT_eSPI(240, 320);
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
Button2 btn3(BUTTON_3);

// Backlight brightness (0-255)
int tftBacklight = 63;

// Start image index
int im = 0;

// Total images
int tot = 7;

#include <TJpg_Decoder.h>
#include "jpeg1.h"
#include "jpeg2.h"
#include "jpeg3.h"
#include "jpeg4.h"
#include "jpeg5.h"
#include "jpeg6.h"

void button_init() {
    btn1.setClickHandler([](Button2 & b) {
        im--;
        if (im < 0) im = 0;
        draw_image(im);
        Serial.println("Button 1 OK");
        Serial.printf("Image %d\n", im);
    });

    btn2.setClickHandler([](Button2 & b) {
        im = 0;
        draw_image(im);
        Serial.println("Button 2 OK");
        Serial.printf("Image %d\n", im);
    });

    btn3.setClickHandler([](Button2 & b) {
        im++;
        if (im > tot-1) im = tot-1;
        draw_image(im);
        Serial.println("Button 3 OK");
        Serial.printf("Image %d\n", im);
    });
}

void button_loop() {
    btn1.loop();
    btn2.loop();
    btn3.loop();
}
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n Cheguei aqui =)");

  tft.begin();
  tft.fillScreen(OLIVE);
 
  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);

  draw_image(im);
  button_init();

  // Set backlight intensity using PWM output
  ledcSetup(1, 1000, 8);      // PWM channel 1, 1000Hz, 8 bit
  ledcAttachPin(TFT_BL, 1);   // attach to TFT backlight
  ledcWrite(1, tftBacklight); // set backlight
}

// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}

void draw_image(int i) {
  switch (i) {
    case 0:
     tft.setRotation(0);  // portrait
     TJpgDec.drawJpg(0, 0, gato4, sizeof(gato4));
      break;
    case 1:
      tft.setRotation(0);  // portrait
      TJpgDec.drawJpg(0, 0, gato1, sizeof(gato1));
      break;
    case 2:
      tft.setRotation(0);  // portrait
      TJpgDec.drawJpg(0, 0, gato0, sizeof(gato0));
      break;
    case 3:
      tft.setRotation(0);  // portrait
      TJpgDec.drawJpg(0, 0, gato3, sizeof(gato3));
      break;
    case 4:
      tft.setRotation(0);  // portrait
      TJpgDec.drawJpg(0, 0, gato2, sizeof(gato2));
      break;
    case 5:
      tft.setRotation(0); // portrait
      TJpgDec.drawJpg(0, 0, gato5, sizeof(gato5));
      break;
    case 6:
      for (int i = 0; i >= 0; i++){
        tft.fillScreen(random(0x10000));
        delay(300);
      }
      
      break;
    default:
      tft.fillScreen(TFT_BLACK);
      break;
  }
}
void loop() {
    button_loop();
}
