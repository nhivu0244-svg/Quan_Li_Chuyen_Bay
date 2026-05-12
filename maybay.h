#pragma once
#include <bits/stdc++.h>
const int sohieumb_MAX = 16;
const int loaimb_MAX = 41;
const int MAX_MB = 400;

using namespace std;
struct maybay{
	char sohieumb[sohieumb_MAX];
	char loaimb[loaimb_MAX];
	int socho;
	int Solanthuchienchuyenbay;
};
typedef struct maybay MB;

struct danhsachmaybay{
    int soluong;
    MB *DSMB[MAX_MB];
};
typedef struct danhsachmaybay DSMB;
void khoitaomaybay(danhsachmaybay &LA);
int timvitrimaybay(danhsachmaybay LA, const char *Ma);
bool kiemtraxoamaybay(DSMB &LA, int vt);
void Thongtin1maybay(MB *A, int position);
void Thongtinmaybaymottrang(DSMB &LA, int StartIndex);
void DocFileMayBay(DSMB &LA);
void GhiFileMayBay(DSMB &LA);
void NhapLieuMayBay(DSMB &LA, int &StartIdx, int NumberPerPage);
void SuaMayBay(DSMB &LA, int vt, int &StartIdx, int NumberPerPage);
void MenuMayBay();

