#pragma once
#include <bits/stdc++.h>

struct ve{
	unsigned int CMND;
	int ghe_so;
	bool tt;
};
typedef struct ve VE;

struct chuyenbay; 
typedef struct chuyenbay CB;          
struct Datetime;  
struct nodeCB;  
struct nodeHK; 

typedef nodeCB* PTR;
typedef nodeHK* NODEPTR;

static int TimVeHanhKhach(CB &cb, unsigned int cmnd);
static int TimViTriTheoSoGhe(CB &cb, int soGheMuon);
void InSoDoGhe(CB &cb);
static void NhapNhanhHanhKhach(NODEPTR &root, unsigned int cmnd);
bool ConHon3Tieng(Datetime dt);
static PTR KiemTraHanhKhachCoVeChuaHoanThanh(PTR First, unsigned int cmnd, CB cbMoi);
static string ChuyenTrangThaiToStr(int tt);
static void VeKhungDonNoi(int top, int bot, int left, int right);
static void VeDSCBTrongForm(const vector<PTR> &dsCB, int startIdx, int highlight, int perPage);
static PTR ChonChuyenBay(PTR First, bool modeDat);
void DatVe(PTR &First, NODEPTR &root);
void HuyVe(PTR &First, NODEPTR &root);
void VeKhungDon(int t, int b, int l, int r);
static string TrangThaiStr(int tt);
static void VeSoDoGhe(CB &cb);
static void InDSMayBay_VT(DSMB &LA, int highlight, int startIdx);

//static void InDSMayBay(DSMB &LA, int highlight, int startIdx);
static void InDSChuyenBay(vector<PTR> &dsCB, int highlight, int startIdx);
static int BuocChonMayBay(DSMB &LA);
static PTR BuocChonChuyenBay(PTR First, const char *soHieuMB);
static void BuocXemVeTrong(CB &cb);
void InVeTrong(DSMB &LA, PTR First);
void MenuVe() ;


