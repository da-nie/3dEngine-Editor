#include "cdocument_map.h"

extern SBSPParam sBSPParam;

//-������� ��������� ��������� ������----------------------------------------
//-����������� ������--------------------------------------------------------
CDocument_Map::CDocument_Map(void)
{
 CurrentPoint=0;
 cWall_Current.Frontier=false;
 cWall_Current.Select=false;
 PlayerX=0;
 PlayerY=0;
}
//-���������� ������---------------------------------------------------------
//-������� ������------------------------------------------------------------

//---------------------------------------------------------------------------
//�������� ��������� �� ��������� ���������
//---------------------------------------------------------------------------
vector<CWall>* CDocument_Map::GetVector_CWallPtr(void)
{
 return(&vector_CWall);
}
//---------------------------------------------------------------------------
//�������� ��������� �� ��������� ��������
//---------------------------------------------------------------------------
vector<CSector>* CDocument_Map::GetVector_CSectorPtr(void)
{
 return(&vector_CSector);
}
//---------------------------------------------------------------------------
//�������� ��������� �� ����������� �������
//---------------------------------------------------------------------------
CWall* CDocument_Map::GetCurrentWall(void)
{
 return(&cWall_Current);
}
//---------------------------------------------------------------------------
//�������� ��������� �� ����������� ������
//---------------------------------------------------------------------------
CSector* CDocument_Map::GetCurrentSector(void)
{
 return(&cSector_Current);
}
//---------------------------------------------------------------------------
//�������� ���������� �����
//---------------------------------------------------------------------------
long CDocument_Map::GetCurrentPoint(void)
{
 return(CurrentPoint);
}
//---------------------------------------------------------------------------
//�������� ������ �����
//---------------------------------------------------------------------------
void CDocument_Map::ResetCurrentPoint(void)
{
 CurrentPoint=0;
 cSector_Current.vector_SSectorPoint.clear();
}
//---------------------------------------------------------------------------
//�������� ����� � ������������ ��������
//---------------------------------------------------------------------------
void CDocument_Map::AddWallPoint(long x,long y,CDialog_SettingsWall *cDialog_SettingsWall_Ptr)
{
 if (CurrentPoint==0)
 {
  cWall_Current.X1=x;
  cWall_Current.Y1=y;
 }
 if (CurrentPoint==1)
 {
  cWall_Current.X2=x;
  cWall_Current.Y2=y;
 }
 CurrentPoint++;
 if (CurrentPoint==2)//������� ��������� ����� ��������
 {
  CurrentPoint=0;
  cWall_Current.Frontier=false;//��� �� ����� �������
  //��������� ����� ��������
  long dx=cWall_Current.X2-cWall_Current.X1;
  long dy=cWall_Current.Y2-cWall_Current.Y1;
  float length=(float)sqrt(dx*dx+dy*dy);
  if (length<0.0001)  CurrentPoint=1;//������ ����� ���� ������� ������
  else
  {
   //�������� ������� �������� ��������� ��������
   cWall_Current.sWall_State=cDialog_SettingsWall_Ptr->GetState();
   vector_CWall.push_back(cWall_Current);//��������� ������� � ������
  }
 }
}
//---------------------------------------------------------------------------
//�������� ����� � ����������� ����� �������
//---------------------------------------------------------------------------
void CDocument_Map::AddFrontierPoint(long x,long y,CDialog_SettingsWall *cDialog_SettingsWall_Ptr)
{
 if (CurrentPoint==0)
 {
  cWall_Current.X1=x;
  cWall_Current.Y1=y;
 }
 if (CurrentPoint==1)
 {
  cWall_Current.X2=x;
  cWall_Current.Y2=y;
 }
 CurrentPoint++;
 if (CurrentPoint==2)//������� ��������� ����� ��������
 {
  CurrentPoint=0;
  cWall_Current.Frontier=true;//��� ����� �������
  //��������� ����� ��������
  long dx=cWall_Current.X2-cWall_Current.X1;
  long dy=cWall_Current.Y2-cWall_Current.Y1;
  float length=(float)sqrt(dx*dx+dy*dy);
  if (length<0.0001)  CurrentPoint=1;//������ ����� ���� ������� ������
  else
  {
   //�������� ������� �������� ��������� ��������
   cWall_Current.sWall_State=cDialog_SettingsWall_Ptr->GetState();
   vector_CWall.push_back(cWall_Current);//��������� ������� � ������
  }
 }
}
//---------------------------------------------------------------------------
//�������� ����� � ����������� ������
//---------------------------------------------------------------------------
void CDocument_Map::AddSectorPoint(long x,long y,CDialog_SettingsSector *cDialog_SettingsSector_Ptr)
{
 SSectorPoint sSectorPoint;
 sSectorPoint.X=x;
 sSectorPoint.Y=y;
 long size=cSector_Current.vector_SSectorPoint.size();
 if (size!=0)
 {
  long dx=x-cSector_Current.vector_SSectorPoint[size-1].X;
  long dy=y-cSector_Current.vector_SSectorPoint[size-1].Y;
  float length=(float)sqrt(dx*dx+dy*dy);
  if (length<0.0001) return;//����� �� ����������� � ������
  //��������, ��� ��� ����� �� �������� ���������� �������
  CSector cSector_Test;
  cSector_Test=cSector_Current;
  cSector_Test.vector_SSectorPoint.push_back(sSectorPoint);
  bool enable=true;
  long size_test=cSector_Test.vector_SSectorPoint.size();
  for(long n=0;n<size_test;n++)
  {
   SSectorPoint cSectorPoint_Current=cSector_Test.vector_SSectorPoint[n];//������� ����
   SSectorPoint cSectorPoint_Next;//��������� �����
   //��� ��������� ����� ���� ������
   if (n!=size_test-1) cSectorPoint_Next=cSector_Test.vector_SSectorPoint[n+1];
                  else cSectorPoint_Next=cSector_Test.vector_SSectorPoint[0];
   double xw1=cSectorPoint_Current.X;
   double yw1=cSectorPoint_Current.Y;
   double xw2=cSectorPoint_Next.X;
   double yw2=cSectorPoint_Next.Y;
   //��������� ��� �����
   long last_side=0;
   for(long m=0;m<size_test;m++)
   {
    double xp=cSector_Test.vector_SSectorPoint[m].X;
    double yp=cSector_Test.vector_SSectorPoint[m].Y;
    //����������, � ����� ������� �� ����� ��������� ������� �������
    double side_value=xp*(yw1-yw2)-yp*(xw1-xw2)+xw1*yw2-xw2*yw1;
    long side=0;
    if (side_value<-EPS) side=-1;
    if (side_value>EPS) side=1;
    if (side==0) continue;
    if (last_side==0) last_side=side;
    if (last_side!=side)//������
    {
     enable=false;
     break;
    }
   }
   if (enable==false) break;
  }
  if (enable==false) return;
  //��������, ��� ��������� ����� �� ����� ��������
  if (cSector_Current.vector_SSectorPoint[0].X==x && cSector_Current.vector_SSectorPoint[0].Y==y)//������ ������, ��������� ��� � ������ ��������
  {
   cSector_Current.Select=false;
   //�������� ������� �������� ��������� �������
   cSector_Current.sSector_State=cDialog_SettingsSector_Ptr->GetState();
   vector_CSector.push_back(cSector_Current);
   cSector_Current.vector_SSectorPoint.clear();
   return;
  }
 }
 //��������� ����� ����� � ������ ����� �������
 cSector_Current.vector_SSectorPoint.push_back(sSectorPoint);
}
//---------------------------------------------------------------------------
//������� �������
//---------------------------------------------------------------------------
void CDocument_Map::WallSelect(long x,long y)
{
 //������� �������, �� ������� ��������� ��������� ����
 long size=vector_CWall.size();
 double min_dist=100000000.0;
 long select_segment_index=-1;
 for(long n=0;n<size;n++)
 {
  if (vector_CWall[n].Frontier==false)
  {
   double dist=DistanceBeforeLine(x,y,vector_CWall[n].X1,vector_CWall[n].Y1,vector_CWall[n].X2,vector_CWall[n].Y2);
   if (dist>=0)
   {
    if (dist<=min_dist)
    {
     min_dist=dist;
	 select_segment_index=n;
    }
   }
  }
 }
 if (select_segment_index<0) return;//������� �� ������
 if (min_dist>10) return;//������� ������
 if (vector_CWall[select_segment_index].Select==false) vector_CWall[select_segment_index].Select=true;
                                                  else vector_CWall[select_segment_index].Select=false;
}
//---------------------------------------------------------------------------
//������� ����� �������
//---------------------------------------------------------------------------
void CDocument_Map::FrontierSelect(long x,long y)
{
 //������� �������, �� ������� ��������� ��������� ����
 long size=vector_CWall.size();
 double min_dist=100000000.0;
 long select_segment_index=-1;
 for(long n=0;n<size;n++)
 {
  if (vector_CWall[n].Frontier==true)
  {
   double dist=DistanceBeforeLine(x,y,vector_CWall[n].X1,vector_CWall[n].Y1,vector_CWall[n].X2,vector_CWall[n].Y2);
   if (dist>=0)
   {
    if (dist<=min_dist)
    {
     min_dist=dist;
	 select_segment_index=n;
    }
   }
  }
 }
 if (select_segment_index<0) return;//������� �� ������
 if (min_dist>10) return;//������� ������
 if (vector_CWall[select_segment_index].Select==false) vector_CWall[select_segment_index].Select=true;
                                                  else vector_CWall[select_segment_index].Select=false;
}
//---------------------------------------------------------------------------
//������� ������
//---------------------------------------------------------------------------
void CDocument_Map::SectorSelect(long x,long y)
{
 long select_sector_index=-1;
 long size=vector_CSector.size();
 for(long n=0;n<size;n++)
 {
  long last_side=0;
  bool select=true;
  //������� ������
  long size_point=vector_CSector[n].vector_SSectorPoint.size();
  for(long m=0;m<size_point;m++)
  {
   SSectorPoint cSectorPoint_Current=vector_CSector[n].vector_SSectorPoint[m];//������� ����
   SSectorPoint cSectorPoint_Next;//��������� �����
   //��� ��������� ����� ���� ������
   if (m!=size_point-1) cSectorPoint_Next=vector_CSector[n].vector_SSectorPoint[m+1];
                   else cSectorPoint_Next=vector_CSector[n].vector_SSectorPoint[0];
   double xw1=cSectorPoint_Current.X;
   double yw1=cSectorPoint_Current.Y;
   double xw2=cSectorPoint_Next.X;
   double yw2=cSectorPoint_Next.Y;
   //����������, � ����� ������� �� ����� ��������� ������� �������
   double side_value=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
   long side=0;
   if (side_value<-EPS) side=-1;
   if (side_value>EPS) side=1;
   if (side==0) continue;
   if (last_side==0) last_side=side;
   if (last_side!=side)//������
   {
    select=false;
	break;
   }
  }
  if (select==true) select_sector_index=n;
 }
 if (select_sector_index<0) return;
 if (vector_CSector[select_sector_index].Select==false) vector_CSector[select_sector_index].Select=true;
                                                   else vector_CSector[select_sector_index].Select=false;
}
//---------------------------------------------------------------------------
//������ ��������� ������
//---------------------------------------------------------------------------
void CDocument_Map::SetPlayerPosition(long x,long y)
{
 PlayerX=x;
 PlayerY=y;
}
//---------------------------------------------------------------------------
//�������� ��������� ������
//---------------------------------------------------------------------------
void CDocument_Map::GetPlayerPosition(long &x,long &y)
{
 x=PlayerX;
 y=PlayerY;
}
//---------------------------------------------------------------------------
//�������� ��������� �������� � �������
//---------------------------------------------------------------------------
void CDocument_Map::ResetSelect(void)
{
 long size=vector_CWall.size();
 for(long n=0;n<size;n++) vector_CWall[n].Select=false;
 size=vector_CSector.size();
 for(n=0;n<size;n++) vector_CSector[n].Select=false;
}
//---------------------------------------------------------------------------
//���������� �� ����� �� �������
//---------------------------------------------------------------------------
double CDocument_Map::DistanceBeforeLine(double xp,double yp,double x1,double y1,double x2,double y2)
{
 //������ ������� � �������
 double nx=y1-y2;//-y
 double ny=x2-x1;//x
 double norma=sqrt(nx*nx+ny*ny);
 if (norma>0)
 {
  nx/=norma;
  ny/=norma;
 }
 //���������� ���������� �� ��������� ������ �� �����
 double dist=nx*(xp-x1)+ny*(yp-y1);
 //���������, ��� ����� ����������� ������ � ������� ����� �� �������
 double xi=xp-dist*nx;
 double yi=yp-dist*ny;
 if (xi<x1 && xi<x2) return(-1);
 if (xi>x1 && xi>x2) return(-1);
 if (yi<y1 && yi<y2) return(-1);
 if (yi>y1 && yi>y2) return(-1);
 return(fabs(dist));
}
//---------------------------------------------------------------------------
//������� ��� ��������� ��������
//---------------------------------------------------------------------------
void CDocument_Map::DeleteSelected(void)
{
 long n;
 long size=vector_CWall.size();
 n=0;
 while(n<size)
 {
  if (vector_CWall[n].Select==true)
  {
   vector_CWall.erase(vector_CWall.begin()+n);
   size--;
   continue;
  }
  n++;
 }
 //�������� ������ �� ��� ����� � ����������� ������� ���������� ������
 vector<CWall>(vector_CWall).swap(vector_CWall);

 size=vector_CSector.size();
 n=0;
 while(n<size)
 {
  if (vector_CSector[n].Select==true)
  {
   vector_CSector.erase(vector_CSector.begin()+n);
   size--;
   continue;
  }
  n++;
 }
 //�������� ������ �� ��� ����� � ����������� ������� ���������� ������
 vector<CSector>(vector_CSector).swap(vector_CSector);
}
//---------------------------------------------------------------------------
//������������� ��������� �������
//---------------------------------------------------------------------------
void CDocument_Map::EditSelected(CDialog_SettingsWall *cDialog_SettingsWall_Ptr,CDialog_SettingsSector *cDialog_SettingsSector_Ptr)
{
 long n;
 long size;
 long selected;
 selected=0;
 size=vector_CWall.size();
 for(n=0;n<size;n++)
 {
  if (vector_CWall[n].Select==true) selected++;
 }
 size=vector_CSector.size();
 for(n=0;n<size;n++)
 {
  if (vector_CSector[n].Select==true) selected++;
 }
 if (selected==0) return;
 if (selected>1)
 {
  MessageBox(NULL,"���������� ������� ���� �������!","������",MB_OK);
  return;
 }

 size=vector_CWall.size();
 for(n=0;n<size;n++)
 {
  if (vector_CWall[n].Select==true)
  {
   cDialog_SettingsWall_Ptr->SetState(vector_CWall[n].sWall_State);
   cDialog_SettingsWall_Ptr->DoModal();
   vector_CWall[n].sWall_State=cDialog_SettingsWall_Ptr->GetState();
   return;
  }
 }

 size=vector_CSector.size();
 for(n=0;n<size;n++)
 {
  if (vector_CSector[n].Select==true)
  {
   cDialog_SettingsSector_Ptr->SetState(vector_CSector[n].sSector_State);
   cDialog_SettingsSector_Ptr->DoModal();
   vector_CSector[n].sSector_State=cDialog_SettingsSector_Ptr->GetState();
   return;
  }
 }

}

//---------------------------------------------------------------------------
//������� ��� ��������
//---------------------------------------------------------------------------
void CDocument_Map::DeleteAll(void)
{
 ResetCurrentPoint();
 vector_CWall.clear();
 vector_CSector.clear();
}
//---------------------------------------------------------------------------
//��������� �������
//---------------------------------------------------------------------------
void CDocument_Map::Load(FILE *file)
{
 DeleteAll();
 PlayerX=LoadLong(file);//X
 PlayerY=LoadLong(file);//Y
 LoadLong(file);//����

 long n;
 long size=LoadLong(file);
 for(n=0;n<size;n++)
 {
  CWall cWall;
  cWall.Load(file);
  vector_CWall.push_back(cWall);
 }
 size=LoadLong(file);
 for(n=0;n<size;n++)
 {
  CSector cSector;
  cSector.Load(file);
  vector_CSector.push_back(cSector);
 }
}
//---------------------------------------------------------------------------
//��������� �������
//---------------------------------------------------------------------------
void CDocument_Map::Save(FILE *file)
{
 long n;
 SaveLong(file,PlayerX);//X
 SaveLong(file,PlayerY);//Y
 SaveLong(file,0);//����
 long size=vector_CWall.size();
 SaveLong(file,size);
 for(n=0;n<size;n++) vector_CWall[n].Save(file);
 size=vector_CSector.size();
 SaveLong(file,size);
 for(n=0;n<size;n++) vector_CSector[n].Save(file);
}
//---------------------------------------------------------------------------
//�������������� ������� � BSP
//---------------------------------------------------------------------------
void CDocument_Map::ExportBSP(FILE *file)
{
 long n; 
 SaveCommonExportData(file);//��������� ����� ������
 //������ ������ ��������� ��� ������ BSP-������
 long size=vector_CWall.size();
 vector<SBSPSegment> vector_SBSPSegment;
 for(n=0;n<size;n++)
 {
  SBSPSegment sBSPSegment;
  sBSPSegment.WallIndex=n;
  sBSPSegment.X1=vector_CWall[n].X1;
  sBSPSegment.Y1=vector_CWall[n].Y1;
  sBSPSegment.X2=vector_CWall[n].X2;
  sBSPSegment.Y2=vector_CWall[n].Y2;
  vector_SBSPSegment.push_back(sBSPSegment);
 }
 sBSPParam.Error=false;
 //��������� ���������� ������
 SBSPNode *sBSPNode_Ptr=BuildBSPTree(&vector_SBSPSegment);
 sBSPParam.File=file;
 sBSPParam.vector_CWall_Ptr=&vector_CWall;
 sBSPParam.vector_CSector_Ptr=&vector_CSector;
 //��������� ������
 SaveBSPTree(sBSPNode_Ptr);
 //������� ������
 DeleteBSPTree(sBSPNode_Ptr);
 if (sBSPParam.Error==false) MessageBox(NULL,"������� ��������. ������ ���.","���������",MB_OK);
                        else MessageBox(NULL,"�� ����� �������� ��������� ������.","���������",MB_OK);
}
//---------------------------------------------------------------------------
//�������������� ������� � PORTAL
//---------------------------------------------------------------------------
void CDocument_Map::ExportPORTAL(FILE *file)
{
 SaveCommonExportData(file);//��������� ����� ������
 MessageBox(NULL,"������� ��������. ������ ���.","���������",MB_OK);
}
//---------------------------------------------------------------------------
//������ ����� �� ���������� �����
//---------------------------------------------------------------------------
void CDocument_Map::ImportMapFromTXT(FILE *file,CDialog_SettingsWall *cDialog_SettingsWall_Ptr,CDialog_SettingsSector *cDialog_SettingsSector_Ptr)
{
 long n;
 DeleteAll();
 //��������� ��������� ���� � ������� ������ (0-��������� ������)
 vector<unsigned char> vector_data;
 long x=0;
 long y=0;
 long max_x=0;
 while(1)
 {
  unsigned char b;
  if (fread(&b,sizeof(char),1,file)<=0) break;//���� ����������
  if (b<static_cast<unsigned char>(' '))
  {
   if (x>0)//���� � ������ ���-�� ���� �������, ������ ������� ������ 
   {
	y++;
    vector_data.push_back(0);
   }   
   if (x>max_x) max_x=x;
   x=0;//������ ���������� ������
   continue;
  }  
  x++;
  vector_data.push_back(b);
 }
 long max_y=y;
 //������������� ��������� ����� � ��������� ������ [max_y][max_x] � ��������� ��� �������
 vector< vector<unsigned char> > vector_map(max_y,vector<unsigned char>(max_x,'.'));
 x=0;
 y=0;
 long size=vector_data.size();
 for(n=0;n<size;n++)
 {
  if (vector_data[n]==0 || n==size-1)
  {
   y++;
   x=0;
   continue;
  }
  if (vector_data[n]==static_cast<unsigned char>('#')) vector_map[max_y-y-1][x]=static_cast<unsigned char>('#');//�������� ����
  x++;
 }
 vector_data.clear();
 //������ ������� � �������� �� ��������� �����
 CSector cSector_Create;//����������� ������
 cSector_Create.vector_SSectorPoint.clear();
 cSector_Create.Select=false;
 cSector_Create.sSector_State=cDialog_SettingsSector_Ptr->GetState();
 CWall cWall_Create;//����������� �����
 cWall_Create.Frontier=false;
 cWall_Create.Select=false;
 cWall_Create.sWall_State=cDialog_SettingsWall_Ptr->GetState();
 for(y=0;y<max_y;y++)
 {
  for(x=0;x<max_x;x++)
  {
   unsigned char b=vector_map[y][x];
   if (b==static_cast<unsigned char>('.'))//������ ������
   {
    //������ ������ ������
    cSector_Create.vector_SSectorPoint.clear();
    //��������� ����� ���������������, ������������ ������
    SSectorPoint sSectorPoint[4];
    sSectorPoint[0].X=(x+1)*100;
    sSectorPoint[0].Y=(y+1)*100;
    sSectorPoint[1].X=(x+1)*100;
    sSectorPoint[1].Y=(y+0)*100;
    sSectorPoint[2].X=(x+0)*100;
    sSectorPoint[2].Y=(y+0)*100;
    sSectorPoint[3].X=(x+0)*100;
    sSectorPoint[3].Y=(y+1)*100;

    cSector_Create.vector_SSectorPoint.push_back(sSectorPoint[0]);
    cSector_Create.vector_SSectorPoint.push_back(sSectorPoint[1]);
    cSector_Create.vector_SSectorPoint.push_back(sSectorPoint[2]);
    cSector_Create.vector_SSectorPoint.push_back(sSectorPoint[3]);
    //��������� ������ � ������ ��������
    vector_CSector.push_back(cSector_Create);
	//���� ������ ������� ���� ��������-�����, �� ��������� �����, ����� ��������� ����� �������
	for(n=0;n<4;n++)
	{
     long next_n=(n+1)%4;
     cWall_Create.X1=sSectorPoint[n].X;
     cWall_Create.Y1=sSectorPoint[n].Y;
     cWall_Create.X2=sSectorPoint[next_n].X;
     cWall_Create.Y2=sSectorPoint[next_n].Y;
     cWall_Create.Frontier=true;//����� - ����� �������
	 if (n==0)//������ �����
	 {
      if (x<max_x-1)
	  {
       if (vector_map[y][x+1]!=static_cast<unsigned char>('.')) cWall_Create.Frontier=false;//������ ������ - �����
	  }
	  else cWall_Create.Frontier=false;
	 }

	 if (n==1)//������ �����
	 {
      if (y>0)
	  {
       if (vector_map[y-1][x]!=static_cast<unsigned char>('.')) cWall_Create.Frontier=false;//������ ����� - �����
                                                           else continue;//�� ������ ������, ��� ��� �� ��� ���� � ���� �������
	  }
	  else cWall_Create.Frontier=false;
	 }

	 if (n==2)//����� �����
	 {
      if (x>0)
	  {
       if (vector_map[y][x-1]!=static_cast<unsigned char>('.')) cWall_Create.Frontier=false;//������ ����� - �����
	                                                       else continue;//�� ������ ������, ��� ��� �� ��� ���� � ���� �������
	  }
	  else cWall_Create.Frontier=false;
	 }

	 if (n==3)//������� �����
	 {
      if (y<max_y-1)
	  {
       if (vector_map[y+1][x]!=static_cast<unsigned char>('.')) cWall_Create.Frontier=false;//������ ������ - �����
	  }
	  else cWall_Create.Frontier=false;
	 }
	 //��������� �������
     vector_CWall.push_back(cWall_Create);
	}
   }
  }
 }
}
//---------------------------------------------------------------------------
//���������� ����� ������ �����
//---------------------------------------------------------------------------
void CDocument_Map::SaveCommonExportData(FILE *file)
{
 long n;
 long m;
 //��������� ��������� �������
 SaveFloat(file,SCALE*PlayerX);//X
 SaveFloat(file,SCALE*PlayerY);//Y
 SaveFloat(file,0);//����
 //��������� �����
 long wall_size=vector_CWall.size();
 SaveLong(file,wall_size);
 sBSPParam.Error=false;

 vector<SWallSector> vector_SWallSector;
 for(n=0;n<wall_size;n++)
 {
  vector_CWall[n].SaveParam(file);
  //������ ��� ������ �����, � ������ ������� ��� �����������
  double x1=vector_CWall[n].X1;
  double y1=vector_CWall[n].Y1;
  double x2=vector_CWall[n].X2;
  double y2=vector_CWall[n].Y2;
  bool frontier=vector_CWall[n].Frontier;
  long sector1;
  long sector2;
  GetSector(&vector_CSector,x1,y1,x2,y2,frontier,sector1,sector2);
  if (sBSPParam.Error==true) break;
  SaveLong(file,sector1);
  SaveLong(file,sector2);

  SWallSector sWallSector;
  sWallSector.Sector1=sector1;
  sWallSector.Sector2=sector2;
  vector_SWallSector.push_back(sWallSector);
 }
 //��������� �������
 long sector_size=vector_CSector.size();
 SaveLong(file,sector_size);
 for(n=0;n<sector_size;n++)
 {
  //��������� ��� �������
  vector_CSector[n].SaveType(file);
  //���������� ������ �������� � ���� ��� �������
  vector<unsigned long> vector_wall_index;//������ �������� ����, ������������� �������
  vector<unsigned long> vector_wall_portal_index;//������ �������� ����, ������������� ������� � ���������� ���������
  for(m=0;m<wall_size;m++)
  {
   if (vector_CWall[m].Frontier==false)//����� �� �������� ������ �������
   {
    if (vector_SWallSector[m].Sector1==n) vector_wall_index.push_back(m);
   }
   else//����� �������� ������ �������
   {
    if (vector_SWallSector[m].Sector1==n || vector_SWallSector[m].Sector2==n) vector_wall_portal_index.push_back(m);
   }
  }
  //��������� ���������� ������ ����
  long wall_amount=vector_wall_index.size();
  SaveLong(file,wall_amount);
  for(m=0;m<wall_amount;m++) SaveLong(file,vector_wall_index[m]);
  //��������� ���������� ������ ��������
  long wall_portal_amount=vector_wall_portal_index.size();
  SaveLong(file,wall_portal_amount);
  for(m=0;m<wall_portal_amount;m++) SaveLong(file,vector_wall_portal_index[m]);
  //��������� ������ �������
  vector_CSector[n].SaveParam(file);
 }
}




//-������� ��������� ��������� ������----------------------------------------
//-������--------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CDocument_Map,CDocument)












