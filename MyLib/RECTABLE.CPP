#include <stdafx.h>
#include <afxwin.h>

#include "rectable.h"
#include "..\glass.h"
#include <conio.h>
#include <stdio.h>
#include <fstream.h>
#include <mmsystem.h>
#include <math.h>

//***********************************************************************
//********* RECTABLE.CPP - программы для работы с таблицей рекордов *****


static void DrawGradientString(HDC hdc,int x, int y, CString str, COLORREF clr, int step, int hei)
{
/*	CSize size=pDC->GetTextExtent(str);

	int r=GetRValue(clr), g=GetGValue(clr), b=GetBValue(clr);
	for(int i=0; i<hei; i++)
	{
		pDC->FillSolidRect(x, y +i, size.cx, 1,RGB(r,g,b));
		r-=step;
		g-=step;
		b-=step;
		if (r<0) r=0;
		if (g<0) g=0;
		if (b<0) b=0;
	}
*/

//	SetBkMode(hdc,TRANSPARENT);
	SetTextColor(hdc,clr);
	TextOut(hdc, x,y, str,strlen(str));

}


//показать таблицу на экране
void RECTABLE::Show(HDC hdc,int newscore, char *name, int lines, int second,COLORREF curColor)
{
	Load();
	LOGFONT lf={0};

	int size=GetFontWidth();
	lf.lfWidth=size;
	lf.lfHeight=size*2;
	lf.lfPitchAndFamily=FF_MODERN | FIXED_PITCH;


/*	lf.lfHeight=glass->GetOneLen()*glass->Hei / MAX_RECORD/2;
	lf.lfWidth=long(lf.lfHeight*0.55);
	lf.lfCharSet=RUSSIAN_CHARSET;
	lf.lfPitchAndFamily=FIXED_PITCH;
*/

	HFONT hfont=CreateFontIndirect(&lf);
	HFONT oldfont=(HFONT)SelectObject(hdc, hfont);

	//CBrush br(RGB(0,0,127));
	//glass->showDC->SelectObject(br);
	//glass->showDC->SetBkMode(TRANSPARENT);

	/*int x=glass->GetOneLen()*glass->Len, y=0,
	len=glass->GetOneLen()*20,
	hei=glass->GetOneLen()*glass->Hei/2;
	*/

	int len=glass->GetOneLen()*glass->Len,
	hei=glass->GetOneLen()*glass->Hei/2;

	COLORREF clr;
	bool alreadyShow=false;
	static double RBright;
	RBright+=0.1;

	for (int i=0,j=0; j<MAX_RECORD; i++,j++)
	{

			int sc=record[i].score;
			char *nam=record[i].name;
			int lin=record[i].lines;
			int sec=record[i].second;
			if (newscore > sc &&
				!alreadyShow)
			{

				alreadyShow=true;
				sc=newscore;
				nam=name;
				lin=lines;
				sec=second;

				clr=RGB(180+75*sin(RBright),0,0);
				SetBkMode(hdc,TRANSPARENT);
				i--;
			}
			else
			{
					//glass->showDC->Rectangle(x,j*lf.lfHeight, x+len,(j+1)*lf.lfHeight);
				clr=RGB(255,255,255);
				SetBkMode(hdc,TRANSPARENT);
			}
			
			CString m;
			m.Format("%2i. %-14s %06i %04i %02i:%02i", j+1, nam,
				sc, lin, sec/60, sec %60 );
			DrawGradientString(hdc,x, y+j*lf.lfHeight, m, clr, 10,lf.lfHeight);

			
			//glass->showDC->TextOut(x, j*lf.lfHeight, m);
		}
	SelectObject(hdc,oldfont);
	DeleteObject(hfont);
}

//считать информацию с диска
void RECTABLE::Load()
{
	CFile file;

	
	char *name[]={ "OLEG", "EVGENY", 
		"ALEX", "KATY",
	"ADMIN", "SERGEY",
	"MOKOV"};

	//пытаемся открыть файл с таблицей

	//если файла таблицы нет, обнуляем то, что есть
	if (!file.Open("records.dat", file.modeRead))
	{
		for(int i=0; i<MAX_RECORD; i++)
		{
			strcpy(record[i].name, name[rand()%7]);
			record[i].score=(9-i+1)*200;
			record[i].lines=record[i].score/150;
			record[i].second=23*(MAX_RECORD+2-i);

		}
		//сохраняем ее на диске
		Save();
		return;
	}
	//иначе читаем таблицу в память
	else
	{
		//int k=sizeof(RECORD)*MAX_RECORD;
		file.Read(record, sizeof(record) );
		//закрываем файл
		file.Close();
	}
}

//записать таблицу на диск
void RECTABLE::Save()
{
	ofstream ofl;

	//пытаемся открыть файл с таблицей
	ofl.open("records.dat", ios::binary);

	//если таблица затерта, обнуляем то, что есть
	if (!ofl)
	{
//		Debug("RECTABLE::Save - can't save table to disk");
		return;
	}
	//иначе пишем таблицу на диск
	else
	{
		ofl.write( (char*) record, 
			sizeof(record));
		//закрываем файл
		ofl.close();
	}

}

//конструктор
RECTABLE::RECTABLE()
{
	//считываем таблицу с диска
	Load();
}

//деструктор
RECTABLE::~RECTABLE()
{
	//сохраняем информация на диске
	Save();
}


int RECTABLE::GetMaxScore()
{
	return record[0].score;
}

int RECTABLE::GetMinScore()
{
	return record[MAX_RECORD-1].score;
}


//============== попытаться положить новые очки =============
void RECTABLE::PutNewRecord(int newscore, int lines, int second, char * name)
{
	//узнаем, вошел ли рекорд в таблицу
	if ((int)newscore>(int)record[MAX_RECORD-1].score)
	{

		record[MAX_RECORD].score=newscore;
		record[MAX_RECORD].lines=lines;
		strcpy(record[MAX_RECORD].name,name);
		record[MAX_RECORD].second=second;
//		scr.setbkcolor(0);
//		scr.update();
		int newnum;

		//определим номер, под каким рекорд вошел в таблицу
		for (int i=0; i<MAX_RECORD; i++)
		{
			if (int(record[i].score)<int(newscore))
			{
				newnum=i;
				break;
			}
		}

		//сортировка массива по возрастанию
		for (i=0; i<=MAX_RECORD; i++)
		{
			for (int k=0; k<=MAX_RECORD-1; k++)
			{
				if (record[k].score<record[k+1].score)
				{
					RECORD tmp=record[k];
					record[k]=record[k+1];
					record[k+1]=tmp;
				}
			}
		}

		//записываем рекорд
		Save();

	}
}


int RECTABLE::GetWidth()
{
//"%2i. %-14s %06i %04i %02i:%02i"
		return GetFontWidth()*(2+2+14+1+6+1+4+1+2+1+2);
}

int RECTABLE::GetFontWidth()
{
	return int(glass->GetOneLen()/2*1.2);
}
