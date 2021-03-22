////////////////////////////////////////
// Copyright (C) Лапшин Евгений, 1997 //
////////////////////////////////////////

#include "stdafx.h"

#include "moveobj.h"

#include "..\glass.h"

CGLASS * MOVEOBJ::glass;

MOVEOBJ::~MOVEOBJ()
{
}


//конструктор объекта, использующегося в качестве структуры
//(конструктор по умолчанию)
MOVEOBJ::MOVEOBJ()
{
}


//================= 'Show' - показать объект на экране
void MOVEOBJ::Show()
{
	glass->ShowAbsolute( int(x), int(y), bx );
}

//==================анимация объектов=====================
void MOVEOBJ::Animate(void)
{
	x += Speedx;
	y += Speedy;
	Speedx += Acceleratx;
	Speedy += Acceleraty;
}






