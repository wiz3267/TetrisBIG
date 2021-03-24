// FIGURE.h: interface for the CFIGURE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIGURE_H__7540F50F_C801_4734_AA15_BB37F1AAC8F4__INCLUDED_)
#define AFX_FIGURE_H__7540F50F_C801_4734_AA15_BB37F1AAC8F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glass.h"

class CFIGURE  
{
public:
	int len,hei;
	int x,y;		//координаты фигуры в стакане

	bool NeedMoveDown;//=false;
	bool NeedMoveLeft;//=false;
	bool NeedMoveRight;//=false;
	int NeedMoveLeftRightCounter;


	static CGLASS * glass;	//привязка к стакану
	bool Show();
	bool Show(int x, int y);
	bool * bxData;
	int dy;	//задает дополнительное смещение вниз
	BOX bx;

	void Draw(int x, int y);
	void DrawAnySize(int x, int y, int size);
	bool Check(int x,int y);
	void Rotate(bool sign);
	bool Cut(int x,int y);

	CFIGURE(CFIGURE&fig);
	CFIGURE(int len, int hei, bool * bxData);
	CFIGURE();
	virtual ~CFIGURE();

};

#endif // !defined(AFX_FIGURE_H__7540F50F_C801_4734_AA15_BB37F1AAC8F4__INCLUDED_)
