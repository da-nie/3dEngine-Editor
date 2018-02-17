#include "csector.h"

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CSector::CSector()
{
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CSector::~CSector()
{ 
}
//----------------------------------------------------------------------------------------------------
//загрузка
//----------------------------------------------------------------------------------------------------
void CSector::Load(FILE *file)
{
 vector_SSectorPoint.clear();
 long size=LoadLong(file);
 for(long n=0;n<size;n++)
 {
  SSectorPoint sSectorPoint;
  sSectorPoint.X=LoadLong(file);
  sSectorPoint.Y=LoadLong(file);
  vector_SSectorPoint.push_back(sSectorPoint);
 }
 sSector_State.cTextureFollow_Up.Load(file);
 sSector_State.cTextureFollow_Down.Load(file);
 sSector_State.UpLevel=LoadLong(file);
 sSector_State.DownLevel=LoadLong(file);
 sSector_State.WorkingLevel=LoadLong(file); 
 sSector_State.LightingMode=LoadLong(file);
 sSector_State.BaseLighting=LoadLong(file);
 sSector_State.BaseLightingTime=LoadLong(file);
 sSector_State.MaxLightingTime=LoadLong(file);
 sSector_State.SectorType=LoadLong(file);
 if (LoadUChar(file)!=0) sSector_State.Antigravitation=true;
                    else sSector_State.Antigravitation=false;
 LoadCharArray(file,sSector_State.Label,SECTOR_LABEL_SIZE);
}
//----------------------------------------------------------------------------------------------------
//запись
//----------------------------------------------------------------------------------------------------
void CSector::Save(FILE *file)
{
 long size=vector_SSectorPoint.size();
 SaveLong(file,size);
 for(long n=0;n<size;n++)
 {
  SaveLong(file,vector_SSectorPoint[n].X);
  SaveLong(file,vector_SSectorPoint[n].Y);
 }
 sSector_State.cTextureFollow_Up.Save(file);
 sSector_State.cTextureFollow_Down.Save(file);
 SaveLong(file,sSector_State.UpLevel);
 SaveLong(file,sSector_State.DownLevel);
 SaveLong(file,sSector_State.WorkingLevel);
 SaveLong(file,sSector_State.LightingMode);
 SaveLong(file,sSector_State.BaseLighting);
 SaveLong(file,sSector_State.BaseLightingTime);
 SaveLong(file,sSector_State.MaxLightingTime);
 SaveLong(file,sSector_State.SectorType);
 if (sSector_State.Antigravitation==true) SaveUChar(file,1);
                                     else SaveUChar(file,0);
 SaveCharArray(file,sSector_State.Label,SECTOR_LABEL_SIZE);
}
//----------------------------------------------------------------------------------------------------
//запись типа сектора
//----------------------------------------------------------------------------------------------------
void CSector::SaveType(FILE *file)
{
 //сохраняем тип сектора
 SaveLong(file,sSector_State.SectorType);
}
//----------------------------------------------------------------------------------------------------
//запись данных сектора
//----------------------------------------------------------------------------------------------------
void CSector::SaveParam(FILE *file)
{
 //сохраняем координаты точек сектора
 long size=vector_SSectorPoint.size();
 SaveLong(file,size);
 float xb1;
 float xb2;
 float yb1;
 float yb2;
 if (size>0)
 {
  xb1=SCALE*vector_SSectorPoint[0].X;
  yb1=SCALE*vector_SSectorPoint[0].Y;
  xb2=SCALE*vector_SSectorPoint[0].X;
  yb2=SCALE*vector_SSectorPoint[0].Y;
 }
 for(long n=0;n<size;n++)
 {
  float x=SCALE*vector_SSectorPoint[n].X;
  float y=SCALE*vector_SSectorPoint[n].Y;
  SaveFloat(file,x);
  SaveFloat(file,y);
  if (x<xb1) xb1=x;
  if (y<yb1) yb1=y;
  if (x>xb2) xb2=x;
  if (y>yb2) yb2=y;
 }
 //сохраняем параметры освещённости
 SaveLong(file,sSector_State.LightingMode);
 SaveLong(file,sSector_State.BaseLighting);
 SaveLong(file,sSector_State.BaseLightingTime);
 SaveLong(file,sSector_State.MaxLightingTime);
 //сохраняем параметры сектора
 sSector_State.cTextureFollow_Up.Save(file);
 sSector_State.cTextureFollow_Down.Save(file);

 SaveLong(file,sSector_State.DownLevel);//высота пола
 SaveLong(file,sSector_State.UpLevel);//высота потолка  
 
 //сохраняем метку сектора
 SaveCharArray(file,sSector_State.Label,SECTOR_LABEL_SIZE);
 if (sSector_State.Antigravitation==true) SaveUChar(file,1);
                                     else SaveUChar(file,0);
 //сохраняем описывающий прямоугольник
 SaveFloat(file,xb1);
 SaveFloat(file,yb1);
 SaveFloat(file,xb2);
 SaveFloat(file,yb2);
 //сохраняем особые параметры сектора
 if (sSector_State.SectorType==SECTOR_TYPE_PLATFORM ||
	 sSector_State.SectorType==SECTOR_TYPE_SWITCH_PLATFORM ||
	 sSector_State.SectorType==SECTOR_TYPE_BRIDGE)
 {
  SaveLong(file,sSector_State.WorkingLevel);
 }
 if (sSector_State.SectorType==SECTOR_TYPE_TELEPORT)
 {
  //не реализовано задание координат телепортации!
  SaveLong(file,SCALE*100);//X
  SaveLong(file,SCALE*100);//Y
 }
 if (sSector_State.SectorType==SECTOR_TYPE_SWITCH)
 {
  //не реализовано!
 }
}
