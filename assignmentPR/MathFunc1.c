/* 

MathFunc01.c
Written by Stephen White & Kalen Wood
9/23/18

*/

/* Import Statements (no math allowed) */
#include <stdlib.h>
#include <stdio.h>


/* Global Constants */
typedef int bool;
#define true 1
#define false 0

const int SAME_STRING = 0;          // Utility Constants
const int CHAR_ARRAY_SIZE_MAX = 80; // Array Size Constants
const int CHAR_ARRAY_SIZE_MIN = 40;
const int CHAR_ARRAY_SIZE_AVG = 60;

const int CONFIG_FILE_ERROR = -3; // Config File Error Code

const int WHITESPACE = 32;

const int SUCCESSFUL_EXECUTION = 0; // General Program Error/Sucess Codes
const int SUCCESSFUL_VALIDATION = 0;
const int FAILED_EXECUTION = -1;
const int INT_CONVERSION_ERROR = -1;

const char NULL_CHAR = '\0';
const char NEW_LINE = '\n';
const char CARRIAGE_RETURN = '\r';
const char TAB = '\t';
const char SEMICOLON = ';';
const char COLON = ':';
const char SPACE = ' ';
const char DOT = '.';
const char OPEN_PARENTHESES = '(';
const char CLOSED_PARENTHESES = ')';
const char *ZERO_STRING = "0";


/* Function Declarations */

bool characteristic(char numString[], int *c);

bool mantissa(char numString[], int *numerator, int *denominator);

void myStrCpy(char *string1, char *string2);

char *myStrCat(char *dest, const char *src);

void concatMultiple(int numArguments, char *dest, ...);

int compareString(const char *stringOne, const char *stringTwo);

int isSpace(unsigned char character);

int getDataTo(char *string, char delimeter, char *dataPtr);

void cleanCharArray(char *charArray, int arraySize);

char skipWhiteSpace(char *string);

int isNumericChar(char character);

int myAtoi(char *stringSequence);

void reverse(char string[]);

void intToString(int num, char string[]);

int myStrLen(char *string);

int tenToThePowerOf(int stringLength);


/* Function implementations */

int main()
{
    printf("\n\n");
    char number[] = "123.456";
    int c, n, d;

    bool result = mantissa(number, &n, &d);
    
    if(result == true)
    {
        printf("True\n");
        printf("n within main: %d\n", n);
        printf("d within main: %d\n", d);
    }
    else
    {
        printf("False\n");
    }

    /*
    //if the conversion from C string to integers can take place
    if (characteristic(number, &c) && mantissa(number, &n, &d))
    {
        //do some math with c, n, and d
    }
    else
    {
        //handle the error on input
    }*/
}

bool characteristic(char numString[], int* c)
{
    // If we can get data up to a decimal point, then true
    // if there is no decimal point, than go until \0 and return true 
       // Save the characteristic in c
    char num[CHAR_ARRAY_SIZE_MAX];
    cleanCharArray(num, CHAR_ARRAY_SIZE_MAX);
        
    int iterator;
    for(iterator = 0; numString[iterator] != '\0'; iterator++)
    {
        num[iterator] = numString[iterator];

        // Skip all whitespace 
        if (num[iterator] <= 32)
        {
            continue; 
        }

        // Catch all letters 
        if (!isNumericChar(num[iterator]) && numString[iterator] != '.')
        {
            return false;
        }

        // if we hit the delimeter 
        if(numString[iterator] == '.')
        {
            num[iterator] = '\0';
            *c = myAtoi(num);
            return true;
        }
    }

    // If the num string contains non-numeric vals, return false 
    return false;
}

bool mantissa(char numString[], int* numerator, int *denominator)
{
    // If we can get data up to a decimal point, that means we have a characteristic & mantissa 
       // Get data from the . to the \0 and if we can, return true
       // save the numerator and denominator

    char num[CHAR_ARRAY_SIZE_MAX];
    cleanCharArray(num, CHAR_ARRAY_SIZE_MAX);

    int iterator;
    for (iterator = 0; numString[iterator] != '\0'; iterator++)
    {
        num[iterator] = numString[iterator];

        // Skip all whitespace
        if (num[iterator] <= 32)
        {
            continue;
        }

        // Catch all letters
        if (!isNumericChar(num[iterator]) && numString[iterator] != '.')
        {
            return false;
        }

        // if we hit the delimeter
        if (numString[iterator] == '.')
        {
            numString[iterator++];
            cleanCharArray(num, CHAR_ARRAY_SIZE_MAX);
            break;            
        }
    }

    int newNumIterator = 0;
    for (iterator; numString[iterator] != '\0'; iterator++)
    {
        num[newNumIterator] = numString[iterator];
        printf("Char: %c\n\n", num[newNumIterator]);

        // Skip all whitespace
        if (num[newNumIterator] <= 32)
        {
            continue;
        }

        // Catch all letters
        if (!isNumericChar(num[newNumIterator]))
        {
            return false;
        }

        newNumIterator++;
    }

    // If the num string contains non-numeric vals, return false
    *numerator = myAtoi(num);
    *denominator = tenToThePowerOf(myStrLen(num));

    printf("In Mantissa -> numerator: %d\n", *numerator);
    printf("In Mantissa -> denominator: %d\n", *denominator);

    return true; 
}

int tenToThePowerOf(int stringLength)
{
    int answer = 1;
    int iterator;
    for (iterator = 0; iterator < stringLength; iterator++)
    {
        answer *= 10;
    }
    return answer;
}

/*

The two functions, characteristic() and mantissa(), 
will break a character array into a characteristic and a mantissa. The characteristic for 
the number 2.351 is 2 and the mantissa is 351 over 1,000. The characteristic for the number 
0.0125 is 0 and the mantissa is 125 over 10,000. The characteristic for the number -4.0 is -4 and 
the mantissa is 0 over 10. These values should be stored in the reference parameters c, numerator and
denominator. The C string may include leading or trailing spaces, unary plus or minus signs, integers,
or real numbers. Your functions must handle all of these cases. If an invalid string is passed in your
function will return false. If the passed in string was valid return true.

*/


/* Utility Functions */ 


// Function to copy the contents of one char array into another so that
// it will not be erased when a pointer is moved
void myStrCpy(char *destination, char *source)
{
    int index = 0;
    while (source[index] != NULL_CHAR)
    {
        destination[index] = source[index];
        index = index + 1;
    }
}

/* compares two strings, returns 0 for same, -1 for different.
   method adapted from online source:
   https://en.wikibooks.org/wiki/C_Programming/string.h/strcmp
*/
int compareString(const char *stringOne, const char *stringTwo)
{
    for (; *stringOne == *stringTwo; ++stringOne, ++stringTwo)
    {
        if (*stringOne == 0)
        {
            return 0;
        }
    }
    return *(unsigned char *)
                       stringOne < *(unsigned char *)stringTwo
               ? -1
               : 1;
}



// "clean out" a given char array by filling it entirely with the null char.
// this prevents the presence of any "UN-Readable" character within this array
void cleanCharArray(char *charArray, int arraySize)
{
    int index;
    for (index = 0; index < arraySize; index++)
    {
        charArray[index] = '\0';
    }
}



// Modified from https://www.geeksforgeeks.org/write-your-own-atoi/
// A utility function to check whether character is numeric
int isNumericChar(char character)
{
    return (character >= '0' && character <= '9') ? true : false;
}

// Modified from https://www.geeksforgeeks.org/write-your-own-atoi/
// A simple atoi() function. If the given string contains
// any invalid character, then this function returns INT_CONVERSION_ERROR
int myAtoi(char *stringSequence)
{
    if (compareString(stringSequence, "\0") == SAME_STRING)
    {
        return INT_CONVERSION_ERROR;
    }

    int result = 0; // Initialize result
    int index = 0;  // Initialize index of first digit

    // If number is negative, then fail gracefully
    if (stringSequence[0] == '-')
    {
        return INT_CONVERSION_ERROR;
    }

    // Iterate through all digits of input string and update result
    for (; stringSequence[index] != '\0'; ++index)
    {
        if (isNumericChar(stringSequence[index]) == false)
        {
            if ((int)(stringSequence[index] <= WHITESPACE))
            {
                continue;
            }
            else if (stringSequence[index] == '.')
            {
                break;
            }

            else
            {
                return INT_CONVERSION_ERROR;
            }
        }
        else
        {
            result = (result * 10) + stringSequence[index] - '0';
        }
    }
    return result;
}

/* Modified from https://en.wikibooks.org/wiki/C_Programming/stdlib.h/itoa */
void reverse(char string[])
{
    int count, stringLength;
    char character;

    for (count = 0, stringLength = myStrLen(string) - 1; count < stringLength;
         count++, stringLength--)
    {
        character = string[count];
        string[count] = string[stringLength];
        string[stringLength] = character;
    }
}


int myStrLen(char *string)
{
    int count = 0;
    while (string[count] != '\0')
    {
        count++;
    }
    return count;
}