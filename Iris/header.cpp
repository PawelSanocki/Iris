#include "header.h"

int biggest(float* tab)
{
	int k = 0;
	for (int i = 1; i < LAST_LAYER; i++)
	{
		if (tab[i] > tab[k])
		{
			k = i;
		}
	}
	return k;
}

void mix()
{
	srand(time(NULL));
	vector <string> lines;
	string str;
	ifstream file1("data.txt");
	for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
	{
		file1 >> str;
		lines.push_back(str);
	}
	file1.close();
	ofstream file2("data.txt", ios::trunc);
	random_shuffle(lines.begin(),lines.end());
	for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
	{
		file2 << lines[i] << endl;
	}
	file2.close();
}