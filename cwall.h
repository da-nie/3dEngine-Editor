#ifndef CWALL_H
#define CWALL_H

#include "stdafx.h"
#include "ctexture.h"
#include "cdialog_texturefollow.h"

struct SWall_State
{
 CTextureFollow cTextureFollow_Up;//последовательность анимации текстуры
 CTextureFollow cTextureFollow_Down;//последовательность анимации текстуры
 bool Switch;//является ли стена переключателем
 char SwitchLabel[SECTOR_LABEL_SIZE];//метка сектора, с которым связан переключатель 
};


//класс сегмента
class CWall
{
 public:
  //координаты стены
  SWall_State sWall_State;//настройки стены
  long X1;
  long Y1;
  long X2;
  long Y2;
  //параметры стены
  bool Frontier;//true-стена- линия раздела
  //параметры редактирования стены
  bool Select;//true-стена выделена
 public:
  CWall();//конструктор
  ~CWall();//деструктор
  void Load(FILE *file);//загрузка
  void Save(FILE *file);//запись
  void SaveParam(FILE *file);//запись параметров стены
 protected:
};
#endif 