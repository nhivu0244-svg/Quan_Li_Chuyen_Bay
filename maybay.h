#pragma once
#include <bits/stdc++.h>
const int sohieumb_MAX = 16;
const int loaimb_MAX = 41;
const int MAX_MB = 400;

struct nodeCB; 
typedef struct nodeCB* PTR;
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
void khoitaomaybay(DSMB &LA);
int timvitrimaybay(DSMB LA, const char *Ma);
void Thongtin1maybay(MB *A, int position);
void Thongtinmaybaymottrang(DSMB &LA, int StartIndex);
void DocFileMayBay(DSMB &LA);
void GhiFileMayBay(DSMB &LA);
void NhapLieuMayBay(DSMB &LA, int &StartIdx, int NumberPerPage);
void InDSMayBay(DSMB &LA, int highlight, int startIdx);
static int SMayBay(DSMB &LA);
void SuaMayBay();
bool DKXoaMayBay(PTR First, const char* sohieu);
static int XMayBay(DSMB &LA, PTR &First);
void XoaMayBay();
void MenuMayBay();

