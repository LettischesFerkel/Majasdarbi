#include <stdio.h>
#include <math.h>

int ParseInteger(char* input, int length)
{
	int power = 0;
	int num = 0;
	for (int i = 0; i < length; i++)
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
int ParseIntegers(char* input, int length, int** out, int outCount)
{
	char reading = 0;
	int count = -1;
	int power = 0;
	int num = 0;
	if (outCount == 1)
	{
		**out = ParseInteger(input, length) + 1;
		return 0;
	}
	for (int i = 0; (i < length) && (count < outCount); i++)
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
					**(out + outCount - 1 - count) = num;
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
				**(out + outCount - 1 - count) = num;
				num = 0;
				power = 0;
			}		
			reading = 0;	
		}
	}
	return 0;
}

void clearInputBuffer(char* inputBufferP, int inputBufferSize)
{
	for (int i = 0; i <= inputBufferSize; i++)
	{
		*(inputBufferP + i) = '\0';
	}
}

int remainderOf2toI(int n, int i) { return (~((unsigned int)(-1) << i)) & n; } // rēķina atlikumu no 2^i

int main()
{
    const int inputBufferSize = 64;
	char inputBuffer[inputBufferSize + 1];
	clearInputBuffer(inputBuffer, inputBufferSize);
	fgets(inputBuffer, inputBufferSize, stdin);	
	int t = ParseInteger(inputBuffer, inputBufferSize);

    while (t--)
    {
        unsigned int l, r, i, k;
        int* input[4] = { &l, &r, &i, &k };
        clearInputBuffer(inputBuffer, inputBufferSize);
        fgets(inputBuffer, inputBufferSize, stdin);
        ParseIntegers(inputBuffer, inputBufferSize, input, 4);
        //printf("l: %d, r: %d, i: %d, k: %d\n", l, r, i, k);

        unsigned int result = 0;
        for (unsigned int x = l; x <= r; x++) // saraksts ar [l, r] skaitļiem
        {
            //printf("\t%d - ", x);
            // pārbauda vai x≢ k(mod2i), izlaiž nederīgos
            if (remainderOf2toI(x, i) == remainderOf2toI(k, i)) { /*printf("skipped\n");*/ continue; }
            //printf("%d ^ %d = ", result, x);
            result = result ^ x;
            //printf("%d\n", result);
        }
        printf("%d\n", result);
    }

    /*clearInputBuffer(inputBuffer, inputBufferSize);
	fgets(inputBuffer, inputBufferSize, stdin);	
	int niga = ParseInteger(inputBuffer, inputBufferSize);
    printf("\nNiga: %d\n", niga);
    for (int x = 0; x <= 30; x++)
    {
        printf("\tniga mod(%d) = %d\n", (1 << x), remainderOf2toI(niga, x));
    }*/
}