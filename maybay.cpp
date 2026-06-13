
#include <bits/stdc++.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
#include "bien.h"
#include "maybay.h"
#include "chuyenbay1.h"

int timvitrimaybay(DSMB LA, const char *Ma){
	for (int i = 0; i < LA.soluong;i++){
		if(strcmp(LA.DSMB[i] -> sohieumb, Ma)==0) return i;
	}
	return -1;
}
void Thongtin1maybay(MB *A, int position){
	int leftt = 40;
	int top = 2;
	int y = top + 2 + position;
	ClearArea(leftt + 5, y, 65, 1);
	gotoXY(leftt + 5, y); cout << left << setw(20) << A->sohieumb;
	gotoXY(leftt + 25, y); cout << setw(30) << A->loaimb;
	gotoXY(leftt + 55, y); cout << setw(15) << A->socho; // left can le trai
}
void Thongtinmaybaymottrang(DSMB &LA, int StartIndex){ 
	for(int i = 0; i < 20; i++){
        ClearArea(41, 4 + i, 70, 1);
}
	int NumberPerPage = 20;
    for (int i = 0; i + StartIndex < LA.soluong && i < NumberPerPage; i++) {
        Thongtin1maybay(LA.DSMB[i + StartIndex], i);
    }
    int totalPage = (LA.soluong - 1) / NumberPerPage + 1;
    int curPage = (StartIndex / NumberPerPage) + 1;
    gotoXY(75, 26); // T?a d? du?i dáy khung
    cout << " Trang " << curPage << " / " << totalPage; 
}
void DocFileMayBay(DSMB &LA){
    ifstream filein("DSMB.txt");
    if (!filein.is_open()) return;
    filein >> LA.soluong;
    filein.ignore();
    for(int j = 0; j < LA.soluong; j++){
    	LA.DSMB[j] = new MB;
    	filein >> LA.DSMB[j]->sohieumb;
        filein.ignore();
        filein.getline(LA.DSMB[j]->loaimb, 40);
        filein >> LA.DSMB[j]->socho;
    	filein.ignore(1000, '\n');
    	LA.DSMB[j]->Solanthuchienchuyenbay = 0;
	}
    filein.close();
}
void GhiFileMayBay(DSMB &LA){
	ofstream outFile;
    outFile.open("DSMB.txt", ios::out); 
    outFile << LA.soluong << endl;
    if (outFile.is_open()) {
        for (int i = 0; i < LA.soluong; i++) {
            outFile << LA.DSMB[i]->sohieumb << endl;;
            outFile << LA.DSMB[i]->loaimb << endl;
            outFile << LA.DSMB[i]->socho << endl;
        }
        outFile.close();
    }
}
void NhapLieuMayBay(DSMB &LA, int &StartIdx, int NumberPerPage){
	ShowCur(true);
	bool SaveOrNot = true;//luu lai hay chua
	bool IDExisted = false;// kiem tra xem can tim kiem co ton tai khong - > false la khong ton tai
	string ID;// so hieu
	string TypeAirplane;// loai may bay
	unsigned int nChair;// so cho ngoi
	int ordinal = 0;
	while(true){
		switch(ordinal){
			case 0:{
				ConstraintForLETTERAndNumber(ID, ordinal, SaveOrNot, 12);
				if(SaveOrNot){
				if(timvitrimaybay(LA, ID.c_str()) != -1){
					gotoXY(4, 10); SetColor(12);cout << "Loi! So hieu nay da ton tai!";
					SetColor(7);
					_getch();
					//ClearArea(4 + 12, 4, 10, 1);
					ClearArea(4, 10, 28, 1);
					gotoXY(4 + 12, ordinal + 4); cout << string(ID.length(),' ');
					ID = "";
					ordinal = 0;	
				}
				else ordinal++;
		        } else return;
				break;
			}
			case 1:{
		        ConstraintForOnlyLetter(TypeAirplane,ordinal,SaveOrNot,12);
				if(SaveOrNot)  ordinal++;
				else return;
				break;
			}
			case 2:{
				ConstraintForOnlyNumber(nChair,ordinal,SaveOrNot,12,400);
				if(SaveOrNot){
					if (nChair <= 20) {
                        gotoXY(4, 19); SetColor(12); 
						cout << "Chuyen bay phai co tren 20 cho ngoi!"; SetColor(7);
                        _getch();
                        ClearArea(4, 19, 45, 1); 
                        gotoXY(4 + 12, ordinal * 2 + 4); 
                        cout << "    "; 
                        nChair = 0;
                        continue;
                    }
					LA.DSMB[LA.soluong] = new MB;
					strcpy(LA.DSMB[LA.soluong ]->sohieumb, ID.c_str());
					strcpy(LA.DSMB[LA.soluong]->loaimb, TypeAirplane.c_str());
					LA.DSMB[LA.soluong]->socho = nChair;
					LA.DSMB[LA.soluong]->Solanthuchienchuyenbay = 0;
					LA.soluong++;	
			    }else return;
			    ordinal++;
			    break;
	        }
	        case 3:{
	        	gotoXY(4,10); SetColor(10);cout<<"Them thanh cong";SetColor(7);
	        	StartIdx = ((LA.soluong - 1) / NumberPerPage) * NumberPerPage;
	        	GhiFileMayBay(LA);
	        	Thongtinmaybaymottrang(LA,StartIdx);
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
void InDSMayBay(DSMB &LA, int highlight, int startIdx)
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
static int SMayBay(DSMB &LA)
{
    ClearConsole();
    ShowCur(false);
    VeKhungDon(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "THONG TIN"; SetColor(7);
    gotoXY(4, 4); cout << "SO HIEU      :";
    gotoXY(4, 6); cout << "LOAI MAY BAY :";
    gotoXY(4, 8); cout << "SO CHO       :";
    ClearArea(1,BOT-2,L_RIGHT-2,2);

	SetColor(8);

	gotoXY(2,BOT);
	cout<<"UP/DOWN : Di chuyen";

	gotoXY(2,BOT-1);
	cout<<"ENTER : Chon    ESC : Thoat";

	SetColor(7);
    VeKhungDon(TOP, BOT, R_LEFT, R_RIGHT);
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
    InDSMayBay(LA, highlight, startIdx);
    while (true) {
        // Hien thi o nhap
        ClearArea(18, 4, L_RIGHT-16, 1);
        gotoXY(18, 4); SetColor(10); cout << soHieu; SetColor(7);

        int key = ReadKey();

        if (key == 1) {      // len
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= PER_PAGE;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            InDSMayBay(LA, highlight, startIdx);
            ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                
            gotoXY(X_VALUE, 4); SetColor(10); cout << LA.DSMB[highlight]->sohieumb;
            gotoXY(X_VALUE, 6); SetColor(10);  cout << LA.DSMB[highlight]->loaimb;
            gotoXY(X_VALUE, 8); SetColor(10);  cout << LA.DSMB[highlight]->socho;
        }
        else if (key == 2) { // xuong
            if (highlight < LA.soluong - 1) {
                highlight++;
                if (highlight >= startIdx + PER_PAGE) startIdx += PER_PAGE;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            InDSMayBay(LA, highlight, startIdx);
            ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                
            gotoXY(X_VALUE, 4); SetColor(10); cout << LA.DSMB[highlight]->sohieumb;
            gotoXY(X_VALUE, 6); SetColor(10);  cout << LA.DSMB[highlight]->loaimb;
            gotoXY(X_VALUE, 8); SetColor(10);  cout << LA.DSMB[highlight]->socho;
        }
        else if (key == 4) { // ESC
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
            InDSMayBay(LA, highlight, startIdx);
            
            gotoXY(2, 10); cout << "Chon: "; SetColor(10);
            cout << LA.DSMB[vt]->sohieumb; SetColor(7);
            gotoXY(2, 12); SetColor(8); cout << "ENTER:OK  ESC:Nhap lai"; SetColor(7);
            bool dongYSua = false;
			while (true) {
                int k = _getch();
                if (k == 13) { ClearArea(2,10,30,4); dongYSua = true; break;}
                if (k == 27) { 
				    ClearArea(2,10,30,4); 
				    dongYSua = false;
					break; }
            }
            if(dongYSua){
                unsigned int nChair;
                int oldChair = LA.DSMB[highlight]->socho;
                bool SaveOrNot = false;
                int ordinal = 2;
                ShowCur(true); 
                ClearArea(X_VALUE, 8, 10, 1); 
                while(true){
                    ConstraintForOnlyNumber(nChair, ordinal, SaveOrNot, 14, 400);
                    if (SaveOrNot) {
                        if (nChair <= oldChair) {
                            gotoXY(2, 11); SetColor(12); 
                            cout << "Loi: So cho moi phai > " << oldChair; SetColor(7);
                            _getch();
                            ClearArea(2, 11, 30, 1);
                            gotoXY(4 + 14, ordinal*2 + 4); cout <<"   ";
                            nChair = 0;
                            continue;
                        }
                        else {
                            LA.DSMB[highlight]->socho = nChair;
                            GhiFileMayBay(LA); 
                            gotoXY(2, 11); SetColor(10); 
                            cout << "Cap nhat thanh cong!"; SetColor(7);
                            _getch();
                            ClearArea(2, 11, 30, 1);
                            break;
                        }
                    }
                }
            }        
			else {
                gotoXY(X_VALUE, 4); SetColor(10); cout << LA.DSMB[highlight]->sohieumb;
                gotoXY(X_VALUE, 6); SetColor(10); cout << LA.DSMB[highlight]->loaimb;
                gotoXY(X_VALUE, 8); SetColor(10); cout << LA.DSMB[highlight]->socho;
            }
                ShowCur(false); 
                InDSMayBay(LA, highlight, startIdx);
        }
    }
}

bool DKXoaMayBay(PTR First, const char* sohieu) {
    PTR p = First;
    while (p != NULL) {
        if (strcmp(p->data.sohieumaybay, sohieu) == 0) {
            return false;     
        }
        p = p->next;
    }
    return true; 
}
static int XMayBay(DSMB &LA, PTR &First)
{
    ClearConsole();
    ShowCur(false);
    VeKhungDon(TOP, BOT, L_LEFT, L_RIGHT);
    gotoXY(2, 1); SetColor(14); cout << "THONG TIN"; SetColor(7);
    gotoXY(4, 4); cout << "SO HIEU      :";
    gotoXY(4, 6); cout << "LOAI MAY BAY :";
    gotoXY(4, 8); cout << "SO CHO       :";
    ClearArea(1,BOT-2,L_RIGHT-2,2);

	SetColor(8);

	gotoXY(2,BOT-2);
	cout<<"UP/DOWN : Di chuyen";

	gotoXY(2,BOT-1);
	cout<<"ENTER : Chon    ESC : Thoat";

	SetColor(7);

    VeKhungDon(TOP, BOT, R_LEFT, R_RIGHT);
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
    InDSMayBay(LA, highlight, startIdx);
    while (true) {
        // Hien thi o nhap
        ClearArea(18, 4, L_RIGHT-16, 1);
        gotoXY(18, 4); SetColor(10); cout << soHieu; SetColor(7);

        int key = ReadKey();

        if (key == 1) {      // len
            if (highlight > 0) {
                highlight--;
                if (highlight < startIdx) startIdx -= PER_PAGE;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            InDSMayBay(LA, highlight, startIdx);
            ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                
            gotoXY(X_VALUE, 4); SetColor(10); cout << LA.DSMB[highlight]->sohieumb;
            gotoXY(X_VALUE, 6); SetColor(10);  cout << LA.DSMB[highlight]->loaimb;
            gotoXY(X_VALUE, 8); SetColor(10);  cout << LA.DSMB[highlight]->socho;
        }
        else if (key == 2) { // xuong
            if (highlight < LA.soluong - 1) {
                highlight++;
                if (highlight >= startIdx + PER_PAGE) startIdx += PER_PAGE;
            }
            soHieu = string(LA.DSMB[highlight]->sohieumb);
            InDSMayBay(LA, highlight, startIdx);
            ClearArea(X_VALUE, 4, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 6, L_RIGHT - X_VALUE - 1, 1);
            ClearArea(X_VALUE, 8, L_RIGHT - X_VALUE - 1, 1);
                
            gotoXY(X_VALUE, 4); SetColor(10); cout << LA.DSMB[highlight]->sohieumb;
            gotoXY(X_VALUE, 6); SetColor(10);  cout << LA.DSMB[highlight]->loaimb;
            gotoXY(X_VALUE, 8); SetColor(10);  cout << LA.DSMB[highlight]->socho;
        }
        else if (key == 4) { // ESC
            return -1;
        }
        else if (key == 3) { 
            if (soHieu.empty()) soHieu = string(LA.DSMB[highlight]->sohieumb);
                int vt = timvitrimaybay(LA, soHieu.c_str());
                if (vt == -1) {
                    gotoXY(2, 5); SetColor(12); cout << "Khong tim thay!    ";
                    SetColor(7); _getch(); ClearArea(2,5,22,1); soHieu = ""; continue;
                }
                if (!DKXoaMayBay(First, soHieu.c_str())) {
                    gotoXY(1, 18); SetColor(4);
                    cout << "Khong the xoa! May bay da co chuyen bay";
                    _getch();
                    ClearArea(1, 18, 39, 1);
                    continue;
                }
                highlight = vt;
                startIdx  = (vt / PER_PAGE) * PER_PAGE;
                InDSMayBay(LA, highlight, startIdx);
                gotoXY(2, 10); SetColor(12); cout << "Ban co chac chan muon xoa khong(y/n): "; SetColor(10);
                char confirm = _getch();
                if (confirm == 'y' || confirm == 'Y') {
                	// i là s? th? t? dòng tính t? d?u trang (0 d?n PER_PAGE - 1)
                    int i = highlight - startIdx; 
    
                    // Ðè m?t dòng tr?ng mang màu ch? bình thu?ng (SetColor 7) dè lên dòng highlight cu
                    gotoXY(R_LEFT + 1, 2 + i);
                    SetColor(7);
                    cout << left << setw(4) << "" << setw(12) << "" << setw(17) << "" << setw(5) << "";
            	    delete LA.DSMB[highlight];
                    for (int i = highlight; i < LA.soluong - 1; i++) {
                        LA.DSMB[i] = LA.DSMB[i + 1];
                    }
                    LA.soluong--; 
                    GhiFileMayBay(LA);
                    if (highlight >= LA.soluong && LA.soluong > 0) {
                        highlight = LA.soluong - 1;
                        startIdx = (highlight / PER_PAGE) * PER_PAGE;
                    } else if (LA.soluong == 0) {
                        highlight = -1;
                        startIdx = 0;
                    }
                    ClearArea(2, 10, 40, 10);
                    gotoXY(4, 19); SetColor(10);cout << "=> DA XOA THANH CONG!"; 
                    InDSMayBay(LA, highlight, startIdx);
                    _getch();
                    ClearArea(4, 19, 30, 1);
                }
                else {
                ClearArea(2, 10, 40, 10);
                gotoXY(4, 19); SetColor(10);cout << "=> DA HUY THAO TAC XOA.";
                _getch();
                ClearArea(2, 19, 40, 1);
            }
        }
    }
}

void MenuMayBay(){
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
            VeMenuMayBay(chon);
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
            }
            if (chon < 0) chon = 2;
            if (chon > 2) chon = 0;
        }
        else if(menuCap == 2){
            if (!daClear) {
                system("cls");
                VeKhungNhapLieu();
                VeKhungDSMB();
                Thongtinmaybaymottrang(LA, startIdx);
				daClear =true;
            }
            gotoXY(4,2); cout << "NHAP THONG TIN";
            NhapLieuMayBay(LA, startIdx, numberPerPage);
            system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            daClear = false;
            chon = 0;
        }  
		else if(menuCap == 3){
			ShowCur(true);
			SMayBay(LA);
			system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            chon = 1; 
		}
		else if(menuCap == 4){
			ShowCur(true);
			XMayBay(LA, First);
			system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            chon = 0;
        }
    }
}
