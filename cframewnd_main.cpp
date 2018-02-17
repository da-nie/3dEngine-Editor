#include "cframewnd_main.h"

//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CFrameWnd_Main,CFrameWnd)
 ON_WM_CREATE()
 ON_WM_DESTROY()
 ON_WM_TIMER()
 ON_CBN_SELCHANGE(IDD_COMBOBOX_GRIDSIZE,ToolBar_ChangeGridSize) 
 ON_COMMAND(ID_MENU_WINDOW_MAIN_PANEL,OnMenu_Window_ShowMainPanel)
 ON_COMMAND(ID_MENU_WINDOW_CONTROL_PANEL,OnMenu_Window_ShowControlPanel)
 ON_COMMAND(ID_MENU_WINDOW_VIEW_PANEL,OnMenu_Window_ShowViewPanel) 
 ON_COMMAND(ID_MENU_FILE_CLEARMAP,OnMenu_File_ClearMap)
 ON_COMMAND(ID_MENU_FILE_LOAD,OnMenu_File_Load)
 ON_COMMAND(ID_MENU_FILE_SAVE,OnMenu_File_Save)
 ON_COMMAND(ID_MENU_FILE_EXPORT_BSP,OnMenu_File_ExportBSP)
 ON_COMMAND(ID_MENU_FILE_EXPORT_PORTAL,OnMenu_File_ExportPORTAL)
 ON_COMMAND(ID_MENU_FILE_IMPORT_TXT,OnMenu_File_ImportTXT)
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CFrameWnd_Main::CFrameWnd_Main(void)
{
 //cTexture.LoadPaletteTexture("texture.tpi");
 if (cTexture.Load("texture.tia")==false) cTexture.LoadPaletteTexture("texture.tpi");
}
//-Деструктор класса---------------------------------------------------------
CFrameWnd_Main::~CFrameWnd_Main()
{
 cTexture.Release();
}
//-Функции класса------------------------------------------------------------
//-Функции обработки сообщений класса----------------------------------------

//---------------------------------------------------------------------------
//событие создания окна
//---------------------------------------------------------------------------
int CFrameWnd_Main::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
 EnableDocking(CBRS_ALIGN_ANY);
 //создадим диалоговую панель
 cDialogBar_Control.Create(this,IDD_DIALOGBAR_CONTROL,WS_VISIBLE|CBRS_ALIGN_LEFT|CBRS_GRIPPER,IDD_DIALOGBAR_CONTROL);
 cDialogBar_Control.SetWindowText("Вспомогательная панель управления");
 cDialogBar_Control.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
 DockControlBar(&cDialogBar_Control,AFX_IDW_DOCKBAR_LEFT);
 //установим значения в полях панели
 CStatic *cStatic_CursorX=(CStatic *)cDialogBar_Control.GetDlgItem(IDC_STATIC_DIALOGBAR_CONTROL_CURSOR_X);
 CStatic *cStatic_CursorY=(CStatic *)cDialogBar_Control.GetDlgItem(IDC_STATIC_DIALOGBAR_CONTROL_CURSOR_Y);
 cStatic_CursorX->SetWindowText("0"); 
 cStatic_CursorY->SetWindowText("0"); 
 /*
 CButton *cButton_ActivateMode=(CButton *)cMap.cDialogBar_Control.GetDlgItem(IDC__BUTTON__DIALOGBAR_CONTROL__ACTIVATE_MODE);
 cButton_ActivateMode->ShowWindow(SW_HIDE);
 */
 //создадим общую панель управления
 cToolBar_Main.Create(this,WS_CHILD|WS_VISIBLE|CBRS_SIZE_FIXED|CBRS_TOP|CBRS_TOOLTIPS);
 cToolBar_Main.LoadBitmap(IDB_BITMAP_MAIN);
 UINT ButtonIndex_Main[7];
 ButtonIndex_Main[0]=ID_BUTTON_TOOLBAR_MAIN_CREATE_WALL;
 ButtonIndex_Main[1]=ID_BUTTON_TOOLBAR_MAIN_CREATE_FRONTIER;
 ButtonIndex_Main[2]=ID_BUTTON_TOOLBAR_MAIN_CREATE_SECTOR;
 ButtonIndex_Main[3]=ID_BUTTON_TOOLBAR_MAIN_WALL_SELECT;
 ButtonIndex_Main[4]=ID_BUTTON_TOOLBAR_MAIN_FRONTIER_SELECT;
 ButtonIndex_Main[5]=ID_BUTTON_TOOLBAR_MAIN_SECTOR_SELECT;
 ButtonIndex_Main[6]=ID_BUTTON_TOOLBAR_MAIN_SET_PLAYER_POSITION;
 cToolBar_Main.SetButtons(ButtonIndex_Main,7);
 cToolBar_Main.SetButtonStyle(0,TBBS_CHECKGROUP);
 cToolBar_Main.SetButtonStyle(1,TBBS_CHECKGROUP);
 cToolBar_Main.SetButtonStyle(2,TBBS_CHECKGROUP);
 cToolBar_Main.SetButtonStyle(3,TBBS_CHECKGROUP);
 cToolBar_Main.SetButtonStyle(4,TBBS_CHECKGROUP);
 cToolBar_Main.SetButtonStyle(5,TBBS_CHECKGROUP);
 cToolBar_Main.SetButtonStyle(6,TBBS_CHECKGROUP);
 cToolBar_Main.SetSizes(CSize(39,39),CSize(32,32));
 cToolBar_Main.EnableDocking(CBRS_ALIGN_TOP);
 cToolBar_Main.SetWindowText("Основная панель управления"); 
 DockControlBar(&cToolBar_Main,AFX_IDW_DOCKBAR_TOP);
 //создадим панель инструментов
 cToolBar_View.Create(this,WS_CHILD|WS_VISIBLE|CBRS_SIZE_FIXED|CBRS_TOP|CBRS_TOOLTIPS);
 //загрузим картинки для панели
 cToolBar_View.LoadBitmap(IDB_BITMAP_VIEW_TOOLBAR);
 //установим число кнопок и их идентификаторы
 UINT ButtonIndex_View[6];
 ButtonIndex_View[0]=ID_BUTTON_TOOLBAR_VIEW_SCALE_PLUS;
 ButtonIndex_View[1]=ID_BUTTON_TOOLBAR_VIEW_SCALE_MINUS;
 ButtonIndex_View[2]=0;
 ButtonIndex_View[3]=0;
 ButtonIndex_View[4]=0;
 ButtonIndex_View[5]=ID_BUTTON_TOOLBAR_VIEW_BINDING;
 cToolBar_View.SetButtons(ButtonIndex_View,6);
 //настроим кнопки панели
 cToolBar_View.SetButtonStyle(0,TBBS_BUTTON);
 cToolBar_View.SetButtonStyle(1,TBBS_BUTTON);
 cToolBar_View.SetButtonInfo(2,ID_SEPARATOR,TBBS_SEPARATOR,12);
 cToolBar_View.SetButtonInfo(3,IDD_COMBOBOX_GRIDSIZE,TBBS_SEPARATOR,200);
 cToolBar_View.SetButtonInfo(4,ID_SEPARATOR,TBBS_SEPARATOR,12);
 cToolBar_View.SetButtonStyle(5,TBBS_CHECKBOX);
 //название панели
 cToolBar_View.SetWindowText("Настройка вида");
 //устанавливаем новые размеры кнопок
 SIZE Size_Button;
 Size_Button.cx=33;
 Size_Button.cy=33;
 SIZE Size_Image;
 Size_Image.cx=26;
 Size_Image.cy=26;
 cToolBar_View.SetSizes(Size_Button,Size_Image);
 //создадим в панели комбинированный список
 CRect rect;
 cToolBar_View.GetItemRect(3,&rect);
 rect.top=2;
 rect.bottom=rect.top+100;
 cComboBox_GridSize.Create(WS_VSCROLL|CBS_DISABLENOSCROLL|CBS_NOINTEGRALHEIGHT|CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP,rect,&cToolBar_View,IDD_COMBOBOX_GRIDSIZE);
 cComboBox_GridSize.AddString("Шаг сетки 1");
 cComboBox_GridSize.AddString("Шаг сетки 10");
 cComboBox_GridSize.AddString("Шаг сетки 50");
 cComboBox_GridSize.AddString("Шаг сетки 100");
 cComboBox_GridSize.AddString("Шаг сетки 500");
 cComboBox_GridSize.AddString("Шаг сетки 1000");
 cComboBox_GridSize.AddString("Шаг сетки 5000");
 cComboBox_GridSize.AddString("Шаг сетки 10000");
 cComboBox_GridSize.SetCurSel(1); 
 cToolBar_View.EnableDocking(CBRS_ALIGN_ANY);
 DockControlBar(&cToolBar_View,AFX_IDW_DOCKBAR_BOTTOM);
 //подключаем таймер
 SetTimer(IDR_TIMER_MAIN,100,0);
 return(CFrameWnd::OnCreate(lpCreateStruct));
}
//---------------------------------------------------------------------------
//событие уничтожения окна
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnDestroy(void)
{
 KillTimer(IDR_TIMER_MAIN);
}
//---------------------------------------------------------------------------
//изменили масштаб сетки
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::ToolBar_ChangeGridSize(void)
{
 long sizeno=cComboBox_GridSize.GetCurSel();
 long gridsize=1;
 if (sizeno==0) gridsize=1;
 if (sizeno==1) gridsize=10;
 if (sizeno==2) gridsize=50;
 if (sizeno==3) gridsize=100;
 if (sizeno==4) gridsize=500;
 if (sizeno==5) gridsize=1000;
 if (sizeno==6) gridsize=5000;
 if (sizeno==7) gridsize=10000;
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->SetGridSize(gridsize);
}
//---------------------------------------------------------------------------
//событие таймера
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnTimer(UINT nIDEvent)
{
 if (nIDEvent==IDR_TIMER_MAIN)
 {
  CMenu *cMenu_Main=GetMenu();
  if (cMenu_Main!=NULL)
  {
   long bVisible_ControlPanel=((cDialogBar_Control.GetStyle()&WS_VISIBLE)!=0);
   long bVisible_MainPanel=((cToolBar_Main.GetStyle()&WS_VISIBLE)!=0);
   long bVisible_ViewPanel=((cToolBar_View.GetStyle()&WS_VISIBLE)!=0);

   long state_ControlPanel=cMenu_Main->GetMenuState(ID_MENU_WINDOW_CONTROL_PANEL,MF_BYCOMMAND);
   if (state_ControlPanel==MF_CHECKED && bVisible_ControlPanel==0) cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_CONTROL_PANEL,MF_UNCHECKED);

   long state_MainPanel=cMenu_Main->GetMenuState(ID_MENU_WINDOW_MAIN_PANEL,MF_BYCOMMAND);
   if (state_MainPanel==MF_CHECKED && bVisible_MainPanel==0) cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_MAIN_PANEL,MF_UNCHECKED);

   long state_ViewPanel=cMenu_Main->GetMenuState(ID_MENU_WINDOW_VIEW_PANEL,MF_BYCOMMAND);
   if (state_ViewPanel==MF_CHECKED && bVisible_ViewPanel==0) cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_VIEW_PANEL,MF_UNCHECKED);
  }
 }
 CFrameWnd::OnTimer(nIDEvent);
}
//---------------------------------------------------------------------------
//выбрана смена видимости главной панели
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_Window_ShowMainPanel(void)
{
 CMenu *cMenu_Main=GetMenu();
 long state=cMenu_Main->GetMenuState(ID_MENU_WINDOW_MAIN_PANEL,MF_BYCOMMAND);
 if (state==MF_CHECKED)//уничтожить панель
 {
  cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_MAIN_PANEL,MF_UNCHECKED);
  ShowControlBar(&cToolBar_Main,FALSE,FALSE);
 }
 if (state==MF_UNCHECKED)//создать панель
 {
  cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_MAIN_PANEL,MF_CHECKED);
  ShowControlBar(&cToolBar_Main,TRUE,FALSE);
 }
}
//---------------------------------------------------------------------------
//выбрана смена видимости панели управления
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_Window_ShowControlPanel(void)
{
 CMenu *cMenu_Main=GetMenu();
 long state=cMenu_Main->GetMenuState(ID_MENU_WINDOW_CONTROL_PANEL,MF_BYCOMMAND);
 if (state==MF_CHECKED)//уничтожить панель
 {
  cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_CONTROL_PANEL,MF_UNCHECKED);
  ShowControlBar(&cDialogBar_Control,FALSE,FALSE);
 }
 if (state==MF_UNCHECKED)//создать панель
 {
  cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_CONTROL_PANEL,MF_CHECKED);
  ShowControlBar(&cDialogBar_Control,TRUE,FALSE);
 }
}
//---------------------------------------------------------------------------
//выбрана смена видимости панели вида
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_Window_ShowViewPanel(void)
{
 CMenu *cMenu_Main=GetMenu();
 long state=cMenu_Main->GetMenuState(ID_MENU_WINDOW_VIEW_PANEL,MF_BYCOMMAND);
 if (state==MF_CHECKED)//уничтожить панель
 {
  cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_VIEW_PANEL,MF_UNCHECKED);
  ShowControlBar(&cToolBar_View,FALSE,FALSE);
 }
 if (state==MF_UNCHECKED)//создать панель
 {
  cMenu_Main->CheckMenuItem(ID_MENU_WINDOW_VIEW_PANEL,MF_CHECKED);
  ShowControlBar(&cToolBar_View,TRUE,FALSE);
 }
}
//---------------------------------------------------------------------------
//выбрана очистка поля
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_File_ClearMap(void)
{
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->ClearMap();
}
//---------------------------------------------------------------------------
//выбрана загрузка
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_File_Load(void)
{
 char Path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,Path); 
 CFileDialog cFileDialog(TRUE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.3dm|*.3dm||",this);
 cFileDialog.m_ofn.lpstrInitialDir=Path;
 char Title[256];
 strcpy(Title,"Загрузка файла уровня");
 cFileDialog.m_ofn.lpstrTitle=Title;
 if (cFileDialog.DoModal()!=IDOK) return;
 string file_name=cFileDialog.GetFileName();
 FILE *file=fopen(file_name.c_str(),"rb");
 if (file==NULL)
 {
  MessageBox("Не могу открыть файл!","Ошибка",MB_OK);
  return;
 }
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->LoadMap(file);
 fclose(file);
}
//---------------------------------------------------------------------------
//выбрано сохранение
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_File_Save(void)
{
 char Path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,Path); 
 CFileDialog cFileDialog(FALSE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.3dm|*.3dm||",this);
 cFileDialog.m_ofn.lpstrInitialDir=Path;
 char Title[256];
 strcpy(Title,"Сохранение файла уровня");
 cFileDialog.m_ofn.lpstrTitle=Title;
 if (cFileDialog.DoModal()!=IDOK) return;
 string file_name=cFileDialog.GetFileName();
 FILE *file=fopen(file_name.c_str(),"wb");
 if (file==NULL)
 {
  MessageBox("Не могу сохранить файл!","Ошибка",MB_OK);
  return;
 }
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->SaveMap(file);
 fclose(file);
}
//---------------------------------------------------------------------------
//выбран экспорт карты в BSP
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_File_ExportBSP(void)
{
 char Path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,Path); 
 CFileDialog cFileDialog(FALSE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.bsp|*.bsp||",this);
 cFileDialog.m_ofn.lpstrInitialDir=Path;
 char Title[256];
 strcpy(Title,"Экспорт файла уровня в формате BSP");
 cFileDialog.m_ofn.lpstrTitle=Title;
 if (cFileDialog.DoModal()!=IDOK) return;
 string file_name=cFileDialog.GetFileName();
 FILE *file=fopen(file_name.c_str(),"wb");
 if (file==NULL)
 {
  MessageBox("Не могу сохранить файл!","Ошибка",MB_OK);
  return;
 }
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->ExportMapBSP(file);
 fclose(file);
}
//---------------------------------------------------------------------------
//выбран экспорт карты в PORTAL
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_File_ExportPORTAL(void)
{
 char Path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,Path); 
 CFileDialog cFileDialog(FALSE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.ptl|*.ptl||",this);
 cFileDialog.m_ofn.lpstrInitialDir=Path;
 char Title[256];
 strcpy(Title,"Экспорт файла уровня в формате PORTAL");
 cFileDialog.m_ofn.lpstrTitle=Title;
 if (cFileDialog.DoModal()!=IDOK) return;
 string file_name=cFileDialog.GetFileName();
 FILE *file=fopen(file_name.c_str(),"wb");
 if (file==NULL)
 {
  MessageBox("Не могу сохранить файл!","Ошибка",MB_OK);
  return;
 }
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->ExportMapPORTAL(file);
 fclose(file);
}
//---------------------------------------------------------------------------
//импортировать карту из текстового файла
//---------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnMenu_File_ImportTXT(void)
{
 char Path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,Path); 
 CFileDialog cFileDialog(TRUE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.txt|*.txt||",this);
 cFileDialog.m_ofn.lpstrInitialDir=Path;
 char Title[256];
 strcpy(Title,"Импорт карты из текстового файла");
 cFileDialog.m_ofn.lpstrTitle=Title;
 if (cFileDialog.DoModal()!=IDOK) return;
 string file_name=cFileDialog.GetFileName();
 FILE *file=fopen(file_name.c_str(),"rb");
 if (file==NULL)
 {
  MessageBox("Не могу открыть файл!","Ошибка",MB_OK);
  return;
 }
 //получим указатель на представление
 CView_Map* cView=reinterpret_cast<CView_Map*>(GetActiveView());
 cView->ImportMapFromTXT(file);
 fclose(file);
}
//-Прочее--------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CFrameWnd_Main,CFrameWnd)
//-Функции класса----------------------------------------------------------

//---------------------------------------------------------------------------
//установить в окне координаты курсора
//---------------------------------------------------------------------------
void CFrameWnd_Main::SetCursorPos(long x,long y)
{ 
 CStatic *cStatic_CursorX=(CStatic *)cDialogBar_Control.GetDlgItem(IDC_STATIC_DIALOGBAR_CONTROL_CURSOR_X);
 CStatic *cStatic_CursorY=(CStatic *)cDialogBar_Control.GetDlgItem(IDC_STATIC_DIALOGBAR_CONTROL_CURSOR_Y);
 char string[255];
 sprintf(string,"%ld",x);
 cStatic_CursorX->SetWindowText(string);
 sprintf(string,"%ld",y);
 cStatic_CursorY->SetWindowText(string);
}
