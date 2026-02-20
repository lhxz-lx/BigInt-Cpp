#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <string>
#include <algorithm>

class BigInt{
    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    friend BigInt operator+(BigInt, const BigInt&); //a + b, 此处是形参，修改不会影响本身
    friend BigInt operator-(BigInt, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator%(const BigInt&, const BigInt&);
private:
    int* nums_;
    int len_;
    int cap_;
    bool is_neg_; 
    void trim();
    void resize(int); //改容量
    void add_abs(const BigInt&); //绝对值相加
    void sub_abs(const BigInt&); //绝对值相减，保证*this >= other
    bool abs_less(const BigInt&) const; //绝对值*this < other
    void div_mod_abs(const BigInt&, BigInt& q, BigInt& r) const; //q是商quotient，r是余数remainder
public:
    BigInt();
    ~BigInt();
    BigInt(const BigInt&);
    BigInt(const int);
    BigInt(const long long&);
    BigInt(const std::string&);
    BigInt(const char*);
    BigInt(BigInt&&) noexcept; //移动构造
    BigInt& operator=(BigInt&&) noexcept; //移动赋值
    BigInt& operator=(const BigInt&);
    explicit operator long long() const; //转long long
    explicit operator std::string() const; //转string
    bool operator==(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt operator-() const;
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);
};

#endif