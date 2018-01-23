#include "utils.h"

#include <cmath>
#include <map>
#include <numeric>

#include "boost/algorithm/string.hpp"

std::map<std::string, int> WORD_TO_NUMBER = {
        { "ZERO", 0 },
        { "ONE", 1 },
        { "TWO", 2 },
        { "THREE", 3 },
        { "FOUR", 4 },
        { "FIVE", 5 },
        { "SIX", 6 },
        { "SEVEN", 7 },
        { "EIGHT", 8 },
        { "NINE", 9 }
};

bool xcopilot::parseToBoolean(const std::string& phrase) {
    return phrase == "ON" || phrase == "DOWN";
}

std::vector<int> xcopilot::parseNumbers(const std::string& numbersAsWords) {
    std::vector<std::string> numbers;
    boost::split(numbers, numbersAsWords, boost::is_any_of(" "));
    std::vector<int> result(numbers.size());
    std::transform(numbers.begin(), numbers.end(), result.begin(), [](const std::string& num) { return WORD_TO_NUMBER[num]; });
    return result;
}

double xcopilot::parseToNumber(const std::string& numbersAsWords, unsigned short decimals) {
    std::vector<int> numbers = xcopilot::parseNumbers(numbersAsWords);
    double exp = numbers.size() - 1.0 - decimals;
    double scale = std::pow(10.0, exp);
    return std::accumulate(numbers.begin(), numbers.end(), 0.0, [&scale](double result, double number) {
        result += number * scale;
        scale /= 10;
        return result;
    });
}

int xcopilot::parseToInt(const std::string& numbersAsWords) {
    return xcopilot::parseToNumber(numbersAsWords);
}

double xcopilot::parseToDecimal(const std::string& numbersAsWords, unsigned short decimals) {
    return xcopilot::parseToNumber(numbersAsWords, decimals);
}

float xcopilot::parseToFloat(const std::string& numbersAsWords, unsigned short decimals) {
    return static_cast<float>(xcopilot::parseToDecimal(numbersAsWords, decimals));
}
