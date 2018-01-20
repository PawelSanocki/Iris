#include "Net.h"

using namespace std;

int main()
{
	Net myNet = Net();
	int c = 1; //repeat
	int n;
	cout << "Fill randomly weights - 0, load weights - 1 : ";
	cin >> n;
	switch (n)
	{
	case 0:
	{
		myNet.fillRandomly();
	}break;
	default:
	{
		myNet.loadWeights();
	}break;
	}
	// the end of loading weights
	do {
		cout << "Learn - 0 \nTest - 1 \nLearn 30k times - 4 \n" << endl;
		cin >> n;
		cout << endl;
		try
		{
			switch (n)
			{
			case 0:		// learn
			{
				myNet.learn();
			}break;
			case 1:		// test
			{
				myNet.test();
			}break;
			case 4:
			{
				for (int it = 0; it < 30000; it++)
				{
					myNet.learn();
					if (it%1000==0) cout << it << " ";
				}
			}break;
			}

		}
		catch (exception &e)
		{
			cout << e.what();
		}
		cout << endl << endl << "Press 1 to repead: ";
		cin >> c;
	} while (c);
	myNet.saveWeights();
	cout << endl << "The end" << endl;
	Sleep(2000);
	getchar(); getchar();
	return 0;
}
