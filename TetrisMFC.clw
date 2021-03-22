; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTetrisMFCView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TetrisMFC.h"
LastPage=0

ClassCount=10
Class1=CTetrisMFCApp
Class2=CTetrisMFCDoc
Class3=CTetrisMFCView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDD_LOADING
Class5=CAboutDlg
Resource3=IDD_DIALOG2
Class6=DialogInputName
Resource4="IDR_MENU1"
Resource5=IDR_MENU1
Resource6=IDD_DIALOG1
Resource7=ID_DIALOG_SETTING
Resource8=IDD_ABOUTBOX (English (U.S.))
Class7=CSetting
Class8=CSetdial
Class9=CSettingDialog
Resource9=IDR_MAINFRAME
Class10=CLoading
Resource10=IDR_MAINFRAME (English (U.S.))

[CLS:CTetrisMFCApp]
Type=0
HeaderFile=TetrisMFC.h
ImplementationFile=TetrisMFC.cpp
Filter=N
LastObject=CTetrisMFCApp

[CLS:CTetrisMFCDoc]
Type=0
HeaderFile=TetrisMFCDoc.h
ImplementationFile=TetrisMFCDoc.cpp
Filter=N
LastObject=CTetrisMFCDoc

[CLS:CTetrisMFCView]
Type=0
HeaderFile=TetrisMFCView.h
ImplementationFile=TetrisMFCView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CTetrisMFCView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=TetrisMFC.cpp
ImplementationFile=TetrisMFC.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=DialogInputName
ControlCount=2
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817

[CLS:DialogInputName]
Type=0
HeaderFile=DialogInputName.h
ImplementationFile=DialogInputName.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
CommandCount=0

[MNU:"IDR_MENU1"]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
Command12=ID_MENU_SHOW_ONLY_GLASS
CommandCount=12

[DLG:IDD_DIALOG2]
Type=1
Class=CSetting
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CSetting]
Type=0
HeaderFile=Setting.h
ImplementationFile=Setting.cpp
BaseClass=CDialog
Filter=D

[CLS:CSetdial]
Type=0
HeaderFile=Setdial.h
ImplementationFile=Setdial.cpp
BaseClass=CDialog
Filter=D

[DLG:ID_DIALOG_SETTING]
Type=1
Class=CSettingDialog
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO1,combobox,1344339970
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK2,button,1342242819
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_CHECK3,button,1342242819
Control8=IDC_CHECK4,button,1342242819

[CLS:CSettingDialog]
Type=0
HeaderFile=SettingDialog2.h
ImplementationFile=SettingDialog2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK3

[DLG:IDD_LOADING]
Type=1
Class=CLoading
ControlCount=1
Control1=IDC_STATIC1,static,1342308352

[CLS:CLoading]
Type=0
HeaderFile=Loading.h
ImplementationFile=Loading.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLoading

