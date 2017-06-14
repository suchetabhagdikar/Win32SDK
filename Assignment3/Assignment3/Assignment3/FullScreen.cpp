#include <Windows.h>
BOOL gbFullScreen = false;															
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HWND ghwnd;
//Global variable Declarations
DWORD dwStyle;																		
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };								
HBRUSH ghBrush;

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
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);


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
						NULL	
						);


	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	ghwnd = hwnd;
	//message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
//	Function Prototype
	void ToggleFullScreen(void);

//	code
	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case 0x46:			//for 'f' or 'F'
				ToggleFullScreen();		
			
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
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
	
			MONITORINFO mi;										//variable to Structure of MONITORINFO
			mi.cbSize = { sizeof(MONITORINFO) };				//This is size of MONITORINFO

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
		SetWindowPlacement(ghwnd,&wpPrev);												
		SetWindowPos(ghwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER |SWP_NOZORDER |SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
	
}










