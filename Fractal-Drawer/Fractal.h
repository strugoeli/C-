
#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

#include <iostream>

#include <cmath>

#include <boost/algorithm/string.hpp>

static const int SIERPINSKI_CARPET = 1;

static const int SIERPINSKI_SIEVE = 2;

static const int CANTOR_DUST = 3;

static const char *const INVALID_INPUT_MSG = "Invalid input\n";

static const char *const USAGE_MAG = "Usage: FractalDrawer <file path>\n";

static const int DIMENSION_DEFAULT_VALUE = 1;

static const int SIERPINSKI_CARPET_DIM_FACTOR = 3;

static const int SIERPINSKI_SIEVE_DIM_FACTOR = 2;

static const int CANTOR_DUST_DIM_FACTOR = 3;

static const int MIN_DIM = 1;

static const int MAX_DIM = 6;

static const char *const MARKED_CELL = "#";

static const char *const EMPTY_CELL = " ";

/**
 * This class represents a general abstract Fractal
 */

class Fractal
{
public:

    /**
    * Default Constructor
    */
    Fractal() : _dim(DIMENSION_DEFAULT_VALUE)
    {}

    /**
     * This Constructor creates Fractal object with the given dimension
     * @param dim - dimension of the fractal (Integer)
     */
    explicit Fractal(int n);

    /**
     * Destructor
     */
    virtual ~Fractal() = 0;

    /**
     * This method prints the fractal in ASCII art
     */
    void drawFractal() const;

protected:
    /**
     * Fractal's dimension
     */
    int _dim;


    /**
     * @param i - represent index of a row in fractal matrix
     * @param j - represent index of a row in fractal matrix
     * @return True if the cell (i,j) has to be marked in this fractal matrix
     *  and false otherwise
     */
    bool isInFractal(int i, int j) const;

    /**
    * @param i - represent index of a row in fractal matrix
    * @param j - represent index of a row in fractal matrix
    * @return True if the cell (i,j) has to be empty in this fractal matrix
    * and false otherwise
    */
    virtual bool _isEmptyCell(int i, int j) const = 0;

    /**
     * @return The class dim factor
     */
    virtual int _getDimFactor() const = 0;

};


/**
 * This class represents a Sierpinski Carpet Fractal
 */
class SierpinskiCarpet : public Fractal
{
    static const int _dimFactor = SIERPINSKI_CARPET_DIM_FACTOR;

public:
    /**
     * Default Constructor
     */
    SierpinskiCarpet() : Fractal()
    {}

    /**
   * This Constructor creates Sierpinski Carpet object with the given dimension
   * @param dim - dimension of the fractal (Integer)
   */
    explicit SierpinskiCarpet(int dim) : Fractal(dim)
    {}

    /**
     * Copy Constructor
     */
    SierpinskiCarpet(SierpinskiCarpet & other) = default;

    /**
     * Move Constructor
     */
    SierpinskiCarpet(SierpinskiCarpet && other) = default;

    /**
     * Destructor
     */
    ~SierpinskiCarpet() override = default;

    /**
    * Copy assignment operator overload (Default)
    */
    SierpinskiCarpet & operator=(const SierpinskiCarpet & other) = default;

    /**
    * Move assignment operator overload (Default)
    */
    SierpinskiCarpet & operator=(SierpinskiCarpet && other) = default;

private:

    bool _isEmptyCell(int i, int j) const override
    { return i % _dimFactor == 1 and j % _dimFactor == 1; }


    int _getDimFactor() const override
    { return SierpinskiCarpet::_dimFactor; }

};


/**
 * This class represents a Sierpinski Sieve Fractal
 */
class SierpinskiSieve : public Fractal
{
    static const int _dimFactor = SIERPINSKI_SIEVE_DIM_FACTOR;

public:
    /**
     * Default Constructor
     */
    SierpinskiSieve() : Fractal()
    {}

    /**
    * This Constructor creates Sierpinski Sieve object with the given dimension
    * @param dim - dimension of the fractal (Integer)
    */
    explicit SierpinskiSieve(int dim) : Fractal(dim)
    {}

    /**
     * Copy Constructor
     * @param other
     */
    SierpinskiSieve(SierpinskiSieve & other) = default;

    /**
     * Move Constructor
     * @param other
     */
    SierpinskiSieve(SierpinskiSieve && other) = default;

    /**
     * Destructor
     */
    ~SierpinskiSieve() override = default;

    /**
    * Copy assignment operator overload (Default)
    */
    SierpinskiSieve & operator=(const SierpinskiSieve & other) = default;

    /**
    * Move assignment operator overload (Default)
    */
    SierpinskiSieve & operator=(SierpinskiSieve && other) = default;

private:

    bool _isEmptyCell(int i, int j) const override
    { return i % _dimFactor == 1 and j % _dimFactor == 1; }

    int _getDimFactor() const override
    { return SierpinskiSieve::_dimFactor; }
};

/**
 * Cantor Dust Fractal
 */
class CantorDust : public Fractal
{
    static const int _dimFactor = CANTOR_DUST_DIM_FACTOR;

public:
    /**
     * Default Constructor
     */
    CantorDust() : Fractal()
    {}

    /**
     * This Constructor creates CantorDust object with the given dimension
     * @param dim - dimension of the fractal (Integer)
     */
    explicit CantorDust(int dim) : Fractal(dim)
    {}

    /**
     * Copy Constructor
     */
    CantorDust(CantorDust & other) = default;

    /**
     * Move constructor
     */
    CantorDust(CantorDust && other) = default;

    /**
     * Destructor
     */
    ~CantorDust() override = default;

    /**
     * Copy assignment operator overload (Default)
     */
    CantorDust & operator=(const CantorDust & other) = default;

    /**
     * Move assignment operator overload (Default)
     */
    CantorDust & operator=(CantorDust && other) = default;


private:

    bool _isEmptyCell(int i, int j) const override
    { return i % 2 != 0 or j % _dimFactor == 1; }

    int _getDimFactor() const override
    { return CantorDust::_dimFactor; }
};

/**
* This class represents a Fractal Factory that creates Fractal(pointers to) Objects
*/
class FractalFactory
{
public:

    /**
     * This method is given a string that contains the commands for creating a fractal creates
     * a unique pointer to Fractal object according to the given commands
     * @param fractalCmd - string in csv format that contains the commands that determines the
     * fractal condition
     * @return unique pointer to the appropriate Fractal object that fits to the type in the
     * given commands
     */
    static std::unique_ptr<Fractal> selectFractal(std::string fractalCmd);

private:
    /**
     * Default Constructor
     */
    FractalFactory() = default;

    /**
     * Copy Constructor
     */
    FractalFactory(const FractalFactory & other) = default;

    /**
     * Move Constructor
     */
    FractalFactory(FractalFactory && other) = default;

    /**
     * Copy assignment operator overload (Default)
     */
    FractalFactory & operator=(const FractalFactory & other) = default;

    /**
     * Move assignment operator overload (Default)
     */
    FractalFactory & operator=(FractalFactory && other) = default;

    /**
     * Destructor
     */
    ~FractalFactory() = default;
};

#endif
