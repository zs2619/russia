// russia.cpp : 定义应用程序的入口点。
//
///////////////////////////////////////////////////////////////////////////////////////
/*
*                                 zs2619@gmail.com           张帅
*///////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "base.h"
#include "CShapeFactory.h"
#include "russia.h"


#define MAX_LOADSTRING 100
#define MS_NEWBLOCK    WM_USER+1  // 消息ID，产生新的【方块】
#define MS_DRAW        WM_USER+2 
#define WM_BACKGROUND   WM_USER+3         

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名


	CBlockPlate plate;
	CT ct(plate);
	CI ci(plate);
	CL cl(plate);
	CS cs(plate);
	CSquare co(plate);
	CShapeFactory *shapefactory=new CShapeFactory;
	bool flag=true;


// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);	
   


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;
	shapefactory->AddShape(&ct);
	shapefactory->AddShape(&ci);
	shapefactory->AddShape(&cl);
	shapefactory->AddShape(&cs);
	shapefactory->AddShape(&co);



	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RUSSIA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RUSSIA));
   
	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDC_RUSSIA));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject (BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_RUSSIA);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中
   int iScreenWide=GetSystemMetrics (SM_CXFULLSCREEN);
   hWnd = CreateWindow(szWindowClass, szTitle, WS_MINIMIZEBOX|WS_SYSMENU,
      iScreenWide/2-12*20/2, 20,
        20*12+6, 20*21+53, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SendMessage(hWnd,MS_NEWBLOCK,0,0);
   SetTimer (hWnd, 1, 550/4,NULL);//设置下落时间
  
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hpen;   
	static CShape *shape;
	if(flag){
	shape=shapefactory->RandomShape();
	flag=false;
	}
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
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
	case WM_PAINT:		
		{
			hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...			
			hpen =CreatePen (PS_SOLID,1,RGB(255,255,255));
			SelectObject (hdc,hpen);
			shape->Draw(hdc);
			plate.UpDate(hdc);	
	
		EndPaint(hWnd, &ps);
		break;
		}
	case WM_TIMER:
		{
			if(shape->DownMove())			
			{
				InvalidateRect (hWnd, NULL, TRUE);
				break;
			}
		    //MessageBox(hWnd,_T("shuai"),_T("shuai"),0);
			
			shape->SetPlate();
	
			SendMessage(hWnd,WM_BACKGROUND,0,0);
			if (plate.OutBound())
			{
				KillTimer (hWnd, 1);
				MessageBox (hWnd, _T("游戏结束,即将退出 !"),_T("退出"), MB_OK);
				PostQuitMessage (0);
			}
			
           
			break;
		}
	case MS_NEWBLOCK:
		{ 
		  
		  shape->Initialize();
         InvalidateRect (hWnd, NULL, TRUE);		 			
         break;
		}
	case WM_KEYDOWN:
        switch((int)wParam)
        {
        case VK_LEFT:
			shape->LeftMove();
			break;
		 case VK_RIGHT:
			 shape->RightMove();
			 break;
        case VK_DOWN:
			shape->DownMove();
			break;
        case VK_UP:
			shape->ChangeShape();
			break;
		}
       InvalidateRect (hWnd, NULL, TRUE);
	   break;
   case WM_BACKGROUND:
	   hdc = BeginPaint(hWnd, &ps);
	   
	   hpen =CreatePen (PS_SOLID,1,RGB(255,255,255));
	   SelectObject (hdc,hpen);
	   plate.UpDate(hdc);
	   EndPaint(hWnd, &ps);
	   flag=true;
	   SendMessage(hWnd,MS_NEWBLOCK,0,0);
	   break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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
