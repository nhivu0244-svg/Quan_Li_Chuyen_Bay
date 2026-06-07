#include <bits/stdc++.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
#include "Datetime1.h"
#include "maybay.h"
#include "chuyenbay1.h"
#include "Ve.h"

void khoitaochuyenbay(CB &A){
	A.tongsodaban = 0;
	A.tongsove = 0;
	A.dsve = new VE[100];//cap phat mang dong (giaithich)
	A.trang_thai = 1;
}
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
bool KiemTraMayBayDangBan(PTR First, const char* sohieumb) {
    for (PTR p = First; p != NULL; p = p->next) {
        if (stricmp(p->data.sohieumaybay, sohieumb) == 0) {
            if (p->data.trang_thai == 1 || p->data.trang_thai == 2) {
                return true; 
            }
        }
    }
    return false; 
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
        ClearArea(41, 4 + i, 73, 1); 
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
                        gotoXY(4, 18); cout << "So Hieu MB khong ton tai!";
                        _getch();
                        ClearArea(4, 18, 30, 1);
                        gotoXY(4 + 21, 4); cout << string(sohieumb.length(), ' ');
                        sohieumb = ""; 
                    }
                    else if (KiemTraMayBayDangBan(First, sohieumb.c_str())) {
                        gotoXY(4, 19); SetColor(12);
                        cout << "May bay co lich bay chua hoan tat!"; SetColor(7);
                        _getch();
                        ClearArea(4, 19, 34, 1);
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
					gotoXY(4, 18); cout << "Loi! Ma CB nay da ton tai!";
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
	        			gotoXY(4,18); cout<< "Loi! Thoi gian o qua khu";
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
						gotoXY(4,18); cout<< "Phai them truoc it nhat 1 tuan";
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
					else ordinal++;
				break;
			}
	        case 4:{
	        	strcpy(x.machuyenbay, maCB.c_str());
                strcpy(x.sohieumaybay, sohieumb.c_str());
                strcpy(x.noiden, noiden.c_str());
                x.tongsodaban = 0; // M?c d?nh chua bán vé nào
                x.trang_thai = 1;
                int vtMB = timvitrimaybay(LA, x.sohieumaybay);
                if(vtMB != -1) {
                    x.tongsove = LA.DSMB[vtMB]->socho;
                }  
                DSVCuaMotCB(x); // cap phat va khoi tao mang ve
                Insert_Order_CB(First, x);
                GhiFileChuyenBay(First);
	        	int n = 0;
	        	for (PTR p = First; p != NULL; p = p->next) n++;
	        	StartIdx = ((n - 1) / NumberPerPage) * NumberPerPage;
	        	gotoXY(4,18); cout<<"Them chuyen bay thanh cong";
				Thongtinchuyenbaymottrang(First,StartIdx);
	        	while(true){
	        		int key = ReadKey();
	        		    if(key == 4) return;
                        if(key == 6){
                        	if (StartIdx + NumberPerPage < LA.soluong) {
                                StartIdx += NumberPerPage;
                                Thongtinmaybaymottrang(LA, StartIdx);
                            }
                        }
                        else if (key == 5) {
                            if (StartIdx >= NumberPerPage) {
                                StartIdx -= NumberPerPage;
                                Thongtinmaybaymottrang(LA, StartIdx);
                            }
                        }
                    }
                    break;
                }
			}
	    }
    }
void HieuChinhThoiGian(PTR &First, DSMB &LA,int StartIdx,int NumberPerPage){
	ShowCur(true);
	string maCB;
	int ordinal = 1;
	bool SaveOrNot = false;
	PTR p = NULL;
	while(true){
	    ConstraintForLETTERAndNumber(maCB,ordinal,SaveOrNot,21);
	    if(!SaveOrNot) return;
	    p = First;
        while (p != NULL) {
            if (strcmp(p->data.machuyenbay, maCB.c_str()) == 0) break;
            p = p->next;
        }
        if(p == NULL){
        	gotoXY(4, 18); cout << "Khong tim thay ma chuyen bay!";
            _getch();
            ClearArea(4, 18, 30, 1);
            gotoXY(4 + 21, ordinal*2 + 4); cout << string(maCB.length(),' ');
		    maCB = "";
		    continue;
        }
        if (p->data.trang_thai == 0 || p->data.trang_thai == 3) {
            gotoXY(4, 18); 
            if(p->data.trang_thai == 0) cout << "Chuyen bay da HUY, khong duoc sua!";
            else cout << "CB da HOAN TAT, khong duoc sua!";
            _getch();
            gotoXY(4 + 21, ordinal*2 + 4); cout << string(maCB.length(),' ');
		    maCB = ""; 
            ClearArea(4, 18, 32, 1); 
            continue;
        }
		gotoXY(4 + 21, 0*2 + 4); cout << p->data.sohieumaybay;
		gotoXY(4 + 21, 2*2 + 4); cout << p->data.noiden;
		gotoXY(4 + 21, 14); cout << p->data.trang_thai;
		gotoXY(4 + 10, 12); cout << p->data.thoigiandi.hour << ":"<<p->data.thoigiandi.minute << " " << p->data.thoigiandi.day << "/" << p->data.thoigiandi.month <<"/" << p->data.thoigiandi.year;
		gotoXY(4, 18); cout << "Nhan Enter de sua";
		_getch();
		ClearArea(4, 18, 20, 1);
		ClearArea(14, 12, 20,1);
        break;
	}
	    gotoXY(14, 12);
		NhapLieuThoiGian(p->data.thoigiandi);
			if(!kiemtrahople(p->data.thoigiandi)){
	        	gotoXY(4,18); cout<< "Loi! Thoi gian o qua khu";
	        	_getch();
	        	ClearArea(4, 18, 30, 1);
	        	ClearArea(14, 12, 17, 1);
	        	gotoXY(14, 12); cout << "                 ";
                p->data.thoigiandi.hour  = 0;
                p->data.thoigiandi.minute = 0;
                p->data.thoigiandi.day = 0;
                p->data.thoigiandi.month = 0;
                p->data.thoigiandi.year = 0;
			}
			else if(!ConHon1Tuan(p->data.thoigiandi)){
				gotoXY(4,18); cout<< "Phai sua truoc it nhat 1 tuan";
	        	_getch();
	        	ClearArea(4, 18, 34, 1);
	        	ClearArea(14, 12, 17, 1);
	        	gotoXY(14, 12); cout << "                 ";
	        	p->data.thoigiandi.hour = 0;
                p->data.thoigiandi.minute = 0;
                p->data.thoigiandi.day = 0;
                p->data.thoigiandi.month = 0;
                p->data.thoigiandi.year = 0;
			}
			else {
				gotoXY(4,18);
				cout << "Hieu chinh ngay gio thanh cong";
				GhiFileChuyenBay(First);
				Thongtinchuyenbaymottrang(First,StartIdx);
	        	while(true){
	        		int key = ReadKey();
	        		    if(key == 4) return;
                        if(key == 6){
                        	if (StartIdx + NumberPerPage < LA.soluong) {
                                StartIdx += NumberPerPage;
                                Thongtinmaybaymottrang(LA, StartIdx);
                            }
                        }
                        else if (key == 5) {
                            if (StartIdx >= NumberPerPage) {
                                StartIdx -= NumberPerPage;
                                Thongtinmaybaymottrang(LA, StartIdx);
                            }
                        }
                    }
			}
	}
void SuaTrangThai(PTR &First, DSMB &LA, int StartIdx, int NumberPerPage){
	ShowCur(true);
	string macb;
	int ordinal = 1; 
    bool SaveOrNot = false;
    PTR p = NULL;
    while(true){
    	ConstraintForLETTERAndNumber(macb, ordinal, SaveOrNot, 21);
    	p = timmachuyenbay(First, macb.c_str());
    	if( p == NULL){
    		gotoXY(4, 18); cout << "Khong tim thay ma chuyen bay!";
            _getch();
            ClearArea(4, 18, 30, 1);
            gotoXY(4 + 21, ordinal*2 + 4); cout << string(macb.length(),' ');
		    macb = "";
            continue;
		}
		if(p->data.trang_thai == 0 || p->data.trang_thai == 3){
			if(p->data.trang_thai == 0) cout <<"Chuyen bay da huy khong the sua";
			else { 
			    gotoXY(4, 18); cout << "Chuyen bay da hoan tat khong the";
                gotoXY(4, 19); cout << "sua";
			}
			_getch();
            ClearArea(4, 18, 32, 2);
            gotoXY(4 + 21, ordinal*2 + 4); cout << string(macb.length(),' ');
		    macb = "";
            continue;
		}
		gotoXY(4 + 21, 0*2 + 4); cout << p->data.sohieumaybay;
		gotoXY(4 + 21, 2*2 + 4); cout << p->data.noiden;
		gotoXY(4 + 10, 12); cout << p->data.thoigiandi.hour << ":"<<p->data.thoigiandi.minute << " " << p->data.thoigiandi.day << "/" << p->data.thoigiandi.month <<"/" << p->data.thoigiandi.year;
		gotoXY(4 + 21, 14); cout << p->data.trang_thai;
		gotoXY(4, 18); cout << "Nhan Enter de sua";
		_getch();
		ClearArea(4, 18, 20, 1);
		ClearArea(4 + 21, 14, 1,1);
        break;
	} 
	int ttMoi = p->data.trang_thai;
	while(true){
		gotoXY(4 + 21, 14);
		int c = _getch();
		if (c == 4) { // Phím ESC
            ClearArea(4, 18, 90, 1);
            gotoXY(4, 18); cout << "Da huy chinh sua trang thai!";
            _getch();
            ShowCur(false);
            return;
        }
        if ( c == 13) break;
        if ( c == '0' || c == '2'){
        	int soNhap = c - '0';
        	if (soNhap == 0 && p->data.tongsodaban > 0) {
                gotoXY(4, 18); SetColor(4);
                cout << "Chuyen bay da co khach dat ve";
				gotoXY(4, 19); cout << "KHONG DUOC phep HUY!"; SetColor(7);
                _getch();
                ClearArea(4, 18, 30, 2);
                continue;
            }
            ttMoi = soNhap;
            gotoXY(4 + 21, 14); cout <<ttMoi;
		}
	}
	ShowCur(false);
	p->data.trang_thai = ttMoi;
	gotoXY(4, 18);
    cout << "Cap nhat trang thai thanh cong!";
    
    GhiFileChuyenBay(First);
    Thongtinchuyenbaymottrang(First, StartIdx);
    while (true) {
        int key = ReadKey();
        if (key == 4) return; 
        
        if (key == 6) { 
            if (StartIdx + NumberPerPage < LA.soluong) {
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
	CB x; PTR First = NULL;
	khoitaochuyenbay(x);
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
                VeKhungNhapLieuCB();
                VeKhungDSCB();
                VeKhungHuongDanCB();
                Thongtinchuyenbaymottrang(First, startIdx);
				daClear =true;
            }
            gotoXY(4,2); cout << "HIEU CHINH NGAY GIO";
            HieuChinhThoiGian(First, LA, startIdx, numberPerPage);
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
                VeKhungNhapLieuCB();
                VeKhungDSCB();
                VeKhungHuongDanCB();
                Thongtinchuyenbaymottrang(First, startIdx);
				daClear =true;
            }
            gotoXY(4,2); cout << "THAY DOI TRANG THAI";
            SuaTrangThai(First, LA, startIdx, numberPerPage);
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
            }
        }
    }
}

