/***************************************************************************

                 function:this file is used to load  images
				 author:Demon
				 Time:2017/10/4

***************************************************************************/
#pragma once
#include"precompiled_header.h"
#include"arithmetic.h"
extern  int GobangMap[Row][Line];

my_namespace_begin

//load to dcMem(不透明加载）
void LoadtoDcmem(HDC dcMem,WCHAR const*path, int wide, int hight,int nXDest = 0, int nYDest = 0);

//load to dcMem(透明加载）
void Transparent_LoadtoDcmem(HDC dcMem, WCHAR const*path, UINT R, UINT G, UINT B , int wide, int hight,int nXOriginDest,int nYOriginDest);

//draw
void DrawAll(HWND hwnd,UINT Message,WPARAM wparam, LPARAM lparam);



my_namespace_end