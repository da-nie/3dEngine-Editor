#ifndef C_DOCUMENT_MAP_H
#define C_DOCUMENT_MAP_H

#include "stdafx.h"
#include "csector.h"
#include "cwall.h"
#include "bsp.h"
#include "cdialog_settingswall.h"
#include "cdialog_settingssector.h"

//---------------------------------------------------------------------------
//класс документов
//---------------------------------------------------------------------------
class CDocument_Map:public CDocument 
{
 protected:
  //-Переменные класса-------------------------------------------------------
  vector<CWall> vector_CWall;//стены
  vector<CSector> vector_CSector;//сектора

  CWall cWall_Current;//текущий создаваемый сегмент
  long CurrentPoint;//номер создаваемой точки (сегмента, линии раздела)

  CSector cSector_Current;//текущий создаваемый сектор

  //структура для хранения номеров секторов стены во время экспорта в PORTAL
  struct SWallSector
  {
   long Sector1;
   long Sector2;
  };

  long PlayerX;//начальные координаты игрока
  long PlayerY;

  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CDocument_Map(void); 
  //-Деструктор класса-------------------------------------------------------
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  vector<CWall>* GetVector_CWallPtr(void);//получить указатель на контейнер стен
  vector<CSector>* GetVector_CSectorPtr(void);//получить указатель на контейнер секторов
  CWall* GetCurrentWall(void);//получить указатель на создаваемую стену
  CSector* GetCurrentSector(void);//получить указатель на создаваемый сектор
  long GetCurrentPoint(void);//получить количество точек
  void ResetCurrentPoint(void);//сбросить список точек 
  void AddWallPoint(long x,long y,CDialog_SettingsWall *cDialog_SettingsWall_Ptr);//добавить точку к создаваемой стене
  void AddFrontierPoint(long x,long y,CDialog_SettingsWall *cDialog_SettingsWall_Ptr);//добавить точку к создаваемой стене-линии раздела
  void AddSectorPoint(long x,long y,CDialog_SettingsSector *cDialog_SettingsSector_Ptr);//добавить точку в создаваемый сектор
  void WallSelect(long x,long y);//выбрать стену
  void FrontierSelect(long x,long y);//выбрать стену-линию раздела
  void SectorSelect(long x,long y);//выбрать сектор
  void SetPlayerPosition(long x,long y);//задать положение игрока
  void GetPlayerPosition(long &x,long &y);//получить положение игрока 
  void ResetSelect(void);//сбросить выбранные стены и сектора
  double DistanceBeforeLine(double xp,double yp,double x1,double y1,double x2,double y2);//расстояние от точки до отрезка
  void DeleteSelected(void);//удалить все выбранные элементы
  void EditSelected(CDialog_SettingsWall *cDialog_SettingsWall_Ptr,CDialog_SettingsSector *cDialog_SettingsSector_Ptr);//редактировать выбранный элемент
  void DeleteAll(void);//удалить все элементы
  void Load(FILE *file);//загрузить уровень
  void Save(FILE *file);//сохранить уровень
  void ExportBSP(FILE *file);//экспортировать уровень в BSP
  void ExportPORTAL(FILE *file);//экспортировать уровень в PORTAL
  void ImportMapFromTXT(FILE *file,CDialog_SettingsWall *cDialog_SettingsWall_Ptr,CDialog_SettingsSector *cDialog_SettingsSector_Ptr);//импорт карты из текстового файла
 protected:
  void SaveCommonExportData(FILE *file);//сохранение общих данных карты  	 
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CDocument_Map) 
};
#endif

