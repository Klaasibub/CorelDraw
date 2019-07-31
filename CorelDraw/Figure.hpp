#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "GUI.hpp"
#include "graphics.h"
// ����������� ����� - ������
class Figure : public DisplayObj
{
   protected:
      int type;
      int color; // ���� ������� ������
   public:
      Figure(int x1,int y1,int x2,int y2, int color)
         : DisplayObj(x1,y1,x2,y2),color(color){}
      virtual void move(int dx, int dy); // ����������� ������
      virtual int vertex(int x, int y); // ������� �������, �� ������� ������
      virtual void changeSize(int x, int y, int vert); // ��������� ������� ������
      virtual int selected(int x, int y); //�������� �� �� �� ������
      virtual void save(FILE *f); // ��������� ������
};
// ����� - �����
class Line : public Figure
{
   public:
      Line(int x1,int y1,int x2,int y2,int color):Figure(x1,y1,x2,y2,color){ type = 1; }
      void draw(); //���������� �����
      int selected(int x, int y); //�������� �� �� �� �����
};
// ����� - �������������
class Rect : public Figure
{
   public:
      Rect(int x1,int y1,int x2,int y2,int color):Figure(x1,y1,x2,y2,color){ type = 2; }
      void draw(); // ���������� �������������
};
// ����� - ����������� �������������
class Bar : public Figure
{
   int fill_color; // ���� ��������
   public:
      Bar(int x1,int y1,int x2,int y2,int color,int fill_color);
      void draw(); // ���������� ����������� �������������
      void save(FILE *f){ Figure::save(f); fwrite(&fill_color,1,sizeof(int),f); }
};

#endif