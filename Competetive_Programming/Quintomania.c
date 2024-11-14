#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long Parselongeger(char* input, long length)
{
	long power = 0;
	long num = 0;
	for (long i = 0; i < length; i++)
	{
		char current = *(input + length - 1 - i);
		if ((current >= 48) && (current < 59))
		{
			num += (current - 48) * pow(10, power);
			power++;
		}
	}
	return num;
}
long Parselongegers(char* input, long length, long* out, long outCount)
{
	char reading = 0;
	long count = -1;
	long power = 0;
	long num = 0;
	if (outCount == 1)
	{
		*out = Parselongeger(input, length) + 1;
		return 0;
	}
	for (long i = 0; (i < length) && (count < outCount); i++)
	{
		char current = *(input + length - 1 - i);
		if ((current >= 48) && (current < 59))
		{
			if (!reading) { count++; }
			reading = 1;
			
			num += (current - 48) * pow(10, power);
			power++;
		}
		else
		{
			if (reading)
			{
				if ((count >= 0)  && (i < length))
				{
					*(out + outCount - 1 - count) = num;
					num = 0;
					power = 0;
				}		
				reading = 0;				
			}
		}
		if (reading && (i == length - 1) && (i < length))
		{
			if (count >= 0)
			{
				*(out + outCount - 1 - count) = num;
				num = 0;
				power = 0;
			}		
			reading = 0;	
		}
	}
	return 0;
}

void clearinBuf(char* buf, long size)
{
    for (long i = 0; i < size; i++)
    {
        *(buf+i) = 0;
    }
}

long main()
{
    const long inputB = 200;
    char inBuf[200];
    clearinBuf(inBuf, inputB);
    fgets(inBuf, inputB, stdin);
    long t = Parselongeger(inBuf, inputB);

    while (t--)
    {
        clearinBuf(inBuf, inputB);
        fgets(inBuf, inputB, stdin);
        long n = Parselongeger(inBuf, inputB);

        long a[n];
        for (long i = 0; i < n; i++) { a[i] = 0; }
        
        clearinBuf(inBuf, inputB);
        fgets(inBuf, inputB, stdin);
        Parselongegers(inBuf, inputB, a, n);
        //prlongf("a: ");
        //for (long i = 0; i < n; i++) { prlongf("%d, ", a[n]); }
        //prlongf("\n");

        char gut = 1;
        for (long i = 0; i < n - 1; i++)
        {
            long a1 = a[i];
            long a2 = a[i+1];
            gut = (abs(a1 - a2) == 5) || (abs(a1 - a2) == 7);
            if (!gut) { break; }
        }
        printf("%s\n", (gut ? "YES" : "NO"));
    }
}