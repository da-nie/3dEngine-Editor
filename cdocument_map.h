#ifndef C_DOCUMENT_MAP_H
#define C_DOCUMENT_MAP_H

#include "stdafx.h"
#include "csector.h"
#include "cwall.h"
#include "bsp.h"
#include "cdialog_settingswall.h"
#include "cdialog_settingssector.h"

//---------------------------------------------------------------------------
//����� ����������
//---------------------------------------------------------------------------
class CDocument_Map:public CDocument 
{
 protected:
  //-���������� ������-------------------------------------------------------
  vector<CWall> vector_CWall;//�����
  vector<CSector> vector_CSector;//�������

  CWall cWall_Current;//������� ����������� �������
  long CurrentPoint;//����� ����������� ����� (��������, ����� �������)

  CSector cSector_Current;//������� ����������� ������

  //��������� ��� �������� ������� �������� ����� �� ����� �������� � PORTAL
  struct SWallSector
  {
   long Sector1;
   long Sector2;
  };

  long PlayerX;//��������� ���������� ������
  long PlayerY;

  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CDocument_Map(void); 
  //-���������� ������-------------------------------------------------------
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  vector<CWall>* GetVector_CWallPtr(void);//�������� ��������� �� ��������� ����
  vector<CSector>* GetVector_CSectorPtr(void);//�������� ��������� �� ��������� ��������
  CWall* GetCurrentWall(void);//�������� ��������� �� ����������� �����
  CSector* GetCurrentSector(void);//�������� ��������� �� ����������� ������
  long GetCurrentPoint(void);//�������� ���������� �����
  void ResetCurrentPoint(void);//�������� ������ ����� 
  void AddWallPoint(long x,long y,CDialog_SettingsWall *cDialog_SettingsWall_Ptr);//�������� ����� � ����������� �����
  void AddFrontierPoint(long x,long y,CDialog_SettingsWall *cDialog_SettingsWall_Ptr);//�������� ����� � ����������� �����-����� �������
  void AddSectorPoint(long x,long y,CDialog_SettingsSector *cDialog_SettingsSector_Ptr);//�������� ����� � ����������� ������
  void WallSelect(long x,long y);//������� �����
  void FrontierSelect(long x,long y);//������� �����-����� �������
  void SectorSelect(long x,long y);//������� ������
  void SetPlayerPosition(long x,long y);//������ ��������� ������
  void GetPlayerPosition(long &x,long &y);//�������� ��������� ������ 
  void ResetSelect(void);//�������� ��������� ����� � �������
  double DistanceBeforeLine(double xp,double yp,double x1,double y1,double x2,double y2);//���������� �� ����� �� �������
  void DeleteSelected(void);//������� ��� ��������� ��������
  void EditSelected(CDialog_SettingsWall *cDialog_SettingsWall_Ptr,CDialog_SettingsSector *cDialog_SettingsSector_Ptr);//������������� ��������� �������
  void DeleteAll(void);//������� ��� ��������
  void Load(FILE *file);//��������� �������
  void Save(FILE *file);//��������� �������
  void ExportBSP(FILE *file);//�������������� ������� � BSP
  void ExportPORTAL(FILE *file);//�������������� ������� � PORTAL
  void ImportMapFromTXT(FILE *file,CDialog_SettingsWall *cDialog_SettingsWall_Ptr,CDialog_SettingsSector *cDialog_SettingsSector_Ptr);//������ ����� �� ���������� �����
 protected:
  void SaveCommonExportData(FILE *file);//���������� ����� ������ �����  	 
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CDocument_Map) 
};
#endif

