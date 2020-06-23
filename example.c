// UTFT_Demo_320x240 (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>

#include <ITDB02_Touch.h>
// #include <URTouch.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

UTFT myGLCD(ILI9325C,A5,A4,A3,11);//myGLCD(GEEE24,19,18,17,16);   // Remember to change the model parameter to suit your display module!

ITDB02_Touch  myTouch( A1, 10, A0, 9, 8);
// URTouch  myTouch( A1, 10, A0, 9, 8);


void setup()
{
//   randomSeed(analogRead(0));
    // Serial.begin(9600);
// Setup the LCD
    myGLCD.InitLCD();
    myGLCD.setFont(SmallFont);

    myTouch.InitTouch(LANDSCAPE);
    myTouch.setPrecision(PREC_MEDIUM);
}

void loop()
{
  int buf[318];

// Clear the screen and draw the frame
  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 319, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 226, 319, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("* SUPAH TESTER *", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255,255,0);
  myGLCD.print("<MICHAEL & LUCAS PRODUCTIONS>", CENTER, 227);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, 319, 225);

  myGLCD.setColor(255, 255, 255);


  long x, y;
  while(true)
  {
    if(myTouch.dataAvailable())
    {  
        while (myTouch.dataAvailable() == true)
        {
            myTouch.read();
            x = myTouch.getX();
            y = myTouch.getY();
            if ((x!=-1) and (y!=-1))
            {
            myGLCD.drawPixel(x, y);
            }
        }
    }
  }

  

   

// myGLCD.drawPixel(2+random(316), 16+random(209));

  delay (10000);
}
