#include <bits/stdc++.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
#include "Datetime1.h"
#include "Ve.h"
#include "maybay.h"
#include "chuyenbay1.h"

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
int timsanbay(PTR First, char*sanbayden){
	int index = 0;
	for(PTR p = First; p != NULL; p = p->next){
		if(stricmp(p->data.noiden, sanbayden) == 0) return index;
		index++;
	}
	return -1;
}

void Insert_Order_CB(PTR &First, CB x){
	string ma;
	if (timvtchuyenbay(First, ma.c_str()) != -1) {
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
    //cout << right << setw(5) << x.tongsodaban;
    cout << right << setw(5) << x.trang_thai;
}
void Thongtinchuyenbaymottrang(PTR First, int StartIndex) { 
    // 1. Xóa vùng d? li?u cu (Xóa 20 dòng trong khung)
    for(int i = 0; i < 20; i++) {
        ClearArea(41, 4 + i, 70, 1); 
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
void DSVCuaMotCB(CB &x){// Doc File cua mot chuyen bay
	x.dsve = new VE[x.tongsove];
    for (int i = 0; i < x.tongsove; i++) {
        x.dsve[i].ghe_so = i + 1;
        x.dsve[i].CMND = 0;
        x.dsve[i].tt = false;
    }
	ifstream file;
	char filenameve[100] = "DSV\\";
	strcat(filenameve, x.machuyenbay);
	strcat(filenameve, ".txt");
	file.open(filenameve, ios_base::in);
	if (file.is_open()) {
		file >> x.tongsodaban;
		string tmp;
		getline(file, tmp);
		if(x.tongsodaban > 0){
		    x.dsve = new VE[x.tongsodaban];
		    for(int i = 0; i < x.tongsodaban; i++){
			    file >> x.dsve[i].CMND;
			    file >> x.dsve[i].ghe_so; 
		    }
	    }
	}
	file.close();
}

void DocFileChuyenBay(PTR &First, DSMB &LA) {
    ifstream filein("DSCB.txt", ios::in);
    if (!filein.is_open()) return;
    // Reset thong ke may bay
    for(int i = 0; i < LA.soluong; i++) {
        LA.DSMB[i]->Solanthuchienchuyenbay = 0;
    }
    int nFlight;
    if (!(filein >> nFlight)) return; 
    filein.ignore(1000, '\n'); // Xoa sach dong dau tien
    for(int j = 0; j < nFlight; j++) {
        CB x;
        // Khong can goi khoitaochuyenbay(x) o day vi DSVCuaMotCB se cap phat
        x.dsve = NULL; 
        filein.getline(x.machuyenbay, 15);
        filein.getline(x.noiden, 30);
        filein.getline(x.sohieumaybay, 15);

        filein >> x.thoigiandi.hour; 
		filein >> x.thoigiandi.minute; 
        filein >> x.thoigiandi.day; 
		filein >> x.thoigiandi.month; 
		filein >> x.thoigiandi.year;
		filein >> x.tongsodaban;
        filein >> x.trang_thai;
        filein.ignore(1000, '\n');
        int vt = timvitrimaybay(LA, x.sohieumaybay);
        if (vt != -1) {
            x.tongsove = LA.DSMB[vt]->socho;
            LA.DSMB[vt]->Solanthuchienchuyenbay++; // Th?ng kê lu?t bay
        } else {
            x.tongsove = 0;
        }
        DSVCuaMotCB(x); // Ham nay se cap phat x.dsve theo dung so ghe
        Insert_Order_CB(First, x);
    }
    filein.close();
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
    }
    fileout.close();
}
void NhapLieuThoiGian(Datetime &DT, int ordinal)
{
	int DTordinal = 0;// vi tri khoi dau cho viec nhap
	bool SaveOrNot = false;
	while( true )
	{
		switch(DTordinal)
		{
		case 0:
			ConstraintForDateAndTime(DT.hour,DTordinal,SaveOrNot,23);
			cout << ":";
			DTordinal++;
			break;
		case 1:
			ConstraintForDateAndTime(DT.minute,DTordinal,SaveOrNot,59);
			cout << " ";
			DTordinal++;
			break;
		case 2:
			ConstraintForDateAndTime(DT.day,DTordinal,SaveOrNot,31);
			cout << "/";
			DTordinal++;
			break;
		case 3:
			ConstraintForDateAndTime(DT.month,DTordinal,SaveOrNot,13);
			cout << "/";
			DTordinal++;
			break;
		case 4:
			ConstraintForDateAndTime(DT.year,DTordinal,SaveOrNot,2100);
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
				ConstraintForLETTERAndNumber(maCB, ordinal, SaveOrNot, 21);
				if(SaveOrNot){
				if(timvtchuyenbay(First, maCB.c_str()) != -1){
					gotoXY(4, 18); cout << "Loi! Ma CB nay da ton tai!";
					_getch();
					//ClearArea(4 + 12, 4, 10, 1);
					ClearArea(4, 18, 28, 1);
					gotoXY(4 + 21, ordinal + 4); cout << string(maCB.length(),' ');
					maCB = "";
					ordinal = 0;	
				}
				else ordinal++;
			}
				break;
			}
			case 1: {
                ConstraintForLETTERAndNumber(sohieumb, ordinal, SaveOrNot, 21);
                if (SaveOrNot) {
                    int vt = -1;
                    for (int i = 0; i < LA.soluong; i++) {
                        if (stricmp(LA.DSMB[i]->sohieumb, sohieumb.c_str()) == 0) {
                            vt = i;
                            break;
                        }
                    }
                    if (vt == -1) { 
                        gotoXY(4, 18); cout << "So Hieu MB khong ton tai!";
                        _getch();
                        ClearArea(4, 18, 30, 1);
                        gotoXY(4 + 21, 6); cout << string(sohieumb.length(), ' ');
                        sohieumb = ""; 
                    } else {
                        ordinal++; 
                    }
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
	        	NhapLieuThoiGian(x.thoigiandi, ordinal);
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
	int ordinal = 0;
	bool SaveOrNot = false;
	PTR p = NULL;
	while(true){
	    ConstraintForLETTERAndNumber(maCB,ordinal,SaveOrNot,21);
	    p = First;
        while (p != NULL) {
            if (strcmp(p->data.machuyenbay, maCB.c_str()) == 0) break;
            p = p->next;
        }
        if(p == NULL){
        	gotoXY(4, 18); cout << "Khong tim thay ma chuyen bay!";
            _getch();
        	ClearArea(4, 18, 30, 1);
        	continue;
        }
        if (p->data.trang_thai == 0 || p->data.trang_thai == 3) {
            gotoXY(4, 18); 
            if(p->data.trang_thai == 0) cout << "Chuyen bay da HUY, khong duoc sua!";
            else cout << "CB da HOAN TAT, khong duoc sua!";
            _getch();
            gotoXY(4 + 21, ordinal + 4); cout << string(maCB.length(),' ');
		    maCB = ""; 
            ClearArea(4, 18, 32, 1);
            continue; 
        }
		ClearArea(4, 4 + 18, 20, 1);// da vuot qua het thi xoa thong bao
        break;
	}
		gotoXY(4 + 21, 1*2 + 4); cout << p->data.sohieumaybay;
		gotoXY(4 + 21, 2*2 + 4); cout << p->data.noiden;
		gotoXY(4 + 21, 14); cout << p->data.trang_thai;
		gotoXY(4 + 10, 12);
		NhapLieuThoiGian(p->data.thoigiandi, 0);
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
                } else if (chon == 2) {// Xoa
                }
            }
            if (chon < 0) chon = 2;
            if (chon > 2) chon = 0;
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
    }
}
int TimSoChoMayBay(DSMB &LA, char* soHieu) {
    for (int i = 0; i < LA.soluong; i++) {
        if (strcmp(LA.DSMB[i]->sohieumb, soHieu) == 0) {
            return LA.DSMB[i]->socho;
        }
    }
    return 0; // Không tìm th?y
}
