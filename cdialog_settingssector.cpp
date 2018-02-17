#include "cdialog_settingssector.h"

extern CTexture cTexture;

//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CDialog_SettingsSector,CDialog)
 ON_WM_DESTROY()
 ON_WM_CLOSE()
 ON_WM_PAINT()
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_CANCEL,OnCommand_Button_Cancel)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_OK,OnCommand_Button_Ok)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_CHANGETEXTURE_UP,OnCommand_Button_ChangeTextureUp)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_CHANGETEXTURE_DOWN,OnCommand_Button_ChangeTextureDown)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_ANIMATE_UP,OnCommand_Button_ChangeTextureFollowUp)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_ANIMATE_DOWN,OnCommand_Button_ChangeTextureFollowDown)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_COPY_TO_FLOOR,OnCommand_Button_CopyFlowToFloor)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_SECTOR_COPY_TO_FLOW,OnCommand_Button_CopyFloorToFlow)
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CDialog_SettingsSector::CDialog_SettingsSector(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{ 
 STexture sTexture;
 sTexture.TextureIndex=0;
 sSector_State_Current.cTextureFollow_Up.Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 sSector_State_Current.cTextureFollow_Up.vector_STexture.clear();
 sSector_State_Current.cTextureFollow_Up.vector_STexture.push_back(sTexture);

 sSector_State_Current.cTextureFollow_Down.Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 sSector_State_Current.cTextureFollow_Down.vector_STexture.clear();
 sSector_State_Current.cTextureFollow_Down.vector_STexture.push_back(sTexture);

 sSector_State_Current.UpLevel=127;
 sSector_State_Current.DownLevel=0;
 sSector_State_Current.WorkingLevel=sSector_State_Current.DownLevel;
 sSector_State_Current.Antigravitation=false;

 sSector_State_Current.LightingMode=LIGHTING_MODE_STATIC;
 sSector_State_Current.BaseLighting=255;
 sSector_State_Current.BaseLightingTime=100;
 sSector_State_Current.MaxLightingTime=100;
 sSector_State_Current.SectorType=SECTOR_TYPE_SIMPLY;

 strcpy(sSector_State_Current.Label,"STANDART");

 sSector_State_Local=sSector_State_Current;
}
//-Деструктор класса---------------------------------------------------------
CDialog_SettingsSector::~CDialog_SettingsSector()
{
}
//-Замещённые функции предка-------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnOK(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCancel(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnClose(void)
{
 EndDialog(0);
}
//---------------------------------------------------------------------------
//инициализация диалога
//---------------------------------------------------------------------------
afx_msg BOOL CDialog_SettingsSector::OnInitDialog(void)
{
 sSector_State_Local=sSector_State_Current;
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_DOWN_LEVEL))->SetLimitText(50);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_UP_LEVEL))->SetLimitText(50);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_BASE_LIGHTING))->SetLimitText(5);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_BASE_LIGHTING_TIME))->SetLimitText(50);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_MAX_LIGHTING_TIME))->SetLimitText(50);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_LABEL))->SetLimitText(SECTOR_LABEL_SIZE-1);

 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->ResetContent();
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Простой сектор");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Обычная дверь");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Сектор-переключатель");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Дверь от переключателя");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Платформа");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Платформа от переключателя");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Выход с уровня");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Телепортатор");
 ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->AddString("Мостик"); 

 if (sSector_State_Local.SectorType==SECTOR_TYPE_SIMPLY) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(0);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_DOOR) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(1);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_SWITCH) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(2);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_SWITCH_DOOR) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(3);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_PLATFORM) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(4);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_SWITCH_PLATFORM) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(5);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_END) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(6);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_TELEPORT) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(7);
 if (sSector_State_Local.SectorType==SECTOR_TYPE_BRIDGE) ((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->SetCurSel(8);

 ((CButton*)GetDlgItem(IDC_CHECK_DIALOG_SETTINGS_ANTIGRAVITATION))->SetCheck(0);
 if (sSector_State_Local.Antigravitation==true) ((CButton*)GetDlgItem(IDC_CHECK_DIALOG_SETTINGS_ANTIGRAVITATION))->SetCheck(1);

 char string[255];
 sprintf(string,"%ld",sSector_State_Local.UpLevel);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_UP_LEVEL))->SetWindowText(string);
 sprintf(string,"%ld",sSector_State_Local.DownLevel);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_DOWN_LEVEL))->SetWindowText(string);
 sprintf(string,"%ld",sSector_State_Local.WorkingLevel);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_WORKING_LEVEL))->SetWindowText(string);

 sprintf(string,"%ld",sSector_State_Local.BaseLighting);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_BASE_LIGHTING))->SetWindowText(string);

 sprintf(string,"%ld",sSector_State_Local.BaseLightingTime);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_BASE_LIGHTING_TIME))->SetWindowText(string);

 sprintf(string,"%ld",sSector_State_Local.MaxLightingTime);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_MAX_LIGHTING_TIME))->SetWindowText(string);

 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_LABEL))->SetWindowText(sSector_State_Local.Label);

 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_STATIC))->SetCheck(0);
 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_FLASH))->SetCheck(0);
 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_RANDOM_FLASH))->SetCheck(0);
 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_DAWNING_SUNDOWN))->SetCheck(0);

 if (sSector_State_Local.LightingMode==LIGHTING_MODE_STATIC) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_STATIC))->SetCheck(1);
 if (sSector_State_Local.LightingMode==LIGHTING_MODE_FLASH) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_FLASH))->SetCheck(1);
 if (sSector_State_Local.LightingMode==LIGHTING_MODE_RANDOM_FLASH) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_RANDOM_FLASH))->SetCheck(1);
 if (sSector_State_Local.LightingMode==LIGHTING_MODE_DAWNING_SUNDOWN) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_DAWNING_SUNDOWN))->SetCheck(1);

 return(CDialog::OnInitDialog());
}
//-Новые функции класса------------------------------------------------------
//-Функции обработки сообщений класса----------------------------------------

//---------------------------------------------------------------------------
//событие уничтожения окна
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnDestroy(void)
{
 CDialog::OnDestroy();
}
//---------------------------------------------------------------------------
//событие отрисовки
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnPaint(void)
{ 
 CPaintDC cPaintDC(this);

 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=128;
 bmih.biHeight=-128;
 bmih.biPlanes=1;
 bmih.biBitCount=32;
 bmih.biCompression=BI_RGB;
 bmih.biSizeImage=0;
 bmih.biXPelsPerMeter=300;
 bmih.biYPelsPerMeter=300;
 bmih.biClrUsed=0;
 bmih.biClrImportant=0;
 RGBQUAD rgbq;
 BITMAPINFO info;
 rgbq.rgbBlue=1;
 rgbq.rgbGreen=0;
 rgbq.rgbRed=0;
 rgbq.rgbReserved=0;
 info.bmiHeader=bmih;
 info.bmiColors[0]=rgbq;

 CRect cRect;
 cRect.left=144;
 cRect.right=cRect.left+64;
 cRect.top=16;
 cRect.bottom=cRect.top+64;
 MapDialogRect(&cRect);

 STextureImage *sTextureImage_Ptr=cTexture.GetTextureImagePtr(sSector_State_Local.cTextureFollow_Up.vector_STexture[0].TextureIndex);
 unsigned char error[128*128*4];
 memset(error,255,128*128*4);
 unsigned char *image=error;
 if (sTextureImage_Ptr!=NULL)
 {
  image=sTextureImage_Ptr->Image;
  bmih.biWidth=sTextureImage_Ptr->Size;
  bmih.biHeight=-sTextureImage_Ptr->Size;
 }
 StretchDIBits(cPaintDC,cRect.left,cRect.top,cRect.right-cRect.left,cRect.bottom-cRect.top,0,0,abs(bmih.biWidth),abs(bmih.biHeight),image,&info,DIB_RGB_COLORS,SRCCOPY);

 sTextureImage_Ptr=cTexture.GetTextureImagePtr(sSector_State_Local.cTextureFollow_Down.vector_STexture[0].TextureIndex);
 image=error;
 if (sTextureImage_Ptr!=NULL)
 {
  image=sTextureImage_Ptr->Image;
  bmih.biWidth=sTextureImage_Ptr->Size;
  bmih.biHeight=-sTextureImage_Ptr->Size;
 }
 cRect.left=8;
 cRect.right=cRect.left+64;
 cRect.top=16;
 cRect.bottom=cRect.top+64;
 MapDialogRect(&cRect);
 StretchDIBits(cPaintDC,cRect.left,cRect.top,cRect.right-cRect.left,cRect.bottom-cRect.top,0,0,abs(bmih.biWidth),abs(bmih.biHeight),image,&info,DIB_RGB_COLORS,SRCCOPY);
}
//---------------------------------------------------------------------------
//отмена
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_Cancel(void)
{
 EndDialog(0);
}
//---------------------------------------------------------------------------
//применить
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_Ok(void)
{
 //считываем настройки
 char string[255]; 

 long index=((CComboBox*)GetDlgItem(IDC_COMBO_DIALOG_SETTINGS_SECTOR_TYPE))->GetCurSel();;
 if (index==0) sSector_State_Local.SectorType=SECTOR_TYPE_SIMPLY;
 if (index==1) sSector_State_Local.SectorType=SECTOR_TYPE_DOOR;
 if (index==2) sSector_State_Local.SectorType=SECTOR_TYPE_SWITCH;
 if (index==3) sSector_State_Local.SectorType=SECTOR_TYPE_SWITCH_DOOR;
 if (index==4) sSector_State_Local.SectorType=SECTOR_TYPE_PLATFORM;
 if (index==5) sSector_State_Local.SectorType=SECTOR_TYPE_SWITCH_PLATFORM;
 if (index==6) sSector_State_Local.SectorType=SECTOR_TYPE_END;
 if (index==7) sSector_State_Local.SectorType=SECTOR_TYPE_TELEPORT;
 if (index==8) sSector_State_Local.SectorType=SECTOR_TYPE_BRIDGE; 

 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_UP_LEVEL))->GetWindowText(string,255);
 sSector_State_Local.UpLevel=atoi(string);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_DOWN_LEVEL))->GetWindowText(string,255);
 sSector_State_Local.DownLevel=atoi(string);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_WORKING_LEVEL))->GetWindowText(string,255);
 sSector_State_Local.WorkingLevel=atoi(string);

 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_BASE_LIGHTING))->GetWindowText(string,255);
 sSector_State_Local.BaseLighting=atoi(string);

 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_BASE_LIGHTING_TIME))->GetWindowText(string,255);
 sSector_State_Local.BaseLightingTime=atoi(string);

 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_MAX_LIGHTING_TIME))->GetWindowText(string,255);
 sSector_State_Local.MaxLightingTime=atoi(string);

 if (sSector_State_Local.BaseLighting>255)
 {
  MessageBox("Базовая освещённость не должна быть больще 255!","Ошибка",MB_OK);
  return;
 }
 sSector_State_Local.Antigravitation=false;
 if (((CButton*)GetDlgItem(IDC_CHECK_DIALOG_SETTINGS_ANTIGRAVITATION))->GetCheck()) sSector_State_Local.Antigravitation=true;

 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_SECTOR_LABEL))->GetWindowText(sSector_State_Local.Label,SECTOR_LABEL_SIZE);

 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_STATIC))->GetCheck()) sSector_State_Local.LightingMode=LIGHTING_MODE_STATIC;
 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_FLASH))->GetCheck()) sSector_State_Local.LightingMode=LIGHTING_MODE_FLASH;
 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_RANDOM_FLASH))->GetCheck()) sSector_State_Local.LightingMode=LIGHTING_MODE_RANDOM_FLASH;
 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_SETTINGS_SECTOR_LIGHTING_MODE_DAWNING_SUNDOWN))->GetCheck()) sSector_State_Local.LightingMode=LIGHTING_MODE_DAWNING_SUNDOWN;

 sSector_State_Current=sSector_State_Local;
 EndDialog(0);
}
//---------------------------------------------------------------------------
//выбрать верхнюю текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_ChangeTextureUp(void)
{
 CDialog_SelectTexture cDialog_SelectTexture((LPCSTR)IDD_DIALOG_SELECT_TEXTURE,this);
 cDialog_SelectTexture.SetSelectedTexture(sSector_State_Local.cTextureFollow_Up.vector_STexture[0].TextureIndex);
 if (cDialog_SelectTexture.DoModal()==0) sSector_State_Local.cTextureFollow_Up.vector_STexture[0].TextureIndex=cDialog_SelectTexture.GetSelectedTexture();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//выбрать нижнюю текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_ChangeTextureDown(void)
{
 CDialog_SelectTexture cDialog_SelectTexture((LPCSTR)IDD_DIALOG_SELECT_TEXTURE,this);
 cDialog_SelectTexture.SetSelectedTexture(sSector_State_Local.cTextureFollow_Down.vector_STexture[0].TextureIndex);
 if (cDialog_SelectTexture.DoModal()==0) sSector_State_Local.cTextureFollow_Down.vector_STexture[0].TextureIndex=cDialog_SelectTexture.GetSelectedTexture();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//задать анимацию верхней текстуры
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_ChangeTextureFollowUp(void)
{
 CDialog_TextureFollow cDialog_TextureFollow((LPCSTR)IDD_DIALOG_TEXTURE_FOLLOW,this);
 cDialog_TextureFollow.SetTextureFollow(sSector_State_Local.cTextureFollow_Up);
 if (cDialog_TextureFollow.DoModal()==0) sSector_State_Local.cTextureFollow_Up=cDialog_TextureFollow.GetTextureFollow();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//задать анимацию нижней текстуры
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_ChangeTextureFollowDown(void)
{
 CDialog_TextureFollow cDialog_TextureFollow((LPCSTR)IDD_DIALOG_TEXTURE_FOLLOW,this);
 cDialog_TextureFollow.SetTextureFollow(sSector_State_Local.cTextureFollow_Down);
 if (cDialog_TextureFollow.DoModal()==0) sSector_State_Local.cTextureFollow_Down=cDialog_TextureFollow.GetTextureFollow();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//скопировать текстуру потолка на пол
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_CopyFlowToFloor(void)
{
 sSector_State_Local.cTextureFollow_Down=sSector_State_Local.cTextureFollow_Up;
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//скопировать текстуру пола на потолок
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsSector::OnCommand_Button_CopyFloorToFlow(void)
{
 sSector_State_Local.cTextureFollow_Up=sSector_State_Local.cTextureFollow_Down;
 InvalidateRect(NULL,FALSE);
}
//-Новые функции класса------------------------------------------------------

//---------------------------------------------------------------------------
//получить параметры сектора
//---------------------------------------------------------------------------
SSector_State CDialog_SettingsSector::GetState(void)
{
 return(sSector_State_Current);
}
//---------------------------------------------------------------------------
//задать параметры сектора
//---------------------------------------------------------------------------
void CDialog_SettingsSector::SetState(const SSector_State &sSector_State)
{
 sSector_State_Current=sSector_State;
}


//---------------------------------------------------------------------------

