#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

long LoadLong(FILE *file);//загрузка числа типа long
void SaveLong(FILE *file,long value);//запись числа типа long

unsigned char LoadUChar(FILE *file);//загрузка числа типа unsigned char
void SaveUChar(FILE *file,unsigned char value);//запись числа типа unsigned char

float LoadFloat(FILE *file);//загрузка числа типа float
void SaveFloat(FILE *file,float value);//запись числа типа float

short LoadShort(FILE *file);//загрузка числа типа short
unsigned long LoadULong(FILE *file);//загрузка числа типа unsigned long
unsigned short LoadUShort(FILE *file);//загрузка числа типа unsigned short

void SaveCharArray(FILE *file,const char *ptr,long size);//сохранить массив типа char
void LoadCharArray(FILE *file,char *ptr,long size);//загрузить массив типа char

#endif