#include <bits/stdc++.h>
#include "DateTime1.h"

int Dayofmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void  InitDatetime(Datetime &dt){
	time_t baygio = time(0);// time_t co trong thu vien ctime, time(0) ham tra ve tong so giay tu lúc 00:00:00 ngày 01/01/1970 den gio
	tm *ltm = localtime(&baygio);// localtime chia tong so giay thanh tung phan: nam, thang, ngay,gio, phut, dua tren mui gio cua mk
	// tm la stuct co san trong ctime
	
	dt.year = 1900 + ltm -> tm_year;// tm_year chi luu khoang cach (so nam) tinh tu 1900
	dt.month = 1 + ltm -> tm_mon; // bat dau tu thang 0 nen phai cong 1
	dt.day = ltm -> tm_mday;
	dt.hour = ltm -> tm_hour;
	dt.minute = ltm -> tm_min;                          
}
void kiemtranamnhuan( Datetime &dt){
	if ((dt.year % 400 == 0)|| (dt.year % 4 == 0 && dt.year % 100 != 0))
	    Dayofmonth[2] = 29;
	else  Dayofmonth[2] = 28;
}
bool kiemtrahople( Datetime &dt){
	//1. KT thoi gian co ban
	if (dt.month < 1 || dt.month > 12) return false;
    kiemtranamnhuan(dt);
    if (dt.day < 1 || dt.day > Dayofmonth[dt.month]) return false;
    if (dt.hour < 0 || dt.hour > 23) return false;
    if (dt.minute < 0 || dt.minute > 59) return false;
	//2. So sanh thoi gian voi thuc tai
	Datetime dtNow;
	InitDatetime(dtNow);
	if(dt.year < dtNow.year) return false;
	if ((dt.year == dtNow.year) && (dt.month < dtNow.month))  return false;// thang nhap vao nho hon thang hien tai
	if (dt.year == dtNow.year && dt.month == dtNow.month && dt.day < dtNow.day)return false;// ngay nhap vao nho hon ngay hien tai
	if (dt.year == dtNow.year && dt.month == dtNow.month && dt.day == dtNow.day && dt.hour < dtNow.hour)return false;// gio nhap bi sai
	// so phut nhap vao bi sai
	if (dt.year == dtNow.year && dt.month == dtNow.month && dt.day == dtNow.day && dt.hour == dtNow.hour && dt.minute <= dtNow.minute)return false;
	return true;
}
void OutputDateTime(Datetime &dt)
{
	cout << dt.hour  << ":" << dt.minute << " " << dt.day << "/" << dt.month << "/" << dt.year;
}
bool CompareDate(Datetime dt1, Datetime dt2)// thong ke
{
	return dt1.day == dt2.day && dt2.month == dt1.month  && dt1.year == dt2.year;
}
