#include <iostream>
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define ld long double
#define each auto &
#define endl '\n'
#define pll pair<ll, ll>
#define all(v) v.begin(), v.end()
#define INF LONG_LONG_MAX
#define Outsiders freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define FastAsFBoy ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
using namespace std;

int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};


class BigReal
{
    friend ostream& operator<<(ostream &os, const BigReal Real);
    deque<uint8_t> l, r;
    bool sign;
    bool isvalid(string s)
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
        return true;
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
    BigReal(string s = "0.0")
    {
        *this = s;
    }
    BigReal(const BigReal &src) : l{src.l}, r{src.r}, sign{src.sign} 
    {
    }
    BigReal operator=(const BigReal &src)
    {
        l = src.l, r = src.r, sign = src.sign;
        return *this;
    }
    BigReal operator=(string s)
    {
        if (!s.empty() && s[0] == '-') sign = 1, s.erase(0, 1);
        else sign = 0;
        if (!isvalid(s)) throw("Invalid decimal number");
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
        return *this;
    }
    bool operator>(const BigReal &rhs)
    {
        if (sign != rhs.sign) return !sign;
        if (rhs.l.size() != l.size()) return (l.size() > rhs.l.size()) ^ sign;
        for (ll i{l.size() - 1}; i >= 0; i--)
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
    BigReal operator+(const BigReal &rhs)
    {
        BigReal tmp(*this);
        deque<uint8_t> &l{tmp.l}, &r{tmp.r};
        while (rhs.l.size() > l.size()) l.push_back(0);
        while (rhs.r.size() > r.size()) r.push_front(0);
        int c{};
        for (int i{}; i < r.size() && i < rhs.r.size(); i++)
        {
            c = r[i] + rhs.r[i] + c;
            r[i] = c % 10;
            c /= 10;
        }
        for (int i{}; i < l.size() && i < rhs.l.size(); i++)
        {
            c = l[i] + rhs.l[i] + c;
            l[i] = c % 10;
            c /= 10;
        }
        if (c) l.push_back(c);
        return tmp;
    }
};


ostream& operator<<(ostream &os, const BigReal r)
{
    os << r.getString();
    return os;
}

istream& operator<<(istream &is, BigReal r)
{
    string s;
    is >> s;
    r = s;
    return is;
}


int main()
{
    FastAsFBoy
    string s, t;
    cin >> s >> t;
    BigReal r(s), rr(t);
    cout << (r > rr ? "Yes" : "No") << endl;
}

