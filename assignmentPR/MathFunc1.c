#include <stdlib.h>
#include <stdio.h>

typedef int bool;
#define true 1
#define false 0


bool characteristic(char numString[], int *c);
bool mantissa(char numString[], int *numerator, int *denominator);

bool characteristic(char numString[], int* c)
{
    return false;
}
bool mantissa(char numString[], int* numerator, int *denominator)
{
    return false; 
}

int main()
{
    char number[] = "123.456";
    int c, n, d;

    //if the conversion from C string to integers can take place
    if (characteristic(number, &c) && mantissa(number, &n, &d))
    {
        //do some math with c, n, and d
    }
    else
    {
        //handle the error on input
    }
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