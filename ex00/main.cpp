#include "BitcoinExchange.hpp"

#include <iostream>
#include <limits>

void runTests(BitcoinExchange &btc);

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try {
        BitcoinExchange btc;
        // runTests(btc);
        btc.parseFile(argv[1], '|');
    } catch (std::string error) {
        std::cerr << "Error: " << error << std::endl;
        return 1;
    }

    return 0;
}

void runTests(BitcoinExchange &btc) {
    std::cout << "Test Dates" << std::endl;

    btc.testDate("2023-11-20");   // [VALID]
    btc.testDate("2023-08-2");    // min digits day
    btc.testDate("2023-8-02");    // min digits month
    btc.testDate("202-08-02");    // min digits year
    btc.testDate("2023-8-2");     // min digits month and day
    btc.testDate("202-8-2");      // min digits year, month and day
    btc.testDate("2023-08-2a");   // letter
    btc.testDate("2023-b8-20");   // letter
    btc.testDate("20c3-08-20");   // letter
    btc.testDate("2023/08/20");   // bad separator
    btc.testDate("2023_08_20");   // bad separator
    btc.testDate("2023-02-29");   // wrong leap year
    btc.testDate("2024-02-29");   // [VALID] ok leap year
    btc.testDate("9999-02-20");   // [VALID] year max
    btc.testDate("0000-02-20");   // [VALID] year min
    btc.testDate("99999-02-20");  // bad year max
    btc.testDate("-001-02-20");   // bad year min
    btc.testDate("00000-02-20");  // bad year min
    btc.testDate("0000-022-20");  // 3 digits month
    btc.testDate("0000-02-200");  // 3 digits day
    btc.testDate("00000-022-20"); // too many digits year month and
    btc.testDate("2023--20");     // no month
    btc.testDate("2023-02-");     // no day
    btc.testDate("-02-20");       // no year
    btc.testDate("---");          // no nothing

    // btc.printData();

    std::cout << "Test Values" << std::endl;
    const char databaseFile = ',';
    const char inputFile = '|';

    const float MIN = static_cast<float>(std::numeric_limits<float>::lowest());
    const float MAX = static_cast<float>(std::numeric_limits<float>::max());

    std::cout << "For data.csv file" << std::endl;
    btc.testValue(0, databaseFile);
    btc.testValue(-1, databaseFile);
    btc.testValue(1, databaseFile);
    btc.testValue(42.42, databaseFile);
    btc.testValue(1000, databaseFile);
    btc.testValue(1001, databaseFile);
    btc.testValue(MIN, databaseFile);
    btc.testValue(MAX, databaseFile);
    std::cout << "\n"
              << "For input file" << std::endl;
    btc.testValue(0, inputFile);
    btc.testValue(-1, inputFile);
    btc.testValue(1, inputFile);
    btc.testValue(42.42, inputFile);
    btc.testValue(1000, inputFile);
    btc.testValue(1001, inputFile);
    btc.testValue(MIN, inputFile);
    btc.testValue(MAX, inputFile);
}
