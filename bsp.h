#ifndef BSP_H
#define BSP_H

#include "stdafx.h"
#include "csector.h"
#include "cwall.h"

//������������
enum MATH_RETURN_CODE
{
 //����� �����
 MATH_RETURN_CODE_SIDE_LEFT,
 //����� ������
 MATH_RETURN_CODE_SIDE_RIGHT,
 //����� �� ������
 MATH_RETURN_CODE_SIDE_IDENTITY,
 //����� ����������
 MATH_RETURN_CODE_POINT_IDENTITY,
 //����� ������
 MATH_RETURN_CODE_POINT_DIFFERENT
};

//��� ���� ������
#define BSP_ATOM  (1<<0)
//����� ����� ����
#define BSP_LEFT  (1<<1)
//������ ����� ����
#define BSP_RIGHT (1<<2)

//��������� ��������
struct SBSPSegment
{
 //���������� �����
 double X1;
 double Y1;
 double X2;
 double Y2;
 long WallIndex;//����� �������� �� ������ ������ ����
};
//��������� ����� BSP-������
struct SBSPNode
{
 SBSPNode* sBSPNode_Left_Ptr;//����� ���������
 SBSPNode* sBSPNode_Right_Ptr;//������ ���������
 SBSPSegment sBSPSegment;//����������� �����
 bool Atom;//true - ���� ��������� (������ ���� ������ �������)
 double LX1,LX2,LY1,LY2;//����� ����������� �������������
 double RX1,RX2,RY1,RY2;//������ ����������� �������������
};
//��������� ��� �������� � BSP
struct SBSPParam
{
 FILE *File;
 vector<CWall> *vector_CWall_Ptr;//�����
 vector<CSector> *vector_CSector_Ptr;//�������
 bool Error;//���� �� ������
};

MATH_RETURN_CODE GetSide(double x,double y,double x1,double y1,double x2,double y2);//��������, � ����� ������� �� ������ ��������� �����
MATH_RETURN_CODE GetPointIdentity(double x,double y,double x1,double y1);//��������, ���������� �� �����
void Crossing(double xa1,double ya1,double xa2,double ya2,double xb1,double yb1,double xb2,double yb2,double &xot,double &yot);//�������� ����� ���������� ���� �����
void FindRectangle(vector<SBSPSegment> *vector_SBSPSegment_Ptr,double &x1,double &y1,double &x2,double &y2);//����������� ������������ ��������������
long FindSector(double x,double y,long sector_index,vector<CSector> *vector_CSector_Ptr);//����� �������, �������� ����������� �����, ������� � ���������
void GetSector(vector<CSector> *vector_CSector_Ptr,double x1,double y1,double x2,double y2,bool frontier,long &sector1,long &sector2);//����� ��������, ������� ����������� �����

SBSPNode *BuildBSPTree(vector<SBSPSegment> *vector_SBSPSegment_Ptr);//���������� BSP-������
void DeleteBSPTree(SBSPNode *sBSPNode_Ptr);//�������� BSP-������
void SaveBSPTree(SBSPNode *sBSPNode_Ptr);//���������� BSP-������

#endif