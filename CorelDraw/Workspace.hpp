#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP
#include <vector>
#include "GUI.hpp"
#include "Figure.hpp"
#include "graphics.h"
using namespace std;


//������� �������
class Workspace : public ActiveElement
{
   int size; //������ ������� �������
   void *buf; // ��������������� ����, ��� ���������� ������� ������
   vector<Figure* > figures; //�������� ����� ����������� � ������� �������
   Workspace(int x1,int y1,int x2,int y2);
   ~Workspace();
   Workspace(Workspace const&)=delete;
   Workspace& operator=(const Workspace&)=delete;
   public:
      static Workspace &getInstance();
      // ����� ������ ������  � �������� ��������
      Figure *find(int x, int y, int (Figure::*comp)(int,int));
      vector<Figure*> &getFigures();
      void press(); // ������� �� ������� �� ������� �������
      void draw(); // ����������� ����� �� ������
      void add(Figure *figure){ figures.push_back(figure); } // �������� ������
      void remove(Figure *f); // ������� ������
};

void createLine(); // ���������� �����
void createRectangle(); // ���������� �������������
void createBar(); //���������� ����������� �������������
//��������������� ������� ��� ������������� ����������� ��� ���������
void dynamicDraw(int &x1, int &y1, int &x2, int &y2, 
                         void (*figure)(int x1, int y1, int x2, int y2));
void tempBar(int x1,int y1,int x2,int y2); // ������� ��� ������������ ��������������
void deleteFigure(); //���������� �������� ������
void moveFigure(); // ���������� ����������� ������
void changeFigure(); // ���������� ��������� �������� ������
#endif