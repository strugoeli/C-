#include <iostream>
#include <vector>
#include <fstream>
#include "Fractal.h"

static const char SEPARATOR = ',';

static const int FORMAT_LENGTH = 3;

static const int NUM_OF_ARGS = 2;

/**
 *This function is given a message, prints it and exits the program
 * @param msg - Informative message
 */
void throwFailure(const std::string &msg)
{
    std::cerr << msg;
    exit(EXIT_FAILURE);
}

/**
 * This function is given a vector of fractals.
 * the function prints the last fractal in the vector till it's empty
 * @param vecFractals - vector of unique pointers to Fractal
 */
void printOutput(std::vector<std::unique_ptr<Fractal>> &vecFractals)
{
    while (!vecFractals.empty())
    {
        vecFractals.back()->drawFractal();
        vecFractals.pop_back();
        std::cout << "\n";
    }
}

/**
 *This function is given reference to input stream and a string, going over the characters
 * within the stream one by one the and adding to given string (which being cleared at first),
 * the content without unwanted characters
 * @param iStream - input stream
 * @param line - string
 * @return The given stream
 */
std::istream &getLine(std::istream &iStream, std::string &line)
{
    line.clear();
    std::istream::sentry se(iStream, true);
    std::streambuf *pStreamBuf = iStream.rdbuf();

    while (true)
    {
        char currentChar = static_cast<char>(pStreamBuf->sbumpc());
        switch (currentChar)
        {
            case '\n':
                return iStream;

            case '\r':

                if (pStreamBuf->sgetc() == '\n')
                {
                    pStreamBuf->sbumpc();
                }
                return iStream;

            case std::streambuf::traits_type::eof():
                if (line.empty())
                {
                    iStream.setstate(std::ios::eofbit);
                }
                return iStream;

            default:
                line += currentChar;
        }
    }
}

/**
 * Main function: the Main is given a path to a file checks that the file is in the
 * right csv format and contains the relevant data for creating fractals by there types and
 * dimension and prints the fractals in the reverse order from there appearance in the file
 */
int main(int argc, char *argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        throwFailure(USAGE_MAG);
    }
    std::ifstream inFile(argv[1]);
    std::string currLine;
    std::vector<std::unique_ptr<Fractal>> vecFractals;
    std::unique_ptr<Fractal> fractal;

    if (!inFile.is_open())
    {
        throwFailure(INVALID_INPUT_MSG);
    }
    while (!getLine(inFile, currLine).eof())
    {
        if (currLine.length() != FORMAT_LENGTH or currLine[1] != SEPARATOR)
        {
            throwFailure(INVALID_INPUT_MSG);
        }
        fractal = FractalFactory::selectFractal(currLine);
        vecFractals.push_back(std::move(fractal));
    }
    printOutput(vecFractals);
    return 0;
}


