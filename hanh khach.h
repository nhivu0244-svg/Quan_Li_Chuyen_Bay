#pragma once
#include <bits/stdc++.h>
const int ho_MAX = 20;
const int ten_MAX = 10;

struct hanhkhach{
	unsigned int CMND;
	char Ho[ho_MAX];
	char Ten[ten_MAX];
	bool Phai; //true:nam-false:nu
};
typedef struct hanhkhach HK;

struct nodeHK{
	HK data;
	struct nodeHK *left;
	struct nodeHK *right;
};
typedef nodeHK *NODEPTR;
void Insert_node( NODEPTR &p, HK x);
void DocFileHanhKhach(NODEPTR &root);
void DuyetCay(NODEPTR root, unsigned int Arr[], int &index);
NODEPTR Timkiemhanhkhach(NODEPTR root, unsigned int cmndinput);
int DemNode(NODEPTR root) ;
void GhiFileHanhKhach(NODEPTR root);
void NhapLieuHanhKhach(NODEPTR &root, int &StartIdx, int NumberPerPage);
void MenuVe();
