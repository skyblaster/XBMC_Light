//------------------------------------------------------------------------------
//  XBMC/BOBLIGHT WS2811 
//------------------------------------------------------------------------------
//  by Marco Gözelt (marco.goezelt@live.de)
//  Built for "XBMC Light" using the Arduino/Teensy FastSPI v2 library.
//------------------------------------------------------------------------------
//  * Startup test (Brighten,R, G, B) to test LED strip without PC.
//------------------------------------------------------------------------------

#include "FastSPI_LED2.h"

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

//Number of LEDs
#define NUM_LEDS 198

//BaudRate:  (3key + (3rgb * NUM)) * MaxFPS * 10bits = MinBAUD
#define BAUD 500000

//Key bytes to syncronize begining of Frame.             [DEFAULT = FF 55 00]
#define KEY1 0xFF
#define KEY2 0x55
#define KEY3 0x00

//LED communication-pin (SPI MOSI).                      [DEFAULT = 12]  (D12)
WS2811Controller800Mhz<12> LED;

//Change order of RGB below for some LED pixel brands.   [DEFAULT = r; g; b;]
struct CRGB { byte g; byte r; byte b; };
struct CRGB leds[NUM_LEDS];


//------------------------------------------------------------------------------
// Setup
//------------------------------------------------------------------------------

void setup() {

	//------------------------------------------------------------------------------
	//FastSPI Setup
	//------------------------------------------------------------------------------
  
    // initialize the controller
    Serial.begin(BAUD);
	LED.init();
	
	// zero out all the leds
	//memset(leds, 0, sizeof(struct CRGB) * NUM_LEDS); 
	memset(leds, 0, NUM_LEDS * 3);
	
	// set all the LEDs to white
	for(int i = 0; i < NUM_LEDS; i++) {leds[i].r = 255; leds[i].g = 255; leds[i].b = 255;}
	LED.showRGB((byte*)leds, NUM_LEDS);
	delay(1000);
	
	// set all the LEDs to red
	for(int i = 0; i < NUM_LEDS; i++) {leds[i].r = 255; leds[i].g = 0; leds[i].b = 0;}
	LED.showRGB((byte*)leds, NUM_LEDS);
	delay(1000);
	
	// set all the LEDs to green
	for(int i = 0; i < NUM_LEDS; i++) {leds[i].r = 0; leds[i].g = 255; leds[i].b = 0;}
	LED.showRGB((byte*)leds, NUM_LEDS);
	delay(1000);
	
	// set all the LEDs to blue
	for(int i = 0; i < NUM_LEDS; i++) {leds[i].r = 0; leds[i].g = 0; leds[i].b = 255;}
	LED.showRGB((byte*)leds, NUM_LEDS);
	delay(1000);
	
	// zero out all the leds
	memset(leds, 0, sizeof(struct CRGB) * NUM_LEDS);
	LED.showRGB((byte*)leds, NUM_LEDS);
	delay(1000);
}

//------------------------------------------------------------------------------
//  Main Loop
//------------------------------------------------------------------------------

void loop() {

	if (Serial.available())                       				//Check for 3 KEY Bytes
	{
		if (Serial.read()==KEY1)
		{
		while (!Serial.available()) {}
			if (Serial.read()==KEY2)
			{
			while (!Serial.available()) {}
				if (Serial.read()==KEY3)
				{
					for (int iLed=0; iLed<NUM_LEDS; iLed++)     //Read 3*NUM_LEDS Bytes
					{
						while (!Serial.available()) {}
						leds[iLed].r = Serial.read();
						while (!Serial.available()) {}
						leds[iLed].g = Serial.read();
						while (!Serial.available()) {}
						leds[iLed].b = Serial.read();
					}
					LED.showRGB((byte*)leds, NUM_LEDS);;
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
//  End
//------------------------------------------------------------------------------
