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
	if(root->data.CMND < cmndinput) return Timkiemhanhkhach(root->right, cmndinput);
		else return 
		
		Timkiemhanhkhach(root->left, cmndinput);
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
void Thongtin1hanhkhach(NODEPTR p, int soghe, int position) {
    if (p == NULL) return;

    int leftt = 10;
    int top = 2;
    int y = top + 7 + position; 

    cout << setfill(' ');
    ClearArea(leftt + 1, y, 98, 1); 

    string hoTenFull = string(p->data.Ho) + " " + string(p->data.Ten);

    gotoXY(leftt + 3,  y); cout << left << position + 1; // STT t?m th?i trong trang
    gotoXY(leftt + 12, y); cout << setw(12) << soghe;
    gotoXY(leftt + 25, y); cout << setw(12) << p->data.CMND;
    gotoXY(leftt + 45, y); cout << setw(35) << hoTenFull;
    gotoXY(leftt + 85, y); 
	if(p->data.Phai == 1) cout << setw(10) << "Nam";
	else cout << setw(10) << "Nu";
}
// Truy?n vào con tr? qu?n lý cây hành khách (root) và con tr? chuy?n bay dang ch?n (pChuyenBay)
void Thongtinhanhkhachmottrang(NODEPTR root, int StartIndex, PTR pChuyenBay) {
    int leftt = 10;
    int NumberPerPage = 16; // Khung ch?a t?i da 16 dòng hành khách (Dòng 9 -> 24)

    // 1. Xóa vùng d? li?u cu trong khung
    for(int i = 0; i < NumberPerPage; i++) {
        ClearArea(leftt + 1, 9 + i, 98, 1); 
    }

    // B?y l?i: N?u chuy?n bay không t?n t?i ho?c m?ng vé chua du?c c?p phát/không có vé nào
    if (pChuyenBay == NULL || pChuyenBay->data.dsve == NULL || pChuyenBay->data.tongsove <= 0) {
        gotoXY(leftt + 38, 14); cout << "[ DANH SACH DANG TRONG ]";
        gotoXY(leftt + 45, 26); cout << " Trang 0 / 0";
        return;
    }

    // 2. Gom t?t c? các vé ÐÃ BÁN (tt == true) t? m?ng c?p phát d?ng vào m?t danh sách t?m d? d? phân trang
    // Vì s? lu?ng vé t?i da b?ng t?ng s? gh? (tongsove), ta t?o m?t m?ng ch? s? t?m
    int* viTriVeDaBan = new int[pChuyenBay->data.tongsove];
    int tongSoKhachCB = 0; // Ð?m s? hành khách th?c t? c?a riêng chuy?n bay này

    for (int k = 0; k < pChuyenBay->data.tongsove; k++) {
        if (pChuyenBay->data.dsve[k].tt == true) { // N?u gh? này dã du?c d?t
            viTriVeDaBan[tongSoKhachCB] = k; // Luu l?i v? trí ch? s? i c?a m?ng dsve
            tongSoKhachCB++;
        }
    }

    // N?u chuy?n bay h?p l? nhung th?c t? chua có ai d?t vé
    if (tongSoKhachCB == 0) {
        gotoXY(leftt + 36, 14); cout << "[ CHUYEN BAY CHUA CO KHACH DAT VE ]";
        gotoXY(leftt + 45, 26); cout << " Trang 0 / 0";
        delete[] viTriVeDaBan; // Gi?i phóng m?ng t?m
        return;
    }

    // 3. In d? li?u c?a trang hi?n t?i d?a trên danh sách vé dã l?c
    int i = 0;
    while (i < NumberPerPage && (StartIndex + i) < tongSoKhachCB) {
        int idxVe = viTriVeDaBan[StartIndex + i]; // L?y ra v? trí vé th?c t? trên RAM
        
        unsigned int cmndKhach = pChuyenBay->data.dsve[idxVe].CMND;
        int soGheKhach = pChuyenBay->data.dsve[idxVe].ghe_so;

        // DÙNG HÀM S?N CÓ C?A NHI: Tìm node hành khách trên cây d? l?y thông tin cá nhân
        NODEPTR pKhach = Timkiemhanhkhach(root, cmndKhach);
        
        if (pKhach != NULL) {
            // G?i hàm in dòng khách, truy?n s? gh? l?y t? m?ng d?ng vào c?t 2
            Thongtin1hanhkhach(pKhach, soGheKhach, i); 
        }
        i++;
    }

    // 4. Tính toán và in s? trang du?i dáy khung theo t?ng s? khách ÐÃ Ð?T VÉ c?a chuy?n bay
    int totalPage = (tongSoKhachCB - 1) / NumberPerPage + 1;
    int curPage = (StartIndex / NumberPerPage) + 1;
    
    gotoXY(leftt + 45, 26); 
    cout << " Trang " << curPage << " / " << totalPage; 

    // 5. Gi?i phóng vùng nh? c?a m?ng t?m sau khi dùng xong d? tránh leak b? nh?
    delete[] viTriVeDaBan;
}
void NhapThongTinHK(NODEPTR& root) {
    // Ham nay nhap 1 hanh khach moi vao BST
    ShowCur(true);
    system("cls");
    int top = 2, bottom = 16, left = 5, right = 50;
    gotoXY(left, top); cout << (char)201;
    gotoXY(right, top); cout << (char)187;
    gotoXY(left, bottom); cout << (char)200;
    gotoXY(right, bottom); cout << (char)188;
    for (int i = left + 1; i < right; i++) { gotoXY(i, top); cout << (char)205; gotoXY(i, bottom); cout << (char)205; }
    for (int i = top + 1; i < bottom; i++) { gotoXY(left, i); cout << (char)186; gotoXY(right, i); cout << (char)186; }
    gotoXY(left + 2, top + 1); SetColor(14); cout << " NHAP THONG TIN HANH KHACH MOI "; SetColor(7);
    gotoXY(left + 2, top + 2); cout << "So CMND  : ";
    gotoXY(left + 2, top + 4); cout << "Ho       : ";
    gotoXY(left + 2, top + 6); cout << "Ten      : ";
    gotoXY(left + 2, top + 8); cout << "Phai(0=Nu, 1=Nam): ";

    bool SaveOrNot = false;
    unsigned int cmnd = 0;
    string ho, ten;
    int phai = 0;
    int ordinal = 0;

    while (true) {
        switch (ordinal) {
        case 0: {
            ConstraintForOnlyNumber(cmnd, ordinal, SaveOrNot, 14, 4294967295u);
            if (!SaveOrNot) return;
            if (Timkiemhanhkhach(root, cmnd)) {
                gotoXY(left + 2, top + 12); cout << "CMND nay da ton tai!";
                _getch(); ClearArea(left + 2, top + 12, 25, 1);
                ClearArea(left + 2 + 9, top + 2, 12, 1); cmnd = 0; ordinal = 0;
            } else ordinal++;
            break;
        }
        case 1: {
            ConstraintsForLetterAndSpace(ho, ordinal, SaveOrNot, 14);
            if (!SaveOrNot) return;
            ordinal++; break;
        }
        case 2: {
            ConstraintForOnlyLetter(ten, ordinal, SaveOrNot, 14);
            if (!SaveOrNot) return;
            ordinal++; break;
        }
        case 3: {
            ConstraintForOnlyGender(phai, ordinal, SaveOrNot, 21);
            if (!SaveOrNot) return;
            HK hk; hk.CMND = cmnd;
            strcpy(hk.Ho, ho.c_str()); strcpy(hk.Ten, ten.c_str());
            hk.Phai = (phai == 1);
            Insert_node(root, hk);
            GhiFileHanhKhach(root);
            gotoXY(left + 2, top + 12); cout << "Them hanh khach thanh cong!";
            _getch(); return;
        }
        }
    }
}
void InDSHanhKhach(PTR First, NODEPTR root){
	ShowCur(true);
	bool SaveOrNot = false;
	int ordinal = 0;
	string macb;
	int NumberPerPage = 16; // Khung dòng 9 -> 24 ch?a t?i da 16 dòng hành khách
    int StartIndex = 0;     // Ph?n t? b?t d?u c?a trang d?u tiên là v? trí s? 0
    int tongHK = DemNode(root);
	PTR p = NULL;
	while(true){
	    ConstraintForLETTERAndNumber(macb,ordinal,SaveOrNot,74);
		if(SaveOrNot){
			p = timmachuyenbay(First, macb.c_str());
			if(p != NULL){
				if(p->data.trang_thai == 0){
					gotoXY(11, 5); cout <<"Chuyen bay da bi huy";
					_getch();
					gotoXY(4 + 74, ordinal + 4); cout << string(macb.length(),' ');
		            macb = ""; 
                    ClearArea(11, 5, 30, 1);
                    continue;
				}
				break;
			}
			else{
				gotoXY(11, 5); cout <<"Khong tim thay ma chuyen bay";
				_getch();
				gotoXY(4 + 74, ordinal + 4); cout << string(macb.length(),' ');
		        macb = ""; 
                ClearArea(11, 5, 30, 1);
                continue; 
			}
		}
		else return;
	}
	ShowCur(false);
	gotoXY(10 + 30, 5); cout <<"Ngay gio khoi hanh:"<< p->data.thoigiandi.day <<"/"<< p->data.thoigiandi.month << "/"
	                         << p->data.thoigiandi.year <<" "<<p->data.thoigiandi.hour <<":"<< p->data.thoigiandi.minute;
    gotoXY (75 + 5, 5);
    cout<< "Noi den" << " "<< p->data.noiden;
    Thongtinhanhkhachmottrang(root, StartIndex, p);
    while(tongHK > 0){
    	int key = ReadKey();
	    if(key == 4) return;
        if(key == 6){
            if (StartIndex + NumberPerPage < tongHK) {
                StartIndex += NumberPerPage;
                Thongtinhanhkhachmottrang(root, StartIndex, p);
            }
        }
        else if (key == 5) {
            if (StartIndex >= NumberPerPage) {
                StartIndex -= NumberPerPage;
                Thongtinhanhkhachmottrang(root, StartIndex, p);
            }
        }
	}
    
}
void MenuHanhKhach(){
	ShowCur(false);
    NODEPTR root = NULL; 
    DocFileHanhKhach(root); // N?p s?n cây hành khách t? file lên RAM d? tra c?u h? tên
    DSMB LA;
    DocFileMayBay(LA);      // N?p danh sách máy bay d? l?y s? ch? (n?u c?n)
    PTR First = NULL;
    DocFileChuyenBay(First, LA); // N?p danh sách chuy?n bay d? ki?m tra mã nh?p vào
    int chon = 0;
    int menuCap = 1;
	bool daClear = false;
    VeKhung();
    VeKhungHuongDan();
    while (true) {
        if (menuCap == 1){// menu chon them sua xoa
    	    if (!daClear){
                ClearArea(30 + 8, 7 + 3, 32, 10);
                daClear = true;
            }
            VeMenuHanhKhach(chon);
            int key = ReadKey();
            if(key == 1) chon--;
            else if(key == 2) chon++; // Xu?ng
            else if (key == 4) break;  // ESC ? Menu chính -> Thoát ra Menu t?ng
            else if (key == 3) {       // ENTER
                if (chon == 0) {     
                    menuCap = 2;
                    daClear = false;
                } else if (chon == 1){
                	menuCap = 3;
                	daClear = false;
                }
            }    
            if (chon < 0) chon = 1;
            if (chon > 1) chon = 0;
        }
        else if(menuCap == 2){
            if (!daClear) {
                system("cls");
                NhapThongTinHK(root);
				daClear =true;
            }
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
                VeKhungDSHanhKhach();
                InDSHanhKhach(First, root);
				daClear =true;
            }
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

