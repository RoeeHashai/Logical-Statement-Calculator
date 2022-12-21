#include <stdio.h>

#define DIFFERENCE_UPPER_LOWER_ASCII ('a' - 'A')
#define DECIMAL 10

void printMenu();

void printExitMessage();

void printErrorMessage();

int getChoice();

void bufferSkip();

int isCharVariableValid(char variable);

int isOperationValid(char operation);

int areEqualChars(char variable1, char variable2,
                  long long numVar1, long long numVar2);

int isCharNum(char variable);

char modifyOperator(char operation, int notChar);

int convertCharNumToNum(char variable);

int oneStatementCalc();

void LogicalStatementManager();

int countDigitsInNum(long long num, int digit);

void countDigitsInNumManager();

long long max(long long num1, long long num2);

long long gcd(long long num1, long long num2);

void gcdCalculatorManager();

enum statementStatus {
    false, true, syntaxError, enterError
};

enum notChar {
    noNot, hasNot
};

int main() {
    char choice;
    do {
        printMenu();
        choice = getChoice();
        switch (choice) {
            case '1':
                LogicalStatementManager();
                break;
            case '2':
                countDigitsInNumManager();
                break;
            case '3':
                gcdCalculatorManager();
                break;
            case '4':
                printExitMessage();
                break;
            case '\n':
                printErrorMessage();
                break;
            default:
                printErrorMessage();
                bufferSkip();
                break;
        }
    } while (choice != '4');
    return 0;
}

/***********************************************************************
* function name: printMenu
* The Input: no input
* The output: no output
* The Function operation: print the menu
***********************************************************************/
void printMenu() {
    printf("Choose an option:\n\t"
           "1: Logical Statement Calculator\n\t"
           "2: Count digit in a number\n\t"
           "3: GCD Calculator\n\t"
           "4: Exit\n");
}

/***********************************************************************
* function name: printExitMessage
* The Input: no input
* The output: no output
* The Function operation: print the exit message
***********************************************************************/
void printExitMessage() {
    printf("So Long, and Thanks for All the Fish!\n");
}

/***********************************************************************
* function name: printErrorMessage
* The Input: no input
* The output: no output
* The Function operation: prints the error message
***********************************************************************/
void printErrorMessage() {
    printf("Fool of a Took!\n"
           "This is a serious journey, not a hobbit walking-party.\n"
           "Throw yourself in next time, and then you will be no further "
           "nuisance.\n");
}

/***********************************************************************
* function name: getChoice
* The Input: no input
* The output: the users choice
* The Function operation: returns the users choice of user
***********************************************************************/
int getChoice() {
    return getchar();
}

/***********************************************************************
* function name: bufferSkip
* The Input: no input
* The output: no output
* The Function operation: gets to the next whitespace in buffer(next word),
* or to the end of line.
***********************************************************************/
void bufferSkip() {
    char tempChar = getchar();
    while (tempChar != ' ') {
        // if the char is Enter so buffer is empty done reading from buffer
        if (tempChar == '\n') break;
        tempChar = getchar();
    }

}

/***********************************************************************
* function name: isCharVariableValid
* The Input: char variable
* The output: true/false(1/0)
* The Function operation: checks if variable is a valid char by ascii value and
* return true/false accordingly. valid chars are Alphabet letters and numbers
***********************************************************************/
int isCharVariableValid(char variable) {
    if ((variable >= 'A' && variable <= 'Z') ||
        (variable >= 'a' && variable <= 'z'))
        return true;
    else if (variable >= '0' && variable <= '9')
        return true;
    else
        return false;
}

/***********************************************************************
* function name: isOperationValid
* The Input: char operation
* The output: true/false(1/0)
* The Function operation: checks if operation is a valid operation
***********************************************************************/
int isOperationValid(char operation) {
    if (operation == '<' || operation == '>' || operation == '=')
        return true;
    else
        return false;
}

/***********************************************************************
* function name: isEqualChar
* The Input: char variables and number variables
* The output: true/false(1/0)
* The Function operation: in case of mixed complex comparison chars between
* numbers, the function determines if the chars are the same char(upper and
* lower) and determines if the char in upper case is equal to the char ascii
* value in lower case
***********************************************************************/
int areEqualChars(char variable1, char variable2,
                  long long numVar1, long long numVar2) {
    if ((variable1 - variable2 == DIFFERENCE_UPPER_LOWER_ASCII) ||
        (variable2 - variable1 == DIFFERENCE_UPPER_LOWER_ASCII) ||
        (variable1 + DIFFERENCE_UPPER_LOWER_ASCII == numVar2) ||
        (variable2 + DIFFERENCE_UPPER_LOWER_ASCII == numVar1))
        return true;
    else
        return false;
}

/***********************************************************************
* function name: isCharNum
* The Input: char variable
* The output: true/false(1/0)
* The Function operation: gets a char and returns if the char is a number by
* its ascii value
***********************************************************************/
int isCharNum(char variable) {
    if (variable >= '0' && variable <= '9')
        return true;
    else
        return false;
}

/***********************************************************************
* function name: modifyOperator
* The Input: char operation and int not char(status)
* The output: char operation
* The Function operation: gets the operation and modify the char to the
* opposite operation if the expression has a not char
***********************************************************************/
char modifyOperator(char operation, int notChar) {
    if (notChar == hasNot && operation == '>')
        return '<';
    else if (notChar == hasNot && operation == '<')
        return '>';
    else
        return operation;
}

/***********************************************************************
* function name: convertCharNumToNum
* The Input: char variable
* The output: number
* The Function operation: gets a number char, returns its numeric value as int
***********************************************************************/
int convertCharNumToNum(char variable) {
    return variable - '0';
}

/***********************************************************************
* function name: oneStatementCalc
* The Input: no input
* The output: int result of the logical expression
* The Function operation: the function calculates one logical expression
* determines its value and checks for invalid inputs
***********************************************************************/
int oneStatementCalc() {
    // variable declaration, initialization.
    int notChar = noNot;
    long long numVar1 = 0, numVar2 = 0;
    char firstChar, lastChar, variable1, operation, variable2;

    // read from buffer the first char, and determine if its ~ or ( or invalid
    firstChar = getchar();
    if (firstChar == '~') {
        notChar = hasNot;
        firstChar = getchar();
        if (firstChar == '\n')
            return enterError;
        else if (firstChar != '(')
            return syntaxError;
    } else if (firstChar == '\n') {
        return enterError;
    } else if (firstChar != '(') {
        return syntaxError;
    }
    // read from buffer the first variable and check if valid
    variable1 = getchar();
    if (variable1 == '\n' || variable1 == ' ')
        return enterError;
    else if (!isCharVariableValid(variable1))
        return syntaxError;

    /* treatment in case of number variable, else gets the ascii value of char
    * get the next char in buffer and assign it to be operation */
    if (isCharNum(variable1)) {
        while (isCharNum(variable1)) {
            numVar1 = (numVar1 * DECIMAL) + convertCharNumToNum(variable1);
            variable1 = getchar();
        }
        operation = variable1;

    } else {
        numVar1 = (long long) variable1;
        operation = getchar();
    }

    // check if operation is valid
    if (operation == '\n' || operation == ' ')
        return enterError;
    else if (!isOperationValid(operation))
        return syntaxError;

    // read from buffer the second variable and check if valid
    variable2 = getchar();
    if (variable2 == '\n' || variable2 == ' ')
        return enterError;
    else if (!isCharVariableValid(variable2))
        return syntaxError;

    /* treatment in case of number variable, else gets the ascii value of char
    * get the next char in buffer and assign it to be lasChar */
    if (isCharNum(variable2)) {
        while (isCharNum(variable2)) {
            numVar2 = (numVar2 * DECIMAL) + convertCharNumToNum(variable2);
            variable2 = getchar();
        }
        lastChar = variable2;
    } else {
        numVar2 = (long long) variable2;
        lastChar = getchar();
    }
    // check if last char is valid
    if (lastChar == '\n')
        return enterError;
    else if (lastChar != ')')
        return syntaxError;

    // modify operation if needed
    operation = modifyOperator(operation, notChar);

    /* return the value of the logical operation after valid checks and after
    * modifying according to not char, check if operation is valid */
    switch (operation) {
        case '>':
            if (numVar1 > numVar2)
                return true;
            else
                return false;
        case '<':
            if (numVar1 < numVar2)
                return true;
            else
                return false;
        case '=':
            /* check if the numbers are equal or the chars are equal of if
            * the char is equal to it's the uppercase ascii value*/
            if (numVar1 == numVar2 || variable1 == variable2 ||
                areEqualChars(variable1, variable2, numVar1, numVar2)) {
                if (notChar)
                    return false;
                else
                    return true;
            } else
                return false;
        default:
            return false;

    }
}

/***********************************************************************
* function name: LogicalStatementManager
* The Input: no input
* The output: no output
* The Function operation: calculates multiple logical expressions and prints
* the logical value of them
***********************************************************************/
void LogicalStatementManager() {
    // variable declaration, initialization, get input if buffer is empty
    char currentChar;
    int logicalExpression1, logicalExpression2;
    printf("\nPlease write your logical statement: ");
    currentChar = getchar();


    // get the logical value of the first expression
    logicalExpression1 = oneStatementCalc();
    // valid checks
    if (logicalExpression1 == enterError) {
        printf("You have a syntax error in your statement.\n");
        return;
    } else if (logicalExpression1 == syntaxError) {
        printf("You have a syntax error in your statement.\n");
        // if error in the middle of a word ge to the next one with skip buffer
        bufferSkip();
        return;
    }

    currentChar = getchar();
    // if the currentChar is ' '/Enter-there isn't any more expressions to calc
    if (currentChar == '\n' || currentChar == ' ') {
        switch (logicalExpression1) {
            case true:
                printf("The statement is true.\n");
                return;
            case false:
                printf("The statement is false.\n");
                return;
            default:
                return;
        }
        /* the loop will always compare between two logical expressions put its
        * result into logicalExpression1 and then proceed until the end of the
        * all expression */
    } else {
        while (currentChar != ' ') {
            switch (currentChar) {
                case '&':
                    // calculate the second expression
                    logicalExpression2 = oneStatementCalc();
                    // error checks
                    if (logicalExpression2 == enterError) {
                        logicalExpression1 = enterError;
                        break;
                    } else if (logicalExpression2 == syntaxError) {
                        logicalExpression1 = syntaxError;
                        break;
                        // implement the && operand between the logical statements
                    } else if (logicalExpression1 == true &&
                               logicalExpression2 == true) {
                        logicalExpression1 = true;
                        break;
                    } else {
                        logicalExpression1 = false;
                        break;
                    }

                case '|':
                    // calculate the second expression
                    logicalExpression2 = oneStatementCalc();
                    // error checks
                    if (logicalExpression2 == enterError) {
                        logicalExpression1 = enterError;
                        break;
                    } else if (logicalExpression2 == syntaxError) {
                        logicalExpression1 = syntaxError;
                        break;
                        // implement the && operand between the logical statements
                    } else if (logicalExpression1 == true ||
                               logicalExpression2 == true) {
                        logicalExpression1 = true;
                        break;
                    } else {
                        logicalExpression1 = false;
                        break;
                    }
                default:
                    printf("You have a syntax error in your statement.\n");
                    bufferSkip();
                    return;
            }
            currentChar = getchar();
            // if the current char is Enter the expression is at the end
            if (currentChar == '\n') break;
        }

        // prints the value of all the logical comparisons
        switch (logicalExpression1) {
            case true:
                printf("The statement is true.\n");
                return;
            case false:
                printf("The statement is false.\n");
                return;
            case syntaxError:
                printf("You have a syntax error in your statement.\n");
                bufferSkip();
                return;
            case enterError:
                printf("You have a syntax error in your statement.\n");
                return;
        }
    }
}

/***********************************************************************
* function name: max
* The Input: num1, num2
* The output: int
* The Function operation: returns the maximum value of num1, num2
***********************************************************************/
long long max(long long num1, long long num2) {
    return (num1 > num2) ? num1 : num2;
}

/***********************************************************************
* function name: countDigitsInNum
* The Input: num, digit
* The output: int
* The Function operation: a recursive function that returns the amount of times
* the digits is in a number
***********************************************************************/
int countDigitsInNum(long long num, int digit) {
    // break condition
    if (num == 0)
        return 0;
        // if the last digits is equal to the digit add one to the calc(at the end)
    else if (num % DECIMAL == digit)
        return countDigitsInNum(num / DECIMAL, digit) + 1;
        // the digits aren't equal
    else
        return countDigitsInNum(num / DECIMAL, digit);
}

/***********************************************************************
* function name: countDigitsInNumManager
* The Input: no input
* The output: no output
* The Function operation: prints the amount of times a digit is in a number
***********************************************************************/
void countDigitsInNumManager() {
    // variable declaration, initialization, get input from user
    long long num;
    int count, digit;
    printf("\nEnter a number and a digit: ");
    scanf("%lld %d", &num, &digit);
    // valid checks
    if (num < 0 || digit >= DECIMAL || digit < 0) {
        printf("You should stay positive, and so should your input.\n");
        getchar();
        return;
        // calc a specific input
    } else if (num == 0 && digit == 0)
        count = 1;
    else
        count = countDigitsInNum(num, digit);
    printf("The digit %d appears %d times in the number %lld\n",
           digit, count, num);
    getchar();
}

/***********************************************************************
* function name: gcd
* The Input: num1, num2
* The output: int
* The Function operation: a recursive function that returns the largest GCD
* of 2 numbers and prints its calculations
***********************************************************************/
long long gcd(long long num1, long long num2) {
    // breaking condition
    if (num2 == 0) {
        printf("GCD = %d\n", num1);
        return num1;
    } else {
        printf("%lld*%lld+%lld = %lld (num1=%lld, num2=%lld)\n",
               num2, (num1 / num2), (num1 % num2), num1, num1, num2);
        return gcd(num2, num1 % num2);
    }
}

/***********************************************************************
* function name: gcdCalculatorManager
* The Input: no input
* The output: no output
* The Function operation: prints the largest GCD of 2 numbers
***********************************************************************/
void gcdCalculatorManager() {
    // variable declaration, initialization, get input from user
    long long num1, num2;
    printf("\nEnter two positive numbers: ");
    scanf("%lld %lld", &num1, &num2);
    // valid checks
    if (num1 < 0 || num2 < 0) {
        printf("You should stay positive, and so should your input.\n");
        getchar();
        return;
    }
    // send to the function the max from num1 and num2
    if (num1 == max(num1, num2)) gcd(num1, num2);
    else gcd(num2, num1);
    getchar();
}