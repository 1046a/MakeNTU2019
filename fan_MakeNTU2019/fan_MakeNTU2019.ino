#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Stepper.h>

#include "index.h"

#define EN 1       // LOW works
//#define X_DIR     5
//#define Y_DIR     6
//#define X_STP     2
//#define Y_STP     3
#define STEP 12
#define DIR 14

ESP8266WebServer server(80);
extern "C"// this is the setup of timer only usable for esp8266
{
#include "user_interface.h"
}

os_timer_t myTimer;//initialize the timer variable of esp8266 timer
//int durationToCallISR = 2;

void user_init(void) // the function will be set in setup to trigger the ISR function
{
  os_timer_setfn(&myTimer, ISR, NULL);
  os_timer_arm(&myTimer, 1000, true);//every 5 millisecs to call the timer interrupt - interruptServiceRoutine function
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  //wificonnection();
  //serverSetup();//setup the server 
  
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  digitalWrite(STEP, LOW);
  digitalWrite(DIR, false);

  //user_init();
}
void moving(){
  digitalWrite(DIR, true);
  for (int i = 0; i < 200; i++) // 200 steps making a round
  {
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);// notice that it's microseconds
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  moving();
}
