#include "cdialog_selecttexture.h"

extern CTexture cTexture;

//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CDialog_SelectTexture,CDialog)
 ON_WM_DESTROY()
 ON_WM_CLOSE()
 ON_WM_PAINT()
 ON_WM_VSCROLL()
 ON_WM_HSCROLL()
 ON_WM_LBUTTONUP()
 ON_COMMAND(IDC_BUTTON_DIALOG_SELECT_TEXTURE_CANCEL,OnCommand_Button_Cancel)
 ON_COMMAND(IDC_BUTTON_DIALOG_SELECT_TEXTURE_OK,OnCommand_Button_Ok)
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CDialog_SelectTexture::CDialog_SelectTexture(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{ 
 SelectedTexture=0;
}
//-Деструктор класса---------------------------------------------------------
CDialog_SelectTexture::~CDialog_SelectTexture()
{
}
//-Замещённые функции предка-------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnOK(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnCancel(void)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnClose(void)
{
 EndDialog(0);
}
//---------------------------------------------------------------------------
//инициализация диалога
//---------------------------------------------------------------------------
afx_msg BOOL CDialog_SelectTexture::OnInitDialog(void)
{ 
 long texture_amount=cTexture.GetTextureAmount();

 vPosMax=texture_amount/50-1;
 if (vPosMax<0) vPosMax=0;
 hPosMax=50-5;
 vPos=SelectedTexture/50;
 hPos=SelectedTexture-vPos*50;
 if (vPos>=vPosMax-1) vPos=vPosMax-1;
 if (vPos<0) vPos=0;
 if (hPos>=hPosMax-1) hPos=hPosMax-1;
 if (hPos<0) hPos=0;

 ((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_HORIZONTAL))->SetScrollRange(0,hPosMax-1,TRUE);
 ((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_HORIZONTAL))->SetScrollPos(hPos,TRUE);
 ((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_VERTICAL))->SetScrollRange(0,vPosMax-1,TRUE);
 ((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_VERTICAL))->SetScrollPos(vPos,TRUE);


 return(CDialog::OnInitDialog());
}
//-Новые функции класса------------------------------------------------------
//-Функции обработки сообщений класса----------------------------------------

//---------------------------------------------------------------------------
//событие уничтожения окна
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnDestroy(void)
{
 CDialog::OnDestroy();
}
//---------------------------------------------------------------------------
//событие отрисовки
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnPaint(void)
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
 long texture_amount=cTexture.GetTextureAmount();
 for(long x=0;x<5;x++)
 {
  for(long y=0;y<3;y++)
  {
   long index=hPos+x+(vPos+y)*50;
   long tms=128;
   STextureImage *sTextureImage_Ptr=cTexture.GetTextureImagePtr(index);
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
     if (SelectedTexture==index)
     {
      if (tx<8 || tx>=120 || ty<8 || ty>=120)
      {
       R=G^255;
       G=B^255;
       B=R^255;
      }
     }
     TextureMap[offset]=B;
     TextureMap[offset+1]=G;
     TextureMap[offset+2]=R; 
	 TextureMap[offset+3]=0;
    }
   }
   CRect cRect;
   cRect.left=4+x*64;
   cRect.right=cRect.left+64;
   cRect.top=4+y*64;
   cRect.bottom=cRect.top+64;
   MapDialogRect(&cRect);
   StretchDIBits(cPaintDC,cRect.left,cRect.top,cRect.right-cRect.left,cRect.bottom-cRect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
  }  
 }
}
//---------------------------------------------------------------------------
//перемещение горизонтального бегунка
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
 if (pScrollBar==((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_HORIZONTAL)))
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
   if (hPos>=hPosMax-1) hPos=hPosMax-1;
   if (hPos<0) hPos=0;
   ((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_HORIZONTAL))->SetScrollPos(hPos,TRUE);
   InvalidateRect(NULL,FALSE);
  }
 }
}
//---------------------------------------------------------------------------
//перемещение вертикального бегунка
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{	
 if (pScrollBar==((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_VERTICAL)))
 {
  bool move=false;
  if (nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK)
  {
   vPos=nPos;
   move=true;
  }
  if (nSBCode==SB_LINELEFT)
  {
   vPos--;
   move=true;
  }
  if (nSBCode==SB_LINERIGHT)
  {
   vPos++;
   move=true;
  }
  if (nSBCode==SB_PAGELEFT)
  {
   vPos-=3;
   move=true;
  }
  if (nSBCode==SB_PAGERIGHT)
  {
   vPos+=3;
   move=true;
  }
  if (move==true)
  {
   if (vPos>vPosMax-1) vPos=vPosMax-1;
   if (vPos<0) vPos=0;
   ((CScrollBar*)GetDlgItem(IDC_SCROLL_DIALOG_SELECT_TEXTURE_VERTICAL))->SetScrollPos(vPos,TRUE);
   InvalidateRect(NULL,FALSE);
  }
 }
}
//---------------------------------------------------------------------------
//отпускание левой кнопки мыши
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnLButtonUp(UINT nFlags,CPoint point)
{
 CRect cRect;
 cRect.left=4;
 cRect.right=cRect.left+64;
 cRect.top=4;
 cRect.bottom=cRect.top+64;
 MapDialogRect(&cRect);
 long MouseX=point.x-cRect.left;
 long MouseY=point.y-cRect.top;
 if (MouseX>=0 && MouseY>=0 && MouseX<=(cRect.right-cRect.left)*5 && MouseY<=(cRect.bottom-cRect.top)*3)
 {
  long x=MouseX/(cRect.right-cRect.left);
  long y=MouseY/(cRect.bottom-cRect.top);
  int st=x+hPos+(y+vPos)*50;
  long texture_amount=cTexture.GetTextureAmount();
  if (st<texture_amount)
  {
   SelectedTexture=st;
   InvalidateRect(NULL,FALSE);
  }
 }
}
//---------------------------------------------------------------------------
//отмена
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnCommand_Button_Cancel(void)
{
 EndDialog(1);
}
//---------------------------------------------------------------------------
//применить
//---------------------------------------------------------------------------
afx_msg void CDialog_SelectTexture::OnCommand_Button_Ok(void)
{ 
 EndDialog(0);
}
//-Новые функции класса------------------------------------------------------

//---------------------------------------------------------------------------
//установить выбранную текстуру
//---------------------------------------------------------------------------
void CDialog_SelectTexture::SetSelectedTexture(long index)
{ 
 long texture_amount=cTexture.GetTextureAmount();
 SelectedTexture=index;
 if (SelectedTexture<0) SelectedTexture=0;
 if (SelectedTexture>=texture_amount) SelectedTexture=texture_amount;
}
//---------------------------------------------------------------------------
//получить выбранную текстуру
//---------------------------------------------------------------------------
long CDialog_SelectTexture::GetSelectedTexture(void)
{ 
 return(SelectedTexture);
}
//---------------------------------------------------------------------------
