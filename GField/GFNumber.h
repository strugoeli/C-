
#ifndef CPP_EX1_GFNUMBER_H
#define CPP_EX1_GFNUMBER_H

static const int RHO_FAILED = -1;

static const int EXTENDING_FACTOR = 2;

static const int DEFAULT_CAPACITY = 2;

static const int DEFAULT_ARRAY_LENGTH = 0;

static const int EMPTY = 0;

static const int DEFAULT_VALUE = 0;

static const int COPRIME_INTEGERS_GCD = 1;

#include "GField.h"
#include <iostream>

/**
 *This class represents a number which is a member of Galua field
 */
class GFNumber
{
private:
    long value;

    GField field;

    long _trailDev(long n) const;

    /**
    * This method use Indeterminism to calculate a factor of the given number
    *(not necessarily prime factor)
    * @param n - GFNumber with the same field of this number
    * @return - Factor of the given number if succeed and -1 otherwise
    */
    long _pollardRho(GFNumber n) const;

    /**
    *This method sample with discrete uniform distribution a number between 1 to n-1 (pseudo random)
    * @param n - Natural number
    * @return - member of [n-1]
    */
    long _getRand(long n) const;

    /**
    *This function is given a member of Zn x and calculates x^2+1 (mod(n))
    * @param x- member of Zn
    * @param n - natural number
    * @return - x^2 + 1 mod(n)
    */
    static long _f(long x, long n);

    /**
     *
     * @param a -Integer
     * @param b - Integer
     * @return modulo of a and b ( considering the cast of negative numbers)
     */
    static long _mod(long a, long b)
    { return (a % b + b) % b; }

    /**
    *This method is given an array and a given size and creates a copy of the given array to a new array with size'
    * with size' =size * FACTOR
    * @param size - size of the given array
    * @param arr- array of GFNumbers
    * @return - resized array
    */
    static GFNumber *_reSizeArray(int *size, GFNumber *arr);

    /**
     *
     * @return True if the number is even and false otherwise
     */
    bool _isEven()
    { return value % 2 == 0; }

    /**
     * @param k GFNumber
     * @return gcd(this number,k)
     */
    GFNumber _gcd(const GFNumber &k)
    { return field.gcd(*this, k); }


public:
    /**
    * Default constructor : default value which member of Galua field of default order
    */
    GFNumber();

    /**
    * Constructor 1 - creates a member of a given Galua field  of order 2 s.t the given number and the member are
    * equivalent mod(order)
    * @param num - Integer
    */
    GFNumber(long num);

    /**
    * Constructor 2 - creates a member of a given Galua field s.t the given number and the member are
    * equivalent mod( order of the given field)
    * @param num - Integer
    * @param f - reference to a finite field
    */

    GFNumber(long num, const GField &s);

    /**
     *Copy Constructor
     * @param other
     */
    GFNumber(const GFNumber &other);

    /**
     *Destructor
     */
    ~GFNumber();

    /**
     *
     * @return number's value
     */
    long getNumber() const
    { return value; }

    /**
     *
     * @return number's field
     */
    GField getField() const
    { return field; }

    /**
     *
     * @return true if the number is prime false otherwise
     */
    bool getIsPrime() const;

    /**
    * This method prints the the number's prime factors(not necessarily distinct)
    */
    void printFactors() const;

    /**
    * This method create a list of the number's prime factors( not necessarily distinct),
    * and updates the length of the list respectively
    * @param len- The current length of the prime factors list
    * @return list of the number's prime factors
    */
    GFNumber *getPrimeFactors(int *len) const;

    /**
     *Overloads the * operator
     * @param other
     * @return
     */
    GFNumber &operator=(const GFNumber &other);

    /**
     *Overloads the = operator
     * @param other
     * @return
     */
    GFNumber operator+(const GFNumber &other);

    /**
     *Overloads the + operator
     * @param other
     * @return
     */
    GFNumber &operator+=(const GFNumber &other);

    /**
     *Overloads the - operator
     * @param other
     * @return
     */
    GFNumber operator-(const GFNumber &other);

    /**
     *Overloads the -= operator
     * @param other
     * @return
     */
    GFNumber &operator-=(const GFNumber &other);

    /**
     *Overloads the * operator
     * @param other
     * @return
     */
    GFNumber operator*(const GFNumber &other);

    /**
     *Overloads the * operator
     * @param other
     * @return
     */
    GFNumber &operator*=(const GFNumber &other);

    /**
     *Overloads the *= operator
     * @param other
     * @return
     */
    GFNumber operator%(const GFNumber &other);

    /**
     *Overloads the %= operator
     * @param other
     * @return
     */
    GFNumber &operator%=(const GFNumber &other);

    /**
     *Overloads the == operator
     * @param other
     * @return
     */
    bool operator==(const GFNumber &other) const;

    /**
     *Overloads the != operator
     * @param other
     * @return
     */
    bool operator!=(const GFNumber &other) const;

    /**
     *Overloads the < operator
     * @param other
     * @return
     */
    bool operator<(const GFNumber &other) const;

    /**
     *Overloads the <= operator
     * @param other
     * @return
     */
    bool operator<=(const GFNumber &other) const;

    /**
     *Overloads the > operator
     * @param other
     * @return
     */
    bool operator>(const GFNumber &other) const;

    /**
     *Overloads the >= operator
     * @param other
     * @return
     */
    bool operator>=(const GFNumber &other) const;

    /**
     *Overloads the << operator
     * @param stream
     * @param num
     * @return
     */
    friend std::ostream &operator<<(std::ostream &stream, const GFNumber &num);

    /**
     *Overloads the >> operator
     * @param in
     * @param num
     * @return
     */
    friend std::istream &operator>>(std::istream &in, GFNumber &num);

    /**
     *Overloads the = operator
     * @param rNum
     * @return
     */
    GFNumber &operator=(const long &rNum);

    /**
     *Overloads the + operator
     * @param rNum
     * @return
     */
    GFNumber operator+(const long &rNum);

    /**
     *Overloads the += operator
     * @param rNum
     * @return
     */
    GFNumber &operator+=(const long &rNum);

    /**
     *Overloads the - operator
     * @param rNum
     * @return
     */
    GFNumber operator-(const long &rNum);

    /**
     *Overloads the -= operator
     * @param rNum
     * @return
     */
    GFNumber &operator-=(const long &rNum);

    /**
     *Overloads the * operator
     * @param rNum
     * @return
     */
    GFNumber operator*(const long &rNum);

    /**
     *Overloads the % operator
     * @param rNum
     * @return
     */
    GFNumber &operator*=(const long &rNum);

    /**
     *Overloads the * operator
     * @param rNum
     * @return
     */
    GFNumber operator%(const long &rNum);

    /**
     *Overloads the %= operator
     * @param rNum
     * @return
     */
    GFNumber &operator%=(const long &rNum);

};

#endif