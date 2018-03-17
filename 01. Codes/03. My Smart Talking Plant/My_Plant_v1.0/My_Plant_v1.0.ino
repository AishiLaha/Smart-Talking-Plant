#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Wi-Fi
char auth[] = "copy&paste the auth code shared with the developers";
char ssid[] = "Lenovo P1ma40";
char pass[] = "abcd12345";
int value = 0;

//Notification LED's
int R=D2;
int Y=D1;
int G=D0;
int B=D3;

//Threshold values of the sensor
int up=372;
int mid=360;
int low=350;

/*//Timer
unsigned long previousMillis = 0; // last time update
long interval = 2000; // interval at which to do something (milliseconds)
boolean water=false;*/
int count=0;

/*//pump
int pump=D7;
int pwm=D6;*/

void setup()
{
  // LED
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  Blynk.email("mratanusarkar@gmail.com", "Plant", "Hey! I'm your Plant, and I came Online !!!");
}

void loop()
{
  
  Blynk.run();

  value=analogRead(A0);
  if (value>up) 
  {
    digitalWrite(R,HIGH);
    digitalWrite(Y,LOW);
    digitalWrite(G,LOW);
    if(count <= 50)
    {
    digitalWrite(B,LOW);
    }
    
    count++;
    
    Serial.println("Soil Dry");
    Blynk.notify("I'm Dying...Water me !!");  //   We allow 1 notification per 15 seconds for now.
    Blynk.email("mratanusarkar@gmail.com", "From MyPlant", "I'm Dying...it's Drought right here !! please Water me !!");

    if(count >= 50)
    {
      digitalWrite(R,HIGH);
      digitalWrite(Y,LOW);
      digitalWrite(G,LOW);
      digitalWrite(B,HIGH);

      Serial.println("Pump STARTED");
      //Blynk.notify("Your water pump had been started by your Plant");  //   We allow 1 notification per 15 seconds for now.
      //Blynk.email("mratanusarkar@gmail.com", "From MyPlant", "Dude...Enough !! I can water myself !!");
    }
  }
  else if(value<up && value>mid)
  {
    digitalWrite(R,LOW);
    digitalWrite(Y,HIGH);
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
    
    Serial.println("Soil Moist");
    //water=true;
    count=0;
    
  }
  else
  {
    digitalWrite(R,LOW);
    digitalWrite(Y,LOW);
    digitalWrite(G,HIGH);
    digitalWrite(B,LOW);
    
    Serial.println("Soil over watered");
    //water=true;
    count=0;
  }
}

