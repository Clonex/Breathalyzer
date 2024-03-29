#include <UTFT.h>
#include <ITDB02_Touch.h>

extern uint8_t SmallFont[];
UTFT myGLCD(ILI9325C, A5, A4, A3, 11);
ITDB02_Touch  myTouch(A1, 10, A0, 9, 8);

bool inSettings = false;
int alkoMax = 1023;
int SIDEBAR_MAX = 7;

#define btnPin 12
#define alkoPin A2

#define DISPLAY_WIDTH 319
#define DISPLAY_HEIGHT 239

#define SIDEBAR_SIZE 75
#define SIDEBAR_MARGIN (DISPLAY_HEIGHT / SIDEBAR_MAX)

#define GRAPH_SIZE (DISPLAY_WIDTH - SIDEBAR_SIZE)

#define btnWidth 50
#define btnHeight 50

#define standbyInteractionI 4000

int colors[][3] = {
  // {27, 231, 255},   // Light blue
  // {110, 235, 131},  // Light green
  // {228, 255, 26},   // Green yellow
  // {232, 170, 20},   // Orange
  // {255, 87, 20},    // Deep orange
  // {233, 188, 183},  // Pink
  // {197, 175, 160},  // Light brown
  // {41, 82, 74},     // Dark green
  // {123, 44, 191},   // Purple

  {209, 41, 224}, // Pink
  {48, 224, 41},
  {224, 223, 41},
  {224, 130, 41}, // Orange
  {224, 41, 41}, // Red
  {41, 194, 224}, // Light blue
  {41, 224, 161}, // Turquieze
  {224, 41, 96}, // Red blue
  {41, 52, 224}, // Blue
  {209, 41, 224}, // Purple
};

int lastInteractionI = 0;

int selectedBar = 0;
int sideBar[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int oldSideBar[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

bool measuring = false;
bool wasPressed = false;
float buffer = 0;
int measureLength = 0;

int graphX = 0;

void startMeasure(){
  buffer = 0;
  measureLength = 0;
  measuring = true;
}

void stopMeasure(){
  if(measuring)
  {
    measuring = false;
    oldSideBar[selectedBar] = sideBar[selectedBar];
    sideBar[selectedBar] = mesaureValue();
    drawBarElement(selectedBar, selectedBar);
  }
}

int mesaureValue()
{
  if(measureLength == 0)
  {
    return 0;
  }
  return buffer / measureLength;
}

void busyStandby()
{
  myGLCD.clrScr();
  myGLCD.setBackColor(VGA_TRANSPARENT);
  myGLCD.setColor(150, 150, 150);
  myGLCD.print("STANDBY", (DISPLAY_WIDTH / 2) + 1 - 30, (DISPLAY_HEIGHT / 2) + 1);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("STANDBY", (DISPLAY_WIDTH / 2) - 30, DISPLAY_HEIGHT / 2);

  while(digitalRead(btnPin) == LOW)
  {
    delay(3500);
  }
  lastInteractionI = 0;
  firstDraw();
}

void setup()
{
  pinMode(btnPin, INPUT);
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);

  firstDraw();
}

void firstDraw(){
  myGLCD.clrScr();
  
  drawChartArea();
  drawSidebar();

  if(inSettings)
  {
    toSettings();
  }
}

void drawBarElement(int selected, int i)
{
  bool showOld = oldSideBar[i] != 0;
  String msg = String(sideBar[i]);

  int backColor = 255;
  if(selected == i)
  {
    backColor = 238;
  }

  myGLCD.setColor(backColor, backColor, backColor);
  myGLCD.fillRect(GRAPH_SIZE, (i * SIDEBAR_MARGIN), DISPLAY_WIDTH, ((i + 1) * SIDEBAR_MARGIN) + 5);

  if(selected == i)
  {
    // myGLCD.setColor(218, 218, 218);
    myGLCD.setColor(colors[i][0], colors[i][1], colors[i][2]);
    myGLCD.fillRect(GRAPH_SIZE + 1, (i * SIDEBAR_MARGIN), GRAPH_SIZE + 1, ((i + 1) * SIDEBAR_MARGIN) + 5);
  }

  // Circle shadow
  myGLCD.setColor(200, 200, 200);
  myGLCD.drawCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))) + 1, 6);
  myGLCD.fillCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))) + 1, 3);

  // Circle
  myGLCD.setColor(colors[i][0], colors[i][1], colors[i][2]);
  myGLCD.drawCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))), 6);
  myGLCD.fillCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))), 3);
  
  if(showOld)
  {
    drawText(msg, GRAPH_SIZE + 30, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2) - 14)), 0, 189);
    drawText(String(oldSideBar[i]), GRAPH_SIZE + 30, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2) - 2)), 150, 189);
  }else{
    drawText(msg, GRAPH_SIZE + 30, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2) - 6)), 0, 189);
  }
}

void drawText(String msg, int x, int y, int color, int backColor)
{
   // Shadow
  myGLCD.setColor(200, 200, 200);
  if(backColor == 189)
  {
    myGLCD.setBackColor(VGA_TRANSPARENT);
  }else{
    myGLCD.setBackColor(backColor, backColor, backColor);
  }
  myGLCD.print(msg, x + 1, y + 1);

  myGLCD.setColor(color, color, color);
  myGLCD.print(msg, x, y);
}

void drawSidebar()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(GRAPH_SIZE, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

  for(int i = 0; i < SIDEBAR_MAX; i++)
  {
      drawBarElement(selectedBar, i);
  }
}

void drawSystem(int x)
{
  myGLCD.setColor(225, 225, 225);
  int unitSizeY = DISPLAY_HEIGHT / 100;

  if((x % (DISPLAY_WIDTH / 10)) == 0)
  {
    myGLCD.fillRect(x, 0, x, DISPLAY_HEIGHT);
  }else{
    for(int y = 0; y <= 110; y += 10)
    {
      int yPos = y * unitSizeY;
      myGLCD.drawPixel(x, yPos);
    }
  }
}

void drawChartArea()
{
  myGLCD.setColor(241, 241, 241);
  myGLCD.fillRect(0, 0, GRAPH_SIZE, DISPLAY_HEIGHT);

  // Draw grid
  for(int x = 0; x < DISPLAY_WIDTH; x++){
    drawSystem(x);

    // Initial score lines for every player
    for(int i = 0; i < SIDEBAR_MAX; i++)
    {
      if(sideBar[i] > 0)
      {
        myGLCD.setColor(colors[i][0], colors[i][1], colors[i][2]);
        int tempY = map(sideBar[i], 0, alkoMax, DISPLAY_HEIGHT, 0);
        myGLCD.drawPixel(x, tempY);
      }
    }
  }
}

void updateSidebar(int newSelectedBar)
{
  drawBarElement(newSelectedBar, selectedBar);
  drawBarElement(newSelectedBar, newSelectedBar);
  selectedBar = newSelectedBar;
}

void updateChart()
{
  //alkoMax
  int value = analogRead(alkoPin);
  value = map(value, 0, alkoMax, 0, 1023);
  int y = map(value, 0, alkoMax, DISPLAY_HEIGHT, 0);

  myGLCD.setColor(241, 241, 241);
  if(graphX + 1 == GRAPH_SIZE)
  {
    myGLCD.fillRect(0, 0, 1, DISPLAY_HEIGHT);
    drawSystem(0);
  }else{
    myGLCD.fillRect(graphX, 0, graphX + 1, DISPLAY_HEIGHT);
    drawSystem(graphX);
    drawSystem(graphX + 1);
  }

  // Draw current score for every player
  for(int i = 0; i < SIDEBAR_MAX; i++)
  {
    if(sideBar[i] > 0)
    {
      myGLCD.setColor(colors[i][0], colors[i][1], colors[i][2]);
      int tempY = map(sideBar[i], 0, alkoMax, DISPLAY_HEIGHT, 0);
      myGLCD.drawPixel(graphX, tempY);
    }
  }
  
  // Draw current value line
  myGLCD.setColor(colors[selectedBar][0], colors[selectedBar][1], colors[selectedBar][2]);
  myGLCD.drawPixel(graphX, y);
  myGLCD.drawPixel(graphX, y - 1);

  drawText(String(value), GRAPH_SIZE / 2, 1, 0, 241);

  myGLCD.setColor(200, 200, 200); // Shadow
  myGLCD.drawPixel(graphX, y + 1);
  myGLCD.setColor(220, 220, 220);
  myGLCD.drawPixel(graphX, y + 2);

  buffer += value;
  measureLength++;
  
  graphX++;
  if(graphX >= GRAPH_SIZE)
  {
    graphX = 0;
  }
}

void toSettings()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  drawText("SETTINGS", (DISPLAY_WIDTH / 2) - 15, 10, 0, 255);
  inSettings = true;
}

void exitSettings()
{
  inSettings = false;
  firstDraw();
}

void drawSettingsText()
{
  myGLCD.setColor(100, 100, 100);
  myGLCD.print("Players:", CENTER, 60);
  myGLCD.print(String(SIDEBAR_MAX), CENTER, 80);
  
  myGLCD.drawRoundRect((DISPLAY_WIDTH / 2) - (100 + btnWidth), 50, (DISPLAY_WIDTH / 2) - 100, 50 + btnHeight); // -
  myGLCD.print("-", (DISPLAY_WIDTH / 2) - (100 + (btnWidth / 2)), 50 + (btnHeight / 2));

  myGLCD.drawRoundRect((DISPLAY_WIDTH / 2) + (100 + btnWidth), 50, (DISPLAY_WIDTH / 2) + 100, 50 + btnHeight); // +
  myGLCD.print("+", (DISPLAY_WIDTH / 2) + (100 + (btnWidth / 2)), 50 + (btnHeight / 2));

  myGLCD.print("Sensitivity MAX:", CENTER, 140);
  myGLCD.print(String(alkoMax), CENTER, 160);
  myGLCD.drawRoundRect((DISPLAY_WIDTH / 2) - (100 + btnWidth), 130, (DISPLAY_WIDTH / 2) - 100, 130 + btnHeight); // -
  myGLCD.print("-", (DISPLAY_WIDTH / 2) - (100 + (btnWidth / 2)), 130 + (btnHeight / 2));

  myGLCD.drawRoundRect((DISPLAY_WIDTH / 2) + (100 + btnWidth), 130, (DISPLAY_WIDTH / 2) + 100, 130 + btnHeight); // +
  myGLCD.print("+", (DISPLAY_WIDTH / 2) + (100 + (btnWidth / 2)), 130 + (btnHeight / 2));

  myGLCD.drawRoundRect((DISPLAY_WIDTH / 2) - (100 + btnWidth), 190, (DISPLAY_WIDTH / 2) + (100 + btnWidth), 190 + btnHeight); // +
  myGLCD.print("Exit", (DISPLAY_WIDTH / 2), 190 + (btnHeight / 2));
}

void handleSettingsTouch()
{
  while(myTouch.dataAvailable())
  {
    lastInteractionI = 0;
    myTouch.read();
    int x = myTouch.getX();
    int y = myTouch.getY();
    if(x != -1 && y != -1)
    {
      if(y >= 50 && y <= (50 + (btnHeight))) // Players
      {
        if(x <= ((DISPLAY_WIDTH / 2) + (100 + btnWidth)) && x >= ((DISPLAY_WIDTH / 2) + 100) && SIDEBAR_MAX < 10)
        {
          SIDEBAR_MAX++;
        }else if(x >= ((DISPLAY_WIDTH / 2) - (100 + btnWidth)) && x <= ((DISPLAY_WIDTH / 2) - 100) && SIDEBAR_MAX > 1)
        {
          if(SIDEBAR_MAX == 10) // Decimal fix
          {
            myGLCD.setColor(255, 255, 255);
            myGLCD.fillRect(0, 40, DISPLAY_WIDTH, 100);
          }
          SIDEBAR_MAX--;
        }
        break;
      }else if(y >= 130 && y <= (130 + btnHeight)) // Sensitivity
      {
        if(x <= ((DISPLAY_WIDTH / 2) + (100 + btnWidth)) && x >= ((DISPLAY_WIDTH / 2) + 100) && alkoMax < 1023)
        {
          alkoMax += 10;
        }else if(x >= ((DISPLAY_WIDTH / 2) - (100 + btnWidth)) && x <= ((DISPLAY_WIDTH / 2) - 100) && alkoMax > 1)
        {
          int newVal = alkoMax - 10;
          if((newVal < 1000 && alkoMax > 1000) || (newVal < 100 && alkoMax > 100) || (newVal < 10 && alkoMax > 10)) // Decimal fix
          {
            myGLCD.setColor(255, 255, 255);
            myGLCD.fillRect(0, 160, DISPLAY_WIDTH, 170);
          }
          alkoMax -= 10;
        }
        break;
      }else if(y >= 190 && y <= (190 + btnHeight)) // Exit
      {
        exitSettings();
        break;
      } 
    }
  }
}

void loop()
{
  int btnPresses = LOW;
  if(inSettings)
  {
    drawSettingsText();
    handleSettingsTouch();
  }else{
    btnPresses = digitalRead(btnPin);
    
    updateChart();
    if(btnPresses == HIGH && wasPressed == false) // Initial button press
    {
      lastInteractionI = 0;
      wasPressed = true;
      startMeasure();
    }else if(btnPresses == LOW && wasPressed) // onKeyUp
    {
      lastInteractionI = 0;
      wasPressed = false;
      stopMeasure();
    }

    myGLCD.setColor(0, 0, 0);
    myGLCD.print("Settings", 10, 5);

    while(myTouch.dataAvailable())
    {
      lastInteractionI = 0;
      myTouch.read();
      int x = myTouch.getX();
      int y = myTouch.getY();

      if(x != -1 && y != -1)
      {
        if(x <= 55 && y <= 30)
        {
          toSettings();
          break;
        }else if(x >= GRAPH_SIZE)
        {
          graphX = 0;
          updateSidebar(y / SIDEBAR_MARGIN);
        } 
      }
    }
  }

  if(btnPresses == LOW)
  {
    lastInteractionI++;
    if(lastInteractionI > standbyInteractionI) // GO TO STANDBY
    {
      busyStandby();
    }
  }
}