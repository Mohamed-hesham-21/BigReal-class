// FCAI - OOP Programming - 2023 - Assignment 1
// Last Modification Date : October 10th 2023
// Ahmed Yosry Saad       ID: 20221014   E-mail: ahmedyosry1014@gmail.com
// Sherif Yousef Mahmoud  ID: 20221081   E-mail: sherifyousef209@gmail.com
// Mohamed Hesham Mohamed ID: 20221133   E-mail: mohamedmaybe4u@gmail.com
// Purpose: make a variable that holds an unlimited number of digits (including decimals)

#ifndef __BIGREAL__
#define __BIGREAL__
#include <bits/stdc++.h>
#define ll long long
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
using namespace std;

class BigReal
{
    friend ostream& operator<<(ostream &os, const BigReal Real);
    deque<uint8_t> l, r;
    bool sign;
    void removeTrailingZeros();
    string getString() const;
    public:
    bool isValid(string &s) const;
    BigReal(const BigReal &src);
    BigReal(string s = "0.0");
    BigReal(double d);
    BigReal operator=(const BigReal &src);
    BigReal operator=(string s);
    BigReal operator=(double d);
    bool operator==(const BigReal &rhs) const;
    bool operator!=(const BigReal &rhs) const;
    bool operator>(const BigReal &rhs) const;
    bool operator<(const BigReal rhs) const;
    bool operator>=(const BigReal &rhs) const;
    bool operator<=(const BigReal &rhs) const;
    BigReal operator+=(BigReal rhs);
    BigReal operator+(BigReal rhs);
    BigReal operator-=(BigReal rhs);
    BigReal operator-(BigReal rhs);
    
};

#endif