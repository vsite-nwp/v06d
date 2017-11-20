#include "main.h"
#include <cmath>
#include "rc.h"
const double pi = 3.1415926;

int howMany(HWND handle,int br) 
{	
	NumDialog numDial;
	numDial.broj = br;
	if (numDial.DoModal(NULL, handle) == IDOK)
		br = numDial.broj;
	
	return br;
};

COLORREF GetColor(HWND parent, COLORREF cur) {
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = custCols;
	cc.rgbResult = cur;
	if (ChooseColor(&cc))
		cur = cc.rgbResult;
	return cur;
}


int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, broj);
	return true;
}

bool NumDialog::OnOK(){
NumDialog:broj = GetInt(IDC_EDIT1);
	return true;
}

void MainWindow::OnPaint(HDC hdc){

	RECT mainRect;
	GetClientRect(*this, &mainRect);
	int size = mainRect.bottom > mainRect.right ? mainRect.right / 4 : mainRect.bottom / 4;
	HBRUSH cetka = CreateSolidBrush(mojaBoja);
	HBRUSH staraCetka = SelectBrush(hdc, cetka);
	SelectPen(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	SetViewportOrgEx(hdc, mainRect.right / 2, mainRect.bottom / 2, NULL);
	for (float n= 0;  n < 360  ;  n+= 360./mojBroj) {
		int circleMiddleX = size*cos(n*pi/180);
		int circleMiddleY = size*sin(n*pi / 180);
		::Ellipse(hdc, circleMiddleX - size, circleMiddleY- size, circleMiddleX+ size, circleMiddleY+ size);
	}
	SelectBrush(hdc, staraCetka);
	DeleteObject(cetka);
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR:
			mojaBoja = GetColor(*this, mojaBoja);
			InvalidateRect(*this, NULL, true);
			break;
		case ID_NUMBER:
			mojBroj=howMany(*this, mojBroj);
			InvalidateRect(*this, NULL, true);
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;	
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

