#include "cdialog_texturefollow.h"

extern CTexture cTexture;

//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CDialog_TextureFollow,CDialog)
 ON_WM_DESTROY()
 ON_WM_CLOSE()
 ON_WM_PAINT()
 ON_WM_HSCROLL()
 ON_COMMAND(IDC_BUTTON_DIALOG_TEXTURE_FOLLOW_CANCEL,OnCommand_Button_Cancel)
 ON_COMMAND(IDC_BUTTON_DIALOG_TEXTURE_FOLLOW_OK,OnCommand_Button_Ok)
 ON_COMMAND(IDC_BUTTON_DIALOG_TEXTURE_FOLLOW_ADD,OnCommand_Button_Add)
 ON_COMMAND(IDC_BUTTON_DIALOG_TEXTURE_FOLLOW_CLEAR,OnCommand_Button_Clear)
 ON_COMMAND(IDC_BUTTON_DIALOG_TEXTURE_FOLLOW_REPEAT,OnCommand_Button_Repeat)
 ON_COMMAND(IDC_BUTTON_DIALOG_TEXTURE_FOLLOW_DELETE,OnCommand_Button_Delete)
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CDialog_TextureFollow::CDialog_TextureFollow(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{ 
 cTextureFollow_Current.Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 //добавляем первую текстуру
 STexture sTexture;
 sTexture.TextureIndex=0;
 cTextureFollow_Current.vector_STexture.push_back(sTexture);

 cTextureFollow_Local=cTextureFollow_Current;
}
//-Деструктор класса---------------------------------------------------------
CDialog_TextureFollow::~CDialog_TextureFollow()
{
}
//-Замещённые функции предка-------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnOK(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCancel(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnClose(void)
{
 EndDialog(0);
}
//---------------------------------------------------------------------------
//инициализация диалога
//---------------------------------------------------------------------------
afx_msg BOOL CDialog_TextureFollow::OnInitDialog(void)
{ 
 cTextureFollow_Local=cTextureFollow_Current;
 UpdateScrollPos();
 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_DISABLE))->SetCheck(0);
 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_CYCLES))->SetCheck(0);
 ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_ZIGZAG))->SetCheck(0);
 if (cTextureFollow_Local.Mode==TEXTURE_FOLLOW_MODE_CYCLES) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_CYCLES))->SetCheck(1);
 if (cTextureFollow_Local.Mode==TEXTURE_FOLLOW_MODE_DISABLE) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_DISABLE))->SetCheck(1);
 if (cTextureFollow_Local.Mode==TEXTURE_FOLLOW_MODE_ZIGZAG) ((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_ZIGZAG))->SetCheck(1);
 return(CDialog::OnInitDialog());
}
//-Новые функции класса------------------------------------------------------
//-Функции обработки сообщений класса----------------------------------------

//---------------------------------------------------------------------------
//событие уничтожения окна
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnDestroy(void)
{
 CDialog::OnDestroy();
}
//---------------------------------------------------------------------------
//событие отрисовки
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnPaint(void)
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
 unsigned char TextureMap[128*128*4]; 
 for(long x=0;x<4;x++)
 {
  long t_index=-1;
  if (hPos+x<cTextureFollow_Local.vector_STexture.size()) t_index=cTextureFollow_Local.vector_STexture[hPos+x].TextureIndex;
  if (t_index>=0)//создаём текстуру
  {
   long tms=128;
   STextureImage *sTextureImage_Ptr=cTexture.GetTextureImagePtr(t_index);
   if (sTextureImage_Ptr!=NULL) tms=sTextureImage_Ptr->Size;//текстура есть
   float kx=(float)((float)tms/128.0);
   float ky=(float)((float)tms/128.0);
   float tmx=0;
   float tmy=0;
   for(long tx=0;tx<128;tx++,tmx=tmx+kx)
   {
    tmy=0;
    for(long ty=0;ty<128;ty++,tmy=tmy+ky)
    {
     long offset=(tx+ty*128)*4;
     long offset1=(tx+ty*tms)*4;
     unsigned char R=0;
     unsigned char G=0;
     unsigned char B=0;
     if (sTextureImage_Ptr!=NULL)
     {
      B=sTextureImage_Ptr->Image[offset1];
      G=sTextureImage_Ptr->Image[offset1+1];
      R=sTextureImage_Ptr->Image[offset1+2];
     }
     TextureMap[offset]=B;
     TextureMap[offset+1]=G;
     TextureMap[offset+2]=R; 
	 TextureMap[offset+3]=0;
    }
   }
  }
  else
  {
   for(long tx=0;tx<128;tx++)
   {
    for(long ty=0;ty<128;ty++)
    {
     long offset=(tx+(127-ty)*128)*4;
     TextureMap[offset]=0;
     TextureMap[offset+1]=0;
     TextureMap[offset+2]=0;
     TextureMap[offset+3]=0;
    }
   }
  }
  CRect cRect;
  cRect.left=8+x*64;
  cRect.right=cRect.left+64;
  cRect.top=8;
  cRect.bottom=cRect.top+64;
  MapDialogRect(&cRect);
  StretchDIBits(cPaintDC,cRect.left,cRect.top,cRect.right-cRect.left,cRect.bottom-cRect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 }
}
//---------------------------------------------------------------------------
//перемещение горизонтального бегунка
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
 if (pScrollBar==((CScrollBar*)GetDlgItem(IDC_SCROLLBAR_DIALOG_TEXTURE_FOLLOW_LIST)))
 {
  bool move=false;
  if (nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK)
  {
   hPos=nPos;
   move=true;
  }
  if (nSBCode==SB_LINERIGHT)
  {
   hPos++;
   move=true;
  }
  if (nSBCode==SB_LINELEFT)
  {
   hPos--;
   move=true;
  }
  if (nSBCode==SB_PAGELEFT)
  {
   hPos-=5;
   move=true;
  }
  if (nSBCode==SB_PAGERIGHT)
  {
   hPos+=5;
   move=true;
  }
  if (move==true)
  {
   long hPosMax=cTextureFollow_Local.vector_STexture.size()-1;
   if (hPosMax<0) hPosMax=0;
   if (hPos>=hPosMax-1) hPos=hPosMax-1;
   if (hPos<0) hPos=0;
   ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR_DIALOG_TEXTURE_FOLLOW_LIST))->SetScrollPos(hPos,TRUE);
   InvalidateRect(NULL,FALSE);
  }
 }
}
//---------------------------------------------------------------------------
//отмена
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCommand_Button_Cancel(void)
{
 EndDialog(1);
}
//---------------------------------------------------------------------------
//применить
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCommand_Button_Ok(void)
{ 
 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_CYCLES))->GetCheck()) cTextureFollow_Local.Mode=TEXTURE_FOLLOW_MODE_CYCLES;
 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_ZIGZAG))->GetCheck()) cTextureFollow_Local.Mode=TEXTURE_FOLLOW_MODE_ZIGZAG;
 if (((CButton*)GetDlgItem(IDC_RADIOBUTTON_DIALOG_TEXTURE_FOLLOW_DISABLE))->GetCheck()) cTextureFollow_Local.Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 cTextureFollow_Current=cTextureFollow_Local;
 EndDialog(0);
}
//---------------------------------------------------------------------------
//очистить список
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCommand_Button_Clear(void)
{
 //удаляем все текстуры, кроме первой
 while(1)
 {
  long size=cTextureFollow_Local.vector_STexture.size();
  if (size<=1) break;
  size--;
  cTextureFollow_Local.vector_STexture.erase(cTextureFollow_Local.vector_STexture.begin()+size); 
 }
 UpdateScrollPos();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//добавить текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCommand_Button_Add(void)
{
 STexture sTexture;
 CDialog_SelectTexture cDialog_SelectTexture((LPCSTR)IDD_DIALOG_SELECT_TEXTURE,this);
 long size=cTextureFollow_Local.vector_STexture.size();
 cDialog_SelectTexture.SetSelectedTexture(cTextureFollow_Local.vector_STexture[size-1].TextureIndex);
 if (cDialog_SelectTexture.DoModal()==0)
 {
  sTexture.TextureIndex=cDialog_SelectTexture.GetSelectedTexture();
  cTextureFollow_Local.vector_STexture.push_back(sTexture);
  UpdateScrollPos();
  InvalidateRect(NULL,FALSE);
 } 
}
//---------------------------------------------------------------------------
//удалить текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCommand_Button_Delete(void)
{
 long size=cTextureFollow_Local.vector_STexture.size();
 if (size<=1) return;//первую текстуру нельзя удалять
 size--;
 cTextureFollow_Local.vector_STexture.erase(cTextureFollow_Local.vector_STexture.begin()+size); 
 UpdateScrollPos();
 InvalidateRect(NULL,FALSE);
}
//---------------------------------------------------------------------------
//повторить текстуру
//---------------------------------------------------------------------------
afx_msg void CDialog_TextureFollow::OnCommand_Button_Repeat(void)
{
 long size=cTextureFollow_Local.vector_STexture.size();
 size--;
 STexture sTexture=cTextureFollow_Local.vector_STexture[size];
 cTextureFollow_Local.vector_STexture.push_back(sTexture);
 UpdateScrollPos();
 InvalidateRect(NULL,FALSE);
}

//-Новые функции класса------------------------------------------------------
//---------------------------------------------------------------------------
//установить выбранную анимацию текстуры
//---------------------------------------------------------------------------
void CDialog_TextureFollow::SetTextureFollow(const CTextureFollow &cTextureFollowSet)
{ 
 cTextureFollow_Current=cTextureFollowSet;
}
//---------------------------------------------------------------------------
//получить выбранную анимацию текстуры
//---------------------------------------------------------------------------
CTextureFollow CDialog_TextureFollow::GetTextureFollow(void)
{ 
 return(cTextureFollow_Current);
}

//---------------------------------------------------------------------------
//обновить позицию бегунка
//---------------------------------------------------------------------------
void CDialog_TextureFollow::UpdateScrollPos(void)
{
 long hPosMax=cTextureFollow_Local.vector_STexture.size()-1;
 if (hPosMax<0) hPosMax=0;
 ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR_DIALOG_TEXTURE_FOLLOW_LIST))->SetScrollRange(0,hPosMax,TRUE);
 hPos=hPosMax-2;
 if (hPos<0) hPos=0;
 ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR_DIALOG_TEXTURE_FOLLOW_LIST))->SetScrollPos(hPos,TRUE);
}

//---------------------------------------------------------------------------
