#include <LiquidCrystal.h>
#include <Wire.h>

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Initialization time
uint8_t seconds = 40;
uint8_t minutes = 1;
uint8_t hours = 19;
uint8_t weekday = 7;
uint8_t days = 21;
uint8_t months = 11;
uint16_t year = 15;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int adc_key_in = 0;
char szLine1[16], szLine2[16];

void setup() {
	lcd.begin(16, 2);
    	Wire.begin();
    	// To set the current time, set the time in lines 11-18 and then enable the following line. Do it once and then disable it.
	//write_initial_time();
}

void loop() {
	Wire.beginTransmission(0x68); //Send the address of DS1307
	Wire.write(0); //Sending address	
	Wire.endTransmission(); //The end of the IIC communication

	//IIC communication is started, you can continue to access another address (address auto increase) and the number of visits
	Wire.requestFrom(0x68, 7); 
	//read time
	seconds = bcd2bin(Wire.read()); 
	minutes = bcd2bin(Wire.read());
	hours = bcd2bin(Wire.read());
	weekday = Wire.read();
	days = bcd2bin(Wire.read());
	months = bcd2bin(Wire.read());
	year = bcd2bin(Wire.read()) + 2000;
	
	//lcd.clear();
	// display date
	sprintf(szLine1, "%02d/%02d/%04d", days, months, year);
	lcd.setCursor(0,0);
	lcd.print(szLine1);
	// display time
	sprintf(szLine2, "%02d:%02d:%02d", hours, minutes, seconds);
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

void write_initial_time () {
	//DS1307 write the initial time
	Wire.beginTransmission(0x68);
	Wire.write(0);
	Wire.requestFrom(0x68, 7);
	Wire.write(bin_to_bcd(seconds));
	Wire.write(bin_to_bcd(minutes));
	Wire.write(bin_to_bcd(hours));
	Wire.write(bin_to_bcd(weekday));
	Wire.write(bin_to_bcd(days));
	Wire.write(bin_to_bcd(months));
	Wire.write(bin_to_bcd(year));  
	Wire.endTransmission();
}

// BCD to Binary
int bcd2bin(int temp) {
	int a,b,c;
	a=temp;
	b=0;
	if(a>=16) {
		while(a>=16) {
			a=a-16;
			b=b+10;
			c=a+b;
			temp=c;
		}
	}
	return temp;
}

// Binary to BCD
int bin_to_bcd(int temp) {
	int a,b,c;
	a=temp;
	b=0;
	if(a>=10) {
		while(a>=10) {
			  a=a-10;
			  b=b+16;
			  c=a+b;
			  temp=c;
		}
	}
	return temp;
}
