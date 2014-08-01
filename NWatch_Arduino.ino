#include <TFT_ILI9163C.h>
#include <SPI.h>
#include <fonts.h>
#include <Adafruit_GFX.h>

#define _CS 2
#define _RST 3
#define _DC 4

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

// Message codes
#define MSG_STP			'0'
#define MSG_INC_CALL	'1'
#define MSG_MIS_CALL	'2'
#define MSG_INC_SMS		'3'
#define MSG_INC_EMAIL	'4'

TFT_ILI9163C tft = TFT_ILI9163C(_CS, _DC, _RST);

uint16_t isHome = 0;
uint8_t message;
uint8_t LED = 13;

void setup() {
	tft.begin();
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		tft.setBitrate(24000000);
	#endif
	tft.setRotation(2);
	tft.fillScreen(BLACK);
	
	//bluetooh setup
	Serial.begin(9600);
	pinMode(LED, OUTPUT);

}

void loop() {
	if (isHome == 0)
		home();
	if (Serial.available() > 0) {
		message = Serial.read();
		if (message == MSG_INC_CALL) {			
			incomingCall();
		}
		if (message == MSG_MIS_CALL) {

		}
		if (message == MSG_INC_SMS) {

		}
		if (message == MSG_INC_EMAIL) {

		}
		if (message == MSG_STP) {
			if (isHome == 0)
				home();
		}
	}
}

void home() {
	tft.fillScreen();
	tft.setCursor(10, 45);
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.println("Nothing\n   happens");
	isHome = 1;
}

void incomingCall() {
	digitalWrite(LED, HIGH);
	isHome = 0;
	tft.fillScreen();
	tft.setCursor(10, 45);
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.println("Phone is\n ringing!");
}
