#ifndef CTEXTUREFOLLOW_H
#define CTEXTUREFOLLOW_H

#include "stdafx.h"
#include "ctexture.h"

//нет анимации
#define TEXTURE_FOLLOW_MODE_DISABLE 0
//циклическа€ анимаци€
#define TEXTURE_FOLLOW_MODE_CYCLES  1
//анимаци€ смена с возвратом
#define TEXTURE_FOLLOW_MODE_ZIGZAG  2

//класс элемента анимации текстуры
class CTextureFollow
{
 public:
  //-ѕеременные класса-------------------------------------------------------
  vector<STexture> vector_STexture;
  long Mode;//режим смены текстуры

  long CurrentPointer;//текущий номер текстуры в массиве
  long dPointer;//его изменение
  //-‘ункции класса----------------------------------------------------------
  //-ѕрочее------------------------------------------------------------------
 public:
  //- онструктор класса------------------------------------------------------
  CTextureFollow(void);
  //-ƒеструктор класса-------------------------------------------------------
  ~CTextureFollow(void);
  //-Ќовые функции класса----------------------------------------------------
  void Save(FILE *file);//сохранить анимацию текстуры
  void Load(FILE *file);//загрузить анимацию текстуры
  void Processing(void);//обработка анимации текстуры
};

#endif