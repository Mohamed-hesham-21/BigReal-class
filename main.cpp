// FCAI - OOP Programming - 2023 - Assignment 1
// Last Modification Date : October 10th 2023
// Ahmed Yosry Saad       ID: 20221014   E-mail: ahmedyosry1014@gmail.com
// Sherif Yousef Mahmoud  ID: 20221081   E-mail: sherifyousef209@gmail.com
// Mohamed Hesham Mohamed ID: 20221133   E-mail: mohamedmaybe4u@gmail.com
// Purpose: make a variable that holds an unlimited number of digits (including decimals)

#include <iostream>
#include "BigReal.cpp"
using namespace std;

int main()
{
    cout <<"Welcome ya a7la user ^^\n";
    cout << "Enter first number :\n";

    BigReal Number_1, Number_2;
    cin >> Number_1;
    cout << "Enter second number :\n";
    cin >> Number_2;

    while (true)
    {
        cout << "============================================\n";
        cout << "Choose any operation from the following:\n";
        cout << "1-Num_1 + Num_2\n";
        cout << "2-Num_1 - Num_2\n";
        cout << "3-Num_2 - Num_1\n";
        cout << "4-Change the two numbers\n";
        cout << "0-End the program\n";
        cout << "============================================\n";
        int op;
        cin >> op;
        if (!op) return 0;
        if (op >= 0 && op <= 4) cout << "Result: ";
        if (op == 1)
        {
            BigReal x = Number_1 + Number_2;
            cout << x << endl;
        }
        else if (op == 2) cout << Number_1 - Number_2 << endl;
        else if (op == 3) cout << Number_2 - Number_1 << endl;
        else if (op == 4)
        {
            cout << "Enter first number :\n";
            cin >> Number_1 ;
            cout << "Enter second number :\n";
            cin >> Number_2 ;
        }
    }
}