//ABI Defines that:
//Frame Pointer(FP) is Register R2 
//Stack Pointer(SP) is Register R3

int y; //this is placed at 0x00 (global scope)

int foo(int a, int b);


int main()
{
    int result;    //placed in stack(FP - 2)
    int x = 6;     //placed in stack(FP - 3) 
    y = 4;

    result = foo(x, y);

    return 0;
}


int foo(int a, int b)   
{
    //arg a placed in stack(FP + 2)
    //arg b placed in stack(FP + 1)

    int sum; //placed in stack (FP - 2)
    
    if(a > 5)
        sum = a + b;
    else
        sum = a * b;

    return sum;
}