#ifndef __MOVEOBJ_H
#define __MOVEOBJ_H

#include "..\glass.h"

class MOVEOBJ {
public:
static CGLASS * glass;
	BOX bx;
	double
		x,y,		//������� ���������� �������
		Acceleratx,	//��������� �� ��� X
		Acceleraty, //��������� �� ��� Y
		Speedx,		//�������� �������� �� ��� X
		Speedy,		//�������� �������� �� ��� X
		Speed;		//������ ������� ��������

	int	Status;		//��������� �������
public:
	void Animate();				//YES �������� �������
	     MOVEOBJ();				//NO ����������� move-�������
	    ~MOVEOBJ();                     	//YES, NO ����������
void Show();				//NO ���������� ������

};


#endif