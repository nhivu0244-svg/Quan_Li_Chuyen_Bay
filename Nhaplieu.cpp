#include <bits/stdc++.h>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <cctype>
#include "giaodien.h"
//key
#define SPACE  32
#define ESC  27
#define ENTER 13
#define BACKSPACE 8
#define KEY_UP 72// 0
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F10 68
#define PAGE_DOWN 81// 224
#define PAGE_UP 73
#define INSERT 82
#define DEL 83
#define HOME 71
#define END 79// 224


using namespace std;

void ConstraintForLetterAndNumber(string &result,bool &MoveOrNot,bool &SaveOrNot,int distance)
{
	int lenght = (int)result.length();
	cout << result;
	int count = lenght;
	while(true)
	{
		while( _kbhit() )
		{
			int signal = _getch();
			if( signal != 224 && signal != BACKSPACE && signal != 0)
			{
				/*	--------tu A den Z -----				------Tu a den z -------				-----Tu 0 den 9 -----*/
				if( ( 65 <= signal && signal <= 90 ) || ( 97 <= signal && signal <= 122 ) || ( 48 <= signal && signal <= 57 ) )
				{
						count++;// cap nhat bien count 
						cout << (char)signal;// hien thi no tren man hinh nhap thong tin
						result += (char)signal;// cap nhat ket qua vao RESULT
					
				}
				else if( signal == ENTER)
				{
					SaveOrNot = true;// Enter cung tuong duong voi xuong dong 
					return;
				}
				
				else if(signal == ESC){
					SaveOrNot = false;
					return;
				}
			}
			else if( signal == BACKSPACE && count > 0)
			{
				/* xoa ki tu khoang trang - \b dai dien cho 
				khoang trang dung tren ban phim - xoa khoang trang vua nhap*/
				cout << "\b" << " " << "\b";
				/* xoa di 1 ki tu o vi tri cuoi cung - cap nhat lai 1 vi tri*/
				result.erase(result.length() - 1 , 1);
				/* vi day la BACKSPACE nen khong tinh gia tri nay vao bien count*/
				count--;
			}
		}
	}
}
void ConstraintForLETTERAndNumber(string &result,int &ordinal,bool &SaveOrNot,int distance)
{
	int lenght = (int)result.length();
	gotoXY(4 + distance, ordinal*2 + 4);
	cout << result;
	int count = lenght;
	while(true)
	{
		while( _kbhit() )
		{
			int signal = _getch();
			if( signal == 224 || signal == 0){
				_getch();
				
				continue;
			}
				/*	--------tu A den Z -----				------Tu a den z -------				-----Tu 0 den 9 -----*/
			if( ( 65 <= signal && signal <= 90 ) || ( 97 <= signal && signal <= 122 ) || ( 48 <= signal && signal <= 57 ) )
			{
					char tmp = toupper(char(signal)); 
					cout << tmp;// hien thi no tren man hinh nhap thong tin
					result += tmp;// cap nhat ket qua vao RESULT
			 		count++;// cap nhat bien count
			}
			else if( signal == ENTER){
				if(count > 0){
					SaveOrNot = true;
				    return;					    
					}
				}
			else if(signal == ESC){
				SaveOrNot = false;
				return;
			}
			else if( signal == BACKSPACE && count > 0)
			{
				cout << "\b" << " " << "\b";
				result.erase(result.length() - 1 , 1);
				count--;
			}
		}
	}
}
void ConstraintsForLetterAndSpace(string &result,int &ordinal,bool &SaveOrNot,int distance)
{
	int count = result.length();
	cout << result;
	gotoXY(4 + distance, ordinal*2 + 4);
	bool Spaced = false; // false nghia la chua space
	int signal;
	while( true )
	{
		while( _kbhit() )
		{
			signal = _getch();
			if( signal == 224 || signal == 0){
				_getch();
				continue;
			}
			if ((65 <= signal && signal <= 90) || (97 <= signal && signal <= 122))
            {
                char c = (char)signal;
                if (result.length() == 0 || result[result.length() - 1] == ' ') {
                    c = toupper(c);
                }
                else {
                c = tolower(c);
                } 
            cout << c;
            result += c;
            count++;
            }
			else if ( signal == SPACE){
				if ( result.length() == 0 ) continue;
				if (result[result.length() - 1] == ' ') continue;
				cout <<" ";
				result+=' ';
				count++;
			}
			else if( signal == ENTER)
			{
				if(count == 0) continue;
				SaveOrNot = true; 
				return;
			}	
			else if(signal == ESC){
				SaveOrNot = false;
				return;
			}
			else if( signal == BACKSPACE && count > 0)
			{
				cout << "\b" << " " << "\b";
				result.erase(result.length() - 1 , 1);
				count--;
			}
		}//end while( kbhit() )
	}// end while(true)
}
void ConstraintForOnlyLetter(string &result,int &ordinal,bool &SaveOrNot,int distance)
{
	int lenght = (int)result.length();
	gotoXY(4 + distance, ordinal*2 + 4);
	int count = lenght;
	cout << result;
	while(true)
	{
		while( _kbhit() )
		{
			int signal = _getch();
			if ( signal == 224 || signal == 0)
			{
				_getch();
				continue;
		    }
				/*   --- tu A den Z ---						---- tu a den z ---*/ 
			if( ( 65 <= signal && signal <= 90 ) || ( 97 <= signal && signal <= 122 ) )
			{
					char tmp;
					if(count == 0) tmp = toupper((char)signal);
					else tmp = (char)signal;
					result += tmp;
					cout<< tmp;
					count++;
			}
			else if( signal == ENTER)
			{
				if(count == 0) continue;
				SaveOrNot = true; 
				return;
			}	
			else if(signal == ESC){
				SaveOrNot = false;
				return;
			}
			else if( signal == BACKSPACE && count > 0)
			{
				cout << "\b" << " " << "\b";
				result.erase(result.length() - 1 , 1);
				count--;
			}
		}
	}
}
void ConstraintForOnlyNumber(unsigned int &result,int &ordinal,bool &SaveOrNot,int distance,unsigned int LimitNumber)
{
	gotoXY(4 + distance,ordinal*2 + 4);
	int count = 0;// mac dinh 

	int num = result;
	while (num != 0)
	{
		count++;
		num /= 10;
	} 
	while( true )
	{
		while( _kbhit() )
		{
			int signal = _getch();
			if( signal == 224 || signal == 0 )
			{
				_getch();
				continue;
			}
				/*  ---tu 0 den 9--- va count nho hon 3*/
			if( 48 <= signal && signal <= 57)
			{
					/* signal = 56 -> numb = 56 - 48 = 8 -> ung dung voi so 8*/
			    int Numb = signal - 48;
		     	if( signal == 48 && count == 0 )
				{
					continue;
					}
					/* vi du LimitNumber = 100 co nghia may bay chi cho 
					nhap toi da 100 cho ngoi */
			    else if( (result*10 + Numb) <= LimitNumber) 
				{
					cout << Numb;
					result = result*10 + Numb;
					count ++;
				}
			}
			else if (signal == ESC)
			{
				SaveOrNot = false;
				return;
			}	 
			else if( signal == 8 && count > 0 )
			{
				cout << (char)BACKSPACE<<" "<<(char)BACKSPACE;
				count--;
				result /= 10;
			}
			else if( signal == ENTER)
			{
				if(count == 0) continue;
				if (result > LimitNumber)  continue;
				SaveOrNot = true;
				return;
			}
		}
			
	}
}
void ConstraintForOnlyGender(int &result,int &ordinal,bool &SaveOrNot,int distance)
{
	gotoXY(4 + distance, ordinal*2 + 4);
	if( result != 0)
	{
		cout << result;
	}
	int count = 0;
	while( true )
	{
		while( _kbhit() )
		{
			int signal = _getch();
			if( signal != 224 && signal != SPACE && signal != 0 )
			{
				/*  ---tu 0 den 1--- va count nho hon 3*/
				if( 48 <= signal && signal <= 49)
				{
					/* signal = 56 -> numb = 56 - 48 = 8 -> ung dung voi so 8*/
					int Numb = signal - 48;
					
					/* vi du LimitNumber = 100 co nghia may bay chi cho 
					nhap toi da 100 cho ngoi */
					if( -1 < result*10 + Numb && result*10 +Numb < 2) 
					{
						cout << Numb;
						result = result*10 + Numb;
						count ++;
					}
					else if(signal == ESC)
					{
						SaveOrNot = false;
						return;
					}

				}
				 
				else if (signal == 8 && count >= 0)
				{
					cout << (char)BACKSPACE << " " << (char)BACKSPACE;
					count--;
					result /= 10;
				}

				else if( signal == ENTER)
				{
					if (result > 1)
						continue;
					return;
				}
			}// ( signal != 224 && signal != BACKSPACE && signal != 0)
		}// while( _kbhit() )
	}// while(true)
}

void ConstraintForDateAndTime( int &result,bool &SaveOrNot,  int LimitReach)
{
    result = 0;
	int count = 0;
	int signal ;
	while(true)
	{
		while( _kbhit() )
		{
			signal = _getch();
            if( signal == 224 || signal == 0 )
			{
				_getch();
				continue;
			}
			if(  48 <= signal && signal <= 57 )
			{
				int numb = signal - 48;
				/*vi nhu nhap 13 la gio thi khong hop le*/
				if( result > LimitReach )
					continue;
				if ( (result * 10 + numb) <= LimitReach)
				{
					cout << numb;
					result = result * 10 + (numb);
					count++;
				}
			}
			else if (signal == 8 && count > 0)
			{
				cout << (char)BACKSPACE << " " << (char)BACKSPACE;
				count--;
				result /= 10;
			}	
			else if (signal == ENTER)
			{
				if (count == 0) continue;
                if (result > LimitReach) continue;
				if (result == 0 && LimitReach != 23 && LimitReach != 59)
                {
                    continue; // Khóa Enter d?i v?i Ngày 00, Tháng 00
                }
				    SaveOrNot = true; 
					return;
			}
		}
	}
}

