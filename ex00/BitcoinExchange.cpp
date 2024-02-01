#include "BitcoinExchange.hpp"

/* -------------------------------------------------------------------------- */
/*                                    Utils                                   */
/* -------------------------------------------------------------------------- */
static float ft_stof(const std::string &str) {
    float num;
    std::stringstream ss(str);

    ss >> num;
    return num;
}

static bool is_digits(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

/* -------------------------------------------------------------------------- */
/*                                    Class                                   */
/* -------------------------------------------------------------------------- */

BitcoinExchange::BitcoinExchange() { parseCsvFile(); }

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _data(src._data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
    if (this == &rhs)
        return *this;

    this->_data = rhs._data;
    return *this;
}

/* -------------------------------------------------------------------------- */
/*                              Member Functions                              */
/* -------------------------------------------------------------------------- */

void BitcoinExchange::printLine(const std::string &key, const float value) {
    std::map<std::string, float>::iterator it = this->_data.lower_bound(key);

    if (it != this->_data.begin() && it->first != key)
        it--;

    std::cout << key << " => " << value << " = " << value * it->second << std::endl;
}
void BitcoinExchange::parseCsvFile() {
    std::ifstream ifs("data.csv");
    if (!ifs.good())
        throw std::string("could not open data.csv file, make sure to add it "
                          "to the project directory.");

    std::string line;

    // validate row header
    std::getline(ifs, line);
    if (line != "date,exchange_rate")
        throw std::string("data.csv row header is invalid. Check if you have "
                          "the correct file.");

    while (std::getline(ifs, line)) {
        std::istringstream ss(line);
        std::string date, value;
        float btcValue;

        if (std::getline(ss, date, ',') && std::getline(ss, value)) {
            btcValue = ft_stof(value);
            this->_data.insert(std::pair<std::string, float>(date, btcValue));
        }
    }

    ifs.close();
}

void BitcoinExchange::parseFile(const std::string file) {
    std::ifstream ifs(file.c_str());
    if (!ifs.good())
        throw std::string("could not open file.");

    std::string line;
    int count = 0;

    // validate row header
    std::getline(ifs, line);
    if (line != "date | value")
        std::cerr << "Error: input file has invalid row header." << std::endl;

    while (std::getline(ifs, line)) {
        count++;

        std::istringstream ss(line);
        std::string date, value;
        float btcValue;

        if (std::getline(ss, date, '|') && std::getline(ss, value)) {

            // force to have spaces between the | eg "2023-10-10 | 1"
            if (date.length() && date[date.length() - 1] == ' ' && value.length() &&
                value[0] == ' ') {

                date.erase(date.length() - 1, 1); // remove space at end
                value.erase(0, 1);                // remove space at begining
            } else {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }

            btcValue = ft_stof(value);

            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }

            if (!isValidValue(btcValue)) {
                // a custom error msg was already printed in the cout
                // continue to prevent reaching printLine
                continue;
            }

            printLine(date, btcValue);

        } else
            std::cerr << "Error: bad input => " << line << std::endl;
    }

    ifs.close();
}

/* -------------------------------------------------------------------------- */
/*                              Value Validation                              */
/* -------------------------------------------------------------------------- */
bool BitcoinExchange::isValidValue(const float value) {
    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    } else if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    return true;
}

/* -------------------------------------------------------------------------- */
/*                               Date Validation                              */
/* -------------------------------------------------------------------------- */

// Returns true if given year is valid.
bool isLeap(int year) {
    // Return true if year is a multiple of 4 and not multiple of 100.
    // OR year is multiple of 400.
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool BitcoinExchange::isValidDate(const std::string &date) {
    std::istringstream ss(date);
    std::string year, month, day;

    std::getline(ss, year, '-');
    std::getline(ss, month, '-');
    std::getline(ss, day);

    // Make sure it has all 3 fields, values are all digits and has the required
    // amount of digits
    if (ss.fail() || !is_digits(year) || !is_digits(month) || !is_digits(day) ||
        year.length() != 4 || month.length() != 2 || day.length() != 2)
        return false;

    // convert to int
    int y, m, d;
    y = std::atoi(year.c_str());
    m = std::atoi(month.c_str());
    d = std::atoi(day.c_str());

    // If year, month and day are not in given range
    if (y < 0 || y > 9999)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    // Handle February month with leap year
    if (m == 2) {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }

    // Months of April, June, Sept and Nov must have number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);

    return true;
}

/* -------------------------------------------------------------------------- */
/*                                   Testing                                  */
/* -------------------------------------------------------------------------- */
void BitcoinExchange::testDate(const std::string &date) {
    std::cout << "Date: " << std::setw(14) << std::setfill('_') << std::left << date << " is ";
    if (isValidDate(date))
        std::cout << "valid" << std::endl;
    else
        std::cout << "invalid" << std::endl;
}

void BitcoinExchange::testValue(const float value) {
    std::cout << "Value: " << std::setw(14) << std::setfill('_') << std::left << value << " is ";
    if (isValidValue(value))
        std::cout << "valid" << std::endl;
    else
        std::cout << "invalid" << std::endl;
}

void BitcoinExchange::printData() {
    std::map<std::string, float>::iterator it = this->_data.begin();

    while (it != this->_data.end()) {
        std::cout << it->first << " : " << it->second << std::endl;
        it++;
    }
}
