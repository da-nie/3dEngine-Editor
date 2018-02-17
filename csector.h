#ifndef CSECTOR_H
#define CSECTOR_H

#include "stdafx.h"
#include "ctexture.h"
#include "ctexturefollow.h"


//структура хранения точек сектора
struct SSectorPoint
{
 //координаты точки
 long X;
 long Y;
};

//типы секторов

//простой сектор
#define SECTOR_TYPE_SIMPLY          0
//обычная дверь
#define SECTOR_TYPE_DOOR            1
//переключатель
#define SECTOR_TYPE_SWITCH          2
//дверь от переключателя
#define SECTOR_TYPE_SWITCH_DOOR     3
//платформа
#define SECTOR_TYPE_PLATFORM        4
//платформа от переключателя
#define SECTOR_TYPE_SWITCH_PLATFORM 5
//выход с уровня
#define SECTOR_TYPE_END             6
//телепортатор
#define SECTOR_TYPE_TELEPORT        7
//мостик
#define SECTOR_TYPE_BRIDGE          8

//типы освещения

//равномерное освещение
#define LIGHTING_MODE_STATIC          0
//мигание
#define LIGHTING_MODE_FLASH           1
//случайное мигание
#define LIGHTING_MODE_RANDOM_FLASH    2
//затухание/нарастание
#define LIGHTING_MODE_DAWNING_SUNDOWN 3

struct SSector_State
{
 CTextureFollow cTextureFollow_Up;//последовательность анимации текстуры
 CTextureFollow cTextureFollow_Down;//последовательность анимации текстуры
 long UpLevel;//уровень потолка
 long DownLevel;//уровень пола
 long WorkingLevel;//рабочий уровень (для мостиков, платформ и т.д.)

 long LightingMode;//тип освещения
 long BaseLighting;//базовая освещённость
 long BaseLightingTime;//время базовой освещённости (для режима мигания)
 long MaxLightingTime;//время максимальной освещённости (для режима мигания)

 long SectorType;//тип сектора

 char Label[SECTOR_LABEL_SIZE];//метка сектора

 bool Antigravitation;//имеется ли в секторе антигравитация
};

//класс секторов
class CSector
{
 public:
  SSector_State sSector_State;//настройки сектора
  vector<SSectorPoint> vector_SSectorPoint;//точки сектора
  bool Select;//true-сектор выбран 
 public:
  CSector();//конструктор
  ~CSector();//деструктор
  void Load(FILE *file);//загрузка
  void Save(FILE *file);//запись
  void SaveType(FILE *file);//запись типа сектора
  void SaveParam(FILE *file);//запись параметров сектора
  SSector_State GetState(void);//получить параметры сектора
 protected:
};
#endif 