#include "big_int.h"

void BigInt::trim(){
    while(len_ > 1 && nums_[len_ - 1] == 0){
        len_--;
    }
}

void BigInt::resize(int new_cap){
    if(new_cap == cap_) return;
    if(new_cap < len_) return;
    cap_ = new_cap;
    int* new_nums = new int[new_cap];
    for(int i = 0; i < len_; i++){
        new_nums[i] = nums_[i];
    }
    for(int i = len_; i < new_cap; i++){
        new_nums[i] = 0;
    }
    delete[] nums_;
    nums_ = new_nums;
}

BigInt::BigInt(){
    cap_ = 1;
    len_ = 1;
    nums_ = new int[1];
    nums_[0] = 0;
    is_neg_ = 0;
}

BigInt::~BigInt(){
    delete[] nums_;
}

BigInt::BigInt(const BigInt& other){
    len_ = other.len_;
    cap_ = other.len_;
    is_neg_ = other.is_neg_;
    nums_ = new int[cap_];
    for(int i = 0; i < len_; i++){
        nums_[i] = other.nums_[i];
    }
}

BigInt::BigInt(const long long& num){
    unsigned long long cpy = num; 
    if(num < 0) cpy = -cpy;
    if(num >= 0) is_neg_ = 0;
    else is_neg_ = 1;
    if(num == 0){
        len_ = 1;
        cap_ = 1;
        nums_ = new int[1];
        nums_[0] = 0;
        return;
    }
    cap_ = 20;
    nums_ = new int[cap_];
    len_ = 0;
    while(cpy > 0){
        nums_[len_] = cpy % 10; 
        cpy /= 10;
        len_++;
    }
}

BigInt::BigInt(const int num) : BigInt((long long)num){
}

BigInt::BigInt(const std::string& str){
    int st_idx = 0;
    is_neg_ = 0;
    if(str.size() > 0 && str[0] == '-'){
        st_idx = 1;
        is_neg_ = 1;
    }
    else if(str.size() > 0 && str[0] == '+'){
        st_idx = 1;
    }
    len_ = str.size() - st_idx;
    if(len_ == 0){
        len_ = 1;
        cap_ = 1;
        is_neg_ = 0;
        nums_ = new int[1];
        nums_[0] = 0;
        return;
    }
    cap_ = len_;
    nums_ = new int[cap_];
    for(int i = 0; i < len_; i++){
        nums_[i] = str[str.size() - i - 1] - '0';
    }
    trim();
    if(is_neg_ == 1 && len_ == 1 && nums_[0] == 0) is_neg_ = 0;
}

BigInt::BigInt(const char* str) : BigInt(std::string(str)){
}

BigInt::BigInt(BigInt&& other) noexcept{
    nums_ = other.nums_;
    len_ = other.len_;
    cap_ = other.cap_;
    is_neg_ = other.is_neg_;
    other.nums_ = nullptr;
    other.len_ = 0;
    other.cap_ = 0;
    other.is_neg_ = 0;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept{
    if(this == &other){
        return *this;
    }
    delete[] nums_;
    nums_ = other.nums_;
    len_ = other.len_;
    cap_ = other.cap_;
    is_neg_ = other.is_neg_;
    other.nums_ = nullptr;
    other.len_ = 0;
    other.cap_ = 0;
    other.is_neg_ = 0;
    return *this;
}

BigInt& BigInt::operator=(const BigInt& other){
    if(this == &other) return *this;
    delete[] nums_;
    len_ = other.len_;
    cap_ = other.len_;
    is_neg_ = other.is_neg_;
    nums_ = new int[cap_];
    for(int i = 0; i < len_; i++){
        nums_[i] = other.nums_[i];
    }
    return *this;
}

std::istream& operator>>(std::istream &is, BigInt& n){
    std::string str;
    if(!(is >> str)) return is;
    n = BigInt(str);
    return is;
}

std::ostream& operator<<(std::ostream &os, const BigInt& n){
    if(n.is_neg_) os << '-';
    for(int i = n.len_ - 1; i >= 0; i--){
        os << n.nums_[i];
    }
    return os;
}

BigInt::operator long long() const{
    unsigned long long ans = 0;
    unsigned long long base = 1;
    int idx = 0;
    while(idx < len_){
        ans += base * nums_[idx];
        base *= 10;
        idx++;
    }
    return is_neg_ ? -ans : ans;
}

BigInt::operator std::string() const{
    std::string ans;
    if(is_neg_) ans += '-';
    for(int i = len_ - 1; i >= 0; i--){
        ans += nums_[i] + '0';
    }
    return ans;
}

bool BigInt::operator==(const BigInt& other) const{
    if(is_neg_ != other.is_neg_) return 0;
    if(len_ != other.len_) return 0;
    for(int i = 0; i < len_; i++){
        if(nums_[i] != other.nums_[i]) return 0;
    }
    return 1;
}

bool BigInt::operator>(const BigInt& other) const{
    if(is_neg_ != other.is_neg_) return is_neg_ < other.is_neg_;
    if(len_ != other.len_){
        return (len_ > other.len_) ^ is_neg_;
    }
    for(int i = len_ - 1; i >= 0; i--){
        if(nums_[i] != other.nums_[i]){
            return (nums_[i] > other.nums_[i]) ^ is_neg_;
        }
    }
    return 0;
}

bool BigInt::operator<(const BigInt& other) const{
    return other > *this;
}

bool BigInt::operator>=(const BigInt& other) const{
    return !(other > *this);
}

bool BigInt::operator<=(const BigInt& other) const{
    return !(*this > other);
}

bool BigInt::operator!=(const BigInt& other) const{
    return !(*this == other);
}

void BigInt::add_abs(const BigInt& other){
    int new_cap = std::max(len_, other.len_) + 1;
    resize(new_cap);
    for(int i = len_; i < cap_; i++){
        nums_[i] = 0;
    }
    len_ = cap_;
    for(int i = 0; i < other.len_; i++){
        nums_[i] += other.nums_[i];
        if(nums_[i] >= 10){
            nums_[i + 1]++;
            nums_[i] -= 10;
        }
    }
    for(int i = other.len_; i < len_ - 1; i++){
        if(nums_[i] >= 10){
            nums_[i + 1]++;
            nums_[i] -= 10;
        }
        else break;
    }
    trim();
}

void BigInt::sub_abs(const BigInt& other){
    for(int i = 0; i < other.len_; i++){
        nums_[i] -= other.nums_[i];
        if(nums_[i] < 0){
            nums_[i] += 10;
            nums_[i + 1]--;
        }
    }
    for(int i = other.len_; i < len_ - 1; i++){
        if(nums_[i] < 0){
            nums_[i] += 10;
            nums_[i + 1]--;
        }
        else break;
    }
    trim();
}

bool BigInt::abs_less(const BigInt& other) const{
    if(len_ != other.len_){
        return len_ < other.len_;
    }
    for(int i = len_ - 1; i >= 0; i--){
        if(nums_[i] != other.nums_[i]){
            return nums_[i] < other.nums_[i];
        }
    }
    return 0;
}

BigInt& BigInt::operator+=(const BigInt& other){
    if(is_neg_ == other.is_neg_){
        add_abs(other);
        return *this;
    }
    if(abs_less(other)){
        BigInt tmp = other;
        tmp.sub_abs(*this);
        *this = std::move(tmp);
        return *this;
    }
    sub_abs(other);
    if(len_ == 1 && nums_[0] == 0) {
        is_neg_ = 0; 
    }
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other){
    if(is_neg_ != other.is_neg_){
        add_abs(other);
        return *this;
    }
    if(abs_less(other)){
        BigInt tmp = other;
        tmp.sub_abs(*this);
        tmp.is_neg_ = !tmp.is_neg_;
        *this = std::move(tmp);
        return *this;
    }
    sub_abs(other);
    if(len_ == 1 && nums_[0] == 0) {
        is_neg_ = 0; 
    }
    return *this;
}

BigInt BigInt::operator-() const{
    BigInt res = *this;
    if(res.len_ == 1 && res.nums_[0]== 0){
        return res;
    }
    res.is_neg_ = !res.is_neg_;
    return res;
}

BigInt operator+(BigInt lhs, const BigInt& rhs){
    lhs += rhs;
    return lhs;
}

BigInt operator-(BigInt lhs, const BigInt& rhs){
    lhs -= rhs;
    return lhs;
}

BigInt& BigInt::operator++(){
    *this += 1; // 自动帮我把1转成BigInt
    return *this;
}

BigInt& BigInt::operator--(){
    *this -= 1;
    return *this;
}

BigInt BigInt::operator++(int){
    BigInt tmp = *this;
    *this += 1;
    return tmp;
}

BigInt BigInt::operator--(int){
    BigInt tmp = *this;
    *this -= 1;
    return tmp;
}

BigInt operator*(const BigInt& lhs, const BigInt& rhs){
    BigInt res = 0;
    res.resize(lhs.len_ + rhs.len_);
    res.len_ = res.cap_;
    for(int i = 0; i < lhs.len_; i++){
        for(int j = 0; j < rhs.len_; j++){
            res.nums_[i + j] += lhs.nums_[i] * rhs.nums_[j];
        }
    }
    for(int i = 0; i < res.len_ - 1; i++){
        if(res.nums_[i] >= 10){
            res.nums_[i + 1] += res.nums_[i] / 10;
            res.nums_[i] %= 10;
        }
    }
    res.is_neg_ = lhs.is_neg_ ^ rhs.is_neg_;
    res.trim();
    if (res.len_ == 1 && res.nums_[0] == 0) {
        res.is_neg_ = false;
    }
    return res;
}

BigInt& BigInt::operator*=(const BigInt& other){
    *this = *this * other;
    return *this;
}

void BigInt::div_mod_abs(const BigInt& other, BigInt& q, BigInt& r) const{
    if(other == 0){
        throw std::invalid_argument("Division by zero!");
    }
    q.resize(len_);
    q.len_ = len_;
    for(int i = 0; i < q.len_; i++){
        q.nums_[i] = 0;
    }
    r = 0;
    if(abs_less(other)){
        r = *this;
        r.is_neg_ = 0;
        return;
    }
    for(int i = len_ - 1; i >= 0; i--){
        r = r * 10 + nums_[i];
        int cnt = 0;
        while(!r.abs_less(other)){
            cnt++;
            r.sub_abs(other);
        }
        q.nums_[i] = cnt;
    }
    q.trim();
    r.is_neg_ = 0;
}

BigInt operator/(const BigInt& lhs, const BigInt& rhs){
    if(rhs == 0){
        throw std::invalid_argument("Division by zero!");
    }
    BigInt q = 0;
    BigInt r = 0;
    lhs.div_mod_abs(rhs, q, r);
    q.is_neg_ = lhs.is_neg_ ^ rhs.is_neg_;
    if(q.len_ == 1 && q.nums_[0] == 0) {
        q.is_neg_ = 0;
    }
    return q;
}

BigInt operator%(const BigInt& lhs, const BigInt& rhs){
    if(rhs == 0){
        throw std::invalid_argument("Division by zero!");
    }
    BigInt q = 0;
    BigInt r = 0;
    lhs.div_mod_abs(rhs, q, r);
    r.is_neg_ = lhs.is_neg_;
    if(r.len_ == 1 && r.nums_[0] == 0) {
        r.is_neg_ = 0;
    }
    return r;
}

BigInt& BigInt::operator/=(const BigInt& other){
    *this = *this / other;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& other){
    *this = *this % other;
    return *this;
}