////////////////////////////////////////
// Copyright (C) ������ �������, 1997 //
////////////////////////////////////////

#include "stdafx.h"

#include "moveobj.h"

#include "..\glass.h"

CGLASS * MOVEOBJ::glass;

MOVEOBJ::~MOVEOBJ()
{
}


//����������� �������, ��������������� � �������� ���������
//(����������� �� ���������)
MOVEOBJ::MOVEOBJ()
{
}


//================= 'Show' - �������� ������ �� ������
void MOVEOBJ::Show()
{
	glass->ShowAbsolute( int(x), int(y), bx );
}

//==================�������� ��������=====================
void MOVEOBJ::Animate(void)
{
	x += Speedx;
	y += Speedy;
	Speedx += Acceleratx;
	Speedy += Acceleraty;
}






