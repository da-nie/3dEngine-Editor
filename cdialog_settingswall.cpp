#include "cdialog_settingswall.h"

extern CTexture cTexture;

//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CDialog_SettingsWall,CDialog)
 ON_WM_DESTROY()
 ON_WM_CLOSE()
 ON_WM_PAINT()
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_CANCEL,OnCommand_Button_Cancel)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_OK,OnCommand_Button_Ok)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_CHANGETEXTURE_UP,OnCommand_Button_ChangeTextureUp)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_CHANGETEXTURE_DOWN,OnCommand_Button_ChangeTextureDown)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_ANIMATE_UP,OnCommand_Button_ChangeTextureFollowUp)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_ANIMATE_DOWN,OnCommand_Button_ChangeTextureFollowDown)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_COPY_TO_DOWN,OnCommand_Button_CopyUpToDown)
 ON_COMMAND(IDC_BUTTON_DIALOG_SETTINGS_WALL_COPY_TO_UP,OnCommand_Button_CopyDownToUp)
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CDialog_SettingsWall::CDialog_SettingsWall(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{ 
 STexture sTexture;
 sTexture.TextureIndex=0;
 sWall_State_Current.cTextureFollow_Up.Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 sWall_State_Current.cTextureFollow_Up.vector_STexture.clear();
 sWall_State_Current.cTextureFollow_Up.vector_STexture.push_back(sTexture);

 sWall_State_Current.cTextureFollow_Down.Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 sWall_State_Current.cTextureFollow_Down.vector_STexture.clear();
 sWall_State_Current.cTextureFollow_Down.vector_STexture.push_back(sTexture);

 sWall_State_Current.Switch=false;
 strcpy(sWall_State_Current.SwitchLabel,"");

 sWall_State_Local=sWall_State_Current;
}
//-Деструктор класса---------------------------------------------------------
CDialog_SettingsWall::~CDialog_SettingsWall()
{
}
//-Замещённые функции предка-------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnOK(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCancel(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnClose(void)
{
 EndDialog(0);
}
//---------------------------------------------------------------------------
//инициализация диалога
//---------------------------------------------------------------------------
afx_msg BOOL CDialog_SettingsWall::OnInitDialog(void)
{
 sWall_State_Local=sWall_State_Current;
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_WALL_SWITCH_LABEL))->SetLimitText(SECTOR_LABEL_SIZE-1);
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_WALL_SWITCH_LABEL))->SetWindowText(sWall_State_Local.SwitchLabel);
 ((CButton*)GetDlgItem(IDC_CHECK_DIALOG_SETTINGS_WALL_SWITCH))->SetCheck(0);
 if (sWall_State_Current.Switch==true) ((CButton*)GetDlgItem(IDC_CHECK_DIALOG_SETTINGS_WALL_SWITCH))->SetCheck(1); 
 return(CDialog::OnInitDialog());
}
//-Новые функции класса------------------------------------------------------
//-Функции обработки сообщений класса----------------------------------------

//---------------------------------------------------------------------------
//событие уничтожения окна
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnDestroy(void)
{
 CDialog::OnDestroy();
}
//---------------------------------------------------------------------------
//событие отрисовки
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnPaint(void)
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
 cRect.left=4;
 cRect.right=cRect.left+64;
 cRect.top=4;
 cRect.bottom=cRect.top+64;
 MapDialogRect(&cRect);

 STextureImage *sTextureImage_Ptr=cTexture.GetTextureImagePtr(sWall_State_Local.cTextureFollow_Up.vector_STexture[0].TextureIndex);
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

 sTextureImage_Ptr=cTexture.GetTextureImagePtr(sWall_State_Local.cTextureFollow_Down.vector_STexture[0].TextureIndex);
 image=error;
 if (sTextureImage_Ptr!=NULL)
 {
  image=sTextureImage_Ptr->Image;
  bmih.biWidth=sTextureImage_Ptr->Size;
  bmih.biHeight=-sTextureImage_Ptr->Size;
 }
 cRect.left=84;
 cRect.right=cRect.left+64;
 cRect.top=4;
 cRect.bottom=cRect.top+64;
 MapDialogRect(&cRect);
 StretchDIBits(cPaintDC,cRect.left,cRect.top,cRect.right-cRect.left,cRect.bottom-cRect.top,0,0,abs(bmih.biWidth),abs(bmih.biHeight),image,&info,DIB_RGB_COLORS,SRCCOPY);
}
//---------------------------------------------------------------------------
//отмена
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_Cancel(void)
{
 EndDialog(0);
}
//---------------------------------------------------------------------------
//применить
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_Ok(void)
{
 sWall_State_Local.Switch=false;
 if (((CButton*)GetDlgItem(IDC_CHECK_DIALOG_SETTINGS_WALL_SWITCH))->GetCheck()) 
 {
  sWall_State_Local.Switch=true;
 }
 ((CEdit*)GetDlgItem(IDC_EDIT_DIALOG_SETTINGS_WALL_SWITCH_LABEL))->GetWindowText(sWall_State_Local.SwitchLabel,SECTOR_LABEL_SIZE);
 sWall_State_Current=sWall_State_Local;
 EndDialog(0);
}
//---------------------------------------------------------------------------
//выбрать верхнюю текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_ChangeTextureUp(void)
{
 CDialog_SelectTexture cDialog_SelectTexture((LPCSTR)IDD_DIALOG_SELECT_TEXTURE,this);
 cDialog_SelectTexture.SetSelectedTexture(sWall_State_Local.cTextureFollow_Up.vector_STexture[0].TextureIndex);
 if (cDialog_SelectTexture.DoModal()==0) sWall_State_Local.cTextureFollow_Up.vector_STexture[0].TextureIndex=cDialog_SelectTexture.GetSelectedTexture();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//выбрать нижнюю текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_ChangeTextureDown(void)
{
 CDialog_SelectTexture cDialog_SelectTexture((LPCSTR)IDD_DIALOG_SELECT_TEXTURE,this);
 cDialog_SelectTexture.SetSelectedTexture(sWall_State_Local.cTextureFollow_Down.vector_STexture[0].TextureIndex);
 if (cDialog_SelectTexture.DoModal()==0) sWall_State_Local.cTextureFollow_Down.vector_STexture[0].TextureIndex=cDialog_SelectTexture.GetSelectedTexture();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//задать анимацию верхней текстуры
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_ChangeTextureFollowUp(void)
{
 CDialog_TextureFollow cDialog_TextureFollow((LPCSTR)IDD_DIALOG_TEXTURE_FOLLOW,this);
 cDialog_TextureFollow.SetTextureFollow(sWall_State_Local.cTextureFollow_Up);
 if (cDialog_TextureFollow.DoModal()==0) sWall_State_Local.cTextureFollow_Up=cDialog_TextureFollow.GetTextureFollow();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//задать анимацию нижней текстуры
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_ChangeTextureFollowDown(void)
{
 CDialog_TextureFollow cDialog_TextureFollow((LPCSTR)IDD_DIALOG_TEXTURE_FOLLOW,this);
 cDialog_TextureFollow.SetTextureFollow(sWall_State_Local.cTextureFollow_Down);
 if (cDialog_TextureFollow.DoModal()==0) sWall_State_Local.cTextureFollow_Down=cDialog_TextureFollow.GetTextureFollow();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//скопировать верхнюю текстуру в нижнюю
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_CopyUpToDown(void)
{
 sWall_State_Local.cTextureFollow_Down=sWall_State_Local.cTextureFollow_Up;
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//скопировать нижнюю текстуру в верхнюю
//---------------------------------------------------------------------------
afx_msg void CDialog_SettingsWall::OnCommand_Button_CopyDownToUp(void)
{
 sWall_State_Local.cTextureFollow_Up=sWall_State_Local.cTextureFollow_Down;
 InvalidateRect(NULL,FALSE);
}
//-Новые функции класса------------------------------------------------------

//---------------------------------------------------------------------------
//получить параметры стены
//---------------------------------------------------------------------------
SWall_State CDialog_SettingsWall::GetState(void)
{
 return(sWall_State_Current);
}
//---------------------------------------------------------------------------
//задать параметры стены
//---------------------------------------------------------------------------
void CDialog_SettingsWall::SetState(const SWall_State &sWall_State)
{
 sWall_State_Current=sWall_State;
}
//---------------------------------------------------------------------------

