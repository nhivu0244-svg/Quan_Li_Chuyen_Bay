#include <bits/stdc++.h>
#include <string.h>
#include "maybay.h"
#include "chuyenbay1.h"
void ThongKeMayBay(DSMB& LA, PTR First) {
    system("cls");
    ShowCur(false);
 
    // ===================== TINH LAI LUOT BAY =====================
    // Reset ve 0 truoc, sau do dem lai tu danh sach chuyen bay
    // (dam bao chinh xac khi co chuyen bi huy sau khi lap)
    for (int i = 0; i < LA.soluong; i++){
    	if (LA.DSMB[i] == NULL) continue; 
        LA.DSMB[i]->Solanthuchienchuyenbay = 0;
    }
    for (PTR p = First; p != NULL; p = p->next) {
    	if (p->data.trang_thai == 0) continue;
        // Chi tinh chuyen bay co trang_thai != 0 (bo qua huy chuyen)
        if (p->data.trang_thai == 0) continue;
 
        int vt = timvitrimaybay(LA, p->data.sohieumaybay);
        if (vt != -1 && LA.DSMB[vt] != NULL)
            LA.DSMB[vt]->Solanthuchienchuyenbay++;
    }
 
    // ===================== SAP XEP GIAM DAN =====================
    // Mang chi so de sap xep, khong doi cho phan tu goc trong LA
    int idx[MAX_MB];
    for (int i = 0; i < LA.soluong; i++) idx[i] = i;
 
    for (int i = 0; i < LA.soluong - 1; i++)
        for (int j = 0; j < LA.soluong - 1 - i; j++)
            if (LA.DSMB[idx[j]]->Solanthuchienchuyenbay <
                LA.DSMB[idx[j + 1]]->Solanthuchienchuyenbay)
                swap(idx[j], idx[j + 1]);
 
    // ===================== VE KHUNG KET QUA =====================
    int rtop = 2, rbottom = 28, rleft = 2, rright = 100;
 
    gotoXY(rleft, rtop);     cout << (char)201;
    gotoXY(rright, rtop);    cout << (char)187;
    gotoXY(rleft, rbottom);  cout << (char)200;
    gotoXY(rright, rbottom); cout << (char)188;
    for (int i = rleft + 1; i < rright; i++) {
        gotoXY(i, rtop);    cout << (char)205;
        gotoXY(i, rbottom); cout << (char)205;
    }
    for (int i = rtop + 1; i < rbottom; i++) {
        gotoXY(rleft, i);  cout << (char)186;
        gotoXY(rright, i); cout << (char)186;
    }
 
    // ===================== TIEU DE =====================
    SetColor(14);
    gotoXY(rleft + 2, rtop + 1);
    cout << "THONG KE SO LUOT THUC HIEN CHUYEN BAY (GIAM DAN)";
    gotoXY(rleft + 2, rtop + 2);
    cout << string(rright - rleft - 3, '-');
 
    // Header cot
    gotoXY(rleft + 2, rtop + 3);
    cout << std::left
         << setw(6)  << "STT"
         << setw(20) << "SO HIEU MB"
         << setw(30) << "LOAI MAY BAY"
         << setw(10) << "SO CHO"
         << "SO LUOT THUC HIEN";
    gotoXY(rleft + 2, rtop + 4);
    cout << string(rright - rleft - 3, '-');
    SetColor(7);
 
    // ===================== IN DU LIEU =====================
    if (LA.soluong == 0) {
        gotoXY(rleft + 2, rtop + 5);
        SetColor(4);
        cout << "(Chua co may bay nao trong he thong)";
        SetColor(7);
    } else {
        int row     = rtop + 5;
        int tongthu = 0;
 
        for (int i = 0; i < LA.soluong; i++) {
            if (row >= rbottom - 2) break; // tranh tran khung
 
            int vi   = idx[i];
            int luot = LA.DSMB[vi]->Solanthuchienchuyenbay;
            tongthu += luot;
 
            gotoXY(rleft + 2, row);
 
            // STT
            SetColor(8);
            cout << std::left << setw(6) << (i + 1);
 
            // So hieu may bay
            SetColor(11);
            cout << setw(20) << LA.DSMB[vi]->sohieumb;
 
            // Loai may bay
            SetColor(7);
            cout << setw(30) << LA.DSMB[vi]->loaimb;
 
            // So cho
            cout << setw(10) << LA.DSMB[vi]->socho;
 
            // So luot - mau theo nguong
            if      (luot == 0)  SetColor(8);  // xam   - chua bay
            else if (luot <= 5)  SetColor(7);  // trang - it
            else if (luot <= 15) SetColor(14); // vang  - trung binh
            else                 SetColor(10); // xanh  - nhieu
 
            cout << luot << " luot";
            SetColor(7);
            row++;
        }
 
        // Dong tong ket
        if (row < rbottom - 1) {
            gotoXY(rleft + 2, row);
            cout << string(rright - rleft - 3, '-');
            gotoXY(rleft + 2, row + 1);
            SetColor(14);
            cout << "Tong so may bay: " << LA.soluong
                 << "   |   Tong luot bay (trang_thai != 0): " << tongthu;
            SetColor(7);
        }
    }
 
    // Huong dan thoat
    gotoXY(rleft + 2, rbottom + 1);
    SetColor(8);
    cout << "Nhan phim bat ky de quay lai...";
    SetColor(7);
 
    ShowCur(false);
    _getch();
}
