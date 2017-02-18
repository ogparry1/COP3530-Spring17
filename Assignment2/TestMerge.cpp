#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>

using namespace std;

/*
int max(int k, int l)
{
	return ((k > l)?k:l);
}

int min(int k, int l)
{
	return ((k < l)?k:l);
}

void insertSort(int* keys, int N)
{
	if (N == 2)
	{
		int temp = min(keys[0], keys[1]);
		keys[0] = max(keys[0], keys[1]);
		keys[1] = temp;
	}
	else if (N == 3)
	{
		int a = keys[0], b = keys[1], c = keys[2];
		keys[0] = max(max(a,b),c);
		keys[2] = min(min(a,b),c);
		keys[1] = (a > keys[2] && a < keys[0]?a:(b > keys[2] && b < keys[0]?b:c));
	}
	else
	{
		int i = 0, j = 0;
		int lastOdd = 0;
		int* fHalf = new int[N/2]; 
		int* sHalf = new int[N/2];
		if (N % 2 != 0) lastOdd = keys[N-1]; //if N is odd, point to last element and insert it last
		for (int ii = 0; ii < N/2; ii++) //fill in halves
		{
			fHalf[ii] = keys[ii];
			sHalf[ii] = keys[N/2+ii+1];
		}
		insertSort(fHalf, N/2);
		insertSort(sHalf, N/2);
		for (int ii = 0; ii < N; ii++) //merge halves
		{
			if (lastOdd > fHalf[i] && lastOdd > sHalf[i] && lastOdd != 0)
			{
				keys[ii] = lastOdd;
				lastOdd = 0;
			}
			if (i != N/2 && j != N/2)
			{
				if (fHalf[i] >= sHalf[j])
				{
					keys[ii] = fHalf[i];
					i++;
				}
				else
				{
					keys[ii] = sHalf[j];
					j++;
				}
			}
			else if (i == N/2)
			{
				for (int kk = ii; kk < N; kk++) //fill in halves
				{
					keys[ii] = sHalf[j];
					j++;
				}
				break;
			}
			else if (j == N/2)
			{
				for (int kk = ii; kk < N; kk++) //fill in halves
				{
					keys[ii] = fHalf[i];
					i++;
				}
				break;
			}
		}
	}
}*/

int main()								//Needs Work and to check input
{
	int N;
	cin >> N;
	int* test = new int[N];
	int input = 0;
	for (int ii=0; ii<N; ii++) //cycle through to take in all inputs
	{
		cin >> input; //take input
		if (ii == 0)
		{
			test[ii] = input;
		}
		else
		{
			int i = ii;
			//insert sort//
			while (input > test[i-1] && i > 0)
			{
				test[i] = test[i-1];
				i--;
			}
			test[i] = input;
			//insert sort//
		}
	}
	for (int ii = 0; ii < N; ii++)
	{
		cout << (ii==0?"{":"") << test[ii] << (ii==N-1?"}\n":", ");
	}
	return 0;
}

