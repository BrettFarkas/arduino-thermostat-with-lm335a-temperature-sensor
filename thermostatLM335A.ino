#include <LM335A.h>

int value=100;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;

unsigned long now;
unsigned long then=0;

int seconds=0;
int minutes=0;
int hours=0;

LM335A InsideTemp(1); //pass the analog input pin number
void setup() {
Serial.begin(57600);
Serial.println("starting");
pinMode(13,OUTPUT);
pinMode(2,OUTPUT);
}

void loop() {
// delay(3000);
  //user must call ReadTemp before any valid temp data is available
  InsideTemp.ReadTemp(); 
// Serial.print("Fahrenheit: ");
 
   now=millis();
  if(now-then > 999){
seconds++;
then=now;
Serial.print("Seconds: ");
Serial.println(seconds);
  Serial.print("Minutes: ");
Serial.println(minutes);
Serial.print("Hours: ");
Serial.println(hours);
Serial.println();
}

if(seconds>59){
minutes++;
seconds=0;
}

if (minutes>=60){
hours++;
minutes=minutes-60;

}

if (hours==24){
hours=0;
}
 
  //functions to get the temperature in various unitsfs
/*
  Serial.println(InsideTemp.Fahrenheit());
  Serial.print("Celsius: ");
  Serial.println(InsideTemp.Celsius());
  Serial.print("Kelvin: ");
  Serial.println(InsideTemp.Kelvin());
*/
if(hours >= 0 && hours < 7 ){
  digitalWrite(2,HIGH);
 
value1=InsideTemp.Fahrenheit();
delay(200);
InsideTemp.ReadTemp(); 
value2=InsideTemp.Fahrenheit();
delay(200);
InsideTemp.ReadTemp(); 
value3=InsideTemp.Fahrenheit();
delay(200);
InsideTemp.ReadTemp(); 
value4=InsideTemp.Fahrenheit();

value= (value1+value2+value3+value4)/4;

Serial.println(value+14); //the 14 makes it accurate, calibrated

//if(value+14 > 74) summer setting
if(value+14 < 70){       //--------BELOW 69 DEGREES
digitalWrite(13,HIGH);

  delay(360000);             //6 minutes, 5 is 300,000
  minutes+=6;

}else{
digitalWrite(13,LOW);
}
}else{
digitalWrite(2,LOW);
digitalWrite(13,LOW);
}

}
