#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 0, y = 0;
	static int Wset[100] = {};
	//‰½•¶Žš–Ú‚Å‰üs‚µ‚½‚©ŠÇ—
	TEXTMETRIC tm;
	if(y == 100){
		MessageBox(hwnd, "‚à‚¤•¶Žš‚Í“ü‚è‚Ü‚¹‚ñ", "‚¦‚ç[", MB_OK);
		y = 99;
		x = Wset[y];
		}
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		if(wp == VK_BACK){
			if(x != 0){
				TextOut(hdc, 10 + (x - 1) * 10, 10 + y * tm.tmHeight,"    ", 4);
				x--;
			} else if(y > 0){
				y--;
				x = Wset[y];
			}
		} else if(wp == VK_RETURN){
			Wset[y] = x;
			y++;
			x = 0;
		} else {
			TextOut(hdc, 10 + x * 10, 10 + y * tm.tmHeight, (LPSTR)&wp, 1);
			x++;
		}
		ReleaseDC(hwnd, hdc);
		return 0;
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow ) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("MEMOSAMPLE");

	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
			TEXT("MEMOSAMPLE") , TEXT("‚ß‚à‚¿‚å‚¤?") ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			NULL , NULL , hInstance , NULL
	);

	if (hwnd == NULL) return -1;

	while(GetMessage(&msg , NULL , 0 , 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}