/*-------------------------------------------------------------------------

          GUI Calculator

Programmer           : Nemonet TYP


Software Details
====================
Developed in   : C++
Compiler used  : CodeBlocks
OS             : Windows OS


License   : Protected (Please give the credit of programming to author.)


-------------------------------------------------------------------------------------*/



#include "iostream"
#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

// Window
#define TITLEBARHEIGHT 21
#define BORDERWIDTH 1


#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3
#define DIVIDE 4

/*--------------------- Global Data ---------------------*/

int ButtonId;
enum bool{false,true};
enum BUTTON{MOUSE_NORMAL = 0,MOUSE_LBUTTON=1,MOUSE_RBUTTON=2,MOUSE_MBUTTON=4};
enum BUTTON_STATUS
{
   BUTTON_STATUS_NORMAL,
   BUTTON_STATUS_DOWN
};

/*------------------------------------------------------
       Mouse Class
------------------------------------------------------*/
class Mouse

{
  private:

   int MouseXpos, MouseYpos;
   BUTTON MouseBtn;
   union REGS in,out;

  public:

   int InstallMouse();
   int ShowMouse();
   int HideMouse();
   void GetMouseStatus();
   BUTTON GetButton();
   int GetPosX();
   int GetPosY();
   void SetMousePosi(int &xpos, int &ypos);
   int MouseInside(int x1, int y1, int x2, int y2);
   void RestrictMousePtr(int x1, int y1, int x2, int y2);

};


 int Mouse::InstallMouse()
 {
std::cerr << "[ERROR] >>> Entering Mouse::InstallMouse()" << std::endl;

  in.x.ax = 0;
  int86(51,&in,&out);
std::cerr << "[WARN] <<< Exiting Mouse::InstallMouse()" << std::endl;
  return out.x.ax;

 }
 int Mouse::ShowMouse()
 {
std::cerr << "[ERROR] >>> Entering Mouse::ShowMouse()" << std::endl;

  in.x.ax = 1;
  int86(51,&in,&out);
std::cerr << "[WARN] <<< Exiting Mouse::ShowMouse()" << std::endl;
  return 1;

 }
 int Mouse::HideMouse()
 {
std::cerr << "[ERROR] >>> Entering Mouse::HideMouse()" << std::endl;

  in.x.ax = 2;
  int86(51,&in,&out);
std::cerr << "[WARN] <<< Exiting Mouse::HideMouse()" << std::endl;
  return 1;

 }
 void Mouse::GetMouseStatus()
 {
std::cerr << "[ERROR] >>> Entering Mouse::GetMouseStatus()" << std::endl;

  in.x.ax = 3;
  int86(51,&in,&out);
  MouseXpos = out.x.cx;
std::cerr << "[DEBUG] Mouse::GetMouseStatus(): MouseXpos → " << MouseXpos << std::endl;
  MouseYpos = out.x.dx;
std::cerr << "[DEBUG] Mouse::GetMouseStatus(): MouseYpos → " << MouseYpos << std::endl;
  MouseBtn = out.x.bx;
std::cerr << "[DEBUG] Mouse::GetMouseStatus(): MouseBtn → " << MouseBtn << std::endl;

std::cerr << "[WARN] <<< Exiting Mouse::GetMouseStatus()" << std::endl;
 }
 BUTTON Mouse::GetButton()
 {
std::cerr << "[ERROR] >>> Entering Mouse::GetButton()" << std::endl;
  std::cerr << "[WARN] <<< Exiting Mouse::GetButton()" << std::endl;
  return MouseBtn;
 }

 int Mouse::GetPosX()
 {
std::cerr << "[ERROR] >>> Entering Mouse::GetPosX()" << std::endl;
  std::cerr << "[WARN] <<< Exiting Mouse::GetPosX()" << std::endl;
  return MouseXpos;
 }

 int Mouse::GetPosY()
 {
std::cerr << "[ERROR] >>> Entering Mouse::GetPosY()" << std::endl;
  std::cerr << "[WARN] <<< Exiting Mouse::GetPosY()" << std::endl;
  return MouseYpos;
 }

 void Mouse::SetMousePosi(int &xpos, int &ypos)
 {
std::cerr << "[ERROR] >>> Entering Mouse::SetMousePosi(xpos=" << xpos << ",ypos=" << ypos << ")" << std::endl;
  in.x.ax = 4;
  in.x.cx = xpos;
  in.x.dx = ypos;
  int86(51,&in,&out);
std::cerr << "[WARN] <<< Exiting Mouse::SetMousePosi(xpos=" << xpos << ",ypos=" << ypos << ")" << std::endl;
 }
 int Mouse::MouseInside(int x1, int y1, int x2, int y2)
 {
std::cerr << "[ERROR] >>> Entering Mouse::MouseInside(x1=" << x1 << ",y1=" << y1 << ",x2=" << x2 << ",y2=" << y2 << ")" << std::endl;
  int x_pos, y_pos;
  in.x.ax = 3;
  int86(51,&in,&out);
  x_pos = out.x.cx;
std::cerr << "[DEBUG] Mouse::MouseInside(x1=" << x1 << ",y1=" << y1 << ",x2=" << x2 << ",y2=" << y2 << "): x_pos → " << x_pos << std::endl;
  y_pos = out.x.dx;
std::cerr << "[DEBUG] Mouse::MouseInside(x1=" << x1 << ",y1=" << y1 << ",x2=" << x2 << ",y2=" << y2 << "): y_pos → " << y_pos << std::endl;

  if(x_pos >= x1 && y_pos >= y1 && x_pos <= x2 && y_pos <= y2)
   return 1;
  else
   return 0;

 }
 void Mouse::RestrictMousePtr(int x1, int y1, int x2, int y2)
 {
std::cerr << "[ERROR] >>> Entering Mouse::RestrictMousePtr(x1=" << x1 << ",y1=" << y1 << ",x2=" << x2 << ",y2=" << y2 << ")" << std::endl;

  in.x.ax = 7;
  in.x.cx = x1;
  in.x.dx = x2;
  int86(51,&in,&out);

  in.x.ax = 8;
  in.x.cx = y1;
  in.x.dx = y2;
  int86(51,&in,&out);

std::cerr << "[WARN] <<< Exiting Mouse::RestrictMousePtr(x1=" << x1 << ",y1=" << y1 << ",x2=" << x2 << ",y2=" << y2 << ")" << std::endl;
 }


/*------------------------------------------------------
       End of Mouse Class
------------------------------------------------------*/


/*------------------------------------------------------
       TextBox Class
------------------------------------------------------*/

class TextBox
{

 private:

 int Alignment;

 int Left,Top,Width,Height;
 char Caption[50];

 public:

 TextBox(int left, int top, int width, int height, char caption[],int Align);
 void Draw();
 void SetText(char text[]);
 char *GetText();
 void Clear();
};

 TextBox::TextBox(int left, int top, int width, int height, char caption[],int Align)
    {
  Left = left;
  Top = top;
  Width = width;
  Height = height;
  strcpy(Caption,caption);
  Alignment = Align;
    }


    void TextBox::Draw()
   {
std::cerr << "[ERROR] >>> Entering TextBox::Draw()" << std::endl;
  setfillstyle(SOLID_FILL,WHITE);
  bar(Left,Top,Left+Width,Top+Height);

  setcolor(DARKGRAY);
  rectangle(Left,Top,Left+Width,Top+Height);

  setcolor(BLACK);

  settextjustify(Alignment,TOP_TEXT);
  if(Alignment==LEFT_TEXT)
   outtextxy(Left+2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
  else
   if(Alignment==RIGHT_TEXT)
    outtextxy(Left+Width-2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
  else
   outtextxy(Left+(Width/2),Top+1+((Height/2)-(textheight(Caption)/2)),Caption);


std::cerr << "[WARN] <<< Exiting TextBox::Draw()" << std::endl;
   }


 void TextBox::SetText(char text[])
 {
std::cerr << "[ERROR] >>> Entering TextBox::SetText(text=" << text << ")" << std::endl;
  if (Left + textwidth(Caption) <= Left + Width - textwidth(" "))
  {
   strcat(Caption,text);
   Draw();
  }
std::cerr << "[WARN] <<< Exiting TextBox::SetText(text=" << text << ")" << std::endl;
 }

 char *TextBox::GetText()
 {
std::cerr << "[ERROR] >>> Entering TextBox::GetText()" << std::endl;
  std::cerr << "[WARN] <<< Exiting TextBox::GetText()" << std::endl;
  return Caption;
 }

 void TextBox::Clear()
 {
std::cerr << "[ERROR] >>> Entering TextBox::Clear()" << std::endl;
  strcpy(Caption,"");
  Draw();
std::cerr << "[WARN] <<< Exiting TextBox::Clear()" << std::endl;
 }


/*------------------------------------------------------
       End of TextBox Class
------------------------------------------------------*/

/*-------------------Mouse Object---------------------*/

static Mouse mouse;

/*------------------------------------------------------
       Button Class
------------------------------------------------------*/

class Button
{

 private:

 int Left,Top,Width,Height,ID;
 char Caption[50];
 BUTTON_STATUS btnStatus;
 void MouseDown();
 void MouseUp();
 bool State;

 public:

 Button(int left, int top, int width, int height, char caption[], int Id);
 void Draw();
 void EnableClickHandler();

};

 Button::Button(int left, int top, int width, int height, char caption[], int Id)
    {
  Left = left;
  Top = top;
  Width = width;
  Height = height;
  strcpy(Caption,caption);
  ID = Id;
  btnStatus = BUTTON_STATUS_NORMAL;
  State = false;
    }


   void Button::Draw()
   {
std::cerr << "[ERROR] >>> Entering Button::Draw()" << std::endl;
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(Left,Top,Left+Width,Top+Height);

  setcolor(WHITE);
  line(Left,Top,Left+Width,Top);
  line(Left,Top,Left,Top+Height);

  setcolor(BLACK);
  line(Left+Width,Top,Left+Width,Top+Height);
  line(Left,Top+Height,Left+Width,Top+Height);

  settextjustify(LEFT_TEXT,TOP_TEXT);
  setcolor(BLACK);
  outtextxy(Left + (Width/2) - textwidth(Caption)/2 + 1,
  Top + (Height/2) - textheight(Caption)/2 + 1, Caption);

std::cerr << "[WARN] <<< Exiting Button::Draw()" << std::endl;
   }

   void Button::MouseDown()
   {
std::cerr << "[ERROR] >>> Entering Button::MouseDown()" << std::endl;




    mouse.HideMouse();

    setcolor(BLACK);
    line(Left,Top,Left+Width,Top);
    line(Left,Top,Left,Top+Height);

    setcolor(WHITE);
    line(Left+Width,Top,Left+Width,Top+Height);
    line(Left,Top+Height,Left+Width,Top+Height);

    mouse.ShowMouse();




std::cerr << "[WARN] <<< Exiting Button::MouseDown()" << std::endl;
   }

   void Button::MouseUp()
   {
std::cerr << "[ERROR] >>> Entering Button::MouseUp()" << std::endl;



     mouse.HideMouse();

     setcolor(WHITE);
     line(Left,Top,Left+Width,Top);
     line(Left,Top,Left,Top+Height);

     setcolor(BLACK);
     line(Left+Width,Top,Left+Width,Top+Height);
     line(Left,Top+Height,Left+Width,Top+Height);

     mouse.ShowMouse();

std::cerr << "[WARN] <<< Exiting Button::MouseUp()" << std::endl;
   }

   void Button::EnableClickHandler()
   {
std::cerr << "[ERROR] >>> Entering Button::EnableClickHandler()" << std::endl;

  if(State)
  {
   ButtonId = 0;
std::cerr << "[DEBUG] Button::EnableClickHandler(): ButtonId → " << ButtonId << std::endl;
   State = false;
std::cerr << "[DEBUG] Button::EnableClickHandler(): State → " << State << std::endl;
   return;
  }

  if( mouse.MouseInside(Left,Top,Left+Width,Top+Height) == 1)
  {

   if( mouse.GetButton() == MOUSE_LBUTTON)
   {
    MouseDown();
    btnStatus = BUTTON_STATUS_DOWN;
	std::cerr << "[ERROR] Button::EnableClickHandler(): btnStatus → " << btnStatus << std::endl;
	std::cerr << "[DEBUG] Button::EnableClickHandler(): btnStatus → " << btnStatus << std::endl;
   }

   else if(btnStatus == BUTTON_STATUS_DOWN &&  mouse.GetButton() == MOUSE_NORMAL)
   {
    MouseUp();
    ButtonId = ID;
	std::cerr << "[ERROR] Button::EnableClickHandler(): ButtonId → " << ButtonId << std::endl;
    btnStatus = BUTTON_STATUS_NORMAL;
    State = true;
	std::cerr << "[ERROR] Button::EnableClickHandler(): State → " << State << std::endl;

   }

  }

std::cerr << "[WARN] <<< Exiting Button::EnableClickHandler()" << std::endl;
 }

/*------------------------------------------------------
                     End of Button Class
------------------------------------------------------*/

/*------------------------------------------------------
                     Window Class
------------------------------------------------------*/

class Window
{

 private:

 int Left,Top,Width,Height;
 char Caption[50];
 Button *CloseBtn;
 public:

 Window(int left, int top, int width, int height, char caption[]);
 void JCLogo();
 void Draw();
 void EnableClickHandler();
};


 Window::Window(int left, int top, int width, int height, char caption[])
 {
  Left = left;
  Top = top;
  Width = width;
  Height = height;
  strcpy(Caption,caption);
 }
 void Window::JCLogo()
 {
	std::cerr << "[ERROR] >>> Entering Window::JCLogo()" << std::endl;
    /*********** Logo ************/

  setcolor(3);
  setfillstyle(SOLID_FILL,3);
  fillellipse(Left+(BORDERWIDTH)+TITLEBARHEIGHT/2,Top+TITLEBARHEIGHT/2,TITLEBARHEIGHT/2-1,TITLEBARHEIGHT/2-1);
  setcolor(15);
  setfillstyle(SOLID_FILL,15);
  circle(Left+(BORDERWIDTH)+TITLEBARHEIGHT/2,Top+TITLEBARHEIGHT/2,TITLEBARHEIGHT/2-3);
  settextstyle(SMALL_FONT,0,0);
  outtextxy(Left+6,Top+4,"JC");
  settextstyle(0,0,0);
std::cerr << "[WARN] <<< Exiting Window::JCLogo()" << std::endl;
 }
 void Window::Draw()
 {
std::cerr << "[ERROR] >>> Entering Window::Draw()" << std::endl;
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(Left,Top,Left+Width,Top+Height);

  setcolor(WHITE);
  line(Left,Top,Left+Width,Top);
  line(Left,Top,Left,Top+Height);

  setcolor(BLACK);
  line(Left,Top+Height,Left+Width,Top+Height);
  line(Left+Width,Top,Left+Width,Top+Height);

  setfillstyle(SOLID_FILL,BLUE);
  bar(Left+BORDERWIDTH,Top+BORDERWIDTH,
  Left+Width-(BORDERWIDTH*2),Top+TITLEBARHEIGHT);

  setcolor(WHITE);
  settextjustify(LEFT_TEXT,TOP_TEXT);
  outtextxy(Left+(BORDERWIDTH*2)+TITLEBARHEIGHT+2,Top+(BORDERWIDTH*2)+(TITLEBARHEIGHT/2)-(textheight(Caption)/2),Caption);
  CloseBtn = new Button(Left+Width-TITLEBARHEIGHT-1, Top+2,TITLEBARHEIGHT-2, TITLEBARHEIGHT-2, "X", 9809);
std::cerr << "[ERROR] Window::Draw(): CloseBtn → " << CloseBtn << std::endl;
  CloseBtn->Draw();

  JCLogo();

std::cerr << "[WARN] <<< Exiting Window::Draw()" << std::endl;
 }
 void Window::EnableClickHandler()
 {
std::cerr << "[ERROR] >>> Entering Window::EnableClickHandler()" << std::endl;
  CloseBtn->EnableClickHandler();
  if (ButtonId == 9809)
  exit(0);

std::cerr << "[WARN] <<< Exiting Window::EnableClickHandler()" << std::endl;
 }


/*------------------------------------------------------
       End of Window Class
------------------------------------------------------*/


/*------------------------------------------------------
       Main Function
------------------------------------------------------*/

void main()
{
std::cerr << "[ERROR] >>> Entering main()" << std::endl;
 int gd=DETECT,gm,ch,errorcode;
 double opr1 = 0,opr2 = 0,result = 0,d=0;
std::cerr << "[ERROR] main(): opr1 → " << opr1 << std::endl;
std::cerr << "[ERROR] main(): d → " << d << std::endl;
std::cerr << "[ERROR] main(): opr2 → " << opr2 << std::endl;
std::cerr << "[ERROR] main(): result → " << result << std::endl;
 int Operation=0;
 double temp;
 char *chr,str[30];
 int len;
 int x = 160,y = 130;
std::cerr << "[ERROR] main(): x → " << x << std::endl;
std::cerr << "[ERROR] main(): h → " << h << std::endl;
 int w = 50, h = 40;
 char deci[]={"."};

 char btn[][3]={"AC","/","X","<-","7","8","9","-",
 "4","5","6","+","1","2","3","=","0",".","+/-"};


  // initialize graphics and local variables
  initgraph(&gd,&gm,"c://turboc3//bgi");

  // read result of initialization
  errorcode = graphresult();
std::cerr << "[ERROR] main(): errorcode → " << errorcode << std::endl;
std::cerr << "[DEBUG] main(): errorcode → " << errorcode << std::endl;

  if (errorcode != grOk)// an error occurred
  {
   cout<<"Graphics error :: "<<grapherrormsg(errorcode);
   cout <<"\n press any key to halt: ";
   getch();
   exit(1);// terminate with an error code
  }

 mouse.InstallMouse();

 /* Drawing a Calculator Window */

 Window *pWindow = new Window(150,50,265,340,"Calculator");
 pWindow->Draw();

 /* Drawing Textbox */

 TextBox *pTextBox = new TextBox(160,80,243,30,"",RIGHT_TEXT);
 pTextBox->Draw();

 /* Drawing Buttons */

 Button *pButton[19];
 for (int i = 0;i<19;i++)
 {
    if(i == 15)
  h = 90;
    else
  h=40;
    pButton[i] = new Button(x,y,w,h,btn[i],i+1);
    pButton[i]->Draw();
    x = x+65;
    if(i == 3 || i == 7 || i==11 || i== 15)
    {
      y = y+50;
      x = 160;
    }
 }

 while(1){

   mouse.ShowMouse(); // To show mouse
   mouse.GetMouseStatus(); // To get position of mouse

  // Enabling click event on close button in window
  pWindow->EnableClickHandler();
  // Enabling click event on buttons
  for(int k = 0;k<19;k++)
  pButton[k]->EnableClickHandler();


  switch(ButtonId)
  {
    case 1: //AC
      pTextBox->Clear();
      d = 0;
      opr1=0;
      opr2=0;
	std::cerr << "[DEBUG] main(): opr2 → " << opr2 << std::endl;
      result = 0;
      Operation = 0;
	std::cerr << "[ERROR] main(): Operation → " << Operation << std::endl;

    break;
    case 2: //Divide
      opr1 = atof(pTextBox->GetText());
      pTextBox->Clear();
      Operation = DIVIDE;
      d = 0;

    break;
    case 3: //Multiply
      opr1 = atof(pTextBox->GetText());
      pTextBox->Clear();
      Operation = MULTIPLY;
      d=0;

    break;
    case 4: //Backspace
      strcpy(chr,pTextBox->GetText());
      len=strlen(chr);
	std::cerr << "[DEBUG] main(): len → " << len << std::endl;
      if(chr[len-2] == deci[0])
      {
		std::cerr << "[ERROR] main(): len → " << len << std::endl;
         chr[len-1]=0;
         chr[len-2]=0;
      }
      else
         chr[len-1] = 0;
      pTextBox->Clear();
      pTextBox->SetText(chr);

    break;
    case 5: //7
      pTextBox->SetText("7");

    break;
    case 6: //8
      pTextBox->SetText("8");

    break;
    case 7: //9
      pTextBox->SetText("9");

    break;
    case 8: // Subtraction
      opr1 = atoi(pTextBox->GetText());
      pTextBox->Clear();
      Operation = SUBTRACT;
      d=0;

    break;
    case 9: //4
      pTextBox->SetText("4");

    break;
    case 10: //5
      pTextBox->SetText("5");

    break;
    case 11: //6
      pTextBox->SetText("6");

    break;
    case 12: //Addition
      opr1 = atof(pTextBox->GetText());
      pTextBox->Clear();
      Operation = ADD;
      d=0;

    break;
    case 13: //1
      pTextBox->SetText("1");

    break;
    case 14: //2
      pTextBox->SetText("2");

    break;
    case 15: //3
      pTextBox->SetText("3");

    break;
    case 16: // Equal(=)
      opr2 = atof(pTextBox->GetText());

      switch(Operation)
      {
   case ADD:
   result = opr1+opr2;
   break;
   case SUBTRACT:
   result = opr1-opr2;
   break;
   case MULTIPLY:
   result = opr1*opr2;
   break;
   case DIVIDE:
   result = opr1/opr2;
   break;
      }

      pTextBox->Clear();
      pTextBox->SetText(gcvt(result,10,str));
      opr1=0;
      opr2=0;
      result = 0;
      Operation=0;

    break;
    case 17: //0
      pTextBox->SetText("0");

    break;
    case 18: // Decimal(.)
      if(d == 0)
      {
       d = 1;
       pTextBox->SetText(".");
      }

    break;
    case 19: //Plus & Minus (+/-)



   temp = atof(pTextBox->GetText());
   temp = temp* -1;
   pTextBox->Clear();
   pTextBox->SetText(gcvt(temp,10,str));


    break;
  }


       while(kbhit()){
  ch = getch();
std::cerr << "[ERROR] main(): ch → " << ch << std::endl;
  if (ch == 27)  //ESC key pressed
  exit(0);
    } }

std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}


