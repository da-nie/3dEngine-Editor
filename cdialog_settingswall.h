#ifndef CDIALOG_SETTINGSWALL_H
#define CDIALOG_SETTINGSWALL_H

#include "stdafx.h"
#include "ctexture.h"
#include "cdialog_selecttexture.h"
#include "cdialog_texturefollow.h"
#include "cwall.h"

class CDialog_SettingsWall:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  SWall_State sWall_State_Current;//������� ���������
  SWall_State sWall_State_Local;//��������� ���������
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CDialog_SettingsWall(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_SettingsWall();
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
  afx_msg void OnCommand_Button_Cancel(void);//������
  afx_msg void OnCommand_Button_Ok(void);//���������
  afx_msg void OnCommand_Button_ChangeTextureUp(void);//������� ������� ��������
  afx_msg void OnCommand_Button_ChangeTextureDown(void);//������� ������ ��������
  afx_msg void OnCommand_Button_ChangeTextureFollowUp(void);//������ �������� ������� ��������
  afx_msg void OnCommand_Button_ChangeTextureFollowDown(void);//������ �������� ������ ��������
  afx_msg void OnCommand_Button_CopyUpToDown(void);//����������� ������� �������� � ������
  afx_msg void OnCommand_Button_CopyDownToUp(void);//����������� ������ �������� � �������
  //-����� ������� ������----------------------------------------------------
 public:
  SWall_State GetState(void);//�������� ��������� �����
  void SetState(const SWall_State &sWall_State);//������ ��������� �����
  //-������------------------------------------------------------------------
 protected:
};
#endif