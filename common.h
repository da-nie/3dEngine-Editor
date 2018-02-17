#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

long LoadLong(FILE *file);//�������� ����� ���� long
void SaveLong(FILE *file,long value);//������ ����� ���� long

unsigned char LoadUChar(FILE *file);//�������� ����� ���� unsigned char
void SaveUChar(FILE *file,unsigned char value);//������ ����� ���� unsigned char

float LoadFloat(FILE *file);//�������� ����� ���� float
void SaveFloat(FILE *file,float value);//������ ����� ���� float

short LoadShort(FILE *file);//�������� ����� ���� short
unsigned long LoadULong(FILE *file);//�������� ����� ���� unsigned long
unsigned short LoadUShort(FILE *file);//�������� ����� ���� unsigned short

void SaveCharArray(FILE *file,const char *ptr,long size);//��������� ������ ���� char
void LoadCharArray(FILE *file,char *ptr,long size);//��������� ������ ���� char

#endif