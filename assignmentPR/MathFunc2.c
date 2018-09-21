typedef int bool;
#define true 1
#define false 0


bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

// Code Here

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{

}

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{

}


char answer[100];

 
int c1 = 1;
int n1 = 1;
int d1 = 2;
 
int c2 = 2;
int n2 = 2;
int d2 = 3;

int main(void)
{
    //if the C string could hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 100))
    {
        //display string with answer 4.166666666...
    }
    else
    {
        //display error message
    }

}
