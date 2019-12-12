#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int main()
{
	ifstream file;
	string enc = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789,.\n";
	string sent;
	int str_len,k,count1=0,count2;
	file.open("normal.txt",ios::in);
	

	stringstream buffer;
	buffer <<file.rdbuf();
	sent=buffer.str();
	str_len=sent.length();
	

	
	cout << "PLEASE ENTER VALUE OF K " << endl;
	cin >> k;
	k = k % 66;
	
	for (int i = 0; i < str_len; i++)
	{
		char z;
		z = sent[i];
		count1 = 0;
		for (int j = 0; j < 66; j++)
		{
			if (z == enc[j])
			{
				break;
			}
			else
			{
				count1++;
			}
		}

		count2 = count1 + k;

		if (count2 > 66)
		{
			count2 = count2 - 66;
			sent[i] = enc[count2];
		}
		else
		{
			sent[i] = enc[count2];
		}
	}

	cout << sent;

	ofstream output;
	output.open("encrypted.txt");
	output <<sent;
	


}
