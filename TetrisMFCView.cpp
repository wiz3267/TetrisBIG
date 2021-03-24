//сделать игру вдвоем (троем и более) по интернету

 //идея 1 - создать BitMap, содержащий все изображения кубиков
//и тогда скорость прорисовки будет значительно увеличена
//идея 2 - картинка будет занимать весь экран

//кнопка сброса одной линии

//при нажатии паузы чтобы надпись отображалась

/*новые фигуры

*
*
*
*
*

*
*
***

*
***** 

*/




#include "stdafx.h"
#include "TetrisMFC.h"

#include "TetrisMFCDoc.h"
#include "TetrisMFCView.h"


#include "dialoginputname.h"
#include <mmsystem.h>
#include "mylib\moveobj.h"
#include "figure.h"
#include "settingdialog2.h"
#include <atlbase.h>
#include "loading.h"

#define TIMER_DEVIDE 25

//#define SHOW_LOADING

CFIGURE fig[2];
bool NeedMoveDown=false;
bool NeedMoveLeft=false;
bool NeedMoveRight=false;

int Ycntr=0;
int NeedMoveLeftRightCounter=0;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TIMER 1
#define ID_TIMER_RESTART_MUSIC 2
/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCView

IMPLEMENT_DYNCREATE(CTetrisMFCView, CView)

BEGIN_MESSAGE_MAP(CTetrisMFCView, CView)
	//{{AFX_MSG_MAP(CTetrisMFCView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	ON_WM_DESTROY()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_SHOW_ONLY_GLASS, OnMenuShowOnlyGlass)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int tetris_view=0;	//номер текущего тетриса

void PlaySound(char *name)
{
	sndPlaySound(name,SND_ASYNC);
}

HANDLE hMailSlotServer;

//стандартные фигурки тетриса
	bool buf0[]={
		0,0,1,
		1,1,1,
		0,0,0
	};
	
	bool buf1[]={
		0,1,0,
		1,1,1,
		0,0,0
	};
	bool buf2[]={
		1,1,
		1,1
	};
	bool buf3[]={
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0
	};

	bool buf4[]={
		1,1,0,
		0,1,1,
		0,0,0
	};

//далее идут нестандартные фигуры
	bool buf5[]={
		1,1,1,
		0,1,0,
		0,1,0
	};


	
	bool buf6[]={1};



	bool buf7[]={
		1,1,1,1,1,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};

	bool buf8[]={
		1,1,1,
		1,0,0,
		1,0,0
	};


	bool buf9[]={
		1,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0

	};

	bool buf10[]={
		1,0,1,
		1,1,1,
		0,0,0
	};

	bool buf11[]={
		1,0,0,1,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0
	};

	bool buf12[]={
		1,0,0,1,
		1,0,0,1,
		1,1,1,1,
		0,0,0,0
	};

	bool buf13[]={
		1,0,1,
		1,0,1,
		1,1,1,
	};





	bool buf_death[]={
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1
	};

int nPlayer;

CFIGURE

 //стандартные фигурки тетриса
 fig0(3,3, buf0),
 fig1(3,3, buf1),
 fig2(2,2, buf2),
 fig3(4,4, buf3),
 fig4(3,3, buf4),
 
 //дополнительные фигурки
 fig5(3,3, buf5),
 fig7(5,5, buf7),
 fig8(3,3, buf8),
 fig9(4,4, buf9),
 fig10(3,3, buf10),
 fig11(4,4, buf11),
 fig12(4,4, buf12),
 fig13(3,3, buf13),

 

fig_small(1,1, buf6),
fig_death(4,4, buf_death);


int Pause=false;

int ShowNextFigureFlag=1;


int rand(int n)
{
	return rand()%n;
}
/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCView construction/destruction

CTetrisMFCView::CTetrisMFCView() //: fig(fig0)
{
	fig[0]=fig0;
	// TODO: add construction code here

	srand(GetTickCount());

	//!!!НАСТРОЙКИ!!!
	
	//ЗДЕСЬ ЗАДАЕТСЯ РАЗМЕР СТАКАНА
	glass= new CGLASS(80,50,NULL);


	fig[0].glass=glass;
	fig[0].bx=RGB(128+rand(127),128+rand(127),128+rand(127));


	rectable.glass=glass;
	
}

CTetrisMFCView::~CTetrisMFCView()
{
}

BOOL CTetrisMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCView drawing

void CTetrisMFCView::OnDraw(CDC* pDC)
{
	CTetrisMFCDoc* pDoc = GetDocument();
	pDoc->_glass_=glass;
	pDoc->rectab=&rectable;
	ASSERT_VALID(pDoc);

	glass->showDC=pDC;
	//rectable.Show(glass->Score, glass->Name.GetBuffer(0), glass->Lines, RGB(255,0,0));
	glass->Show();

	//рисуем текст паузу
	//Zorxor
	if (Pause)
	{
		//mciSendString("pause snd",NULL,0,NULL);

		LOGFONT lf={0};
		lf.lfHeight=60;
		lf.lfWidth=lf.lfHeight/2;
		CFont font;
		font.CreateFontIndirect(&lf);
		CFont * oldf=pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255,255,255));
		
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText("Pause...",
		//CRect(0, glass->GetOneLen(), glass->GetPixelWidth(),
		CRect(0, 100, glass->GetPixelWidth(),

		glass->GetPixelHeight()),1);
		pDC->SelectObject(oldf);
	}

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCView diagnostics

#ifdef _DEBUG
void CTetrisMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisMFCDoc* CTetrisMFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisMFCDoc)));
	return (CTetrisMFCDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCView message handlers

void CTetrisMFCView::OnTimer(UINT nIDEvent) 
{ 

	//MoveWindow(0,0,1024,768,0);
	//
	static int ccc=0;
	ccc++;
	if (ccc==1)
	{
		//MoveWindow(0,0,2048,2048,TRUE)
		
		OnChar('L', 0, 0);

	}
	//if ( (ccc%20)==5 )
	//{
	
	//}

	static bool noTimer=false;
	// TODO: Add your message handler code here and/or call default
//	if (TimerStop) return;

	if (nIDEvent==ID_TIMER_RESTART_MUSIC)
	{
		//mciSendString("stop snd",NULL,NULL,0);
		//mciSendString("play snd",NULL,NULL,0);
		//mciSendString("play music.mid",0,0,0);
		return;
	}

	if (noTimer) return;


	GetDocument()->SetTitle(CString("PLAYER-")+char(48+nPlayer));

	struct MailMessage
	{
					UINT message;
					WPARAM wParam;
					LPARAM lParam;
	};

	MailMessage mail;


	DWORD fact;
	ReadFile(hMailSlotServer, &mail, sizeof(mail),
		&fact, NULL);


	if (fact== sizeof(mail))
	{
		//AfxMessageBox("OK READ MAIL!");
		//снимаем паузу
		Pause=false;
		if (mail.message==WM_KEYUP)
				OnKeyUp(mail.wParam, mail.lParam);

		if (mail.message==WM_KEYDOWN)
				OnKeyDown(mail.wParam, mail.lParam);
	}
	
	{
		static int mmm=1;
		if(mmm<20 && mmm>0) 
		{
			mmm++;
         if (mmm==19) OnMenuShowOnlyGlass(),mmm=-1;

		}
	}

	//считаем время
	if (!Pause)
	{
		static float k=0;
		if (k++ > 1000/TIMER_DEVIDE) 
			glass->Second++, k=0;
	} else 	return;

	//вырезаем фигуру в старых координатах
	fig[0].Cut(fig[0].x,fig[0].y);
	

	fig[0].dy++;

	//перемещение влево-вправо
	if (NeedMoveLeft || NeedMoveRight)
	{
/////////////////////////////////////////////////////////
	if (NeedMoveLeftRightCounter++ >1)
	{
		NeedMoveLeftRightCounter=0;

		int step=0, stepy=0;

		if (NeedMoveLeft) step=-1;
		if (NeedMoveRight) step=+1;

		//NeedMoveDown && NeedMoveLeft) stepy=-2;

		fig[0].x+=step;
		//если удалось поставить
		int dy=0;

		if (fig[0].dy!=0) dy=1;
		
		if (fig[0].Check(fig[0].x,fig[0].y+dy)) 
		{
			//ставим фигуру
			if (fig[0].dy!=0)
				fig[0].Show(fig[0].x,fig[0].y);
			else 
				fig[0].Show(fig[0].x,fig[0].y-1);

			Invalidate(false);
			UpdateWindow();
			return;
	}
	//невозможно отобразить
	else {
		fig[0].x-=step;
		fig[0].y-=stepy;
		//
		//fig[0].Show(x,y);
	}
	}
/////////////////////////////////////////////////////////	
	}

	if (fig[0].dy>=glass->GetOneLen() || NeedMoveDown)
	{
		fig[0].y++;
		fig[0].dy=0;
	}


	if (settings.m_all_level==TRUE) glass->Speed= 1+glass->Score/2000;
	else glass->Speed= settings.m_level;


	//если более нижнее положение НЕ наложится на существующий массив
	if (fig[0].Check(fig[0].x,fig[0].y+1) == true) 
	{
		fig[0].Show(fig[0].x,fig[0].y);
	}
	
	//иначе фигура села
	else {


		fig[0].dy=0;
		fig[0].Show(fig[0].x,fig[0].y); 
		OnChar('S', 0, 0);	//записываем состояние
		//MessageBeep(1);

		//glass->Show();
		glass->showDC=GetDC();
		glass->Scroll(0);			//скорллим и уничтожаем линии

		ReleaseDC(glass->showDC);

		//Beep(600, 100);

		//!!НАСТРОЙКИ!!!
		/*int prob=rand()%100;
		
		if (prob>60)fig[0]=fig3;
		else if (prob>70) fig[0]=fig2;
		else if (prob>80)fig[0]=fig1; 
		else if (prob>85)fig[0]=fig5; 		
		
		//else if (prob>90)fig[0]=fig6; 
		else if (prob>91)fig[0]=fig7; 
		else if (prob>92)fig[0]=fig8; 
		else if (prob>93)fig[0]=fig9; 
		else if (prob>93)fig[0]=fig10; 

		else fig[0]=fig4;*/


		//!!НАСТРОЙКИ!!!
		
		//алгоритм генерации новой фигуры
		int prob=rand()%14;
		
		//стандартные фигуры
		if (prob==0)fig[0]=fig0;
		else if (prob==1) fig[0]=fig1;
		else if (prob==2)fig[0]=fig2; 
		else if (prob==3)fig[0]=fig3; 		
		else if (prob==4) fig[0]=fig4;
		

		//нестандартные
		else if (prob==7)fig[0]=fig7; 
		else if (prob==8)fig[0]=fig8; 
		else if (prob==9)fig[0]=fig9; 
		else if (prob==10)fig[0]=fig10; 
		else if (prob==11)fig[0]=fig11; 
		else if (prob==12)fig[0]=fig12; 
		else if (prob==13)fig[0]=fig13; 



		//случайно поворачиваем
		for(int n=0; n< rand(4); n++) fig[0].Rotate(true);

		if (rand(40)==39) {
			fig[0]=fig_small;
		}

		//x=glass->Len/2;
		

		//int a1=rand(2), a2=rand(2), a3=rand(2);
		//if (! (a1+a2+a3) ) a1=1;
		//fig[0].bx.color=RGB(a1*255,a2*255,a3*255);
		
		//Zorxor 
		int a1=rand()%255, a2=rand()%255, a3=rand()%255;
		fig[0].bx.color=RGB(a1,a2,a3);
		
		fig[0].bx.type=rand()%5;
	
		fig[0].y=5;

		//Beep(600, 100);
		
		//check game over
		
		

		if (!fig[0].Check(fig[0].x,fig[0].y)) 
		{
			//Игра не прерывается
			fig[0].y=5; fig[0].x=10;

			/*fig[0].Show(fig[0].x,fig[0].y);
			glass->Show();
			noTimer=true;
			//Sleep(500);		
			//sndPlaySound("EXORCISM.wav", SND_ASYNC);
			//game OVER
			Sleep(1000);		

			if (glass->Score > rectable.GetMinScore())
			{

			DialogInputName di;
			di.DoModal();

			glass->Name=di.m_InputName;

			UpdateData();
				rectable.PutNewRecord(
				(int)glass->Score,
				(int)glass->Lines, 
				(int)glass->Second, 
				di.m_InputName.GetBuffer(0));

			}

			glass->Clear();			
			//MessageBox("ИГРА ОКОНЧЕНА");
			//game over
			Invalidate(true);
			UpdateWindow();
			noTimer=false;
			*/
		}
		else fig[0].Show(fig[0].x,fig[0].y);

	
		
		NeedMoveDown=false;	
	}

	RECT rt;
	GetClientRect(&rt);

	if (glass->GetOneLen() - rt.bottom/glass->Hei
		!=0)
	{
	glass->SetOneLen(rt.bottom/glass->Hei);
	//InvalidateRect(NULL);
	//UpdateWindow();
	}

	//CDC * pDC=GetDC();
	//OnDraw(pDC);
	//ReleaseDC(pDC);
	InvalidateRect(NULL);
	UpdateWindow();


	//есть переход через 1000 ?
	static int oldScore=0;
	if (abs(oldScore-glass->Score) > 1000)
	{
		oldScore=glass->Score;
		glass->LoadNextBackground();
	}

	
	OnLButtonDown(0,CPoint(0,0));

	CView::OnTimer(nIDEvent);
}

int CTetrisMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	glass->Name="Предендент";
	SetTimer(ID_TIMER, TIMER_DEVIDE,NULL);
	SetTimer(ID_TIMER_RESTART_MUSIC, 10000,NULL);

	CString mailName="\\\\.\\mailslot\\ServerGame";
	hMailSlotServer=CreateMailslot(mailName+'1', 0,
		0, NULL);

	if (hMailSlotServer == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox("Create mail slot for two player");
		//mailName[strlen(mailName)-1]++;

		hMailSlotServer=CreateMailslot(mailName+'2', 0,
		0, NULL);
		if (hMailSlotServer == INVALID_HANDLE_VALUE)
		{
					AfxMessageBox("ERROR - Create mail slot for two player");
		}
		else
			nPlayer=2;


	}
	else nPlayer=1;

	InvalidateRect(NULL);
	UpdateWindow();
	return 0;
}




BOOL CTetrisMFCView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN)
		OnKeyDown(pMsg->wParam , pMsg->lParam);

	if (pMsg->message == WM_KEYUP)
		OnKeyUp(pMsg->wParam , pMsg->lParam);

	return CView::PreTranslateMessage(pMsg);
}



void CTetrisMFCView::OnKeyDown(WPARAM wp, LPARAM lp)
{
	// TODO: Add your message handler code here and/or call default

	//сброс линий
	if (wp==VK_F7)
	{
		//????? тест разлета фигур
		fig[0].Cut(fig[0].x,fig[0].y);

		glass->showDC=GetDC();
		glass->Scroll(1);			//скорллим и уничтожаем линии

		ReleaseDC(glass->showDC);


	}

	//отмена упавшей фигуры
	if (wp==VK_ESCAPE)
	{
	}

	if (wp==VK_F1)
	{
		char *help=
		"F1 help\n"
		"F2 clear\n"
		"F11 F12 change view\n"
		;

		MessageBox(help,"help");
	}

	if (wp==VK_F11)
	{
		tetris_view--;
		if (tetris_view<0) tetris_view=0;
		LoadTetris();
	}

	if (wp==VK_F12)
	{
		tetris_view++;
		if (tetris_view>9) tetris_view=9;
		LoadTetris();
	}


	if (wp==VK_F2)
	{
		//int n=MessageBox("Начать новую игру?","Стакан будет очищен!!!",MB_OKCANCEL);
		int n=MessageBox("Очистить поле?","Внимание!",MB_OKCANCEL);
		if (n==IDOK)
		{
			glass->Clear();
		}
		Pause=false;
		
	}


	if (wp==VK_SPACE) 
	{
		if (++glass->TypeBoxView>5)
		glass->TypeBoxView=0;
		
	}
	
	if (wp == VK_DOWN) NeedMoveDown=true;	
	
	int K=255/3;

	if (wp == VK_LEFT) {
		NeedMoveLeft=true;

		NeedMoveLeftRightCounter=K;
	}
	
	if (wp == VK_RIGHT) {
		NeedMoveRight=true;
		NeedMoveLeftRightCounter=K;
	}

	//??????????????
	if (wp == VK_PAUSE) Pause^=1;
	if (wp == 'P') Pause^=1;


	//выразем фигуру по старым координатам
	fig[0].Cut(fig[0].x,fig[0].y);

	int step=0, stepy=0;
//	if (wp==VK_LEFT) step=-1;
//	else if (wp==VK_RIGHT) step=+1;
	//else if (nChar==`'5') stepy=+1;
	if (wp==VK_UP) fig[0].Rotate(true);
	//else if (nChar=='9') fig[0].Rotate(false);
	else return;

	//
	fig[0].x+=step;
	fig[0].y+=stepy;

	if (fig[0].Check(fig[0].x,fig[0].y)) 
	{
		fig[0].Show(fig[0].x,fig[0].y);
		Invalidate(false);
		UpdateWindow();
	}
	else if (fig[0].Check(fig[0].x-1,fig[0].y))
	{
		fig[0].Show(fig[0].x-1,fig[0].y);
		fig[0].x--;

		Invalidate(false);
		UpdateWindow();
	}
	else if (fig[0].Check(fig[0].x+1,fig[0].y))
	{
		fig[0].Show(fig[0].x+1,fig[0].y);
		fig[0].x++;

		Invalidate(false);
		UpdateWindow();
	}

	//невозможно отобразить
	else {

		//обратно вращаем
		if (wp==VK_UP) 
		{
			fig[0].Rotate(true);
			fig[0].Rotate(true);
			fig[0].Rotate(true);
		}
		//if (nChar=='9') fig[0].Rotate(true);
		//возвращаем фигуру в прежнее положение
		fig[0].x-=step;
		fig[0].y-=stepy;
		fig[0].Show(fig[0].x,fig[0].y);

		//MOVEOBJ obj;
		
	}
		
	//MessageBeep(1);
}

void CTetrisMFCView::OnKeyUp(WPARAM wp, LPARAM lp)
{
	if (wp == VK_DOWN) NeedMoveDown=false;	
	if (wp == VK_LEFT) NeedMoveLeft=false;	
	if (wp == VK_RIGHT) NeedMoveRight=false;
}

void CTetrisMFCView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);

	Pause=true;
	Invalidate(false);
	UpdateWindow();
	// TODO: Add your message handler code here
	
}

void CTetrisMFCView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);


	//mciSendString("play snd",0,0,0);

	//Pause=false;
	// TODO: Add your message handler code here
	
}


void CTetrisMFCView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	if (nChar=='s' || nChar=='S' || nChar=='ы' || nChar=='Ы')
	{
		SaveTetris();

	}

	if (nChar=='l' || nChar=='L' || nChar=='д' || nChar=='Д')
	{
		LoadTetris();
	}


	/*
	if (nChar=='z')
	{
		const MAX=640;
		int mas[MAX]={0};
		for(int j=0; j<2000; j++)
		for(int i=0; i<MAX; i++)
		{
			mas[rand(640)]++;
			glass->showDC->SetPixel(i, mas[i], RGB(255,255,0));
		}
	}
	*/

//	if (nChar=='~') glass->Score+=1000;

	if (nChar == 'p') 
	{
		Pause^=1;
		Invalidate(false);
		UpdateWindow();

	}
	//if (nChar=='n') glass->LoadNextBackground();

	//if (nChar=='f')
	//	for(int i=0; i<glass->Len; i++)
	//		for(int j=0; j<glass->Hei; j++)
	//			glass->Write(i,j, (255<<8)*rand(2)+(255<<16)*rand(2)+255*rand(2));
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CTetrisMFCView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
//	MessageBox("DESTROY");	

}

void CTetrisMFCView::OnAppExit() 
{
	//??????
	//OnChar('s', 0,0);
}

void CTetrisMFCView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	//InvalidateRect(NULL, true);
	//UpdateWindow();
	
}

void CTetrisMFCView::OnMenuShowOnlyGlass() 
{
	// TODO: Add your command handler code here
//	CWnd *win=GetParent();

  CRect myRect, allwin;
  GetClientRect(&myRect);
  GetParent()->GetWindowRect(&allwin);

    //myRect.Width(), myRect.Height());

	GetParent()->
		MoveWindow(allwin.left, allwin.top, 
		glass->GetPixelWidth()+ allwin.Width ()-myRect.Width(),
		glass->GetPixelHeight()+ allwin.Height()-myRect.Height (),
		true);

	
}

void CTetrisMFCView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnMenuShowOnlyGlass();

	CView::OnLButtonDown(nFlags, point);
}

void CTetrisMFCView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRegKey reg;
	if (reg.Open(HKEY_CURRENT_USER,"Software\\TetrisMFC") != ERROR_SUCCESS)
	{
		settings.DoModal();
	}
	else
		settings.LoadSetting();

	//char ret[256];

	#ifdef SHOW_LOADING
		CLoading loading;
		loading.DoModal();
	#endif
}

void CTetrisMFCView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	settings.DoModal();

	KillTimer(ID_TIMER);
	SetTimer(ID_TIMER,41-4*settings.m_level,NULL);

	CView::OnRButtonDown(nFlags, point);
}

BOOL CTetrisMFCView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CTetrisMFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTetrisMFCView::SaveTetris()
{
	CFile file;
	CString k;
	k.Format("save%i.tet",tetris_view);
	file.Open(k,file.modeCreate|file.modeWrite);
	file.Write(glass->Data,glass->Hei*glass->Len*sizeof(BOX));
	file.Close();
}

void CTetrisMFCView::LoadTetris()
{
	CFile file;
	CString k;
	k.Format("save%i.tet",tetris_view);
	if (file.Open(k,file.modeRead))
	{
		file.Read(glass->Data,glass->Hei*glass->Len*sizeof(BOX));
		file.Close();
	}
	else glass->Clear();

}
