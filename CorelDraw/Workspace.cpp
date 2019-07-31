#include <iostream>
#include <vector>
#include "Workspace.hpp"
#include "graphics.h"
using namespace std;

Workspace::Workspace(int x1,int y1,int x2,int y2)
   : ActiveElement(x1,y1,x2,y2)
{
   size = imagesize(x1,y1,x2,y2);
   setfillstyle(SOLID_FILL,WHITE);
   bar(x1,y1,x2,y2);
   buf = malloc(size);
}
Workspace::~Workspace()
{
   freeimage(buf);
   for(auto figure : figures)
      delete figure;
}
Workspace &Workspace::getInstance()
{
   static Workspace instance(160,5,1195,565);
   return instance;
}
Figure *Workspace::find(int x, int y, int (Figure::*comp)(int,int))
{
   for(int i = figures.size()-1; i >= 0; i--)
      if((figures[i]->*comp)(x-x1,y-y1))
         return figures[i];
   return nullptr;
}
void Workspace::remove(Figure *f)
{
   for(int i = 0; i < figures.size(); i++)
      if(figures[i] == f){
         figures.erase(figures.begin()+i);
         break;
      }
}
void Workspace::press()
{
   fun_ptr Tool = Tool::getTool();
   int x = mousex();
   int y = mousey();
   if(selected(x,y));
      Tool();
}
void Workspace::draw()
{
   setactivepage(1);
   setfillstyle(SOLID_FILL,WHITE);
   bar(x1,y1,x2,y2);
   setviewport(x1,y1,x2,y2,1);
   for(auto figure : figures)
      figure->draw();
   setviewport(0,0,1200,600,1);
   getimage(x1,y1,x2,y2,buf);
   setactivepage(0);
   putimage(x1,y1,buf,COPY_PUT);
}
vector<Figure*> &Workspace::getFigures()
{
   return figures;
}
// Tools:
void createLine()
{
   Workspace &ws = Workspace::getInstance();
   int _x1,_y1,_x2,_y2;
   _x1 = mousex();
   _y1 = mousey();
   if(_x1 < 160 || _x1 > 1195 || _y1 < 5 || _y1 > 565)
      return;
   dynamicDraw(_x1,_y1,_x2,_y2,line);
   ws.add(new Line(_x1,_y1,_x2,_y2,Color::getFg()));
}
void createRectangle()
{
   Workspace &ws = Workspace::getInstance();
   int _x1,_y1,_x2,_y2;
   _x1 = mousex();
   _y1 = mousey();
   if(_x1 < 160 || _x1 > 1195 || _y1 < 5 || _y1 > 565)
      return;
   dynamicDraw(_x1,_y1,_x2,_y2,rectangle);
   ws.add(new Rect(_x1,_y1,_x2,_y2,Color::getFg()));
}
void createBar()
{
   Workspace &ws = Workspace::getInstance();
   int _x1,_y1,_x2,_y2;
   _x1 = mousex();
   _y1 = mousey();
   if(_x1 < 160 || _x1 > 1195 || _y1 < 5 || _y1 > 565)
      return;
   dynamicDraw(_x1,_y1,_x2,_y2,tempBar);
   ws.add(new Bar(_x1,_y1,_x2,_y2,Color::getFg(),Color::getBg()));
}
void dynamicDraw(int &x1, int &y1, int &x2, int &y2, 
                          void (*figure)(int x1, int y1, int x2, int y2))
{
   do
   {
      x2 = mousex();
      y2 = mousey();
      Workspace::getInstance().draw();
      setfillstyle(SOLID_FILL,Color::getBg());
      setcolor(Color::getFg());
      setviewport(160,5,1195,565,1);
      figure(x1-160,y1-5,x2-160,y2-5);
      setviewport(0,0,1200,600,1);
      delay(30);
   }while(mousebuttons());
   x1-=160;
   x2-=160;
   y1-=5; 
   y2-=5;
}
void tempBar(int x1,int y1,int x2,int y2)
{
   bar(min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2));
   rectangle(min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2));
}

void moveFigure()
{
   int dx,dy,x,y;
   Workspace &ws = Workspace::getInstance();
   x = mousex(); 
   y = mousey();
   
   if(!ws.selected(x,y))
      return;
   Figure *t = ws.find(x,y,Figure::selected);
   if(!t)
      return;
   while(mousebuttons())
   {
      dx = mousex(); 
      dy = mousey();
      delay(40);
      x = mousex(); 
      y = mousey();
      dx = x - dx;
      dy = y - dy;
      t->move(dx,dy);
      ws.draw();
   }
}
void changeFigure()
{
   int x,y;
   Workspace &ws = Workspace::getInstance();
   x = mousex(); y = mousey();
   if(!ws.selected(x,y))
      return;
   Figure *t = ws.find(x,y,Figure::vertex);
   if(!t)
      return;
   int vertex = t->vertex(x-160,y-5);
   while(mousebuttons())
   {
      x = mousex();
      y = mousey();
      t->changeSize(x-160,y-5,vertex);
      ws.draw();
   }
}
void deleteFigure()
{
   Workspace &ws = Workspace::getInstance();
   int x = mousex();
   int y = mousey();
   if(!ws.selected(x,y))
      return;
   Figure *t = ws.find(x,y,Figure::selected);
   if(!t)
      return;
   ws.remove(t);
   ws.draw();
}