
#include <iostream>
#include <cassert>

#ifndef CPP_EX1_GFIELD_H
#define CPP_EX1_GFIELD_H

static const int DEFALUT_CHAR = 2;
static const int DEFAULT_DEG = 1;


class GFNumber;

/**
 *This Class represents Galua field
 */
class GField
{

public:

    /**
     * Default constructor;
     */
    GField();

    /**
 * Constructor 1 - Creating Galua field with given characteristic and default degree
 * @param p
 */
    GField(long p);

    /**
    * Constructor 2 - Creating Galua field with given characteristic and given degree
    * @param p - Integer bigger than 1
    * @param l - Integer bigger than 0
    */
    GField(long p, long l);

    /**
   * Copy Constructor
   * @param other
   */
    GField(const GField &other);

    /**
     *
     * @return Field characteristic
     */
    long getChar() const
    { return p; }

    /**
     *
     * @return Field degree
     */
    long getDegree() const
    { return l; }

    /**
    *Calculates the order of the field
    * @return The order of the field
    */
    long getOrder() const;


    /**
    *This method is given an number (Integer) and returns true if the number is prime and false otherwise
    * @param p - Integer number
    * @return true if p is prime and false otherwise
    */
    static bool isPrime(long p);

    /**
    * Overloads the operator =
    *  @param other - Galua field defined by his char and degree
    * @return reference to the field
    */
    GField &operator=(const GField &other);

    /**
     *
     * @param other Galua field
     * @return
     */
    bool operator==(const GField &other) const
    { return p == other.p && l == other.l; }

    /**
     *
     * @param other Galua field
     * @return
     */
    bool operator!=(const GField &other) const
    { return !(*this == other); }


    /**
    *Overloads the operator >>
    * @param in - input stream
    * @param field - The field which the date flows into
    * @return the given input stream
    */
    friend std::istream &operator>>(std::istream &in, GField &field);

    /**
     *Overloads the operator <<
    * @param stream output stream
    * @param field - The field which the date flows from
    * @return The given output stream
    */
    friend std::ostream &operator<<(std::ostream &stream, const GField &field);

    /**
    * This method is given an integer and creates a member of the field with a value which equivalent to the given
    * value modulo the order of the field
     * @param k - Integer
    * @return member of the field m s.t m=k (mod(order))
    */
    GFNumber createNumber(long k) const;

    /**
    * This method is given two number which belong to field (a^2 + b^2 > 0), and finds calculates there gcd
    * @param a - member of the field
    * @param b - member of the field
    * @return Greatest common divisor of the given numbers
    */
    GFNumber gcd(GFNumber a, GFNumber b) const;


private:
    /**
     *  p - characteristic
     *  l - degree
     */
    long p, l;

};

#endif
