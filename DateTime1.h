#pragma once
#include <bits/stdc++.h>
#include <string.h>
#include "giaodien.h"
#include "nhaplieu.h"

struct Datetime{
	int year;
	int month;
	int day;
	int hour;
	int minute;
};
void  InitDatetime(Datetime &dt);
void kiemtranamnhuan( Datetime &dt);
bool kiemtrahople( Datetime &dt);
void OutputDateTime(Datetime &dt);
bool CompareDate(Datetime dt1, Datetime dt2);

