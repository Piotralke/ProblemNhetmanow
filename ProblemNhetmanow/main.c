#include <stdio.h>
#include <stdlib.h>

char* make_array(int size)
{
	return (char*)calloc(size, sizeof(char));
}

void fill_array(char** array, int size)
{
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
			array[i][j] = '0';
	}
}

void print_array(char** array, int size)
{
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
			printf("%c\t", array[i][j]);
		printf("\n");
	}
}

void free_ptr(char** array, int size)
{
	for (int i = 0;i < size;i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void fill_with_hetman(char** array, int size)
{
	int counter = 0,licznik=0;

	for (int xh = 0;xh < size;xh++) {
		for (int yh = 0;yh < size;yh++) {
			fill_array(array,size);
			array[xh][yh] = 'H';
			for (int i = 0;i < size;i++)
			{
				for (int j = 0;j < size;j++)
				{
					if (array[i][j] == '0')
					{
						array[i][j] = 'H';
						fill_with_xes(array, size, i, j);						counter++;						break;
					}
				}
			}
			if (counter == size) {
				licznik++;
			}
		}
	}
	

}

int fill_with_xes(char** array, int size, int i, int j)
{
	for (int x = i + 1;x < size;x++)	//prawo
		array[x][j] = 'x';
	for (int x = i - 1;x > 0;x--)	//lewo
		array[x][j] = 'x';
	for (int y = j + 1;y < size;y++)	//dol
		array[i][y] = 'x';
	for (int y = j - 1;y > 0;y--)	//gora
		array[i][y] = 'x';
	for (int x = i + 1, y = j + 1;x < size && y < size;x++, y++)	//prawy dolny
			array[x][y] = 'x';
	for (int x = i - 1, y = j + 1;x > 0 && y < size;x--, y++)	//lewy dolny
			array[x][y] = 'x';
	for (int x = i - 1, y = j - 1;x > 0 && y > 0; x--,y--)	//lewy gorny
			array[x][y] = 'x';
	for (int x = i + 1, y = j - 1;x < size && y >0;x++, y--)	//prawy gorny
			array[x][y] = 'x';
}

int main()
{
	int size = 0;
	scanf("%d", &size);
	char** array = (char**)calloc(size, sizeof(char *));
	for (int i = 0;i < size;i++)
		array[i] = (char*)calloc(size, sizeof(char));
	if (!array)
	{
		printf("Blad zalokowania pamieci");
		free_ptr(array, size);
	}
	else
	{
		fill_array(array, size);
		fill_with_hetman(array, size);
		print_array(array, size);
		free_ptr(array, size);
	}
	return 0;
}