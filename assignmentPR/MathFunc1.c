/*

MathFunc01.c
Written by Stephen White, Kalen Wood-Wardlow, & Gary Baker
9/23/18

*/

/* Import Statements (no math allowed) */
#include <stdlib.h>
#include <stdio.h>


/* Global Constants */
typedef int bool;
#define true 1
#define false 0

const int CHAR_ARRAY_SIZE_MAX = 80;
const int INT_CONVERSION_ERROR = -1;
const int WHITESPACE = 32;
const int SAME_STRING = 0;


/* Function Declarations */

bool characteristic(char numString[], int *c);

bool mantissa(char numString[], int *numerator, int *denominator);

int compareString(const char *stringOne, const char *stringTwo);

void cleanCharArray(char *charArray, int arraySize);

int isNumericChar(char character);

int myAtoi(char *stringSequence);

int myStrLen(char *string);

int tenToThePowerOf(int stringLength);


/* Function implementations */

int main(int argc, char *argv[])
{
    printf("\n");
    char number[] = "-0.456";

    int c, n, d;

    //if the conversion from C string to integers can take place
    if (characteristic(number, &c) && mantissa(number, &n, &d))
    {
        printf("Value of c: %d\n", c);
        printf("Value of n: %d\n", n);
        printf("Value of d: %d\n", d);
    }
    else
    {
        printf("\nInvalid number sequence.\n");
    }
    printf("\n");
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

    int negativeFlag = 0;
    char num[CHAR_ARRAY_SIZE_MAX];
    cleanCharArray(num, CHAR_ARRAY_SIZE_MAX);

    if (numString[0] == '-' && numString[1] == '0')
    {
        negativeFlag = 1;
    }

    int iterator;
    for (iterator = 0; numString[iterator] != '\0'; iterator++)
    {
        num[iterator] = numString[iterator];

        // Skip all whitespace
        if (num[iterator] <= WHITESPACE)
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

        // Skip all whitespace
        if (num[newNumIterator] <= WHITESPACE)
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
    if ( negativeFlag )
    {
        *numerator *= -1;
    }

    *denominator = tenToThePowerOf(myStrLen(num));

    return true;
}


/* Utility Functions */

/* compares two strings, returns 0 for same, -1 for different.
   method adapted from online source:
   https://en.wikibooks.org/wiki/C_Programming/string.h/strcmp
*/
int compareString(const char *stringOne, const char *stringTwo)
{
   // Iterate over the whole string
   for (; *stringOne == *stringTwo; ++stringOne, ++stringTwo)
   {
      // If we have reached the end of stringOne, these two are the same!
      if (*stringOne == 0)
      {
         return 0;
      }
   }
   // Determine if the strings are not the same
   return *(unsigned char *) stringOne < *(unsigned char *)stringTwo ? -1 : 1;
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
    return (character >= '0' && character <= '9' || character == '-') ? true : false;
}


// Modified from https://www.geeksforgeeks.org/write-your-own-atoi/
// A simple atoi() function. If the given string contains
// any invalid character, then this function returns INT_CONVERSION_ERROR
int myAtoi(char *stringSequence)
{
    int negativeFlag = 0;

    if (compareString(stringSequence, "\0") == SAME_STRING)
    {
        return INT_CONVERSION_ERROR;
    }

    int result = 0; // Initialize result
    int index = 0;  // Initialize index of first digit

    // If number is negative, then fail gracefully
    if (stringSequence[0] == '-')
    {
        negativeFlag = 1;
        index = 1;
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

    if ( negativeFlag == 1)
    {
        return -1 *result;
    }
    return result;
}


/* Returns the length of a char array */
int myStrLen(char *string)
{
    int count = 0;
    while (string[count] != '\0')
    {
        count++;
    }
    return count;
}


/* Returns the numeric value of 10 ^ stringLength */
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
