#ifndef CDIALOG_SETTINGSSECTOR_H
#define CDIALOG_SETTINGSSECTOR_H

#include "stdafx.h"
#include "ctexture.h"
#include "cdialog_selecttexture.h"
#include "cdialog_texturefollow.h"
#include "csector.h"


class CDialog_SettingsSector:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  SSector_State sSector_State_Current;//������� ���������
  SSector_State sSector_State_Local;//��������� ���������
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CDialog_SettingsSector(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_SettingsSector();
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
  afx_msg void OnCommand_Button_CopyFlowToFloor(void);//����������� �������� ������� �� ���
  afx_msg void OnCommand_Button_CopyFloorToFlow(void);//����������� �������� ���� �� �������
  //-����� ������� ������----------------------------------------------------
 public:
  SSector_State GetState(void);//�������� ��������� �������
  void SetState(const SSector_State &sSector_State);//������ ��������� �������
  //-������------------------------------------------------------------------
 protected:
};
#endif