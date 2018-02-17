#include "cview_map.h"

//-������� ��������� ��������� ������--------------------------------------
BEGIN_MESSAGE_MAP(CView_Map,CView)
 ON_COMMAND(ID_BUTTON_TOOLBAR_VIEW_SCALE_PLUS,OnButton_ToolBar_View_ScalePlus)
 ON_COMMAND(ID_BUTTON_TOOLBAR_VIEW_SCALE_MINUS,OnButton_ToolBar_View_ScaleMinus)
 ON_COMMAND(ID_BUTTON_TOOLBAR_VIEW_BINDING,OnButton_ToolBar_View_Binding)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_CREATE_WALL,OnButton_ToolbarMain_CreateWall)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_CREATE_FRONTIER,OnButton_ToolbarMain_CreateFrontier)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_CREATE_SECTOR,OnButton_ToolbarMain_CreateSector)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_WALL_SELECT,OnButton_ToolbarMain_WallSelect)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_FRONTIER_SELECT,OnButton_ToolbarMain_FrontierSelect)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_SECTOR_SELECT,OnButton_ToolbarMain_SectorSelect)
 ON_COMMAND(ID_BUTTON_TOOLBAR_MAIN_SET_PLAYER_POSITION,OnButton_ToolbarMain_SetPlayerPosition)
 ON_COMMAND(IDC_BUTTON_DIALOGBAR_CONTROL_DELETE,OnButton_DialogbarControl_Delete)
 ON_COMMAND(IDC_BUTTON_DIALOGBAR_CONTROL_EDIT,OnButton_DialogbarControl_Edit)
 ON_COMMAND(IDC_BUTTON_DIALOGBAR_CONTROL_WALL_SETTINGS,OnButton_DialogbarControl_WallSettings)
 ON_COMMAND(IDC_BUTTON_DIALOGBAR_CONTROL_SECTOR_SETTINGS,OnButton_DialogbarControl_SectorSettings)
 ON_WM_ERASEBKGND()
 ON_WM_RBUTTONDOWN()
 ON_WM_RBUTTONUP()
 ON_WM_LBUTTONDOWN()
 ON_WM_LBUTTONUP()
 ON_WM_MOUSEMOVE()
 ON_WM_TIMER()
 ON_WM_DESTROY()
END_MESSAGE_MAP()
//-����������� ������--------------------------------------------------------
CView_Map::CView_Map() 
{
 LeftUpAngle_X=0;
 LeftUpAngle_Y=0;
 GridSize=10;
 Increase=1;
 ViewMode=0;
 Binding=false;
 CurrentMode=WORKING_MODE_NONE;
 cDialog_SettingsWall_Ptr=NULL;
 cDialog_SettingsSector_Ptr=NULL;
}
//-���������� ������---------------------------------------------------------
//-������� ������------------------------------------------------------------

//---------------------------------------------------------------------------
//������������� ����
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnInitialUpdate(void)
{
 CView::OnInitialUpdate();
 //������ ������ ��������� ����
 cDialog_SettingsWall_Ptr=new CDialog_SettingsWall((LPCSTR)IDD_DIALOG_SETTINGS_WALL,this); 
 //������ ������ ��������� ��������
 cDialog_SettingsSector_Ptr=new CDialog_SettingsSector((LPCSTR)IDD_DIALOG_SETTINGS_SECTOR,this); 
 SetTimer(IDR_TIMER_MAP,1,0);
}
//---------------------------------------------------------------------------
//�������� ��������
//---------------------------------------------------------------------------
CDocument_Map* CView_Map::GetDocument()
{
 ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));// ��������� ���� �� ����� ���������
 return( reinterpret_cast<CDocument_Map*>(m_pDocument));//���������� ��������� �� ��������
}
//---------------------------------------------------------------------------
//������� ���������� ����
//---------------------------------------------------------------------------
void CView_Map::OnDraw(CDC* pDC)
{
 //������� ����
 CDC cDC_Mem;
 cDC_Mem.CreateCompatibleDC(pDC);
 CRect cRect;
 GetClientRect(&cRect);
 CBitmap cBitmap;
 cDC_Mem.SetMapMode(MM_TEXT);
 cBitmap.CreateCompatibleBitmap(pDC,cRect.right,cRect.bottom);
 cDC_Mem.SelectObject(&cBitmap);
 //������� �������
 CBrush cBrush;
 cBrush.CreateSolidBrush(RGB(255,255,255));
 cDC_Mem.FillRect(&cRect,&cBrush);
 cBrush.DeleteObject();
 //������ ����� ��������
 //�������� �����
 DrawGrid(&cDC_Mem);
 //�������� �������
 DrawSectors(&cDC_Mem);
 //�������� ��������
 DrawWalls(&cDC_Mem);
 //�������� ��������� �����
 DrawBinding(&cDC_Mem);
 //�������� ���
 DrawAxes(&cDC_Mem);
 //�������� ��������� ������
 DrawPlayerPosition(&cDC_Mem);
 //������� �������
 pDC->BitBlt(0,0,cRect.right,cRect.bottom,&cDC_Mem,0,0,SRCCOPY);
 cDC_Mem.DeleteDC(); 
}
//---------------------------------------------------------------------------
//���������� �����
//---------------------------------------------------------------------------
void CView_Map::DrawGrid(CDC *pDC)
{
 //�������� ����������� ������ ����� 
 float dp=GridSize*Increase;
 if (dp<=2) return;//����� �� ����� 

 CRect cRect;
 GetClientRect(&cRect);
 long grid_x_left=(long)(LeftUpAngle_X/GridSize)-1;
 long grid_x_right=(long)(LeftUpAngle_X+(cRect.right-cRect.left)/Increase)/GridSize+1;

 long grid_y_top=(long)(LeftUpAngle_Y/GridSize)-1;
 long grid_y_bottom=(long)(LeftUpAngle_Y+(cRect.bottom-cRect.top)/Increase)/GridSize+1;

 HPEN hPen1,hPen2,hOldPen;
 hPen1=CreatePen(PS_SOLID,1,RGB(230,230,230));
 hPen2=CreatePen(PS_SOLID,1,RGB(192,192,192));
 hOldPen=(HPEN)pDC->SelectObject((HPEN)hPen1);
 for(long x=grid_x_left;x<=grid_x_right;x++)
 {
  if (x%5!=0) pDC->SelectObject((HPEN)hPen1);
         else pDC->SelectObject((HPEN)hPen2);
  pDC->MoveTo(CPoint((long)((x*GridSize-LeftUpAngle_X)*Increase),cRect.top));
  pDC->LineTo((long)((x*GridSize-LeftUpAngle_X)*Increase),cRect.bottom);   
 }
 for(long y=grid_y_top;y<=grid_y_bottom;y++)
 {
  if (y%5!=0) pDC->SelectObject((HPEN)hPen1);
         else pDC->SelectObject((HPEN)hPen2);
  pDC->MoveTo(CPoint(cRect.left,(long)(cRect.bottom-(y*GridSize-LeftUpAngle_Y)*Increase)));
  pDC->LineTo(cRect.right,(long)(cRect.bottom-(y*GridSize-LeftUpAngle_Y)*Increase));   
 }
 pDC->SelectObject((HPEN)hOldPen);
 DeleteObject(hPen1);
 DeleteObject(hPen2);
}
//---------------------------------------------------------------------------
//���������� ��������� ������
//---------------------------------------------------------------------------
void CView_Map::DrawPlayerPosition(CDC *pDC)
{
 CRect cRect;
 GetClientRect(&cRect);
 //������ ���������� ���� ������
 long x_left=(long)(LeftUpAngle_X-GridSize);
 long x_right=(long)(LeftUpAngle_X+(cRect.right-cRect.left)/Increase)+GridSize;

 long y_top=(long)(LeftUpAngle_Y-GridSize);
 long y_bottom=(long)(LeftUpAngle_Y+(cRect.bottom-cRect.top)/Increase)+GridSize;
 //������ ����
 HPEN hPen,hOldPen;
 hPen=CreatePen(PS_SOLID,2,RGB(255,0,255));
 hOldPen=(HPEN)pDC->SelectObject((HPEN)hPen);
 HBRUSH hOldBrush,hBrush;
 hBrush=CreateSolidBrush(RGB(255,0,255));
 hOldBrush=(HBRUSH)pDC->SelectObject((HBRUSH)hBrush);
 //�������� ��������
 CDocument_Map *cDocument_MapPtr=GetDocument();
 //����������� ���������� ������
 long PlayerX;
 long PlayerY;
 cDocument_MapPtr->GetPlayerPosition(PlayerX,PlayerY);
 //������� ���������� ����� �������
 long sx=(long)((PlayerX-LeftUpAngle_X)*Increase);
 long sy=(long)(cRect.bottom-(PlayerY-LeftUpAngle_Y)*Increase);
 //������ �������
 pDC->Ellipse(sx-5,sy-5,sx+5,sy+5);
 pDC->SelectObject((HPEN)hOldPen);
 pDC->SelectObject((HBRUSH)hOldBrush);
 DeleteObject(hBrush);
 DeleteObject(hPen);
}
//---------------------------------------------------------------------------
//���������� ���
//---------------------------------------------------------------------------
void CView_Map::DrawAxes(CDC *pDC)
{
 CRect cRect;
 GetClientRect(&cRect);
 HPEN hPen,hOldPen;
 hPen=CreatePen(PS_SOLID,2,RGB(0,0,255));
 hOldPen=(HPEN)pDC->SelectObject((HPEN)hPen);
 pDC->MoveTo(CPoint(cRect.left+5,cRect.top+5));
 pDC->LineTo(cRect.left+5,cRect.bottom-5);   
 pDC->MoveTo(CPoint(cRect.left+5,cRect.top+5));
 pDC->LineTo(cRect.left,cRect.top+10);   
 pDC->MoveTo(CPoint(cRect.left+5,cRect.top+5));
 pDC->LineTo(cRect.left+10,cRect.top+10);   
 pDC->MoveTo(CPoint(cRect.right-5,cRect.bottom-5));
 pDC->LineTo(cRect.left+5,cRect.bottom-5);   
 pDC->MoveTo(CPoint(cRect.right-5,cRect.bottom-5));
 pDC->LineTo(cRect.right-10,cRect.bottom);   
 pDC->MoveTo(CPoint(cRect.right-5,cRect.bottom-5));
 pDC->LineTo(cRect.right-10,cRect.bottom-10);   
 pDC->SelectObject((HPEN)hOldPen);
 DeleteObject(hPen);

 LOGFONT lf;
 lf.lfHeight=24; 
 lf.lfWidth=0; 
 lf.lfEscapement=0;
 lf.lfOrientation=0; 
 lf.lfWeight=FW_NORMAL; 
 lf.lfItalic=0;
 lf.lfUnderline=0; 
 lf.lfStrikeOut=0; 
 lf.lfCharSet=DEFAULT_CHARSET; 
 lf.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 lf.lfQuality=DEFAULT_QUALITY; 
 lf.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(lf.lfFaceName,"Times New Roman"); 
 CFont ft;
 ft.CreateFontIndirect(&lf);
 CFont* oldf=pDC->SelectObject(&ft);
 pDC->SetTextColor(RGB(0,127,255));
 long oldbkmode=pDC->SetBkMode(TRANSPARENT);
 pDC->TextOut(cRect.left+12,cRect.top+5,"Y");
 SIZE Size;
 GetTextExtentPoint32(pDC->m_hDC,"X",1,&Size);
 pDC->TextOut(cRect.right-Size.cx-6,cRect.bottom-11-Size.cy,"X");
 pDC->SelectObject(oldf);
 ft.DeleteObject();
 pDC->SetBkMode(oldbkmode);
}
//---------------------------------------------------------------------------
//���������� ��������
//---------------------------------------------------------------------------
void CView_Map::DrawBinding(CDC *pDC)
{
 if (Binding==false || ViewMode==1) return;
 CRect cRect;
 GetClientRect(&cRect);
 //������ �������� ����������
 long sx=(long)((NearestPoint.x-LeftUpAngle_X)*Increase);
 long sy=(long)(cRect.bottom-(NearestPoint.y-LeftUpAngle_Y)*Increase);

 HPEN hPen,hOldPen;
 hPen=CreatePen(PS_SOLID,1,RGB(0,0,255));
 hOldPen=(HPEN)pDC->SelectObject((HPEN)hPen);
 
 pDC->MoveTo(CPoint(sx-5,sy-5));
 pDC->LineTo(CPoint(sx+5,sy+5));
 pDC->MoveTo(CPoint(sx-5,sy+5));
 pDC->LineTo(CPoint(sx+5,sy-5));

 pDC->SelectObject((HPEN)hOldPen);
 DeleteObject(hPen);
}
//---------------------------------------------------------------------------
//���������� ��������
//---------------------------------------------------------------------------
void CView_Map::DrawWalls(CDC *pDC)
{
 CRect cRect;
 GetClientRect(&cRect);
 //������ ���������� ���� ������
 long x_left=(long)(LeftUpAngle_X-GridSize);
 long x_right=(long)(LeftUpAngle_X+(cRect.right-cRect.left)/Increase)+GridSize;

 long y_top=(long)(LeftUpAngle_Y-GridSize);
 long y_bottom=(long)(LeftUpAngle_Y+(cRect.bottom-cRect.top)/Increase)+GridSize;
 //������ ����� ������ ������
 HPEN hPen_NoFrontier,hPen_Frontier,hPen_Select,hOldPen,hPen_Create;
 hPen_NoFrontier=CreatePen(PS_SOLID,2,RGB(0,0,0));
 hPen_Frontier=CreatePen(PS_SOLID,2,RGB(0,0,255));
 hPen_Select=CreatePen(PS_SOLID,2,RGB(255,0,0));
 hPen_Create=CreatePen(PS_SOLID,2,RGB(0,127,255));
 hOldPen=(HPEN)pDC->SelectObject((HPEN)hPen_NoFrontier);
 //�������� ��������
 CDocument_Map *cDocument_MapPtr=GetDocument();
 //�������� ��������� �� ��������� ���� 
 vector<CWall> *vector_CWallPtr=cDocument_MapPtr->GetVector_CWallPtr();
 //������� ��� �������� � ������� �� �� �����
 long size=vector_CWallPtr->size();
 for(long n=0;n<size;n++)
 { 
  CWall *cWallPtr=&(*vector_CWallPtr)[n];
  //�������� ��������� �����
  if ((cWallPtr->X1<x_left && cWallPtr->X2<x_left) || (cWallPtr->X1>x_right && cWallPtr->X2>x_right)) continue;
  if ((cWallPtr->Y1<y_top && cWallPtr->Y2<y_top) || (cWallPtr->Y1>y_bottom && cWallPtr->Y2>y_bottom)) continue;
  //������ �����
  long sx1=(long)((cWallPtr->X1-LeftUpAngle_X)*Increase);
  long sy1=(long)(cRect.bottom-(cWallPtr->Y1-LeftUpAngle_Y)*Increase);
  long sx2=(long)((cWallPtr->X2-LeftUpAngle_X)*Increase);
  long sy2=(long)(cRect.bottom-(cWallPtr->Y2-LeftUpAngle_Y)*Increase);  
  if (cWallPtr->Frontier==false) pDC->SelectObject((HPEN)hPen_NoFrontier); 
                            else pDC->SelectObject((HPEN)hPen_Frontier); 
  if (cWallPtr->Select==true) pDC->SelectObject((HPEN)hPen_Select); 
  pDC->MoveTo(CPoint(sx1,sy1));
  pDC->LineTo(CPoint(sx2,sy2));
 }
 //������ ������� ����������� �����
 if (CurrentMode==WORKING_MODE_CREATE_WALL || CurrentMode==WORKING_MODE_CREATE_FRONTIER)//���� ����� �������� ��������� ��� ����� �������
 {
  if (cDocument_MapPtr->GetCurrentPoint()==1)//��� ������� ������ ����� �����, ������ ��� �� ������� �����
  {
   CWall *cWallPtr=cDocument_MapPtr->GetCurrentWall();

   long sx1=(long)((cWallPtr->X1-LeftUpAngle_X)*Increase);
   long sy1=(long)(cRect.bottom-(cWallPtr->Y1-LeftUpAngle_Y)*Increase);
   long sx2=(long)((NearestPoint.x-LeftUpAngle_X)*Increase);
   long sy2=(long)(cRect.bottom-(NearestPoint.y-LeftUpAngle_Y)*Increase);  
   pDC->SelectObject((HPEN)hPen_Create); 
   pDC->MoveTo(CPoint(sx1,sy1));
   pDC->LineTo(CPoint(sx2,sy2));
  }
 }
 pDC->SelectObject((HPEN)hOldPen);
 DeleteObject(hPen_NoFrontier);
 DeleteObject(hPen_Frontier);
 DeleteObject(hPen_Select);
 DeleteObject(hPen_Create);
}
//---------------------------------------------------------------------------
//���������� �������
//---------------------------------------------------------------------------
void CView_Map::DrawSectors(CDC *pDC)
{
 long m;
 CRect cRect;
 GetClientRect(&cRect);
 //������ ���������� ���� ������
 long x_left=(long)(LeftUpAngle_X-GridSize);
 long x_right=(long)(LeftUpAngle_X+(cRect.right-cRect.left)/Increase)+GridSize;

 long y_top=(long)(LeftUpAngle_Y-GridSize);
 long y_bottom=(long)(LeftUpAngle_Y+(cRect.bottom-cRect.top)/Increase)+GridSize;
 //������ ����� ������ ������
 HPEN hPen,hPen_Select,hOldPen,hPen_Create;
 hPen=CreatePen(PS_SOLID,2,RGB(0,255,0));
 hPen_Select=CreatePen(PS_SOLID,2,RGB(255,0,0));
 hPen_Create=CreatePen(PS_SOLID,2,RGB(0,127,255));
 hOldPen=(HPEN)pDC->SelectObject((HPEN)hPen);
 HBRUSH hOldBrush,hBrush_Select,hBrush;
 hBrush=CreateHatchBrush(HS_CROSS,RGB(0,255,0));
 hBrush_Select=CreateHatchBrush(HS_CROSS,RGB(255,0,0)); 
 hOldBrush=(HBRUSH)pDC->SelectObject((HBRUSH)hBrush);
 //�������� ��������
 CDocument_Map *cDocument_MapPtr=GetDocument();
 //�������� ��������� �� ��������� ����
 vector<CSector> *vector_CSectorPtr=cDocument_MapPtr->GetVector_CSectorPtr();
 //������� ��� ������� � ������� �� �� �����
 long size=vector_CSectorPtr->size();
 for(long n=0;n<size;n++)
 { 
  CSector *cSectorPtr=&(*vector_CSectorPtr)[n];
  //�������� ������ ������ �������
  long size_point=(*cSectorPtr).vector_SSectorPoint.size();
  //��������� ��������� �������
  bool visible=false;
  //���������, ��� ������ �� ������
  for(m=0;m<size_point;m++)
  {
   if ((*cSectorPtr).vector_SSectorPoint[m].X>x_left)
   {
    visible=true;
	break;
   }     
  }
  if (visible==false) continue;//������ �������
  //���������, ��� ������ �� �����
  visible=false;
  for(m=0;m<size_point;m++)
  {
   if ((*cSectorPtr).vector_SSectorPoint[m].X<x_right)
   {
    visible=true;
	break;
   }  
  }
  if (visible==false) continue;//������ �������
  //���������, ��� ������ �� ������
  visible=false;
  for(m=0;m<size_point;m++)
  {
   if ((*cSectorPtr).vector_SSectorPoint[m].Y>y_top)
   {
    visible=true;
	break;
   }  
  }
  if (visible==false) continue;//������ �������
  //���������, ��� ������ �� �����
  visible=false;
  for(m=0;m<size_point;m++)
  {
   if ((*cSectorPtr).vector_SSectorPoint[m].Y<y_bottom)
   {
    visible=true;
	break;
   }  
  }
  if (visible==false) continue;//������ �������
  //������ �����
  if (cSectorPtr->Select==true)
  {
   pDC->SelectObject((HPEN)hPen_Select);
   pDC->SelectObject((HBRUSH)hBrush_Select);
  }
  else
  {
   pDC->SelectObject((HPEN)hPen);
   pDC->SelectObject((HBRUSH)hBrush);
  }
  //������� ���������� ����� �������
  POINT *Point=new POINT[size_point+1];
  //��������� ����� � ������
  for(m=0;m<size_point;m++)
  {
   long sx=(long)(((*cSectorPtr).vector_SSectorPoint[m].X-LeftUpAngle_X)*Increase);
   long sy=(long)(cRect.bottom-((*cSectorPtr).vector_SSectorPoint[m].Y-LeftUpAngle_Y)*Increase);
   Point[m].x=sx;
   Point[m].y=sy;
  }
  //������ �������
  pDC->Polygon(Point,size_point);
  delete[](Point);
 }
 //������ ������� ����������� �������
 if (CurrentMode==WORKING_MODE_CREATE_SECTOR)//���� ����� �������� ��������
 {
  pDC->SelectObject((HPEN)hPen_Create);  
  CSector *cSectorPtr=cDocument_MapPtr->GetCurrentSector();
  //�������� ������ ������ �������
  long size_point=cSectorPtr->vector_SSectorPoint.size();
  //��������� ������� � ������ �����
  if (size_point!=0)
  {
   long sx=(long)((cSectorPtr->vector_SSectorPoint[0].X-LeftUpAngle_X)*Increase);
   long sy=(long)(cRect.bottom-(cSectorPtr->vector_SSectorPoint[0].Y-LeftUpAngle_Y)*Increase);
   pDC->MoveTo(CPoint(sx,sy)); 
  }
  //������ ����� �� ��� ����������� �����
  for(m=1;m<size_point;m++)
  {
   long sx=(long)((cSectorPtr->vector_SSectorPoint[m].X-LeftUpAngle_X)*Increase);
   long sy=(long)(cRect.bottom-(cSectorPtr->vector_SSectorPoint[m].Y-LeftUpAngle_Y)*Increase);
   pDC->LineTo(CPoint(sx,sy));
  }
  if (size_point!=0)
  {
   //� ������ ����� � ������� �����
   long sx=(long)((NearestPoint.x-LeftUpAngle_X)*Increase);
   long sy=(long)(cRect.bottom-(NearestPoint.y-LeftUpAngle_Y)*Increase);
   pDC->LineTo(CPoint(sx,sy));
  }
 }
 pDC->SelectObject((HPEN)hOldPen);
 pDC->SelectObject((HBRUSH)hOldBrush);
 DeleteObject(hBrush);
 DeleteObject(hBrush_Select);
 DeleteObject(hPen);
 DeleteObject(hPen_Select);
 DeleteObject(hPen_Create);
}
//---------------------------------------------------------------------------
//���������� ��� �����
//---------------------------------------------------------------------------
void CView_Map::SetGridSize(long gridsize)
{
 GridSize=gridsize;
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//�������� ����
//---------------------------------------------------------------------------
void CView_Map::ClearMap(void)
{
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->DeleteAll();
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//��������� �����
//---------------------------------------------------------------------------
void CView_Map::LoadMap(FILE *file)
{
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->Load(file);
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//��������� �����
//---------------------------------------------------------------------------
void CView_Map::SaveMap(FILE *file)
{
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->Save(file);
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� ����� � BSP
//---------------------------------------------------------------------------
void CView_Map::ExportMapBSP(FILE *file)
{
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->ExportBSP(file);
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� ����� � PORTAL
//---------------------------------------------------------------------------
void CView_Map::ExportMapPORTAL(FILE *file)
{
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->ExportPORTAL(file);
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������ ����� �� ���������� �����
//---------------------------------------------------------------------------
void CView_Map::ImportMapFromTXT(FILE *file)
{
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->ImportMapFromTXT(file,cDialog_SettingsWall_Ptr,cDialog_SettingsSector_Ptr);
 tempDocument->UpdateAllViews(NULL);
}
//-������� ��������� ��������� ������----------------------------------------

//---------------------------------------------------------------------------
//������� ���������� ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolBar_View_ScalePlus(void)
{
 Increase=(float)(Increase*2.0);
 if (Increase>=32) Increase=32;//������ �����������
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� ���������� ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolBar_View_ScaleMinus(void)
{
 Increase=(float)(Increase/2.0);
 if (Increase<(float)1.0/65536.0) Increase=(float)1.0/65536.0;
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� ����� ����������� ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolBar_View_Binding(void)
{
 if (Binding==false) Binding=true;
                else Binding=false;
 CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
 tempDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� ����������� ����
//---------------------------------------------------------------------------
BOOL CView_Map::OnEraseBkgnd(CDC *pDC)
{
 return(TRUE);
}
//---------------------------------------------------------------------------
//������� ������� ������ ������ ����
//---------------------------------------------------------------------------
void CView_Map::OnRButtonDown(UINT nFlags,CPoint point)
{
 if (ViewMode!=0) return;
 ClientToScreen(&point);
 MouseOnePoint=point;
 ViewMode=1;
 while (ShowCursor(FALSE)>0); 
 //��������� ������ � ����
 CRect cRect;
 GetWindowRect(&cRect);
 ClipCursor(&cRect);
}
//---------------------------------------------------------------------------
//������� ���������� ������ ������ ����
//---------------------------------------------------------------------------
void CView_Map::OnRButtonUp(UINT nFlags,CPoint point)
{
 if (ViewMode==1)
 {
  ViewMode=0;
  while (ShowCursor(TRUE)<0);
  //������������ ������ � ����
  while(ClipCursor(NULL)<0);
  //������� ��������� ���������� ����
  OnMouseMove(nFlags,point);
 }
}
//---------------------------------------------------------------------------
//������� ������� ����� ������ ����
//---------------------------------------------------------------------------
void CView_Map::OnLButtonDown(UINT nFlags,CPoint point)
{
 if (CurrentMode==WORKING_MODE_NONE) return;//������ ������ �� ����
 //�������� ��������
 CDocument_Map *cDocument_MapPtr=GetDocument();
 //���������� ��������� ����� ������ �������������
 long nx=NearestPoint.x;
 long ny=NearestPoint.y;
 if (CurrentMode==WORKING_MODE_CREATE_WALL) cDocument_MapPtr->AddWallPoint(nx,ny,cDialog_SettingsWall_Ptr);//����� �������� ����
 if (CurrentMode==WORKING_MODE_CREATE_FRONTIER) cDocument_MapPtr->AddFrontierPoint(nx,ny,cDialog_SettingsWall_Ptr);//����� �������� ����-����� �������
 if (CurrentMode==WORKING_MODE_CREATE_SECTOR) cDocument_MapPtr->AddSectorPoint(nx,ny,cDialog_SettingsSector_Ptr);//����� �������� ��������
 if (CurrentMode==WORKING_MODE_WALL_SELECT) cDocument_MapPtr->WallSelect(nx,ny);//����� ������ ����
 if (CurrentMode==WORKING_MODE_FRONTIER_SELECT) cDocument_MapPtr->FrontierSelect(nx,ny);//����� ������ ����-����� �������
 if (CurrentMode==WORKING_MODE_SECTOR_SELECT) cDocument_MapPtr->SectorSelect(nx,ny);//����� ������ ��������
 if (CurrentMode==WORKING_MODE_SET_PLAYER_POSITION) cDocument_MapPtr->SetPlayerPosition(nx,ny);//����� ������� ��������� ������� ������
 cDocument_MapPtr->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� ���������� ����� ������ ����
//---------------------------------------------------------------------------
void CView_Map::OnLButtonUp(UINT nFlags,CPoint point)
{
 if (ViewMode==2)
 {
  //������������ ������ � ����
  while(ClipCursor(NULL)<0);
  ViewMode=0;
 }
}
//---------------------------------------------------------------------------
//������� ����������� �����
//---------------------------------------------------------------------------
void CView_Map::OnMouseMove(UINT nFlags,CPoint point)
{
 CRect cRect;
 GetClientRect(&cRect);
 //������� "�������" ���������� ����
 long mx=(long)(point.x/Increase+LeftUpAngle_X)/GridSize;
 long my=(long)((cRect.bottom-point.y)/Increase+LeftUpAngle_Y)/GridSize;
 //���������, � ����� ��������� ������ ���� ����� �����
 long mx_l=mx-1;
 long my_l=my-1;
 long mx_r=mx+1;
 long my_r=my+1;
 if (mx_l<0) mx_l=0;
 if (my_l<0) my_l=0;
 float currentdelta=1000000000;
 for(long x=mx_l;x<=mx_r;x++)
  for(long y=my_l;y<=my_r;y++)
  {
   float xs=(x*GridSize-LeftUpAngle_X)*Increase;
   float ys=cRect.bottom-(y*GridSize-LeftUpAngle_Y)*Increase;
   float delta=(xs-point.x)*(xs-point.x)+(ys-point.y)*(ys-point.y);
   if (currentdelta>delta)
   {
    currentdelta=delta;
	mx=x;
	my=y;
   }
  }  
 //�������� ��������
 CDocument_Map *cDocument_MapPtr=GetDocument();
 if ((NearestPoint.x!=mx*GridSize || NearestPoint.y!=my*GridSize) && ViewMode!=1)
 {
  NearestPoint.x=mx*GridSize;
  NearestPoint.y=my*GridSize;
  if (Binding==true || ViewMode==2 || CurrentMode==WORKING_MODE_CREATE_WALL || CurrentMode==WORKING_MODE_CREATE_FRONTIER || CurrentMode==WORKING_MODE_CREATE_SECTOR) cDocument_MapPtr->UpdateAllViews(NULL);//���������� ���
 }
 //������������� ���������� ������� � ����
 CFrameWnd_Main *cFrameWnd_Main=reinterpret_cast<CFrameWnd_Main*>(GetParentFrame());
 cFrameWnd_Main->SetCursorPos(mx*GridSize,my*GridSize);
}
//---------------------------------------------------------------------------
//������� �������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnTimer(UINT nIDEvent)
{
 if (nIDEvent!=IDR_TIMER_MAP) 
 {
  CView::OnTimer(nIDEvent);
  return;
 }
 if (ViewMode==1) 
 {
  POINT MousePos;
  GetCursorPos(&MousePos);
  float dx=(MousePos.x-MouseOnePoint.x)/Increase;
  float dy=(MousePos.y-MouseOnePoint.y)/Increase;
  LeftUpAngle_X+=dx;
  LeftUpAngle_Y-=dy;//�.�. ��� �������������
  if (LeftUpAngle_X<0) LeftUpAngle_X=0;
  if (LeftUpAngle_X>1000000) LeftUpAngle_X=1000000;
  if (LeftUpAngle_Y<0) LeftUpAngle_Y=0;
  if (LeftUpAngle_Y>1000000) LeftUpAngle_Y=1000000;
  CDocument_Map* tempDocument=GetDocument();//�������� ����� ���������
  tempDocument->UpdateAllViews(NULL);
  SetCursorPos(MouseOnePoint.x,MouseOnePoint.y);

  CRect cRect;
  GetClientRect(&cRect);
  //������� "�������" ���������� ����
  long mx=(long)(MousePos.x/Increase+LeftUpAngle_X)/GridSize;
  long my=(long)((cRect.bottom-MousePos.y)/Increase+LeftUpAngle_Y)/GridSize;
  if ((NearestPoint.x!=mx*GridSize || NearestPoint.y!=my*GridSize) && ViewMode!=1)
  {
   NearestPoint.x=mx*GridSize;
   NearestPoint.y=my*GridSize;
   if (Binding==true || ViewMode==2 || CurrentMode==WORKING_MODE_CREATE_WALL || CurrentMode==WORKING_MODE_CREATE_FRONTIER || CurrentMode==WORKING_MODE_CREATE_SECTOR) tempDocument->UpdateAllViews(NULL);//���������� ���
  }
  return;
 } 
}
//---------------------------------------------------------------------------
//������� ����������� ����
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnDestroy(void)
{
 KillTimer(IDR_TIMER_MAP);
 delete(cDialog_SettingsWall_Ptr);
 delete(cDialog_SettingsSector_Ptr);
}
//---------------------------------------------------------------------------
//������ ����� �������� ����
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_CreateWall(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint();
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_CREATE_WALL;
}
//---------------------------------------------------------------------------
//������ ����� �������� ����-����� �������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_CreateFrontier(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint();
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_CREATE_FRONTIER;
}
//---------------------------------------------------------------------------
//������ ����� �������� ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_CreateSector(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint(); 
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_CREATE_SECTOR;
}
//---------------------------------------------------------------------------
//������ ����� ������ ����
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_WallSelect(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint(); 
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_WALL_SELECT;
}
//---------------------------------------------------------------------------
//������ ����� ������ ����-����� �������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_FrontierSelect(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint(); 
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_FRONTIER_SELECT;
}
//---------------------------------------------------------------------------
//������ ����� ������ ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_SectorSelect(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint(); 
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_SECTOR_SELECT;
}
//---------------------------------------------------------------------------
//������ ����� ������� ��������� ��������� ������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_ToolbarMain_SetPlayerPosition(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->ResetCurrentPoint(); 
 cDocument_MapPtr->ResetSelect();
 cDocument_MapPtr->UpdateAllViews(NULL);
 CurrentMode=WORKING_MODE_SET_PLAYER_POSITION;
}
//---------------------------------------------------------------------------
//������� �������� ��������� ���������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_DialogbarControl_Delete(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->DeleteSelected();
 cDocument_MapPtr->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������� �������������� ���������� ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_DialogbarControl_Edit(void)
{
 CDocument_Map *cDocument_MapPtr=GetDocument();
 cDocument_MapPtr->EditSelected(cDialog_SettingsWall_Ptr,cDialog_SettingsSector_Ptr);
 cDocument_MapPtr->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
//������ ������ ��������� ����
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_DialogbarControl_WallSettings(void)
{
 cDialog_SettingsWall_Ptr->DoModal();
}
//---------------------------------------------------------------------------
//������ ������ ��������� ��������
//---------------------------------------------------------------------------
afx_msg void CView_Map::OnButton_DialogbarControl_SectorSettings(void)
{
 cDialog_SettingsSector_Ptr->DoModal();
}

//-������--------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CView_Map,CView)

