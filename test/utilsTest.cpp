#include "gmock/gmock.h"

#include "utils.h"

using namespace testing;

class UtilsTest : public Test
{
};

TEST_F(UtilsTest, ParseNumbersWordsToNumbersArray)
{
    ASSERT_THAT(parseNumbers("one two"), ElementsAre(1, 2));
    ASSERT_THAT(parseNumbers("four nine seven zero eight"), ElementsAre(4, 9, 7, 0, 8));
    ASSERT_THAT(parseNumbers("three five zero six"), ElementsAre(3, 5, 0, 6));
}

TEST_F(UtilsTest, ParseToInteger)
{
    ASSERT_THAT(parseToInt("nine five zero zero"), Eq(9500));
    ASSERT_THAT(parseToInt("four three"), Eq(43));
    ASSERT_THAT(parseToInt("zero"), Eq(0));
}

TEST_F(UtilsTest, ParseToDecimal)
{
    ASSERT_THAT(parseToDecimal("two nine nine two", 0), DoubleEq(2992));
    ASSERT_THAT(parseToDecimal("two nine nine two", 1), DoubleEq(299.2));
    ASSERT_THAT(parseToDecimal("two nine nine two", 2), DoubleEq(29.92));
    ASSERT_THAT(parseToDecimal("two nine nine two", 3), DoubleEq(2.992));
    ASSERT_THAT(parseToDecimal("two nine nine two", 4), DoubleEq(0.2992));
}