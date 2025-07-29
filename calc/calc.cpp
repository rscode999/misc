#include "calc_funcs.cpp"
#include <iomanip>
#include <cctype>


/**
 * Prompts the user to press Enter or Return, then returns `returnCode`.
 * 
 * Should be used only to exit the `main` function.
 * 
 * @param returnCode the value to return
 * @return `returnCode`, after user presses Enter or Return
 */
int promptExit(int returnCode) {
    string s;
    cout << "Press ENTER or RETURN to exit." << flush;
    getline(cin, s);
    return returnCode;
}


/**
 * Removes any spaces from `input`.
 * 
 * @param input string to remove spaces from
 * @return copy of `input` with no spaces
 */
string removeSpaces(string input) {
    string output = "";

    for(int i=0; i<input.length(); i++) {
        if(input[i] != ' ') {
            output.push_back(input[i]);
        }
    }

    return output;
}


/**
 * Returns true if `c` is a valid operator, false otherwise
 * 
 * @param c character to check
 * @return if `c` is a valid operator
 */
bool isOperator(char c) {
    return c=='+' || c=='-'
        || c=='*' || c=='/' 
        || c=='^'
        || c=='(' || c==')';
}


/**
 * Returns `stringExpr` as an expression list.
 * 
 * All numbers, operators, and symbols should be in separate strings.
 * 
 * If `stringExpr` is not a valid expression string, or some parentheses don't close,
 * the method should print the user's input, indicate where in the input the invalid character is,
 * then return the empty list `{}`.
 * (Note: For parentheses, the function doesn't need to indicate where.)
 * 
 * @param stringExpr the string to convert to an expression list. Must have length at least 1
 * @return expression list version of `stringExpr`
 */
list<string> stringToExpr(string stringExpr) {
    string input = removeSpaces(stringExpr);


    list<string> expr = {};
    bool negative = false;

    int parenthesesLayers = 0;

    string currentNumberStr = "";
    for(int i=0; i<input.length(); i++) {
        //If operator, load the number to the expression list, then load the operator
        if(isOperator(input[i])) {
            //Load number
            try {
                // cout << "Current N: " << currentNumberStr << endl;
                
                //First, check if the number is valid
                if(currentNumberStr.length()>0) {
                    float n = stof(currentNumberStr);
                }

                //If valid, add the string (negate if necessary) and wipe the current number
                if(currentNumberStr.length()>0) {
                    expr.push_back(negative ? "-"+currentNumberStr : currentNumberStr);
                }
                currentNumberStr = "";
                negative=false;

                //Update parentheses layers
                if(input[i]=='(') {
                    parenthesesLayers += 1;
                }
                if(input[i]==')') {
                    parenthesesLayers -= 1;
                }
            }
            //If invalid number, flag as syntax error
            catch(invalid_argument& excep) {
                cout << "Syntax error- Invalid number entered at position " << (i+1)  << endl;
                cout << input << endl;
                for(int e=0; e<i; e++) {
                    cout << " ";
                }
                cout << "^" << flush;
                cout << "Error here\n" << endl;
                return {};
            }

            string s = string(1, input[i]);
            expr.push_back(s);
        }
        //If number, decimal point, or negative sign, add to the current number string
        else if(isdigit(input[i]) || input[i]=='.' || (input[i]=='n' || input[i]=='N')) {
            //If negative sign, don't add, but mark the number as negative
            if(input[i]=='n' || input[i]=='N') {
                negative=true;
            }
            else {
                currentNumberStr.push_back(input[i]);
            }
        }
        //If not anything, invalid
        else {
            cout << "Syntax error- Invalid character entered at position " << (i+1)  << endl;
            cout << input << endl;
            for(int e=0; e<i; e++) {
                cout << " ";
            }
            cout << "^" << flush;
            cout << "Error here\n" << endl;
            return {};
        }

        // for(string s : expr) {
        //     cout << s << " ";
        // }
        // cout << endl;
        // cout << currentNumberStr << endl;
    }


    //Load any remaining number
    try {
        //First, check if the number is valid
        if(currentNumberStr.length()>0) {
            float n = stof(currentNumberStr);
        }

        //If valid, add the string and wipe the current number
        if(currentNumberStr.length()>0) {
            expr.push_back(negative ? "-"+currentNumberStr : currentNumberStr);
        }
        currentNumberStr = "";
    }
    catch(invalid_argument& excep) {
        cout << "Syntax error- Invalid number entered at position " << (input.size())  << endl;
        cout << input << endl;
        for(int e=0; e<input.size()-1; e++) {
            cout << " ";
        }
        cout << "^" << flush;
        cout << "Error here\n" << endl;
        return {};
    }

    //Parentheses check
    if(parenthesesLayers != 0) {
       cout << "Syntax error- Parentheses are not closed\n" << endl; 
       return {};
    }

    return expr;
}





int main(int argc, const char** argv) {

    cout << "Use 'n' as the negative sign. Type 'exit' into the prompt to end the program.\n" << endl;

    //Continue operation until the user exits
    while(true) {

        string initialExpression;
        while(true) {
            //Get the user's input
            cout << "Type expression here, then press Enter: ";
            getline(cin, initialExpression);

            //Remove all spaces
            initialExpression = removeSpaces(initialExpression);

            //Check if the entry is empty. If not, move to the next stage
            if(initialExpression.size() > 0) {
                break;
            }
        }

        //Check if user wanted to exit
        if(initialExpression == "exit" || initialExpression == "clear") {
            return 0;
        }

        //Convert expression into a list
        list<string> expression;
        expression = stringToExpr(initialExpression);

        //If the expression is empty (meaning there's a syntax error), skip the evaluation steps
        if(expression.size()==0) {
            continue;
        }

        // cout << "Entered expression: " << flush;
        // for(string s : expression) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;

        //Evaluate the expression
        list<string> result;
        try {
            result = evalFullExpression(expression);
        }
        catch(runtime_error& e) {
            cout << e.what() << "\n" << endl;
            continue;
        }

        //Get the precision
        int argv1Value = 0;
        if(argc>1) {
            string str = argv[1];
            argv1Value = stoi(str);
        }
        if(argv1Value<0 || argv1Value>100) {
            argv1Value = 0;
        }
        
        //Display the result with the given precision
        cout << "Result: " << fixed << setprecision(argc>1 ? argv1Value : 4) << stof(*result.begin()) << "\n" << endl;
    }
    
    return 0;
}