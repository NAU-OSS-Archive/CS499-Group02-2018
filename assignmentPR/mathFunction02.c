bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
...
...
 
 
char answer[100];
int c1, n1, d1;
int c2, n2, d2;
 
c1 = 1;
n1 = 1;
d1 = 2;
 
c2 = 2;
n2 = 2;
d2 = 3; 
 
//if the C string could hold at least the characteristic
if(add(c1, n1, d1, c2, n2, d2, answer, 100))
{
    //display string with answer 4.166666666...
}
else
{
    //display error message
}
