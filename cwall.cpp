#include "cwall.h"

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CWall::CWall()
{
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CWall::~CWall()
{ 
}
//----------------------------------------------------------------------------------------------------
//загрузка
//----------------------------------------------------------------------------------------------------
void CWall::Load(FILE *file)
{
 X1=LoadLong(file);
 Y1=LoadLong(file);
 X2=LoadLong(file);
 Y2=LoadLong(file);
 Frontier=false;
 if (LoadLong(file)!=0) Frontier=true;
 sWall_State.cTextureFollow_Up.Load(file);
 sWall_State.cTextureFollow_Down.Load(file);
 sWall_State.Switch=false;
 if (LoadLong(file)!=0) sWall_State.Switch=true;
 LoadCharArray(file,sWall_State.SwitchLabel,SECTOR_LABEL_SIZE);
}
//----------------------------------------------------------------------------------------------------
//запись
//----------------------------------------------------------------------------------------------------
void CWall::Save(FILE *file)
{
 SaveLong(file,X1);
 SaveLong(file,Y1);
 SaveLong(file,X2);
 SaveLong(file,Y2);
 if (Frontier==true) SaveLong(file,1);
                else SaveLong(file,0);
 sWall_State.cTextureFollow_Up.Save(file);
 sWall_State.cTextureFollow_Down.Save(file);
 if (sWall_State.Switch==true) SaveLong(file,1);
                             else SaveLong(file,0);
 SaveCharArray(file,sWall_State.SwitchLabel,SECTOR_LABEL_SIZE);
}
//----------------------------------------------------------------------------------------------------
//запись параметров стены
//----------------------------------------------------------------------------------------------------
void CWall::SaveParam(FILE *file)
{
 //сохраняем координаты
 SaveFloat(file,SCALE*X1);
 SaveFloat(file,SCALE*Y1);
 SaveFloat(file,SCALE*X2);
 SaveFloat(file,SCALE*Y2);
 //сохраняем, является ли стена линией раздела
 if (Frontier==true) SaveUChar(file,1);
                else SaveUChar(file,0);
 //сохраняем верхнюю и нижнюю текстуру
 sWall_State.cTextureFollow_Up.Save(file);
 sWall_State.cTextureFollow_Down.Save(file);
 //сохраняем, является ли стена переключателем
 if (sWall_State.Switch==true)
 {
  SaveUChar(file,1);
  SaveCharArray(file,sWall_State.SwitchLabel,SECTOR_LABEL_SIZE);
 }
 else SaveUChar(file,0);
}
