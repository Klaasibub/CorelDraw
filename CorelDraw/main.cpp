#include <vector>
#include "Workspace.hpp"
#include "Figure.hpp"
#include "GUI.hpp"
#include "graphics.h"
#include <iostream>
using namespace std;
void init();

int main()
{
   initwindow(1200,600);
   init();
   ToolBar &tb = ToolBar::getInstance();
   Workspace &ws = Workspace::getInstance();
   Path &path = Path::getInstance();
   Coords &coords = Coords::getInstance();
   
   while(1)
   {
      while(!mousebuttons())
      {
         coords.draw();
         delay(50);
      }
      tb.press();
      path.press();
      ws.press();
      while(mousebuttons())
      {
         coords.draw();
         delay(100);
      }
   }
   closegraph();
}

void init()
{
   setbkcolor(LIGHTGRAY);
   cleardevice();
   setbkcolor(WHITE);
   ToolBar &tb = ToolBar::getInstance();
   
   int count,x,y,d;
   //INIT COLORS
   count = 0;
   x = 40;
   y = 450;
   d = 20;
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
         tb.add(new Color(x+i*d,y+j*d,x+15+i*d,y+15+j*d,count++));
   Color::drawCurrent();
   //INIT TOOLS
   tb.add(new FileTool(15,75,55,115,"save.bmp",save));
   tb.add(new FileTool(60,75,100,115,"load.bmp",load));
   
   tb.add(new Tool(15,120,55,160,"1.bmp",createLine));
   tb.add(new Tool(60,120,100,160,"2.bmp",createRectangle));
   tb.add(new Tool(105,120,145,160,"3.bmp",createBar));
   tb.add(new Tool(15,165,55,205,"4.bmp",deleteFigure));
   tb.add(new Tool(60,165,100,205,"5.bmp",moveFigure));
   tb.add(new Tool(105,165,145,205,"6.bmp",changeFigure));
}