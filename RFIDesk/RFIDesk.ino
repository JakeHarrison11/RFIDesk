#include <SPI.h>
#include <MFRC522.h>
#include "Keyboard.h"
#include "Adafruit_NeoTrellis.h"
int m = 0;
int x = 17;
bool pixelState = false;
int redButtons[] = {15, 14, 11, 10, 7, 6, 3, 2};
int greenButtons[] = {13, 12, 9, 8, 5, 4, 1, 0};
int selector = 0;
Adafruit_NeoTrellis trellis;

#define MOMENTARY 0
#define LATCHING 1
#define MODE LATCHING //all Trellis buttons in latching mode
#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define SS_PIN 10
#define RST_PIN 9
#define PASSWORD "YOURPASSWORDHERE"
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//define a callback for key presses
TrellisCallback blink(keyEvent evt) {
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
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //while(!Serial);

  if (!trellis.begin()) {
    Serial.println("Could not start trellis, check wiring?");
    while (1);
  } else {
    Serial.println("NeoPixel Trellis started");
  }

  //activate all NeoTrellis keys and set callbacks
  for (int i = 0; i < NEO_TRELLIS_NUM_KEYS; i++) {
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }

  rainbowScroll();
  clearPixels();
  lightPixels();
}



void loop() {

  if (x != 17) {
    Serial.println(x);
  }

  //And now a bunch of if statements so I can know which button is pressed
  if (m == 0) {
    if (x == 0) {                         //shutdown
      Serial.println("shutdown");
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      delay(100);
      Keyboard.println("shutdown /s /t 00");
      x = 17;
    }

    if (x == 4) {                         //reboot
      Serial.println("reboot");
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      delay(100);
      Keyboard.println("shutdown /r /t 00");
      x = 17;
    }

    if (x == 8) {                      //lock
      Serial.println("lock");
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('l');
      delay(100);
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 2) {                       //volume down
      Serial.println("volume down");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('k');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 1) {                       //volume up
      Serial.println("volume up");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('j');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 10) {                       //play/pause
      Serial.println("play/pause");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('f');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 6) {                       //skip foward
      Serial.println("skip foward");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('h');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 14) {                       //skip previous
      Serial.println("skip previous");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('g');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 13) {                       //launch firefox
      Serial.println("launch firefox");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('1');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 9) {                       //launch discord
      Serial.println("launch discord");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('2');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 5) {                       //launch spotify
      Serial.println("launch spotify");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('3');
      Keyboard.releaseAll();
      x = 17;
    }

    if (x == 3) {                       //rainbow
      m = 2;
      x = 17;
    }

    if (x == 12) {
      Serial.println("led toggle");
      if (pixelState == true) {
        clearPixels();
        x = 17;
        Serial.println(pixelState);
      }
      else {
        lightPixels();
        x = 17;
        Serial.println(pixelState);
      }
    }

    if (x == 15) {
      selector = 0;
      trellis.pixels.setPixelColor(15, 255, 255, 255);
      trellis.pixels.setPixelColor(11, 0, 0, 0);
      trellis.pixels.setPixelColor(7, 0, 0, 0);
      trellis.pixels.show();
      x = 17;
    }

    if (x == 11) {
      selector = 1;
      trellis.pixels.setPixelColor(15, 0, 0, 0);
      trellis.pixels.setPixelColor(11, 255, 255, 255);
      trellis.pixels.setPixelColor(7, 0, 0, 0);
      trellis.pixels.show();
      x = 17;
    }

    if (x == 7) {
      selector = 2;
      trellis.pixels.setPixelColor(15, 0, 0, 0);
      trellis.pixels.setPixelColor(11, 0, 0, 0);
      trellis.pixels.setPixelColor(7, 255, 255, 255);
      trellis.pixels.show();
      x = 17;
    }
  }

  if (m == 1) {
    selectionPixels();
    int y = 0;
    for (y = 0; y < 8; y = y + 1) {
      if (greenButtons[y] == x) {
        Serial.println("Password approved");
        typePassword();
        clearPixels();
        lightPixels();
        y = 8; // force end of array check
        x = 17;
        m = 0;
      }
    }

    for (y = 0; y < 8; y = y + 1) {
      if (redButtons[y] == x) {
        clearPixels();
        lightPixels();
        Serial.println("Password not approved");
        y = 8; // force end of array check
        x = 17;
        m = 0;
      }
    }
  }

  if (m == 2) {
    rainbowScroll();
    if (x < 17) {
      m = 0;
      x = 17;
      clearPixels();
      lightPixels();
    }
  }

  trellis.read();

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "63 E6 74 03")
  {
    Serial.println("Authorized access");
    Serial.println();
    m = 1;
    delay(200);
  }

  else   {
    Serial.println(" Access denied");
    redPixels();
    delay(2000);
    clearPixels();
    lightPixels();
  }

  delay(200); //the NeoTrellis has a resolution of around 60hz
}

//going into the void

void clearPixels() {
  for (uint16_t i = 0; i < trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(2);
  }
  pixelState = false;
}

int lightPixels() {
  trellis.pixels.setPixelColor(0, 255, 0, 0); //shutdown
  trellis.pixels.setPixelColor(4, 0, 255, 0); //reboot
  trellis.pixels.setPixelColor(8, 0, 0, 255); //lock
  trellis.pixels.setPixelColor(12, 255, 255, 255); //light toggle
  trellis.pixels.setPixelColor(1, 107, 5, 186); //volume up
  trellis.pixels.setPixelColor(2, 107, 5, 186); //volume down
  trellis.pixels.setPixelColor(10, 255, 233, 0); //play
  trellis.pixels.setPixelColor(14, 255, 131, 0); //skip previous
  trellis.pixels.setPixelColor(6, 255, 131, 0); //skip foward
  trellis.pixels.setPixelColor(13, 255, 50, 40); //firefox
  trellis.pixels.setPixelColor(9, 130, 148, 209); //discord
  trellis.pixels.setPixelColor(5, 30, 215, 96); //steam
  trellis.pixels.setPixelColor(3, 0, 242, 255); //rainbow
  if (selector == 0) {
    trellis.pixels.setPixelColor(15, 255, 255, 255);
  }
  if (selector == 1) {
    trellis.pixels.setPixelColor(11, 255, 255, 255);
  }
  if (selector == 2) {
    trellis.pixels.setPixelColor(7, 255, 255, 255);
  }
  trellis.pixels.show();
  pixelState = true;
}

int selectionPixels() {
  trellis.pixels.setPixelColor(15, 255, 0, 0);
  trellis.pixels.setPixelColor(14, 255, 0, 0);
  trellis.pixels.setPixelColor(11, 255, 0, 0);
  trellis.pixels.setPixelColor(10, 255, 0, 0);
  trellis.pixels.setPixelColor(7, 255, 0, 0);
  trellis.pixels.setPixelColor(6, 255, 0, 0);
  trellis.pixels.setPixelColor(3, 255, 0, 0);
  trellis.pixels.setPixelColor(2, 255, 0, 0);
  trellis.pixels.setPixelColor(13, 0, 255, 0);
  trellis.pixels.setPixelColor(12, 0, 255, 0);
  trellis.pixels.setPixelColor(9, 0, 255, 0);
  trellis.pixels.setPixelColor(8, 0, 255, 0);
  trellis.pixels.setPixelColor(5, 0, 255, 0);
  trellis.pixels.setPixelColor(4, 0, 255, 0);
  trellis.pixels.setPixelColor(1, 0, 255, 0);
  trellis.pixels.setPixelColor(0, 0, 255, 0);
  trellis.pixels.show();
}

int redPixels() {
  for (uint16_t i = 0; i < trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 255, 0, 0);
    trellis.pixels.show();
    delay(2);
  }
}

int typePassword() {
  if (selector == 0) {
    Keyboard.press(KEY_UP_ARROW);
    delay(100);
    Keyboard.release(KEY_UP_ARROW);
    delay(100);
    Keyboard.println(PASSWORD);
    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.releaseAll();
    rainbowScroll();
    lightPixels();
  }
  if (selector == 1) {
    Keyboard.println("Selector 1 works!");
  }
  if (selector == 2) {
    Keyboard.println("Selector 2 works!");
  }
  if (selector == 3) {
    Keyboard.println("Selector 3 works!");
  }
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return trellis.pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return trellis.pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return trellis.pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}

int rainbowScroll() {
  //do a little animation to show we're on
  for (uint16_t i = 0; i < trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, Wheel(map(i, 0, trellis.pixels.numPixels(), 0, 255)));
    trellis.pixels.show();
    delay(50);
  }
  for (uint16_t i = 0; i < trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(50);
  }
}
