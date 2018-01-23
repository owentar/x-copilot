#include "gmock/gmock.h"

#include "utils.h"

using namespace testing;
using namespace xcopilot;

class UtilsTest : public Test { };

TEST_F(UtilsTest, ParsePhraseToBoolean) {
    ASSERT_THAT(parseToBoolean("ON"), Eq(true));
    ASSERT_THAT(parseToBoolean("DOWN"), Eq(true));
    ASSERT_THAT(parseToBoolean("OFF"), Eq(false));
    ASSERT_THAT(parseToBoolean("UP"), Eq(false));
}

TEST_F(UtilsTest, ParseNumbersWordsToNumbersArray) {
    ASSERT_THAT(parseNumbers("ONE TWO"), ElementsAre(1, 2));
    ASSERT_THAT(parseNumbers("FOUR NINE SEVEN ZERO EIGHT"), ElementsAre(4, 9, 7, 0, 8));
    ASSERT_THAT(parseNumbers("THREE FIVE ZERO SIX"), ElementsAre(3, 5, 0, 6));
}

TEST_F(UtilsTest, ParseToInteger) {
    ASSERT_THAT(parseToInt("NINE FIVE ZERO ZERO"), Eq(9500));
    ASSERT_THAT(parseToInt("FOUR THREE"), Eq(43));
    ASSERT_THAT(parseToInt("ZERO"), Eq(0));
}

TEST_F(UtilsTest, ParseToDecimal) {
    ASSERT_THAT(parseToDecimal("TWO NINE NINE TWO", 0), DoubleEq(2992));
    ASSERT_THAT(parseToDecimal("TWO NINE NINE TWO", 1), DoubleEq(299.2));
    ASSERT_THAT(parseToDecimal("TWO NINE NINE TWO", 2), DoubleEq(29.92));
    ASSERT_THAT(parseToDecimal("TWO NINE NINE TWO", 3), DoubleEq(2.992));
    ASSERT_THAT(parseToDecimal("TWO NINE NINE TWO", 4), DoubleEq(0.2992));
}

TEST_F(UtilsTest, ParseToFloat) {
    ASSERT_THAT(parseToFloat("THREE ZERO ZERO FOUR"), FloatEq(30.04));
}
