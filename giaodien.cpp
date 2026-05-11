#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string>

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

void ClearArea(int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) cout << " ";
    }
}
int GetConsoleWidth() {// lay chieu rong console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int ReadKey() {
    int c = _getch();
    if (c == 224 || c == 0) { // phím dac biet
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
// ================= GIAO DIEN =================
void VeKhung(){
    int width = GetConsoleWidth();

    int boxWidth = 50; // ?? d? r?ng khung
    int left = (width - boxWidth) / 2;
    int right = left + boxWidth;

    int top = 7, bottom = 20;

    // ===== 4 góc =====
    gotoXY(left, top);     cout << (char)201;
    gotoXY(right, top);    cout << (char)187;
    gotoXY(left, bottom);  cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;

    // ===== c?nh trên du?i =====
    for (int i = left + 1; i < right; i++) {
        gotoXY(i, top);    cout << (char)205;
        gotoXY(i, bottom); cout << (char)205;
    }

    // ===== c?nh trái ph?i =====
    for (int i = top + 1; i < bottom; i++) {
        gotoXY(left, i);   cout << (char)186;
        gotoXY(right, i);  cout << (char)186;
    }

    // ===== TIÊU Ð? =====
    string title = " QUAN LI ";
    int x = (left + right - title.length()) / 2;
    gotoXY(x, top);
    cout << title;
}
void VeKhungHuongDan(){
    int width = GetConsoleWidth();

    int boxWidth = 50;
    int left = (width - boxWidth) / 2;
    int right = left + boxWidth;

    int top = 22, bottom = 25; // ?? n?m du?i menu chính

    // ===== 4 góc =====
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
        "Ve"
    };
    int left = 30, top = 7;
    for (int i = 0; i < 4; i++) {
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
	string menu[] = {"Them", "Sua", "Xoa"};
	for (int i = 0; i < 3; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // Màu xanh duong sáng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeMenuChuyenBay(int chon){
	string menu[] = {"Them", "Hieu Chinh", "Huy"};
	for (int i = 0; i < 3; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // Màu xanh duong sáng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeMenuVe(int chon){
	string menu[] = {"Dat ve", "Huy ve"};
	for (int i = 0; i < 2; i++) {
        gotoXY(30 + 8, 7 + 3 + i * 2);
        if (i == chon) {
            SetColor(11); // Màu xanh duong sáng
            cout << ">> " << menu[i];
            SetColor(7);
        } else {
            cout << "   " << menu[i];
        }
    }
}
void VeKhungNhapLieu(){
	int top = 2, bottom = 12, left = 2, right = 35;
    // V? khung tuong t? nhu các hàm tru?c c?a b?n
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
    cout << setw(5) << "SO HIEU" 
         << setw(25) << "LOAI MAY BAY" 
         << setw(22) << "SO CHO";
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
    
    // Cac nhan nhap lieu
    gotoXY(left + 2, top + 2); cout << "Ma chuyen bay      : ";
    gotoXY(left + 2, top + 4); cout << "So Hieu MB         : ";
    gotoXY(left + 2, top + 6); cout << "San bay den        : ";
    gotoXY(left + 2, top + 8); cout << "Ngay gio khoi hanh : ";
    gotoXY(left + 2, top + 12);cout << "Trang thai         : ";

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
    
    // Tieu de cot
    gotoXY(left + 5, top + 1);
    SetColor(14);
    cout << setw(4) << "MA CB" 
         << setw(12) << "NOI DEN" 
         << setw(17) << "SO HIEU"
         << setw(17) << "NGAY GIO"
         << setw(19) << "TRANG THAI";
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
    
    // Cac nhan nhap lieu
    gotoXY(left + 2, top + 1); cout << "           Chu Thich          ";
	gotoXY(left + 2, top + 3); cout << "    0:Huy chuyen    1:Con ve";
    gotoXY(left + 2, top + 5); cout << "    2:Het ve        3:Hoan tat";
}
void VeKhungNhapLieuVe(){
	int top = 2, bottom = 18, left = 2, right = 35;
    // V? khung tuong t? nhu các hàm tru?c c?a b?n
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
    gotoXY(left + 2, top + 10);cout << "So ghe       : ";
}
void VeKhungDSV(){
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
    cout << setw(4) << "MA CHUYEN BAY" 
         << setw(40) << "TONG SO GHE"; 
    SetColor(7);
}
