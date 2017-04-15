#include "GameH.H"
#include <dos.h>

int Mouse::X =0;
int Mouse::Y =0;
int Mouse::Button =0;


int hande_mouse[32]=
{

  0XFEFF,//0000110000000000
  0XFAFF,//0000110000000000
  0XFABF,//0000110000000000
  0XFABF,//0000110000000000
  0XFAAF,//0000110000000000
  0XFA2F,//0000111111111000
  0XF80F,//0111111111111000
  0XE80F,//0111111111111000
  0XE80F,//0111111111111000
  0xE00F,//0111111111111000
  0XF80F,//0111111111111000
  0XF81F,//0111111111111000
  0XFC3F,//0111111111111000
  0XFFFF,
  0XFFFF,
  0XFFFF,

  0X0100,//0000110000000000
  0X0500,//0000110000000000
  0X0540,//0000110000000000
  0X0540,//0000110000000000
  0X0550,//0000110000000000
  0X05d0,//0000111111111000
  0X07F0,//0111111111111000
  0X17F0,//0111111111111000
  0X17F0,//0111111111111000
  0x1ff0,//0111111111111000
  0X07F0,//0111111111111000
  0X07e0,//0111111111111000
  0X03c0,//0111111111111000
  0X0000,//0000111111111000
  0X0000,//0000000000000000
  0X0000,//0000000000000000
};

Mouse::Mouse()
{
  asm{
       mov ax,0001h
       int 33h
     }
}

void Mouse::Init()
{
   asm{
       mov ax,0000h
       int 33h
       mov ax,0001h
       int 33h
     }
}

Mouse::~Mouse()
{

}
void Mouse::State()
{
  int x,y,button;
  asm{
       mov ax,0003h
       int 33h
       mov word ptr x,cx
       mov word ptr y,dx
       mov word ptr button,bx
     }
   X=x; Y=y; Button=button;
}

void Mouse::Hide()
{
  asm{
       mov ax,0002h
       int 33h
     }
}
void Mouse::getInformation(int &x,int &y,int &button)
{
  State();
  x=X; y=Y; button=Button;
}
void Mouse::setXY(const int x,const int y)
{
  asm{
       mov ax,0004h
       mov cx,x
       mov dx,y
       int 33h
     }
}

void Mouse::Show()
{
  asm{
       mov ax,0001h
       int 33h
      }
}
void Mouse::Hande()
{
  int far *Ptr;
  int segm,depl;
  Ptr=(int far*)hande_mouse;
  segm=FP_SEG(Ptr);
  depl=FP_OFF(Ptr);

  asm{
       push es
       mov  bx,0
       mov  cx,0
       mov  dx,depl
       mov  ax,segm
       mov  es,ax
       mov  ax,0009h
       int 33h
       pop es
     }
}
//--------------------------------------------------------------------//
