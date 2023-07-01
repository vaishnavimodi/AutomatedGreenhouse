#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float setTemp = 20.0;
  float e = 0.0;
  float k = 1;
  float Tp = 1000.0;
  unsigned long userTime = 57600000; //16hrs in milliseconds
  unsigned long currTime;
  unsigned long second;
  unsigned long minutes;
  unsigned long hour;
  unsigned long runTime = 0;
  unsigned long runTime2 = 0;
  int check = 1;
  unsigned long testTime;
  unsigned long lastTime = 0;
  float t = 0.0;
  
//Test code
int v0;
float r2 = 100000;
float logrt, rt;
float c1 = 1.009249522e-03;
float c2 = 2.378405444e-04;
float c3 = 2.019202697e-07;

  
void setup() {
  pinMode(2, OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(2, LOW);
  dht.begin();

}

void loop() {
  
  currTime = millis();
  second = currTime/1000;
  minutes = second/60;
  hour = minutes/60;

// for lights : start
  int lightValue = analogRead(4); //for lights
  //Serial.println("light value");
  //Serial.println(lightValue);
  userTime = 0.023 * lightValue; //correct way to get user time
  //Serial.println("usertime");
  //Serial.println(userTime);

  //Serial.println("currtime");
  //Serial.println(second);
 
  testTime = hour;
  unsigned long dT = testTime - lastTime;
  runTime = dT + runTime;
  //Serial.println("run time");
  //Serial.println(runTime);
  runTime2 = dT + runTime2;
  if ((userTime-runTime) > 0 && (check == 1)){
    //Serial.println("Light on"); // send val to switch on light
    digitalWrite(5, HIGH);
  } else if ((runTime - userTime) <= 0 && (check == 1)){
    //Serial.println(runTime);
    check = 0;
    runTime2 = 0;
  } else if (((24 - userTime) - runTime2) > 0 && (check == 0)){
    //Serial.println("Light off"); // send val to switch off light
    digitalWrite(5, LOW);
  } else if (((24 - userTime) - runTime2) <= 0 && (check == 0)){
    //Serial.println("run time2");
    //Serial.println(runTime2);
    check = 1;
    runTime = 0;
  }
  lastTime = testTime;
  

  // for fan : start
 
//test code
v0 = analogRead(1);
Serial.println("Analog Read");
Serial.println(v0);
rt = r2*(1023/(float)v0 - 1.0);
logrt = log(rt);
t = (1.0/(c1+(c2*logrt+(c3*(logrt*(logrt*(logrt)))))));
t = t - 273.15;
Serial.println(t);
 
  float sensorValue = analogRead(3); //for temperature
  Serial.println("\nsensor value");
  //Serial.println(sensorValue);
 
  setTemp = 15 + (0.014*sensorValue);  //to convert to 15-30 degrees
  Serial.println("Set Temp");
  Serial.println(setTemp);
  if (t > setTemp){
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  delay(500);
  
// for fan : end
  
}
