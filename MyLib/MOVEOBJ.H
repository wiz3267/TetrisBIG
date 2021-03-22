#ifndef __MOVEOBJ_H
#define __MOVEOBJ_H

#include "..\glass.h"

class MOVEOBJ {
public:
static CGLASS * glass;
	BOX bx;
	double
		x,y,		//текущие координаты обьекта
		Acceleratx,	//ускорение по оси X
		Acceleraty, //ускорение по оси Y
		Speedx,		//проекции скорости на оси X
		Speedy,		//проекции скорости на оси X
		Speed;		//модуль вектора скорости

	int	Status;		//состояние обьекта
public:
	void Animate();				//YES анимация обектов
	     MOVEOBJ();				//NO конструктор move-объекта
	    ~MOVEOBJ();                     	//YES, NO деструктор
void Show();				//NO показываем объект

};


#endif