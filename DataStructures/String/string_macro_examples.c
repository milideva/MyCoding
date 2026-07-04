#include <stdio.h>

/*
  Problem: C Macro Stringization and Concatenation

  Description:
  Demonstrate the use of '#' (stringize) and '##' (token pasting) 
  operators in C macros.

  Macro Operators:
  1. '#' (Stringize): Converts a macro parameter into a string literal.
  2. '##' (Concatenate): Joins two tokens together into a single token.
*/

#define STRINGIZE(x) #x
#define CONCAT(a, b) a##b

#define PRINT_INT(n) printf(#n " = %d\n", n)

int main() {
    // 1. Stringization
    printf("Stringized: %s\n", STRINGIZE(Hello World));
    
    // 2. Concatenation
    int myVar = 10;
    int CONCAT(other, Var) = 20; 
    int CONCAT(test, 1) = 42;
    printf("Concatenated variable test1: %d\n", test1);

    // 3. combined
    PRINT_INT(test1);

    return 0;
}
