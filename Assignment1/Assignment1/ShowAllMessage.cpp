//Headers
#include<Windows.h>
#include<windowsx.h>

//GLOBAL DECLARATIONS
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	//variable declarations
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
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
		
	//Register class
	RegisterClassEx(&wndclass);

	//create window
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

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
	
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int coordinateX;
	int coordinateY;
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd,
			TEXT("WM_CREATE MESSAGE IS CREATED "),	
		TEXT("WM_CREATE"),
			MB_OK);
		break;

	case WM_LBUTTONDOWN:



			coordinateX = GET_X_LPARAM(lParam);
			coordinateY = GET_Y_LPARAM(lParam);
		
			char buffer[256];
		
			wsprintf(buffer,"LBUTTONDOWN X COORDINATE IS %d AND Y COORDINATE IS %d",coordinateX,coordinateY);
		
			MessageBox(
				hwnd,
				buffer,
				TEXT("WM_LBUTTONDOWN"),
				MB_OK);

		break;

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			MessageBox(hwnd,
						TEXT("ESCAPE KEY IS PRESSED"),
						TEXT("ESCAPE KEY"),
						MB_OK);
			break;
		case 0x41:			        																		//A
			MessageBox(
				hwnd,
				TEXT( "A KEY IS PRESSED"),
				TEXT("A KEY"),
				MB_OK);
			break;

		case 0x42:																							//B
			MessageBox(
				hwnd,
				TEXT("B KEY IS PRESSED"),
				TEXT("B KEY"),
				MB_OK);
			break;

		case 0x4C:																							//L
			MessageBox(hwnd,
				TEXT("KEY IS PRESSED"),
				TEXT("L KEY"),
				MB_OK);
			break;

		case 0x46:																							//F
			MessageBox(hwnd,
				TEXT("F KEY IS PRESSED"),
				TEXT("F KEY"),
				MB_OK);
			break;

		case 0x54:																							//T
			MessageBox(hwnd,
				TEXT("T KEY IS PRESSES"),
				TEXT("T KEY"),
				MB_OK);
			break;
				
		case 0x51:																							//Q
			MessageBox(hwnd,
				TEXT("Q KEY IS PRESSED"), 
				TEXT("Q KEY"),
				MB_OK);
			break;
		}
		break;

	case WM_DESTROY:
		MessageBox(hwnd,
					TEXT("Windows getting closed.."),
					TEXT("WM_DESTROY"),
					MB_OK);
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}


















