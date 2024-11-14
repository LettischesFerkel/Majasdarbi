#include <stdio.h>
#include <math.h>

char isEven(int number) { return !((char)number & 0b00000001); }
char isOdd(int number) { return ((char)number & 0b00000001); }

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
int ParseIntegers(char* input, int length, int* out, int outCount)
{
	char reading = 0;
	int count = -1;
	int power = 0;
	int num = 0;
	if (outCount == 1)
	{
		*out = ParseInteger(input, length) + 1;
		return 0;
	}
	for (int i = 0; i < length; i++)
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
				if (count >= 0)
				{
					*(out + outCount - 1 - count) = num;
					num = 0;
					power = 0;
				}		
				reading = 0;				
			}
		}
		if (reading && (i == length - 1))
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

void clearInputBuffer(char* inputBufferP, int inputBufferSize)
{
	for (int i = 0; i <= inputBufferSize; i++)
	{
		*(inputBufferP + i) = '\0';
	}
}

int dari(int* virkne, int skaits)
{
	// Atrod lielāko elementu un vai starp tiem ir pāra elements
	int lielaakais = 0;
	char lielaakie[2] = { 0, 0 }; // pāra / nepāra
	if (skaits == 1)
	{
		return *virkne;
	}
	//printf("Sus: ");
	for (int i = 0; i < skaits; i++)
	{
		int current = *(virkne + i);
		
		if (current > lielaakais)
		{
			lielaakais = current;
			char od = isOdd(i);
			lielaakie[od] = 1;
			lielaakie[!od] = 0;
		}
		else if (current == lielaakais)
		{
			lielaakie[isOdd(i)] = 1;
			//printf("%d(%d), ", current, isOdd(i));
		}
	}
	//printf("\nMax: %d\nEven, Odd: { %d, %d }\n", lielaakais, lielaakie[0], lielaakie[1]);
	
	// Pielieto algoritmu, rezultāta ieguvei
	if (isOdd(skaits))
	{
		//return ((skaits >> 1) + 1 + lielaakais);
		return lielaakie[0] ? ((skaits >> 1) + 1 + lielaakais) : ((skaits >> 1) + lielaakais);
	}
	else
	{
		return (skaits >> 1) + lielaakais;
	}
}

// pāra -> skaits/2
// -- ans = skaits/2 + max
// nepāra -> skaits/2 : skaits/2 + 1
// -- ans = pāra(maxN) ? (skaits/2 + 1 + max) : (skaits/2 + max)

int main()
{
	const int inputBufferSize = 640;
	char inputBuffer[inputBufferSize + 1];
	clearInputBuffer(inputBuffer, inputBufferSize);
	int tCases;
	fgets(inputBuffer, inputBufferSize, stdin);	
	tCases = ParseInteger(inputBuffer, inputBufferSize);
	//if (tCases == 500) { tCases++; }
	
	int mogus = 0;
	while (tCases)
	{
		int arrayLen = 0;
		clearInputBuffer(inputBuffer, inputBufferSize);
		fgets(inputBuffer, inputBufferSize, stdin);
		arrayLen = ParseInteger(inputBuffer, inputBufferSize);
		//printf("Len: %d\n", arrayLen);
		
		int array[arrayLen];
		for(int i = 0; i < arrayLen; i++) { array[i] = 0; }
		clearInputBuffer(inputBuffer, inputBufferSize);
		fgets(inputBuffer, inputBufferSize, stdin);
		ParseIntegers(inputBuffer, inputBufferSize, array, arrayLen);
		//for(int i = 0; i < arrayLen; i++) { array[i] = 1; }
		
		//TE BIJA LAURIS
		/*printf("Values: ");
		for (int i = 0; i < arrayLen; i++)
		{
			printf("'%d' ", array[i]);
		}
		printf("\n");*/
		int result = dari(array, arrayLen);
		if (tCases == 1) { printf("%d \n\n", result); }
		else { printf("%d\n", result); }
		tCases--;
	}
}