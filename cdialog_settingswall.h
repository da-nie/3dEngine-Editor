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
  //-Переменные класса-------------------------------------------------------
  SWall_State sWall_State_Current;//текущие настройки
  SWall_State sWall_State_Local;//локальные настройки
  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CDialog_SettingsWall(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-Деструктор класса-------------------------------------------------------
  ~CDialog_SettingsWall();
  //-Переменные класса-------------------------------------------------------
  //-Замещённые функции предка-----------------------------------------------
  afx_msg void OnOK(void);
  afx_msg void OnCancel(void);
  afx_msg void OnClose(void);
  afx_msg BOOL OnInitDialog(void);//инициализация диалога
  //-Новые функции класса----------------------------------------------------
  //-Функции обработки сообщений класса--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//событие уничтожения окна
  afx_msg void OnPaint(void);//событие отрисовки
  afx_msg void OnCommand_Button_Cancel(void);//отмена
  afx_msg void OnCommand_Button_Ok(void);//применить
  afx_msg void OnCommand_Button_ChangeTextureUp(void);//выбрать верхнюю текстуру
  afx_msg void OnCommand_Button_ChangeTextureDown(void);//выбрать нижнюю текстуру
  afx_msg void OnCommand_Button_ChangeTextureFollowUp(void);//задать анимацию верхней текстуры
  afx_msg void OnCommand_Button_ChangeTextureFollowDown(void);//задать анимацию нижней текстуры
  afx_msg void OnCommand_Button_CopyUpToDown(void);//скопировать верхнюю текстуру в нижнюю
  afx_msg void OnCommand_Button_CopyDownToUp(void);//скопировать нижнюю текстуру в верхнюю
  //-Новые функции класса----------------------------------------------------
 public:
  SWall_State GetState(void);//получить параметры стены
  void SetState(const SWall_State &sWall_State);//задать параметры стены
  //-Прочее------------------------------------------------------------------
 protected:
};
#endif