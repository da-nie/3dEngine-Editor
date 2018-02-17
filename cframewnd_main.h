#ifndef C_FRAME_WND_MAIN_H
#define C_FRAME_WND_MAIN_H

#include "stdafx.h"
#include "cview_map.h"
#include "ctexture.h"

extern CTexture cTexture;

class CFrameWnd_Main:public CFrameWnd
{
 protected:
  //-Переменные класса-------------------------------------------------------
  CToolBar cToolBar_View;//панель настроек вида
  CComboBox cComboBox_GridSize;//список размеров сетки
  CDialogBar cDialogBar_Control;//боковая панель настроек
  CToolBar cToolBar_Main;//главная панель действий
  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CFrameWnd_Main(void);
  //-Деструктор класса-------------------------------------------------------
  ~CFrameWnd_Main();
  //-Переменные класса-------------------------------------------------------
  //-Функции обработки сообщений класса--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//событие создания окна  
  afx_msg void OnDestroy(void);//событие уничтожения окна
  afx_msg void ToolBar_ChangeGridSize(void);//изменили масштаб сетки
  afx_msg void OnTimer(UINT nIDEvent);//событие таймера
  afx_msg void OnMenu_Window_ShowMainPanel(void);//выбрана смена видимости главной панели
  afx_msg void OnMenu_Window_ShowControlPanel(void);//выбрана смена видимости панели управления
  afx_msg void OnMenu_Window_ShowViewPanel(void);//выбрана смена видимости панели вида
  afx_msg void OnMenu_File_ClearMap(void);//выбрана очистка поля
  afx_msg void OnMenu_File_Load(void);//выбрана загрузка
  afx_msg void OnMenu_File_Save(void);//выбрано сохранение
  afx_msg void OnMenu_File_ExportBSP(void);//выбран экспорт карты в BSP
  afx_msg void OnMenu_File_ExportPORTAL(void);//выбран экспорт карты в PORTAL
  afx_msg void OnMenu_File_ImportTXT(void);//импортировать карту из текстового файла
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CFrameWnd_Main)
 public:
  //-Функции класса----------------------------------------------------------
  void SetCursorPos(long x,long y);//установить в окне координаты курсора
};

#endif