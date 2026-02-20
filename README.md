\# BigInt-Cpp



A custom arbitrary-precision integer class in C++ developed for learning and practicing object-oriented programming, dynamic memory management, and modern C++ features.



\## 🚀 Features



\* \*\*Arbitrary Precision:\*\* Handles integers of any size, limited only by available memory.

\* \*\*Full Operator Overloading:\*\* Supports standard arithmetic and relational operators (`+`, `-`, `\*`, `/`, `%`, `==`, `!=`, `<`, `>`, `<=`, `>=`).

\* \*\*Modern C++ Semantics:\*\* \* Implements the \*\*Rule of Five\*\* (Destructor, Copy Constructor, Copy Assignment, Move Constructor, Move Assignment) for safe and efficient memory management.

&nbsp; \* Utilizes \*\*Move Semantics\*\* (`std::move`) to prevent unnecessary deep copies and optimize performance.

\* \*\*Compound Assignment \& Increment/Decrement:\*\* Supports `+=`, `-=`, `\*=`, `/=`, `%=`, as well as prefix and postfix `++`/`--`.

\* \*\*Flexible Initialization:\*\* Can be constructed from `int`, `long long`, `std::string`, or `const char\*`.



\## 💻 Usage Example



```cpp

\#include <iostream>

\#include "big\_int.h"



int main() {

&nbsp;   BigInt a = "12345678901234567890";

&nbsp;   BigInt b = 9876543210;



&nbsp;   BigInt sum = a + b;

&nbsp;   BigInt product = a \* b;



&nbsp;   std::cout << "Sum: " << sum << std::endl;

&nbsp;   std::cout << "Product: " << product << std::endl;



&nbsp;   return 0;

}

