#pragma once
#include <bits/stdc++.h>
#include "DateTime1.h"
#include "maybay.h"
#include "Ve.h"
const int macb_MAX = 16;
const int noiden_MAX = 30;

struct chuyenbay{
	char machuyenbay[macb_MAX];
	Datetime thoigiandi;
	char noiden[noiden_MAX];
	char sohieumaybay[sohieumb_MAX];
	int tongsove;
	int tongsodaban;
	int trang_thai;//0: huy chuyen, 1: con ve, 2: het ve,3: hoan tat
	VE *dsve;
};
typedef struct chuyenbay CB;

struct nodeCB{
	CB data;
	nodeCB *next;
};
typedef nodeCB *PTR;
void khoitaochuyenbay(CB &A);
PTR timmachuyenbay(PTR First, const char *ma);
int timvtchuyenbay(PTR First, const char *ma);
bool KiemTraMayBayDangBan(PTR First, const char* sohieumb);
void Insert_Order_CB(PTR &First, CB x);
void Thongtin1chuyenbay(CB x, int position);
void Thongtinchuyenbaymottrang(PTR First, int StartIndex);
string TrangThaiStr(int tt);
void DSVCuaMotCB(CB &x);
void DocFileDSV(CB &x);
void GhiFileChuyenBay(PTR First);
bool ConHon1Tuan(Datetime dt);
void TuDongCapNhat(PTR pCB, PTR &First);
void DocFileChuyenBay(PTR &First, DSMB &LA);
void NhapLieuThoiGian(Datetime &DT);
void NhapLieuChuyenBay(PTR &First, DSMB &LA, int &StartIdx, int NumberPerPage);
void InDSChuyenBay(PTR First, int highlight, int startIdx);
static nodeCB* GetNode(PTR First, int idx);
static int CountNodes(PTR First);
static int SNgayGio(PTR First, DSMB LA);
static int STrangThai(PTR First, DSMB LA);
void InCBConVe(PTR First);
void MenuChuyenBay();

