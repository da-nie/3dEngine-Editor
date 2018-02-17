#ifndef CTEXTURE_H
#define CTEXTURE_H

#include "stdafx.h"

//размер текстуры
#define TEXTURE_SIZE_POW 7

//класс параметров текстуры
struct STexture
{
 long TextureIndex;//индекс текстуры
 string Name;//имя текстуры
};

//структура изображения текстуры
struct STextureImage
{
 unsigned char Image[(1<<TEXTURE_SIZE_POW)*(1<<TEXTURE_SIZE_POW)*4];//данные текстуры 
 long Size;//размер текстуры
 string Name;//имя текстуры
};

//класс хранения текстур
class CTexture
{
 public:
  vector<STextureImage*> vector_STextureImagePtr;//загруженные текстуры
 public:
  CTexture();//конструктор
  ~CTexture();//деструктор
  void Release(void);//освободить память
  bool Load(char *TextureFileName);//загрузка текстур
  bool LoadPaletteTexture(char *TextureFileName);//загрузка палитровых текстур
  long GetTextureAmount(void);//получить количество текстур
  STextureImage* GetTextureImagePtr(long index);//получить указатель на данные текстуры
  long GetTextureIndex(string name);//получить индекс текстуры по её имени
  string GetTextureName(long index);//получить имя текстуры по её индексу
};
#endif 