#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "GUI.hpp"
#include "graphics.h"
// Абстрактный класс - фигура
class Figure : public DisplayObj
{
   protected:
      int type;
      int color; // цвет контура фигуры
   public:
      Figure(int x1,int y1,int x2,int y2, int color)
         : DisplayObj(x1,y1,x2,y2),color(color){}
      virtual void move(int dx, int dy); // перемещение фигуры
      virtual int vertex(int x, int y); // вернуть вершину, на которую нажали
      virtual void changeSize(int x, int y, int vert); // изменение размера фигуры
      virtual int selected(int x, int y); //навелись ли мы на фигуру
      virtual void save(FILE *f); // сохранить фигуру
};
// Класс - линия
class Line : public Figure
{
   public:
      Line(int x1,int y1,int x2,int y2,int color):Figure(x1,y1,x2,y2,color){ type = 1; }
      void draw(); //отобразить линию
      int selected(int x, int y); //навелись ли мы на линию
};
// Класс - прямоугольник
class Rect : public Figure
{
   public:
      Rect(int x1,int y1,int x2,int y2,int color):Figure(x1,y1,x2,y2,color){ type = 2; }
      void draw(); // отобразить прямоугольник
};
// Класс - заполненный прямоугольник
class Bar : public Figure
{
   int fill_color; // цвет закраски
   public:
      Bar(int x1,int y1,int x2,int y2,int color,int fill_color);
      void draw(); // отобразить закрашенный прямоугольник
      void save(FILE *f){ Figure::save(f); fwrite(&fill_color,1,sizeof(int),f); }
};

#endif