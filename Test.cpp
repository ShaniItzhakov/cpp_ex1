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

const int MAX_TESTS = 800;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    input.erase(remove(input.begin(), input.end(), '\t'), input.end());
    input.erase(remove(input.begin(), input.end(), '\n'), input.end());
    input.erase(remove(input.begin(), input.end(), '\r'), input.end());
	return input;
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

string get_hat(int digit) {
   
    switch (digit)
    {
    case 1:
        return "_===_";
    case 2:
        return "___.....";   
    case 3:
        return "_/_\\";
    case 4:
        return "___(_*_)";
    default:
        return NULL;
    }
}

string get_nose(int digit) {
   
    switch (digit)
    {
    case 1:
        return ",";
    case 2:
        return ".";   
    case 3:
        return "_";
    case 4:
        return "";
    default:
        return NULL;
    }
}

string get_left_eye(int digit) {
   
    switch (digit)
    {
    case 1:
        return "(.";
    case 2:
        return "(o";   
    case 3:
        return "(O";
    case 4:
        return "(-";
    default:
        return NULL;
    }
}

string get_right_eye(int digit) {
   
    switch (digit)
    {
    case 1:
        return ".)";
    case 2:
        return "o)";   
    case 3:
        return "O)";
    case 4:
        return "-)";
    default:
        return NULL;
    }
}

string get_left_arm(int digit) {
   
    switch (digit)
    {
    case 1:
        return "<";
    case 2:
        return "\\";   
    case 3:
        return "/";
    case 4:
        return "";
    default:
        return NULL;
    }
}

string get_right_arm(int digit) {
   
    switch (digit)
    {
    case 1:
        return ">";
    case 2:
        return "/";   
    case 3:
        return "\\";
    case 4:
        return "";
    default:
        return NULL;
    }
}

string get_torso(int digit) {
   
    switch (digit)
    {
    case 1:
        return "(:)";
    case 2:
        return "(][)";   
    case 3:
        return "(><)";
    case 4:
        return "()"; 
    default:
        return NULL;
    }
}

string get_base(int digit) {
   
    switch (digit)
    {
    case 1:
        return "(:)";
    case 2:
        return "(\"\")";   
    case 3:
        return "(___)";
    case 4:
        return "()"; 
    default:
        return NULL;
    }
}

TEST_CASE("Good snowman code") {
    // Checks in case of valid input using private function.
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(11111111)) == nospaces("_===_(.,.)<(:)>(:)"));
    CHECK(nospaces(snowman(22222222)) == nospaces("___.....\\(o.o)/(][)(\"\")"));
    CHECK(nospaces(snowman(33333333)) == nospaces("_/_\\(O_O)/(><)\\(___)"));
    CHECK(nospaces(snowman(44444444)) == nospaces("___(_*_)(--)()()"));
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_(.,.)(:)(:)"));
    CHECK(nospaces(snowman(33232124)) == nospaces("_/_\\\\(o_O)(][)>()"));
    CHECK(nospaces(snowman(12341234)) == nospaces("_===_(O.-)/<(><)()"));
    CHECK(nospaces(snowman(43214321)) == nospaces("___(_*_)(o_.)(][)\\(:)"));
    CHECK(nospaces(snowman(11442211)) == nospaces("_===_\\(-,-)/(:)(:)"));
    CHECK(nospaces(snowman(44332244)) == nospaces("___(_*_)\\(OO)/()()"));
}

TEST_CASE("Bad snowman code") {
    // Checks in case of invalid input that the code throws an exception with the specific message (second parameter)
    CHECK_THROWS_WITH_MESSAGE(snowman(5), "Invalid code '5'", "invalid length and digit 5");
    CHECK_THROWS_WITH_MESSAGE(snowman(11111110), "Invalid code '11111110'", "invalid digit 0");
    CHECK_THROWS_WITH_MESSAGE(snowman(1), "Invalid code '1'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(12), "Invalid code '12'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(123), "Invalid code '123'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(1234), "Invalid code '1234'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(12341), "Invalid code '12341'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(123412), "Invalid code '123412'", "invalid length");
    CHECK_THROWS_WITH_MESSAGE(snowman(1234123), "Invalid code '1234123'", "invalid length");
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
            
            int number = input;
            int digits[8];
            for (int i = 0; i < 8; i++) {
                digits[7-i] = number%10;
                number /= 10;
            }
            // Check that the snowman has all the correct body parts
            CHECK(nospaces(snowman(input)).find(get_hat(digits[0])) != -1);
            CHECK(nospaces(snowman(input)).find(get_nose(digits[1])) != -1);
            CHECK(nospaces(snowman(input)).find(get_left_eye(digits[2])) != -1);
            CHECK(nospaces(snowman(input)).find(get_right_eye(digits[3])) != -1);
            CHECK(nospaces(snowman(input)).find(get_left_arm(digits[4])) != -1);
            CHECK(nospaces(snowman(input)).find(get_right_arm(digits[5])) != -1);
            CHECK(nospaces(snowman(input)).find(get_torso(digits[6])) != -1);
            CHECK(nospaces(snowman(input)).find(get_base(digits[7])) != -1);
        }
    }
}