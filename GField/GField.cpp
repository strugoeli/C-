
#include <cmath>
#include "GField.h"
#include "GFNumber.h"

/**
 * Constructor default
 */
GField::GField() : p(DEFALUT_CHAR), l(DEFAULT_DEG)
{}

/**
 * Constructor 1 - Creating Galua field with given characteristic and default degree
 * @param p_char
 */
GField::GField(long p_char) : p(labs(p_char)), l(DEFAULT_DEG)
{
    assert(0 < l and isPrime(p));
}

/**
 * Constructor 2 - Creating Galua field with given characteristic and given degree
 * @param p_char - Integer bigger than 1
 * @param l_degree - Integer bigger than 0
 */

GField::GField(long p_char, long l_deg) : p(labs(p_char)), l(l_deg)
{
    assert(0 < l and isPrime(p));
}

/**
 * Copy Constructor
 * @param other
 */
GField::GField(const GField &other) : p(other.p), l(other.l)
{
    assert(0 < l and isPrime(p));
}


/**
 *This method is given an number (Integer) and returns true if the number is prime and false otherwise
 * @param p - Integer number
 * @return true if p is prime and false otherwise
 */
bool GField::isPrime(long p)
{
    long n = labs(p);
    if (n == 2)
    {
        return true;
    }
    else if (n % 2 == 0 or n < 2)
    {
        return false;
    }
    else
    {
        for (int i = 3; i <= sqrt(n); i += 2)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}

/**
 * This method is given two number which belong to field (a^2 + b^2 > 0), and finds calculates there gcd
 * @param a - member of the field
 * @param b - member of the field
 * @return Greatest common divisor of the given numbers
 */
GFNumber GField::gcd(GFNumber a, GFNumber b) const
{
//    assert(a.getNumber() != 0 or b.getNumber() != 0);
//    assert(a.getField() == b.getField());
    if (b.getNumber() == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

/**
 * This method is given an integer and creates a member of the field with a value which equivalent to the given
 * value modulo the order of the field
 * @param k - Integer
 * @return member of the field m s.t m=k (mod(order))
 */
GFNumber GField::createNumber(long k) const
{
    return GFNumber(k % getOrder(), *this);
}


/**
 * Overloads the operator =
 * @param other - Galua field defined by his char and degree
 * @return reference to the field
 */
GField &GField::operator=(const GField &other)
{
    p = other.p;
    l = other.l;
    return *this;
}

/**
 *Overloads the operator >>
 * @param in - input stream
 * @param field - The field which the date flows into
 * @return the given input stream
 */
std::istream &operator>>(std::istream &in, GField &field)
{
    in >> field.p >> field.l;
    field.p = labs(field.p);
    assert(!in.fail() and field.isPrime(field.p));
    return in;
}

/**
 *Overloads the operator <<
 * @param stream output stream
 * @param field - The field which the date flows from
 * @return The given output stream
 */
std::ostream &operator<<(std::ostream &stream, const GField &field)
{
    stream << "GF(" << field.p << "**" << field.l << ")";
    return stream;
}

/**
 *Calculates the order of the field
 * @return The order of the field
 */
long GField::getOrder() const
{
    { return static_cast<long>(std::pow(p, l)); }
}
