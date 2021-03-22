#ifndef __RECTABLE_H
#define __RECTABLE_H

class CGLASS;
//класс RECTABLE - таблица результатов
class RECTABLE
{
public:
		CGLASS *glass;
	enum {
		MAX_RECORD=10,		//максимальное число рекордов
		NAME_MAXLEN=14		//максимальная длина имени
	};


//хранит информацию о рекордсменах
struct RECORD
{
	char name[ NAME_MAXLEN] ;		//имя
	DWORD score;	        //число очков
	DWORD lines;			//число линий
	DWORD second;			//время игры(cекунд)
};

RECORD record[MAX_RECORD+1];		//таблица рекордов

public:
	int x,y;	//координаты показа таблицы
	int GetFontWidth();
	int GetWidth();
	RECTABLE();	//конструктор
	~RECTABLE();	//дестркутор
	void Save();		//записать таблицу на диск
	void Load();		//считать таблицу с диска

	//попытка поместить новый рекорд в таблицу
	void PutNewRecord(int newscore, int lines, int second, char * name);
	void Show(HDC hdc,int score, char *name, int lines, int second,COLORREF);		//показать таблицу на экране

	//получить максимальный рекорд из таблицы
	int GetMaxScore();
	int GetMinScore();
};

#endif