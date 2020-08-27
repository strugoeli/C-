
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <random>
#include "GFNumber.h"


/**
 * Default constructor : default value which member of Galua field of default order
 */
GFNumber::GFNumber()
{
    field = GField();
    value = DEFAULT_VALUE;
}

/**
 * Constructor 2 - creates a member of a given Galua field s.t the given number and the member are
 * equivalent mod( order of the given field)
 * @param num - Integer
 * @param f - reference to a finite field
 */
GFNumber::GFNumber(long num, const GField &f)
{
    field = GField(f);
    value = _mod(num, field.getOrder());
}

/**
 * Constructor 1 - creates a member of a given Galua field  of order 2 s.t the given number and the member are
 * equivalent mod(order)
 * @param num - Integer
 */
GFNumber::GFNumber(long num)
{
    field = GField();
    value = _mod(num, field.getOrder());
}

/**
 * Destructor
 */
GFNumber::~GFNumber()
= default;


/** Copy Constructor
 * @param other - Field to copy
 */
GFNumber::GFNumber(const GFNumber &other)
{
    field = GField(other.field);
    value = _mod(other.getNumber(), field.getOrder());
}

/**
 * This method prints the the number's prime factors(not necessarily distinct)
 */
void GFNumber::printFactors() const
{
    int len = DEFAULT_ARRAY_LENGTH;
    GFNumber *factors = getPrimeFactors(&len);
    if (len == EMPTY)
    {
        std::cout << value << "=" << value << "*1\n";
    }
    else
    {
        std::cout << value << "=";
        for (int i = 0; i < len; i++)
        {
            std::cout << factors[i].value;
            if (i != len - 1)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << "\n";
            }
        }
    }
    delete[] factors;
}

/**
 * This method create a list of the number's prime factors( not necessarily distinct),
 * and updates the length of the list respectively
 * @param len- The current length of the prime factors list
 * @return list of the number's prime factors
 */
GFNumber *GFNumber::getPrimeFactors(int *len) const
{
    if (getIsPrime())
    {
        return {};
    }
    int size = DEFAULT_CAPACITY;
    auto *factors = new GFNumber[size];
    GFNumber r = GFNumber(*this);
    long p;

    while (r.getNumber() != 1 and r.getNumber() != 0)
    {
        p = _pollardRho(r);

        while (!GField::isPrime(p))
        {
            if (p == RHO_FAILED)
            {
                p = _trailDev(r.getNumber());
            }
            else
            {
                p = _pollardRho(GFNumber(p, field));
            }
        }
        if (size == *len)
        {
            factors = _reSizeArray(&size, factors);
        }
        factors[*len] = field.createNumber(p);
        r = field.createNumber(r.getNumber() / p);
        *len += 1;
    }
    return factors;
}

/**
 *This method is given an array and a given size and creates a copy of the given array to a new array with size'
 * with size' =size * FACTOR
 * @param size - size of the given array
 * @param arr- array of GFNumbers
 * @return - resized array
 */
GFNumber *GFNumber::_reSizeArray(int *size, GFNumber *arr)
{
    int newSize = *size * EXTENDING_FACTOR;
    auto *newArr = new GFNumber[newSize];

    for (int i = 0; i < *size; i++)
    {
        newArr[i] = arr[i];
    }
    *size = newSize;
    delete[] arr;
    arr = newArr;
    return arr;
}

/**
 * This method use Indeterminism to calculate a factor of the given number
 *(not necessarily prime factor)
 * @param n - GFNumber with the same field of this number
 * @return - Factor of the given number if succeed and -1 otherwise
 */
long GFNumber::_pollardRho(GFNumber n) const
{

    if (n.getNumber() == 1)
    { return n.getNumber(); }

    if (n._isEven())
    { return 2; }

    long x, y, d, nVal;
    nVal = n.getNumber();
    y = x = _getRand(n.getNumber());
    d = COPRIME_INTEGERS_GCD;
    GFNumber t;

    while (d == COPRIME_INTEGERS_GCD)
    {
        x = _f(x, nVal);
        y = _f(_f(y, nVal), nVal);
        t = n.getField().createNumber(labs(x - y));
        d = n._gcd(t).getNumber();

        if (d == nVal)
        {
            return RHO_FAILED;
        }
    }
    return d;
}

/**
 *This function is given a member of Zn x and calculates x^2+1 (mod(n))
 * @param x- member of Zn
 * @param n - natural number
 * @return - x^2 + 1 mod(n)
 */
long GFNumber::_f(long x, long n)
{
    return _mod(x * x + 1, n);
}

/**
 *This method using ‫‪Trail‬‬ ‫‪Division‬‬ to calculate a prime factor of the number
 * by iterating from the min odd positive prime number to root square of n
 * and returns the first number that divides n
 * @param n - Integer
 * @return factor of n (or itself)
 */
long GFNumber::_trailDev(long n) const
{
    int i = 3;
    while (i <= sqrt(n))
    {
        if (n % i == 0)
        {
            return i;
        }
        i++;
    }
    return n;
}

/**
 *This method sample with discrete uniform distribution a number between 1 to n-1 (pseudo random)
 * @param n - Natural number
 * @return - member of [n-1]
 */
long GFNumber::_getRand(long n) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dis(1, n - 1);
    return dis(gen);
}

/**
 *
 * @return true if the number is prime and false otherwise
 */
bool GFNumber::getIsPrime() const
{
    return GField::isPrime(value);
}



//---------------------OPERATORS-------------------//

/**
 *Overloads the = operator
 * @param other
 * @return
 */
GFNumber &GFNumber::operator=(const GFNumber &other)
{
    value = other.value;
    field = other.field;
    return *this;
}

/**
 *Overloads the + operator
 * @param other
 * @return
 */
GFNumber GFNumber::operator+(const GFNumber &other)
{
    assert(field == other.field);
    long val = _mod(value + other.value, field.getOrder());
    return GFNumber(val, field);
}

/**
 *Overloads the += operator
 * @param other
 * @return
 */
GFNumber &GFNumber::operator+=(const GFNumber &other)
{
    *this = *this + other;
    return *this;
}

/**
 *Overloads the - operator
 * @param other
 * @return
 */
GFNumber GFNumber::operator-(const GFNumber &other)
{
    assert(field == other.field);
    long val = _mod(value - other.value, field.getOrder());
    return GFNumber(val, field);
}

/**
 *Overloads the -= operator
 * @param other
 * @return
 */
GFNumber &GFNumber::operator-=(const GFNumber &other)
{
    *this = *this - other;
    return *this;
}

/**
 *Overloads the * operator
 * @param other
 * @return
 */
GFNumber GFNumber::operator*(const GFNumber &other)
{
    assert(field == other.field);
    long val = _mod(value * other.getNumber(), field.getOrder());
    return GFNumber(val, field);
}

/**
 *Overloads the *= operator
 * @param other
 * @return
 */
GFNumber &GFNumber::operator*=(const GFNumber &other)
{
    *this = *this * other;
    return *this;
}

/**
 *Overloads the % operator
 * @param other
 * @return
 */
GFNumber GFNumber::operator%(const GFNumber &other)
{
    assert(field == other.field);
    long val = value % other.value;
    return GFNumber(val, field);
}

/**
 *Overloads the %= operator
 * @param other
 * @return
 */
GFNumber &GFNumber::operator%=(const GFNumber &other)
{
    *this = *this % other;
    return *this;
}

/**
 *Overloads the == operator
 * @param other
 * @return
 */
bool GFNumber::operator==(const GFNumber &other) const
{
    return value == other.value and field == other.getField();
}

/**
 *Overloads the != operator
 * @param other
 * @return
 */
bool GFNumber::operator!=(const GFNumber &other) const
{
    return !(*this == other);
}

/**
 *Overloads the > operator
 * @param other
 * @return
 */
bool GFNumber::operator>(const GFNumber &other) const
{
    assert(field == other.field);
    return value > other.value;
}

/**
 *Overloads the <= operator
 * @param other
 * @return
 */
bool GFNumber::operator<=(const GFNumber &other) const
{
    return !(*this > other);
}

/**
 *Overloads the < operator
 * @param other
 * @return
 */
bool GFNumber::operator<(const GFNumber &other) const
{
    assert(field == other.field);
    return value < other.value;
}

/**
 *Overloads the >= operator
 * @param other
 * @return
 */
bool GFNumber::operator>=(const GFNumber &other) const
{
    return !(*this < other);
}

/**
 *Overloads the << operator
 * @param stream
 * @param num
 * @return
 */
std::ostream &operator<<(std::ostream &stream, const GFNumber &num)
{
    stream << num.value << " " << num.field;
    return stream;
}

/**
 *Overloads the >> operator
 * @param in
 * @param num
 * @return
 */
std::istream &operator>>(std::istream &in, GFNumber &num)
{
    in >> num.value >> num.field;
    assert(!in.fail());
    num %= num.field.getOrder();

    return in;
}

/**
 *Overloads the + operator
 * @param rNum
 * @return
 */
GFNumber GFNumber::operator+(const long &rNum)
{
    long val = _mod((value + rNum), field.getOrder());
    return GFNumber(val, field);
}

/**
 *Overloads the += operator
 * @param rNum
 * @return
 */
GFNumber &GFNumber::operator+=(const long &rNum)
{
    *this = *this + rNum;
    return *this;
}

/**
 *Overloads the - operator
 * @param rNum
 * @return
 */
GFNumber GFNumber::operator-(const long &rNum)
{
    long val = _mod(value - rNum, field.getOrder());
    return GFNumber(val, field);
}

/**
 *Overloads the -= operator
 * @param rNum
 * @return
 */
GFNumber &GFNumber::operator-=(const long &rNum)
{
    *this = *this - rNum;
    return *this;
}

/**
 *Overloads the * operator
 * @param rNum
 * @return
 */
GFNumber GFNumber::operator*(const long &rNum)
{
    long val = _mod(value * rNum, field.getOrder());
    return GFNumber(val, field);
}

/**
 *Overloads the *= operator with respect to long
 * @param rNum
 * @return
 */
GFNumber &GFNumber::operator*=(const long &rNum)
{
    *this = *this * rNum;
    return *this;
}

/**
 *Overloads the % operator with respect to long
 * @param rNum
 * @return
 */
GFNumber GFNumber::operator%(const long &rNum)
{
    long val = _mod(rNum, field.getOrder());
    if (val == 0)
    {
        val = _mod(value, rNum);
    }
    else
    {
        val = _mod(value, val);
    }
    return GFNumber(val, field);
}

/**
 *Overloads the %= operator with respect to long
 * @param rNum
 * @return
 */
GFNumber &GFNumber::operator%=(const long &rNum)
{
    *this = *this % rNum;
    return *this;
}

/**
 *Overloads the = operator with respect to long
 * @param rNum
 * @return
 */
GFNumber &GFNumber::operator=(const long &rNum)
{
    value = _mod(rNum, field.getOrder());
    field = GField();
    return *this;
}
