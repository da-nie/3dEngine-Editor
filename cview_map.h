#ifndef C_VIEW_MAP_H
#define C_VIEW_MAP_H

#include "stdafx.h"
#include "cdocument_map.h"
#include "cframewnd_main.h"
#include "cdialog_settingswall.h"
#include "cdialog_settingssector.h"

//������� ����� ������
enum WORKING_MODE
{
 //����� ����������
 WORKING_MODE_NONE,
 //����� �������� ���������
 WORKING_MODE_CREATE_WALL,
 //����� �������� ����� �������
 WORKING_MODE_CREATE_FRONTIER,
 //����� �������� ��������
 WORKING_MODE_CREATE_SECTOR,
 //����� ������ ���������
 WORKING_MODE_WALL_SELECT,
 //����� ������ ����� �������
 WORKING_MODE_FRONTIER_SELECT,
 //����� ������ ��������
 WORKING_MODE_SECTOR_SELECT,
 //����� ������� ��������� ������� ������
 WORKING_MODE_SET_PLAYER_POSITION
};

//---------------------------------------------------------------------------
//����� �������������
//---------------------------------------------------------------------------
class CView_Map:public CView
{
 protected: 
  //-���������� ������-------------------------------------------------------
  //��������� ����
  float LeftUpAngle_X;//���������� ������ �������� ���� �����
  float LeftUpAngle_Y;
  long GridSize;//��� �����
  float Increase;//����������� ����������
  //��������� ��������� ����
  bool Binding;//true-���������� ��������� �����
  //��������������� ���������
  long ViewMode;//����� ������ �������������(0-�����, 1-������� �����)
  POINT MouseOnePoint;//���������� ����, ������� ���� ����� �� ������ ������� �����
  POINT NearestPoint;//���������� ��������� ����� ��� ����

  WORKING_MODE CurrentMode;//������� ����� ������
  CDialog_SettingsWall *cDialog_SettingsWall_Ptr;//��������� �� ������ ��������� ����
  CDialog_SettingsSector *cDialog_SettingsSector_Ptr;//��������� �� ������ ��������� ��������
  //-������� ������----------------------------------------------------------
  CDocument_Map* GetDocument();//�������� ��������
  afx_msg void OnInitialUpdate(void);//������������� ����
  void DrawGrid(CDC *pDC);//���������� �����
  void DrawPlayerPosition(CDC *pDC);//���������� ��������� ������
  void DrawAxes(CDC *pDC);//���������� ���
  void DrawBinding(CDC *pDC);//���������� ��������
  void DrawWalls(CDC *pDC);//���������� �����
  void DrawSectors(CDC *pDC);//���������� �������
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CView_Map();
  //-���������� ������-------------------------------------------------------
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  void SetGridSize(long gridsize);//���������� ��� �����
  void ClearMap(void);//�������� ����
  void LoadMap(FILE *file);//��������� �����
  void SaveMap(FILE *file);//��������� �����
  void ExportMapBSP(FILE *file);//������� ����� � BSP
  void ExportMapPORTAL(FILE *file);//������� ����� � PORTAL
  void ImportMapFromTXT(FILE *file);//������ ����� �� ���������� �����
 protected:
  virtual void OnDraw(CDC* pDC);//��� ������� ���������� ���� (�.�. ����������� �� ������������ ������, �� ��� �����)
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnButton_ToolBar_View_ScalePlus(void);//������� ���������� ��������
  afx_msg void OnButton_ToolBar_View_ScaleMinus(void);//������� ���������� ��������
  afx_msg void OnButton_ToolBar_View_Binding(void);//������� ����� ����������� ��������
  afx_msg BOOL OnEraseBkgnd(CDC *pDC);//������� ����������� ����
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//������� ������� ������ ������ ����
  afx_msg void OnRButtonUp(UINT nFlags,CPoint point);//������� ���������� ������ ������ ����
  afx_msg void OnLButtonDown(UINT nFlags,CPoint point);//������� ������� ����� ������ ����
  afx_msg void OnLButtonUp(UINT nFlags,CPoint point);//������� ���������� ����� ������ ����
  afx_msg void OnMouseMove(UINT nFlags,CPoint point);//������� ����������� �����
  afx_msg void OnTimer(UINT nIDEvent);//������� �������
  afx_msg void OnDestroy(void);//������� ����������� ����
  afx_msg void OnButton_ToolbarMain_CreateWall(void);//������ ����� �������� ����
  afx_msg void OnButton_ToolbarMain_CreateFrontier(void);//������ ����� �������� ����-����� �������
  afx_msg void OnButton_ToolbarMain_CreateSector(void);//������ ����� �������� ��������
  afx_msg void OnButton_ToolbarMain_WallSelect(void);//������ ����� ������ ����
  afx_msg void OnButton_ToolbarMain_FrontierSelect(void);//������ ����� ������ ����-����� �������
  afx_msg void OnButton_ToolbarMain_SectorSelect(void);//������ ����� ������ ��������
  afx_msg void OnButton_ToolbarMain_SetPlayerPosition(void);//������ ����� ������� ��������� ��������� ������
  afx_msg void OnButton_DialogbarControl_Delete(void);//������� �������� ��������� ���������
  afx_msg void OnButton_DialogbarControl_Edit(void);//������� �������������� ���������� ��������
  afx_msg void OnButton_DialogbarControl_WallSettings(void);//������ ������ ��������� ����
  afx_msg void OnButton_DialogbarControl_SectorSettings(void);//������ ������ ��������� ��������
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CView_Map) 
};

#endif