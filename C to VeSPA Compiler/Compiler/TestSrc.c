float function1(int x, float y, float z);

int main()
{
    //float z, y;
    float z = 3.3, y = 5.8;
    unsigned int x;
    int array[3];

    z = 3.3;
    y = 5.8;                        //show type check
    x = 4 + (-3 + 4) + array[2];    //show array range

    x = x / 1;                      //show divison by 0

    float ret = function1(x, y, z);             //show number of arguments and type check

    {
        //int j;
        int* ptr;
        int* ptr2;
        ptr = ptr2;                 //show pointer type check
    }

    {
        int counter = 250;          //show creation of a new scope
        
        while(counter > 0)
        {
            counter --;
        }
    }
    return x;                       //show return type check
}


float function1(int x, float y, float z)
{   
    float res;
    if((x<<3) > 0)
    {
        res = y + z;
    }
    else
    {
        float res_aux = 1.0;
        res = res_aux;
    }
    return res;
}