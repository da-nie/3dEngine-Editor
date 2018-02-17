#ifndef C_FRAME_WND_MAIN_H
#define C_FRAME_WND_MAIN_H

#include "stdafx.h"
#include "cview_map.h"
#include "ctexture.h"

extern CTexture cTexture;

class CFrameWnd_Main:public CFrameWnd
{
 protected:
  //-���������� ������-------------------------------------------------------
  CToolBar cToolBar_View;//������ �������� ����
  CComboBox cComboBox_GridSize;//������ �������� �����
  CDialogBar cDialogBar_Control;//������� ������ ��������
  CToolBar cToolBar_Main;//������� ������ ��������
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CFrameWnd_Main(void);
  //-���������� ������-------------------------------------------------------
  ~CFrameWnd_Main();
  //-���������� ������-------------------------------------------------------
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//������� �������� ����  
  afx_msg void OnDestroy(void);//������� ����������� ����
  afx_msg void ToolBar_ChangeGridSize(void);//�������� ������� �����
  afx_msg void OnTimer(UINT nIDEvent);//������� �������
  afx_msg void OnMenu_Window_ShowMainPanel(void);//������� ����� ��������� ������� ������
  afx_msg void OnMenu_Window_ShowControlPanel(void);//������� ����� ��������� ������ ����������
  afx_msg void OnMenu_Window_ShowViewPanel(void);//������� ����� ��������� ������ ����
  afx_msg void OnMenu_File_ClearMap(void);//������� ������� ����
  afx_msg void OnMenu_File_Load(void);//������� ��������
  afx_msg void OnMenu_File_Save(void);//������� ����������
  afx_msg void OnMenu_File_ExportBSP(void);//������ ������� ����� � BSP
  afx_msg void OnMenu_File_ExportPORTAL(void);//������ ������� ����� � PORTAL
  afx_msg void OnMenu_File_ImportTXT(void);//������������� ����� �� ���������� �����
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CFrameWnd_Main)
 public:
  //-������� ������----------------------------------------------------------
  void SetCursorPos(long x,long y);//���������� � ���� ���������� �������
};

#endif