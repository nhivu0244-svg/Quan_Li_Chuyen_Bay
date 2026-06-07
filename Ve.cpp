#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
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
    const int frameLeft   = 43;
    const int frameRight  = 113;
    const int frameTop    = 4;
    const int frameBot    = 27;

    ClearArea(frameLeft, frameTop - 1, frameRight - frameLeft, 1);
    gotoXY(frameLeft, frameTop - 1);
    SetColor(14);
    cout << "SO DO GHE [" << cb.machuyenbay << "]";
    SetColor(8);
    cout << "   [vang]=trong  [do]=da dat";
    SetColor(7);

    if (cb.tongsove == 0) return;

    const int cellW    = 5;
    int cols           = (frameRight - frameLeft) / cellW;
    if (cols < 1)  cols = 1;
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
        int x   = frameLeft + col * colSpacing;
        int y   = frameTop  + row * rowSpacing;

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
    
    gotoXY(4, 20); cout << "Nhap Ho hanh khach  : ";
    ClearArea(24, 20, 15, 1);
    ShowCur(true);
    gotoXY(24, 20);
    ConstraintsForLetterAndSpace(ho, ord, sv, 0);
    if (!sv) { ShowCur(false); return; }
    strcpy(k.Ho, ho.c_str());

    string ten = "";
    sv = false;
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
        if (c == '0') { phai = 0; cout << "0"; }
        else if (c == '1') { phai = 1; cout << "1"; }
        else if (c == 27) { ShowCur(false); return; }
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
    tg.tm_year = dt.year  - 1900;
    tg.tm_mon  = dt.month - 1;
    tg.tm_mday = dt.day;
    tg.tm_hour = dt.hour;
    tg.tm_min  = dt.minute;
    tg.tm_sec  = 0;
    tg.tm_isdst = -1;
    time_t gioBay = mktime(&tg);
    return difftime(gioBay, now) >= 3 * 60 * 60;
}
static PTR KiemTraHanhKhachCoVeChuaHoanThanh(PTR First, unsigned int cmnd, CB cbMoi) {
    // 1. Ð?i th?i gian c?a chuy?n bay M?I dang ch?n ra time_t
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
        // N?u là chính chuy?n bay dang ch?n thì b? qua
        if (stricmp(p->data.machuyenbay, cbMoi.machuyenbay) == 0) continue; 
        
        // Chuy?n bay dã HUY (0) thì không c?n tính
        if (p->data.trang_thai == 0) continue; 
        
        // 2. Ki?m tra n?u hành khách dã có vé trên chuy?n bay cu p này
        if (TimVeHanhKhach(p->data, cmnd) != -1) {
            
            // Ð?i th?i gian c?a chuy?n bay CU trong danh sách ra time_t
            tm tgCu;
            tgCu.tm_year  = p->data.thoigiandi.year  - 1900;
            tgCu.tm_mon   = p->data.thoigiandi.month - 1;
            tgCu.tm_mday  = p->data.thoigiandi.day;
            tgCu.tm_hour  = p->data.thoigiandi.hour;
            tgCu.tm_min   = p->data.thoigiandi.minute;
            tgCu.tm_sec   = 0; 
            tgCu.tm_isdst = -1;
            time_t gioBayCu = mktime(&tgCu);

            // 3. Tính kho?ng cách tr? tuy?t d?i (abs) gi?a 2 chuy?n bay (tính b?ng giây)
            double giayChenhLech = abs(difftime(gioBayMoi, gioBayCu));

            // N?u 2 chuy?n bay cách nhau DU?I 3 TI?NG (3 * 60 * 60 = 10800 giây)
            // Nghia là b? trùng gi? ho?c sát gi? nhau quá, không th? di k?p -> CH?N
            if (giayChenhLech < 3 * 60 * 60) {
                return p; // Tr? v? chuy?n bay b? xung d?t l?ch d? báo l?i
            }
        }
    }
    return NULL; // Khác ngày ho?c cùng ngày nhung cách nhau trên 3 ti?ng -> CHO PHÉP Ð?T
}
void DatVe(PTR &First, NODEPTR &root) {
    system("cls");
    ShowCur(true);
    VeKhungNhapLieuVe();
    VeKhungDSV();
    int ordinal = 0;
    bool SaveOrNot = false;
    string maCB;
    PTR pCB = NULL;
    while (true) {
        ConstraintForLETTERAndNumber(maCB,ordinal,SaveOrNot,15);
        if(SaveOrNot){
            pCB = timmachuyenbay(First, maCB.c_str());
            if (pCB == NULL) {
                gotoXY(4, 19); SetColor(12); cout << "Ma chuyen bay khong ton tai!";
                SetColor(7); _getch();
				ClearArea(4, 19, 32, 1);
				gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' '); 
				maCB = ""; continue;
            }
            if (pCB->data.trang_thai == 0) {
                gotoXY(4, 19); SetColor(12); cout << "Chuyen bay da HUY! Nhap lai.";
                SetColor(7); _getch(); 
				ClearArea(4, 19, 35, 1); 
				gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' ');
				pCB = NULL; maCB = ""; continue;
            }
            if (pCB->data.trang_thai == 2) {
                gotoXY(4, 19); SetColor(12); cout << "Chuyen bay HET VE! Nhap lai.";
                SetColor(7); _getch(); 
				ClearArea(4, 19, 35, 1); 
				gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' ');
				pCB = NULL; maCB = ""; continue;
            }
            if (pCB->data.trang_thai == 3) {
                gotoXY(4, 19); SetColor(12); cout << "Chuyen bay da HOAN TAT! Nhap lai.";
                SetColor(7); 
				_getch(); 
				ClearArea(4, 19, 35, 1); 
				gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' ');
				pCB = NULL; maCB = ""; continue;
            }
            if (!ConHon3Tieng(pCB->data.thoigiandi)) {
                time_t now = time(0);
                tm tg;
                tg.tm_year  = pCB->data.thoigiandi.year   - 1900;
                tg.tm_mon   = pCB->data.thoigiandi.month  - 1;
                tg.tm_mday  = pCB->data.thoigiandi.day;
                tg.tm_hour  = pCB->data.thoigiandi.hour;
                tg.tm_min   = pCB->data.thoigiandi.minute;
                tg.tm_sec   = 0;
                tg.tm_isdst = -1;
                time_t gioBay = mktime(&tg);

                // Vì chua sang tr?ng thái 3 (chua quá 3 ti?ng), n?u now >= gioBay nghia là ÐANG BAY
                if (now >= gioBay) {
                    gotoXY(4, 19); SetColor(12); cout << "Chuyen bay DANG BAY!"; 
					gotoXY(4, 20); SetColor(12); cout << "Khong the dat ve.";
                } else {
                    gotoXY(4, 19); SetColor(12); cout << "Chuyen bay con duoi 3 tieng!";
					gotoXY(4, 20); SetColor(12); cout << "Khong the dat ve.";
                }
                
                SetColor(7); _getch(); 
                ClearArea(4, 19, 32, 2); 
                gotoXY(4 + 15, ordinal * 2 + 4); cout << string(maCB.length(), ' ');
                pCB = NULL; maCB = ""; continue;
            }
            ordinal ++;
        }
        else return;
        break;
	}
    InSoDoGhe(pCB->data);

    unsigned int cmnd = 0;
    NODEPTR pHK = NULL;
    while (true) {
        //ClearArea(20, 6, 15, 1);
        // Xoa thong tin cu truoc khi nhap moi
        //ClearArea(20,  8, 30, 1);
        //ClearArea(20, 10, 30, 1);
        //ClearArea(20, 12, 10, 1);
        ConstraintForOnlyNumber(cmnd,ordinal,SaveOrNot,15,4294967);
        if (SaveOrNot){
        	PTR cbTrung = KiemTraHanhKhachCoVeChuaHoanThanh(First, cmnd, pCB->data);
            if (cbTrung != NULL) {
                gotoXY(4, 19); cout << "LOI: Hanh khach dang co ve chua";
			    gotoXY(4, 20); cout << "hoan thanh o chuyen " << cbTrung->data.machuyenbay << "!";
                SetColor(7); _getch(); ClearArea(4, 19, 32, 2); 
                gotoXY(4 + 15, ordinal*2 + 4); cout << "           ";
                cmnd = 0; pHK = NULL; continue;
            }
			pHK = Timkiemhanhkhach(root, cmnd);
            if (pHK != NULL) {
            // In thong tin hanh khach thang hang vao khung nhap lieu
            //ClearArea(20,  8, 30, 1);
           // ClearArea(20, 10, 30, 1);
            //ClearArea(20, 12, 10, 1);
                gotoXY(20,  8); SetColor(11); cout << pHK->data.Ho;   SetColor(7);
                gotoXY(20, 10); SetColor(11); cout << pHK->data.Ten;  SetColor(7);
                gotoXY(20, 12); SetColor(11); cout << (pHK->data.Phai ? "Nam" : "Nu"); SetColor(7);
            }
            if (pHK == NULL) {
                gotoXY(2, 19); SetColor(14); cout << "Hanh khach chua co! Can nhap thong tin.";
                SetColor(7); _getch(); ClearArea(2, 19, 44, 1);
                NhapNhanhHanhKhach(root, cmnd);
                pHK = Timkiemhanhkhach(root, cmnd);
                if (pHK == NULL) continue;
                // Hien thi thong tin vua nhap len khung
                ClearArea(20,  8, 15, 1);
                ClearArea(20, 10, 15, 1);
                ClearArea(20, 12, 6, 1);
                gotoXY(20,  8); SetColor(11); cout << pHK->data.Ho;   SetColor(7);
                gotoXY(20, 10); SetColor(11); cout << pHK->data.Ten;  SetColor(7);
                gotoXY(20, 12); SetColor(11); cout << (pHK->data.Phai ? "Nam" : "Nu"); SetColor(7);
            }
            if (TimVeHanhKhach(pCB->data, cmnd) != -1) {
                gotoXY(1, 22); SetColor(12); cout << "Hanh khach nay DA CO VE tren chuyen bay";
                SetColor(7); _getch(); 
			    ClearArea(1, 22, 39, 1); 
			    ClearArea(20,  8, 15, 1);
                ClearArea(20, 10, 15, 1);
                ClearArea(20, 12, 10, 1);
                ClearArea(4 + 15, ordinal*2 + 4, 15, 1);
			    cmnd = 0; pHK = NULL; 
			    continue;
            }
            ordinal = 5;
        }
        else return;
        break;     
		}
    // Thong tin da duoc in trong vong lap, khong can in lai o day
    int viTriGhe = -1;
    while (true) {
        //ClearArea(20, 14, 10, 1);
        gotoXY(1, 19);
        unsigned int soGheNhap = 0;
		cout << "Nhap ghe muon chon (1-" << pCB->data.tongsove << ", ESC de huy): ";
        ConstraintForOnlyNumber(soGheNhap,ordinal,SaveOrNot,15,4294967295u);
        if(SaveOrNot){
            int vt = TimViTriTheoSoGhe(pCB->data, (int)soGheNhap);
            if (vt == -1) {
                ClearArea(1, 19, 39, 1);
                gotoXY(1, 19); SetColor(12); cout << "Ghe khong ton tai! Nhap lai.";
                SetColor(7); _getch(); 
				ClearArea(1, 19, 39, 1); soGheNhap = 0; 
				gotoXY(4 + 15, ordinal*2 + 4); cout << "   ";
				continue;
            }
            if (pCB->data.dsve[vt].CMND != 0) {
                ClearArea(1, 19, 39, 1);
                gotoXY(1, 19); SetColor(12); cout << "Ghe " << soGheNhap << " da duoc dat! Chon ghe khac.";
                SetColor(7); _getch();
				ClearArea(1, 19, 39, 1); soGheNhap = 0; 
				gotoXY(4 + 15, ordinal*2 + 4); cout << "   ";
				continue;
            }
            viTriGhe = vt;
		}
		else{
			ClearArea(1, 19, 39, 1);
            gotoXY(1, 19); SetColor(12); cout << "Da huy dat ve."; SetColor(7);
            _getch(); ShowCur(false); return;
		}
		break;
	}

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
    system("cls");
    ShowCur(true);
    VeKhungNhapLieuVe();
    VeKhungDSV();
    int ordinal = 0;
    bool SaveOrNot = false;
    string maCB;
    unsigned int cmnd;
    NODEPTR pHK = NULL;
    PTR pCB = NULL;
    while (true) {
    	ConstraintForLETTERAndNumber(maCB,ordinal,SaveOrNot,15);
    	if(SaveOrNot){
            pCB = timmachuyenbay(First, maCB.c_str());
             if (pCB == NULL) {
                gotoXY(4, 19); SetColor(12); cout << "Ma chuyen bay khong ton tai!";
                SetColor(7); _getch();
				ClearArea(4, 19, 32, 1);
				gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' '); 
				maCB = ""; continue;
            }
            if (pCB->data.trang_thai == 0 || pCB->data.trang_thai == 3) {
                gotoXY(1, 19); SetColor(12);
                cout << (pCB->data.trang_thai == 0 ? "Chuyen bay da HUY!" : "Chuyen bay da HOAN TAT!");
                SetColor(7); _getch(); ClearArea(1,19,35,1); 
                gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' ');
                maCB = ""; 
				continue;
            }
            if (!ConHon3Tieng(pCB->data.thoigiandi)) {
                gotoXY(4, 17); SetColor(12); cout << "Chuyen bay con duoi 3 tieng! Khong the huy ve.";
                SetColor(7); _getch(); ClearArea(4, 17, 50, 1); pCB = NULL; maCB = ""; 
				gotoXY(4 + 15, ordinal*2 + 4); cout << string(maCB.length(),' ');
				continue;
            }
            ordinal++;
		}
		else return;
		break;
	}
    InSoDoGhe(pCB->data);
    int viTriVe = -1;
    while (true) {
        ClearArea(19, 6, 15, 1);
        ConstraintForOnlyNumber(cmnd,ordinal,SaveOrNot,15,4294967295u);
        if(SaveOrNot){
        	pHK = Timkiemhanhkhach(root, cmnd);
            if (pHK == NULL) {
                gotoXY(1, 19); SetColor(12); cout << "Khong tim thay hanh khach!";
                SetColor(7); _getch(); ClearArea(1,19,30,1); 	
				continue;
            }
            viTriVe = TimVeHanhKhach(pCB->data, cmnd);
                if (viTriVe == -1) {
                gotoXY(1, 19); SetColor(12); cout << "Hanh khach KHONG CO VE tren chuyen bay!";
                SetColor(7); _getch(); ClearArea(1,19,39,1); cmnd = 0; pHK = NULL; continue;
            }
		}
		else return;
        break;
    }
    gotoXY(20,  8); cout << pHK->data.Ho;
    gotoXY(20, 10); cout << pHK->data.Ten;
    gotoXY(20, 12); SetColor(10); cout << pCB->data.dsve[viTriVe].ghe_so; SetColor(7);

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
            gotoXY(1, 19); SetColor(10);
            cout << "HUY VE THANH CONG!";
            SetColor(7); break;
        }
        if (c == 'N' || c == 'n' || c == 27) {
            ClearArea(1, 19, 39, 1);
            gotoXY(1, 19); SetColor(12); cout << "Da huy thao tac."; SetColor(7); break;
        }
    }
    _getch();
    ShowCur(false);
}



/*static void VeKhungDon(int t, int b, int l, int r)
{
    gotoXY(l,t); cout<<(char)201;
    gotoXY(r,t); cout<<(char)187;
    gotoXY(l,b); cout<<(char)200;
    gotoXY(r,b); cout<<(char)188;
    for(int i=l+1;i<r;i++){gotoXY(i,t);cout<<(char)205;gotoXY(i,b);cout<<(char)205;}
    for(int i=t+1;i<b;i++){gotoXY(l,i);cout<<(char)186;gotoXY(r,i);cout<<(char)186;}
}


static bool NhapChuoiTX(string &result, int x, int y, int maxLen)
{
    result = "";
    int count = 0;
    gotoXY(x, y);
    ShowCur(true);
    while (true) {
        int c = _getch();
        if (c==224||c==0){ _getch(); continue; }
        if (c==27)  { ShowCur(false); return false; }
        if (c==13)  { if(count>0){ ShowCur(false); return true; } continue; }
        if (c==8 && count>0){
            cout<<"\b \b";
            result.erase(result.length()-1,1);
            count--; continue;
        }
        if (count>=maxLen) continue;
        if ((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9')){
            char ch = toupper((char)c);
            cout<<ch; result+=ch; count++;
        }
    }
}


static void VeSoDoGhe(CB &cb, int frameLeft, int frameTop,
                               int frameRight, int frameBot)
{
    // Tieu de
    ClearArea(frameLeft, frameTop-1, frameRight-frameLeft, 1);
    gotoXY(frameLeft, frameTop-1);
    SetColor(14);
    cout << "SO DO GHE  [" << cb.machuyenbay << "]";
    SetColor(8);
    cout << "   [vang]=con trong   [do]=da dat";
    SetColor(7);

    if (cb.tongsove == 0) return;

	const int seatW = 5;
	const int seatH = 3;

	int usableWidth  = frameRight - frameLeft - 4;
	int usableHeight = frameBot - frameTop - 2;

	int cols = usableWidth / seatW;

	if (cols > 12) cols = 12;
	if (cols < 1)  cols = 1;

	int rows = (cb.tongsove + cols - 1) / cols;

	int startX = frameLeft + 2;
	int startY = frameTop;
	int totalH = frameBot - frameTop - 1;
    // Xoa vung
    for (int r = 0; r <= totalH; r++)
        ClearArea(frameLeft, frameTop+r, frameRight-frameLeft, 1);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < cb.tongsove; i++) {
        int row = i / cols;
		int col = i % cols;

		int x = startX + col * seatW;
		int y = startY + row * seatH;
		
		if (x + seatW >= frameRight)
    		continue;

		if (y + 1 >= frameBot)
    		continue;

        gotoXY(x, y);
        if (cb.dsve[i].tt)
            // Do: ghe da dat
            SetConsoleTextAttribute(hOut,
                BACKGROUND_RED |
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else
            // Vang: ghe con trong
            SetConsoleTextAttribute(hOut,
                BACKGROUND_RED | BACKGROUND_GREEN |
                FOREGROUND_RED | FOREGROUND_INTENSITY);

        cout << " X ";

        SetColor(8);
        gotoXY(x, y + 1);

		cout << setw(3) << cb.dsve[i].ghe_so;
    }
    SetColor(7);
}

static void InDanhSachVeTrong(CB &cb, int startRow)
{
    // Thu thap danh sach ghe trong
    vector<int> vecTrong; // luu so ghe
    for (int i = 0; i < cb.tongsove; i++)
        if (!cb.dsve[i].tt) vecTrong.push_back(cb.dsve[i].ghe_so);

    // Xoa vung hien thi cu
    for (int i = startRow; i < startRow + 20; i++)
        ClearArea(3, i, 36, 1);

    gotoXY(3, startRow);
    SetColor(14);
    cout << "DANH SACH VE CON TRONG (" << vecTrong.size() << " ve):";
    SetColor(7);

    if (vecTrong.empty()) {
        gotoXY(3, startRow+1); SetColor(12); cout << "  Khong con ve trong!"; SetColor(7);
        return;
    }

    // In danh sach thanh nhieu cot (6 ghe / dong) de tiet kiem chieu cao
    int col = 0;
    int y   = startRow + 1;
    for (int i = 0; i < (int)vecTrong.size(); i++) {
        if (col == 0) gotoXY(3, y);
        SetColor(10);
        cout << setw(4) << right << vecTrong[i];
        SetColor(7);
        col++;
        if (col == 8) { col = 0; y++; }
    }
}

// THAY TH? TOÀN B? HÀM BUOCCHONMAYBAY CU B?NG BLOCK CODE NÀY:

// Bu?c 1: Khai báo m?t hàm thông thu?ng d? thay th? cho Lambda InDSMB b? l?i
static void VeDanhSachMayBayTrongForm(DSMB &LA, int startIdx, int highlight, int perPage)
{
    // Xóa vùng hi?n th? cu tru?c khi in trang m?i
    for (int i = 0; i < perPage; i++) 
        ClearArea(43, 4 + i, 74, 1);
        
    // In danh sách máy bay theo trang hi?n t?i
    for (int i = 0; i + startIdx < LA.soluong && i < perPage; i++) {
        int idx = i + startIdx;
        gotoXY(44, 4 + i);
        
        // N?u dòng dang du?c ch?n (highlight) thì d?i màu n?n sang màu xám tr?ng (112)
        if (idx == highlight) SetColor(112); else SetColor(7);
        
        cout << left
             << setw(5)  << (idx + 1)
             << setw(16) << LA.DSMB[idx]->sohieumb
             << setw(42) << LA.DSMB[idx]->loaimb
             << setw(8)  << LA.DSMB[idx]->socho;
        SetColor(7); // Tr? l?i màu ch? m?c d?nh
    }
    
    // Hi?n th? ch? s? phân trang ? góc du?i khung
    gotoXY(44, 35);
    cout << "Trang " << (startIdx / perPage + 1)
         << " / "    << ((LA.soluong - 1) / perPage + 1);
}

// Bu?c 2: Hàm x? lý ch?n máy bay chính th?c
static int BuocChonMayBay(DSMB &LA)
{
    system("cls");
    ShowCur(false);

    // Giao di?n Khung bên trái: Nh?p li?u
    VeKhungDon(2, 38, 2, 40);
    gotoXY(4,  2); SetColor(14); cout << "BUOC 1: CHON MAY BAY"; SetColor(7);
    gotoXY(4,  5); cout << "Nhap So Hieu MB: ";
    gotoXY(4, 34); SetColor(8);
    cout << "MUI TEN: Cuon DS   ESC: Thoat";
    SetColor(7);

    // Giao di?n Khung bên ph?i: Danh sách máy bay
    VeKhungDon(2, 38, 42, 118);
    gotoXY(44, 3); SetColor(14);
    cout << left
         << setw(5)  << "STT"
         << setw(16) << "SO HIEU"
         << setw(42) << "LOAI MAY BAY"
         << setw(8)  << "SO CHO";
    SetColor(7);

    int highlight = 0;
    int startIdx  = 0;
    const int perPage = 30;

    // THAY Ð?I T?I ÐÂY: G?i hàm thông thu?ng thay vì dùng cú pháp Lambda cu
    VeDanhSachMayBayTrongForm(LA, startIdx, highlight, perPage);

    gotoXY(4, 36); SetColor(8);
    cout << "Hoac dung MUI TEN len/xuong de chon,";
    gotoXY(4, 37); cout << "ENTER de xac nhan.";
    SetColor(7);

    string soHieu = "";

    while (true) {
        ClearArea(21, 5, 18, 1);
        gotoXY(21, 5);
        SetColor(10); cout << soHieu; SetColor(7);

        int key = ReadKey();

        if (key == 1) { // Ngu?i dùng b?m MUI TÊN LÊN
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= perPage;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            // C?p nh?t l?i giao di?n danh sách
            VeDanhSachMayBayTrongForm(LA, startIdx, highlight, perPage);
        }
        else if (key == 2) { // Ngu?i dùng b?m MUI TÊN XU?NG
            if (highlight < LA.soluong - 1) {
                highlight++;
                if (highlight >= startIdx + perPage) startIdx += perPage;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            // C?p nh?t l?i giao di?n danh sách
            VeDanhSachMayBayTrongForm(LA, startIdx, highlight, perPage);
        }
        else if (key == 4) { // B?m ESC d? thoát
            return -1;
        }
        else if (key == 3) { // B?m ENTER d? ch?n
            if (soHieu.empty()) soHieu = string(LA.DSMB[highlight]->sohieumb);
            int vt = timvitrimaybay(LA, soHieu.c_str());
            if (vt == -1) {
                gotoXY(4, 8); SetColor(12); cout << "Khong tim thay So Hieu MB!   ";
                SetColor(7); _getch(); ClearArea(4, 8, 38, 1); soHieu = ""; continue;
            }
            highlight = vt;
            startIdx = (vt / perPage) * perPage;
            VeDanhSachMayBayTrongForm(LA, startIdx, highlight, perPage);
            gotoXY(4, 8); cout << "Da chon: "; SetColor(10);
            cout << LA.DSMB[vt]->sohieumb; SetColor(7);
            gotoXY(4, 9); cout << "ENTER: Tiep tuc   ESC: Nhap lai";
            while (true) {
                int k = _getch();
                if (k == 13) return vt;
                if (k == 27) { ClearArea(4, 8, 40, 2); soHieu = ""; break; }
            }
        }
    }
}
// ============================================================================
// ÐO?N CODE M?I ÐÃ CHU?N HÓA - NHI COPY VÀ THAY TH? CHO KHU V?C CU B? L?I
// ============================================================================

// 1. Hàm ph? chuy?n d?i tr?ng thái (Ðã tách ra t? tru?c)
static string ChuyenTrangThaiChuyenBayToString(int tt) 
{
    switch(tt){
        case 0: return "Huy chuyen";
        case 1: return "Con ve";
        case 2: return "Het ve";
        case 3: return "Hoan tat";
        default: return "?";
    }
}

// 2. TÁCH HÀM IN DANH SÁCH CHUY?N BAY RA NGOÀI Ð? S?A D?T ÐI?M L?I 'InDSCB'
static void VeDanhSachChuyenBayTrongForm(const vector<PTR> &dsCB, int startIdx, int highlight, int perPage)
{
    // Xóa vùng danh sách cu tru?c khi v? trang m?i
    for (int i = 0; i < perPage; i++) 
        ClearArea(43, 4 + i, 74, 1);

    // Duy?t qua các chuy?n bay c?a trang hi?n t?i d? in ra màn hình
    for (int i = 0; i + startIdx < (int)dsCB.size() && i < perPage; i++) {
        int idx = i + startIdx;
        CB cb   = dsCB[idx]->data;
        int conTrong = cb.tongsove - cb.tongsodaban;

        gotoXY(44, 4 + i);
        if (idx == highlight) SetColor(112); else SetColor(7);

        cout << left << setw(5) << (idx + 1)
                     << setw(12) << cb.machuyenbay
                     << setw(25) << cb.noiden;

        // Ð?nh d?ng xu?t ngày gi? bay (dd/mm/yyyy hh:mm)
        cout << right << setfill('0')
             << setw(2) << cb.thoigiandi.day   << "/"
             << setw(2) << cb.thoigiandi.month << "/"
             << cb.thoigiandi.year << " "
             << setw(2) << cb.thoigiandi.hour  << ":"
             << setw(2) << cb.thoigiandi.minute;
        cout << setfill(' ') << left;

        // Ð?i màu c?t s? vé còn tr?ng (Còn vé: Xanh lá, H?t vé: Ð?)
        if (idx == highlight) SetColor(112);
        else if (conTrong > 0) SetColor(10); else SetColor(12);
        cout << setw(10) << conTrong;

        if (idx == highlight) SetColor(112); else SetColor(7);
        cout << setw(10) << cb.tongsove;
        cout << setw(12) << ChuyenTrangThaiChuyenBayToString(cb.trang_thai);

        SetColor(7);
    }

    // Hi?n th? thanh thông tin phân trang ? cu?i khung ph?i
    gotoXY(44, 35);
    cout << "Trang " << (startIdx / perPage + 1)
         << " / "    << (((int)dsCB.size() - 1) / perPage + 1)
         << "   (" << dsCB.size() << " chuyen bay)      ";
}

// 3. Hàm bu?c ch?n chuy?n bay chính th?c sau khi d?n s?ch Lambda l?i
static PTR BuocChonChuyenBay(PTR First, const char *soHieuMB)
{
    // L?c danh sách chuy?n bay thu?c s? hi?u máy bay dang ch?n
    vector<PTR> dsCB;
    for (PTR p = First; p != NULL; p = p->next)
        if (stricmp(p->data.sohieumaybay, soHieuMB) == 0)
            dsCB.push_back(p);

    system("cls");
    ShowCur(false);

    // Thi?t k? giao di?n Khung trái
    VeKhungDon(2, 38, 2, 40);
    gotoXY(4,  2); SetColor(14); cout << "BUOC 2: CHON CHUYEN BAY"; SetColor(7);
    gotoXY(4,  4); cout << "May bay : "; SetColor(10); cout << soHieuMB; SetColor(7);
    gotoXY(4, 34); SetColor(8);
    cout << "MUI TEN: Di chuyen   ENTER: Chon   ESC: Quay lai";
    SetColor(7);

    // Thi?t k? giao di?n Khung ph?i
    VeKhungDon(2, 38, 42, 118);
    gotoXY(44, 3); SetColor(14);
    cout << left
         << setw(5)  << "STT"
         << setw(12) << "MA CB"
         << setw(25) << "NOI DEN"
         << setw(18) << "NGAY GIO"
         << setw(10) << "CON TRONG"
         << setw(10) << "TONG SO"
         << setw(12) << "TRANG THAI";
    SetColor(7);

    if (dsCB.empty()) {
        gotoXY(44, 5); SetColor(12);
        cout << "May bay nay chua co chuyen bay nao!";
        SetColor(7);
        gotoXY(44, 7); cout << "Nhan phim bat ky de quay lai...";
        _getch();
        return NULL;
    }

    int highlight = 0;
    int startIdx  = 0;
    const int perPage = 30;

    // THAY Ð?I T?I ÐÂY: G?i hàm C++ chu?n thay th? cho InDSCB(); b? l?i
    VeDanhSachChuyenBayTrongForm(dsCB, startIdx, highlight, perPage);

    while (true) {
        int key = ReadKey();
        if (key == 1) { // MUI TÊN LÊN
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= perPage;
                VeDanhSachChuyenBayTrongForm(dsCB, startIdx, highlight, perPage);
            }
        }
        else if (key == 2) { // MUI TÊN XU?NG
            if (highlight < (int)dsCB.size() - 1) {
                highlight++;
                if (highlight >= startIdx + perPage) startIdx += perPage;
                VeDanhSachChuyenBayTrongForm(dsCB, startIdx, highlight, perPage);
            }
        }
        else if (key == 4) { // ESC -> Quay l?i bu?c 1
            return NULL;
        }
        else if (key == 3) { // ENTER -> Ch?t ch?n chuy?n bay này
            return dsCB[highlight];
        }
    }
}
static void BuocXemVeTrong(CB &cb)
{
    system("cls");
    ShowCur(false);

    // --- Khung trai (thong tin + danh sach ve trong) ---
    VeKhungDon(2, 48, 2, 40);

    gotoXY(4,  2); SetColor(14); cout << "VE CON TRONG"; SetColor(7);

    gotoXY(4,  4); cout << "Ma CB      : "; SetColor(10); cout << cb.machuyenbay; SetColor(7);
    gotoXY(4,  5); cout << "May bay    : "; cout << cb.sohieumaybay;
    gotoXY(4,  6); cout << "Noi den    : "; cout << cb.noiden;
    gotoXY(4,  7); cout << "Ngay gio   : ";
    cout << right << setfill('0')
         << setw(2) << cb.thoigiandi.day   << "/"
         << setw(2) << cb.thoigiandi.month << "/"
         << cb.thoigiandi.year  << "  "
         << setw(2) << cb.thoigiandi.hour  << ":"
         << setw(2) << cb.thoigiandi.minute;
    cout << setfill(' ') << left;

    int conTrong = cb.tongsove - cb.tongsodaban;
    gotoXY(4,  9); cout << "Tong so ghe : "; SetColor(7);   cout << cb.tongsove;
    gotoXY(4, 10); cout << "Da dat      : "; SetColor(12);  cout << cb.tongsodaban; SetColor(7);
    gotoXY(4, 11); cout << "Con trong   : "; SetColor(10);  cout << conTrong;       SetColor(7);

    // Duong ke ngang phan cach
    gotoXY(3, 13);
    SetColor(8);
    for (int i = 0; i < 36; i++) cout << (char)196;
    SetColor(7);

    // Danh sach so ghe trong
    InDanhSachVeTrong(cb, 14);

    gotoXY(4, 46); SetColor(8); cout << "Nhan phim bat ky de quay lai..."; SetColor(7);

    // --- Khung phai (so do ghe) ---
    VeKhungDon(2, 48, 38, 118);

    // Ve so do ghe (khung phai: col 43..117, row 4..47)
    VeSoDoGhe(cb, 40, 3, 116, 46);

    _getch();
}


void InVeTrong()
{
    // Doc du lieu
    DSMB LA;
    LA.soluong = 0;
    DocFileMayBay(LA);

    PTR First = NULL;
    DocFileChuyenBay(First, LA);

    if (LA.soluong == 0) {
        system("cls");
        gotoXY(5, 5); SetColor(12);
        cout << "Chua co du lieu may bay! Vui long nhap lieu truoc.";
        SetColor(7); _getch(); return;
    }

    while (true) {
        // Buoc 1: Chon may bay
        int vtMB = BuocChonMayBay(LA);
        if (vtMB == -1) break; // ESC -> thoat

        while (true) {
            // Buoc 2: Chon chuyen bay thuoc may bay nay
            PTR pCB = BuocChonChuyenBay(First, LA.DSMB[vtMB]->sohieumb);
            if (pCB == NULL) break; // ESC -> quay lai buoc 1

            // Buoc 3: Hien thi ve trong + so do ghe
            BuocXemVeTrong(pCB->data);
            // Xong -> quay lai buoc 2 de chon chuyen bay khac
        }
    }

    system("cls");
}


#ifdef TEST_VETRONG
int main()
{
    InVeTrong();
    return 0;
}
#endif*/
void MenuVe() {
    DSMB LA;
    PTR First = NULL;
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
                if (chon == 0) {       //Thêm
                    menuCap = 2;
                    daClear = false;
                } else if (chon == 1) {
                	menuCap = 3;
                	daClear = false;
                } else if (chon == 2) {
                	menuCap = 4;
                	daClear = false;
                }
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
        else if (menuCap == 4) { // 3. CH?C NANG XEM VÉ TR?NG & SO Ð? GH?
            //InVeTrong(); // Hàm v? so d? gh? không ch?a auto t?i mình v?a làm xong
            system("cls"); ShowCur(false);
            VeKhung(); VeKhungHuongDan();
            menuCap = 1; daClear = false; chon = 2;
        }
    }
}
