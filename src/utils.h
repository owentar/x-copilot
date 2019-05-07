#ifndef X_COPILOT_UTILS_H
#define X_COPILOT_UTILS_H

#include <string>
#include <vector>

namespace xcopilot {
    bool parseToBoolean(const std::string &phrase);

    bool parseToBoolean(const std::vector<int> &values);

    std::vector<int> parseNumbers(const std::string &numbersAsWords);

    double parseToNumber(const std::string &numbersAsWords, unsigned short decimals = 0);

    double parseToNumber(const std::vector<int> &numbers, unsigned short decimals = 0);

    int parseToInt(const std::string &numbersAsWords);

    int parseToInt(const std::vector<int> &numbers);

    double parseToDecimal(const std::string &numbersAsWords, unsigned short decimals = 2);

    double parseToDecimal(const std::vector<int> &numbers, unsigned short decimals = 2);

    float parseToFloat(const std::string &numbersAsWords, unsigned short decimals = 2);

    float parseToFloat(const std::vector<int> &numbers, unsigned short decimals = 2);
}

#endif //X_COPILOT_UTILS_H
