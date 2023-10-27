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
    bool isValid(string &s)
    {
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
        if (s.front() == '.') s = '0'+ s;
        if (s.back() == '.') s += '0';
        return true;
    }
    void removeTrailingZeros()
    {
        while (l.size() > 1 && !l.back()) l.pop_back();
        while (r.size() > 1 && !r.front()) r.pop_front();
    }
    string getString() const
    {
        string s;
        for (each d: r) s.push_back(d + '0');
        s.push_back('.');
        for (each d: l) s.push_back(d + '0');
        if (sign) s.push_back('-');
        reverse(all(s));
        return s;
    }
    public:
    BigReal(const BigReal &src) : l{src.l}, r{src.r}, sign{src.sign} 
    {
    }
    BigReal(string s = "0.0")
    {
        *this = s;
    }
    BigReal(double d) : BigReal(to_string(d))
    {
    }
    BigReal operator=(const BigReal &src)
    {
        l = src.l, r = src.r, sign = src.sign;
        return *this;
    }
    BigReal operator=(string s)
    {
        sign = 0;
        if (!s.empty() && s.front() == '-') sign = 1, s.erase(0, 1);
        else if (!s.empty() && s.front() == '+') s.erase(0, 1);
        
        if (!isValid(s)) throw("Invalid decimal number");
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
        removeTrailingZeros();
        return *this;
    }
    BigReal operator=(double d)
    {
        return *this = to_string(d);
    }
    bool operator==(const BigReal &rhs) const
    {
        if (sign != rhs.sign || l.size() != rhs.l.size() || r.size() != rhs.r.size()) return false;

        for (int i = 0; i < rhs.l.size(); ++i) 
        {
            if (l[i] != rhs.l[i]) return false;
        }
        for (int i = 0; i < rhs.r.size(); ++i) 
        {
            if (r[i] != rhs.r[i]) return false;
        }
        return true;
    }
    bool operator!=(const BigReal &rhs) const
    {
        return !(*this == rhs);
    }
    bool operator>(const BigReal &rhs) const
    {
        if (sign != rhs.sign) return !sign;
        if (rhs.l.size() != l.size()) return (l.size() > rhs.l.size()) ^ sign;
        for (ll i = l.size() - 1; i >= 0; i--)
        {
            if (l[i] != rhs.l[i]) return (l[i] > rhs.l[i]) ^ sign;
        }
        for (ll i{}; i < r.size() && rhs.r.size(); i++)
        {
            if (r[i] != rhs.r[i]) return (r[i] > rhs.r[i]) ^ sign;
        }
        if (r.size() == rhs.r.size()) return false;
        return (r.size() > rhs.r.size()) ^ sign;
    }

    bool operator<(const BigReal rhs)
    {
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

    bool operator>=(const BigReal &rhs)
    {
        return (*this > rhs || *this == rhs);
    }

    bool operator<=(const BigReal &rhs)
    {
        return (*this < rhs || *this == rhs);
    }
    
    BigReal operator+=(BigReal rhs)
    {
        int c{}, si{1};
        if (sign != rhs.sign)
        {
            sign = !sign;
            si *= -1;
            if (rhs > *this && !sign || *this > rhs && sign)  swap(*this, rhs);
            else sign = !sign;
        }

        while (rhs.l.size() > l.size()) l.push_back(0);
        while (rhs.r.size() > r.size()) r.push_front(0);
        while (rhs.l.size() < l.size()) rhs.l.push_back(0);
        while (rhs.r.size() < r.size()) rhs.r.push_front(0);

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
        if (c > 0) l.push_back(c);
        removeTrailingZeros();
        return *this;
    }
    BigReal operator+(BigReal rhs)
    {
        BigReal tmp = *this;
        tmp += rhs;
        return tmp;
    }
    BigReal operator-=(BigReal rhs)
    {
        rhs.sign = !rhs.sign;
        *this += rhs;
        return *this;
    }
    BigReal operator-(BigReal rhs)
    {
        BigReal tmp = *this;
        rhs.sign = !rhs.sign;
        tmp += rhs;
        return tmp;
    }
};


ostream& operator<<(ostream &os, const BigReal r)
{
    os << r.getString();
    return os;
}

istream& operator>>(istream &is, BigReal r)
{
    string s;
    is >> s;
    r = s;
    return is;
}