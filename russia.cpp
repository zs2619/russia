// russia.cpp : ����Ӧ�ó������ڵ㡣
//
///////////////////////////////////////////////////////////////////////////////////////
/*
*                                 zs2619@gmail.com           ��˧
*///////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "base.h"
#include "CShapeFactory.h"
#include "russia.h"


#define MAX_LOADSTRING 100
#define MS_NEWBLOCK    WM_USER+1  // ��ϢID�������µġ����顿
#define MS_DRAW        WM_USER+2 
#define WM_BACKGROUND   WM_USER+3         

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������


	CBlockPlate plate;
	CT ct(plate);
	CI ci(plate);
	CL cl(plate);
	CS cs(plate);
	CSquare co(plate);
	CShapeFactory *shapefactory=new CShapeFactory;
	bool flag=true;


// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;
	shapefactory->AddShape(&ct);
	shapefactory->AddShape(&ci);
	shapefactory->AddShape(&cl);
	shapefactory->AddShape(&cs);
	shapefactory->AddShape(&co);



	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RUSSIA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RUSSIA));
   
	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   int iScreenWide=GetSystemMetrics (SM_CXFULLSCREEN);
   hWnd = CreateWindow(szWindowClass, szTitle, WS_MINIMIZEBOX|WS_SYSMENU,
      iScreenWide/2-12*20/2, 20,
        20*12+6, 20*21+53, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SendMessage(hWnd,MS_NEWBLOCK,0,0);
   SetTimer (hWnd, 1, 550/4,NULL);//��������ʱ��
  
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...			
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
				MessageBox (hWnd, _T("��Ϸ����,�����˳� !"),_T("�˳�"), MB_OK);
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

// �����ڡ������Ϣ�������
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
