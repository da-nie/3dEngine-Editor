#include "ctexture.h"

CTexture cTexture;

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CTexture::CTexture()
{
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CTexture::~CTexture()
{
 Release();	
}
//----------------------------------------------------------------------------------------------------
//освободить память
//----------------------------------------------------------------------------------------------------
void CTexture::Release(void)
{
 long size=vector_STextureImagePtr.size();
 for(long n=0;n<size;n++) delete(vector_STextureImagePtr[n]);
 vector_STextureImagePtr.clear();
}
//----------------------------------------------------------------------------------------------------
//загрузка
//----------------------------------------------------------------------------------------------------
bool CTexture::Load(char *TextureFileName)
{
 Release();
 //загружаем текстуры
 FILE *file=fopen(TextureFileName,"rb");
 if (file==NULL) return(false);
 while(1)
 {
  //читаем имя текстуры
  string name;
  while(1)
  {
   char s;
   if (fread(&s,sizeof(char),1,file)<1) break;
   if (s==0) break;
   name+=s;
  }
  //читаем размер текстуры
  long width;
  long height;
  if (fread(&width,sizeof(long),1,file)<1) break;
  if (fread(&height,sizeof(long),1,file)<1) break;
  //читаем данные текстуры
  char *image=new char[width*height*4];
  if (fread(image,sizeof(unsigned char),width*height*4,file)<width*height*4)
  {
   delete[](image);
   break;
  }
  STextureImage *sTextureImage_Ptr=new STextureImage;
  sTextureImage_Ptr->Name=name;
  sTextureImage_Ptr->Size=(1<<TEXTURE_SIZE_POW);
  if (sTextureImage_Ptr->Size==width && sTextureImage_Ptr->Size==height)//такую текстуру принимаем
  {
   for(long n=0;n<width*height*4;n++) sTextureImage_Ptr->Image[n]=image[n];
   vector_STextureImagePtr.push_back(sTextureImage_Ptr);  
  }
  delete[](image);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузка палитровых текстур
//----------------------------------------------------------------------------------------------------
bool CTexture::LoadPaletteTexture(char *TextureFileName)
{
 Release();
 //загружаем текстуры
 FILE *file=fopen(TextureFileName,"rb");
 if (file==NULL) return(false);
 //данные палитры
 unsigned char R[256];
 unsigned char G[256];
 unsigned char B[256];
 //создаём палитру
 for(long n=0;n<=255;n++)
 {
  R[n]=n&0x07;
  G[n]=(n>>3)&0x7;
  B[n]=(n>>6)&0x3;

  R[n]<<=5;
  G[n]<<=5;
  B[n]<<=6;  
 }
 while(1)
 {
  //читаем имя текстуры
  string name;
  while(1)
  {
   char s;
   if (fread(&s,sizeof(char),1,file)<1) break;
   if (s==0) break;
   name+=s;
  }
  //читаем размер текстуры
  long width;
  long height;
  if (fread(&width,sizeof(long),1,file)<1) break;
  if (fread(&height,sizeof(long),1,file)<1) break;
  //читаем данные текстуры
  char *image=new char[width*height];
  if (fread(image,sizeof(unsigned char),width*height,file)<width*height)
  {
   delete[](image);
   break;
  }
  STextureImage *sTextureImage_Ptr=new STextureImage;
  sTextureImage_Ptr->Name=name;
  sTextureImage_Ptr->Size=(1<<TEXTURE_SIZE_POW);
  if (sTextureImage_Ptr->Size==width && sTextureImage_Ptr->Size==height)//такую текстуру принимаем
  {
   long index=0;
   for(long n=0;n<width*height;n++) 
   {
    unsigned char color=image[n];
	sTextureImage_Ptr->Image[index]=B[color];index++;
	sTextureImage_Ptr->Image[index]=G[color];index++;
	sTextureImage_Ptr->Image[index]=R[color];index++;
	sTextureImage_Ptr->Image[index]=0;index++;
   }
   vector_STextureImagePtr.push_back(sTextureImage_Ptr);  
  }
  delete[](image);
 }
 fclose(file);
 return(true);
}


//----------------------------------------------------------------------------------------------------
//получить количество текстур
//----------------------------------------------------------------------------------------------------
long CTexture::GetTextureAmount(void)
{
 return(vector_STextureImagePtr.size());
}
//----------------------------------------------------------------------------------------------------
//получить указатель на данные текстуры
//----------------------------------------------------------------------------------------------------
STextureImage* CTexture::GetTextureImagePtr(long index)
{
 long size=vector_STextureImagePtr.size();
 if (index>=size) return(NULL);
 return(vector_STextureImagePtr[index]);
}
//----------------------------------------------------------------------------------------------------
//получить индекс текстуры по её имени
//----------------------------------------------------------------------------------------------------
long CTexture::GetTextureIndex(string name)
{
 long size=vector_STextureImagePtr.size();
 for(long n=0;n<size;n++)
 {
  if (vector_STextureImagePtr[n]->Name.compare(name)==0) return(n);
 }	 
 return(0); 
}
//----------------------------------------------------------------------------------------------------
//получить имя текстуры по её индексу
//----------------------------------------------------------------------------------------------------
string CTexture::GetTextureName(long index)
{ 
 string name;
 long size=vector_STextureImagePtr.size();
 if (index>=size) return(name);
 return(vector_STextureImagePtr[index]->Name);
}
