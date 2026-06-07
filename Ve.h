#pragma once
#include <bits/stdc++.h>
const int MAX_VE = 200;
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

//static bool NhapChuoiTaiXY(string &result, int x, int y, int maxLen);
bool NhapSoTaiXY(unsigned int &result, int x, int y, unsigned int giaoHan);
static int TimVeHanhKhach(CB &cb, unsigned int cmnd);
static int TimViTriTheoSoGhe(CB &cb, int soGheMuon);
void InSoDoGhe(CB &cb);
static void NhapNhanhHanhKhach(NODEPTR &root, unsigned int cmnd);
bool ConHon3Tieng(Datetime dt);
void DatVe(PTR &First, NODEPTR &root);
void HuyVe(PTR &First, NODEPTR &root) ;
void MenuVe() ;
void InVeTrong();


