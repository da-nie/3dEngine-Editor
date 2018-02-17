#ifndef CTEXTUREFOLLOW_H
#define CTEXTUREFOLLOW_H

#include "stdafx.h"
#include "ctexture.h"

//��� ��������
#define TEXTURE_FOLLOW_MODE_DISABLE 0
//����������� ��������
#define TEXTURE_FOLLOW_MODE_CYCLES  1
//�������� ����� � ���������
#define TEXTURE_FOLLOW_MODE_ZIGZAG  2

//����� �������� �������� ��������
class CTextureFollow
{
 public:
  //-���������� ������-------------------------------------------------------
  vector<STexture> vector_STexture;
  long Mode;//����� ����� ��������

  long CurrentPointer;//������� ����� �������� � �������
  long dPointer;//��� ���������
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CTextureFollow(void);
  //-���������� ������-------------------------------------------------------
  ~CTextureFollow(void);
  //-����� ������� ������----------------------------------------------------
  void Save(FILE *file);//��������� �������� ��������
  void Load(FILE *file);//��������� �������� ��������
  void Processing(void);//��������� �������� ��������
};

#endif