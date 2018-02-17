#ifndef BSP_H
#define BSP_H

#include "stdafx.h"
#include "csector.h"
#include "cwall.h"

//перечисления
enum MATH_RETURN_CODE
{
 //точка слева
 MATH_RETURN_CODE_SIDE_LEFT,
 //точка справа
 MATH_RETURN_CODE_SIDE_RIGHT,
 //точка на прямой
 MATH_RETURN_CODE_SIDE_IDENTITY,
 //точки одинаковые
 MATH_RETURN_CODE_POINT_IDENTITY,
 //точки разные
 MATH_RETURN_CODE_POINT_DIFFERENT
};

//это лист дерева
#define BSP_ATOM  (1<<0)
//левые ветки есть
#define BSP_LEFT  (1<<1)
//правые ветки есть
#define BSP_RIGHT (1<<2)

//структура сегмента
struct SBSPSegment
{
 //координаты линии
 double X1;
 double Y1;
 double X2;
 double Y2;
 long WallIndex;//номер сегмента по общему списку стен
};
//структура листа BSP-дерева
struct SBSPNode
{
 SBSPNode* sBSPNode_Left_Ptr;//левое поддерево
 SBSPNode* sBSPNode_Right_Ptr;//правое поддерево
 SBSPSegment sBSPSegment;//разделяющая линия
 bool Atom;//true - узел неделимый (дальше него нельзя разбить)
 double LX1,LX2,LY1,LY2;//левый описывающий прямоугольник
 double RX1,RX2,RY1,RY2;//правый описывающий прямоугольник
};
//параметры для экспорта в BSP
struct SBSPParam
{
 FILE *File;
 vector<CWall> *vector_CWall_Ptr;//стены
 vector<CSector> *vector_CSector_Ptr;//сектора
 bool Error;//были ли ошибки
};

MATH_RETURN_CODE GetSide(double x,double y,double x1,double y1,double x2,double y2);//получить, с какой стороны от прямой находится точка
MATH_RETURN_CODE GetPointIdentity(double x,double y,double x1,double y1);//получить, одинаковые ли точки
void Crossing(double xa1,double ya1,double xa2,double ya2,double xb1,double yb1,double xb2,double yb2,double &xot,double &yot);//получить точку пересчения двух линий
void FindRectangle(vector<SBSPSegment> *vector_SBSPSegment_Ptr,double &x1,double &y1,double &x2,double &y2);//определение описывающего прямоугольника
long FindSector(double x,double y,long sector_index,vector<CSector> *vector_CSector_Ptr);//поиск сектора, которому принадлежит точка, начиная с заданного
void GetSector(vector<CSector> *vector_CSector_Ptr,double x1,double y1,double x2,double y2,bool frontier,long &sector1,long &sector2);//поиск секторов, которым принадлежит линия

SBSPNode *BuildBSPTree(vector<SBSPSegment> *vector_SBSPSegment_Ptr);//построение BSP-дерева
void DeleteBSPTree(SBSPNode *sBSPNode_Ptr);//удаление BSP-дерева
void SaveBSPTree(SBSPNode *sBSPNode_Ptr);//сохранение BSP-дерева

#endif