#include <UTFT.h>
#include <ITDB02_Touch.h>

extern uint8_t SmallFont[];

int alkoPin = A2;
UTFT myGLCD(ILI9325C,A5,A4,A3,11);
ITDB02_Touch  myTouch( A1, 10, A0, 9, 8);

#define DISPLAY_WIDTH 319
#define DISPLAY_HEIGHT 239
#define SIDEBAR_SIZE 75
#define SIDEBAR_MAX 7
#define SIDEBAR_MARGIN (DISPLAY_HEIGHT / SIDEBAR_MAX)

#define GRAPH_SIZE (DISPLAY_WIDTH - SIDEBAR_SIZE)

int colors[][3] = {
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

int selectedBar = 0;
int sideBar[] = {
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0,
};

float buffer = 0;
int measureLength = 0;

int graphX = 0;

void startMeasure(){
  buffer = 0;
  measureLength = 0;
}

void stopMeasure(){
  sideBar[selectedBar] = mesaureValue();
  drawBarElement(selectedBar, selectedBar);
}

int mesaureValue()
{
  if(measureLength == 0)
  {
    return 0;
  }
  return buffer / measureLength;
}

void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.clrScr();
  drawChartArea();
  drawSidebar();

  startMeasure(); // TEMP
}


void drawBarElement(int selected, int i)
{
  char msg[3];
  itoa(sideBar[i], msg, 10);

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

  // Shadow
  myGLCD.setColor(200, 200, 200);
  myGLCD.drawCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))) + 1, 6);
  myGLCD.fillCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))) + 1, 3);
  myGLCD.setBackColor(VGA_TRANSPARENT);
  myGLCD.print(msg, GRAPH_SIZE + 31, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2) - 6)) + 1);

  
  myGLCD.setColor(colors[i][0], colors[i][1], colors[i][2]);
  myGLCD.drawCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))), 6);
  myGLCD.fillCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))), 3);

  myGLCD.setColor(0, 0, 0);
  myGLCD.print(msg, GRAPH_SIZE + 30, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2) - 6)));
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
  }


  // for(int y = 0; y <= 110; y += 10)
  // {
  //   int yPos = y * unitSizeY;
  //   myGLCD.fillRect(0, yPos, GRAPH_SIZE, yPos + 1);

  //   for(int x = 0; x < 100; x += 10)
  //   {
  //     int xPos = x * unitSizeX;
  //     myGLCD.fillRect(xPos, 0, xPos + 1, DISPLAY_HEIGHT);
  //   }
  // }
}

void updateSidebar(int newSelectedBar)
{
  drawBarElement(newSelectedBar, selectedBar);
  drawBarElement(newSelectedBar, newSelectedBar);
  selectedBar = newSelectedBar;
}

void updateChart()
{
  int value = analogRead(alkoPin);
  int y = map(value, 0, 1023, DISPLAY_HEIGHT, 0);

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

  myGLCD.setColor(colors[selectedBar][0], colors[selectedBar][1], colors[selectedBar][2]);
  myGLCD.drawPixel(graphX, y);
  myGLCD.drawPixel(graphX, y - 1);

  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(241, 241, 241);
  String val = String(value);
  myGLCD.print(val, GRAPH_SIZE / 2, 1);

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

void loop()
{
  updateChart();

  while(myTouch.dataAvailable())
  {
    myTouch.read();
    int x = myTouch.getX();
    int y = myTouch.getY();
    if(x != -1 && y != -1)
    {
      if(x >= GRAPH_SIZE)
      {
        graphX = 0;
        updateSidebar(y / SIDEBAR_MARGIN);
      }
    }
  }
}