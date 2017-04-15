#include "GameH.h"

Stack::Stack()
{
   Nbr_Element=0; Next=0;
}
Stack::~Stack()
{
 if(Next) delete Next;
 Next=0; Nbr_Element=0;
}
void Stack::Push(int x1,int x2,int x3,int x4,int kind,int kind_c)
{
      if(Nbr_Element==0)
       {
	 X1=x1; X2=x2; X3=x3; X4=x4;  Kind=kind; Kind_c=kind_c;
       }
      else
       {
	 if(!Next) Next=new Stack;
	 Next->Push(x1,x2,x3,x4,kind,kind_c);
       }
      Nbr_Element++;
}

int Stack::Pop(int &x1,int &x2,int &x3,int &x4,int &kind,int &kind_c)
{
      if(!Nbr_Element) return NO;
      if(!Next)
       {
	 x1=X1; x2=X2; x3=X3; x4=X4;  kind=Kind; kind_c=Kind_c;
       }
      else
       {
	 Next->Pop(x1,x2,x3,x4,kind,kind_c);
       }
      Nbr_Element--;
      if(Nbr_Element==1){delete Next; Next=0;}
      return OK;
}
