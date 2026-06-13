#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include "bien.h"

using namespace std;
// ================= CONSOLE UTILS =================
void gotoXY(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// an hien con tro
void ShowCur(bool cursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorCtrl;
    GetConsoleCursorInfo(handle, &cursorCtrl);
    cursorCtrl.bVisible = cursorVisibility;
    SetConsoleCursorInfo(handle, &cursorCtrl);
}
void ClearArea(int x,int y,int w,int h)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD written;

    for(int i=0;i<h;i++)
    {
        COORD pos = {(SHORT)x,(SHORT)(y+i)};

        FillConsoleOutputCharacter(
            hOut,
            ' ',
            w,
            pos,
            &written
        );
    }
}
int ReadKey() {
    int c = _getch();
    if (c == 224 || c == 0) { // ph?m dac biet
        int k = _getch();
        if (k == 72) return 1; // UP
        if (k == 80) return 2; // DOWN
        if (k == 75) return 5; // trai
        if (k == 77) return 6;// phai
    }
    if (c == 13) return 3; // ENTER
    if (c == 27) return 4; // ESC
    return 0;
}

int GetConsoleWidth() {// lay chieu rong console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// ================= GIAO DIEN =================
void VeKhung(){
    int width = GetConsoleWidth();

    int boxWidth = 50; // ?? d? r?ng khung
    int left = (width - boxWidth) / 2;
    int right = left + boxWidth;

    int top = 7, bottom = 20;

    // ===== 4 g?c =====
    gotoXY(left, top);     cout << (char)201;
    gotoXY(right, top);    cout << (char)187;
    gotoXY(left, bottom);  cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    // ===== c?nh tr?n du?i =====
    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top);    cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }

    // ===== c?nh tr?i ph?i =====
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i);   cout << (char)186;
        gotoXY(right, i);  cout << (char)186;
    }

    // ===== TI?U ?? =====
    string title = " QUAN LI ";
    int x = (left + right - title.length()) / 2;
    gotoXY(x, top);
    cout << title;
}
void VeKhungDSHanhKhach(){
    int width = GetConsoleWidth();

    int boxWidth = 100; // ?? d? r?ng khung
    int left = (width - boxWidth) / 2;
    int right = left + boxWidth;

    int top = 2, bottom = 25;

    // ===== 4 g?c =====
    gotoXY(left, top);     cout << (char)201;
    gotoXY(right, top);    cout << (char)187;
    gotoXY(left, bottom);  cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    // ===== c?nh tr?n du?i =====
    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top);    cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }

    // ===== c?nh tr?i ph?i =====
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i);   cout << (char)186;
        gotoXY(right, i);  cout << (char)186;
    }

    // ===== TI?U ?? =====
    gotoXY(left + 30, 4); //left = 10
    cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY";
    gotoXY(left + 3,  7); cout << "STT";
    gotoXY(left + 12, 7); cout << "SO VE";
    gotoXY(left + 25, 7); cout << "SO CMND";
    gotoXY(left + 45, 7); cout << "HO TEN KHACH HANG";
    gotoXY(left + 85, 7); cout << "PHAI";
}
void VeKhungHuongDan(){
    int width = GetConsoleWidth();

    int boxWidth = 50;
    int left = (width - boxWidth) / 2;
    int right = left + boxWidth;

    int top = 22, bottom = 25; // ?? n?m du?i menu ch?nh

    // ===== 4 g?c =====
    gotoXY(left, top);     cout << (char)201;
    gotoXY(right, top);    cout << (char)187;
    gotoXY(left, bottom);  cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    // ===== canh =====
    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top);    cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }

    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i);   cout << (char)186;
        gotoXY(right, i);  cout << (char)186;
    }

    // ===== n?i dung =====
    string text = " Mui Ten: Di chuyen   ENTER: Chon   ESC: Thoat";

    int x = (left + right - text.length()) / 2;
    int y = (top + bottom) / 2;

    gotoXY(x, y);
    cout << text;
}
void VeMenuChinh(int chon){
	string menu[] = {
        "May bay",
        "Chuyen bay",
        "Hanh khach",
        "Ve",
        "Thong ke"
    };
    int left = 30, top = 7;
    for (int i = 0; i < 5; i++) {
        gotoXY(left + 8, top + 3 + i * 2);

        if (i == chon) {
            SetColor(10);
            cout << "> " << menu[i] << "      ";
            SetColor(7);
        } else {
            cout << "  " << menu[i];
        }
    }
}
void VeMenuMayBay(int chon){
	string menu[] = {"Them May Bay", "Sua May Bay", "Xoa May Bay"};
	for (int i = 0; i < 3; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // M?u xanh duong s?ng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeMenuChuyenBay(int chon){
	string menu[] = {"Them Chuyen Bay", "Hieu Chinh Thoi Gian", "Sua Trang Thai", "DS chuyen bay"};
	for (int i = 0; i < 4; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // M?u xanh duong s?ng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeMenuHanhKhach(int chon){
	string menu[] = {"Them Hanh Khach", "In DS Hanh Khach"};
	for (int i = 0; i < 2; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // M?u xanh duong s?ng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeMenuVe(int chon){
	string menu[] = {"Dat ve", "Huy ve", "DS ve trong"};
	for (int i = 0; i < 3; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // M?u xanh duong s?ng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeKhungNhapLieu(){
	int top = 2, bottom = 12, left = 2, right = 35;
    // V? khung tuong t? nhu c?c h?m tru?c c?a b?n
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
    
    // Cac nhan nhap lieu
    gotoXY(left + 2, top + 2); cout << "So Hieu MB: ";
    gotoXY(left + 2, top + 4); cout << "Loai MB   : ";
    gotoXY(left + 2, top + 6); cout << "So cho    : ";
    gotoXY(2, BOT - 1); cout << "ENTER : Chon    ESC : Thoat";
}
void VeKhungDSMB(){
    int top = 2, bottom = 25, left = 40, right = 115;
    // Ve khung
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
    
    // Tieu de cot
    gotoXY(left + 5, top + 1);
    SetColor(14);
    gotoXY(left + 5, top + 1); cout << "SO HIEU"; 
    gotoXY(left + 25, top + 1); cout << "LOAI MAY BAY"; 
    gotoXY(left + 55, top + 1); cout << "SO CHO";
    SetColor(7);
}
void VeKhungNhapLieuCB(){
	int top = 2, bottom = 20, left = 2, right = 38;
  
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
    
    SetColor(14);
    gotoXY(left + 2, top + 2); cout << "So Hieu MB         : ";
    gotoXY(left + 2, top + 4); cout << "Ma chuyen bay      : ";
    gotoXY(left + 2, top + 6); cout << "San bay den        : ";
    gotoXY(left + 2, top + 8); cout << "Ngay gio ( hh:mm dd/mm/yyyy) : ";
    gotoXY(left + 2, top + 12);cout << "Trang thai         : ";
    SetColor(7);
    gotoXY(2, BOT - 1); cout << "ENTER : Chon    ESC : Thoat";

}
void VeKhungDSCB(){
    int top = 2, bottom = 25, left = 40, right = 115;
    // Ve khung
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
    
    SetColor(14);
    gotoXY(left + 3, top + 1); cout << "MA CB"; 
    gotoXY(left + 15, top + 1); cout << "NOI DEN"; 
    gotoXY(left + 32, top + 1); cout << "SO HIEU";
    gotoXY(left + 48, top + 1); cout << "NGAY GIO";
    gotoXY(left + 63, top + 1); cout << "TRANG THAI";
    SetColor(7);
}
void VeKhungHuongDanCB(){
	int top = 21, bottom = 28, left = 2 , right = 38;
  
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
    
    SetColor(14);
    gotoXY(left + 2, top + 1); cout << "           Chu Thich          ";
	gotoXY(left + 2, top + 3); cout << "    0:Huy chuyen    1:Con ve";
    gotoXY(left + 2, top + 5); cout << "    2:Het ve        3:Hoan tat";
    SetColor(7);
}
void VeKhungNhapLieuVe(){
	int top = 2, bottom = 18, left = 2, right = 35;
    // V? khung tuong t? nhu c?c h?m tru?c c?a b?n
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
    
    // Cac nhan nhap lieu
    gotoXY(left + 2, top + 2); cout << "Ma chuyen bay: ";
    gotoXY(left + 2, top + 4); cout << "CCCD         : ";
    gotoXY(left + 2, top + 6); cout << "Ho           : ";
    gotoXY(left + 2, top + 8); cout << "Ten          : ";
    gotoXY(left + 2, top + 10);cout << "Phai         : ";
    gotoXY(left + 2, top + 12);cout << "So ghe       : ";
}
void VeKhungDSV(){
    int top = 2, bottom = 28, left = 40, right = 115;
    // Ve khung
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
}

void InitConsole(int cols, int lines)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufSize = { (SHORT)cols, (SHORT)(lines + 200) };
    SetConsoleScreenBufferSize(hOut, bufSize);

    SMALL_RECT winRect = { 0, 0, (SHORT)(cols - 1), (SHORT)(lines - 1) };
    SetConsoleWindowInfo(hOut, TRUE, &winRect);

    COORD bufSize2 = { (SHORT)cols, (SHORT)lines };
    SetConsoleScreenBufferSize(hOut, bufSize2);

    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &info);
}

void DisableQuickEdit()
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;

    GetConsoleMode(hIn, &mode);

    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_EXTENDED_FLAGS;

    SetConsoleMode(hIn, mode);
}
void ClearConsole()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    DWORD cells =
        csbi.dwSize.X *
        csbi.dwSize.Y;

    DWORD written;

    COORD home = {0,0};

    FillConsoleOutputCharacter(
        hOut,
        ' ',
        cells,
        home,
        &written
    );

    FillConsoleOutputAttribute(
        hOut,
        csbi.wAttributes,
        cells,
        home,
        &written
    );

    SetConsoleCursorPosition(
        hOut,
        home
    );
}
void VeKhungDon(int t, int b, int l, int r)
{
    gotoXY(l,t); cout<<(char)201;
    gotoXY(r,t); cout<<(char)187;
    gotoXY(l,b); cout<<(char)200;
    gotoXY(r,b); cout<<(char)188;
    for(int i=l+1;i<r;i++){gotoXY(i,t);cout<<(char)205;gotoXY(i,b);cout<<(char)205;}
    for(int i=t+1;i<b;i++){gotoXY(l,i);cout<<(char)186;gotoXY(r,i);cout<<(char)186;}
}
