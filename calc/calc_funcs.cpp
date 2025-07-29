#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;


/**
 * Returns a (linked) list of ints containing the indices of the innermost pairs of parentheses of `expression`.
 * 
 * An innermost pair of parentheses has no other parentheses inside of it.
 * Adjacent indices in the output list should represent the beginning and end of an inner pair.
 * 
 * Example: `{"(", "(", "3", "/", "2", ")", "+", "2", ")", "+", "(" "7", "-", "9", ")", "+", "2"}`,
 * representing ((3/2)+2)+(7-9)+2:
 * 
 * Since indices 1 and 5 are parentheses with no other parentheses outside of them, indices 1 and 5 form an inner pair.
 * The same is true for indices 10 and 14.
 * The inner pairs are (1,5) and (10,14), so the output should be a list of length 4: `{1, 5, 10, 14}`.
 * 
 * If `expression` has incomplete inner pairs, or `expression` is empty, the function throws the `runtime_error` exception.
 * 
 * If `expression` has no inner pairs, the function returns the empty list, i.e. `{}`.
 * 
 * @param expression the expression to find inner pairs in. Must be a valid expression list
 * @return (linked) list of ints whose indices are innermost pairs, with members of pairs being in adjacent indices
 */
list<int> findInnerParentheses(list<string> expression) {
    //Throw exception if input is empty
    if(expression.size() <= 0) {
        throw runtime_error("Empty parentheses");
    }

    //Initialize the output
    list<int> output = {};

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
 * Returns a list of one element representing the given partial expression's result.
 * A partial expression has no parentheses.
 * 
 * Calculation should follow the order of operations:
 * powers first, then multiplication/division, then addition/subtraction.
 * Example: if `inputExpression` equals `{"3", "+", "2", "*", "4"}`, 
 * the result should be `{"11"}`, not `{"20"}`.
 * 
 * If there are two operators or numbers in a row, the method should throw a `runtime_error`.
 * 
 * If the input contains a single number, the output is that number.
 * 
 * @param inputExpression the expression list to evaluate. Must be a non-empty list containing a partial expression
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
            || (currentOperatorType==2 && (*currentPosition=="*" || *currentPosition=="/" || *currentPosition=="%"))
            || (currentOperatorType==3 && (*currentPosition=="+" || *currentPosition=="-"))) {

                //Safety check: ensure the operator is not at the beginning or end
                if(currentPosition==expr.begin() || currentPosition==expr.end()) {
                    throw runtime_error("Syntax error- operators cannot begin or end an expression");
                }

                float operand1;
                string calcOperator;
                float operand2;
                float result;
                
                //Get the two operands and the operator. If any of the operands is not a number, throw a runtime_error
                try {
                    currentPosition--;
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
                expr.erase(evaluatedStart, evaluatedEnd);
            }


            currentPosition++;  
            //END OF CURRENT OPERATION EVALUATION
        }

        //END OF OVERALL EXPRESSION EVALUATION
    }

    //There should be a single number remaining. If not, throw exception
    if(expr.size() > 1) {
        throw runtime_error("Syntax error- too many numbers. Note: You must use the '*' operator in multiplication");
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
 * The output should have the expression's result, as a string, as the only element of the list.
 * 
 * Example: `{"(", "3", "+", "2", ")", "/", "5"}`, representing (3+2)/5:
 * The output should be `{"1"}`
 * 
 * Any invalid parentheses arrangements, syntax errors, or division by zero should cause a `runtime_exception`.
 * 
 * If given an expression with a single number, the function should return a list containing the single number as a string.
 * 
 * @param inputExpression the expression list to evaluate. Must be a valid expression list
 * @return expression list representing the evaluated expression
 */
list<string> evalFullExpression(list<string> inputExpression) {

    list<string> expr = inputExpression;
    
    //Find the innermost pair of parentheses. Mark their positions.
    list<int> parenthesesIndexes = findInnerParentheses(expr);

    //Load partial expression from the front
    list<string>::iterator exprIterator = expr.begin(); //Current index in the full expression
    int currentExprIndex = 0; //The current index number in the full expr.

    int loadingStatus = 0; //0=partial expression not found yet, 1=loading, 2=done
    list<int>::iterator currentParenthesesIter = parenthesesIndexes.begin(); //Index of the parentheses pairs

    //Calculate all indices inside parentheses until there are none left.
    while(parenthesesIndexes.size() > 0) {

        list<string> partialExpr = {}; //The current partial expression
        list<string>::iterator partialExprStartIter = exprIterator; //Used to mark the start of the partial expression

        // cout << "Parentheses Indexes Remaining: ";
        // for(int j : parenthesesIndexes) {
        //     cout << j << " ";
        // }
        // cout << endl;
        
        loadingStatus = 0;
        //Find and load the next partial expression
        while(exprIterator != expr.end()) { 
            
            //Change loading status if a parentheses index is found
            if(currentExprIndex == *currentParenthesesIter) {
                loadingStatus += 1;
                currentParenthesesIter++;
            }

            //If no inner parentheses found yet, advance partial expression start
            if(loadingStatus==0) {  
                partialExprStartIter++;
            }
            //If loading, load the partial expression
            else if(loadingStatus==1) {
                partialExpr.push_back(*exprIterator);
            }
            //If done, stop loading
            else if(loadingStatus==2) {
                partialExpr.push_back(*exprIterator);
                // cout << "Load stop at index " << currentExprIndex << endl;
                break;
            }

            //Move to next index, update current index
            exprIterator++;
            currentExprIndex += 1;
            
            //END WHILE
        }

        /*
        At this point:
        -`partialExprStart` marks the position in `expr` where the partial expression begins

        -`exprIterator` is at the end of the partial expression
        -`currentExprIndex` equals the index number of the end of the partial expr.

        -`partialExpr` contains the current partial expression along with its surrounding parentheses
        */

        // cout << "Partial Expr: " << flush;
        // for(string s : partialExpr) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;
        // cout << "Expression Start: " << *partialExprStartIter << endl;
        // cout << "Current Symbol: " << *exprIterator << endl;

        //Remove the parentheses
        partialExpr.pop_front();
        partialExpr.pop_back();


        //EVALUATE THE PARTIAL EXPRESSION (if it's full)
        list<string> result = {};
        if(partialExpr.size() > 0) {
            result = evalPartialExpression(partialExpr);
        }
        else {
            throw runtime_error("Syntax error- incomplete expression inside parentheses");
        }

        // cout << "Result: " << flush;
        // for(string s : result) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;

        //Insert the result, remove the newly evaluated partial expression
        list<string>::iterator start = partialExprStartIter;
        list<string>::iterator end = exprIterator;
        end++;

        expr.insert(start, *result.begin());
        expr.erase(start, end);
        
        parenthesesIndexes.pop_front();
        parenthesesIndexes.pop_front();

        // cout << "Expression after removal: " << flush;
        // for(string s : expr) {
        //     cout << "'" << s << "' ";
        // }
        // cout << endl;

        //Recalculate outermost parentheses if there are no more
        if(parenthesesIndexes.size() == 0) {
            parenthesesIndexes = findInnerParentheses(expr);

            if(parenthesesIndexes.size() != 0) {
                exprIterator = expr.begin();
                currentExprIndex = 0;
                currentParenthesesIter = parenthesesIndexes.begin();
            }
        }
        //If there are no more parentheses, the loop will exit
    }

    // cout << "Final expression: " << flush;
    // for(string s : expr) {
    //     cout << "'" << s << "' ";
    // }
    // cout << endl;

    //Do one final evaluation run
    list<string> output = evalPartialExpression(expr);
    return output;
}



//IMPORTANT: NO MAIN!!!