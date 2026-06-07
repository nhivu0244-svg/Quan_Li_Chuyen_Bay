
#include <bits/stdc++.h>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <cctype>
#include "giaodien.h"

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

void ConstraintForLetterAndNumber(string &result,bool &MoveOrNot,bool &SaveOrNot,int distance);
void ConstraintForLETTERAndNumber(string &result,int &ordinal,bool &SaveOrNot,int distance);
void ConstraintsForLetterAndSpace(string &result,int &ordinal,bool &SaveOrNot,int distance);
void ConstraintForOnlyLetter(string &result,int &ordinal,bool &SaveOrNot,int distance);
void ConstraintForOnlyNumber(unsigned int &result,int &ordinal,bool &SaveOrNot,int distance,unsigned int LimitNumber);
void ConstraintForOnlyGender(int &result,int &ordinal,bool &SaveOrNot,int distance);
void ConstraintForDateAndTime( int &result,bool &SaveOrNot, int LimitReach);



