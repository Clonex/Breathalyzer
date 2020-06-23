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
  10, 
  10, 
  1056, 
  10, 
  10, 
  10, 
  10, 
  10, 
  10, 
  10,
};
 // Wrap around = (startIndex + i) % length
int measureStartX = 0;
int graphBuffer[GRAPH_SIZE * 10] = {0};
int graphX = 0;

int mesaureValue()
{
  int length = abs(graphX - measureStartX);
  int sum = 0;
  for(int i = 0; i < sizeof(graphBuffer); i++)
  {
    int tempX = (measureStartX + i) % length + 1;
    sum += graphBuffer[tempX];
    if(tempX == graphX)
    {
      break;
    }

  }

  return sum;
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
}


void drawBarElement(int selected, int i)
{
  int backColor[3] = {255, 255, 255};
  if(selected == i)
  {
    backColor[0] = 238;
    backColor[1] = 238;
    backColor[2] = 238;
  }

  myGLCD.setColor(backColor[0], backColor[1], backColor[2]);
  myGLCD.fillRect(GRAPH_SIZE, (i * SIDEBAR_MARGIN), DISPLAY_WIDTH, ((i + 1) * SIDEBAR_MARGIN) + 5);
  
  myGLCD.setColor(colors[i][0], colors[i][1], colors[i][2]);
  myGLCD.drawCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))), 6);
  myGLCD.fillCircle(GRAPH_SIZE + 15, (i * SIDEBAR_MARGIN + ((SIDEBAR_MARGIN / 2))), 4);

  myGLCD.setColor(0, 0, 0);

  myGLCD.setBackColor(backColor[0], backColor[1], backColor[1]);

  char msg[30];
  itoa(sideBar[i], msg, 10);
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

void drawChartArea()
{
  myGLCD.setColor(241, 241, 241);
  myGLCD.fillRect(0, 0, GRAPH_SIZE, DISPLAY_HEIGHT);
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
  int y = map(value, 0, 1023, 0, DISPLAY_HEIGHT);
  int tempX = graphX % GRAPH_SIZE;

  myGLCD.setColor(241, 241, 241);
  myGLCD.fillRect(tempX, 0, tempX + 1, DISPLAY_HEIGHT);

  myGLCD.setColor(colors[selectedBar][0], colors[selectedBar][1], colors[selectedBar][2]);
  myGLCD.drawPixel(tempX, y);
  myGLCD.drawPixel(tempX, y - 1);
  myGLCD.drawPixel(tempX, y + 1);

  graphBuffer[graphX] = value;
  graphX++;
  if(graphX > sizeof(graphBuffer))
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

  int tempValue = mesaureValue();
  char msg[30];
  itoa(tempValue, msg, 10);
  myGLCD.print(msg, CENTER, CENTER);
}
