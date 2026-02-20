#include "big_int.h"

int main() {

    //1.构造函数与隐式转换
    std::cout << "1.构造与隐式转换测试\n";
    BigInt zero = 0;
    BigInt n1 = -12345;
    BigInt n2 = "999999999999999999999999999999"; // 30个9
    std::cout << "zero (int): " << zero << "\n";
    std::cout << "n1 (long long): " << n1 << "\n";
    std::cout << "n2 (string): " << n2 << "\n\n";

    //2.极限加减法与进位/借位
    std::cout << "2.加减法极限测试\n";
    BigInt a = "99999999999999999999";
    BigInt b = 1;
    std::cout << a << " + " << b << " = \n" << (a + b) << " (预期: 100000000000000000000)\n\n";
    
    BigInt c = 1000000;
    BigInt d = 1000001;
    std::cout << c << " - " << d << " = " << (c - d) << " (预期: -1)\n";
    std::cout << d << " - " << c << " = " << (d - c) << " (预期: 1)\n\n";

    //3.防御 -0 测试
    std::cout << "3.防御 -0 测试\n";
    BigInt zero_test = 5;
    zero_test -= 5;
    std::cout << "5 - 5 = " << zero_test << " (预期不能有负号: 0)\n";
    std::cout << "0 * -5 = " << (zero * BigInt(-5)) << " (预期不能有负号: 0)\n";
    std::cout << "-0 取相反数: " << (-zero) << " (预期不能有负号: 0)\n\n";

    //4.大数乘法
    std::cout << "4.大数乘法测试\n";
    BigInt m1 = "123456789";
    BigInt m2 = "987654321";
    std::cout << m1 << " * " << m2 << " = \n" << (m1 * m2) << " (预期: 121932631112635269)\n";
    std::cout << "-999 * 0 = " << (BigInt(-999) * 0) << "\n\n";

    //5.大数除法与取模
    std::cout << "5.除法与取模测试\n";
    BigInt div1 = "1000000000000000000000000";
    BigInt div2 = 3;
    std::cout << div1 << " / " << div2 << " = \n" << (div1 / div2) << " (预期: 333333333333333333333333)\n";
    std::cout << div1 << " % " << div2 << " = " << (div1 % div2) << " (预期: 1)\n";
    
    //负数取模测试
    std::cout << "-7 / 3 = " << (BigInt(-7) / 3) << " | -7 % 3 = " << (BigInt(-7) % 3) << " (预期: -2 | -1)\n\n";

    //6.自增自减与复合赋值
    std::cout << "6.运算符重载综合测试\n";
    BigInt count = 10;
    std::cout << "count 初值: " << count << "\n";
    std::cout << "count++ 返回旧值: " << count++ << "，当前真值: " << count << "\n";
    std::cout << "++count 返回新值: " << ++count << "\n";
    count *= 10;
    std::cout << "count *= 10: " << count << "\n\n";

    //7.异常测试
    std::cout << "7.异常捕捉测试 (除以 0)\n";
    try {
        BigInt crash = 100 / zero;
        std::cout << "Bug!" << crash << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "成功捕捉到异常: " << e.what() << " (预期: Division by zero!)\n";
    }
    return 0;
}