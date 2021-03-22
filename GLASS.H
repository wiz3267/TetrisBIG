// GLASS.h: interface for the CGLASS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLASS_H__B1B0B735_BCC1_406E_B7D5_D569200E3FAC__INCLUDED_)
#define AFX_GLASS_H__B1B0B735_BCC1_406E_B7D5_D569200E3FAC__INCLUDED_

/*#if _MSC_VER > 1000
#pragma onm_ce

#endif // _MSC_
*/

//#include "FIGURE.H"

struct BOX
{
	COLORREF color; //цвет кубика
	int type; //тип кубика
	int dy;//задает дополнительное смещение кубика вниз
	//int index;	//смещение кубика в таблице кубиков
	BOX(int c=0) { color=c; type=0;dy=0;}
	operator = (int k) { color=k;}
	operator int() { return color;}
};

//class CFIGURE;
//#include "figure.h"

class CGLASS  
{
public:
	int ONE_LEN;
	int GetPixelHeight();
	int GetPixelWidth();
	int Speed;
	void RestoreBitmap();
	void SaveBitmap();
	int Lines,
	TypeBoxView,
	Score;
	double Second;
	CString Name;
	void Scroll(bool force);
	void SetOneLen(int onelen);
	void LoadNextBackground();
	int ShowAbsolute(int x1, int y1, BOX bx);
	int ShowAbsoluteInDC(int x1, int y1, BOX bx,CDC &memDC);	void Show(int x, int y,BOX BX);//показать ЁЋ≈ћ≈Ќ“ BOX стакана 
	void Show(int x, int y);
	void ShowToScreen();
	int GetOneLen() {return ONE_LEN;}
	CGLASS(int l, int h,CDC *);
	void ReDraw();
	virtual ~CGLASS();

	int Len,Hei;	//ширина и высота стакана (в кубиках)

	BOX * Data;		//указатель на данные(стакан)

	int show_x,show_y;		//координаты стакана на экране(в пикселах)

	CDC * showDC;
	CDC	memDC, memDC_Save,
		cubicDC;

	void	Clear();                         	//очистка стакана
	void	Make(unsigned len, unsigned hei);	//сделать стакан
	BOX		Read(int j, int i);			//считать кубик
	void	Show();					//показать стакан
	void	ShowBackground(int i);			//показать задний план
	void	ShowBorder();				//показать рамку
	bool	Write(int j, int i, BOX bx);		//записать кубик

};

#endif // !defined(AFX_GLASS_H__B1B0B735_BCC1_406E_B7D5_D569200E3FAC__INCLUDED_)
