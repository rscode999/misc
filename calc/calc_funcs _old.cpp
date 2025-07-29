#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <list>
#include <string>
#include <vector>
using namespace std;

/**
 * Returns a vector of ints containing the indices of the innermost pairs of parentheses of `expression`.
 * 
 * An innermost set of parentheses has no other parentheses outside of it.
 * Adjacent indices in the output vector represent the beginning and end of an inner pair.
 * 
 * If `expression` has no inner pairs, the function returns the empty vector, i.e. `{}`.
 * 
 * If `expression` has incomplete inner pairs, or `expression` is empty, the function throws the `runtime_error` exception.
 * 
 * Example: `{"(", "(", "3", "/", "2", ")", "+", "2", ")", "+", "(" "7", "-", "9", ")", "+", "2"}`,
 * representing ((3/2)+2)+(7-9)+2:
 * 
 * Since indices 1 and 5 are parentheses with no other parentheses outside of them, indices 1 and 5 form an inner pair.
 * The same is true for indices 10 and 14.
 * Since the inner pairs are (1,5) and (10,14), the output should be a vector of length 4: {1, 5, 10, 14}.
 * 
 * @param expression the expression to find inner pairs in. Must be a valid expression vector
 * @return vector of ints whose indices are innermost pairs, with members of pairs being in adjacent indices
 */
vector<int> findInnerParentheses(list<string> expression) {
    //Throw exception if input is empty
    if(expression.size() <= 0) {
        throw runtime_error("Empty parentheses");
    }

    //Initialize the output
    vector<int> output = {};

    //To track parentheses layers to ensure complete pairs 
    int parenthesesLayers = 0;

    int index = 0;
    int innermostStart = 0;
    bool prevParenthesesOpening = false;

    //Iterate through the expression list
    for(string s : expression) {
        
        //If opening parentheses, mark the positions
        if(s=="(") {
            parenthesesLayers += 1;
            innermostStart = index;
            prevParenthesesOpening = true;
        }
        //If closing parentheses (inner pair found), add the position and the previously marked position to the output
        else if(s==")") {
            parenthesesLayers -= 1;

            if(prevParenthesesOpening) {
                output.push_back(innermostStart);
                output.push_back(index);
            }

            prevParenthesesOpening = false;
        }

        index += 1;
    }

    //If not equal numbers of open and closed parentheses, there's a syntax error
    if(parenthesesLayers != 0) {
        throw runtime_error("Parentheses were not closed");
    }

    return output;
}




/**
 * Returns a list of one element representing the input's result.
 * 
 * Calculation should follow the order of operations:
 * powers first, then multiplication/division, then addition/subtraction.
 * 
 * The result of the calculation should be stored as a string at the only index of the input.
 * 
 * If there are two operators or numbers in a row, the method should throw a `runtime_error`.
 * 
 * If the input contains a single number, the output is that number.
 * 
 * Example: if `inputExpression` equals `{"3", "+", "2", "*", "4"}`, 
 * the result should be `{"11"}`
 * 
 * @param inputExpression the expression list to evaluate. Must be a valid expression list WITHOUT parentheses
 * @return expression list containing the result in the leftmost index
 */
list<string> evalPartialExpression(list<string> inputExpression) {

    //Check for parentheses
    for(string s : inputExpression) {
        try {
            float f = stof(s);
        }
        catch(invalid_argument& excep) {
            if(!(s=="+" || s=="-" || s=="*" || s=="/" || s=="^")) {
                throw runtime_error("ERROR- INVALID SYMBOL IN PARTIAL EXPRESSION- '" + s + "'");
            }
        }
    }

    //Check for single number. If so, return that number
    if(inputExpression.size()==1) {
        try {
            float f = stof(*inputExpression.begin());
            // cout << "asdkfjasdf" << endl;
            return {*inputExpression.begin()};
        }
        catch(invalid_argument& excep) {
            throw runtime_error("Syntax error- single-value expression is not a number");
        }
    }

    //The expression to output
    list<string> expr = inputExpression;


    //Make 3 passes over the list: for powers (type 1), multiplication/division (type 2), addition/subtraction (type 3)
    for(int currentOperatorType=1; currentOperatorType<=3; currentOperatorType++) {

        //Used to iterate over the expression list
        list<string>::iterator currentPosition = expr.begin();
        
        //Do the pass over the list
        while(currentPosition != expr.end()) {

            //If the desired operator is found, evaluate
            if((currentOperatorType==1 &&  *currentPosition=="^")
            || (currentOperatorType==2 && (*currentPosition=="*" || *currentPosition=="/"))
            || (currentOperatorType==3 && (*currentPosition=="+" || *currentPosition=="-"))) {

                //Safety check: ensure the operator is not at the beginning or end
                if(*currentPosition==expr.front() || *currentPosition==expr.back()) {
                    throw runtime_error("Syntax error- operators cannot begin or end an expression");
                }

                float operand1;
                string calcOperator;
                float operand2;
                float result;
                
                //Get the two operands and the operator. If any of the operands is not a number, throw a runtime_error
                currentPosition--;
                try {
                    operand1 = stof(*currentPosition);
                    currentPosition++;
                    calcOperator = *currentPosition;
                    currentPosition++;
                    operand2 = stof(*currentPosition);
                }
                catch(invalid_argument& excep) {
                    throw runtime_error("Syntax error- cannot have two operators in a row");
                }

                //Do the operation (switch statements didn't work)
                if(calcOperator=="^") {
                    result = pow(operand1, operand2);
                }
                else if(calcOperator=="*") {
                    result = operand1 * operand2;
                }
                else if(calcOperator=="/") {
                    //Throw exception if division by zero would occur
                    if(operand2==0) {
                        throw runtime_error("Arithmetic error- division by zero");
                    }
                    result = operand1 / operand2;
                }
                else if(calcOperator=="+") {
                    result = operand1 + operand2;
                }
                else if(calcOperator=="-") {
                    result = operand1 - operand2;
                }
                //If the operator is not valid, throw the exception
                else {
                    throw runtime_error("Syntax error- invalid operator used");
                }

                //Move the iterator to the first operand's position
                list<string>::iterator evaluatedStart = currentPosition;
                evaluatedStart--;
                evaluatedStart--;

                //Insert result
                expr.insert(evaluatedStart, to_string(result));

                //Remove the evaluated portion
                list<string>::iterator evaluatedEnd = currentPosition;
                evaluatedEnd++;


                // cout << *currentPosition << endl;
                // cout << *evaluatedStart << endl;
                // cout << *evaluatedEnd << endl;

                expr.erase(evaluatedStart, evaluatedEnd);
            }

            currentPosition++;
            //END OF CURRENT OPERATION EVALUATION
        }

        //END OF OVERALL EXPRESSION EVALUATION
    }

    //There should be a single number remaining. If not, throw exception
    if(expr.size() > 1) {
        throw runtime_error("Syntax error- too many numbers");
    }

    try {
        float test = stof(expr.front());
    }
    catch(invalid_argument& excep) {
        throw runtime_error("Syntax error- too many operators");
    }

    return expr;
}




/**
 * Returns a (linked) list of strings representing the result of an expression.
 * 
 * The output should have the expression's result, as a string, as the only element of the list.
 * 
 * Example: `{"(", "3", "+", "2", ")", "/", "5"}`, representing (3+2)/5:
 * The output should be `{"1"}`
 * 
 * Any invalid parentheses arrangements or division by zero should cause a `runtime_exception`.
 * 
 * If given an expression with a single number, the function should return a list containing the single number as a string.
 * 
 * This function may modify its input.
 * 
 * @param inputExpression the expression list to evaluate. Must be a valid expression list
 * @return expression list representing the evaluated expression
 */
list<string> evalFullExpression(list<string> inputExpression) {

    list<string> expr = inputExpression;
    
    //Find the outermost pair of parentheses. Mark their positions.
    vector<int> parenthesesIndexes = findInnerParentheses(expr);

    //Calculate all indices inside parentheses until there are none left.
    while(parenthesesIndexes.size() > 0) {

        //Load from the back
        int currentParenthesesIndex = parenthesesIndexes.size()-1;
        int currentExprIndex = expr.size()-1;
        auto exprIterator = expr.rbegin();

        int loadingStatus = 0; //0=partial expression not found yet, 1=loading, 2=done
        list<string> partialExpr = {};

        reverse_iterator<list<string>::iterator> partialExprEndInd;

        while(exprIterator != expr.rend()) {
            
            //Change loading status if a parentheses index is found
            if(currentExprIndex == parenthesesIndexes[currentParenthesesIndex]) {
                // cout << "Load begin at: " << parenthesesIndexes[currentParenthesesIndex] << endl;

                partialExprEndInd = exprIterator;
                currentParenthesesIndex -= 1;
                loadingStatus += 1;
            }

            //If loading, load the partial expression
            if(loadingStatus==1) {
                partialExpr.push_front(*exprIterator);
            }
            //If done, remove the parentheses indices and stop loading
            if(loadingStatus==2) {
                partialExpr.push_front(*exprIterator);
                // cout << "Load stop" << endl;
                break;
            }

            currentExprIndex -= 1;
            exprIterator++;

            //END WHILE
        }

        //Remove the parentheses
        partialExpr.pop_front();
        partialExpr.pop_back();

        // cout << "Partial Expr: " << flush;
        // for(string s : partialExpr) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;

        //EVALUATE THE PARTIAL EXPRESSION
        list<string> result = evalPartialExpression(partialExpr);

        // cout << "Result: " << flush;
        // for(string s : result) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;

        //Insert the result, remove the partial expression
        //TODO: CONVERT PARENTHESES INDEXES TO LINKED LIST, ITERATE FROM THE FRONT
        list<string>::iterator start = expr.begin();
        list<string>::iterator end = expr.begin();
        advance(start, parenthesesIndexes[parenthesesIndexes.size()-2]);
        advance(end, parenthesesIndexes[parenthesesIndexes.size()-1]+1);

        expr.insert(start, *result.begin());
        expr.erase(start, end);
        
        parenthesesIndexes.pop_back();
        parenthesesIndexes.pop_back();

        // for(string s : expr) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;

        //Recalculate outermost parentheses (very inefficient. I really need this to work)
        parenthesesIndexes = findInnerParentheses(expr);
    }

    //Do one final evaluation run
    expr = evalPartialExpression(expr);
            
    return expr;
}



//IMPORTANT: NO MAIN!!!