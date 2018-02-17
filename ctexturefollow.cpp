#include "ctexturefollow.h"

extern CTexture cTexture;


//---------------------------------------------------------------------------
//конструктор
//---------------------------------------------------------------------------
CTextureFollow::CTextureFollow(void)
{
 CurrentPointer=0;
 dPointer=0;
 Mode=TEXTURE_FOLLOW_MODE_DISABLE;
 vector_STexture.clear();
}
//---------------------------------------------------------------------------
//деструктор
//---------------------------------------------------------------------------
CTextureFollow::~CTextureFollow(void)
{
 vector_STexture.clear();
}
//---------------------------------------------------------------------------
//сохранить анимацию текстуры
//---------------------------------------------------------------------------
void CTextureFollow::Save(FILE *file)
{
 fwrite(&Mode,sizeof(long),1,file);
 long size=vector_STexture.size();
 fwrite(&size,sizeof(long),1,file);
 for(long n=0;n<size;n++)
 {
  STexture sTexture=vector_STexture[n];
  sTexture.Name=cTexture.GetTextureName(sTexture.TextureIndex);
  fwrite(sTexture.Name.c_str(),sizeof(char),strlen(sTexture.Name.c_str())+1,file);  
 }
}
//---------------------------------------------------------------------------
//загрузить анимацию текстуры
//---------------------------------------------------------------------------
void CTextureFollow::Load(FILE *file)
{
 long size;
 fread(&Mode,sizeof(long),1,file);
 fread(&size,sizeof(long),1,file);
 vector_STexture.clear();
 for(long n=0;n<size;n++)
 {
  STexture sTexture;
  while(1)
  {
   char s;
   if (fread(&s,sizeof(char),1,file)<1) break;
   if (s==0) break;
   sTexture.Name+=s;
  }
  //найдём индекс текстуры по имени
  sTexture.TextureIndex=cTexture.GetTextureIndex(sTexture.Name);
  vector_STexture.push_back(sTexture);
 }
}
//---------------------------------------------------------------------------
//обработка анимации текстуры
//---------------------------------------------------------------------------
void CTextureFollow::Processing(void)
{
 //анимация смены текстуры
 if (Mode!=TEXTURE_FOLLOW_MODE_DISABLE)
 {
  CurrentPointer+=dPointer;
  if (Mode==TEXTURE_FOLLOW_MODE_CYCLES)
  {
   if (CurrentPointer>=vector_STexture.size()) CurrentPointer=0;
  }
  if (Mode==TEXTURE_FOLLOW_MODE_ZIGZAG)
  {
   if (CurrentPointer>=vector_STexture.size())
   {
    CurrentPointer=vector_STexture.size()-1;
    dPointer=-dPointer;
   }
   if (CurrentPointer<=0)
   {
    CurrentPointer=0;
    dPointer=-dPointer;
   }
  }
 }
}


