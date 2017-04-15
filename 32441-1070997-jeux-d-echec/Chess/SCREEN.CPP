#include "GameH.h"
#include <graphics.h>

#include <fcntl.h>
#include <io.h>




Screen::Screen()
{

}

Screen::~Screen()
{

}

void Screen::Mode(char mode)
{
  int gdriver = VGA, gmode=VGAHI, errorcode;
  initgraph(&gdriver, &gmode, "../../bgi");
  //setPalette();
}

void Screen::setImage(const int x,const int y,const int width,const int height,BitMap * bitmap)
{
  unsigned char c;
  unsigned int btm_offset,btm_segment;

  btm_offset=FP_OFF(bitmap->Image); btm_segment=FP_SEG(bitmap->Image);
  bitmap->X=width; bitmap->Y=height;
  c=0;
   for(int j=0;j<height;j++)
    for(int i=0;i<width;i++)
    {
      c=getpixel(x+i,y+j);
      i++;
      c=c+16*getpixel(x+i,y+j);
      pokeb(btm_segment,btm_offset,c); btm_offset++;
      c=0;
    }
}

void Screen::getImage(const int x,const int y,const int width,const int height,BitMap * bitmap)
{
  unsigned char c;
  unsigned int btm_offset,btm_segment;

  btm_offset=FP_OFF(bitmap->Image); btm_segment=FP_SEG(bitmap->Image);
  c=0;

   for(int j=0;j<height;j++)
    for(int i=0;i<width;i+=2)
    {
      c=peekb(btm_segment,btm_offset); btm_offset++;
      //putpixel
	 asm{
	   mov ah,0Ch
	   mov bx,0
	   mov dx,y
	   add dx,j
	   mov cx,x
	   add cx,i
	   mov al,c
	   and al,0Fh
	   int 10h
	   inc cx
	   shr byte ptr c,1
	   shr byte ptr c,1
	   shr byte ptr c,1
	   shr byte ptr c,1
	   mov al,c
	   int 10h
	 }
    }
}

void Screen::getImage_Transparent(const int x,const int y,const int width,const int height,BitMap * bitmap)
{
  unsigned char c;
  unsigned int btm_offset,btm_segment;

  btm_offset=FP_OFF(bitmap->Image); btm_segment=FP_SEG(bitmap->Image);
  c=0;
   for(int j=0;j<height;j++)
    for(int i=0;i<width;i+=2)
    {
      c=peekb(btm_segment,btm_offset); btm_offset++;
	  //putpixel
	 asm{
	   mov ah,0Ch
	   mov bx,0
	   mov dx,y
	   add dx,j
	   mov cx,x
	   add cx,i
	   mov al,c
	   and al,0Fh
	   cmp al,0Fh
	   je  Rien
	   int 10h
	 }
      Rien:
       asm{
	    inc cx
	    mov al,c
	    shr al,1
	    shr al,1
	    shr al,1
	    shr al,1
	    cmp al,0Fh
	    je Rien2
	    int 10h
	  }
     Rien2:
    }
}

void Screen::setPalette()
{
 unsigned char offs=0,r,g,b;
 for(r=0;r<16;r++)
  {
   //for(g=0;g<16;g++)
   // {
     for(b=0;b<16;b++)
      {
       outp(0x3c8,offs);
       outp(0x3c9,r*14);
       outp(0x3c9,0);
       outp(0x3c9,b*14);
       offs++;
      }
   //  }
   }
       outp(0x3c8,254);
       outp(0x3c9,63);
       outp(0x3c9,63);
       outp(0x3c9,63);

}

void Screen::Clear(unsigned char Color)
{
  setfillstyle(1,Color);
  bar(0,0,getmaxx(),getmaxy());
}

void Screen::Fill(const int x,const int y,const int width,const int height,unsigned char Color)
{
  setfillstyle(1,Color);
  bar(x,y,x+width,y+height);
}


int Screen::LoadBmpToRC(void far *rc,char *FN)
{
  int F;
  char *Entete;
  unsigned char c;
  char *bc;
  unsigned int x=0,nbr,k,XX,YY;

  if ((F = open(FN, O_BINARY)) != -1)
     {
      bc=(char *)malloc(516);
      Entete=(char *)malloc(0x76);
      read(F,Entete,0x76);
      XX=*(Entete+18);
      YY=*(Entete+22);

      x=(XX*YY/2)-1;
      while(!eof(F))
       {
	 nbr=read(F,bc,516);
	 for(k=0;k<nbr;k++)
	  {
	    pokeb(FP_SEG(rc),FP_OFF(rc)+x,*(bc+k));
	    x--;
	  }
       }
      close(F);
      free(bc);
      return 1;
     }
  printf("Fichier !");
  return 0;
}
