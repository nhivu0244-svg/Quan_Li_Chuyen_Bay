#include <bits/stdc++.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
#include "bien.h"
#include "Datetime1.h"
#include "maybay.h"
#include "chuyenbay1.h"
#include "Ve.h"

PTR timmachuyenbay(PTR First, const char *ma){
	PTR p;
	for (p = First; p != NULL;p =  p -> next)
		if (stricmp(p->data.machuyenbay, ma) == 0) return p;
	return NULL;
}
int timvtchuyenbay(PTR First, const char *ma){
	int tmp = 0;
	for (PTR p = First; p != NULL;p =  p -> next){
		if (stricmp(p->data.machuyenbay, ma) == 0) return tmp;
		tmp++;
    }
	return -1;
}
long long DoiRaTongSoPhut(Datetime dt) {
    long long tongPhut = 0;
    
    // Quy d?i nam ra phút (trung bình 1 nam có 365 ngày)
    tongPhut += (long long)dt.year * 365 * 24 * 60;
    
    // Quy d?i tháng ra phút (tính trung bình 1 tháng có 30 ngày)
    tongPhut += (long long)dt.month * 30 * 24 * 60;
    
    // Quy d?i ngày, gi?, phút th?c t?
    tongPhut += (long long)dt.day * 24 * 60;
    tongPhut += (long long)dt.hour * 60;
    tongPhut += dt.minute;
    
    return tongPhut;
}

/* Hàm chính: Ki?m tra máy bay có dang b?n l?ch bay nào khác không
   - Tr? v? true: Máy bay ÐANG B?N (Không du?c phép thêm chuy?n)
   - Tr? v? false: Máy bay ÐANG R?NH (H?p l?, cho phép thêm chuy?n)
*/
bool KiemTraMayBayDangBan(PTR First, const char* sohieumb, Datetime thoiGianMoi) {
    
    // Bu?c 1: Ð?i th?i gian c?a chuy?n bay m?i d?nh thêm ra t?ng s? phút
    long long phutMoi = DoiRaTongSoPhut(thoiGianMoi);
    
    // Bu?c 2: Duy?t danh sách liên k?t vòng l?p t? d?u d?n cu?i d? ki?m tra l?ch
    for (PTR p = First; p != NULL; p = p->next) {
        
        // Tiêu chí 1: N?u không trùng s? hi?u máy bay -> b? qua, check chuy?n ti?p theo
        if (stricmp(p->data.sohieumaybay, sohieumb) != 0) {
            continue;
        }
        
        // Tiêu chí 2: Ch? check nh?ng chuy?n chua hoàn t?t/chua h?y
        // Tr?ng thái 1: Còn vé, Tr?ng thái 2: H?t vé.
        // N?u chuy?n bay dã H?y (0) ho?c Hoàn t?t (3) thì máy bay dó dã r?nh -> b? qua
        if (p->data.trang_thai != 1 && p->data.trang_thai != 2) {
            continue;
        }
        
        // Bu?c 3: Ð?i th?i gian c?a chuy?n bay cu dang có trong danh sách ra t?ng s? phút
        long long phutCu = DoiRaTongSoPhut(p->data.thoigiandi);
        
        // Bu?c 4: Tính kho?ng cách chênh l?ch th?i gian gi?a 2 chuy?n bay
        long long chenhLech = phutMoi - phutCu;
        
        // L?y giá tr? tuy?t d?i (Tr? tuy?t d?i th? công tránh dùng thu vi?n toán h?c nâng cao)
        if (chenhLech < 0) {
            chenhLech = -chenhLech;
        }
        
        // Bu?c 5: So sánh kho?ng cách c?t cánh
        // N?u kho?ng cách gi?a 2 chuy?n bay nh? hon 420 phút (7 ti?ng)
        if (chenhLech < PHUT_BAN) {
            return true; // K?t lu?n l?p t?c: Máy bay dang b?n!
        }
    }
    
    return false; // Duy?t h?t danh sách không vu?ng l?ch nào -> Máy bay r?nh, an toàn!
}
void Insert_Order_CB(PTR &First, CB x){
	if (timvtchuyenbay(First, x.machuyenbay) != -1) {
        cout << "==> Loi: Ma chuyen bay " << x.machuyenbay << " da ton tai!" << endl;
        return;
    }
	PTR p = new nodeCB;// Tao nut moi cap phat vung nho
	p -> data = x;
	p -> next = NULL;
	// tim vi tri de chen
	PTR s = First, t = NULL;
	while( s!= NULL && strcmp(s-> data.machuyenbay, x.machuyenbay) < 0){
		t = s;
		s = s -> next;
	}
	if ( t == NULL){
		p->next = First;
		First = p;
	}
	else{
		p -> next = s;
		t -> next = p;
	}
}
void Thongtin1chuyenbay(CB x, int position){
	int leftt = 40;
	int top = 2;
	int y = top + 3 + position;
	cout << setfill(' ');
	ClearArea(leftt + 5, y, 65, 1);
	gotoXY(leftt + 3, y); cout << left << setw(10) << x.machuyenbay ;
	gotoXY(leftt + 15, y); cout << setw(15) << x.noiden;
	gotoXY(leftt + 32, y); cout << setw(10) << x.sohieumaybay;
	gotoXY(leftt + 45, y);
	cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
             << setw(2) << x.thoigiandi.minute << " " 
             << setw(2) << x.thoigiandi.day << "/" 
             << setw(2) << x.thoigiandi.month << "/" 
             << x.thoigiandi.year;
    cout << setfill(' ') << left;
    gotoXY(leftt + 65, y);
    if (x.trang_thai == 0 ) cout << right << setw(5) << "Huy chuyen";
    else if (x.trang_thai == 1 ) cout << right << setw(5) << "Con ve";
    else if (x.trang_thai == 2 ) cout << right << setw(5) << "Het ve";
    else if (x.trang_thai == 3 ) cout << right << setw(5) << "Hoan tat";
}
void Thongtinchuyenbaymottrang(PTR First, int StartIndex) { 
    // 1. Xóa vùng d? li?u cu (Xóa 20 dòng trong khung)
    for(int i = 0; i < 20; i++) {
        ClearArea(41, 4 + i, 74, 1); 
    }

    // 2. Ð?m t?ng s? chuy?n bay d? tính trang (Vì DSLK không có bi?n .soluong s?n nhu m?ng)
    int tongCB = 0;
    for (PTR p = First; p != NULL; p = p->next) {
        tongCB++;
    }

    // N?u danh sách r?ng thì thoát s?m
    if (tongCB == 0) {
        gotoXY(70, 10); cout << "DANH SACH TRONG";
        gotoXY(75, 26); cout << " Trang 0 / 0";
        return;
    }

    // 3. Tìm node b?t d?u in (Tuong duong v?i StartIndex trong m?ng)
    PTR p = First;
    for (int i = 0; i < StartIndex && p != NULL; i++) {
        p = p->next;
    }

    // 4. In d? li?u trang hi?n t?i (T?i da 20 dòng)
    int NumberPerPage = 20;
    int i = 0;
    while (p != NULL && i < NumberPerPage) {
        // G?i hàm in chi ti?t 1 dòng Chuy?n bay
        Thongtin1chuyenbay(p->data, i);
        
        p = p->next;
        i++;
    }

    // 5. Tính toán và in s? trang (Gi?ng h?t logic máy bay c?a Nhi)
    int totalPage = (tongCB - 1) / NumberPerPage + 1;
    int curPage = (StartIndex / NumberPerPage) + 1;
    
    gotoXY(75, 26); 
    cout << " Trang " << curPage << " / " << totalPage; 
}
string TrangThaiStr(int tt)
{
    switch(tt){
        case 0: return "HuyCB";
        case 1: return "ConVe";
        case 2: return "HetVe";
        case 3: return "HoanTat";
        default: return "?";
    }
}
// HÀM NÀY CH? DÙNG Ð? GHI VÉ RA FILE KHI Ð?T VÉ/H?Y VÉ KHÔNG ÐU?C G?I KHI Ð?C FILE
void DSVCuaMotCB(CB &x){
    if (x.tongsove <= 0 || x.dsve == NULL) return;

    char filenameve[100] = "DSV\\";
    strcat(filenameve, x.machuyenbay);
    strcat(filenameve, ".txt");

    ofstream file(filenameve, ios::out); // Ch? d? ghi xu?t file
    if (!file.is_open()) return;

    file << x.tongsodaban << endl;

    for(int i = 0; i < x.tongsove; i++){
        if(x.dsve[i].tt == true){
            file << x.dsve[i].CMND << " " << x.dsve[i].ghe_so << endl;
        }
    }
    file.close();
}
// HÀM M?I: CHUYÊN DÙNG Ð? Ð?C D? LI?U VÉ VÀO B? NH? KHI M? APP
void DocFileDSV(CB &x) {
    if (x.tongsove <= 0) {
        x.dsve = NULL;
        return;
    }

    // 1. C?p phát m?ng d?ng tr?ng cho chuy?n bay tru?c d? tránh l?i con tr? hoang
    x.dsve = new VE[x.tongsove];
    for (int i = 0; i < x.tongsove; i++) {
        x.dsve[i].ghe_so = i + 1;
        x.dsve[i].CMND = 0;
        x.dsve[i].tt = false;
    }

    char filenameve[100] = "DSV\\";
    strcat(filenameve, x.machuyenbay);
    strcat(filenameve, ".txt");

    // 2. Dùng ifstream d? Ð?C (Tuy?t d?i không dùng ofstream làm m?t file)
    ifstream file(filenameve, ios::in);
    if (!file.is_open()) return; // N?u chua t?ng d?t vé nào (file chua có) thì m?ng v?n tr?ng, an toàn.

    int sodabanvethucte;
    file >> sodabanvethucte; // Ð?c b? qua dòng s? lu?ng vé dã bán ? d?u file

    unsigned int cmndTmp;
    int gheTmp;
    // 3. Ð?c liên t?c các c?p (CMND, S? gh?) dang luu trong file text n?p vào so d? gh?
    while (file >> cmndTmp >> gheTmp) {
        if (gheTmp >= 1 && gheTmp <= x.tongsove) {
            x.dsve[gheTmp - 1].CMND = cmndTmp;
            x.dsve[gheTmp - 1].tt = true;
        }
    }
    file.close();
}
void GhiFileChuyenBay(PTR First){
    ofstream fileout("DSCB.txt", ios::out); 
    if (!fileout.is_open()) return;
    int tongsoCB = 0;
    for (PTR p = First; p != NULL; p = p->next)
        tongsoCB++;
    fileout << tongsoCB << endl;
    for (PTR p = First; p != NULL; p = p->next) {
        fileout << p->data.machuyenbay << endl;
        fileout << p->data.noiden << endl;
        fileout << p->data.sohieumaybay << endl;
        fileout << p->data.thoigiandi.hour << endl;
        fileout << p->data.thoigiandi.minute << endl;
        fileout << p->data.thoigiandi.day << endl;
        fileout << p->data.thoigiandi.month << endl;
        fileout << p->data.thoigiandi.year << endl;
        fileout << p->data.tongsodaban << endl;
        fileout << p->data.trang_thai << endl;
        
        DSVCuaMotCB(p->data);
    }
    fileout.close();
}
bool ConHon1Tuan(Datetime dt) {
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

    return difftime(gioBay, now) >= 7 * 24 * 60 * 60;
}
void TuDongCapNhat(PTR pCB, PTR &First){
	if(pCB == NULL) return;
	if(pCB->data.trang_thai == 0 || pCB->data.trang_thai == 3) return;
	time_t now = time(0);
    tm tg;
    tg.tm_year = pCB->data.thoigiandi.year   - 1900;
    tg.tm_mon  = pCB->data.thoigiandi.month - 1;
    tg.tm_mday = pCB->data.thoigiandi.day;
    tg.tm_hour = pCB->data.thoigiandi.hour;
    tg.tm_min  = pCB->data.thoigiandi.minute;
    tg.tm_sec  = 0;
    tg.tm_isdst = -1;
    time_t gioBay = mktime(&tg);
    if(difftime(now, gioBay) >= 3 * 60 * 60) {
	    pCB->data.trang_thai = 3;
	    GhiFileChuyenBay(First);
	    }
}
void DocFileChuyenBay(PTR &First, DSMB &LA) {
    ifstream filein("DSCB.txt", ios::in);

    int nFlight;
    if (!(filein >> nFlight)) return;

    filein.ignore();

    for (int j = 0; j < nFlight; j++) {

        CB x;
        x.dsve = NULL;

        filein.getline(x.machuyenbay, 15);
        filein.getline(x.noiden, 30);
        filein.getline(x.sohieumaybay, 15);

        filein >> x.thoigiandi.hour
               >> x.thoigiandi.minute
               >> x.thoigiandi.day
               >> x.thoigiandi.month
               >> x.thoigiandi.year;

        filein >> x.tongsodaban;
        filein >> x.trang_thai;

        filein.ignore();

        int vt = timvitrimaybay(LA, x.sohieumaybay);

        x.tongsove = (vt != -1) ? LA.DSMB[vt]->socho : 0;

        if (vt != -1)
            LA.DSMB[vt]->Solanthuchienchuyenbay++;
            
        DocFileDSV(x);
        Insert_Order_CB(First, x);
        PTR p = First;
        while (p != NULL){
        	if(strcmp(p->data.machuyenbay, x.machuyenbay) == 0){
        		TuDongCapNhat(p, First);
        		break;
			}
			p = p->next;
		}
    }

    filein.close();
}

void NhapLieuThoiGian(Datetime &DT)
{
	int DTordinal = 0;
	bool SaveOrNot = false;
	while( true )
	{
		switch(DTordinal)
		{
		case 0:
			ConstraintForDateAndTime(DT.hour,SaveOrNot,23);
			if(SaveOrNot){
			    cout << ":";
			    DTordinal++;
		    } else return;
			break;
		case 1:
			ConstraintForDateAndTime(DT.minute,SaveOrNot,59);
			if(SaveOrNot){
			    cout << " ";
			    DTordinal++;
		    } else return;
			break;
		case 2:
			ConstraintForDateAndTime(DT.day,SaveOrNot,31);
			if(SaveOrNot){
			    cout << "/";
			    DTordinal++;
		    } else return;
			break;
		case 3:
			ConstraintForDateAndTime(DT.month,SaveOrNot,12);
		    if(SaveOrNot){
			    cout << "/";
			    DTordinal++;
		    } else return;
			break;
		case 4:
			ConstraintForDateAndTime(DT.year,SaveOrNot,2100);
			return;
		}
	}
}
void NhapLieuChuyenBay(PTR &First, DSMB &LA, int &StartIdx, int NumberPerPage){
	ShowCur(true);
	bool SaveOrNot = false;//luu lai hay chua
	CB x;
	x.tongsodaban = 0;
	x.trang_thai = 1;
	x.dsve = NULL;// chua co ve
	string maCB, noiden, sohieumb;
	int h, mi, d, m, y;
	int ordinal = 0;
	gotoXY(4 + 21, 14); cout << "1";
	while(true){
		switch(ordinal){
			case 0:{
				ConstraintForLETTERAndNumber(sohieumb, ordinal, SaveOrNot, 21);
                if (SaveOrNot) {
                    int vt = timvitrimaybay(LA, sohieumb.c_str());
                    if (vt == -1) { 
                        gotoXY(4, 18); SetColor(12);cout << "So Hieu MB khong ton tai!";
                        SetColor(7);
						_getch();
                        ClearArea(4, 18, 30, 1);
                        gotoXY(4 + 21, 4); cout << string(sohieumb.length(), ' ');
                        sohieumb = ""; 
                    }else ordinal++;        
                }
                else return;
                break;
            }
			case 1:
            {
				ConstraintForLETTERAndNumber(maCB, ordinal, SaveOrNot, 21);
				if(SaveOrNot){
				if(timvtchuyenbay(First, maCB.c_str()) != -1){
					gotoXY(4, 18); SetColor(14);cout << "Loi! Ma CB nay da ton tai!";
					SetColor(7);
					_getch();
					//ClearArea(4 + 12, 4, 10, 1);
					ClearArea(4, 18, 28, 1);
					gotoXY(4 + 21, ordinal*2 + 4); cout << string(maCB.length(),' ');
					maCB = "";
					ordinal = 1;	
			 }
				else ordinal++;
			}
				break;
			}
			case 2:{
				gotoXY(4 + 21, ordinal*2 + 4);
				ConstraintsForLetterAndSpace(noiden, ordinal, SaveOrNot, 21);
				if(SaveOrNot)
					ordinal++;	
			    break;
	        }
	        case 3:{
	        	gotoXY(4 + 10, 12);
	        	NhapLieuThoiGian(x.thoigiandi);
	        	
	        		if(!kiemtrahople(x.thoigiandi)){
	        			gotoXY(4,18); SetColor(14);cout<< "Loi! Thoi gian o qua khu";
	        			SetColor(7);
						_getch();
	        			ClearArea(4, 18, 30, 1);
	        			ClearArea(14, 12, 17, 1);
	        			gotoXY(14, 12); cout << "                 ";
	        			x.thoigiandi.hour = 0;
                        x.thoigiandi.minute = 0;
                        x.thoigiandi.day = 0;
                        x.thoigiandi.month = 0;
                        x.thoigiandi.year = 0;
					}
					else if(!ConHon1Tuan(x.thoigiandi)){
						gotoXY(4,18); SetColor(14);cout<< "Phai them truoc it nhat 1 tuan";
	        			SetColor(7);
						_getch();
	        			ClearArea(4, 18, 34, 1);
	        			ClearArea(14, 12, 17, 1);
	        			gotoXY(14, 12); cout << "                 ";
	        			x.thoigiandi.hour = 0;
                        x.thoigiandi.minute = 0;
                        x.thoigiandi.day = 0;
                        x.thoigiandi.month = 0;
                        x.thoigiandi.year = 0;
					}
					else if (KiemTraMayBayDangBan(First, sohieumb.c_str(), x.thoigiandi)) {
					gotoXY(4, 19); SetColor(12);
					cout << "May bay co lich bay chua hoan tat!"; SetColor(7);
					_getch();
					ClearArea(4, 19, 34, 1);
					ClearArea(14, 12, 17, 1); // Xóa ngày gi? v?a nh?p d? nh?p l?i
					gotoXY(14, 12); cout << "                 ";
					continue; // B?t nh?p l?i th?i gian cho trùng kh?p v?i l?ch tr?ng máy bay
				}
					else ordinal++;
				break;
			}
	        case 4:{
	        	strcpy(x.machuyenbay, maCB.c_str());
                strcpy(x.sohieumaybay, sohieumb.c_str());
                strcpy(x.noiden, noiden.c_str());
                x.tongsodaban = 0; 
                x.trang_thai = 1;
                int vtMB = timvitrimaybay(LA, x.sohieumaybay);
                if(vtMB != -1) {
                    x.tongsove = LA.DSMB[vtMB]->socho;
                }  
                Insert_Order_CB(First, x);
                GhiFileChuyenBay(First);
	        	int n = 0;
	        	for (PTR p = First; p != NULL; p = p->next) n++;
	        	StartIdx = ((n - 1) / NumberPerPage) * NumberPerPage;
	        	gotoXY(4,18); SetColor(10);cout<<"Them chuyen bay thanh cong";
				SetColor(7);
				Thongtinchuyenbaymottrang(First,StartIdx);
	        	while(true){
	        		int key = ReadKey();
	        		    if(key == 4) return;
                        if(key == 6){
                        	if (StartIdx + NumberPerPage < First->data.tongsove) {
                                StartIdx += NumberPerPage;
                                Thongtinchuyenbaymottrang(First, StartIdx);
                            }
                        }
                        else if (key == 5) {
                            if (StartIdx >= NumberPerPage) {
                                StartIdx -= NumberPerPage;
                                Thongtinchuyenbaymottrang(First, StartIdx);
                            }
                        }
                    }
                    break;
                }
			}
	    }
    }
void InDSChuyenBay(PTR First, int highlight, int startIdx)
{
    static int oldStart = -1;
    if (oldStart != startIdx)
    {
        for (int i = 0; i < PER_PAGE; i++)
            ClearArea(R_LEFT+1, 2+i, R_RIGHT-R_LEFT-1, 1);
        oldStart = startIdx;
    }

    // Ði t?i ph?n t? d?u c?a trang
    PTR p = First;
    for (int i = 0; i < startIdx && p != NULL; i++)
        p = p->next;

    // In PER_PAGE ph?n t? t? p
    for (int i = 0; i < PER_PAGE && p != NULL; i++)  // <-- s?a i != NULL thành p != NULL
    {
        int  idx = i + startIdx;
        CB  &cb  = p->data;                           // <-- dùng p->data thay vì dsCB[idx]->data

        gotoXY(R_LEFT+1, 2+i);
        if (idx == highlight) SetColor(112); else SetColor(7);
        cout << left
             << setw(7)  << (idx+1)
             << setw(10)  << cb.machuyenbay
             << setw(18) << cb.noiden;
        cout << right << setfill('0')
             << setw(2) << cb.thoigiandi.hour    << ":"
             << setw(2) << cb.thoigiandi.minute  << " "
             << setw(2) << cb.thoigiandi.day   << "/"
             << setw(2) << cb.thoigiandi.month << "/"
             << setfill(' ') << left << setw(10) << cb.thoigiandi.year;
        cout << TrangThaiStr(cb.trang_thai);
        SetColor(7);

        p = p->next;  // <-- bu?c sang node ti?p theo
    }

    // In thanh tr?ng thái trang — c?n d?m t?ng s? node
    int total = 0;
    for (PTR t = First; t != NULL; t = t->next) total++;

    ClearArea(R_LEFT+1, BOT-1, R_RIGHT-R_LEFT-1, 1);
    gotoXY(R_LEFT+1, BOT-1);
    if (total == 0) total = 1;
    cout << "Trang " << (startIdx / PER_PAGE + 1)
         << "/"      << ((total - 1) / PER_PAGE + 1)
         << " ("     << total << " CB)";
}
PTR GetNode(PTR First, int idx)
{
    PTR p = First;
    for (int i = 0; i < idx && p != NULL; i++)
        p = p->next;
    return p;
}

int CountNodes(PTR First)
{
    int count = 0;
    for (PTR p = First; p != NULL; p = p->next) count++;
    return count;
}
static int SNgayGio(PTR First, DSMB LA)
{
    ClearConsole();
    ShowCur(false);

    VeKhungDon(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "THONG TIN"; SetColor(7);
    gotoXY(4, 4);  cout << "MA CHUYEN BAY :";
    gotoXY(4, 6);  cout << "NOI DEN       :";
    gotoXY(4, 8);  cout << "SO HIEU       :";
    gotoXY(4, 10); cout << "NGAY GIO      :"; 
    gotoXY(4, 12); cout << "TRANG THAI    :"; 
    
    ClearArea(1, BOT - 2, L_RIGHT - 2, 2);
    SetColor(8);
    gotoXY(2, BOT - 2); cout << "UP/DOWN : Di chuyen";
    gotoXY(2, BOT - 1); cout << "ENTER : Chon    ESC : Thoat";
    SetColor(7);

    VeKhungDon(TOP, BOT, R_LEFT, R_RIGHT);
    gotoXY(R_LEFT + 1, 1); SetColor(14);
    cout << left
         << setw(7)  << "STT"
         << setw(10)  << "MA CB"
         << setw(18) << "NOI DEN"
         << setw(25) << "NGAY GIO"
         << setw(8)  << "TT";
    SetColor(7);
    
    int highlight = 0;
    int startIdx  = 0;

    InDSChuyenBay(First, highlight, startIdx);
    if (First != NULL) {
    	CB &x = First->data;
        gotoXY(X_VALUE, 4);  SetColor(10); cout << x.machuyenbay;
        gotoXY(X_VALUE, 6);  SetColor(10); cout << x.noiden;
        gotoXY(X_VALUE, 8);  SetColor(10); cout << x.sohieumaybay;
        gotoXY(X_VALUE, 10); SetColor(10); 
        cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
             << setw(2) << x.thoigiandi.minute << " " 
             << setw(2) << x.thoigiandi.day << "/" 
             << setw(2) << x.thoigiandi.month << "/" 
             << x.thoigiandi.year;
        cout << setfill(' ') << left;
        gotoXY(X_VALUE, 12); SetColor(10); cout << x.trang_thai;
        SetColor(7);
    }

    while (true) {
        int key = ReadKey();
        int total = CountNodes(First);
        // 1. X? LÝ DI CHUY?N LÊN
        if (key == 1) {
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= PER_PAGE;
                
                InDSChuyenBay(First, highlight, startIdx);
                PTR p = GetNode(First, highlight);
                if (p != NULL) {
                    CB &x = p->data;
                    ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 10, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 12, L_RIGHT - X_VALUE - 1, 1);
                
                gotoXY(X_VALUE, 4);  SetColor(10); cout << x.machuyenbay;
                gotoXY(X_VALUE, 6);  SetColor(10); cout << x.noiden;
                gotoXY(X_VALUE, 8);  SetColor(10); cout << x.sohieumaybay;
                gotoXY(X_VALUE, 10); SetColor(10); 
                cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
                     << setw(2) << x.thoigiandi.minute << " " 
                     << setw(2) << x.thoigiandi.day << "/" 
                     << setw(2) << x.thoigiandi.month << "/" 
                     << x.thoigiandi.year;
                cout << setfill(' ') << left;
                gotoXY(X_VALUE, 12); SetColor(10); cout << x.trang_thai;
                SetColor(7);
                }
            }
        }
        // 2. X? LÝ DI CHUY?N XU?NG
        else if (key == 2) {
            if (highlight < total - 1) {
                highlight++;
                if (highlight >= startIdx + PER_PAGE) startIdx += PER_PAGE;
                
                InDSChuyenBay(First, highlight, startIdx);
                PTR p = GetNode(First, highlight);
                if (p != NULL) {
                   CB &x = p->data;
                ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 10, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 12, L_RIGHT - X_VALUE - 1, 1);
                
                gotoXY(X_VALUE, 4);  SetColor(10); cout << x.machuyenbay;
                gotoXY(X_VALUE, 6);  SetColor(10); cout << x.noiden;
                gotoXY(X_VALUE, 8);  SetColor(10); cout << x.sohieumaybay;
                gotoXY(X_VALUE, 10); SetColor(10); 
                cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
                     << setw(2) << x.thoigiandi.minute << " " 
                     << setw(2) << x.thoigiandi.day << "/" 
                     << setw(2) << x.thoigiandi.month << "/" 
                     << x.thoigiandi.year;
                cout << setfill(' ') << left;
                gotoXY(X_VALUE, 12); SetColor(10); cout << x.trang_thai;
                SetColor(7);
                } 
            }
        }
        // 3. NH?N ESC Ð? THOÁT
        else if (key == 4) {
            return -1;
        }
        // 4. NH?N ENTER Ð? CH?N S?A
        else if (key == 3) {
        	PTR p = GetNode(First, highlight);
            if (p == NULL) continue;
            CB &x = p->data;
            if (x.trang_thai == 0 || x.trang_thai == 3) {
                gotoXY(2, 14); SetColor(12); cout << "LOI! KHONG THE SUA CHUYEN BAY NAY!"; SetColor(7);
                _getch(); ClearArea(2, 14, 42, 1);
                continue;
            }

            gotoXY(2, 14); cout << "Sua ngay CB: "; SetColor(10);
            cout << x.machuyenbay; SetColor(7);
            gotoXY(2, 15); SetColor(8); cout << "ENTER:OK  ESC:Huy"; SetColor(7);

            bool dongYSua = false;
            while (true) {
                int k = _getch();
                if (k == 13) { ClearArea(2, 14, 40, 2); dongYSua = true; break; }
                if (k == 27) { ClearArea(2, 14, 40, 2); dongYSua = false; break; }
            }
            if (dongYSua) {
                Datetime oldNgayGio = x.thoigiandi;
                ShowCur(true);

                while (true) {
                    Datetime temp = oldNgayGio;  // ? luu t?m d? so sánh
                    ClearArea(X_VALUE, 10, 20, 1);
                    gotoXY(X_VALUE, 10);
                    NhapLieuThoiGian(temp);
                    if (temp.hour   == oldNgayGio.hour   &&
                        temp.minute == oldNgayGio.minute &&
                        temp.day    == oldNgayGio.day    &&
                        temp.month  == oldNgayGio.month  &&
                        temp.year   == oldNgayGio.year)
                    {
                        // Hi?n th? l?i ngày gi? cu
                        ClearArea(X_VALUE, 10, 20, 1);
                        gotoXY(X_VALUE, 10);
                        cout << right << setfill('0') << setw(2) << oldNgayGio.hour << ":"
                             << setw(2) << oldNgayGio.minute << " "
                             << setw(2) << oldNgayGio.day << "/"
                             << setw(2) << oldNgayGio.month << "/"
                             << oldNgayGio.year;
                            cout << setfill(' ') << left;
                            ShowCur(false);
                            break;  // thoát, không luu
                    }

                    x.thoigiandi = temp;  // ? gán l?i sau khi xác nh?n có nh?p

                    if (!kiemtrahople(x.thoigiandi)) {
                        gotoXY(2, 14); SetColor(12);
                        cout << "Loi: Ngay gio khong hop le!"; SetColor(7);
                        _getch();
                        ClearArea(2, 14, 35, 1);
                        x.thoigiandi = oldNgayGio;
                        continue;
                    }
                    else if (!ConHon1Tuan(x.thoigiandi)) {
                        gotoXY(2, 14); SetColor(12);
                        cout << "Phai dieu chinh truoc it nhat 1 tuan"; SetColor(7);
                        _getch();
                        ClearArea(2, 14, 36, 1);
                        x.thoigiandi = oldNgayGio;
                        continue;
                    }

                    GhiFileChuyenBay(First);    
            
                    gotoXY(2, 14); SetColor(10); cout << "Cap nhat thanh cong!"; SetColor(7);
                    _getch(); 
                    ClearArea(2, 14, 30, 1);

                    int dongY = 2 + (highlight - startIdx);
                    gotoXY(R_LEFT+1, dongY);
                    SetColor(116);
                    cout << left << setfill(' ')
                         << setw(7)  << (highlight+1)
                         << setw(10)  << x.machuyenbay
                         << setw(18) << x.noiden;
                    cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
                         << setw(2) << x.thoigiandi.minute << " " 
                         << setw(2) << x.thoigiandi.day << "/" 
                         << setw(2) << x.thoigiandi.month << "/" 
                         << setfill(' ') << left << setw(10) << x.thoigiandi.year;
                    cout << TrangThaiStr(x.trang_thai);
                    SetColor(7);
                    ShowCur(false);
                    break;
                }
                        
            }
       }
    }
}
static int STrangThai(PTR First, DSMB LA)
{
    ClearConsole();
    ShowCur(false);

    VeKhungDon(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "THONG TIN"; SetColor(7);
    gotoXY(4, 4);  cout << "MA CHUYEN BAY :";
    gotoXY(4, 6);  cout << "NOI DEN       :";
    gotoXY(4, 8);  cout << "SO HIEU       :";
    gotoXY(4, 10); cout << "NGAY GIO      :"; 
    gotoXY(4, 12); cout << "TRANG THAI    :"; 
    
    gotoXY(4, 20); cout << "           Chu Thich          ";
	gotoXY(4, 22); cout << "    0:Huy chuyen    1:Con ve";
    gotoXY(4, 24); cout << "    2:Het ve        3:Hoan tat"; 
    
    ClearArea(1, BOT - 2, L_RIGHT - 2, 2);
    SetColor(8);
    gotoXY(2, BOT - 10); cout << "UP/DOWN : Di chuyen";
    gotoXY(2, BOT - 1); cout << "ENTER : Chon    ESC : Thoat";
    SetColor(7);

    VeKhungDon(TOP, BOT, R_LEFT, R_RIGHT);
    gotoXY(R_LEFT + 1, 1); SetColor(14);
    cout << left
         << setw(7)  << "STT"
         << setw(10)  << "MA CB"
         << setw(18) << "NOI DEN"
         << setw(25) << "NGAY GIO"
         << setw(8)  << "TT";
    SetColor(7);
    
    int highlight = 0;
    int startIdx  = 0;

    InDSChuyenBay(First, highlight, startIdx);
    if (First != NULL) {
    	CB &x = First->data;
        gotoXY(X_VALUE, 4);  SetColor(10); cout << x.machuyenbay;
        gotoXY(X_VALUE, 6);  SetColor(10); cout << x.noiden;
        gotoXY(X_VALUE, 8);  SetColor(10); cout << x.sohieumaybay;
        gotoXY(X_VALUE, 10); SetColor(10); 
        cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
             << setw(2) << x.thoigiandi.minute << " " 
             << setw(2) << x.thoigiandi.day << "/" 
             << setw(2) << x.thoigiandi.month << "/" 
             << x.thoigiandi.year;
        cout << setfill(' ') << left;
        gotoXY(X_VALUE, 12); SetColor(10); cout << x.trang_thai;
        SetColor(7);
    }

    while (true) {
        int key = ReadKey();
        int total = CountNodes(First);

        if (key == 1) {
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= PER_PAGE;
                
                InDSChuyenBay(First, highlight, startIdx);
                PTR p = GetNode(First, highlight);
                if (p != NULL) {
                    CB &x = p->data;
                    ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 10, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 12, L_RIGHT - X_VALUE - 1, 1);
                
                gotoXY(X_VALUE, 4);  SetColor(10); cout << x.machuyenbay;
                gotoXY(X_VALUE, 6);  SetColor(10); cout << x.noiden;
                gotoXY(X_VALUE, 8);  SetColor(10); cout << x.sohieumaybay;
                gotoXY(X_VALUE, 10); SetColor(10); 
                cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
                     << setw(2) << x.thoigiandi.minute << " " 
                     << setw(2) << x.thoigiandi.day << "/" 
                     << setw(2) << x.thoigiandi.month << "/" 
                     << x.thoigiandi.year;
                cout << setfill(' ') << left;
                gotoXY(X_VALUE, 12); SetColor(10); cout << x.trang_thai;
                SetColor(7);
                }
            }
        }
        else if (key == 2) {
            if (highlight < total - 1) {
                highlight++;
                if (highlight >= startIdx + PER_PAGE) startIdx += PER_PAGE;
                
                InDSChuyenBay(First, highlight, startIdx);
                PTR p = GetNode(First, highlight);
                if (p != NULL) {
                   CB &x = p->data;
                ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 10, L_RIGHT - X_VALUE - 1, 1);
                ClearArea(X_VALUE, 12, L_RIGHT - X_VALUE - 1, 1);
                
                gotoXY(X_VALUE, 4);  SetColor(10); cout << x.machuyenbay;
                gotoXY(X_VALUE, 6);  SetColor(10); cout << x.noiden;
                gotoXY(X_VALUE, 8);  SetColor(10); cout << x.sohieumaybay;
                gotoXY(X_VALUE, 10); SetColor(10); 
                cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
                     << setw(2) << x.thoigiandi.minute << " " 
                     << setw(2) << x.thoigiandi.day << "/" 
                     << setw(2) << x.thoigiandi.month << "/" 
                     << x.thoigiandi.year;
                cout << setfill(' ') << left;
                gotoXY(X_VALUE, 12); SetColor(10); cout << x.trang_thai;
                SetColor(7);
                } 
            }
        }

        else if (key == 4) {
            return -1;
        }

        else if (key == 3) {
        	PTR p = GetNode(First, highlight);
            if (p == NULL) continue;
            CB &x = p->data;
            if (x.trang_thai == 0 || x.trang_thai == 3 || x.trang_thai == 2 ) {
                gotoXY(2, 14); SetColor(12); cout << "LOI! KHONG THE HIEU CHINH TRANG THAI NAY!"; SetColor(7);
                _getch(); ClearArea(2, 14, 42, 1);
                continue;
            }

            gotoXY(2, 14); cout << "Sua trang thai CB: "; SetColor(10);
            cout << x.machuyenbay; SetColor(7);
            gotoXY(2, 15); SetColor(8); cout << "ENTER:OK  ESC:Huy"; SetColor(7);

            bool dongYSua = false;
            while (true) {
                int k = _getch();
                if (k == 13) { ClearArea(2, 14, 40, 2); dongYSua = true; break; }
                if (k == 27) { ClearArea(2, 14, 40, 2); dongYSua = false; break; }
            }
			if (dongYSua) {
            	ShowCur(true);
            	ClearArea(X_VALUE, 12, 2, 1);
                gotoXY(X_VALUE, 12);
                int ttMoi = -1;
            	while(true){
	                int c = _getch();
                    if (c == 27){
                        ttMoi = x.trang_thai;
                        break;
                    }
                    else if (c == 8)    // BACKSPACE
                    {
                        ttMoi = -1;
                        gotoXY(X_VALUE, 12);
                        cout << " ";
                        gotoXY(X_VALUE, 12);
                        continue;
                    }
                    else if (c == '0' || c == '2')
                    {
                    ttMoi = c - '0';
					gotoXY(X_VALUE, 12);
                    cout << ttMoi;
                    continue;
                    }
                    else if (c == 13)   // ENTER
                    {
                        if (ttMoi == -1)  continue;   // chua nh?p gì
                        if (ttMoi == 0 && p->data.tongsodaban > 0){
                            gotoXY(2,14);
                            SetColor(12);
                            cout << "Chuyen bay da co khach nen khong the huy!";
                            SetColor(7);

                            _getch();
                            ClearArea(2,14,42,1);

                            ttMoi = -1;

                            gotoXY(X_VALUE,12);
                            cout << " ";
                            gotoXY(X_VALUE,12);
                            continue;   // b?t nh?p l?i
                        }
	                    ShowCur(false);
	                    x.trang_thai = ttMoi;
	                    gotoXY(4, 14); SetColor(10);
                        cout << "Cap nhat trang thai thanh cong!";
                        GhiFileChuyenBay(First);
                        _getch(); 
                        ClearArea(4, 14, 31, 1);
                    }
               
                int dongY = 2 + (highlight - startIdx);
                gotoXY(R_LEFT+1, dongY);
                SetColor(116);
                cout << left << setfill(' ')
                     << setw(7)  << (highlight+1)
                     << setw(10)  << x.machuyenbay
                     << setw(18) << x.noiden;
                cout << right << setfill('0') << setw(2) << x.thoigiandi.hour << ":" 
                     << setw(2) << x.thoigiandi.minute << " " 
                     << setw(2) << x.thoigiandi.day << "/" 
                     << setw(2) << x.thoigiandi.month << "/" 
                     << setfill(' ') << left << setw(10) << x.thoigiandi.year;
                cout << TrangThaiStr(x.trang_thai);
                SetColor(7);
                ShowCur(false);
                break;
                }
                        
            }
        }
    }
}
void InCBConVe(PTR First) {
    system("cls");
    ShowCur(true);
    bool SaveOrNot = false;
    // ===================== Váº¼ KHUNG NHáº¬P =====================
    // Khung nháº­p liá»‡u bÃªn trÃ¡i
    int top = 2, bottom = 14, left = 2, right = 50;
    gotoXY(left, top);    cout << (char)201;
    gotoXY(right, top);   cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom);cout << (char)188;
    for (int i = left+1; i < right; i++) { gotoXY(i,top); cout<<(char)205; gotoXY(i,bottom); cout<<(char)205; }
    for (int i = top+1;  i < bottom; i++) { gotoXY(left,i); cout<<(char)186; gotoXY(right,i); cout<<(char)186; }

    SetColor(14);
    gotoXY(left+2, top+1); cout << " CHUYEN BAY CON VE THEO NGAY / NOI DEN";
    SetColor(7);
    gotoXY(left+2, top+3); cout << "Ngay  (dd): ";
    gotoXY(left+2, top+5); cout << "Thang (mm): ";
    gotoXY(left+2, top+7); cout << "Nam  (yyyy):";
    gotoXY(left+2, top+9); cout << "Noi den   : ";

    // ===================== NHáº¬P NGÃ€Y (chá»‰ sá»‘) =====================
    int d = 0, m = 0, y = 0;
    gotoXY(left+14, top+3);
    ConstraintForDateAndTime(d, SaveOrNot, 31);
    if (!SaveOrNot) return;
    gotoXY(left+14, top+5);
    ConstraintForDateAndTime(m, SaveOrNot, 12);
    gotoXY(left+14, top+7);
    ConstraintForDateAndTime(y, SaveOrNot, 2100);

    // ===================== NHáº¬P NÆ I Äáº¾N (chá»‰ chá»¯ + space) =====================
    string noiden = "";
    int noidenCount = 0;
    gotoXY(left+14, top+9);
    SetColor(8);
    cout << "______________________________"; // placeholder 30 kÃ½ tá»±
    SetColor(7);
    gotoXY(left+14, top+9);

    while (true) {
        int signal = _getch();
        if (signal == 224 || signal == 0) { _getch(); continue; } // bá» phÃ­m Ä‘áº·c biá»‡t

        // Chá»‰ nháº­n chá»¯ cÃ¡i a-z A-Z
        if ((65 <= signal && signal <= 90) || (97 <= signal && signal <= 122)) {
            if (noidenCount >= 30) continue; // giá»›i háº¡n 30 kÃ½ tá»±
            char c = (char)signal;
            // Viáº¿t hoa Ä‘áº§u tá»«
            if (noiden.empty() || noiden[noiden.length() - 1]== ' ') c = toupper(c);
            else c = tolower(c);
            noiden += c;
            SetColor(14); cout << c; SetColor(7);
            noidenCount++;
        }
        // Cho phÃ©p nháº­p dáº¥u cÃ¡ch, nhÆ°ng khÃ´ng cÃ¡ch Ä‘áº§u vÃ  khÃ´ng cÃ¡ch Ä‘Ã´i
        else if (signal == SPACE) {
            if (noiden.empty() || noiden[noiden.length() - 1] == ' ') continue;
            if (noidenCount >= 30) continue;
            noiden += ' ';
            cout << ' ';
            noidenCount++;
        }
        else if (signal == BACKSPACE && noidenCount > 0) {
            cout << "\b \b";
            noiden.erase(noiden.length()-1, 1);
            noidenCount--;
        }
        else if (signal == ENTER) {
            if (noidenCount == 0) continue; // khÃ´ng cho enter khi rá»—ng
            break;
        }
        else if (signal == ESC) { ShowCur(false); return; }
    }

    // Trim khoáº£ng tráº¯ng cuá»‘i
    while (!noiden.empty() && noiden[noiden.length() - 1] == ' ') noiden.erase(noiden.length() - 1, 1);

    // ===================== Váº¼ KHUNG Káº¾T QUáº¢ =====================
    int rtop = 16, rbottom = 30, rleft = 2, rright = 75;
    gotoXY(rleft, rtop);     cout << (char)201;
    gotoXY(rright, rtop);    cout << (char)187;
    gotoXY(rleft, rbottom);  cout << (char)200;
    gotoXY(rright, rbottom); cout << (char)188;
    for (int i = rleft+1; i < rright; i++) { gotoXY(i,rtop); cout<<(char)205; gotoXY(i,rbottom); cout<<(char)205; }
    for (int i = rtop+1;  i < rbottom; i++) { gotoXY(rleft,i); cout<<(char)186; gotoXY(rright,i); cout<<(char)186; }

    // TiÃªu Ä‘á» báº£ng káº¿t quáº£
    SetColor(14);
    gotoXY(rleft+2, rtop+1);
    cout << "CHUYEN BAY NGAY "
         << setfill('0') << setw(2) << d << "/"
         << setw(2) << m << "/" << y
         << setfill(' ') << "  DEN: " << noiden;
    gotoXY(rleft+2, rtop+2); cout << string(rright-rleft-3, '-');
    gotoXY(rleft+2, rtop+3);
    cout << std::left << setw(15) << "MA CB"
         << setw(12) << "GIO DI"
         << setw(14) << "SO VE TRONG";
    gotoXY(rleft+2, rtop+4); cout << string(rright-rleft-3, '-');
    SetColor(7);

    // ===================== IN Káº¾T QUáº¢ =====================
    bool found = false;
    int row = rtop + 5;
    for (PTR p = First; p != NULL; p = p->next) {
        CB& cb = p->data;
        int vetrang = cb.tongsove - cb.tongsodaban;

        if (cb.thoigiandi.day   == d &&
            cb.thoigiandi.month == m &&
            cb.thoigiandi.year  == y &&
            _stricmp(cb.noiden, noiden.c_str()) == 0 &&
            cb.trang_thai == 1 &&
            vetrang > 0)
        {
            gotoXY(rleft+2, row);
            SetColor(11);
            cout << std::left << setw(15) << cb.machuyenbay;
            SetColor(7);
            cout << setfill('0')
                 << setw(2) << cb.thoigiandi.hour << ":"
                 << setw(2) << cb.thoigiandi.minute
                 << setfill(' ');
            cout << setw(12) << "";
            SetColor(10);
            cout << vetrang << " ve";
            SetColor(7);
            row++;
            found = true;
            if (row >= rbottom - 1) break; // trÃ¡nh trÃ n khung
        }
    }

    if (!found) {
        gotoXY(rleft+2, rtop+5);
        SetColor(4);
        cout << "(Khong co chuyen bay phu hop)";
        SetColor(7);
    }

    // HÆ°á»›ng dáº«n thoÃ¡t
    gotoXY(rleft+2, rbottom+1);
    SetColor(8); cout << "Nhan phim bat ky de quay lai..."; SetColor(7);
    ShowCur(false);
    _getch();
}
void MenuChuyenBay(){
	DSMB LA;
    PTR First = NULL;
	DocFileMayBay(LA);
	DocFileChuyenBay(First, LA);
    int chon = 0;
    int menuCap = 1;
    int startIdx = 0;      // Vi tri bat dau cua trang hien tai
    int numberPerPage = 20;
	bool daClear = false;
    VeKhung();
    VeKhungHuongDan();
    while (true) {
        if (menuCap == 1){// menu chon them sua xoa
    	    if (!daClear){
                ClearArea(30 + 8, 7 + 3, 32, 10);
                daClear = true;
            }
            VeMenuChuyenBay(chon);
            int key = ReadKey();
            if(key == 1) chon--;
            else if(key == 2) chon++; // Xu?ng
            else if (key == 4) break;  // ESC ? Menu chính -> Thoát ra Menu t?ng
            else if (key == 3) {       // ENTER
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
                else if (chon == 3){
                	menuCap = 5;
                	daClear = false;
				}
            }
            if (chon < 0) chon = 3;
            if (chon > 3) chon = 0;
        }
        else if(menuCap == 2){
            if (!daClear) {
                system("cls");
                VeKhungNhapLieuCB();
                VeKhungDSCB();
                VeKhungHuongDanCB();
                Thongtinchuyenbaymottrang(First, startIdx);
				daClear =true;
            }
            gotoXY(4,2); cout << "NHAP THONG TIN";
            NhapLieuChuyenBay(First, LA, startIdx, numberPerPage);
            system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            daClear = false;
            chon = 0;
        }
        else if(menuCap == 3){
            if (!daClear) {
                system("cls");
				daClear =true;
            }
            SNgayGio(First, LA);
            _getch();
			system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            daClear = false;
            chon = 0;
        }
        else if(menuCap == 4){
            if (!daClear) {
                system("cls");
				daClear =true;
            }
            gotoXY(4,2); cout << "THAY DOI TRANG THAI";
            STrangThai(First, LA);
            _getch();
			system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            daClear = false;
            chon = 0;
        }
        else if(menuCap == 5){
            if (!daClear) {
                system("cls");
                InCBConVe(First);
                _getch();
			    system("cls");
                ShowCur(false);
                VeKhung();
                VeKhungHuongDan();
                menuCap = 1;
                daClear = false;
                chon = 0;
            }
        }
    }
}

