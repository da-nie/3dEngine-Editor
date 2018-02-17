#ifndef CSECTOR_H
#define CSECTOR_H

#include "stdafx.h"
#include "ctexture.h"
#include "ctexturefollow.h"


//��������� �������� ����� �������
struct SSectorPoint
{
 //���������� �����
 long X;
 long Y;
};

//���� ��������

//������� ������
#define SECTOR_TYPE_SIMPLY          0
//������� �����
#define SECTOR_TYPE_DOOR            1
//�������������
#define SECTOR_TYPE_SWITCH          2
//����� �� �������������
#define SECTOR_TYPE_SWITCH_DOOR     3
//���������
#define SECTOR_TYPE_PLATFORM        4
//��������� �� �������������
#define SECTOR_TYPE_SWITCH_PLATFORM 5
//����� � ������
#define SECTOR_TYPE_END             6
//������������
#define SECTOR_TYPE_TELEPORT        7
//������
#define SECTOR_TYPE_BRIDGE          8

//���� ���������

//����������� ���������
#define LIGHTING_MODE_STATIC          0
//�������
#define LIGHTING_MODE_FLASH           1
//��������� �������
#define LIGHTING_MODE_RANDOM_FLASH    2
//���������/����������
#define LIGHTING_MODE_DAWNING_SUNDOWN 3

struct SSector_State
{
 CTextureFollow cTextureFollow_Up;//������������������ �������� ��������
 CTextureFollow cTextureFollow_Down;//������������������ �������� ��������
 long UpLevel;//������� �������
 long DownLevel;//������� ����
 long WorkingLevel;//������� ������� (��� ��������, �������� � �.�.)

 long LightingMode;//��� ���������
 long BaseLighting;//������� ������������
 long BaseLightingTime;//����� ������� ������������ (��� ������ �������)
 long MaxLightingTime;//����� ������������ ������������ (��� ������ �������)

 long SectorType;//��� �������

 char Label[SECTOR_LABEL_SIZE];//����� �������

 bool Antigravitation;//������� �� � ������� ��������������
};

//����� ��������
class CSector
{
 public:
  SSector_State sSector_State;//��������� �������
  vector<SSectorPoint> vector_SSectorPoint;//����� �������
  bool Select;//true-������ ������ 
 public:
  CSector();//�����������
  ~CSector();//����������
  void Load(FILE *file);//��������
  void Save(FILE *file);//������
  void SaveType(FILE *file);//������ ���� �������
  void SaveParam(FILE *file);//������ ���������� �������
  SSector_State GetState(void);//�������� ��������� �������
 protected:
};
#endif 