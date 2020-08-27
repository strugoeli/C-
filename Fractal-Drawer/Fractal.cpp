#include "Fractal.h"

/**
 * This Constructor creates Fractal object with the given dimension
 * @param dim - dimension of the fractal (Integer)
 */
Fractal::Fractal(int n)
{
    if (n < MIN_DIM or n > MAX_DIM)
    {
        std::cerr << INVALID_INPUT_MSG;
        exit(EXIT_FAILURE);
    }
    _dim = n;
}

/**
 * Destructor
 */
Fractal::~Fractal()
= default;

/**
 * This method prints the fractal in ASCII art
 */
void Fractal::drawFractal() const
{
    int size = static_cast<int>(pow(_getDimFactor(), _dim));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << (isInFractal(i, j) ? MARKED_CELL : EMPTY_CELL);
        }
        std::cout << "\n";
    }
}

/**
 *This method checks recursively (by the description of the fractals which given in the exercise),
 * if the given cell (i,j) has to be marked or not
 * @param i -  represent index of a row in fractal matrix
 * @param j  -  represent index of a row in fractal matrix
 * @return True if the cell (i,j) has to be marked in this fractal and false otherwise
 */

bool Fractal::isInFractal(int i, int j) const
{
    if (i == 0 and j == 0)
    {
        return true;
    }
    if (_isEmptyCell(i, j))
    {
        return false;
    }
    return isInFractal(i / _getDimFactor(), j / _getDimFactor());
}

/**
 * This method is given a string that contains the commands for creating a fractal creates
 * a unique pointer to Fractal object according to the given commands
 * @param fractalCmd - string in csv format that contains the commands that determines the
 * fractal condition
 * @return unique pointer to the appropriate Fractal object that fits to the type in the
 * given commands
 */
std::unique_ptr<Fractal> FractalFactory::selectFractal(std::string fractalCmd)
{
    int dim, type;
    type = fractalCmd[0] - '0';
    dim = fractalCmd[2] - '0';
    std::unique_ptr<Fractal> fractal;
    switch (type)
    {
        case SIERPINSKI_CARPET :
            fractal = std::make_unique<SierpinskiCarpet>(dim);
            break;
        case SIERPINSKI_SIEVE :
            fractal = std::make_unique<SierpinskiSieve>(dim);
            break;
        case CANTOR_DUST :
            fractal = std::make_unique<CantorDust>(dim);
            break;
        default:
            std::cerr << INVALID_INPUT_MSG;
            exit(EXIT_FAILURE);
    }
    return fractal;
}
