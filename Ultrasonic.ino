#include <LiquidCrystal.h>

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define TRIGGER_PIN		1
#define ECHO_PIN		0

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int adc_key_in = 0;
char szLine1[16], szLine2[16];
int duration, distance;

void setup() {
	lcd.begin(16, 2);
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
}

void loop() {
	// calculate distance
	digitalWrite(TRIGGER_PIN, HIGH);
	delay(5);
	digitalWrite(TRIGGER_PIN, LOW);
	duration = pulseIn(ECHO_PIN, HIGH);
	delay(10);
	distance = duration / 58;
	
	lcd.clear();
	// display duration
	sprintf(szLine1, "Duration: %d", duration);
	lcd.setCursor(0,0);
	lcd.print(szLine1);
	// display distance
	sprintf(szLine2, "Distance: %d", distance);
	lcd.setCursor(0,1);
	lcd.print(szLine2);
	
	switch (read_LCD_buttons()) {
		case btnUP:
		break;

		case btnDOWN:
		break;

		case btnLEFT:
		break;

		case btnRIGHT:
		break;

		case btnSELECT:
		break;

		default:
		break;
	}	
}

int read_LCD_buttons()
{
	adc_key_in = analogRead(0);
	if (adc_key_in > 1000) return btnNONE;
	if (adc_key_in < 50)   return btnRIGHT;  
	if (adc_key_in < 195)  return btnUP; 
	if (adc_key_in < 380)  return btnDOWN; 
	if (adc_key_in < 555)  return btnLEFT; 
	if (adc_key_in < 790)  return btnSELECT;   
	return btnNONE;
}
