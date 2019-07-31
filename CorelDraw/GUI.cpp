#include "GUI.hpp"
#include "Workspace.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include "graphics.h"

int ActiveElement::selected(int x,int y)
{
   return x>=min(x1,x2) && x<=max(x1,x2) && 
             y>=min(y1,y2) && y<=max(y1,y2);
}
// Color
int Color::currBg = 15;
int Color::currFg = 0;
void Color::draw()
{
   setcolor(BLACK);
   setfillstyle(SOLID_FILL,color);
   bar(x1,y1,x2,y2);
   rectangle(x1,y1,x2,y2);
}

void Color::drawCurrent()
{
   setcolor(BLACK);
   setfillstyle(SOLID_FILL,currBg);
   bar(70,415,95,440);
   rectangle(70,415,95,440);
   setfillstyle(SOLID_FILL,currFg);
   bar(60,405,85,430);
   rectangle(60,405,85,430);
}
void Color::press()
{
   if(mousebuttons() == 1)
      setFg(color);
   else
      setBg(color);
   drawCurrent();
}

// Tool
fun_ptr Tool::currTool = createLine;
Tool::Tool(int x1, int y1, int x2, int y2, string path, fun_ptr tool)
   : ActiveElement(x1,y1,x2,y2), tool(tool)
{
   icon = loadBMP(path.c_str());
   draw();
}
void Tool::draw()
{
   if(icon) 
      putimage(x1,y1,icon,COPY_PUT);
   else
   {
      setbkcolor(BLACK);
      setfillstyle(SOLID_FILL,BLACK);
      setcolor(WHITE);
      bar(x1,y1,x2,y2);
      outtextxy(x1+16,y1+13,"?");
   }
}

// ToolBar
ToolBar::ToolBar(int x1, int y1, int x2, int y2)
   : ActiveElement(x1,y1,x2,y2){ draw(); }
void ToolBar::draw()
{
   setcolor(BLACK);
   setfillstyle(SOLID_FILL,WHITE);
   bar(x1,y1,x2,y2);
   rectangle(x1,y1,x2,y2);
}
ToolBar::~ToolBar()
{
   for(auto button : buttons)
      delete button;
}
   
ToolBar &ToolBar::getInstance()
{
   static ToolBar instance(5,5,155,565);
   return instance;
}

void ToolBar::press()
{
   int x = mousex();
   int y = mousey();
   if(selected(x,y))
      for(auto button : buttons)
         if(button->selected(x,y)){
            button->press();
            break;
         }
}
// Coords
Coords::Coords(int x1, int y1, int x2, int y2) 
   : DisplayObj(x1,y1,x2,y2)
{
   setfillstyle(SOLID_FILL,WHITE);
   setcolor(BLACK);
   bar(x1,y1,x2,y2);
   rectangle(x1,y1,x2,y2);
}
Coords &Coords::getInstance()
{
   static Coords instance(5,570,155,595);
   return instance;
}
void Coords::draw()
{
   int x = mousex();
   int y = mousey();
   if(x>=160 && x<=1195 && y>=5 && y<=565)
   {
      x-=160;
      y-=5;
      setcolor(BLACK);
      setbkcolor(WHITE);
      string strX = "x: "+to_string(x)+"      ";
      string strY = "y: "+to_string(y)+"     ";
      outtextxy(15, 575, strX.c_str());
      outtextxy(85, 575, strY.c_str());
      setcolor(Color::getFg());
   }
}
// Path
Path &Path::getInstance()
{
   static Path instance(160,570,1195,595);
   return instance;
}
Path::Path(int x1, int y1, int x2, int y2)
   : ActiveElement(x1,y1,x2,y2)
{
   path = "untitled";
   draw();
}
void Path::draw()
{
   setcolor(BLACK);
   setfillstyle(SOLID_FILL,WHITE);
   bar(x1,y1,x2,y2);
   rectangle(x1,y1,x2,y2);
   outtextxy(170,575,path.c_str());
}
void Path::press()
{
   int x = mousex();
   int y = mousey();
   if(!selected(x,y))
      return;
   int a;
   while(1)
   {
      if(kbhit())
      {
         a = getch();
         if(a == 13)
            break;
         else if(a == 8)
         {
            if(path.size() > 0)
               path.pop_back();
         }
         else if(isalpha(a)||isdigit(a)||a=='\\'||a=='.'||a=='_'||a==':')
            path += a;
         draw();
      }
   }
}
// FileTool
FileTool::FileTool(int x1, int y1, int x2, int y2, string path, fun_ptr tool)
   : ActiveElement(x1,y1,x2,y2), tool(tool)
{
   icon = loadBMP(path.c_str());
   draw();
}
void FileTool::draw()
{
   if(icon)
      putimage(x1,y1,icon,COPY_PUT);
   else
   {
      setbkcolor(BLACK);
      setfillstyle(SOLID_FILL,BLACK);
      setcolor(WHITE);
      bar(x1,y1,x2,y2);
      outtextxy(x1+16,y1+13,"?");
   }
}
void save()
{
   Workspace& ws = Workspace::getInstance();
   FILE *f = fopen((Path::getInstance().getPath()+".form").c_str(), "wb+");
   fseek(f,0,SEEK_SET);
   int size = ws.getFigures().size();
   fwrite(&size,sizeof(int),1,f);
   for(auto it : ws.getFigures())
      it->save(f);
   fclose(f);
}
void load()
{
   int type;
   int x1,y1,x2,y2;
   int color, fill_color;
   int size;
   Workspace& ws = Workspace::getInstance();
   FILE *f = fopen((Path::getInstance().getPath()+".form").c_str(), "rb+");
   if(f == NULL)
   {
      fclose(f);
      return;
   }
   while(!ws.getFigures().empty())
      ws.getFigures().pop_back();
   
   fseek(f,0,SEEK_SET);
   fread(&size,sizeof(int),1,f);
   for(int i = 0; i < size; i++)
   {
      fread(&type,sizeof(int),1,f);
      fread(&x1,sizeof(int),1,f);
      fread(&x2,sizeof(int),1,f);
      fread(&y1,sizeof(int),1,f);
      fread(&y2,sizeof(int),1,f);
      fread(&color,sizeof(int),1,f);
      if(type == 3)
         fread(&fill_color,1,sizeof(int),f);
      switch (type)
      {
         case 1:
            ws.add(new Line(x1,y1,x2,y2,color));
            break;
         case 2:
            ws.add(new Rect(x1,y1,x2,y2,color));
            break;
         case 3:
            ws.add(new Bar(x1,y1,x2,y2,color,fill_color));
            break;
      }
   }
   ws.draw();
   fclose(f);
}