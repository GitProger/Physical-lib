#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include "phys.hpp" // physical header
#include "calc.hpp"
using namespace std;
using namespace physics;

enum class calc_mode : char {
    int_m, phy_m
};

int main(int argc, char *argv[]) {
    string expr;
    calc_mode mode = calc_mode::phy_m;
    for (;;) {
        getline(cin, expr);
        for (int i = 0; i < expr.length(); i++)
            if (isspace(expr[i])) {
                expr.erase(i, 1);
                i--;
            }
        if (expr == "quit" || expr == "exit")
            break;
        else if (expr == "int")
            mode = calc_mode::int_m;
        else if (expr == "phy")
            mode = calc_mode::phy_m;
        else if (mode == calc_mode::phy_m)            
            cout << calculate_phy(expr) << endl;
        else
            cout << calculate(expr) << endl;
    }
    return 0;
}

