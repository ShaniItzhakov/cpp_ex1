/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Shani Itzhakov
 * 
 * Date: 2021-02
 */
#include "doctest.h"
#include "snowman.hpp"
using namespace ariel;

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_TESTS = 650;

// Matrix that holds the snowman body parts.
const string matrix[8][4] = {
    {"_===_", "___.....", "_/_\\", "___(_*_)"},
    {",", ".", "_", ""},
    {"(.", "(o", "(O", "(-"},
    {".)", "o)", "O)", "-)"},
    {" <", "\\ ", " /", "  "},
    {" >", "/ ", " \\", "  "},
    {"( : )", "(] [)", "(> <)", "(   )"},
    {"( : )", "(\" \")", "(___)", "(   )"}};

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a (tidy issue).
 */
string nospaces(string input) {
    erase(input, ' ');
	erase(input, '\t');
	erase(input, '\n');
	erase(input, '\r');
	return input;
}

/**
 * Returns the expected snowman as a string for the input received.
 * It uses an array to store each digit from the received input.
 * Uses Mathmetical principle to split the number from right to left and insert into the digits array.
 * Gets from the matrix that contains the snowman body parts in the right order and concat it to the expected string. 
 */
string get_expected_snowman(int input) {
    string expected = "";
    int number = input;
    int digits[8];
    for (int i = 0; i < 8; i++) {
        digits[7-i] = number%10;
        number /= 10;
    }
    // HHHHH - hat
    expected += matrix[0][digits[0]-1];
    // X[0] - left upper arm
    expected += matrix[4][digits[4]-1][0];
    // (L - left eye
    expected += matrix[2][digits[2]-1];
    // N - nose
    expected += matrix[1][digits[1]-1];
    // R) - right eye
    expected += matrix[3][digits[3]-1];
    // Y[0] - right upper arm
    expected += matrix[5][digits[5]-1][0];
    // X[1] - left lower arm
    expected += matrix[4][digits[4]-1][1];
    // (TTT) - torso
    expected += matrix[6][digits[6]-1];
    // Y[1] - lower right arm
    expected += matrix[5][digits[5]-1][1];
    // (BBB) - base
    expected += matrix[7][digits[7]-1];
    return expected;
}

/**
 * Returns true if the number received is valid,
 * which means each digit is between 1 and 4, otherwise returns false.
 */
bool valid_number(int number) {
    while (number != 0) {
        int curr_digit = number % 10;
        if (curr_digit < 1 || curr_digit > 4) {
            return false;
        }    
        number /= 10;
    }
    return true;
}

TEST_CASE("Good snowman code") {
    // Checks in case of valid input using private function.
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(11111111)) == nospaces(get_expected_snowman(11111111)));
    CHECK(nospaces(snowman(22222222)) == nospaces(get_expected_snowman(22222222)));
    CHECK(nospaces(snowman(33333333)) == nospaces(get_expected_snowman(33333333)));
    CHECK(nospaces(snowman(44444444)) == nospaces(get_expected_snowman(44444444)));
    CHECK(nospaces(snowman(11114411)) == nospaces(get_expected_snowman(11114411)));
    CHECK(nospaces(snowman(33232124)) == nospaces(get_expected_snowman(33232124)));
    CHECK(nospaces(snowman(12341234)) == nospaces(get_expected_snowman(12341234)));
    CHECK(nospaces(snowman(43214321)) == nospaces(get_expected_snowman(43214321)));
    CHECK(nospaces(snowman(11442211)) == nospaces(get_expected_snowman(11442211)));
    CHECK(nospaces(snowman(44332244)) == nospaces(get_expected_snowman(44332244)));
}

TEST_CASE("Bad snowman code") {
    // Checks in case of invalid input that the code throws an exception with the specific message (second parameter)
    CHECK_THROWS_WITH_MESSAGE(snowman(5), "Invalid code '5'", "invalid length and digit 5");
    CHECK_THROWS_WITH_MESSAGE(snowman(11111110), "Invalid code '11111115'", "invalid digit 0");
    CHECK_THROWS_WITH_MESSAGE(snowman(1), "Invalid code '1'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(-1), "Invalid code '-1'", "invalid length and negetive number -1");
    CHECK_THROWS_WITH_MESSAGE(snowman(1234123412), "Invalid code '1234123412'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(-11111111), "Invalid code '-11111111'", "invalid length and negetive number");
}

TEST_CASE("Automatic tests") {
    // Loop over some possible combinations between 11111111 and 44444444
    int counter = 0;
    for (int input = 11111111; input <= 44444444 && counter < MAX_TESTS; input++) {
        // Valid input number
        if (valid_number(input)) {
            counter++;
            // Check that there are no exeptions thrown
            CHECK_NOTHROW(snowman(input));
            // Check that the snowman is correct
            CHECK(nospaces(snowman(input)) == nospaces(get_expected_snowman(input)));
        }
        // Not a valid input number (33 million cases)
        // else {
        //     CHECK_THROWS(snowman(input));
        // }
    }
}