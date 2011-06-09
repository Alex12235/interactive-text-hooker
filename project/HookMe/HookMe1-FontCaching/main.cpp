/*  Copyright (C) 2010-2011  kaosu (qiupf2000@gmail.com)
 *  This file is part of the Interactive Text Hooker.

 *  Interactive Text Hooker is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// HookMe1.cpp : Defines the entry point for the application.
//

//#include "stdafx.h"
#include <windows.h>
//#include <CommCtrl.h>
#include "AVL.h"
#include "resource.h"
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;								// current instance
HWND hwndMain;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ScriptThread(LPVOID);

int main()
{
	HINSTANCE hInstance=GetModuleHandle(0);
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HOOKME1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, SW_SHOW))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOOKME1));
	CloseHandle(CreateThread(0,0,ScriptThread,hwndMain,0,0));
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	TerminateProcess(GetCurrentProcess(),0);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOOKME1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= 0;//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HOOKME1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	hInst = hInstance; // Store instance handle in our global variable

	hwndMain = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED|WS_SYSMENU,
		100, 100, 900, 700, NULL, NULL, hInstance, NULL);

	if (!hwndMain)
	{
		return FALSE;
	}

	ShowWindow(hwndMain, nCmdShow);
	UpdateWindow(hwndMain);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
static LPCWSTR str=L"���@�Ėڟ��΁@�u��y�͔L�ł���v���";
HBITMAP hBitmap, hOldBmp;
HFONT hFont;

GLYPHMETRICS gm;
BLENDFUNCTION ftn;
DWORD running,click;
HANDLE hClickEvent;
LPWSTR text[]={
	L"��y�͔L�ł���B���O�͂܂������B",
	L"�ǂ��Ő��ꂽ���Ƃ�ƌ��������ʁB",
	L"���ł����Â����߂��߂������Ńj���[�j���[�����Ă����������͋L�����Ă���B",
	L"��y�͂����Ŏn�߂Đl�ԂƂ������̂������B",
	L"���������Ƃŕ����Ƃ���͏����Ƃ����l�Ԓ��ň���ֈ��Ȏ푰�ł������������B",
	L"���̏����Ƃ����͎̂��X��X��߂��ĎςĐH���Ƃ����b�ł���B",
	L"���������̓����͉��Ƃ����l���Ȃ���������ʒi�������Ƃ��v��Ȃ������B",
	L"�����ނ̏��ɍڂ����ăX�[�Ǝ����グ��ꂽ���������t���t�������������������΂���ł���B",
	L"���̏�ŏ����������ď����̊�������̂�������l�ԂƂ������̂̌��n�ł��낤�B",
	L"���̎����Ȃ��̂��Ǝv�������������ł��c���Ă���B",
	L"���т������đ�������ׂ��͂��̊炪��邵�Ă܂�Ŗ�ʂ��B",
	L"���̌�L�ɂ������Ԉ�����������ȕЗւɂ͈�x���o��킵�������Ȃ��B",
	L"�݂̂Ȃ炸��̐^�������܂�ɓˋN���Ă���B",
	L"�������Ă��̌��̒����玞�X�Ղ��Ղ��Ɖ��𐁂��B",
	L"�ǂ����􂹂ۂ��Ď��Ɏ�����B",
	L"���ꂪ�l�Ԃ̈��މ����Ƃ������̂ł��鎖�͂悤�₭���̍��m�����B",
	L"���̏����̏��̗��ł��΂炭�͂悢�S���ɍ����Ă��������A���΂炭����Ɣ��ȑ��͂ŉ^�]���n�߂��B",
	L"�����������̂����������������̂�����Ȃ������ÂɊႪ���B",
	L"���������Ȃ�B���ꏕ����Ȃ��Ǝv���Ă���ƁA�ǂ���Ɖ������ĊႩ��΂��o���B",
	L"����܂ł͋L�����Ă��邪���Ƃ͉��̎���炢����l���o�����Ƃ��Ă�����Ȃ��B",
	L"�ӂƋC���t���Č���Ə����͂��Ȃ��B�������񂨂����Z�킪��D�������ʁB",
	L"�̐S�̕�e�����p���B���Ă��܂����B���̏㍡�܂ł̏��Ƃ͈���Ė��Âɖ��邢�B",
	L"��𖾂��Ă����ʂ��炢���B",
	L"�͂Ăȉ��ł��e�q�����������ƁA�̂��̂������o���Č���Ɣ��ɒɂ��B",
	L"��y�͘m�̏ォ��}�ɍ����̒��֊��Ă�ꂽ�̂ł���B"
};
static const DWORD sentence_count=sizeof(text)/sizeof(LPWSTR);
static const DWORD alpha_depth=16;
static const DWORD char_per_line=24;
class IthGlyph
{
public:
	IthGlyph(HDC hdc):hDC(hdc), glyph_buffer(0), hBmp(0)
	{
		hMemDC=CreateCompatibleDC(hdc);
	}
	~IthGlyph()
	{
		if (hBmp) DeleteObject(hBmp);
		if (hMemDC) DeleteDC(hMemDC);
		if (glyph_buffer) delete glyph_buffer;
		glyph_buffer=0;
		glyph_char=0;
		hMemDC=0;
		hBmp=0;
		hDC=0;
	}
	int InitGlyph(wchar_t ch)
	{
		DWORD len,i,ii,j,k,t;
		BYTE *buffer,*bptr;
		LPVOID ptr;
		MAT2 mt={};
		glyph_char=ch;
		mt.eM11.value=1;
		mt.eM22.value=-1;
		len=GetGlyphOutline(hDC,ch,GGO_GRAY8_BITMAP,&gm,0,0,&mt);
		if (len==-1) return -1;
		glyph_buffer=new BYTE[len];
		len=GetGlyphOutline(hDC,ch,GGO_GRAY8_BITMAP,&gm,len,glyph_buffer,&mt);
		if (len==-1) return -1;	
		BITMAPINFOHEADER info={sizeof(info),gm.gmBlackBoxX,gm.gmBlackBoxY,1,32,BI_RGB,0,0,0,0,0};
		hBmp=CreateDIBSection(hMemDC,(BITMAPINFO*)&info,DIB_RGB_COLORS,&ptr,0,0);
		buffer=(BYTE*)ptr;
		bptr=glyph_buffer;
		k=(gm.gmBlackBoxX+3)&~3;t=0;ii=0;
		for (i=0;i<gm.gmBlackBoxY;i++)
		{
			for (j=0;j<gm.gmBlackBoxX;j++)
			{
				bptr[j]=64-bptr[j];
				if (bptr[j]) 
					buffer[0]=buffer[1]=buffer[2]=(bptr[j]<<2)-1;
				buffer+=4;
			}
			bptr+=k;
		}
		SelectObject(hMemDC,hBmp);
		return 0;
	}
	int DrawGlyph(HDC hdc, int x, int y, int height)
	{
		if (glyph_buffer==0) return -1;
		return BitBlt(hdc, x+gm.gmptGlyphOrigin.x, y+height-gm.gmBlackBoxY+gm.gmptGlyphOrigin.y, 
			gm.gmBlackBoxX, gm.gmBlackBoxY, hMemDC, 0, 0, SRCCOPY);
	}
private:
	HDC hDC, hMemDC;
	HBITMAP hBmp;
	UINT glyph_char;
	GLYPHMETRICS gm;
	BYTE* glyph_buffer;
};
#define DEFAULT_GLYPH_TABLE_SIZE 0x1000

//Turn on to disable caching.
//#define GLYPH_NO_CACHING 
class IthGlyphManager : public AVLTree<wchar_t, DWORD>
{
public:
	IthGlyphManager()
	{	
		glyph_ptr_table=(IthGlyph**)VirtualAlloc(0,DEFAULT_GLYPH_TABLE_SIZE,MEM_COMMIT,PAGE_READWRITE);
		size=DEFAULT_GLYPH_TABLE_SIZE;
		count=0;
	}
	~IthGlyphManager()
	{
		for (DWORD i=0;i<count;i++) delete glyph_ptr_table[i];
		VirtualFree(glyph_ptr_table,size,MEM_RELEASE);
	}
	void ReallocGlyphTable()
	{
		LPVOID buffer=VirtualAlloc(0,size<<1,MEM_COMMIT,PAGE_READWRITE);
		memcpy(buffer,glyph_ptr_table,count*sizeof(IthGlyph*));
		VirtualFree(glyph_ptr_table, size, MEM_RELEASE);
		size<<=1;
		glyph_ptr_table=(IthGlyph**)buffer;
	}
	IthGlyph* InsertGlyph(HDC hDC, wchar_t ch)
	{
#ifndef GLYPH_NO_CACHING	
		TreeNode<wchar_t, DWORD> *p;
		p=Search(ch);
		if (p) return glyph_ptr_table[p->data];	
#endif
		IthGlyph* g=new IthGlyph(hDC);
		g->InitGlyph(ch);
#ifndef GLYPH_NO_CACHING
		Insert(ch, count);
		if (count*sizeof(IthGlyph*)==size) ReallocGlyphTable();
		glyph_ptr_table[count]=g;
		count++;
#endif
		return g;
	}
	void ReleaseGlyph(IthGlyph* g)
	{
		delete g;
	}
private:
	IthGlyph **glyph_ptr_table;
	DWORD size, count;
};

IthGlyphManager* glyph_manager;
int IthDrawText(HDC hDC, LPCWSTR text, int len, int x, int y)
{
	TEXTMETRIC tm;
	GetTextMetrics(hDC,&tm);
	IthGlyph* g;
	for (int i=0;i<len;i++)
	{
		g=glyph_manager->InsertGlyph(hDC,text[i]);
		g->DrawGlyph(hDC, x+i*tm.tmMaxCharWidth, y, tm.tmHeight);
		//glyph_manager->ReleaseGlyph(g);
	}
	return 0;
}
DWORD WINAPI ScriptThread(LPVOID p)
{
	HWND hWnd=(HWND)p;
	HBRUSH brush;
	HBITMAP bmp;
	HDC hDC, hMemDC;
	RECT rect;
	SIZE size;
	int i,j,x,y,len;
	Sleep(100);
	hDC = GetDC(hWnd);
	hMemDC = CreateCompatibleDC( hDC );
	GetClientRect(hWnd,&rect);
	bmp = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
	hFont = CreateFont( 30, 0, 0, 0, FW_THIN,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH |
		FF_DONTCARE,
		L"MS Mincho" );
	SelectObject(hDC, hFont);
	SelectObject(hMemDC, hFont);
	SelectObject(hMemDC, bmp);
	brush = CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
	FillRect(hMemDC,&rect,brush);
	FillRect(hDC,&rect,brush);

	TEXTMETRIC tm;
	GetTextMetrics(hDC,&tm);
	len=wcslen(str);
	size.cx=tm.tmMaxCharWidth*len;
	size.cy=tm.tmHeight+10;
	IthDrawText(hMemDC, str, len, 0, 0);

	ftn.SourceConstantAlpha=0x20;
	for (i=0;i<alpha_depth;i++)
	{
		if (!running) break;
		Sleep(100);
		GetClientRect(hWnd,&rect);
		GdiAlphaBlend(hDC, (rect.right-size.cx)>>1, (rect.bottom-size.cy)>>1, size.cx, size.cy, hMemDC, 0, 0, size.cx, size.cy, ftn);
		UpdateWindow(hWnd);
	}
	FillRect(hMemDC,&rect,brush);

	for (i=0;i<alpha_depth;i++)
	{
		if (!running) break;
		Sleep(100);
		GdiAlphaBlend(hDC, (rect.right-size.cx)>>1, (rect.bottom-size.cy)>>1, size.cx, size.cy, hMemDC, 0, 0, size.cx, size.cy, ftn);
		UpdateWindow(hWnd);
	}
	FillRect(hDC,&rect,brush);

	SelectObject(hMemDC,hFont);
	for (i=0;i<sentence_count;i++)
	{
		len=wcslen(text[i]);
		size.cx=len*tm.tmMaxCharWidth;
		size.cy=tm.tmHeight+10;
		HBITMAP text_bmp=CreateCompatibleBitmap(hDC, size.cx, size.cy);
		RECT r={0,0,size.cx, size.cy};
		SelectObject(hMemDC,text_bmp);
		FillRect(hMemDC,&r,brush);
		IthDrawText(hMemDC,text[i],len,0,0);
		j=0; y=0; 
		x=0; click=0;
		while (len>char_per_line)
		{
			size.cx=char_per_line*tm.tmMaxCharWidth;
			len-=char_per_line;
			j=20;		
			while (j<size.cx)
			{
				if (click) break;
				GdiAlphaBlend(hDC, 0, y, j, size.cy, hMemDC, x, 0, j, size.cy, ftn);
				Sleep(20);
				j+=20;

			}
			BitBlt(hDC,0, y, size.cx, size.cy, hMemDC, x, 0, SRCCOPY);
			y+=size.cy;
			x+=size.cx;
		}
		size.cx=len*tm.tmMaxCharWidth;
		j=20;
		while (j<size.cx)
		{
			if (click) break;
			GdiAlphaBlend(hDC, 0, y, j, size.cy, hMemDC, x, 0, j, size.cy, ftn);
			Sleep(20);
			j+=20;
		}
		BitBlt(hDC,0, y, size.cx, size.cy, hMemDC, x, 0, SRCCOPY);
		y+=size.cy;
		UpdateWindow(hWnd);
		SelectObject(hMemDC,bmp);
		DeleteObject(text_bmp);
		ResetEvent(hClickEvent);
		WaitForSingleObject(hClickEvent,-1);
		ResetEvent(hClickEvent);
		FillRect(hDC,&rect,brush);
	}

	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hDC);
	DeleteObject(bmp);
	MessageBox(0,L"Script over.",L"Over",0);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hDC;
	RECT cli;
	switch (message)
	{
	case WM_CREATE:
		{
			glyph_manager=new IthGlyphManager;
			running=1;
			GetClientRect(hWnd,&cli);
			MoveWindow(hWnd,100,100,1700-cli.right,1300-cli.bottom,0);
			ftn.BlendOp = AC_SRC_OVER;
			hClickEvent=CreateEvent(0,1,0,0);

		}

		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		if (wParam==VK_RETURN)
		{
			SetEvent(hClickEvent);
			click=1;
		}
		break;
	case WM_LBUTTONDOWN:
		SetEvent(hClickEvent);
		click=1;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		running=0;
		delete glyph_manager;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
