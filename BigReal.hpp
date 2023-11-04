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
    bool isValid(string &s) const;
    void removeTrailingZeros();
    string getString() const;
    public:
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