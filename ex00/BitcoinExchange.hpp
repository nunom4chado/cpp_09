#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>  // atoi
#include <fstream>  // std::ifstream
#include <iomanip>  // std::get_time
#include <iostream> // std::cout
#include <map>
#include <sstream> // istringstream, stringstream
#include <string>  // std::string

class BitcoinExchange {
  private:
    std::map<std::string, float> _data;

  public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);

    void parseCsvFile();
    void parseFile(const std::string file);
    bool isValidValue(const float value);
    bool isValidDate(const std::string &date);
    void printLine(const std::string &key, const float value);

    void testDate(const std::string &date); // testing only
    void testValue(const float value);      // testing only
    void printData();                       // testing only
};

#endif /* BITCOINEXCHANGE_HPP */
