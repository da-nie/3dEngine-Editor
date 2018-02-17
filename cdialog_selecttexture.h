#ifndef CDIALOG_SELECTTEXTURE_H
#define CDIALOG_SELECTTEXTURE_H

#include "stdafx.h"
#include "ctexture.h"

class CDialog_SelectTexture:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  long SelectedTexture;//��������� ��������
  long hPos;//�������������� ������� �������
  long vPos;//������������ ������� �������
  long hPosMax;//������������ �������������� ������� �������
  long vPosMax;//������������ ������������ ������� �������
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CDialog_SelectTexture(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_SelectTexture();
  //-���������� ������-------------------------------------------------------
  //-���������� ������� ������-----------------------------------------------
  afx_msg void OnOK(void);
  afx_msg void OnCancel(void);
  afx_msg void OnClose(void);
  afx_msg BOOL OnInitDialog(void);//������������� �������
  //-����� ������� ������----------------------------------------------------
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//������� ����������� ����
  afx_msg void OnPaint(void);//������� ���������
  afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//����������� ��������������� �������
  afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//����������� ������������� �������
  afx_msg void OnLButtonUp(UINT nFlags,CPoint point);//���������� ����� ������ ����
  afx_msg void OnCommand_Button_Cancel(void);//������
  afx_msg void OnCommand_Button_Ok(void);//���������
  //-����� ������� ������----------------------------------------------------
 public:
  void SetSelectedTexture(long index);//���������� ��������� ��������
  long GetSelectedTexture(void);//�������� ��������� ��������
  //-������------------------------------------------------------------------
 protected:
};
#endif