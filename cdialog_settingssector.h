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
  //-Переменные класса-------------------------------------------------------
  SSector_State sSector_State_Current;//текущие настройки
  SSector_State sSector_State_Local;//локальные настройки
  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CDialog_SettingsSector(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-Деструктор класса-------------------------------------------------------
  ~CDialog_SettingsSector();
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
  afx_msg void OnCommand_Button_CopyFlowToFloor(void);//скопировать текстуру потолка на пол
  afx_msg void OnCommand_Button_CopyFloorToFlow(void);//скопировать текстуру пола на потолок
  //-Новые функции класса----------------------------------------------------
 public:
  SSector_State GetState(void);//получить параметры сектора
  void SetState(const SSector_State &sSector_State);//задать параметры сектора
  //-Прочее------------------------------------------------------------------
 protected:
};
#endif