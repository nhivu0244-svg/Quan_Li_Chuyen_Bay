#include "giaodien.h"
#include "maybay.h"
#include "chuyenbay1.h"
#include "hanh khach.h"
#include "thongke.h"
int main() {
    ShowCur(false);
    
    // 1. Kh?i t?o và n?p d? li?u (C?c k? quan tr?ng)
    PTR First = NULL; 
    DSMB LA;
    NODEPTR rootHK = NULL; // Thêm cây hành khách n?a Nhi oi
    
    DocFileMayBay(LA);
    DocFileChuyenBay(First, LA); // Ph?i d?c file Chuy?n bay ? dây
    DocFileHanhKhach(rootHK);

    int chonChinh = 0;
    VeKhung();
    VeKhungHuongDan();

    while (true) {
        VeMenuChinh(chonChinh); 

        int key = ReadKey();
        if (key == 1) chonChinh--; // Mui tên lên
        if (key == 2) chonChinh++; // Mui tên xu?ng
        
        if (chonChinh < 0) chonChinh = 4; 
        if (chonChinh > 4) chonChinh = 0;

        if (key == 3) { // Nh?n ENTER
            switch (chonChinh) {
                case 0: MenuMayBay(); break; 
                case 1: MenuChuyenBay(); break; 
                case 2: MenuHanhKhach(); break; // Nhi b? sung thêm case này nè
                case 3: MenuVe(); break; 
                case 4: ThongKeMayBay(LA, First);
            }
            // Sau khi thoát module con, v? l?i khung chính d? xóa rác
            system("cls");
            VeKhung();
            VeKhungHuongDan();
        }
        if (key == 4) break; // ESC thoát
    }
    return 0;
}
