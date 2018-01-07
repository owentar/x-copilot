#ifndef X_COPILOT_UTILS_H
#define X_COPILOT_UTILS_H

#include <string>
#include <vector>

namespace xcopilot {
    std::vector<int> parseNumbers(const std::string &numbersAsWords);

    double parseToNumber(const std::string &numbersAsWords, unsigned short decimals = 0);

    int parseToInt(const std::string &numbersAsWords);

    double parseToDecimal(const std::string &numbersAsWords, unsigned short decimals = 2);

    float parseToFloat(const std::string &numbersAsWords, unsigned short decimals = 2);
}

#endif //X_COPILOT_UTILS_H
