#include <iostream>
#include <cmath>
#include "Figure.hpp"
#include "graphics.h"
using namespace std;

int Figure::selected(int x,int y)
{
   return x>=min(x1,x2) && x<=max(x1,x2) && 
             y>=min(y1,y2) && y<=max(y1,y2);
}
void Figure::move(int dx, int dy)
{ 
   x1+=dx; 
   x2+= dx; 
   y1+=dy; 
   y2+=dy;
}
int Figure::vertex(int x, int y)
{
   if(abs(x-x1) < 5 && abs(y-y1) < 5)
      return 1;
   if(abs(x-x2) < 5 && abs(y-y1) < 5)
      return 2;
   if(abs(x-x1) < 5 && abs(y-y2) < 5)
      return 3;
   if(abs(x-x2) < 5 && abs(y-y2) < 5)
      return 4;
   return 0;
}
void Figure::changeSize(int x, int y, int vert)
{
   switch(vert)
   {
      case 1:
         x1 = x;
         y1 = y;
         break;
      case 2:
         x2 = x;
         y1 = y;
         break;
      case 3:
         x1 = x;
         y2 = y;
         break;
      case 4:
         x2 = x;
         y2 = y;
         break;
   }
}
void Figure::save(FILE *f)
{
   fwrite(&type,sizeof(int),1,f);
   fwrite(&x1,sizeof(int),1,f);
   fwrite(&x2,sizeof(int),1,f);
   fwrite(&y1,sizeof(int),1,f);
   fwrite(&y2,sizeof(int),1,f);
   fwrite(&color,sizeof(int),1,f);
}
Bar::Bar(int x1,int y1,int x2,int y2,int color,int fill_color)
   : Figure(x1,y1,x2,y2,color),fill_color(fill_color){ type = 3; }
void Bar::draw()
{ 
   setcolor(color); 
   setfillstyle(1,fill_color);
   bar(x1,y1,x2,y2);
   rectangle(x1,y1,x2,y2); 
}
void Rect::draw()
{
   setcolor(color);
   rectangle(x1,y1,x2,y2);
}
void Line::draw()
{
   setcolor(color);
   line(x1,y1,x2,y2);
}

int Line::selected(int x, int y)
{
   //Коэф-ы k и b уравнения линии: y = kx + b;
   double k = (x2==x1)?1000:double(y2-y1)/(x2-x1);
   double b = double(x2*y1 - y2*x1)/(x2-x1);
   int sign = k/abs(k);
   
   if(x > min(x1,x2)-3 && x < max(x1,x2)+3 && 
      y > min(y1,y2)-3 && y < max(y1,y2)+3)
   {
      if(fabs(k) > 16 || fabs(k) < 0.07)
      {
         return true;
      }
      else if(y > k*(x-4*sign)+b && y < k*(x+4*sign)+b && 
                y > k*x+b-4 && y < k*x+b+4)
         return true;
      return false;
   }
   return false;
}