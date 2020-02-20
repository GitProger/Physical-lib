#ifndef __CALC_LIB_INC
#define __CALC_LIB_INC
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "phys.hpp"
using namespace physics;

int gcd(int a, int b) {
    int tmp;
    while (a && b) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a ? a : b;
}

using string = std::string;

int CloseBraces(string expr, int pos) {
     int i = 0, Close = -1;
     for (i = pos + 1; i < expr.length(); i++) { 
         if (expr[i] == '(') Close--; else
         if (expr[i] == ')') Close++;
         if (Close == 0) break;          
     }
     return i;
}

string strFromDouble(long double db) {
    return std::to_string(db);
}

long double doubleFromStr(string str) {
    char buffer[128] = {};
    long double db = 0.0;
    sprintf(buffer, "%s", str.c_str());
    sscanf(buffer, "%llf", &db);
    return db;
}

long double calculate(string expr) {
     while (expr.find('(') != -1) {
         string buffer = expr.substr(expr.find('('), CloseBraces(expr, expr.find('(')) + 1);
         expr = expr.replace( expr.find(buffer),
             buffer.length(),
             strFromDouble( calculate(expr.substr(expr.find('(') + 1, CloseBraces(expr, expr.find('(')) ) ) )
         ); 
     }

     if (expr.find('+') != -1) {
         return calculate(expr.substr(0, expr.find('+'))) + calculate(expr.substr(expr.find('+') + 1, expr.length())); 
     } else
     if ((expr.find('-') != -1) && ((expr[expr.find_last_of('-') - 1] >= '0') && (expr[expr.find_last_of('-') - 1] <= '9'))) {
         return calculate(expr.substr(0, expr.find('-'))) - calculate(expr.substr(expr.find('-') + 1, expr.length())); 
     } else
     if (expr.find('*') != -1) {
         return calculate(expr.substr(0, expr.find('*'))) * calculate(expr.substr(expr.find('*') + 1, expr.length())); 
     } else
     if (expr.find('/') != -1) {
         return calculate(expr.substr(0, expr.find('/'))) / calculate(expr.substr(expr.find('/') + 1, expr.length())); 
     } else
     if (expr.find('^') != -1) {
         return pow(calculate(expr.substr(0, expr.find('^'))), calculate(expr.substr(expr.find('^') + 1, expr.length()))); 
     } else
         return doubleFromStr(expr);
}

string strFromPhy(WidePhyNum w) {
    return strFromDouble(w.getValue()) + "," + strFromDouble(w.getInaccuracy());
}

WidePhyNum phyFromStr(string str) {
    char buffer[128] = { };
    physicalNumber p = {0.0, 0.0};
    if (str[0] == '[' && str[str.length() - 1] == ']') {
        sprintf(buffer, "%s", str.substr(1, str.length() - 2).c_str());
        sscanf(buffer, "%lf,%lf", &p.value, &p.inaccuracy);
    } else 
        p.value = doubleFromStr(str);
    return WidePhyNum(p);
}

WidePhyNum calculate_phy(string expr) {
     while (expr.find('(') != -1) {
         string buffer = expr.substr(expr.find('('), CloseBraces(expr, expr.find('(')) + 1);
         expr = expr.replace( expr.find(buffer),
             buffer.length(),
             strFromPhy( calculate_phy(expr.substr(expr.find('(') + 1, CloseBraces(expr, expr.find('(')) ) ) )
         ); 
     }

     if (expr.find('+') != -1) {
         return calculate_phy(expr.substr(0, expr.find('+'))) + calculate_phy(expr.substr(expr.find('+') + 1, expr.length())); 
     } else
     if ((expr.find('-') != -1) && ((expr[expr.find_last_of('-') - 1] >= '0') && (expr[expr.find_last_of('-') - 1] <= '9'))) {
         return calculate_phy(expr.substr(0, expr.find('-'))) - calculate_phy(expr.substr(expr.find('-') + 1, expr.length())); 
     } else
     if (expr.find('*') != -1) {
         return calculate_phy(expr.substr(0, expr.find('*'))) * calculate_phy(expr.substr(expr.find('*') + 1, expr.length())); 
     } else
     if (expr.find('/') != -1) {
         return calculate_phy(expr.substr(0, expr.find('/'))) / calculate_phy(expr.substr(expr.find('/') + 1, expr.length())); 
     } else
//     if (expr.find('^') != -1) {
//         return pow(calculate_phy(expr.substr(0, expr.find('^'))), calculate_phy(expr.substr(expr.find('^') + 1, expr.length()))); 
//     } else
         return phyFromStr(expr);
}

#endif
