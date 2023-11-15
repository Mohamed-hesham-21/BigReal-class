// FCAI - OOP Programming - 2023 - Assignment 1
// Last Modification Date : October 10th 2023
// Ahmed Yosry Saad       ID: 20221014   E-mail: ahmedyosry1014@gmail.com
// Sherif Yousef Mahmoud  ID: 20221081   E-mail: sherifyousef209@gmail.com
// Mohamed Hesham Mohamed ID: 20221133   E-mail: mohamedmaybe4u@gmail.com
// Purpose: make a variable that holds an unlimited number of digits (including decimals)

#include "BigReal.hpp"

bool BigReal::isValid(string &s) const
{
    // checks if all the characters in the string are digits and that there exists one '.' at the maximum or not
    if (s.empty()) return false;
    bool dot{};
    for (each c: s)
    {
        if (c == '.')
        {
            if (dot) return false;
            else dot = 1;
        }
        else if (!isdigit(c)) return false;
    }
    if (!dot) s += ".0";
    else if (s.front() == '.') s = '0'+ s;
    else if (s.back() == '.') s += '0';
    return true;
}


void BigReal::removeTrailingZeros()
{
    // removes trailing zeros of the start of the r deque and the end of the l deque
    while (l.size() > 1 && !l.back()) l.pop_back();
    while (r.size() > 1 && !r.front()) r.pop_front();
}


string BigReal::getString() const
{
    // forms a string from the digits in the l & r deques
    string s;
    for (each d: r) s.push_back(d + '0');
    s.push_back('.');
    for (each d: l) s.push_back(d + '0');
    if (sign) s.push_back('-');
    reverse(all(s));
    return s;
}

BigReal::BigReal(const BigReal &src) : l{src.l}, r{src.r}, sign{src.sign} 
{
    // copy constructor
}
BigReal::BigReal(string s)
{
    // string constructor which is using the overloaded assignment operator
    *this = s;
}
BigReal::BigReal(double d) : BigReal(to_string(d))
{
    // turn the double to a string then calling the string constructor
}
BigReal BigReal::operator=(const BigReal &src)
{
    l = src.l, r = src.r, sign = src.sign;
    return *this;
}
BigReal BigReal::operator=(string s)
{
    // reset the number
    l.clear(), r.clear();
    sign = 0;
    // get the sign if exists
    if (!s.empty() && s.front() == '-') sign = 1, s.erase(0, 1);
    else if (!s.empty() && s.front() == '+') s.erase(0, 1);
    
    // if the string is invalid, throw an exception
    if (!isValid(s))
    {
        cout << "Error: Invalid decimal number\n";
        throw BigReal();
    }
    // else copy the digits into the l & r deques
    else
    {
        bool dot{};
        reverse(all(s));
        for (each c: s)
        {
            if (c == '.') dot = true;
            else if (dot) l.push_back(c - '0');
            else r.push_back(c - '0');
        }
    }
    // remove trailing zeros
    removeTrailingZeros();
    return *this;
}
BigReal BigReal::operator=(double d)
{
    return *this = to_string(d);
}
bool BigReal::operator==(const BigReal &rhs) const
{
    return !(*this > rhs) && !(*this < rhs);
}
bool BigReal::operator!=(const BigReal &rhs) const
{
    return !(*this == rhs);
}
bool BigReal::operator>(const BigReal &rhs) const
{
    // if the signs are different, return true if the sign of the LHS is posistive, else return false
    if (sign != rhs.sign) return !sign;

    // if the sizes are different (integral part), return true if the LHS is the graeter one (the opposite if the sign is negative)
    if (rhs.l.size() != l.size()) return (l.size() > rhs.l.size()) ^ sign;
    for (ll i = l.size() - 1; i >= 0; i--)
    {
        // if the current digits are different, return true if the digit of LHS is the graeter one (the opposite if the sign is negative)
        if (l[i] != rhs.l[i]) return (l[i] > rhs.l[i]) ^ sign;
    }
    for (ll i{}; i < r.size() && rhs.r.size(); i++)
    {
        // if the current digits are different, return true if the digit of LHS is the graeter one (the opposite if the sign is negative)
        if (r[i] != rhs.r[i]) return (r[i] > rhs.r[i]) ^ sign;
    }
    // if their sized are the same (decimal part), return false
    // else return true if the LHS is the graeter one (the opposite if the sign is negative)
    if (r.size() == rhs.r.size()) return false;
    return (r.size() > rhs.r.size()) ^ sign;
}

bool BigReal::operator<(const BigReal rhs) const
{
    // same as > operator but reversed
    if (sign != rhs.sign) return !sign;
    if (rhs.l.size() != l.size()) return (l.size() < rhs.l.size()) ^ sign;
    for (ll i = l.size() - 1; i >= 0; i--)
    {
        if (l[i] != rhs.l[i]) return (l[i] < rhs.l[i]) ^ sign;
    }
    for (ll i{}; i < r.size() && rhs.r.size(); i++)
    {
        if (r[i] != rhs.r[i]) return (r[i] < rhs.r[i]) ^ sign;
    }
    if (r.size() == rhs.r.size()) return false;
    return (r.size() < rhs.r.size()) ^ sign;
}

bool BigReal::operator>=(const BigReal &rhs) const
{
    return (*this > rhs || *this == rhs);
}

bool BigReal::operator<=(const BigReal &rhs) const
{
    return (*this < rhs || *this == rhs);
}

BigReal BigReal::operator+=(BigReal rhs)
{
    int c{}, si{1};
    if (sign != rhs.sign)
    {
        sign = !sign;
        si *= -1;
        // if abs(rhs) > *this, swap them
        if (rhs > *this && !sign || *this > rhs && sign)  swap(*this, rhs);
        else sign = !sign;
    }
    // add trailing zeros to both numbers if their lengths are different
    while (rhs.l.size() > l.size()) l.push_back(0);
    while (rhs.r.size() > r.size()) r.push_front(0);
    while (rhs.l.size() < l.size()) rhs.l.push_back(0);
    while (rhs.r.size() < r.size()) rhs.r.push_front(0);
    
    // loop through all digits and add / subtract them (depending on whether their signs are different or not)
    for (int i{}; i < r.size() && i < rhs.r.size(); i++)
    {
        int tmp = r[i] + si * rhs.r[i] + c;
        if (tmp < 0) tmp += 10, c = -1;
        else c = tmp / 10, tmp %= 10;
        r[i] = tmp;
    }
    for (int i{}; i < l.size() && i < rhs.l.size(); i++)
    {
        int tmp = l[i] + si * rhs.l[i] + c;
        if (tmp < 0) tmp += 10, c = -1;
        else c = tmp / 10, tmp %= 10;
        l[i] = tmp;
    }
    // if there is a carry, add it to the end of the number;
    if (c > 0) l.push_back(c);
    // remove trailing zeros
    removeTrailingZeros();
    return *this;
}
BigReal BigReal::operator+(BigReal rhs)
{
    BigReal tmp = *this;
    tmp += rhs;
    return tmp;
}
BigReal BigReal::operator-=(BigReal rhs)
{
    // invert the sign of the rhs, then add as usual
    rhs.sign = !rhs.sign;
    *this += rhs;
    return *this;
}
BigReal BigReal::operator-(BigReal rhs)
{
    BigReal tmp = *this;
    rhs.sign = !rhs.sign;
    tmp += rhs;
    return tmp;
}


ostream& operator<<(ostream &os, const BigReal r)
{
    // display the result as a string using the getstring method
    os << r.getString();
    return os;
}

istream& operator>>(istream &is, BigReal &r)
{
    // take input as string, then assigning the BigReal to the string using th overloaded assignment operator
    string s;
    is >> s;
    r = s;
    return is;
}