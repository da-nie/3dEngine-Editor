#ifndef C_VIEW_MAP_H
#define C_VIEW_MAP_H

#include "stdafx.h"
#include "cdocument_map.h"
#include "cframewnd_main.h"
#include "cdialog_settingswall.h"
#include "cdialog_settingssector.h"

//текущий режим работы
enum WORKING_MODE
{
 //режим неопределён
 WORKING_MODE_NONE,
 //режим согдания сегментов
 WORKING_MODE_CREATE_WALL,
 //режим создания линий раздела
 WORKING_MODE_CREATE_FRONTIER,
 //режим создания секторов
 WORKING_MODE_CREATE_SECTOR,
 //режим выбора сегментов
 WORKING_MODE_WALL_SELECT,
 //режим выбора линий раздела
 WORKING_MODE_FRONTIER_SELECT,
 //режим выбора секторов
 WORKING_MODE_SECTOR_SELECT,
 //режим задания начальной позиции игрока
 WORKING_MODE_SET_PLAYER_POSITION
};

//---------------------------------------------------------------------------
//класс представления
//---------------------------------------------------------------------------
class CView_Map:public CView
{
 protected: 
  //-Переменные класса-------------------------------------------------------
  //параметры вида
  float LeftUpAngle_X;//координаты левого верхнего угла карты
  float LeftUpAngle_Y;
  long GridSize;//шаг сетки
  float Increase;//коэффициент увеличения
  //параметры настройки вида
  bool Binding;//true-показывать ближайшую точку
  //вспомогательные параметры
  long ViewMode;//режим работы представления(0-норма, 1-двигаем карту)
  POINT MouseOnePoint;//координаты мыши, которые были когда мы начали двигать карту
  POINT NearestPoint;//координаты ближайшей точки для мыши

  WORKING_MODE CurrentMode;//текущий режим работы
  CDialog_SettingsWall *cDialog_SettingsWall_Ptr;//указатель на диалог настройки стен
  CDialog_SettingsSector *cDialog_SettingsSector_Ptr;//указатель на диалог настройки секторов
  //-Функции класса----------------------------------------------------------
  CDocument_Map* GetDocument();//получить документ
  afx_msg void OnInitialUpdate(void);//инициализация окна
  void DrawGrid(CDC *pDC);//отрисовать сетку
  void DrawPlayerPosition(CDC *pDC);//отрисовать положение игрока
  void DrawAxes(CDC *pDC);//отрисовать оси
  void DrawBinding(CDC *pDC);//отрисовать привязку
  void DrawWalls(CDC *pDC);//отрисовать стены
  void DrawSectors(CDC *pDC);//отрисовать сектора
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CView_Map();
  //-Деструктор класса-------------------------------------------------------
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  void SetGridSize(long gridsize);//установить шаг сетки
  void ClearMap(void);//очистить поле
  void LoadMap(FILE *file);//загрузить карту
  void SaveMap(FILE *file);//сохранить карту
  void ExportMapBSP(FILE *file);//экспорт карты в BSP
  void ExportMapPORTAL(FILE *file);//экспорт карты в PORTAL
  void ImportMapFromTXT(FILE *file);//импорт карты из текстового файла
 protected:
  virtual void OnDraw(CDC* pDC);//это функция прорисовки вида (т.к. наследовали от абстрактного класса, то она нужна)
  //-Функции обработки сообщений класса--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnButton_ToolBar_View_ScalePlus(void);//выбрано увеличение масштаба
  afx_msg void OnButton_ToolBar_View_ScaleMinus(void);//выбрано уменьшение масштаба
  afx_msg void OnButton_ToolBar_View_Binding(void);//выбрана смена отображения привязки
  afx_msg BOOL OnEraseBkgnd(CDC *pDC);//событие перерисовки фона
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//событие нажатия правой кнопки мыши
  afx_msg void OnRButtonUp(UINT nFlags,CPoint point);//событие отпускания правой кнопки мыши
  afx_msg void OnLButtonDown(UINT nFlags,CPoint point);//событие нажатия левой кнопки мыши
  afx_msg void OnLButtonUp(UINT nFlags,CPoint point);//событие отпускания левой кнопки мыши
  afx_msg void OnMouseMove(UINT nFlags,CPoint point);//событие перемещение мышки
  afx_msg void OnTimer(UINT nIDEvent);//событие таймера
  afx_msg void OnDestroy(void);//событие уничтожения окна
  afx_msg void OnButton_ToolbarMain_CreateWall(void);//выбран режим создания стен
  afx_msg void OnButton_ToolbarMain_CreateFrontier(void);//выбран режим создания стен-линий раздела
  afx_msg void OnButton_ToolbarMain_CreateSector(void);//выбран режим создания секторов
  afx_msg void OnButton_ToolbarMain_WallSelect(void);//выбран режим выбора стен
  afx_msg void OnButton_ToolbarMain_FrontierSelect(void);//выбран режим выбора стен-линий раздела
  afx_msg void OnButton_ToolbarMain_SectorSelect(void);//выбран режим выбора секторов
  afx_msg void OnButton_ToolbarMain_SetPlayerPosition(void);//выбран режим задания начальных координат игрока
  afx_msg void OnButton_DialogbarControl_Delete(void);//выбрано удаление выбранных элементов
  afx_msg void OnButton_DialogbarControl_Edit(void);//выбрано редактирование выбранного элемента
  afx_msg void OnButton_DialogbarControl_WallSettings(void);//выбран диалог настройки стен
  afx_msg void OnButton_DialogbarControl_SectorSettings(void);//выбран диалог настройки секторов
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CView_Map) 
};

#endif