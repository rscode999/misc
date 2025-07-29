# C++ Command-Line Calculator
Text-based four-function calculator that supports order of operations  

Evaluates a mathematical expression entered by the user. The results respect the order of operations (parentheses, exponentials, multiplication/division, addition/subtraction).  
The program can detect errors such as unmatched parentheses and division by zero without crashing.


### Compilation Instructions
Compile `calc.cpp` as the main function. The program should compile when using C++11 and later.  
`calc_funcs.cpp` contains helper functions unrelated to taking the user's input.


### Run Instructions
When prompted, enter a mathematical expression, then press Enter. The result of the calculation will be printed. 

Supported operators include: 
- `+`- addition
- `-`- subtraction
- `*`- multiplication
- `/`- division
- `^`- exponentiation
- `(`, `)`- parentheses (to group expressions)  
Use `n` to denote a negative sign.

Examples:  
`(3+2)*9` evaluates to 45.  
`3+4*0` evaluates to 3.  
`n3*2+10` evaluates to 4.  
`3^4+1` evaluates to 82.

### Testing Instructions
Compile and run `test.cpp`. Each function inside `test.cpp` that starts with "test" is a unit test for a function. 

I recommend running the tests in this order: `findInnerParentheses` `evalPartialExpression`, `evalFullExpression`.