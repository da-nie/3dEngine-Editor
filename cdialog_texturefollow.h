#ifndef CDIALOG_TEXTUREFOLLOW_H
#define CDIALOG_TEXTUREFOLLOW_H

#include "stdafx.h"
#include "ctexture.h"
#include "cdialog_selecttexture.h"
#include "ctexturefollow.h"

//класс анимации текстур
class CDialog_TextureFollow:public CDialog
{
 protected:
  //-Переменные класса-------------------------------------------------------
  CTextureFollow cTextureFollow_Current;//текущая анимация текстуры
  CTextureFollow cTextureFollow_Local;//локальная копия анимации текстуры
  long hPos;//позиция бегунка
  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CDialog_TextureFollow(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-Деструктор класса-------------------------------------------------------
  ~CDialog_TextureFollow();
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
  afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//перемещение горизонтального бегунка
  afx_msg void OnCommand_Button_Cancel(void);//отмена
  afx_msg void OnCommand_Button_Ok(void);//применить
  afx_msg void OnCommand_Button_Clear(void);//очистить список
  afx_msg void OnCommand_Button_Add(void);//добавить текстуру
  afx_msg void OnCommand_Button_Delete(void);//удалить текстуру
  afx_msg void OnCommand_Button_Repeat(void);//повторить текстуру
  //-Новые функции класса----------------------------------------------------
 public:
  void SetTextureFollow(const CTextureFollow &cTextureFollowSet);//установить выбранную анимацию текстуры
  CTextureFollow GetTextureFollow(void);//получить выбранную анимацию текстуры
  //-Прочее------------------------------------------------------------------
 protected:
  void UpdateScrollPos(void);//обновить позицию бегунка
};
#endif