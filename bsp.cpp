#include "bsp.h"

//����� ��������� ����� �������� ��������, ���������� ���������� ����������
SBSPParam sBSPParam;

//------------------------------------------------------------------------------------------
//��������, � ����� ������� �� ������ ��������� �����
//------------------------------------------------------------------------------------------
MATH_RETURN_CODE GetSide(double x,double y,double x1,double y1,double x2,double y2)
{
 double MC_EPS=0.01f;
 double p=x*(y1-y2)-y*(x1-x2)+x1*y2-x2*y1;
 if (p>MC_EPS) return(MATH_RETURN_CODE_SIDE_LEFT);
 if (p<-MC_EPS) return(MATH_RETURN_CODE_SIDE_RIGHT);
 return(MATH_RETURN_CODE_SIDE_IDENTITY);
}
//------------------------------------------------------------------------------------------
//��������, ���������� �� �����
//------------------------------------------------------------------------------------------
MATH_RETURN_CODE GetPointIdentity(double x,double y,double x1,double y1)
{
 double MC_EPS=0.05f;
 if (fabs(x-x1)<=MC_EPS && fabs(y-y1)<=MC_EPS) return(MATH_RETURN_CODE_POINT_IDENTITY);
 return(MATH_RETURN_CODE_POINT_DIFFERENT);
}
//------------------------------------------------------------------------------------------
//�������� ����� ���������� ���� �����
//------------------------------------------------------------------------------------------
void Crossing(double xa1,double ya1,double xa2,double ya2,double xb1,double yb1,double xb2,double yb2,double &xot,double &yot)
{
 double lx=xa2-xa1;
 double ly=ya2-ya1;
 double kx=xb2-xb1;
 double ky=yb2-yb1;
 double xl=xa1;
 double yl=ya1;
 double xk=xb1;
 double yk=yb1;
 double d=-ly*kx+lx*ky;//������������
 if (d==0)//�� ������������
 {
  xot=0;
  yot=0;
  return;
 }
 double d1=(ly*xl-lx*yl)*(-kx)+lx*(ky*xk-kx*yk);
 double d2=ly*(ky*xk-kx*yk)-ky*(ly*xl-lx*yl);
 xot=d1/d;//������ ������� �������
 yot=d2/d;
}
//------------------------------------------------------------------------------------------
//����������� ������������ ��������������
//------------------------------------------------------------------------------------------
void FindRectangle(vector<SBSPSegment> *vector_SBSPSegment_Ptr,double &x1,double &y1,double &x2,double &y2)
{
 long size=(*vector_SBSPSegment_Ptr).size();
 if (size==0) return;
 x1=(*vector_SBSPSegment_Ptr)[0].X1;
 y1=(*vector_SBSPSegment_Ptr)[0].Y1;
 x2=(*vector_SBSPSegment_Ptr)[0].X2;
 y2=(*vector_SBSPSegment_Ptr)[0].Y2;

 for(long n=0;n<size;n++)
 {
  double cx1=(*vector_SBSPSegment_Ptr)[n].X1;
  double cy1=(*vector_SBSPSegment_Ptr)[n].Y1;
  double cx2=(*vector_SBSPSegment_Ptr)[n].X2;
  double cy2=(*vector_SBSPSegment_Ptr)[n].Y2;
  if (y1>cy1) y1=cy1;
  if (y1>cy2) y1=cy2;
  if (y2<cy1) y2=cy1;
  if (y2<cy2) y2=cy2;
  if (x1>cx1) x1=cx1;
  if (x1>cx2) x1=cx2;
  if (x2<cx1) x2=cx1;
  if (x2<cx2) x2=cx2;
 }
}
//------------------------------------------------------------------------------------------
//����� �������, �������� ����������� �����, ������� � ���������
//------------------------------------------------------------------------------------------
long FindSector(double x,double y,long sector_index,vector<CSector> *vector_CSector_Ptr)
{
 long size=vector_CSector_Ptr->size();
 for(long n=sector_index;n<size;n++)
 {
  long side_left=0;
  long side_right=0;
  CSector *cSector_Ptr=&((*vector_CSector_Ptr)[n]);
  long points=cSector_Ptr->vector_SSectorPoint.size();
  for(long m=0;m<points;m++)
  {
   double x1=cSector_Ptr->vector_SSectorPoint[m].X;
   double y1=cSector_Ptr->vector_SSectorPoint[m].Y;
   double x2=cSector_Ptr->vector_SSectorPoint[(m+1)%points].X;
   double y2=cSector_Ptr->vector_SSectorPoint[(m+1)%points].Y;
   MATH_RETURN_CODE p=GetSide(x,y,x1,y1,x2,y2);
   if (p==MATH_RETURN_CODE_SIDE_LEFT) side_left++;
   if (p==MATH_RETURN_CODE_SIDE_RIGHT) side_right++;
  }
  if (side_left==0 && side_right!=0) return(n);
  if (side_left!=0 && side_right==0) return(n);
 }
 return(-1);
}

//------------------------------------------------------------------------------------------
//����� ��������, ������� ����������� �����
//------------------------------------------------------------------------------------------
void GetSector(vector<CSector> *vector_CSector_Ptr,double x1,double y1,double x2,double y2,bool frontier,long &sector1,long &sector2)
{
 sector1=-1;
 sector2=-1;
 long n;
 vector<long> vector_Sector1;
 vector<long> vector_Sector2;
 long index=0;
 while(1)
 {
  index=FindSector(x1,y1,index,vector_CSector_Ptr);
  if (index<0) break;//����� �� ���������
  vector_Sector1.push_back(index);
  index++;
 }
 index=0;
 while(1)
 {
  index=FindSector(x2,y2,index,vector_CSector_Ptr);
  if (index<0) break;//����� �� ���������
  vector_Sector2.push_back(index);
  index++;
 }
 //���������� ������� � ���������� ����� �������
 long size_sector_1=vector_Sector1.size();
 long size_sector_2=vector_Sector2.size();
 vector<long> vector_CommonSectors;//������ ����� ��������
 for(n=0;n<size_sector_1;n++)
 {
  for(long m=0;m<size_sector_2;m++)
  {
   if (vector_Sector1[n]==vector_Sector2[m])
   {
    vector_CommonSectors.push_back(vector_Sector1[n]);
    break;
   }
  }
 }
 //���������, ������� �������� ����������� �����
 if (vector_CommonSectors.size()>2)
 {
  MessageBox(NULL,"������� ����� �������� ��������� � �����!","������ BSP",MB_OK);
  sBSPParam.Error=true;
  return;
 }
 if (vector_CommonSectors.size()==0)
 {
  MessageBox(NULL,"����� �� ����������� �� ������ �� ��������!","������ BSP",MB_OK);
  sBSPParam.Error=true;
  return;
 }

 sector1=vector_CommonSectors[0];
 sector2=sector1;
 if (frontier==false) return;//��� �������� �������� ������� ��� ����������

 if (vector_CommonSectors.size()!=2)
 {
  MessageBox(NULL,"����� ������� ����������� ������ ������ �������!","������ BSP",MB_OK);
  sBSPParam.Error=true;
  return;
 }
 sector2=vector_CommonSectors[1];
 //���������� ��������� �������� ������������ ����� �������
 CSector *cSector_Ptr=&((*vector_CSector_Ptr)[sector1]);
 long points=cSector_Ptr->vector_SSectorPoint.size();
 MATH_RETURN_CODE state=MATH_RETURN_CODE_SIDE_IDENTITY;
 for(n=0;n<points;n++)
 {
  double x=cSector_Ptr->vector_SSectorPoint[n].X;
  double y=cSector_Ptr->vector_SSectorPoint[n].Y;
  MATH_RETURN_CODE p=GetSide(x,y,x1,y1,x2,y2);
  if (p==MATH_RETURN_CODE_SIDE_IDENTITY) continue;
  if (p==MATH_RETURN_CODE_SIDE_LEFT)
  {
   state=p;
   break;
  }
  if (p==MATH_RETURN_CODE_SIDE_RIGHT)
  {
   state=p;
   break;
  }
 }
 if (state==MATH_RETURN_CODE_SIDE_IDENTITY)
 {
  MessageBox(NULL,"�� ���������� ��������� �������� ������������ ����� �������!","������ BSP",MB_OK);
  sBSPParam.Error=true;
  return;
 }
 if (state==MATH_RETURN_CODE_SIDE_RIGHT)//���������� ������� �������
 {
  long tmp=sector1;
  sector1=sector2;
  sector2=tmp;  
 }
}

//------------------------------------------------------------------------------------------
//���������� BSP-������
//------------------------------------------------------------------------------------------
SBSPNode *BuildBSPTree(vector<SBSPSegment> *vector_SBSPSegment_Ptr)
{
 long n;
 long size=vector_SBSPSegment_Ptr->size();
 if (size==0) return(NULL);//����� ���
 SBSPNode *sBSPNode_Ptr=new SBSPNode;
 if (size==1)//��� ��������� ������� (������ ������ �� �������)
 {
  sBSPNode_Ptr->Atom=true;
  sBSPNode_Ptr->LX1=(*vector_SBSPSegment_Ptr)[0].X1;
  sBSPNode_Ptr->LX2=(*vector_SBSPSegment_Ptr)[0].X2;
  sBSPNode_Ptr->LY1=(*vector_SBSPSegment_Ptr)[0].Y1;
  sBSPNode_Ptr->LY2=(*vector_SBSPSegment_Ptr)[0].Y2;

  sBSPNode_Ptr->RX1=(*vector_SBSPSegment_Ptr)[0].X1;
  sBSPNode_Ptr->RX2=(*vector_SBSPSegment_Ptr)[0].X2;
  sBSPNode_Ptr->RY1=(*vector_SBSPSegment_Ptr)[0].Y1;
  sBSPNode_Ptr->RY2=(*vector_SBSPSegment_Ptr)[0].Y2;

  sBSPNode_Ptr->sBSPSegment=(*vector_SBSPSegment_Ptr)[0];
  sBSPNode_Ptr->sBSPNode_Left_Ptr=NULL;
  sBSPNode_Ptr->sBSPNode_Right_Ptr=NULL;
  return(sBSPNode_Ptr);
 }
 //���������
 //���������� ��������� ���������, ���������� ���������� ����� ������ � ����� �� ����������� �����
 long line_index=0;
 long min_delta=size+1;//������������ ������� ����� ����� � ������ ���������
 for(n=0;n<size;n++)//���������� �����
 {
  double px1=(*vector_SBSPSegment_Ptr)[n].X1;
  double py1=(*vector_SBSPSegment_Ptr)[n].Y1;
  double px2=(*vector_SBSPSegment_Ptr)[n].X2;
  double py2=(*vector_SBSPSegment_Ptr)[n].Y2;
  //����� ����� ������ � ����� �� ����� ���������
  long left_lines=0;
  long right_lines=0;
  for(long m=0;m<size;m++)
  {
   if (n==m) continue;//���� ���� �� ���������
   double x1=(*vector_SBSPSegment_Ptr)[m].X1;
   double y1=(*vector_SBSPSegment_Ptr)[m].Y1;
   double x2=(*vector_SBSPSegment_Ptr)[m].X2;
   double y2=(*vector_SBSPSegment_Ptr)[m].Y2;
   MATH_RETURN_CODE p1=GetSide(x1,y1,px1,py1,px2,py2);
   MATH_RETURN_CODE p2=GetSide(x2,y2,px1,py1,px2,py2);   
   if (p1==MATH_RETURN_CODE_SIDE_IDENTITY && p2==MATH_RETURN_CODE_SIDE_IDENTITY) right_lines++;//�����, ����������� � ������ ��������� ������� � ������ ������
   else
   {
    if ((p1==MATH_RETURN_CODE_SIDE_LEFT || p1==MATH_RETURN_CODE_SIDE_IDENTITY) && (p2==MATH_RETURN_CODE_SIDE_LEFT || p2==MATH_RETURN_CODE_SIDE_IDENTITY)) right_lines++;
    if ((p1==MATH_RETURN_CODE_SIDE_RIGHT || p1==MATH_RETURN_CODE_SIDE_IDENTITY) && (p2==MATH_RETURN_CODE_SIDE_RIGHT || p2==MATH_RETURN_CODE_SIDE_IDENTITY)) left_lines++;
    if ((p1==MATH_RETURN_CODE_SIDE_LEFT && p2==MATH_RETURN_CODE_SIDE_RIGHT) || (p1==MATH_RETURN_CODE_SIDE_RIGHT && p2==MATH_RETURN_CODE_SIDE_LEFT))
    {
     right_lines++;
	 left_lines++;
	}
   }  
  }
  //����������
  long delta=abs(right_lines-left_lines);
  if (delta<min_delta)
  {
   line_index=n;
   min_delta=delta;
  }
 }
 //������ ��������� ���������, �������� ���������
 sBSPNode_Ptr->Atom=false;
 sBSPNode_Ptr->sBSPSegment=(*vector_SBSPSegment_Ptr)[line_index];

 vector<SBSPSegment> vector_SBSPSegment_Left;//������ ����� ����� �� ����������� �����
 vector<SBSPSegment> vector_SBSPSegment_Right;//������ ����� ������ �� ����������� �����
 double px1=(*vector_SBSPSegment_Ptr)[line_index].X1;
 double py1=(*vector_SBSPSegment_Ptr)[line_index].Y1;
 double px2=(*vector_SBSPSegment_Ptr)[line_index].X2;
 double py2=(*vector_SBSPSegment_Ptr)[line_index].Y2;
 for(n=0;n<size;n++)
 {
  if (n==line_index) continue;//���� ���� �� ���������
  double x1=(*vector_SBSPSegment_Ptr)[n].X1;
  double y1=(*vector_SBSPSegment_Ptr)[n].Y1;
  double x2=(*vector_SBSPSegment_Ptr)[n].X2;
  double y2=(*vector_SBSPSegment_Ptr)[n].Y2;
  MATH_RETURN_CODE p1=GetSide(x1,y1,px1,py1,px2,py2);
  MATH_RETURN_CODE p2=GetSide(x2,y2,px1,py1,px2,py2);   
  if (p1==MATH_RETURN_CODE_SIDE_IDENTITY && p2==MATH_RETURN_CODE_SIDE_IDENTITY)//�����, ����������� � ������ ��������� ������� � ������ ������
  {
   SBSPSegment sBSPSegment; 
   sBSPSegment=(*vector_SBSPSegment_Ptr)[n];
   vector_SBSPSegment_Right.push_back(sBSPSegment);
  }
  else
  {
   if ((p1==MATH_RETURN_CODE_SIDE_LEFT || p1==MATH_RETURN_CODE_SIDE_IDENTITY) && (p2==MATH_RETURN_CODE_SIDE_LEFT || p2==MATH_RETURN_CODE_SIDE_IDENTITY)) 
   {
    SBSPSegment sBSPSegment; 
    sBSPSegment=(*vector_SBSPSegment_Ptr)[n];
    vector_SBSPSegment_Right.push_back(sBSPSegment);
   }
   if ((p1==MATH_RETURN_CODE_SIDE_RIGHT || p1==MATH_RETURN_CODE_SIDE_IDENTITY) && (p2==MATH_RETURN_CODE_SIDE_RIGHT || p2==MATH_RETURN_CODE_SIDE_IDENTITY))
   {
    SBSPSegment sBSPSegment; 
    sBSPSegment=(*vector_SBSPSegment_Ptr)[n];
    vector_SBSPSegment_Left.push_back(sBSPSegment);
   }	   
   if ((p1==MATH_RETURN_CODE_SIDE_LEFT && p2==MATH_RETURN_CODE_SIDE_RIGHT) || (p1==MATH_RETURN_CODE_SIDE_RIGHT && p2==MATH_RETURN_CODE_SIDE_LEFT))
   {
    //��������� ����� ����� ����������� � ��������� �����
	double xot;
	double yot;
    Crossing(px1,py1,px2,py2,x1,y1,x2,y2,xot,yot);//����� �����������
	if (p1==MATH_RETURN_CODE_SIDE_RIGHT)
	{
     if (GetPointIdentity(xot,yot,x1,y1)==MATH_RETURN_CODE_POINT_DIFFERENT)//������� ����� ��������
	 {
      SBSPSegment sBSPSegment; 
	  sBSPSegment.X1=x1;
	  sBSPSegment.Y1=y1;
	  sBSPSegment.X2=xot;
	  sBSPSegment.Y2=yot;
      sBSPSegment.WallIndex=(*vector_SBSPSegment_Ptr)[n].WallIndex;
      vector_SBSPSegment_Left.push_back(sBSPSegment);
	 }
     if (GetPointIdentity(xot,yot,x2,y2)==MATH_RETURN_CODE_POINT_DIFFERENT)//������� ����� ��������
	 {
      SBSPSegment sBSPSegment; 
	  sBSPSegment.X1=xot;
	  sBSPSegment.Y1=yot;
	  sBSPSegment.X2=x2;
	  sBSPSegment.Y2=y2;
      sBSPSegment.WallIndex=(*vector_SBSPSegment_Ptr)[n].WallIndex;
      vector_SBSPSegment_Right.push_back(sBSPSegment);
	 }
	}
	else
	{
     if (GetPointIdentity(xot,yot,x1,y1)==MATH_RETURN_CODE_POINT_DIFFERENT)//������� ����� ��������
	 {
      SBSPSegment sBSPSegment; 
	  sBSPSegment.X1=x1;
	  sBSPSegment.Y1=y1;
	  sBSPSegment.X2=xot;
	  sBSPSegment.Y2=yot;
      sBSPSegment.WallIndex=(*vector_SBSPSegment_Ptr)[n].WallIndex;
      vector_SBSPSegment_Right.push_back(sBSPSegment);
	 }
     if (GetPointIdentity(xot,yot,x2,y2)==MATH_RETURN_CODE_POINT_DIFFERENT)//������� ����� ��������
	 {
      SBSPSegment sBSPSegment; 
	  sBSPSegment.X1=xot;
	  sBSPSegment.Y1=yot;
	  sBSPSegment.X2=x2;
	  sBSPSegment.Y2=y2;
      sBSPSegment.WallIndex=(*vector_SBSPSegment_Ptr)[n].WallIndex;
      vector_SBSPSegment_Left.push_back(sBSPSegment);
	 }
	}
   }
  }  
 }
 //�������� ��� ����� � ������ ������
 //���������� ����������� �������������
 FindRectangle(&vector_SBSPSegment_Left,sBSPNode_Ptr->LX1,sBSPNode_Ptr->LY1,sBSPNode_Ptr->LX2,sBSPNode_Ptr->LY2);
 FindRectangle(&vector_SBSPSegment_Right,sBSPNode_Ptr->RX1,sBSPNode_Ptr->RY1,sBSPNode_Ptr->RX2,sBSPNode_Ptr->RY2);
 sBSPNode_Ptr->sBSPNode_Left_Ptr=BuildBSPTree(&vector_SBSPSegment_Left);
 sBSPNode_Ptr->sBSPNode_Right_Ptr=BuildBSPTree(&vector_SBSPSegment_Right);
 return(sBSPNode_Ptr);
}

//------------------------------------------------------------------------------------------
//�������� BSP-������
//------------------------------------------------------------------------------------------
void DeleteBSPTree(SBSPNode *sBSPNode_Ptr)
{
 if (sBSPNode_Ptr==NULL) return;
 if (sBSPNode_Ptr->Atom==true) return;
 if (sBSPNode_Ptr->sBSPNode_Left_Ptr!=NULL)
 {
  DeleteBSPTree(sBSPNode_Ptr->sBSPNode_Left_Ptr);
  delete(sBSPNode_Ptr->sBSPNode_Left_Ptr);
 }
 if (sBSPNode_Ptr->sBSPNode_Right_Ptr!=NULL)
 {
  DeleteBSPTree(sBSPNode_Ptr->sBSPNode_Right_Ptr);
  delete(sBSPNode_Ptr->sBSPNode_Right_Ptr);
 }
}

//------------------------------------------------------------------------------------------
//���������� BSP-������
//------------------------------------------------------------------------------------------
void SaveBSPTree(SBSPNode *sBSPNode_Ptr)
{
 if (sBSPNode_Ptr==NULL) return;
 unsigned char state=0;
 if (sBSPNode_Ptr->Atom==true) state|=BSP_ATOM;
 if (sBSPNode_Ptr->sBSPNode_Left_Ptr!=NULL) state|=BSP_LEFT;
 if (sBSPNode_Ptr->sBSPNode_Right_Ptr!=NULL) state|=BSP_RIGHT;
 SaveUChar(sBSPParam.File,state);
 //��������� ��������� ��������
 double x1=sBSPNode_Ptr->sBSPSegment.X1;
 double y1=sBSPNode_Ptr->sBSPSegment.Y1;
 double x2=sBSPNode_Ptr->sBSPSegment.X2;
 double y2=sBSPNode_Ptr->sBSPSegment.Y2;
 SaveFloat(sBSPParam.File,SCALE*x1);
 SaveFloat(sBSPParam.File,SCALE*y1);
 SaveFloat(sBSPParam.File,SCALE*x2);
 SaveFloat(sBSPParam.File,SCALE*y2);
 //��������� � ��������� �������� ��������
 long index=sBSPNode_Ptr->sBSPSegment.WallIndex;
 CWall *cWall_Ptr=&(*sBSPParam.vector_CWall_Ptr)[index];
 double dx=(x1-cWall_Ptr->X1);
 double dy=(y1-cWall_Ptr->Y1);
 double offset=sqrt(dx*dx+dy*dy)*SCALE;
 SaveLong(sBSPParam.File,offset); 
 //��������� ������ �������� �����
 SaveLong(sBSPParam.File,index);
 //����������, ������ ������� ����������� �������
 long sector1;
 long sector2;
 GetSector(sBSPParam.vector_CSector_Ptr,x1,y1,x2,y2,cWall_Ptr->Frontier,sector1,sector2);
 if (sBSPParam.Error==true) return;
 SaveLong(sBSPParam.File,sector1);
 SaveLong(sBSPParam.File,sector2);
 if (sBSPNode_Ptr->Atom==true) return;//� ����� ��������� ������ ������
 //��������� ����� ����������� �������������
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->LX1);
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->LY1);
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->LX2);
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->LY2);
 //��������� ������ ����������� �������������
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->RX1);
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->RY1);
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->RX2);
 SaveFloat(sBSPParam.File,SCALE*sBSPNode_Ptr->RY2);
 //��������� ����������
 if (sBSPNode_Ptr->sBSPNode_Left_Ptr!=NULL)
 {  
  SaveBSPTree(sBSPNode_Ptr->sBSPNode_Left_Ptr);
 }
 if (sBSPNode_Ptr->sBSPNode_Right_Ptr!=NULL)
 {
  SaveBSPTree(sBSPNode_Ptr->sBSPNode_Right_Ptr);
 }
}