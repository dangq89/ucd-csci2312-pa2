//
// Created by Quang Dang on 2/17/16.
//

#include "Point.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>


using namespace std;
using namespace Clustering;

namespace Clustering {

    unsigned int Point::__idGen = 0;

    Point::Point(int __i) {
        __id = __idGen++;
        __dim = __i;
        __values = new double[__dim];

        for (int i = 0; i < __dim; i++) {
            __values[i] = 0;
        };
    }

    Point::Point(int __i, double *__v) {
        __dim = __i;
        __values = __v;
        __id = __idGen++;
    }

    Point::Point(const Point &p) {  //copy constructor
        __id = p.__id;
        __dim = p.__dim;
        __values = new double[__dim];

        for (int i = 0; i <= p.__dim; i++) {
            __values[i] = p.__values[i];
        };
    }

    Point &Point::operator=(const Point &rhs) {   //overloaded assignment operator
        __id = __idGen++;
        __dim = rhs.__dim;

        for (int i = 0; i < rhs.__dim; i++) {
            __values[i] = rhs.__values[i];
        };
        return (Point &) rhs;
    }

    Point::~Point() {
    }

    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int a, double b) {
        __values[a] = b;
    }

    double Point::getValue(int a) const {
        return __values[a];
    }

    double Point::distanceTo(const Point &p) const {
        if(__dim != p.__dim)
            return false;

        double sum_Products = 0;

        for (int i = 0; i < __dim; i++) {
            sum_Products += pow(p.getValue(i) - getValue(i), 2);
        }
        return sqrt(sum_Products);
    }

    // Overloaded operators
    // Members
    Point &Point::operator*=(double rhs) {
        for (int i = 0; i < __dim; i++)
            __values[i] *= rhs;
        return *this;

    }

    Point &Point::operator/=(double d) {
        for (int i =0; i < __dim; i++)
            __values[i] /= d;
        return *this;
    }

    const Point Point::operator*(double d) const {
        return Point(*this) *= d;
    }

    const Point Point::operator/(double d) const {
        return Point(*this) /= d;
    }

    double &Point::operator[](int index) {
        return __values[index];
    }

    // Friends
    Point &operator+=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs) {
            for (int i = 0; i < lhs.__dim; i++) {
                lhs.__values[i] += rhs.__values[i];
            }
        }
        else if (lhs.__dim == rhs.__dim) {
            for (int i =0; i < lhs.__dim; i++)
                lhs.__values[i] += rhs.__values[i];
        }
        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs) {
            for (int i = 0; i < lhs.__dim; i++) {
                lhs.__values[i] = 0;
            }
        }
        else if (lhs.__dim == rhs.__dim) {
            for (int i =0; i < lhs.__dim; i++)
                lhs.__values[i] -= rhs.__values[i];
        }
        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs) {
        Point p(lhs);
        return p += rhs;
    }

    const Point operator-(const Point &lhs, const Point &rhs) {
        Point p(lhs);
        return p -= rhs;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Point &lhs, const Point &rhs) {
        return !operator==(lhs, rhs);
    }

    bool operator<(const Point &lhs, const Point &rhs) {

        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {
                return (lhs.__values[i] < rhs.__values[i]);
            }
        }
        return false;
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        return operator<(rhs, lhs);
    }


    bool operator<=(const Point &lhs, const Point &rhs) {
        return !operator>(lhs, rhs);
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        return !operator <(lhs, rhs);
    }

    std::ostream &operator<<(std::ostream &os, const Point &p) {
        for (int i = 0; i < p.__dim; i++) {
            os << p.__values[i];
            if (i != p.__dim - 1) {
                os << ", ";
            }
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Point &p) {
        double d;
        std::string value;
        std::stringstream formatNum;
        formatNum.setf(std::ios::fixed);
        const char delim = ',';

        int i = 0;
        while (std::getline(is, value, delim)) {
            d = std::stod(value);
            formatNum.precision(20);
            formatNum << d;
            formatNum >> d;
            p.__values[i++] = d;
        }
        return is;
    }
}