#ifndef CTEXTURE_H
#define CTEXTURE_H

#include "stdafx.h"

//������ ��������
#define TEXTURE_SIZE_POW 7

//����� ���������� ��������
struct STexture
{
 long TextureIndex;//������ ��������
 string Name;//��� ��������
};

//��������� ����������� ��������
struct STextureImage
{
 unsigned char Image[(1<<TEXTURE_SIZE_POW)*(1<<TEXTURE_SIZE_POW)*4];//������ �������� 
 long Size;//������ ��������
 string Name;//��� ��������
};

//����� �������� �������
class CTexture
{
 public:
  vector<STextureImage*> vector_STextureImagePtr;//����������� ��������
 public:
  CTexture();//�����������
  ~CTexture();//����������
  void Release(void);//���������� ������
  bool Load(char *TextureFileName);//�������� �������
  bool LoadPaletteTexture(char *TextureFileName);//�������� ���������� �������
  long GetTextureAmount(void);//�������� ���������� �������
  STextureImage* GetTextureImagePtr(long index);//�������� ��������� �� ������ ��������
  long GetTextureIndex(string name);//�������� ������ �������� �� � �����
  string GetTextureName(long index);//�������� ��� �������� �� � �������
};
#endif 