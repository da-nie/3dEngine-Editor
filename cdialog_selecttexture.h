#ifndef CDIALOG_SELECTTEXTURE_H
#define CDIALOG_SELECTTEXTURE_H

#include "stdafx.h"
#include "ctexture.h"

class CDialog_SelectTexture:public CDialog
{
 protected:
  //-Переменные класса-------------------------------------------------------
  long SelectedTexture;//выбранная текстура
  long hPos;//горизонтальная позиция бегунка
  long vPos;//вертикальная позиция безунка
  long hPosMax;//максимальная горизонтальная позиция бегунка
  long vPosMax;//максимальная вертикальная позиция бегунка
  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CDialog_SelectTexture(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-Деструктор класса-------------------------------------------------------
  ~CDialog_SelectTexture();
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
  afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//перемещение вертикального бегунка
  afx_msg void OnLButtonUp(UINT nFlags,CPoint point);//отпускание левой кнопки мыши
  afx_msg void OnCommand_Button_Cancel(void);//отмена
  afx_msg void OnCommand_Button_Ok(void);//применить
  //-Новые функции класса----------------------------------------------------
 public:
  void SetSelectedTexture(long index);//установить выбранную текстуру
  long GetSelectedTexture(void);//получить выбранную текстуру
  //-Прочее------------------------------------------------------------------
 protected:
};
#endif