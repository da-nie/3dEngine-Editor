#ifndef CDIALOG_TEXTUREFOLLOW_H
#define CDIALOG_TEXTUREFOLLOW_H

#include "stdafx.h"
#include "ctexture.h"
#include "cdialog_selecttexture.h"
#include "ctexturefollow.h"

//����� �������� �������
class CDialog_TextureFollow:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  CTextureFollow cTextureFollow_Current;//������� �������� ��������
  CTextureFollow cTextureFollow_Local;//��������� ����� �������� ��������
  long hPos;//������� �������
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CDialog_TextureFollow(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_TextureFollow();
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
  afx_msg void OnCommand_Button_Cancel(void);//������
  afx_msg void OnCommand_Button_Ok(void);//���������
  afx_msg void OnCommand_Button_Clear(void);//�������� ������
  afx_msg void OnCommand_Button_Add(void);//�������� ��������
  afx_msg void OnCommand_Button_Delete(void);//������� ��������
  afx_msg void OnCommand_Button_Repeat(void);//��������� ��������
  //-����� ������� ������----------------------------------------------------
 public:
  void SetTextureFollow(const CTextureFollow &cTextureFollowSet);//���������� ��������� �������� ��������
  CTextureFollow GetTextureFollow(void);//�������� ��������� �������� ��������
  //-������------------------------------------------------------------------
 protected:
  void UpdateScrollPos(void);//�������� ������� �������
};
#endif