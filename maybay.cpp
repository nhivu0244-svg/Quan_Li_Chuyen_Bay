
#include <bits/stdc++.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"
#include "maybay.h"
#include "chuyenbay1.h"

void khoitaomaybay(DSMB &LA){
	LA.soluong = 0;
}
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
					gotoXY(4, 10); cout << "Loi! So hieu nay da ton tai!";
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
	        	gotoXY(4,10); cout<<"Them thanh cong";
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
void SuaMayBay(DSMB &LA, int vt, int &StartIdx, int NumberPerPage){
	string TypeAirplane;
	unsigned int nChair = LA.DSMB[vt]->socho;
	int oldChair = nChair;
	int ordinal = 1;
	bool SaveOrNot = false;
	while(true){
		switch(ordinal){
			case 1:{
				ConstraintForOnlyLetter(TypeAirplane,ordinal,SaveOrNot,12);
                if(SaveOrNot) ordinal++;
				break;
			}
			case 2:{
				ConstraintForOnlyNumber(nChair,ordinal,SaveOrNot,12,4294967);
				if(SaveOrNot){
					if(nChair <= oldChair){
						gotoXY(4,10); cout << "So cho moi phai lon hon"<< oldChair;
						_getch();
						ClearArea(4 + 12, 4 + 4, 10, 1);
					    ClearArea(4, 10, 28, 1);
					    nChair = 0;
					    ordinal = 2;
					}
					else {
						strcpy(LA.DSMB[vt]->loaimb, TypeAirplane.c_str());
					    LA.DSMB[vt]->socho = nChair;
					}
				}
				ordinal++;
				break;
			}
			case 3:{
	        	gotoXY(4,10); cout<<"Sua Thanh Cong";
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
void XoaMayBay(PTR First, DSMB &LA, int &StartIdx, int &NumberPerPage) {
    ShowCur(true);
    string sohieumb;
    int ordinal = 0;
    bool SaveOrNot = false;

    while (true) {
        // XÓA CH? CU TRÊN Ô NH?P (Dùng d? dài c? d?nh cho ch?c)
        gotoXY(4 + 12, 4); cout << "            "; 
        sohieumb = ""; // Reset chu?i
        
        gotoXY(4 + 12, 4);
        ConstraintForLETTERAndNumber(sohieumb, ordinal, SaveOrNot, 12);
        
        // N?u nh?n ESC d? thoát
        if (!SaveOrNot) return;

        // 1. CH? C?N DÙNG HÀM NÀY LÀ Ð?
        int vt = timvitrimaybay(LA, (char*)sohieumb.c_str());

        if (vt == -1) {
            gotoXY(4, 18); cout << "Khong tim thay so hieu may bay!";
            _getch();
            ClearArea(4, 18, 40, 1);
            continue; // Quay l?i d?u vòng while d? nh?p l?i
        }

        // 2. KI?M TRA ÐI?U KI?N XÓA
        if (!DKXoaMayBay(First, (char*)sohieumb.c_str())) {
            gotoXY(1, 18); 
            cout << "Khong the xoa! May bay da co chuyen bay";
            _getch();
            ClearArea(1, 18, 39, 1);
            continue;
        }

        // 3. HI?N THÔNG TIN Ð? XÁC NH?N
        gotoXY(4 + 12, 6); cout << LA.DSMB[vt]->loaimb;
        gotoXY(4 + 12, 8); cout << LA.DSMB[vt]->socho;
        
        gotoXY(4, 18); cout << "Ban co chac chan muon xoa? (Y/N): ";
        char confirm = _getch();

        if (confirm == 'y' || confirm == 'Y') {
            delete LA.DSMB[vt];
            for (int i = vt; i < LA.soluong - 1; i++) {
                LA.DSMB[i] = LA.DSMB[i + 1];
            }
            LA.soluong--;
            
            GhiFileMayBay(LA);
            gotoXY(4, 19); cout << "=> DA XOA THANH CONG!";
            
            // C?P NH?T L?I DANH SÁCH HI?N TH?
            Thongtinmaybaymottrang(LA, StartIdx);
            
            _getch(); // Ð?i xem thông báo thành công
            return; // Xóa xong thì thoát ra
        } 
        else {
            gotoXY(4, 19); cout << "=> DA HUY THAO TAC XOA.";
            _getch();
            ClearArea(4, 18, 45, 2);
            // Xóa thông tin máy bay dã hi?n ra d? nh?p mã khác
            gotoXY(4 + 12, 6); cout << "                    ";
            gotoXY(4 + 12, 8); cout << "          ";
        }
    }
}

void MenuMayBay(){
	DSMB LA;
	PTR First = NULL;
	khoitaomaybay(LA);
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
			if(!daClear){
				system("cls");
                VeKhungNhapLieu();
                VeKhungDSMB();
                Thongtinmaybaymottrang(LA, startIdx);
				daClear =true;
			}
			while(true){
		        gotoXY(4, 2); cout << " SUA MAY BAY";
			    string sohieu;
		    	bool tmpMove = false; bool tmpSave = false; int ordinal = 0;
		    	ConstraintForLETTERAndNumber(sohieu,ordinal,tmpSave,12);
                if(tmpSave){
            	    int vt = timvitrimaybay(LA, sohieu.c_str());
            	    if( vt != -1) {
            		    SuaMayBay(LA, vt, startIdx, numberPerPage);
            		    break;
				    }
				    else{
					    gotoXY(4, 10); cout << "Khong tim thay so hieu";
            		    _getch();
            		    ClearArea(4, 10, 28, 1);
            		    gotoXY(4 + 12, 4); cout << string(sohieu.length(),' '); 
            		    sohieu ="";
				    }
			    }
			    else {
				    break;
			    }
		    }
		    system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            daClear = false;
            chon = 1; 
		}
		else if(menuCap == 4){
            if (!daClear) {
                system("cls");
                VeKhungNhapLieu();
                VeKhungDSMB();
                Thongtinmaybaymottrang(LA, startIdx);
				daClear =true;
            }
            gotoXY(4,2); cout << "XOA MAY BAY";
            XoaMayBay(First, LA, startIdx, numberPerPage);
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
