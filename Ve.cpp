#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
#include "Bien.h"
#include "maybay.h"
#include "chuyenbay1.h"
#include "hanh khach.h"
#include "Ve.h"
 
static int TimVeHanhKhach(CB &cb, unsigned int cmnd) {
    for (int i = 0; i < cb.tongsove; i++)
        if (cb.dsve[i].CMND == cmnd && cb.dsve[i].tt == true) return i;
    return -1;
}
 
static int TimViTriTheoSoGhe(CB &cb, int soGheMuon) {
    for (int i = 0; i < cb.tongsove; i++)
        if (cb.dsve[i].ghe_so == soGheMuon) return i;
    return -1;
}

void InSoDoGhe(CB &cb) {
    const int frameLeft  = 43;
    const int frameRight = 113;
    const int frameTop   = 4;
    const int frameBot   = 27;

    ClearArea(frameLeft, frameTop - 1, frameRight - frameLeft, 1);
    gotoXY(frameLeft, frameTop - 1);
    SetColor(14);
    cout << "SO DO GHE [" << cb.machuyenbay << "]";
    SetColor(8);
    cout << " [vang]=trong [do]=da dat";
    SetColor(7);

    if (cb.tongsove == 0) return;

    const int cellW = 5;
    int cols = (frameRight - frameLeft) / cellW;
    if (cols < 1) cols = 1;
    if (cols > 14) cols = 14;

    int rows       = (cb.tongsove + cols - 1) / cols;
    int totalH     = frameBot - frameTop - 1;
    int rowSpacing = (rows > 1) ? (totalH / rows) : 1;
    if (rowSpacing < 2) rowSpacing = 2;
    int colSpacing = (frameRight - frameLeft) / cols;
    if (colSpacing < cellW) colSpacing = cellW;

    for (int r = 0; r <= totalH; r++)
        ClearArea(frameLeft, frameTop + r, frameRight - frameLeft, 1);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < cb.tongsove; i++) {
        int row = i / cols;
        int col = i % cols;
        int x = frameLeft + col * colSpacing;
        int y = frameTop  + row * rowSpacing;
        gotoXY(x, y);
        if (cb.dsve[i].CMND != 0)
            SetConsoleTextAttribute(hOut,
                BACKGROUND_RED |
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else
            SetConsoleTextAttribute(hOut,
                BACKGROUND_RED | BACKGROUND_GREEN |
                FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " X ";
        SetColor(8);
        gotoXY(x, y + 1);
        cout << setw(3) << right << cb.dsve[i].ghe_so;
    }
    SetColor(7);
}

static void NhapNhanhHanhKhach(NODEPTR &root, unsigned int cmnd) {
    HK k;
    k.CMND = cmnd;
    int ord = 99; bool sv = false;
    string ho = "";
    gotoXY(4, 20); cout << "Nhap Ho hanh khach : ";
    ClearArea(24, 20, 15, 1);
    ShowCur(true);
    gotoXY(24, 20);
    ConstraintsForLetterAndSpace(ho, ord, sv, 0);
    if (!sv) { ShowCur(false); return; }
    strcpy(k.Ho, ho.c_str());

    string ten = ""; sv = false;
    gotoXY(4, 21); cout << "Nhap Ten hanh khach : ";
    ClearArea(24, 21, 15, 1);
    gotoXY(24, 21);
    ConstraintForOnlyLetter(ten, ord, sv, 0);
    if (!sv) { ShowCur(false); return; }
    strcpy(k.Ten, ten.c_str());

    gotoXY(4, 22); cout << "Gioi tinh (1-Nam / 0-Nu): ";
    int phai = -1;
    while (phai < 0 || phai > 1) {
        int c = _getch();
        if      (c == '0') { phai = 0; cout << "0"; }
        else if (c == '1') { phai = 1; cout << "1"; }
        else if (c == 27)  { ShowCur(false); return; }
    }
    k.Phai = (phai == 1);
    Insert_node(root, k);
    GhiFileHanhKhach(root);
    gotoXY(4, 23); SetColor(10); cout << "Da cap nhat hanh khach!"; SetColor(7);
    ShowCur(false);
}

bool ConHon3Tieng(Datetime dt) {
    time_t now = time(0);
    tm tg;
    tg.tm_year  = dt.year  - 1900;
    tg.tm_mon   = dt.month - 1;
    tg.tm_mday  = dt.day;
    tg.tm_hour  = dt.hour;
    tg.tm_min   = dt.minute;
    tg.tm_sec   = 0;
    tg.tm_isdst = -1;
    time_t gioBay = mktime(&tg);
    return difftime(gioBay, now) >= 3 * 60 * 60;
}

static PTR KiemTraHanhKhachCoVeChuaHoanThanh(PTR First, unsigned int cmnd, CB cbMoi) {
    tm tgMoi;
    tgMoi.tm_year  = cbMoi.thoigiandi.year  - 1900;
    tgMoi.tm_mon   = cbMoi.thoigiandi.month - 1;
    tgMoi.tm_mday  = cbMoi.thoigiandi.day;
    tgMoi.tm_hour  = cbMoi.thoigiandi.hour;
    tgMoi.tm_min   = cbMoi.thoigiandi.minute;
    tgMoi.tm_sec   = 0;
    tgMoi.tm_isdst = -1;
    time_t gioBayMoi = mktime(&tgMoi);

    for (PTR p = First; p != NULL; p = p->next) {
        if (stricmp(p->data.machuyenbay, cbMoi.machuyenbay) == 0) continue;
        if (p->data.trang_thai == 0) continue;
        if (TimVeHanhKhach(p->data, cmnd) != -1) {
            tm tgCu;
            tgCu.tm_year  = p->data.thoigiandi.year  - 1900;
            tgCu.tm_mon   = p->data.thoigiandi.month - 1;
            tgCu.tm_mday  = p->data.thoigiandi.day;
            tgCu.tm_hour  = p->data.thoigiandi.hour;
            tgCu.tm_min   = p->data.thoigiandi.minute;
            tgCu.tm_sec   = 0;
            tgCu.tm_isdst = -1;
            time_t gioBayCu = mktime(&tgCu);
            double giayChenhLech = abs(difftime(gioBayMoi, gioBayCu));
            if (giayChenhLech < 3 * 60 * 60)
                return p;
        }
    }
    return NULL;
}


static string ChuyenTrangThaiToStr(int tt) {
    switch(tt) {
        case 0: return "Huy chuyen";
        case 1: return "Con ve";
        case 2: return "Het ve";
        case 3: return "Hoan tat";
        default: return "?";
    }
}

static void VeKhungDonNoi(int top, int bot, int left, int right) {
    gotoXY(left, top);  cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bot);  cout << (char)200;
    gotoXY(right, bot); cout << (char)188;
    for (int i = left+1; i < right; i++) {
        gotoXY(i, top); cout << (char)205;
        gotoXY(i, bot); cout << (char)205;
    }
    for (int i = top+1; i < bot; i++) {
        gotoXY(left,  i); cout << (char)186;
        gotoXY(right, i); cout << (char)186;
    }
}

static void VeDSCBTrongForm(const vector<PTR> &dsCB, int startIdx, int highlight, int perPage) {
    for (int i = 0; i < perPage; i++)
        ClearArea(43, 4 + i, 76, 1);

    for (int i = 0; i + startIdx < (int)dsCB.size() && i < perPage; i++) {
        int idx = i + startIdx;
        CB  cb  = dsCB[idx]->data;
        int conTrong = cb.tongsove - cb.tongsodaban;

        gotoXY(44, 4 + i);
        if (idx == highlight) SetColor(112); else SetColor(7);

        cout << left << setw(5)  << (idx + 1)
                     << setw(10) << cb.machuyenbay
                     << setw(18) << cb.noiden;

        cout << right << setfill('0')
             << setw(2) << cb.thoigiandi.hour    << ":"
             << setw(2) << cb.thoigiandi.minute  << " "
             << setw(2) << cb.thoigiandi.day   << "/"
             << setw(2) << cb.thoigiandi.month << "/"
             << setfill(' ') << left << setw(6) << cb.thoigiandi.year;

        if      (idx == highlight) SetColor(112);
        else if (conTrong > 0)     SetColor(10);
        else                       SetColor(12);
        cout << setw(8) << conTrong;

        if (idx == highlight) SetColor(112); else SetColor(7);
        cout << setw(6)  << cb.tongsove;
        cout << setw(5) << ChuyenTrangThaiToStr(cb.trang_thai);
        SetColor(7);
    }

    ClearArea(44, 35, 50, 1);
    gotoXY(44, 35);
    int total = (int)dsCB.size();
    int trang = startIdx / perPage + 1;
    int tongTrang = (total == 0) ? 1 : ((total - 1) / perPage + 1);
    cout << "Trang " << trang << " / " << tongTrang
         << "  (" << total << " chuyen bay)";
}


static PTR ChonChuyenBay(PTR First, bool modeDat) {
    // --- Loc danh sach theo mode ---
    vector<PTR> dsCB;
    for (PTR p = First; p != NULL; p = p->next) {
        if (modeDat) {
            if (p->data.trang_thai == 0 ||
                p->data.trang_thai == 2 ||
                p->data.trang_thai == 3) continue;
            if (!ConHon3Tieng(p->data.thoigiandi)) continue;
        } else {
            if (p->data.trang_thai == 0 ||
                p->data.trang_thai == 3) continue;
            if (!ConHon3Tieng(p->data.thoigiandi)) continue;
        }
        dsCB.push_back(p);
    }

    // --- Ve giao dien (dung ClearConsole thay system cls) ---
    ClearConsole();
    ShowCur(false);

    // Khung trai
    VeKhungDonNoi(2, 38, 2, 40);
    gotoXY(4, 2); SetColor(14);
    cout << (modeDat ? "CHON CHUYEN BAY - DAT VE"
                     : "CHON CHUYEN BAY - HUY VE");
    SetColor(7);
    gotoXY(4, 34); SetColor(8);
    cout << "MUI TEN: Di chuyen  ENTER: Chon  ESC: Thoat";
    SetColor(7);

    // Khung phai – danh sach
    VeKhungDonNoi(2, 38, 42, 118);
    gotoXY(44, 3); SetColor(14);
    cout << left
         << setw(5)  << "STT"
         << setw(10) << "MA CB"
         << setw(18) << "NOI DEN"
         << setw(17) << "NGAY GIO"
         << setw(8)  << "TRONG"
         << setw(6)  << "TONG"
         << setw(4) << "TRANG THAI";
    SetColor(7);

    if (dsCB.empty()) {
        gotoXY(44, 5); SetColor(12);
        cout << (modeDat ? "Khong co chuyen bay hop le de dat ve!"
                         : "Khong co chuyen bay hop le de huy ve!");
        SetColor(7);
        gotoXY(44, 7); SetColor(8);
        cout << "(Chi hien chuyen bay con tren 3 tieng va chua hoan tat)";
        SetColor(7);
        gotoXY(44, 9); cout << "Nhan phim bat ky de quay lai...";
        _getch();
        return NULL;
    }

    int highlight = 0, startIdx = 0;
    const int perPage = 30;
    VeDSCBTrongForm(dsCB, startIdx, highlight, perPage);

    while (true) {
        int key = ReadKey();
        if (key == 1) {                          // MUI TEN LEN
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= perPage;
                VeDSCBTrongForm(dsCB, startIdx, highlight, perPage);
            }
        }
        else if (key == 2) {                     // MUI TEN XUONG
            if (highlight < (int)dsCB.size() - 1) {
                highlight++;
                if (highlight >= startIdx + perPage) startIdx += perPage;
                VeDSCBTrongForm(dsCB, startIdx, highlight, perPage);
            }
        }
        else if (key == 4) {                     // ESC -> thoat
            return NULL;
        }
        else if (key == 3) {                     // ENTER -> chot
            return dsCB[highlight];
        }
    }
}

void DatVe(PTR &First, NODEPTR &root) {
    // Buoc duy nhat: chon chuyen bay tu danh sach hop le de dat ve
    PTR pCB = ChonChuyenBay(First, true);
    if (pCB == NULL) return;   // ESC -> quay ve menu

    // --- Chuyen sang man hinh nhap lieu ---
    // Xoa tung vung thay vi ClearConsole/system cls de khong nhap nhay man hinh
    for (int r = 2; r <= 38; r++) ClearArea(2,  r, 39, 1);   // xoa khung trai cu
    for (int r = 2; r <= 38; r++) ClearArea(42, r, 77, 1);   // xoa khung phai cu
    ShowCur(true);
    VeKhungNhapLieuVe();
    VeKhungDSV();

    // Hien thi san ma chuyen bay da chon (truong "Ma chuyen bay" = ordinal 0 -> row 4)
    gotoXY(4 + 15, 4); SetColor(10); cout << pCB->data.machuyenbay; SetColor(7);

    // Ve so do ghe ngay
    InSoDoGhe(pCB->data);

    int  ordinal   = 1;      
    bool SaveOrNot = false;

    // --- Nhap CCCD ---
    unsigned int cmnd = 0;
    NODEPTR pHK = NULL;

    while (true) {
        ConstraintForOnlyNumber(cmnd, ordinal, SaveOrNot, 15, 4294967);
        if (SaveOrNot) {
            PTR cbTrung = KiemTraHanhKhachCoVeChuaHoanThanh(First, cmnd, pCB->data);
            if (cbTrung != NULL) {
                gotoXY(4, 19); cout << "LOI: Hanh khach dang co ve chua";
                gotoXY(4, 20); cout << "hoan thanh o chuyen " << cbTrung->data.machuyenbay << "!";
                SetColor(7); _getch(); ClearArea(4, 19, 32, 2);
                gotoXY(4 + 15, ordinal*2 + 4); cout << "       ";
                cmnd = 0; pHK = NULL; continue;
            }
            pHK = Timkiemhanhkhach(root, cmnd);
            if (pHK != NULL) {
                gotoXY(20, 8);  SetColor(11); cout << pHK->data.Ho;  SetColor(7);
                gotoXY(20, 10); SetColor(11); cout << pHK->data.Ten; SetColor(7);
                gotoXY(20, 12); SetColor(11); cout << (pHK->data.Phai ? "Nam" : "Nu"); SetColor(7);
            }
            if (pHK == NULL) {
                gotoXY(2, 19); SetColor(14); cout << "Hanh khach chua co! Can nhap thong tin.";
                SetColor(7); _getch(); ClearArea(2, 19, 44, 1);
                NhapNhanhHanhKhach(root, cmnd);
                pHK = Timkiemhanhkhach(root, cmnd);
                if (pHK == NULL) continue;
                ClearArea(20, 8,  15, 1);
                ClearArea(20, 10, 15, 1);
                ClearArea(20, 12,  6, 1);
                gotoXY(20, 8);  SetColor(11); cout << pHK->data.Ho;  SetColor(7);
                gotoXY(20, 10); SetColor(11); cout << pHK->data.Ten; SetColor(7);
                gotoXY(20, 12); SetColor(11); cout << (pHK->data.Phai ? "Nam" : "Nu"); SetColor(7);
            }
            if (TimVeHanhKhach(pCB->data, cmnd) != -1) {
                gotoXY(1, 22); SetColor(12); cout << "Hanh khach nay DA CO VE tren chuyen bay";
                SetColor(7); _getch();
                ClearArea(1, 22, 39, 1);
                ClearArea(20, 8,  15, 1);
                ClearArea(20, 10, 15, 1);
                ClearArea(20, 12, 10, 1);
                ClearArea(4 + 15, ordinal*2 + 4, 15, 1);
                cmnd = 0; pHK = NULL; continue;
            }
            ordinal = 5;   // nhay den truong "So ghe"
        }
        else return;
        break;
    }

  
    int viTriGhe = -1;
    while (true) {
        gotoXY(1, 19);
        unsigned int soGheNhap = 0;
        cout << "Nhap ghe muon chon (1-" << pCB->data.tongsove << ", ESC de huy): ";
        ConstraintForOnlyNumber(soGheNhap, ordinal, SaveOrNot, 15, 4294967295u);
        if (SaveOrNot) {
            int vt = TimViTriTheoSoGhe(pCB->data, (int)soGheNhap);
            if (vt == -1) {
                ClearArea(1, 19, 39, 1);
                gotoXY(1, 19); SetColor(12); cout << "Ghe khong ton tai! Nhap lai.";
                SetColor(7); _getch(); ClearArea(1, 19, 39, 1); soGheNhap = 0;
                gotoXY(4 + 15, ordinal*2 + 4); cout << "   ";
                continue;
            }
            if (pCB->data.dsve[vt].CMND != 0) {
                ClearArea(1, 19, 39, 1);
                gotoXY(1, 19); SetColor(12);
                cout << "Ghe " << soGheNhap << " da duoc dat! Chon ghe khac.";
                SetColor(7); _getch(); ClearArea(1, 19, 39, 1); soGheNhap = 0;
                gotoXY(4 + 15, ordinal*2 + 4); cout << "   ";
                continue;
            }
            viTriGhe = vt;
        }
        else {
            ClearArea(1, 19, 39, 1);
            gotoXY(1, 19); SetColor(12); cout << "Da huy dat ve."; SetColor(7);
            _getch(); ShowCur(false); return;
        }
        break;
    }

    // --- Xac nhan ---
    ClearArea(1, 19, 39, 1);
    gotoXY(1, 19); cout << "Nhan ENTER de xac nhan, ESC de huy: ";
    while (true) {
        int c = _getch();
        if (c == 13) {
            pCB->data.dsve[viTriGhe].CMND = cmnd;
            pCB->data.dsve[viTriGhe].tt   = true;
            pCB->data.tongsodaban++;
            pCB->data.trang_thai = (pCB->data.tongsodaban >= pCB->data.tongsove) ? 2 : 1;
            GhiFileChuyenBay(First);
            InSoDoGhe(pCB->data);
            ClearArea(1, 19, 39, 1);
            gotoXY(4, 19); SetColor(10);
            cout << "DAT VE THANH CONG! Ghe so " << pCB->data.dsve[viTriGhe].ghe_so;
            SetColor(7); break;
        }
        if (c == 27) {
            ClearArea(1, 19, 39, 1);
            gotoXY(1, 19); SetColor(12); cout << "Da huy dat ve."; SetColor(7); break;
        }
    }
    _getch();
    ShowCur(false);
}


void HuyVe(PTR &First, NODEPTR &root) {
    // Buoc duy nhat: chon chuyen bay tu danh sach hop le de huy ve
    PTR pCB = ChonChuyenBay(First, false);
    if (pCB == NULL) return;

    // --- Chuyen sang man hinh nhap lieu ---
    // Xoa tung vung thay vi ClearConsole/system cls de khong nhap nhay man hinh
    for (int r = 2; r <= 38; r++) ClearArea(2,  r, 39, 1);   // xoa khung trai cu
    for (int r = 2; r <= 38; r++) ClearArea(42, r, 77, 1);   // xoa khung phai cu
    ShowCur(true);
    VeKhungNhapLieuVe();
    VeKhungDSV();

    // Hien thi san ma chuyen bay
    gotoXY(4 + 15, 4); SetColor(10); cout << pCB->data.machuyenbay; SetColor(7);
    InSoDoGhe(pCB->data);

    int  ordinal   = 1;
    bool SaveOrNot = false;
    unsigned int cmnd = 0;
    NODEPTR pHK   = NULL;
    int viTriVe   = -1;

    // --- Nhap CCCD ---
    while (true) {
        ClearArea(19, 6, 15, 1);
        ConstraintForOnlyNumber(cmnd, ordinal, SaveOrNot, 15, 4294967295u);
        if (SaveOrNot) {
            pHK = Timkiemhanhkhach(root, cmnd);
            if (pHK == NULL) {
                gotoXY(1, 19); SetColor(12); cout << "Khong tim thay hanh khach!";
                SetColor(7); _getch(); ClearArea(1, 19, 30, 1);
                continue;
            }
            viTriVe = TimVeHanhKhach(pCB->data, cmnd);
            if (viTriVe == -1) {
                gotoXY(1, 19); SetColor(12); cout << "Hanh khach KHONG CO VE tren chuyen bay!";
                SetColor(7); _getch(); ClearArea(1, 19, 39, 1);
                cmnd = 0; pHK = NULL; continue;
            }
        }
        else return;
        break;
    }

    // Hien thi thong tin hanh khach
    gotoXY(20, 8);  cout << pHK->data.Ho;
    gotoXY(20, 10); cout << pHK->data.Ten;
    gotoXY(20, 12); SetColor(10); cout << pCB->data.dsve[viTriVe].ghe_so; SetColor(7);

    // --- Xac nhan huy ---
    gotoXY(1, 19); cout << "Ban co chac chan muon huy ve nay? (Y/N): ";
    while (true) {
        int c = _getch();
        if (c == 'Y' || c == 'y') {
            pCB->data.dsve[viTriVe].CMND = 0;
            pCB->data.dsve[viTriVe].tt   = false;
            pCB->data.tongsodaban--;
            if (pCB->data.trang_thai == 2) pCB->data.trang_thai = 1;
            GhiFileChuyenBay(First);
            InSoDoGhe(pCB->data);
            ClearArea(1, 19, 39, 1);
            gotoXY(1, 19); SetColor(10); cout << "HUY VE THANH CONG!"; SetColor(7); break;
        }
        if (c == 'N' || c == 'n' || c == 27) {
            ClearArea(1, 19, 39, 1);
            gotoXY(1, 19); SetColor(12); cout << "Da huy thao tac."; SetColor(7); break;
        }
    }
    _getch();
    ShowCur(false);
}




static void VeKhungDon_VT(int t, int b, int l, int r)
{
    gotoXY(l,t); cout<<(char)201;
    gotoXY(r,t); cout<<(char)187;
    gotoXY(l,b); cout<<(char)200;
    gotoXY(r,b); cout<<(char)188;
    for(int i=l+1;i<r;i++){gotoXY(i,t);cout<<(char)205;gotoXY(i,b);cout<<(char)205;}
    for(int i=t+1;i<b;i++){gotoXY(l,i);cout<<(char)186;gotoXY(r,i);cout<<(char)186;}
}

static string TrangThaiStr_VT(int tt)
{
    switch(tt){
        case 0: return "HuyCB";
        case 1: return "ConVe";
        case 2: return "HetVe";
        case 3: return "HoanTat";
        default: return "?";
    }
}


static void VeSoDoGhe(CB &cb)
{
    const int fL = R_LEFT + 1;
    const int fR = R_RIGHT - 1;
    const int fT = 3;
    const int fB = BOT - 1;

    const int usableW = fR - fL;
    const int usableH = fB - fT;

    for(int r = fT - 1; r <= fB; r++)
        ClearArea(fL, r, usableW, 1);

    SetColor(14);
    gotoXY(fL, fT-2);
    cout << "CHUYEN BAY: " << cb.machuyenbay;

    SetColor(10);
    gotoXY(fL+30, fT-2);
    cout << "[=] TRONG";

    SetColor(12);
    gotoXY(fL+45, fT-2);
    cout << "[=] DA DAT";

    SetColor(7);

    if(cb.tongsove <= 0)
        return;

    // Moi ghe ve gom 2 dong: dong tren in " X ", dong duoi in so ghe (3 ky tu)
    // Chieu rong moi o ghe = seatW ky tu (bao gom khoang cach ben phai)
    const int seatW = 4;
    const int seatH = 2;

    int maxCols = usableW / seatW;
    if(maxCols < 1) maxCols = 1;

    int cols = maxCols;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < cb.tongsove; i++)
    {
        int row = i / cols;
        int col = i % cols;

        int x = fL + col * seatW;
        int y = fT + row * seatH;

        // Neu vuot qua khung thi dung (truong hop may bay qua nhieu ghe)
        if(y + 1 >= fB) break;
        if(x + 3 >= fR) continue;

        gotoXY(x, y);

        if(cb.dsve[i].tt)
        {
            SetConsoleTextAttribute(
                hOut,
                BACKGROUND_RED |
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
            );
        }
        else
        {
            SetConsoleTextAttribute(
                hOut,
                BACKGROUND_RED | BACKGROUND_GREEN |
                FOREGROUND_RED | FOREGROUND_INTENSITY
            );
        }

        cout << " X ";

        SetColor(8);

        gotoXY(x, y+1);
        cout << setw(3) << right << cb.dsve[i].ghe_so;
    }

    SetColor(7);
}


static void InDSMayBay_VT(DSMB &LA, int highlight, int startIdx)
{
    static int oldStart = -1;

	if(oldStart != startIdx)
	{
	    for(int i=0;i<PER_PAGE;i++)
	        ClearArea(R_LEFT+1, 2+i, R_RIGHT-R_LEFT-1, 1);
	
	    oldStart = startIdx;
	}

    for (int i = 0; i+startIdx < LA.soluong && i < PER_PAGE; i++) {
        int idx = i + startIdx;
        gotoXY(R_LEFT+1, 2+i);
        if (idx == highlight) SetColor(112); else SetColor(7);
        cout << left
             << setw(4)  << (idx+1)
             << setw(12) << LA.DSMB[idx]->sohieumb
             << setw(17) << LA.DSMB[idx]->loaimb
             << setw(5)  << LA.DSMB[idx]->socho;
        SetColor(7);
    }

    ClearArea(R_LEFT+1, BOT-1, R_RIGHT-R_LEFT-1, 1);
    gotoXY(R_LEFT+1, BOT-1);
    int total = (LA.soluong > 0) ? LA.soluong : 1;
    cout << "Trang " << (startIdx/PER_PAGE + 1)
         << "/" << ((total-1)/PER_PAGE + 1);
}

static void InDSChuyenBay(vector<PTR> &dsCB, int highlight, int startIdx)
{
    static int oldStart = -1;

	if(oldStart != startIdx)
	{
	    for(int i=0;i<PER_PAGE;i++)
	        ClearArea(R_LEFT+1, 2+i, R_RIGHT-R_LEFT-1, 1);
	
	    oldStart = startIdx;
	}

    for (int i = 0; i+startIdx < (int)dsCB.size() && i < PER_PAGE; i++) {
        int  idx = i + startIdx;
        CB  &cb  = dsCB[idx]->data;
        int  ct  = cb.tongsove - cb.tongsodaban;

        gotoXY(R_LEFT+1, 2+i);
        if (idx == highlight) SetColor(112); else SetColor(7);

        cout << left
             << setw(4) << (idx+1)
             << setw(8) << cb.machuyenbay
             << setw(16)<< cb.noiden;

        cout << right << setfill('0')
             << setw(2) << cb.thoigiandi.day   << "/"
             << setw(2) << cb.thoigiandi.month << " "
             << setw(2) << cb.thoigiandi.hour  << ":"
             << setw(2) << cb.thoigiandi.minute << " ";
        cout << setfill(' ') << left;

        if (idx == highlight) SetColor(112);
        else if (ct > 0) SetColor(10); else SetColor(12);
        cout << setw(6) << ct;

        if (idx == highlight) SetColor(112); else SetColor(7);
        cout << setw(5) << cb.tongsove
             << setw(8) << TrangThaiStr_VT(cb.trang_thai);
        SetColor(7);
    }

    ClearArea(R_LEFT+1, BOT-1, R_RIGHT-R_LEFT-1, 1);
    gotoXY(R_LEFT+1, BOT-1);
    int total = ((int)dsCB.size() > 0) ? (int)dsCB.size() : 1;
    cout << "Trang " << (startIdx/PER_PAGE + 1)
         << "/" << ((total-1)/PER_PAGE + 1)
         << " (" << (int)dsCB.size() << " CB)";
}


static int BuocChonMayBay(DSMB &LA)
{
    ClearConsole();
    ShowCur(false);

    VeKhungDon_VT(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "BUOC 1: CHON MAY BAY"; SetColor(7);
    gotoXY(2, 3); cout << "So Hieu chon: ";
    ClearArea(1,BOT-2,L_RIGHT-2,2);

	SetColor(8);

	gotoXY(2,BOT-2);
	cout<<"UP/DOWN : Di chuyen";

	gotoXY(2,BOT-1);
	cout<<"ENTER : Chon    ESC : Thoat";

	SetColor(7);

    VeKhungDon_VT(TOP, BOT, R_LEFT, R_RIGHT);
    gotoXY(R_LEFT+1, 1); SetColor(14);
    cout << left
         << setw(4)  << "STT"
         << setw(12) << "SO HIEU"
         << setw(17) << "LOAI MAY BAY"
         << setw(5)  << "CHO";
    SetColor(7);

    int highlight = 0;
    int startIdx  = 0;
    string soHieu = "";

    InDSMayBay_VT(LA, highlight, startIdx);

    while (true) {
        ClearArea(16, 3, L_RIGHT-16, 1);
        gotoXY(16, 3); SetColor(10); cout << soHieu; SetColor(7);

        int key = ReadKey();

        if (key == 1) {
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= PER_PAGE;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            InDSMayBay_VT(LA, highlight, startIdx);
        }
        else if (key == 2) {
            if (highlight < LA.soluong - 1) {
                highlight++;
                if (highlight >= startIdx + PER_PAGE) startIdx += PER_PAGE;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            InDSMayBay_VT(LA, highlight, startIdx);
        }
        else if (key == 4) {
            return -1;
        }
        else if (key == 3) {
            if (soHieu.empty()) soHieu = string(LA.DSMB[highlight]->sohieumb);
            int vt = timvitrimaybay(LA, soHieu.c_str());
            if (vt == -1) {
                gotoXY(2, 5); SetColor(12); cout << "Khong tim thay!    ";
                SetColor(7); _getch(); ClearArea(2,5,22,1); soHieu = ""; continue;
            }
            highlight = vt;
            startIdx  = (vt / PER_PAGE) * PER_PAGE;
            InDSMayBay_VT(LA, highlight, startIdx);
            gotoXY(2, 5); cout << "Chon: "; SetColor(10);
            cout << LA.DSMB[vt]->sohieumb; SetColor(7);
            gotoXY(2, 6); SetColor(8); cout << "ENTER:OK  ESC:Nhap lai"; SetColor(7);
            while (true) {
                int k = _getch();
                if (k == 13) { ClearArea(2,5,30,2); return vt; }
                if (k == 27) { ClearArea(2,5,30,2); soHieu = ""; break; }
            }
        }
    }
}

static PTR BuocChonChuyenBay(PTR First, const char *soHieuMB)
{
    vector<PTR> dsCB;
    for (PTR p = First; p != NULL; p = p->next)
        if (stricmp(p->data.sohieumaybay, soHieuMB) == 0)
            dsCB.push_back(p);

    ClearConsole();
    ShowCur(false);

    VeKhungDon_VT(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "BUOC 2: CHON CHUYEN BAY"; SetColor(7);
    gotoXY(2, 3); cout << "May bay: "; SetColor(10); cout << soHieuMB; SetColor(7);
    ClearArea(1,BOT-2,L_RIGHT-2,2);

	SetColor(8);
	
	gotoXY(2,BOT-2);
	cout<<"UP/DOWN : Di chuyen";
	
	gotoXY(2,BOT-1);
	cout<<"ENTER : Chon    ESC : Quay lai";
	
	SetColor(7);

    VeKhungDon_VT(TOP, BOT, R_LEFT, R_RIGHT);
    gotoXY(R_LEFT+1, 1); SetColor(14);
    cout << left
         << setw(4)  << "STT"
         << setw(8)  << "MA CB"
         << setw(16) << "NOI DEN"
         << setw(14) << "NGAY GIO"
         << setw(6)  << "TRONG"
         << setw(5)  << "TONG"
         << setw(8)  << "TT";
    SetColor(7);

    if (dsCB.empty()) {
        gotoXY(R_LEFT+1, 3); SetColor(12);
        cout << "Chua co chuyen bay nao!"; SetColor(7);
        gotoXY(R_LEFT+1, 5); cout << "Nhan phim bat ky...";
        _getch();
        return NULL;
    }

    int highlight = 0;
    int startIdx  = 0;

    InDSChuyenBay(dsCB, highlight, startIdx);

    while (true) {
        int key = ReadKey();
        if (key == 1) {
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= PER_PAGE;
                InDSChuyenBay(dsCB, highlight, startIdx);
            }
        }
        else if (key == 2) {
            if (highlight < (int)dsCB.size() - 1) {
                highlight++;
                if (highlight >= startIdx + PER_PAGE) startIdx += PER_PAGE;
                InDSChuyenBay(dsCB, highlight, startIdx);
            }
        }
        else if (key == 4) return NULL;
        else if (key == 3) return dsCB[highlight];
    }
}

static void BuocXemVeTrong(CB &cb)
{
    ClearConsole();
    ShowCur(false);

    VeKhungDon_VT(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "VE CON TRONG"; SetColor(7);

    gotoXY(2,  3); cout << "Ma CB   : "; SetColor(10); cout << cb.machuyenbay; SetColor(7);
    gotoXY(2,  4); cout << "May bay : "; cout << cb.sohieumaybay;
    gotoXY(2,  5); cout << "Noi den : "; cout << cb.noiden;
    gotoXY(2,  6); cout << "Ngay gio: ";
    cout << right << setfill('0')
         << setw(2) << cb.thoigiandi.day   << "/"
         << setw(2) << cb.thoigiandi.month << "/"
         << cb.thoigiandi.year             << " "
         << setw(2) << cb.thoigiandi.hour  << ":"
         << setw(2) << cb.thoigiandi.minute;
    cout << setfill(' ') << left;

    int conTrong = cb.tongsove - cb.tongsodaban;
    gotoXY(2,  8); cout << "Tong so  : "; SetColor(7);  cout << cb.tongsove;
    gotoXY(2,  9); cout << "Da dat   : "; SetColor(12); cout << cb.tongsodaban; SetColor(7);
    gotoXY(2, 10); cout << "Con trong: "; SetColor(10); cout << conTrong;       SetColor(7);

    ClearArea(1,BOT-2,L_RIGHT-2,2);

	SetColor(8);
	
	gotoXY(2,BOT-1);
	cout<<"Nhan phim bat ky de quay lai";
	
	SetColor(7);

    VeKhungDon_VT(TOP, BOT, R_LEFT, R_RIGHT);
    VeSoDoGhe(cb);

    _getch();
}

void InVeTrong(DSMB &LA, PTR First)
{
    if (LA.soluong == 0) {
        ClearConsole();
        gotoXY(5, 5); SetColor(12);
        cout << "Chua co du lieu may bay! Vui long nhap lieu truoc.";
        SetColor(7); _getch(); return;
    }

    while (true) {
        int vtMB = BuocChonMayBay(LA);
        if (vtMB == -1) break;

        while (true) {
            PTR pCB = BuocChonChuyenBay(First, LA.DSMB[vtMB]->sohieumb);
            if (pCB == NULL) break;
            BuocXemVeTrong(pCB->data);
        }
    }

    ClearConsole();
}
void MenuVe() {
    DSMB LA;
    PTR First    = NULL;
    NODEPTR root = NULL;
    DocFileMayBay(LA);
    DocFileChuyenBay(First, LA);
    DocFileHanhKhach(root);

    int chon = 0, menuCap = 1;
    bool daClear = false;
    VeKhung();
    VeKhungHuongDan();

    while (true) {
        if (menuCap == 1) {
            if (!daClear) { ClearArea(30+8, 7+3, 32, 10); daClear = true; }
            VeMenuVe(chon);
            int key = ReadKey();
            if (key == 1) chon--;
            else if (key == 2) chon++;
            if (chon < 0) chon = 2;
            if (chon > 2) chon = 0;
            if (key == 4) break;
            if (key == 3) {
                if      (chon == 0) { menuCap = 2; daClear = false; }
                else if (chon == 1) { menuCap = 3; daClear = false; }
                else if (chon == 2) { menuCap = 4; daClear = false; }
            }
        }
        else if (menuCap == 2) {
            DatVe(First, root);
            system("cls"); ShowCur(false);
            VeKhung(); VeKhungHuongDan();
            menuCap = 1; daClear = false; chon = 0;
        }
        else if (menuCap == 3) {
            HuyVe(First, root);
            system("cls"); ShowCur(false);
            VeKhung(); VeKhungHuongDan();
            menuCap = 1; daClear = false; chon = 1;
        }
        else if (menuCap == 4) {
            InVeTrong(LA, First);  // Bo comment neu da merge vao cung file
            system("cls"); ShowCur(false);
            VeKhung(); VeKhungHuongDan();
            menuCap = 1; daClear = false; chon = 2;
        }
    }
}
#ifdef TEST_VETRONG
int main()
{
	InitConsole(120,40);
	DisableQuickEdit();
    InVeTrong();
    return 0;
}
#endif
