#ifndef GUI_HPP
#define GUI_HPP
#include <list>
#include "graphics.h"
using namespace std;
typedef void (*fun_ptr)(); // ��������������� ��� ��������� �� �������

// ����� ������������ ��������
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
//����� ��������� � �������� ����� �����������������
class ActiveElement : public DisplayObj
{
   public:
      ActiveElement(int x1, int y1, int x2, int y2):DisplayObj(x1,y1,x2,y2){}
      virtual void press()=0; 
      virtual int selected(int x, int y); // �������� �� ��, �������� �� �� �� ������
};
//����� ���������� �� ����� ���������
class Color : public ActiveElement
{
   static int currBg, currFg; // ������� ����� �������� � ���������
   int color; // ���� ������������ �� ������� ������ �����
   public:
      Color(int x1, int y1, int x2, int y2, int color)
         : ActiveElement(x1,y1,x2,y2),color(color){ draw(); }
      static int getBg(){ return currBg; } //���������� ������� ���� ��������
      static int getFg(){ return currFg; } //���������� ������� ���� ���������
      static void setBg(int color){ currBg = color; } // ������������� ������� ���� ��������
      static void setFg(int color){ currFg = color; } // ������������� ������� ���� ���������
      static void drawCurrent(); //���������� �� ������ ������� ����� �������� � ���������
      void draw(); // ����������� ������ ������ �����
      void press(); // ��������� ����� ��� �������
};
//����� ���������� �� ����������� 
class Tool : public ActiveElement
{
   IMAGE *icon; // ������ �����������
   static fun_ptr currTool; // ������� ��������� ����������
   fun_ptr tool; // ���������� ������������ �� �������
   public:
      Tool(int x1, int y1, int x2, int y2, string path, fun_ptr tool);
      ~Tool(){ freeimage(icon); } 
      static fun_ptr getTool(){ return currTool; } //���������� ������� �������-����������
      void draw(); // ����������� �����������
      void press(){ currTool = tool; } // ��������� ����������� ��� �������
};

// Singleton - ����� �������� � ���� ������ ��������� ������������
class ToolBar : ActiveElement
{
   list<ActiveElement* > buttons; //���� ������ ��������� ����� � ������ �����������
   ToolBar(int x1, int y1, int x2, int y2);
   ~ToolBar();
   ToolBar(ToolBar const&)=delete;
   ToolBar& operator=(const ToolBar&)=delete;
   public:
      static ToolBar &getInstance(); 
      void add(ActiveElement *Tool){ buttons.push_back(Tool); } // ���������� ����������� � ������
      void press(); // ������� �� �������
      void draw(); // ���������� ������
};
//���������� ���� � ������� Workspace
class Coords : public DisplayObj
{
   Coords(int x1, int y1, int x2, int y2);
   Coords(Coords const&)=delete;
   Coords& operator=(const Coords&)=delete;
   public:
      static Coords &getInstance();
      void draw(); // ���������� ������� ����������
};
//����� ���������� �� ���� �� �����
class Path : public ActiveElement
{
   string path; // ���� � ��������� �������������
   Path(int x1, int y1, int x2, int y2);
   Path(Path const&)=delete;
   Path& operator=(const Path&)=delete;
   public:
      static Path &getInstance();
      void draw(); // ���������� ������� ����
      void press(); // ��������� ���� 
      string getPath() { return path; } // ������� ���� �� �����
};
class FileTool : public ActiveElement
{
   IMAGE *icon; // ������ �����������
   fun_ptr tool; // ���������� ������������ �� �������
   public:
      FileTool(int x1, int y1, int x2, int y2, string path, fun_ptr tool);
      ~FileTool(){ freeimage(icon); }
      void draw(); // ����������� �����������
      void press(){ tool(); } // ����������/�������� � ����������� �� ������
};
void save(); // ���������� �����
void load(); // �������� �����
#endif