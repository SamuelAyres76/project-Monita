
/*
  Project Monita
  By Samuel, Tristan and Kieran
  
*/
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL4zI1uFdGF"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "NusKK-GYywUghkOVaIE922AX6EwSNx8o"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <Bridge.h>
#include <BlynkSimpleYun.h>


BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  digitalWrite(13,value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
  int sensorValue = analogRead(A1);
  Blynk.virtualWrite(V4, sensorValue);
  sensorValue = analogRead(A2);
  Blynk.virtualWrite(V5,sensorValue);

}

#include <Wire.h>
#include "rgb_lcd.h"

/* Variables */
int heat_State = 0;
int sound_State = 0;
int button0State = 0;
int button1State = 0;

rgb_lcd lcd;

/* The colour of the screen */
const int colorR = 10;
const int colorG = 10;
const int colorB = 255;

/* The buttons */
const int button0Pin = 5; /*D5*/
const int button1Pin = 7; /*D7*/

/* set up the LCD's number of columns and rows: */
void setup() {
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  
    lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);

    delay(1000);
}

void loop() {
   Blynk.run();
  timer.run();

/* INTRO no work :(
lcd.setCursor(0, 0);
lcd.print("Beddy ");
lcd.setCursor(0, 1);
lcd.print("Bye");
delay(1000);
*/

  /* Heat toggle */
    button0State = digitalRead(button0Pin);

/* If the Heat button is pressed... */
    if (button0State == HIGH) 
    {
/* If the status is 0 (off) */
      if (heat_State == 0)
      {
/* Turn it on! */
        heat_State = 1;
      }
/* But if the status is 1 (on) */
      else if (heat_State == 1)
      {
/* Turn it off! */
        heat_State = 0;
      }
    } 

    /* set the cursor to column 0, line 0 */
    lcd.setCursor(0, 0);
    
    /* prints the Current heat */
    if (heat_State == 1)
    {
      int sensorValue = analogRead(A1);
      lcd.print("Temp: ");
      lcd.print(sensorValue);
      Blynk.virtualWrite(V2, millis() / 1000);
      sensorValue = analogRead(A1);
      Blynk.virtualWrite(V4, sensorValue);
    }
    
 
    else
    {
      lcd.print("offline      ");
    }
    


    delay(200);

/*##########################################################################################################*/
/*Sound toggle*/
/*##########################################################################################################*/

    button1State = digitalRead(button1Pin);

    // If the Sound button is pressed...
    if (button1State == HIGH) 
    {
      // If the status is 0 (off)
      if (sound_State == 0)
      {
        // Turn it on!
        sound_State = 1;
      }
      // But if the status is 1 (on)
      else if (sound_State == 1)
      {
        // Turn it off!
        sound_State = 0;
      }
    } 

    // set the cursor to column 0, line 0
    lcd.setCursor(0, 1);
    
    // prints the Current sound
    if (sound_State == 1)
    {
      int sensorValue = analogRead(A2);
      lcd.print("Sound: ");
      lcd.print(sensorValue);
      Blynk.virtualWrite(V2, millis() / 1000);
      sensorValue = analogRead(A2);
      Blynk.virtualWrite(V5, sensorValue);
    }

    else
    {
      lcd.print("offline      ");
    }
    


    delay(200);
}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
