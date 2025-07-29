#include <iostream>
#include "calc_funcs.cpp"
using namespace std;

/**
 * Returns true if `list1` and `list2` are not equal, false otherwise.
 * 
 * The lists are not equal if their sizes are not equal, or one of the corresponding elements is not equal to the other.
 * 
 * @param list1 first list to compare
 * @param list2 second list to compare
 * @return true if not equal, false otherwise
 */
bool listsNotEqual(list<string> list1, list<string> list2) {
    if(list1.size() != list2.size()) return true;
    
    std::list<string>::iterator list1Iter = list1.begin();
    std::list<string>::iterator list2Iter = list2.begin();

    while(list1Iter != list1.end()) {
        if(*list1Iter != *list2Iter) {
            return true;
        }

        list1Iter++;
        list2Iter++;
    }

    return false;
}

/**
 * Returns true if `list1` and `list2` are not equal, false otherwise.
 * 
 * The lists are not equal if their sizes are not equal, or one of the corresponding elements is not equal to the other.
 * 
 * @param list1 first list to compare
 * @param list2 second list to compare
 * @return true if not equal, false otherwise
 */
bool listsNotEqual(list<int> list1, list<int> list2) {
    if(list1.size() != list2.size()) return true;
    
    std::list<int>::iterator list1Iter = list1.begin();
    std::list<int>::iterator list2Iter = list2.begin();

    while(list1Iter != list1.end()) {
        if(*list1Iter != *list2Iter) {
            return true;
        }

        list1Iter++;
        list2Iter++;
    }

    return false;
}


/**
 * Tests the function `findInnerParentheses`. Test numbers start at 0.
 * 
 * Calls the function on test cases and compares the result to its expected value.
 * If the expected and result are not equal, the method prints an error message and throws a `std::exception`.
 */
void testFindInnerParenthesesNormal() {
    //The test inputs
    vector<list<string>> tests = { 
    //Single parentheses
    {"(", "3", ")"}, //0
    {"(", "3", "+", "2", ")"},
    {"3", "+", "(", "10", "*", "10", ")"}, //2
    //Single innermost pair of parentheses, nested
    {"(", "(", "1", ")", ")"},
    {"(", "3", "-", "2", "*", "(", "5", "/", "1", ")", ")"}, //4
    {"3", "+", "(", "2", "*", "(", "10", "+", "9", ")", "*", "7", ")"},
    //No parentheses at all
    {"5", "+", "3"}, //6
    {"2", "/", "2", "^", "1"},
    {"3"}, //8
    //Many non-nested pairs
    {"(", "3", "+", "4", ")", "-", "(", "10", "*", "9", ")"}, 
    {"0", "-", "2", "-", "(", "1", "+", "8", "*", "3", ")", "*", "(", "3", ")"}, //10
    {"2", "-", "(", "15", "-", "3", ")", "*", "(", "1", "*", "1", ")", "+", "(", "3", "*", "4", ")"}, 
    //Some nested pairs, some non-nested pairs
    {"(", "3", "+", "(", "4", "/", "2", ")", ")", "*", "(", "4", "+", "7", ")"}, //12
    {"(", "(", "(", "100", ")", ")", ")", "*", "(", "2", "-", "1", ")"},
    {"16", "-", "(", "3", "*", "4", ")", "+", "(", "3", "+", "(", "3", "*", "3", ")", "/", "9", ")"} //14
    };

    vector<list<int>> expecteds = {
    //Single parentheses
    {0, 2}, //0
    {0, 4},
    {2, 6}, //2
    //Single innermost pair, nested
    {1, 3},
    {5, 9}, //4
    {5, 9},
    //None
    {}, //6
    {},
    {}, //8
    //Many non-nested pairs
    {0, 4, 6, 10}, 
    {4, 10, 12, 14}, //10
    {2, 6, 8, 12, 14, 18}, 
    //Some nested pairs, some non-nested pairs
    {3, 7, 10, 14}, //12
    {2, 4, 8, 12},
    {2, 6, 11, 15} //14
    };

    for(int i=0; i<tests.size(); i++) {

        list<int> result = findInnerParentheses(tests[i]);

        if(listsNotEqual(expecteds[i], result)) {
            cout << ">> Test " << i << " failed" << endl;
            cout << ">> Expected: { ";
            for(int j : expecteds[i]) {
                cout << j << " ";
            }
            cout << "}" << endl;
            cout << ">> Result: { ";
            for(int j : result) {
                cout << j << " ";
            }
            cout << "}" << endl;

            throw exception();
        }

        cout << "Test " << i << " passed: { ";
        for(int j : result) {
            cout << j << " ";
        }
        cout << "}" << endl;
    }

    cout << "All tests for `testFindInnerParentheses` (normal) passed" << endl;
}


/**
 * Tests the function `findInnerParentheses`. Test numbers start at 0.
 * 
 * Calls the function on test cases and checks if the function throws a `std::runtime_exception`.
 * If not, the method prints an error message and throws a `std::exception`.
 */
void testFindInnerParenthesesExceptions() {
    //The test inputs
    vector<list<string>> tests = { 
    {"("}, //0
    {"(", ""},
    {"(", "3", "+", "2"}, //2
    {")"},
    {"3", "-", "10", ")"}, //4
    {"3", "+", "(", "29", "-", "(", "3", ")"},
    {"(", "3", "-", "2", ")", ")"}, //6
    {"(", "3", "-", "(", "2", "+", "5", ")", "+", "10"}
    };

    //Run the tests
    for(int i=0; i<tests.size(); i++) {
        
        try {
            //Get the result
            findInnerParentheses(tests[i]);
            
            //If the call doesn't throw an exception, error message
            cout << ">> Test " << i << " failed" << endl;
            cout << ">> A `runtime_error` should be thrown" << endl;

            throw new exception();
        }
        catch(runtime_error& e) {
            cout << "Test " << i << " passed" << endl;
        }
    }

    cout << "All tests for findInnerParentheses (exceptions) passed" << endl;
}


/**
 * Tests the function `evalPartialExpressions`. Test numbers start at 0.
 * 
 * Calls the function on test cases and compares the output to some expected results.
 * If the output and expected are not equal, the method prints an error message and throws a `std::exception`.
 * 
 * A segmentation fault counts as a failed test.
 */
void testEvalPartialExpressionNormal() {
    //The test inputs. THE RESULT MUST BE AN INTEGER.
    vector<list<string>> tests = { 
    //SINGLE OPERATIONS
    {"2", "^", "3"}, //0
    {"2", "*", "10"} ,
    {"10", "+", "47"}, //2
    //MANY OPERATIONS (of equal order)
    {"3", "^", "3", "^", "2"},
    {"2", "*", "4", "/", "8"}, //4
    {"7", "-", "6", "+", "2"},
    {"7", "+", "6", "/", "2"}, //6
    //ORDER OF OPERATIONS
    {"2", "*", "3", "-", "1"}, 
    {"2", "+", "3", "*", "4"}, //8
    {"2", "+", "3", "^", "4", "*", "2"}, 
    {"2", "*", "3", "+", "4", "^", "2"}, //10
    {"9", "^", "3", "/", "3", "+", "10"}, 
    {"2", "-", "10", "^", "2", "^", "2", "*", "-5"}, //10
    //SINGLE NUMBERS
    {"10"}
    };

    //The expected outputs. THE RESULT MUST BE AN INTEGER.
    vector<list<string>> expecteds = {
    //BASIC
    {"8"}, //0
    {"20"},
    {"57"}, //2
    //MANY (equal)
    {"729"},
    {"1"}, //4
    {"3"},
    {"10"}, //6
    //O.O.
    {"5"}, 
    {"14"}, //8
    {"164"}, 
    {"22"}, //10
    {"253"}, 
    {"50002"}, //12
    {"10"}
    };


    for(int i=0; i<tests.size(); i++) {
        
        //Get the result
        list<string> result = evalPartialExpression(tests[i]);

        //Convert the first index to an int
        string firstElem = result.front();
        result.pop_front();
        result.push_front(to_string((int)stof(firstElem)));
        
        //If expected and result are not equal, error message
        if(listsNotEqual(expecteds[i], result)) {
            cout << ">> Test " << i << " failed" << endl;
            cout << ">> Expected: { ";
            for(string s : expecteds[i]) {
                cout << s << " ";
            }
            cout << "}" << endl;

            cout << ">> Result: { ";
            for(string s : result) {
                cout << s << " ";
            }
            cout << "}" << endl;

            throw new exception();
        }

        cout << "Test " << i << " passed: { ";
        for(string s : result) {
            cout << s << " ";
        }
        cout << "}" << endl;
    }

    cout << "All tests for evalPartialExpression (normal) passed" << endl;
}


/**
 * Tests the function `evalPartialExpression`. Test numbers start at 0.
 * 
 * Calls the function on test cases and checks if the function throws a `std::runtime_exception`.
 * If not, the method prints an error message and throws a `std::exception`.
 */
void testEvalPartialExpressionExceptions() {
    //The test inputs
    vector<list<string>> tests = { 
    //Invalid operands
    {"2", "^", "^", "^", "3"}, //0
    {"3", "^", "+", "4", "-", "2"},
    {"3", "+", "-", "4", "/", "2"}, //2
    {"2", "^", "3", "+", "*", "3"},
    //Two numbers in a row
    {"4", "+", "3", "50", "+", "3"}, //4
    {"3", "+", "15", "*", "7", "3", "^", "3"},
    //Operand at the ends of the expression
    {"+", "3", "-", "5"}, //6
    {"3", "-", "3", "*"},
    //Entirely operands
    {"+", "^", "-", "*", "-"} //8
    };

    //Run the tests
    for(int i=0; i<tests.size(); i++) {
        
        try {
            //Get the result
            list<string> result = evalPartialExpression(tests[i]);
            
            //If the call doesn't throw an exception, error message
            cout << ">> Test " << i << " failed" << endl;
            cout << ">> A `runtime_error` should be thrown" << endl;

            throw new exception();
        }
        catch(runtime_error& e) {
            cout << "Test " << i << " passed" << endl;
        }
    }

    cout << "All tests for evalPartialExpression (exceptions) passed" << endl;
}


/**
 * Tests the function `evalFullExpression`. Test numbers start at 0.
 * 
 * Calls the function on test cases and compares the result to its expected output.
 * If the result and expected are not equal, the method prints an error message and throws a `std::exception`.
 * 
 * @param testStart test number to start with
 */
void testEvalFullExpressionNormal(int testStart) {
    //The test inputs.  MUST EVALUATE TO AN INTEGER.
    vector<list<string>> tests = { 
        //NO PARENTHESES
        {"1", "+", "2"}, //0
        {"1", "+", "2", "*", "3"}, 
        {"2", "^", "4", "-", "2"},
        //SINGLE PARENTHESES 
        {"(", "3", "+", "2", ")"}, 
        {"2", "*", "(", "3", "+", "4", ")"},
        {"3", "+", "20", "-", "(", "4", "*", "2", ")", "+", "2"}, 
        //NESTED PARENTHESES
        {"(", "4", "+", "2", ")", "*", "(", "2", "+", "2", ")"},
        {"50", "*", "2", "/", "(", "5", "*", "(", "8", "-", "6", ")", ")"}, 
        {"9", "*", "(", "2", "^", "(", "3", "*", "(", "5", "-", "4", ")", ")", ")"},
        {"(", "(", "(", "3", ")", ")", ")"}, 
        //SOME NESTED, SOME NOT NESTED
        {"(", "5", "+", "(", "4", "-", "2", ")", "*", "3", ")", "^", "3"}, 
        {"(", "(", "4", "+", "8", ")", "/", "(", "10", "-", "6", ")", ")", "^", "(", "18", "-", "(", "16", "*", "1", ")", ")"}, 
        //NEGATIVE NUMBERS
        {"4", "*", "-2"}, 
        {"3", "^", "2", "-", "-5"}, 
        {"2", "/", "(", "-9", "+", "8", ")"}, 
        {"(", "2", "^", "(", "-4", "+", "6", ")", "-", "5", ")", "*", "-1"}, 
        //SINGLE NUMBER
        {"20"}, 
        {"-2"},
        //DECIMALS
        {"0.5", "*", "2"}, 
        {"0.5", "*", "(", "0.25", "*", "8", ")"}
    };

    //The expected outputs. MUST EVALUATE TO AN INTEGER.
    vector<list<string>> expecteds = {
        //NO PARENTHESES
        {"3"},
        {"7"},
        {"14"},
        //SINGLE PARENTHESES 
        {"5"},
        {"14"},
        {"17"},
        //NESTED PARENTHESES
        {"24"},
        {"10"},
        {"72"},
        {"3"},
        //SOME NESTED, SOME NOT NESTED
        {"1331"},
        {"9"}, 
        //NEGATIVE NUMBERS
        {"-8"}, 
        {"14"}, 
        {"-2"},
        {"1"}, 
        //SINGLE NUMBER
        {"20"},
        {"-2"}, 
        //DECIMALS
        {"1"},
        {"1"},
    };


    for(int i=testStart; i<tests.size(); i++) {
        
        //Get the result
        list<string> result = evalFullExpression(tests[i]);

        //Convert the first index to an int
        string firstElem = result.front();
        result.pop_front();
        result.push_front(to_string((int)stof(firstElem)));
        
        //If expected and result are not equal, error message
        if(listsNotEqual(expecteds[i], result)) {
            cout << ">> Test " << i << " failed" << endl;
            cout << ">> Expected: { ";
            for(string s : expecteds[i]) {
                cout << s << " ";
            }
            cout << "}" << endl;

            cout << ">> Result (first index to nearest integer): { ";
            for(string s : result) {
                cout << s << " ";
            }
            cout << "}" << endl;

            throw new exception();
        }

        cout << "Test " << i << " passed: " << flush;
        for(string s : result) {
            cout << "'" << s << "' ";
        }
        cout << endl;
    }

    cout << "All tests from #" << testStart << " for evalPartialExpression (normal) passed" << endl;
}


int main() {
    // testFindInnerParenthesesNormal();
    // testEvalPartialExpressionNormal();
    // testEvalPartialExpressionExceptions();
    testEvalFullExpressionNormal(0);
}