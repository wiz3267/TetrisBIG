


#include "stdafx.h"
#include "GLASS.h"
#include "mylib\moveobj.h"

#include <math.h>
#include <mmsystem.h>


#include "figure.h"
CBitmap bitmap;

int SoundEnable=FALSE;

void PlaySound(char *filename);

int rand(int);

bool buf[]=
{
	1,0,0,
	1,1,0,
	1,0,0
};

CFIGURE NextFigure(3,3,buf);

//CDC memBitmapDC;

//УТЕЧКА ПАМЯТИ!!!!!!!!
void ffLoadImagePixels(CDC &memDC, const char * filename, int &width, int &height,int
bpp)
{
 //MS LoadPic example...
 HANDLE hFile = CreateFile( filename, GENERIC_READ,
	 FILE_SHARE_READ, NULL,
OPEN_EXISTING,
  0, NULL);
 if(hFile==INVALID_HANDLE_VALUE) return;
 DWORD dwFileSize = GetFileSize( hFile, NULL );
 LPVOID pvData = NULL;
 HGLOBAL hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwFileSize );
 pvData = GlobalLock( hGlobal );
 DWORD dwBytesRead = 0;
 BOOL bRead = ReadFile( hFile, pvData, dwFileSize, &dwBytesRead, NULL );
 if(!bRead)
 {
  GlobalUnlock(hGlobal);
  GlobalFree(hGlobal);
  return;
 }
 GlobalUnlock(hGlobal);
 CloseHandle(hFile);

 LPSTREAM pstm = NULL;
 HRESULT hr = CreateStreamOnHGlobal( hGlobal, TRUE, &pstm );
if(FAILED(hr))
 {
 return;
 }
 IPicture *picture = NULL;

 hr = OleLoadPicture( pstm, dwFileSize, FALSE, IID_IPicture,
(void**)&picture );
 if(FAILED(hr))
 {
  pstm->Release();
  return;
 }
 pstm->Release();
 OLE_XSIZE_HIMETRIC olewidth;
 OLE_YSIZE_HIMETRIC oleheight;
 picture->get_Width( &olewidth );
 picture->get_Height( &oleheight );

 //HDC hPictureDC = CreateCompatibleDC( NULL );
 
// picture->SelectPicture( hPictureDC, NULL, NULL );
  picture->SelectPicture( memDC, NULL, NULL );

 picture->Release();

 //DeleteDC(hPictureDC);
 //return pixels;
// return hPictureDC;
}




void CGLASS::LoadNextBackground()
{
	static WIN32_FIND_DATA find;
	static HANDLE hf=0;

	bool a=true;

	for(int Z=0; Z<20; Z++)
	{
		if (!hf)
		{
			hf=FindFirstFile("m:\\*.jpg",
				&find);

			if (hf==INVALID_HANDLE_VALUE) 
			{
				strcpy(find.cFileName, "706065.jpg");
				a=false;
				break;
			}
		}
		else
			if (!FindNextFile(hf, &find))
			{
				FindClose(hf);
				hf=0;
			}
	}
			
	int cx,cy;

	//if (a==false)
	ffLoadImagePixels(memDC, find.cFileName , cx, cy, 1);
	//else
	//ffLoadImagePixels(memDC, CString("m:\\")+find.cFileName , cx, cy, 1);

}


CGLASS::CGLASS(int l, int h, CDC * dc)
{
	TypeBoxView=0;
	Data=new BOX[l*h];
	Len=l,Hei=h; show_x=show_y=Score=0;

//--------------------------------------------------------------

	CDC dc2;
	dc2.m_hDC=GetDC(NULL);
	memDC.CreateCompatibleDC(&dc2);
//	memBitmapDC.CreateCompatibleDC(&dc2);
	memDC_Save.CreateCompatibleDC(&dc2);

	LoadNextBackground();

  CBitmap * bitmap=new CBitmap;
  bitmap->CreateCompatibleBitmap(&memDC,2048,2048);
  memDC_Save.SelectObject(bitmap);


	//bool res=
	cubicDC.CreateCompatibleDC(&dc2);
	CBitmap * bmp=new CBitmap;
	bmp->CreateCompatibleBitmap(&memDC,2048,2048);
	cubicDC.SelectObject(bmp);



	Clear();

}

void CGLASS::Clear()
{
	for(int x=0; x<Len; x++)
		for(int y=0; y<Hei; y++)
			Write(x,y,BOX());

	Score=0;
	Lines=0;
	Second=0;
	Speed=1;
	Name="Претендент";
}

int DrawGradientString(CDC * pDC,int x, int y, CString str, COLORREF clr, int step=5)
{
	CSize size=pDC->GetTextExtent(str);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(x, y, str);
	return x+size.cx;
}

void CGLASS::ShowToScreen()
{

	int LEN=ONE_LEN*Len;
	int HEI=ONE_LEN*Hei;

	//Zorxor рисуем сетку
//	CPen pen;
//	pen.CreatePen(PS_SOLID,1, NULL,0,NULL);
//	memDC.SelectObject(pen);
	//рисует сетку
	for(int x=0;x<LEN;x+=ONE_LEN)
	{
		memDC.MoveTo(x,0);
		memDC.LineTo(x,HEI);
	}

	for(int y=0;y<LEN;y+=ONE_LEN)
	{
		memDC.MoveTo(0,y);
		memDC.LineTo(LEN,y);
	}


//	showDC->StretchBlt(show_x,show_y,
//	ONE_LEN*Len * 0.7,
//	ONE_LEN*Hei * 0.7, 
///	&memDC,0,0,
///	ONE_LEN*Len,
//	ONE_LEN*Hei, 

	CString k,k1,k2,k3,k4;
	k.Format("Score %06i", Score);
	k1.Format(" Lines %03i", Lines);
	k2.Format("Time %02i:%02i", int(Second)/60, int(Second)%60),
	k3.Format(" Level %02i", Speed);
	extern int tetris_view;
	k4.Format(" View %01i", tetris_view);

	CFont  *font=NULL;
	//if (!font)
	//{
		LOGFONT lf={0};
		//lf.lfHeight=long(ONE_LEN/1.4);
		lf.lfHeight=35;
		lf.lfWidth=lf.lfHeight /2;
		lf.lfPitchAndFamily=FF_DECORATIVE;

		//lf.lfPitchAndFamily=FIXED_PITCH;

		lf.lfCharSet=RUSSIAN_CHARSET;
			

		font=new CFont;
		font->CreateFontIndirect(&lf);
		//CFont *oldfont=showDC->SelectObject(font);
		CFont *oldfont=memDC.SelectObject(font);

		//showDC->SetTextColor(RGB(255,255,255));
		memDC.SetTextColor(RGB(255,255,255));
		int _Y_=show_y+ONE_LEN*Hei-lf.lfHeight*2;

//		DrawGradientString(showDC, show_x+ ONE_LEN*Len, _Y_, k, RGB(255,0,0));
//		DrawGradientString(showDC, show_x+ ONE_LEN*Len, _Y_+lf.lfHeight , k1, RGB(0,0,255));
//		DrawGradientString(showDC, show_x+ ONE_LEN*Len, _Y_-lf.lfHeight , k2, RGB(0,255,255));
//		DrawGradientString(showDC, show_x+ ONE_LEN*Len, _Y_-2*lf.lfHeight , k3, RGB

		int Z=25;
	x=40;

	x=DrawGradientString(&memDC, x, 0, k, RGB(255,0,0));
	x=DrawGradientString(&memDC, x+Z, 0*lf.lfHeight , k1, RGB(0,0,255));
	x=DrawGradientString(&memDC, x+Z, 0*lf.lfHeight , k3, RGB(255,Speed*10, 255-Speed*10));
	x=DrawGradientString(&memDC, x+Z, 0*lf.lfHeight , k2, RGB(0,255,255));
	x=DrawGradientString(&memDC, x+Z, 0*lf.lfHeight , k4, RGB(0,255,255));
	
	DrawGradientString(&memDC, Z+Z, 40  , "F1 help         F2 clear        F11 F12 change(- +) view" , RGB(0,255,255));


	



	//показываем стакан на экране
	showDC->BitBlt(show_x,show_y,
	LEN ,
	HEI, 
	&memDC,0,0,
	SRCCOPY);


	//showDC->SelectObject(oldfont);
	memDC.SelectObject(oldfont);

	delete font;
}

extern int ShowNextFigureFlag;

//показать весь стакан в памяти
void CGLASS::ReDraw()
{
	int len=GetPixelWidth(),
		hei=GetPixelHeight();

	{
	
		static a=0;
		a++;
	/*//копируем фон
		if (a>500) { memDC.BitBlt(0,0, 
		len,hei,
		&memDC,
		len,0,
		SRCCOPY);
		}
		*/

	//else
	{
		static double r,g=0.1,b=0.5;
		CBrush br(
			RGB(100+100*sin(r),100+100*sin(g),100+100*sin(b))
			);
		CRect rt(0,0,len,hei);
		memDC.FillRect(rt,&br);
		//r+=0.01;
		//g+=0.02;
		//b+=0.03;
	}

	if (a>1000) a=0;

  }

	/*showDC->BitBlt(len,hei/2, 
		1024,
		hei,
		&memDC,
		len*2,hei/2,
		SRCCOPY);*/

	/*showDC->FillSolidRect(len,hei/2,
		1, hei/2, RGB(0,127,0));*/


	//рисуем стакан
	for(int x=0; x<Len; x++)
		for(int y=0; y<Hei; y++)
			Show(x,y);

		
	if (ShowNextFigureFlag&1) NextFigure.DrawAnySize(ONE_LEN*8,ONE_LEN*2,ONE_LEN/2);
}

//показать весь стакан на экране
void CGLASS::Show()
{
	ReDraw();
	ShowToScreen();
}

//деструктор стакана
CGLASS::~CGLASS()
{
	delete [] Data;
	//здесь нужно удалить битмапы
}

//возвращает элемент
BOX CGLASS::Read(int x, int y)
{
	if (x>=0 && x<Len)
	{
		if (y<0) return BOX(0);
		if (y>=0 && y<Hei)
		return Data[y*Len+x];
	}

	return BOX(1);
}

bool CGLASS::Write(int x, int y, BOX box)
{
	if (y<0) return true;

	if ( (x>=0 && x<Len) && (y>=0 && y<Hei) )
	{
		Data[y*Len+x]=box;
		return true;
	}
	else return false;

}

void nul(int &a)
{
	//if (a<0) a=0;
}

//показать ЭЛЕМЕНТ стакана 
void CGLASS::Show(int x, int y)
{
	Show(x,y,Read(x,y));
}


CGLASS::ShowAbsoluteInDC(int x1, int y1, BOX bx,CDC &mDC)
{
	int ONE=ONE_LEN;

	if (ONE==0) return 0;

	if (!bx)
	{
		//memDC.FillSolidRect(x1,y1, ONE,ONE, 0); //RGB(255,0,0));
		return 0;
	}

	//else showDC->DrawIcon(x1,y1, hIcon); 
	int R=GetRValue(bx),
		B=GetBValue(bx), G=GetGValue(bx);

	int r1,b1,g1;

	r1=R == 0 ? 0 : 1;
	b1=B == 0 ? 0 : 1;
	g1=G == 0 ? 0 : 1;


	//рисуем один кубик

	//if (bx.type == 0)
	//Zorxor

	//!!!НАСТРОЙКИ!!!
	int type=TypeBoxView;
	//type=0;
	//int type=rand()%6;	//вид кубика

	type=5;

	if (type==0)
	{
		for(int i=0; i<=ONE/2; i++)
		{
			int a=255/ONE;
			int b=255/ONE*2;

			int eR1=R-r1*i*a,
				eG1=G-g1*i*a,
				eB1=B-b1*i*a,

				eR2=-R+r1*i*b,
				eG2=-G+g1*i*b,
				eB2=-B+b1*i*b;

			nul(eR1);
			nul(eG1);
			nul(eB1);
			nul(eR2);
			nul(eG2);
			nul(eB2);

		
			mDC.FillSolidRect(x1+i,y1+i, ONE-i*2,1, RGB(eR1,eG1,eB1));
			mDC.FillSolidRect(x1+i,y1+ONE-1-i, ONE-i*2,1, RGB(eR2,eG2,eB2));

			mDC.FillSolidRect(x1+i,y1+i, 1,		 ONE-i*2, RGB(eR1,eG1,eB1));
			mDC.FillSolidRect(x1+ONE-1-i,y1+i, 1,ONE-i*2, RGB(eR2,eG2,eB2));
		}
	}
	else if (type == 1)
	{

		//#ifndef mac
		#define mac RGB(R-r1*i*a,G-g1*i*a,B-b1*i*a)
		//#endif

		#define mac2 RGB(-R+r1*i*b,-G+g1*i*b,-B+b1*i*b)

		CBrush br;
		br.CreateStockObject(NULL_BRUSH);
		mDC.SelectObject(br);
			//GetStockObject

		for(int i=0; i<=ONE/2; i++)
		{
			//int b=255/ONE*2;
			int a=255/ONE;
			int b=255/ONE*2;
		//CBrush *oldbr=memDC.SelectObject(&br);
			CPen pen(PS_SOLID, 1, mac);
			
			#define s 5
			
			R-=s; G-=s; B-=s;
			
			if (R <0) R=0;
			if (G <0) G=0;
			if (B <0) B=0;
 				
				//RGB(-R+r1*i*b,-G+g1*i*b,-B+b1*i*b) 
				
				//);
			CPen * oldpen=mDC.SelectObject(&pen);
			mDC.Ellipse(x1+i,y1+i,x1+ONE-i,y1+ONE-i);
			mDC.SelectObject(oldpen);
		}
	}
	else if (type==2)
	{
		
		for(int i=0; i<ONE; i++)
		{
			int a=255/ONE;
			int b=255/ONE*2;
			mDC.FillSolidRect(x1,y1+i, ONE,1, mac);
		}
	}

	else if (type==3)
	{
		mDC.FillSolidRect(x1,y1, ONE,ONE, bx.color);
	}
	else if (type==4)
	{
		memDC.MoveTo(x1,y1);
		memDC.LineTo(x1+ONE,y1);
		memDC.LineTo(x1,y1+ONE);
	}
	else 
	{
		//memDC.MoveTo(x1,y1);
		//memDC.LineTo(x1+ONE,y1);
		//memDC.LineTo(x1,y1+ONE);

		//mDC.FillSolidRect(x1,y1, ONE,ONE, RGB(255,255,255));
		int r=rand()%255,
		 g=rand()%255,
		 b=rand()%255;

		//r=255;
		//g=0;
		//b=0;
		
		mDC.FillSolidRect(x1,y1, ONE,ONE, RGB(r,g,b));

		r=g=b=0;
		
		int d=3;
		mDC.FillSolidRect(x1+d,y1+d, ONE-d*2,ONE-d*2, RGB(r,g,b));
	}


	return 0;
}


//показать элемент в абсолютных координатах
CGLASS::ShowAbsolute(int x1, int y1, BOX bx)
{
	if (bx.color==0) return 0;

	int a=GetRValue(bx.color)!=0 ? 1 :0;
	int b=GetGValue(bx.color)!=0 ? 1 :0;
	int c=GetBValue(bx.color)!=0 ? 1 :0;

	memDC.BitBlt(x1,y1,ONE_LEN,ONE_LEN,&cubicDC,(a+b*2+c*4)*ONE_LEN,0,SRCCOPY);
	return 0;
}



//показать 
void CGLASS::Show(int x, int y, BOX bx)
{

	int x1=show_x+x*ONE_LEN,
		y1=show_y+y*ONE_LEN+bx.dy;

	//if (bx.dy!=0) return;

	ShowAbsolute(x1,y1, bx);

}

//функция устанавливает размер 
void CGLASS::SetOneLen(int onelen)
{
	//ZORXOR
	//!!!НАСТРОЙКИ!!!
	onelen=10;	//здесь задается размер кубика

	ONE_LEN=onelen;
	BOX bx;
	bx.dy=0;

	COLORREF rgb[]=
	{
		RGB(255,0,0),
		RGB(0,255,0),
		RGB(0,0,255),
		RGB(255,255,0),
		RGB(255,0,255),
		RGB(0,255,255),
		RGB(255,255,255),
		RGB(255,255,255)
	
	};

	for(int i=0; i<=7; i++)
	{
		bx.color=rgb[i];
		ShowAbsoluteInDC(i*ONE_LEN,0,bx,cubicDC);
	}


}

//force=0 обычный режим тест и скролл
//force=1 обязательно скролл даже если есть пустые
void CGLASS::Scroll(bool force)
{
	bool *state=new bool[Hei];
	for(int i=0; i<Hei; i++) state[i]=false;

	int cnt2=0;

	//double percent=0.3;	//процент заполнения строк (0...1), чтобы произошел скролл
	//!!!НАСТРОЙКИ!!!
	int minimum=0;	//сколько кубиков допустимо быть незаполненными
	for(int y=0; y<Hei; y++)
	{
		int cnt=0;
		for(int x=0; x<Len; x++)
			if (Read(x,y)) cnt++;

			if (cnt==Len || (cnt>=Len-minimum)) 
		{
			state[y]=true, cnt2++;
		}
	}

	//cnt2=force;
	if (force==1) {state[Hei-1]=true, cnt2=1;}

	if (!cnt2) {

		if (SoundEnable) PlaySound("pop.wav");

		delete state; 
		return;
		
	}

		if( cnt2<4)
			if (SoundEnable) PlaySound("xplode2.wav");
		else
			if (SoundEnable) PlaySound("explode.wav");



	//начисление очков
	Lines+=cnt2;
	if (cnt2==1) Score+=100;
	if (cnt2==2) Score+=300;
	if (cnt2==3) Score+=700;
	if (cnt2 >= 4 )Score+=1500+(cnt2-4)*350;

	int a1=rand()%2, a2=rand()%2, a3=rand()%2;
	if (!a1 && !a2 && !a3) a1=1;


	bool NeedAnimate=true;
	
	if (NeedAnimate){

	//анимация разлета строки
	CGLASS *glass=this;	

	const max=400;
	MOVEOBJ mo[max];
	mo[0].glass=glass;
	int i=0;
	for(int x=0; x<glass->Len; x++)
		for(int y=0; y<glass->Hei; y++)
			if (glass->Read(x,y) &&
								state[y]==true)
				
		{
		//!!!НАСТРОЙКИ!!!
		//скорость анимации
		double SpeedAnimation=0.1;
		mo[i].x=x*glass->ONE_LEN;
		mo[i].y=y*glass->ONE_LEN;
		mo[i].Speedy=SpeedAnimation*(-2.9-rand(30)*0.1);
		mo[i].Speedx=SpeedAnimation*(0.2+rand(20)*0.1);
		if (rand(2)) mo[i].Speedx*=-1;
		mo[i].bx=glass->Read(x,y);
		mo[i].Acceleratx=0;
		mo[i].Acceleraty=SpeedAnimation*0.02;
		//glass->Write(x,y,0);
		i++;
		if (i==max) { x=255; break;}
	}
	int real=i;

////////
	for(y=0; y<Hei; y++)
	{
		if (state[y])
		for(int x=0;x<Len;x++)
			Write(x,y,BOX(0));
	}


	//////////

	DWORD StartTime=GetTickCount();

	ReDraw();
	SaveBitmap();

	for(int d=0; d<255;d++)
	{
	//////////

		if (d==30) 
		{
			for(y=0; y<Hei; y++)
			{
				if (state[y])
				{
					//скролим
					for(int y1=y; y1>=1; y1--)
					for(int x1=0; x1<Len; x1++)
							Write(x1,y1, Read(x1,y1-1));

								//обнуляем верхнюю строку
						for(int x1=0; x1<Len; x1++)
					Write(x1,0,BOX(0));
				}
			}
			ReDraw();
			SaveBitmap();

		}

		///////////
		//glass->ReDraw();
		RestoreBitmap();
		//ReDraw();

		int cnt=0;
		for(i=0; i<real; i++)
		{
			mo[i].Show();
		#define an  	mo[i].Animate();
			an an an an 
 		#undef an

			if (mo[i].y> (glass->ONE_LEN*(glass->Hei+1)) ) cnt++;
			
			if (mo[i].x<0
				//&& mo[i].y < glass->ONE_LEN*glass->Hei
				) 
			{
				mo[i].Speedx *= -1 ;
				mo[i].x=1;
				//if (i==3) 
				//sndPlaySound("pop2.wav",SND_ASYNC);
			}
				
			if (mo[i].x> glass->ONE_LEN*(glass->Len-1) )
				//&& mo[i].y < glass->ONE_LEN*glass->Hei) 
			{
				mo[i].x=glass->ONE_LEN*(glass->Len-1)-5;
				mo[i].Speedx *= -1 ;
				//sndPlaySound("pop2.wav",SND_ASYNC);
			}
		}

		if (cnt==real) break;
		glass->ShowToScreen();

		Sleep(1);
	}

	//d=1;
	if (d)
	{
	/*int fps=1000/d/(GetTickCount()-StartTime);
	CString m;
	m.Format("FPS=%i", fps);
	showDC->SetTextColor(0);
	showDC->TextOut(320,0, m);
	//Sleep(1000);
	*/
	}

	double d_time=(GetTickCount()-StartTime)/1000.0;
	Second+=d_time;

	}

	delete state;
}


//сохраняет текущую картинку в контексте memDC_Save
void CGLASS::SaveBitmap()
{
	memDC_Save.BitBlt(0,0,
	ONE_LEN*Len ,ONE_LEN*Hei, 
	&memDC,0,0,
	SRCCOPY);
}

//восстанавливает картинку 
void CGLASS::RestoreBitmap()
{
	memDC.BitBlt(0,0,
	ONE_LEN*Len ,
	ONE_LEN*Hei, 
	&memDC_Save,0 ,0,
	SRCCOPY);

}

//получить ширину стакана в пикселах
int CGLASS::GetPixelWidth()
{
	return ONE_LEN*Len;
}

//получить высоту стакана в пикселах
int CGLASS::GetPixelHeight()
{
	return ONE_LEN*Hei;
}
