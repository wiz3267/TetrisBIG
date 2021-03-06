#ifndef __RECTABLE_H
#define __RECTABLE_H

class CGLASS;
//����� RECTABLE - ������� �����������
class RECTABLE
{
public:
		CGLASS *glass;
	enum {
		MAX_RECORD=10,		//������������ ����� ��������
		NAME_MAXLEN=14		//������������ ����� �����
	};


//������ ���������� � ������������
struct RECORD
{
	char name[ NAME_MAXLEN] ;		//���
	DWORD score;	        //����� �����
	DWORD lines;			//����� �����
	DWORD second;			//����� ����(c�����)
};

RECORD record[MAX_RECORD+1];		//������� ��������

public:
	int x,y;	//���������� ������ �������
	int GetFontWidth();
	int GetWidth();
	RECTABLE();	//�����������
	~RECTABLE();	//����������
	void Save();		//�������� ������� �� ����
	void Load();		//������� ������� � �����

	//������� ��������� ����� ������ � �������
	void PutNewRecord(int newscore, int lines, int second, char * name);
	void Show(HDC hdc,int score, char *name, int lines, int second,COLORREF);		//�������� ������� �� ������

	//�������� ������������ ������ �� �������
	int GetMaxScore();
	int GetMinScore();
};

#endif