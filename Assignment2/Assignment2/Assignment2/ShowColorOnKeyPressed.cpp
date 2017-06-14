#include<Windows.h>
//Globval declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL gbFullScreen = false;
DWORD dwStyle;
HWND ghwnd;
void ToggleFullScreen();
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
int giPaintFlag = -1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("MyApplication"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	ghwnd = hwnd;
	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);


}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hBrush=0;
//	hdc = GetDC(hwnd);
	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
	
	case 0x52:																							//Red
		giPaintFlag = 1;
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case 0x47:																							//Green
		giPaintFlag = 2;
		InvalidateRect(hwnd,NULL,TRUE);
		break;

	case 0x42:																							//Blue
		giPaintFlag = 3;
		InvalidateRect(hwnd,NULL,TRUE);
		break;

	case 0x43:																							//Cyan
		giPaintFlag = 4;
		InvalidateRect(hwnd,NULL,TRUE);
		break;

	case 0x4D:																							//Magenta
		giPaintFlag = 5;
		InvalidateRect(hwnd,NULL,TRUE);
		break;
			
	case 0x4B:																							//Black
		giPaintFlag = 6;
		InvalidateRect(hwnd,NULL,TRUE);
		break;

	case 0x57:																							//White
		giPaintFlag = 7;
		InvalidateRect(hwnd,NULL,TRUE);
		break;

	case 0x59:																							//Yellow
		giPaintFlag = 8;
		InvalidateRect(hwnd,NULL,TRUE);
		break;

	case 0x46:																						 //'f' or 'F' for FullScreen
//		giPaintFlag = 9;
		ToggleFullScreen();
		break;

	case VK_ESCAPE:
		DestroyWindow(hwnd);
		break;

	default:
		MessageBox(hwnd,TEXT("Wrong key pressed no color for this key"),TEXT("Error:"),MB_OK);		
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rc);
		if (giPaintFlag == 1)
		{
			hBrush = CreateSolidBrush(RGB(255,0,0));
			FillRect(hdc,&rc, hBrush);							//To color client rectangle
		}
		if (giPaintFlag == 2)
		{
			hBrush = CreateSolidBrush(RGB(0,255,0));
			FillRect(hdc, &rc, hBrush);
		}
		if (giPaintFlag == 3)
		{
			hBrush = CreateSolidBrush(RGB(0,0,255));
			FillRect(hdc,&rc,hBrush);
		}
		if (giPaintFlag == 4)
		{
			hBrush = CreateSolidBrush(RGB(0,255,255));
			FillRect(hdc,&rc,hBrush);
		}
		if (giPaintFlag == 5)
		{
			hBrush = CreateSolidBrush(RGB(255,0,255));
			FillRect(hdc,&rc,hBrush);
		}
		if (giPaintFlag == 6)
		{
			hBrush = CreateSolidBrush(RGB(0,0,0));
			FillRect(hdc,&rc,hBrush);
		}
		if (giPaintFlag == 7)
		{
			hBrush = CreateSolidBrush(RGB(255,255,255));
			FillRect(hdc,&rc,hBrush);
		}
		if (giPaintFlag == 8)
		{
			hBrush = CreateSolidBrush(RGB(255,255,0));
			FillRect(hdc,&rc,hBrush);
		}
		
		DeleteObject(hBrush);
		EndPaint(hwnd,&ps);
		break;

	

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}		
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

	


void ToggleFullScreen(void)
{
	BOOL bIsWindowPlacement;
	BOOL bIsMonitorInfo;	
	if (gbFullScreen == false)
	{
		gbFullScreen = true;
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		
		if (dwStyle & WS_OVERLAPPEDWINDOW)				
		{
				bIsWindowPlacement = GetWindowPlacement(ghwnd, &wpPrev);			
			HMONITOR hMonitor = MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY);

			MONITORINFO mi;									
			mi.cbSize = { sizeof(MONITORINFO) };				

			bIsMonitorInfo = GetMonitorInfo(hMonitor, &mi);

		

			if (bIsWindowPlacement == TRUE && bIsMonitorInfo == TRUE)
			{

					SetWindowLong(ghwnd, GWL_STYLE, dwStyle &  ~WS_OVERLAPPEDWINDOW);
	
				SetWindowPos(ghwnd,
					HWND_TOP,
					mi.rcMonitor.left,
					mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
	
			}


		}
		ShowCursor(FALSE);
	}

	else                                 
	{
		gbFullScreen = false;
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle &  WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);												
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

}










