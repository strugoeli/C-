#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "HashMap.hpp"

static const char SEPARATOR = ',';

static const int NUM_OF_ARGS = 4;

static const int BEFORE_SEPARATOR = 0;

static const int MAX_SEPARATOR_NUM = 1;

static const char *const SPAM_MSG = "SPAM\n";

static const char *const NOT_SPAM_MSG = "NOT_SPAM\n";

static const int MIN_THRESHOLD = 1;


static const char *const BAD_ALLOC_MSG = "Memory allocation failed\n";

/**
 *This method is given an error message and prints it to cerr
 * @param msg - Error message
 */
void printErrorMsg(const std::string & msg)
{
    std::cerr << msg;
}

/**
 *This function is given reference to input stream and a string, going over the characters
 * within the stream one by one the and adding to given string (which being cleared at first),
 * the content without unwanted characters
 * @param iStream - input stream
 * @param line - string
 * @return The given stream
 */
std::istream & getLine(std::istream & iStream, std::string & line)
{

    line.clear();
    std::istream::sentry se(iStream, true);
    std::streambuf *pStreamBuf = iStream.rdbuf();
    int currentChar;


    while (true)
    {
        currentChar = (pStreamBuf->sbumpc());

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
                line += (char) std::tolower(currentChar);
        }
    }
}

/**
 * @param c - a character
 * @return true if the given char is digit (0-9) and false otherwise
 */
bool isDigit(char c)
{
    return c >= '0' and c <= '9';
}

/**
 *This method is given a line in form of bad sequence,score and split this line into
 * two variables
 * @param date - text in form of : bad sequence,score
 * @param text - text container
 * @param score - score container
 * @return true if succeed to
 */
bool splitDataLine(std::string & date, std::string & text, int & score)
{
    int numOfSeparator = 0;
    std::string num;
    text.clear();
    for (auto c: date)
    {
        if (c == SEPARATOR)
        {
            numOfSeparator++;
        }
        else if (numOfSeparator == BEFORE_SEPARATOR)
        {
            text += c;
        }
        else if (isDigit(c) and numOfSeparator <= MAX_SEPARATOR_NUM)
        {
            num += c;
        }
        else
        {
            return false;
        }
    }
    score = std::stoi(num);
    return true;
}

/**
 *This method is given a text and a pair of (bad sequence, score)
 * and add the score to the total score if the bad sequence contained in the text
 * @param textToCheck
 * @param secScorePair - pair of (bad sequence, score)
 * @param totalScore -current score of bad sequence
 */
void updateScore(const std::string & textToCheck, const std::pair<std::string, int> & secScorePair, int & totalScore)
{

    if (textToCheck.find(secScorePair.first) != std::string::npos)
    {
        totalScore += secScorePair.second;
    }
}

/**
 *This method is given container of bad sequence and there scores
 * and determines whether the text file (of the given stream), is spam or not
 * @param hashMap -hash map which contains pairs of (bad sequence, score)
 * @param threshold -  score spam threshold
 * @param text - stream to the file to analyze
 */
void checkSpam(HashMap<std::string, int> & hashMap, int threshold, std::ifstream & text)
{
    std::string line, textToCheck;
    int currTotalScore = 0;

    while (!getLine(text, line).eof())
    {
        textToCheck += line + " ";
    }
    for (const auto & secScorePair:hashMap)
    {
        updateScore(textToCheck, secScorePair, currTotalScore);
        if (currTotalScore >= threshold)
        {
            std::cout << SPAM_MSG;
            return;
        }
    }
    std::cout << NOT_SPAM_MSG;
}

/**
 *This method initialize a given hash map with pairs of (bad sequence, score) by reading from CV format
 * text file
 * @param hashMap - hash map to initialize
 * @param database - file stream
 * @param score -current score of bad sequence
 * @return true if succeed to initialize the given hash map and false otherwise
 */
bool initializeMap(HashMap<std::string, int> & hashMap, std::ifstream & database, int & score)
{
    std::string data, badSec;

    while (!getLine(database, data).eof())
    {
        if (!splitDataLine(data, badSec, score))
        {
            return false;
        }
        hashMap.insert(badSec, score);
    }
    return true;
}

/**
 *Main of the program: given database in CV format which contains bad sequences and there scores,
 *a plain text to analyze and to determine whether the text is spam or not according to the given database
 * @param argc- number of arguments
 * @param argv - database, text to analyze and threshold
 */
int main(int argc, char *argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        printErrorMsg(USAGE_MSG);
        return EXIT_FAILURE;
    }

    try
    {
        HashMap<std::string, int> hashMap;
        std::ifstream database(argv[1]), text(argv[2]);
        int threshold = std::stoi(argv[3]);
        int score;
        bool areFileOpen = database.is_open() and text.is_open();

        if (!areFileOpen or threshold < MIN_THRESHOLD or !initializeMap(hashMap, database, score))
        {
            printErrorMsg(INVALID_MSG);
            return EXIT_FAILURE;
        }
        checkSpam(hashMap, threshold, text);
    }

    catch (const std::logic_error & e)
    {
        printErrorMsg(INVALID_MSG);
        return EXIT_FAILURE;
    }

    catch (const std::bad_alloc & e)
    {
        printErrorMsg(BAD_ALLOC_MSG);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}