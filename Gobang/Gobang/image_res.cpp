
#include"image_res.h"

my_namespace_begin

/****************************************************************************************************************************************
                                author:Deomon
								Time:2017/10/5
*****************************************************************************************************************************************/

//load to dcMem
void LoadtoDcmem(HDC dcMem, WCHAR const*path, int wide, int hight, int nXDest , int nYDest)
{
	
	HDC hdc= CreateCompatibleDC(dcMem);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc,800, 600);
	SelectObject(hdc, bitmap);


	HBITMAP map = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, wide, hight, LR_LOADFROMFILE);
	SelectObject(hdc, map);

	
	BitBlt(dcMem, nXDest, nYDest, wide, hight,hdc,0, 0, SRCCOPY);


	DeleteDC(hdc);
	DeleteObject(bitmap);
	DeleteObject(map);

}

//load to dcMem(透明加载）
void Transparent_LoadtoDcmem(HDC dcMem, WCHAR const*path, UINT R, UINT G, UINT B, int wide, int hight, int nXOriginDest, int nYOriginDest)
{
	HDC hdc = CreateCompatibleDC(dcMem);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, 800, 600);
	SelectObject(hdc, bitmap);


	HBITMAP map = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP,wide,hight, LR_LOADFROMFILE);
	SelectObject(hdc, map);


	TransparentBlt(dcMem, nXOriginDest, nYOriginDest,wide,hight, hdc, 0, 0, wide, hight, RGB(R, G, B));

	DeleteDC(hdc);
	DeleteObject(bitmap);
	DeleteObject(map);

}



//draw
void DrawAll(HWND hwnd,UINT Message,WPARAM wparam, LPARAM lparam)
{

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	int xPos = point.x;
	int yPos = point.y;


	RECT rect = { 0 };
	GetClientRect(hwnd, &rect);
	HDC hdc = GetDC(hwnd);
	HDC dcMem = CreateCompatibleDC(hdc);;
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	SelectObject(dcMem, bitmap);

	/***************************************
	         load background
	****************************************/
	LoadtoDcmem(dcMem, TEXT("myres//background.bmp"), 800, 600);
	

	/*******************************************************************************
	                     判断加载开始游戏，悔棋，求和，退出游戏（有色图）
	********************************************************************************/
	if (xPos > 645 && xPos < 745 && yPos>220 && yPos < 250)
	{
		LoadtoDcmem(dcMem, TEXT("myres//startgame_2.bmp"), 100, 30,645,220);
	
	}

	if (xPos > 645 && xPos < 745 && yPos>275 && yPos <305)
	{

		LoadtoDcmem(dcMem, TEXT("myres//begback_2.bmp"), 100, 30,645,275);
	}

	if (xPos > 645 && xPos < 745 && yPos>350 && yPos <380)
	{

		LoadtoDcmem(dcMem, TEXT("myres//begpeace_2.bmp"), 100, 30,645,350);
	}

	if (xPos >695 && xPos< 795 && yPos>570 && yPos <600)
	{

		LoadtoDcmem(dcMem, TEXT("myres//exitgame_2.bmp"), 100, 30,695,570);
	}
/*********************************************************************************************
                       
					   判断加载可以下棋的标志棋（提示图）
                
*********************************************************************************************/
	/*if (xPos > 55 && xPos < 545 && yPos>55 && yPos < 545)
	{


    }
    */


/*********************************************************************************************
                         
						 加载鼠标的棋子

**********************************************************************************************/
	if (xPos > 55 && xPos < 545 && yPos>55 && yPos < 545)
	{

		Transparent_LoadtoDcmem(dcMem, TEXT("myres//black.bmp"), 255, 255, 255,35, 35, xPos-17.5, yPos-17.5);
    }

/**********************************************************************************************************

                               遍历数组GobangMap,加载棋子

**********************************************************************************************************/
	
	for (int x = 0;x < Row;x++)
	{

		for (int y = 0;y < Line;y++)
		{
			if (GobangMap[x][y] == 1)//加载黑色棋子（本方）
			{
				Transparent_LoadtoDcmem(dcMem, TEXT("myres//black.bmp"), 255, 255, 255,35,35,x*35.5+37.5, y*35+37.5);
			}
			if (GobangMap[x][y] == -1)//加载绿色棋子（对方）
			{
				Transparent_LoadtoDcmem(dcMem, TEXT("myres//green.bmp"), 255, 255, 255, 35, 35, x*35 +37.5, y*35 +37.5);
			}
		}
	}

	BitBlt(hdc, 0, 0,800,600, dcMem, 0,0, SRCCOPY);


	DeleteDC(hdc);
	DeleteDC(dcMem);
	DeleteObject(bitmap);


}


my_namespace_end