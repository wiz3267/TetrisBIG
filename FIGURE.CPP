// FIGURE.cpp: implementation of the CFIGURE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TetrisMFC.h"
#include "FIGURE.h"
#include "GLASS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIGURE::CFIGURE()
{
	x=0;
	y=0;
	
	dy=0;
	
	hei=2;
	len=2;

	bxData=new bool[2*2];

	bxData[0]=0;
	bxData[1]=0;
	bxData[2]=0;
	bxData[3]=0;


	NeedMoveDown=false;
	NeedMoveLeft=false;
	NeedMoveRight=false;
	NeedMoveLeftRightCounter=0;

}

CGLASS * CFIGURE::glass;

CFIGURE::~CFIGURE()
{
	//delete bxData;
}

//конструирование фигуры
//len ширина фигуры
//hei высота фигуры
//bxData  данные фигуры
// 001
// 111
CFIGURE::CFIGURE(int l, int h, bool *bxd)
{
	len=l;
	hei=h;
	bxData=new bool[len*hei];
	CopyMemory(bxData, bxd, len*hei);

	NeedMoveDown=false;
	NeedMoveLeft=false;
	NeedMoveRight=false;
	NeedMoveLeftRightCounter=0;

}

//поворачивает фигуру
void CFIGURE::Rotate(bool sign)
{
	bool *newbox=new bool[len*hei];
	
    for(int y=0; y<hei; y++)
	for(int x=0; x<len; x++)
		{
			newbox[y*len+(len-x-1)]=bxData[x*len+y];
		}

	int h=hei;
	hei=len;
	len=h;

	RtlCopyMemory(bxData,newbox,len*hei);
	
	delete newbox;
}



bool CFIGURE::Show()
{
	return Show(x,y);
}

//показывает фигуру в координатах x,y стакана
// true - OK
// false - либо фигура наложилась на другие
// либо за пределами экрана
bool CFIGURE::Show(int x, int y)
{
	bool err=true;
	for(int x1=0; x1<len; x1++)
		for(int y1=0; y1<hei; y1++)
		{
			BOX bx1;
			
			if (bxData[y1*len+x1]) bx1=bx;

			if (bx1)
			{
				bx1.dy=dy;
				if (!glass->Write(x+x1, y+y1,bx1)) err=false;
			}
		}

	return err;
}

//вырезаем фигуру
bool CFIGURE::Cut(int x, int y)
{
	for(int x1=0; x1<len; x1++)
		for(int y1=0; y1<hei; y1++)
		{
			if (bxData[y1*len+x1]) glass->Write(x+x1,y+y1,BOX());
			//if (!glass->Write(x+x1, y+y1,bx)) return false;
		}

	return true;
}

//можно ли нарисовать фигуру в заданных
//координатах
bool CFIGURE::Check(int x, int y)
{
	for(int x1=0; x1<len; x1++)
		for(int y1=0; y1<hei; y1++)
		{
			//если есть данные в этом месте
			if (bxData[y1*len+x1]) 
			{
				//если в стакане можно считать
				if (glass->Read(x+x1,y+y1).color != 0)
					return false;
			}
		}
	return true;
}

//отрисовывает фигуру в стакане в пиксельных координатах
void CFIGURE::Draw(int x, int y)
{
	for(int x1=0; x1<len; x1++)
		for(int y1=0; y1<hei; y1++)
		{
			BOX bx1=bxData[y1*len+x1];

			if (bx1)
			{
				bx1.dy=dy;
				glass->ShowAbsolute(x+x1*glass->GetOneLen(), y+y1*glass->GetOneLen(),bx1);
			}
		}
}

//отрисовывает фигуру в стакане в пиксельных координатах
//фигура любого размера
void CFIGURE::DrawAnySize(int x, int y, int size)
{

	int oldsize=glass->GetOneLen();
	glass->ONE_LEN=size;
	for(int x1=0; x1<len; x1++)
		for(int y1=0; y1<hei; y1++)
		{
			BOX bx1=bxData[y1*len+x1];

			if (bx1)
			{
				bx1.dy=dy;
				glass->ShowAbsoluteInDC(x+x1*size, y+y1*size,bx1,glass->memDC);
			}
		}

	glass->ONE_LEN=oldsize;
}


//конструктор копирования
CFIGURE::CFIGURE(CFIGURE &fig)
{
	len=fig.len;
	hei=fig.hei;
	dy=fig.dy;
	bx=fig.bx;
	glass=fig.glass;

	bxData=new bool[fig.len*fig.hei];
	CopyMemory(bxData, fig.bxData, fig.len*fig.hei);

	NeedMoveDown=fig.NeedMoveDown;
	NeedMoveLeft=fig.NeedMoveLeft;
	NeedMoveRight=fig.NeedMoveRight;
	NeedMoveLeftRightCounter=fig.NeedMoveLeftRightCounter;

	x=fig.x;
	y=fig.y;

}
