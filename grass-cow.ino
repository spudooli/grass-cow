/* 
/***************************************************************************/	
//  Attempts to track how fast grass grows
//
//  Based on code supplied by Seeed Studio for the sensor and someone else 
//  for the ethernet stuff, or the GPRS stuff, depending on which data
//  transmission method I ending up using
//
//
/*****************************************************************************/

#include "Arduino.h"

class Ultrasonic
{
	public:
		Ultrasonic(int pin);
        void DistanceMeasure(void);
		long microsecondsToCentimeters(void);
		long microsecondsToInches(void);
	private:
		int _pin;//pin number of Arduino that is connected with SIG pin of Ultrasonic Ranger.
        long duration;// the Pulse time received;
};
Ultrasonic::Ultrasonic(int pin)
{
	_pin = pin;
}
/*Begin the detection and get the pulse back signal*/
void Ultrasonic::DistanceMeasure(void)
{
    pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
	duration = pulseIn(_pin,HIGH);
}
/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::microsecondsToCentimeters(void)
{
	return duration/29/2;	
}
/*The measured distance from the range 0 to 157 Inches*/
long Ultrasonic::microsecondsToInches(void)
{
	return duration/74/2;	
}
 
Ultrasonic ultrasonic(7);
void setup()
{
	Serial.begin(9600);
}
void loop()
{
	long RangeInInches;
	long RangeInCentimeters;
	ultrasonic.DistanceMeasure();// get the current signal time;
    RangeInInches = ultrasonic.microsecondsToInches();//convert the time to inches;
	RangeInCentimeters = ultrasonic.microsecondsToCentimeters();//convert the time to centimeters
	Serial.println("The distance to obstacles in front is: ");
	Serial.print(RangeInInches);//0~157 inches
	Serial.println(" inch");
	Serial.print(RangeInCentimeters);//0~400cm
	Serial.println(" cm");
	delay(100);
}
