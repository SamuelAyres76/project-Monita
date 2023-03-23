/*
  Project Beddy-Bye

  By Samuel, Tristan and Kieran
  
*/

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
    lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);

    delay(1000);
}

void loop() {

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
