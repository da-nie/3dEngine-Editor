#ifndef CWALL_H
#define CWALL_H

#include "stdafx.h"
#include "ctexture.h"
#include "cdialog_texturefollow.h"

struct SWall_State
{
 CTextureFollow cTextureFollow_Up;//������������������ �������� ��������
 CTextureFollow cTextureFollow_Down;//������������������ �������� ��������
 bool Switch;//�������� �� ����� ��������������
 char SwitchLabel[SECTOR_LABEL_SIZE];//����� �������, � ������� ������ ������������� 
};


//����� ��������
class CWall
{
 public:
  //���������� �����
  SWall_State sWall_State;//��������� �����
  long X1;
  long Y1;
  long X2;
  long Y2;
  //��������� �����
  bool Frontier;//true-�����- ����� �������
  //��������� �������������� �����
  bool Select;//true-����� ��������
 public:
  CWall();//�����������
  ~CWall();//����������
  void Load(FILE *file);//��������
  void Save(FILE *file);//������
  void SaveParam(FILE *file);//������ ���������� �����
 protected:
};
#endif 