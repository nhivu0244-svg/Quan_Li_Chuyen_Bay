#include <bits/stdc++.h>
#include <string.h>
#include "maybay.h"
#include "chuyenbay1.h"
#include "hanh khach.h"

void Insert_node( NODEPTR &p, HK x){
	if( p==NULL){// vi tri hien tai la nut la
		p = new nodeHK;
		p -> data = x;// key la gia tri duy nhat de phan biet doi tuong nay voi doi tuong khac
		p -> left = NULL; p -> right = NULL;
	}
	if(p->data.CMND  < x.CMND)
	Insert_node (p -> right, x);
	else if(p->data.CMND > x.CMND) 
	Insert_node ( p -> left, x);
}
void DocFileHanhKhach(NODEPTR &root) {
    ifstream f("DSHK.txt");
    if (!f.is_open()) return;
    int n;
    f >> n; 
    for (int i = 0; i < n; i++) {
        HK hk;
        f >> hk.CMND; 
        f.ignore();   
        string tempHo, tempTen;
        getline(f, tempHo);
        strcpy(hk.Ho, tempHo.c_str());
        getline(f, tempTen);
        strcpy(hk.Ten, tempTen.c_str());
        f >> hk.Phai;
        f.ignore();
        Insert_node(root, hk);
    }
    f.close();
}
void DuyetCay(NODEPTR root, unsigned int Arr[], int &index) {
    if (root != NULL) {
        DuyetCay(root->left, Arr, index);
        Arr[index++] = root->data.CMND;
        DuyetCay(root->right, Arr, index);
    }
}
NODEPTR Timkiemhanhkhach(NODEPTR root, unsigned int cmndinput){
	if(root == NULL) return NULL;
	if(root->data.CMND == cmndinput) return root;
	if(root->data.CMND < cmndinput) Timkiemhanhkhach(root->right, cmndinput);
		else Timkiemhanhkhach(root->left, cmndinput);
}
int DemNode(NODEPTR root) {
    if (root == NULL) return 0;
    return 1 + DemNode(root->left) + DemNode(root->right);
}
void GhiFileHanhKhach(NODEPTR root) {
    ofstream f("DSHK.txt", ios::out);
    if (!f.is_open()) return;

    int n = DemNode(root);
    f << n << endl;

    unsigned int Arr[5000]; 
    int index = 0;
    DuyetCay(root, Arr, index);

    for (int i = 0; i < index; i++) {

        NODEPTR p = Timkiemhanhkhach(root, Arr[i]); 
        if (p != NULL) {
            f << p->data.CMND << endl;
            f << p->data.Ho << endl;
            f << p->data.Ten << endl;
            f << p->data.Phai << endl;
        }
    }
    f.close();
}
void NhapLieuHanhKhach(NODEPTR &root, int &StartIdx, int NumberPerPage){
	ShowCur(true);
	bool SaveOrNot = true;//luu lai hay chua
	string ho, ten;
	int Phai;
	unsigned int cmndtmp;
	int ordinal = 0;
	while(true){
		switch(ordinal){
			case 0:{
				ConstraintForOnlyNumber(cmndtmp,ordinal,SaveOrNot,15,4294967);
				if(SaveOrNot){
				    if(Timkiemhanhkhach(root, cmndtmp) != NULL){
					gotoXY(4, 10); cout << "Loi! CMND nay da ton tai!";
					_getch();
					//ClearArea(4 + 12, 4, 10, 1);
					ClearArea(4, 10, 30, 1);
					gotoXY(4 + 12, ordinal + 4); cout << "           ";
					cmndtmp = 0;
					ordinal = 0;	
				    }
				    else ordinal++;
			    } 
			    else return;
				break;
			}
			case 1:{
		        ConstraintsForLetterAndSpace(ho,ordinal,SaveOrNot,15);
				if(SaveOrNot)  ordinal++;
				break;
			}
			case 2:{
				ConstraintForOnlyLetter(ten,ordinal,SaveOrNot,15);
				if(SaveOrNot)  ordinal++;
				break;
	        case 3:{
	        	ConstraintForOnlyGender(Phai,ordinal,SaveOrNot,15);
				if(SaveOrNot){
					HK k;
					k.CMND = cmndtmp;
                    strcpy(k.Ho, ho.c_str());
                    strcpy(k.Ten, ten.c_str());
                    k.Phai = (Phai == 1); // true neu la 1 (Nam)

                    Insert_node(root, k); // Ham chen vao BST
                    
                    gotoXY(4, 10); cout << "Them hanh khach thanh cong!";
                    GhiFileHanhKhach(root); // Ghi lai file sau khi them
                    _getch();
                    return; // Xong thi thoat
				}
				break;
			}
	
			}
	    }
    }
}
void NhapLieuDatVe(PTR &First, NODEPTR &root, int &StartIdx, int &NumberPerPage){
	ShowCur(true);
    bool SaveOrNot = true;
    string maCB;
    unsigned int cmndtmp;
    int ordinal = 0;
    PTR p = NULL;
    while(true){
    	switch(ordinal){
    		case 0:{
    			ConstraintForLETTERAndNumber(maCB,ordinal,SaveOrNot,15);
    			if(SaveOrNot){
    				p = timmachuyenbay(First, maCB.c_str());
    				if (p == NULL){
    					gotoXY(4, 16); cout << "Ma chuyen bay khong ton tai";
                        _getch();
                        ClearArea(4, 16, 30, 1);
                        gotoXY(4 + 15, 4); cout << string(maCB.length(),' ');
                        maCB =""; 
                        ordinal = 0;
					}
					else if (p->data.trang_thai == 0 || p->data.trang_thai == 3) {
                        gotoXY(4, 16); cout << "Chuyen bay da huy hoac hoan tat";
                        _getch();
                        ClearArea(4, 16, 35, 1);
                        ordinal = 0;
                    }
                    else{
                    	gotoXY(2+ 5, 2 + 1); cout << "SO DO GHE CHUYEN BAY: " << p->data.machuyenbay;
                        //InSoDoGhe(p->data);
					    ordinal++;
					    }
				} else return;
				break;
			}
			case 1:{
				ConstraintForOnlyNumber(cmndtmp,ordinal,SaveOrNot,15,4294967);
				if(SaveOrNot){
					NODEPTR phk = Timkiemhanhkhach(root, cmndtmp);
					if(phk == NULL){
						gotoXY(4, 10); cout << "Hanh khach chua co thong tin!";
                        _getch();
                        ClearArea(4, 10, 35, 1);
                        gotoXY(4 + 15, 2 + 4); cout << "               ";
                        NhapLieuHanhKhach(root, StartIdx, NumberPerPage);
                        ordinal = 1;
                    }
					else{
						gotoXY(4 + 15, 2*2 + 4); cout << phk->data.Ho;
						gotoXY(4 + 15, 3*2 + 4); cout << phk->data.Ten;
						ordinal++;
					}
				}
				break;
			}
			case 2:
                int viTriGhe = -1;
                for (int i = 0; i < p->data.tongsove; i++) {
                    if (p->data.dsve[i].CMND == 0) {
                        viTriGhe = i;
                        break;
                    }
                }
                if (viTriGhe == -1) {
                    gotoXY(4, 10); cout << "Loi! Chuyen bay nay da het ve!";
                    _getch();
                    return;
                }

                // Hi?n s? gh? lên khung
                gotoXY(2 + 17, 2 + 10); cout << viTriGhe + 1;
                
                gotoXY(4, 10); cout << "Nhan ENTER de xac nhan dat ve";
                int key = _getch();
                if (key == 13) {
                    // Gán d? li?u vào m?ng vé c?a chuy?n bay
                    p->data.dsve[viTriGhe].CMND = cmndtmp;
                    p->data.dsve[viTriGhe].tt = true;
                    p->data.tongsodaban++;

                    // C?p nh?t tr?ng thái n?u c?n
                    if (p->data.tongsodaban == p->data.tongsove)
                        p->data.trang_thai = 2;

                    gotoXY(4, 10); cout << "Dat ve thanh cong!              ";
                    // Nhi nh? g?i hàm ghi file chuy?n bay nhé
                    // GhiFileChuyenBay(First); 
                    _getch();
                    return;
                } else {
                    ordinal = 1; // Quay l?i bu?c nh?p CMND
                    ClearArea(4, 10, 40, 1);
                }
                break;
            }
			
		}
	}
void MenuVe(){
	DSMB LA;
	CB x;
	PTR First = NULL;
	NODEPTR root = NULL;
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
            VeMenuVe(chon);
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
                VeKhungNhapLieuVe();
                VeKhungDSV();
                //Thongtinmaybaymottrang(LA, startIdx);
				daClear =true;
            }
            gotoXY(4,2); cout << "DAT VE";
            NhapLieuDatVe(First, root, startIdx, numberPerPage);
            system("cls");
            ShowCur(false);
            VeKhung();
            VeKhungHuongDan();
            menuCap = 1;
            daClear = false;
            chon = 0;
        }  
		/*else if(menuCap == 3){
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
        }*/  
    }
}
