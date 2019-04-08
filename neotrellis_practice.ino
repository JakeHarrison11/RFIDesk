/* This example shows basic usage of the NeoTrellis.
  The buttons will light up various colors when pressed.
  The interrupt pin is not used in this example.
*/
#include "Keyboard.h"
#include "Adafruit_NeoTrellis.h"
int x = 17;
bool pixelState = false;
Adafruit_NeoTrellis trellis;

#define MOMENTARY 0
#define LATCHING 1
#define MODE LATCHING //all Trellis buttons in latching mode
#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)

//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    //trellis.pixels.setPixelColor(evt.bit.NUM, 0xFFFFFF); //on rising
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
  // or is the pad released?
  //trellis.pixels.setPixelColor(m, Wheel(map(m*2, 0, trellis.pixels.numPixels(), 0, 255))); //off falling
   x = evt.bit.NUM;
  }

  // Turn on/off the neopixels!
  trellis.pixels.show();

  return 0;
}

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  //while(!Serial);
  
  if (!trellis.begin()) {
    Serial.println("Could not start trellis, check wiring?");
    while(1);
  } else {
    Serial.println("NeoPixel Trellis started");
  }

  //activate all NeoTrellis keys and set callbacks
  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }
clearPixels();
lightPixels();
pixelState = true;
}



void loop() {
  Serial.println(x);
//And now a bunch of if statements so I can know which button is pressed

  if (x==12) {                           //shutdown
    Serial.println("shutdown");
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(100);
    Keyboard.println("shutdown /s /t 00");
    x = 17;
  }

  if (x==13) {                           //reboot
    Serial.println("reboot");
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(100);
    Keyboard.println("shutdown /r /t 00");
    x = 17;
  }

  if (x==14) {                        //lock
    Serial.println("lock");
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
    x = 17;
  }
  
  if (x==0) {                         //volume down
    Serial.println("volume down");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('k');
    Keyboard.releaseAll();
    x = 17;
  }
 
  if (x==4) {                         //volume up
    Serial.println("volume up");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('j');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==2) {                         //play/pause
    Serial.println("play/pause");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('f');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==1) {                         //skip foward
    Serial.println("skip foward");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('h');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==3) {                         //skip previous
    Serial.println("skip previous");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('g');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==7) {                         //launch firefox
    Serial.println("launch firefox");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('1');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==6) {                         //launch discord
    Serial.println("launch discord");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('2');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==5) {                         //launch steam
    Serial.println("launch steam");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('3');
    Keyboard.releaseAll();
    x = 17;
  }

  if (x==15) {
    Serial.println("led toggle");
    if (pixelState==true) {
      clearPixels();
      pixelState = false;
    }
    else {
      lightPixels();
      pixelState = true;
    }
    x = 17;
  }
trellis.read();
delay(100); //the NeoTrellis has a resolution of around 60hz
}


void clearPixels() {
 for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(2);
  }  
  }

int lightPixels() {
    trellis.pixels.setPixelColor(12, 255,0,0);//shutdown
  trellis.pixels.setPixelColor(13, 0,255,0);//reboot
  trellis.pixels.setPixelColor(14, 0,0,255);//lock
  trellis.pixels.setPixelColor(15, 255,255,255);//light toggle
  trellis.pixels.setPixelColor(0, 107,5,186);//volume up
  trellis.pixels.setPixelColor(4, 107,5,186);//volume down
  trellis.pixels.setPixelColor(2, 255,233,0);//play
  trellis.pixels.setPixelColor(3, 255,131,0);//skip previous
  trellis.pixels.setPixelColor(1, 255,131,0);//skip foward
  trellis.pixels.setPixelColor(7, 255,50,40);//firefox
  trellis.pixels.setPixelColor(6, 130,148,209);//discord
  trellis.pixels.setPixelColor(5, 20,48,93);//steam
  trellis.pixels.show();
}
