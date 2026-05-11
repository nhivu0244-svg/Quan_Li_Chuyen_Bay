int main(){
	ShowCur(false);
    int chon = 0;
    int menuCap = 1;
	bool daClear = false; // ?? thêm dòng này
    VeKhung();
    VeKhungHuongDan();
while (true) {

    if (menuCap == 1)
        VeMenuChinh(chon);
    if (menuCap == 2){
    	if (!daClear) {
        ClearArea(30 + 8, 7 + 3, 30, 10);
        daClear = true;
    }
        VeMenuMayBay(chon);
}
    int key = ReadKey();

    if (key == 1) chon--;
    else if (key == 2) chon++;

    // ===== GI?I H?N =====
    if (menuCap == 1) {
        if (chon < 0) chon = 4;
        if (chon > 4) chon = 0;
    } else {
        if (chon < 0) chon = 3;
        if (chon > 3) chon = 0;
    }

    // ===== ENTER =====
    if (key == 3) {

        // ===== MENU CHÍNH =====
        if (menuCap == 1) {
            if (chon == 0) { // Máy bay
                menuCap = 2;
                chon = 0;
                daClear = false;
            }
            else if (chon == 4) {
                break;
            }
        }

        // ===== MENU MÁY BAY =====
        else if (menuCap == 2) {
			if (chon == 0) {
            }
            else if (chon == 1) {
                gotoXY(2 + 5, 6 - 2);
                cout << "Xoa (chua lam)";
            }
            else if (chon == 2) {
                gotoXY(2 + 5, 6 - 2);
                cout << "Sua (chua lam)";
            }
            else if (chon == 3) { // Quay l?i
                menuCap = 1;
                chon = 0;
            }
        }
    }

    // ===== ESC =====
    if (key == 4) {
        if (menuCap == 2) {
            menuCap = 1; // quay l?i menu chính
            chon = 0;
        } else {
            break;
        }
    }
}
}
