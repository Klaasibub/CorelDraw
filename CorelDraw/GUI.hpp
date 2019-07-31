#ifndef GUI_HPP
#define GUI_HPP
#include <list>
#include "graphics.h"
using namespace std;
typedef void (*fun_ptr)(); // Вспомогательный тип указатель на функцию

// Класс отображаемых объектов
class DisplayObj
{
   protected:
      int x1,y1,x2,y2; 
   public:
      DisplayObj(int x1, int y1, int x2, int y2)
         : x1(x1),y1(y1),x2(x2),y2(y2){}
      virtual ~DisplayObj(){}
      virtual void draw()=0; 
};
//Класс элементов с которыми можно взаимодействовать
class ActiveElement : public DisplayObj
{
   public:
      ActiveElement(int x1, int y1, int x2, int y2):DisplayObj(x1,y1,x2,y2){}
      virtual void press()=0; 
      virtual int selected(int x, int y); // проверка на то, навелись ли мы на объект
};
//Класс отвечающий за цвета рисования
class Color : public ActiveElement
{
   static int currBg, currFg; // Текущие цвета закраски и рисования
   int color; // Цвет закрепленный за кнопкой выбора цвета
   public:
      Color(int x1, int y1, int x2, int y2, int color)
         : ActiveElement(x1,y1,x2,y2),color(color){ draw(); }
      static int getBg(){ return currBg; } //Возвращает текущий цвет закраски
      static int getFg(){ return currFg; } //Возвращает текущий цвет рисования
      static void setBg(int color){ currBg = color; } // Устанавливает текущий цвет закраски
      static void setFg(int color){ currFg = color; } // Устанавливает текущий цвет рисования
      static void drawCurrent(); //Отобразить на экране текущие цвета закраски и рисования
      void draw(); // Отображение кнопки выбора цвета
      void press(); // Установка цвета при нажатии
};
//Класс отвечающий за инструменты 
class Tool : public ActiveElement
{
   IMAGE *icon; // иконка инструмента
   static fun_ptr currTool; // текущий выбранный инструмент
   fun_ptr tool; // инструмент закрепленный за кнопкой
   public:
      Tool(int x1, int y1, int x2, int y2, string path, fun_ptr tool);
      ~Tool(){ freeimage(icon); } 
      static fun_ptr getTool(){ return currTool; } //Возвращает текущую функцию-инструмент
      void draw(); // Отображение инструмента
      void press(){ currTool = tool; } // Установка инструмента при нажатии
};

// Singleton - Класс хранящий в себе список доступных инструментов
class ToolBar : ActiveElement
{
   list<ActiveElement* > buttons; //Лист кнопок изменения цвета и выбора инструмента
   ToolBar(int x1, int y1, int x2, int y2);
   ~ToolBar();
   ToolBar(ToolBar const&)=delete;
   ToolBar& operator=(const ToolBar&)=delete;
   public:
      static ToolBar &getInstance(); 
      void add(ActiveElement *Tool){ buttons.push_back(Tool); } // Добавление инструмента в список
      void press(); // Реакция на нажатие
      void draw(); // Отобразить панель
};
//Координаты мыши в области Workspace
class Coords : public DisplayObj
{
   Coords(int x1, int y1, int x2, int y2);
   Coords(Coords const&)=delete;
   Coords& operator=(const Coords&)=delete;
   public:
      static Coords &getInstance();
      void draw(); // отобразить текущие координаты
};
//Класс отвечающий за путь до файла
class Path : public ActiveElement
{
   string path; // путь в текстовом представлении
   Path(int x1, int y1, int x2, int y2);
   Path(Path const&)=delete;
   Path& operator=(const Path&)=delete;
   public:
      static Path &getInstance();
      void draw(); // Отобразить текущий путь
      void press(); // Изменение пути 
      string getPath() { return path; } // Вернуть путь до файла
};
class FileTool : public ActiveElement
{
   IMAGE *icon; // иконка инструмента
   fun_ptr tool; // инструмент закрепленный за кнопкой
   public:
      FileTool(int x1, int y1, int x2, int y2, string path, fun_ptr tool);
      ~FileTool(){ freeimage(icon); }
      void draw(); // Отображение инструмента
      void press(){ tool(); } // Сохранение/Загрузка в зависимости от кнопки
};
void save(); // сохранение файла
void load(); // загрузка файла
#endif