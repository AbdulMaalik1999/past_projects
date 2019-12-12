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
	file.open("encrypted.txt",ios::in);
	

	stringstream buffer;
	buffer << file.rdbuf();
	sent=buffer.str();
	str_len=sent.length();
	
	char a;
	a=sent[0];
	//AS WE KNOW THAT THE FIRST LETTER IS D SO WE CAN FIND THE VALUE OF K AND DONE BELOW
	for(int i=0;i<66;i++)
	{
		if(a==enc[i])
		{
			break;
		}
		else
		{
		
		count1++;
		}
		
		}	
		
		k=count1-3;
		if(k<=0)
		{
			k=66+k;
		}
		
	//THE LOOP BELOW DECRYPT EACH CHARACTER AND SAVE IT IN A STRING
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

		count2 = count1 - k;

		if (count2 < 0)
		{
			count2 = count2 + 66;
			sent[i] = enc[count2];
		}
		else
		{
			sent[i] = enc[count2];
		}
	}

	cout << sent;

	ofstream output;
	output.open("decrypted.txt");
	output <<sent;
	


}
