#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP
#include <vector>
#include "GUI.hpp"
#include "Figure.hpp"
#include "graphics.h"
using namespace std;


//–абоча€ область
class Workspace : public ActiveElement
{
   int size; //размер рабочей области
   void *buf; // вспомогательное поле, дл€ сохранени€ области экрана
   vector<Figure* > figures; //хранение фигур наход€щихс€ в рабочей области
   Workspace(int x1,int y1,int x2,int y2);
   ~Workspace();
   Workspace(Workspace const&)=delete;
   Workspace& operator=(const Workspace&)=delete;
   public:
      static Workspace &getInstance();
      // поиск нужной фигуры  с заданным условием
      Figure *find(int x, int y, int (Figure::*comp)(int,int));
      vector<Figure*> &getFigures();
      void press(); // реакци€ на нажатие по рабочей области
      void draw(); // отображение фигур на экране
      void add(Figure *figure){ figures.push_back(figure); } // добавить фигуру
      void remove(Figure *f); // удалить фигуру
};

void createLine(); // инструмент лини€
void createRectangle(); // инструмент пр€моугольник
void createBar(); //инструмент закрашенный пр€моугольник
//вспомогательна€ функци€ дл€ динамического отображени€ при рисовании
void dynamicDraw(int &x1, int &y1, int &x2, int &y2, 
                         void (*figure)(int x1, int y1, int x2, int y2));
void tempBar(int x1,int y1,int x2,int y2); // функци€ дл€ закрашенного пр€моугольника
void deleteFigure(); //инструмент удаление фигуры
void moveFigure(); // инструмент перемещение фигуры
void changeFigure(); // инструмент изменение размеров фигуры
#endif