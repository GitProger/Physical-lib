#ifndef __PHYS_HPP_INC
#define __PHYS_HPP_INC
#include "exc.hpp"
#include <cmath>
#define PLUS_MINUS "+-"
namespace physics {

struct physicalNumber {
    double value, inaccuracy;
};

class WidePhyNum final: private physicalNumber {
    public:
        WidePhyNum(int __val, int __err = 0.0)
            : physicalNumber({.value = static_cast<double>(__val),
                .inaccuracy = static_cast<double>(__err)})
        {}
        WidePhyNum(double __val, double __err = 0.0)
            : physicalNumber({.value = __val, .inaccuracy = __err})
        {}
        ~WidePhyNum() {}
        double relativeErr() const {
             if (this->value == 0.0)
                 throw ZeroDivisionException("0 value in instanse"
                     " of 'WidePhyNum' in 'relativeErr' const method");
             return this->inaccuracy / this->value;
        }
        void setInaccuracy(double i) {
            this->inaccuracy = i;
        }
        double getInaccuracy() const {
            return this->inaccuracy;
        }
        void setValue(double v) {
            this->value = v;
        }
        double getValue() const {
            return this->value;
        }

        WidePhyNum &operator = (const WidePhyNum &cp) { // references here - only for speed
            this->value = cp.value;
            this->inaccuracy = cp.inaccuracy;
            return *this;            
        }
        const WidePhyNum operator + (const WidePhyNum &cp) const {
            return WidePhyNum( // no refs, because such funcyions returns temp object, 
                this->value + cp.value,  // it should been copy
                this->inaccuracy + cp.inaccuracy
            );
        }
        const WidePhyNum operator - (const WidePhyNum &cp) const {
            return WidePhyNum(
                this->value - cp.value, 
                this->inaccuracy + cp.inaccuracy
            );
        }
        WidePhyNum &operator += (const WidePhyNum &cp) {
            this->value += cp.value; 
            this->inaccuracy += cp.inaccuracy;
            return *this;
        }
        WidePhyNum &operator -= (const WidePhyNum &cp) {
            this->value -= cp.value; 
            this->inaccuracy += cp.inaccuracy;
            return *this;
        }
        const WidePhyNum operator - () const {
            return WidePhyNum(
                -this->value, 
                this->inaccuracy
            );
        }

        const WidePhyNum operator * (const WidePhyNum &cp) const {
            return WidePhyNum(
                this->value * cp.value, 
                this->inaccuracy * cp.value + this->value * cp.inaccuracy
            );
        }
        WidePhyNum &operator *= (const WidePhyNum &cp) {
            this->value *= cp.value;
            this->inaccuracy = this->inaccuracy * cp.value + this->value * cp.inaccuracy;
            return *this;
        }
        const WidePhyNum operator / (const WidePhyNum &cp) const {
            if (cp.value == 0.0)
                throw ZeroDivisionException("0 value in instanse"
                       " of 'WidePhyNum' in 'opertor/' const method");
            return WidePhyNum(
                this->value / cp.value, 
                (this->inaccuracy * cp.value + this->value * cp.inaccuracy) 
                    / (cp.value * cp.value)
            );
        }
        WidePhyNum &operator /= (const WidePhyNum &cp) {
            if (cp.value == 0.0)
                throw ZeroDivisionException("0 value in instanse"
                       " of 'WidePhyNum' in 'opertor/=' method");
            this->value /= cp.value;
            this->inaccuracy = (this->inaccuracy * cp.value + this->value * cp.inaccuracy) 
                    / (cp.value * cp.value);
        }

        const WidePhyNum operator + (double cp) const {
            return this->operator+ (WidePhyNum(cp, 0.0));
        }
        const WidePhyNum operator - (double cp) const {
            return this->operator- (WidePhyNum(cp, 0.0));
        }
        WidePhyNum &operator += (double cp) {
            return this->operator+= (WidePhyNum(cp, 0.0));
        }
        WidePhyNum &operator -= (double cp) {
            return this->operator-= (WidePhyNum(cp, 0.0));
        }
        const WidePhyNum operator * (double cp) const {
            return this->operator* (WidePhyNum(cp, 0.0));
        }
        WidePhyNum &operator *= (double cp) {
            return this->operator*= (WidePhyNum(cp, 0.0));
        }
        const WidePhyNum operator / (double cp) const {
            return this->operator/ (WidePhyNum(cp, 0.0));
        }
        WidePhyNum &operator /= (double cp) {
            return this->operator/= (WidePhyNum(cp, 0.0));
        }
};

double middleValue(double measures[], int N) {
    double m_mid = 0.0;
    for (int i = 0; i < N; i++)
        m_mid += measures[i];
    return (m_mid /= N);
}

double middleSquareInac(double in1, double in2) {
    return sqrt(in1 * in1 + in2 * in2);
}

double randomInaccuracy(double measures[], int N) {
        double res = 0.0, m_mid = middleValue(measures, N);
        for (int i = 0; i < N; i++)
            res += pow(measures[i] - m_mid, 2.0);
        res = sqrt(res / (N * (N - 1)));
        return res;
}

double roundDoubleUp(double d, int symAm) {
    symAm = pow(10, symAm);
    return static_cast<double>(ceil(d * symAm) / symAm);
}

double roundDouble(double d, int symAm) {
    symAm = pow(10, symAm);
    return static_cast<double>(
        static_cast<long long int>(d * symAm)
    ) / symAm;
}

}
#endif
