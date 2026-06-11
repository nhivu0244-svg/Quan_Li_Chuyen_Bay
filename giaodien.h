#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

void gotoXY(int x, int y);
void SetColor(int color);
void ShowCur(bool cursorVisibility);
void ClearArea(int x, int y, int w, int h) ;
int ReadKey();
int GetConsoleWidth();
void VeKhung();
void VeKhungDSHanhKhach();
void VeKhungHuongDan();
void VeMenuChinh(int chon);
void VeMenuMayBay(int chon);
void VeMenuChuyenBay(int chon);
void VeMenuHanhKhach(int chon);
void VeMenuVe(int chon);
void VeKhungNhapLieu();
void VeKhungDSMB();
void VeKhungNhapLieuCB();
void VeKhungDSCB();
void VeKhungHuongDanCB();
void VeKhungNhapLieuVe();
void VeKhungDSV();
void InitConsole(int cols, int lines);
void DisableQuickEdit();
void ClearConsole();
void VeKhungDon(int t, int b, int l, int r);
