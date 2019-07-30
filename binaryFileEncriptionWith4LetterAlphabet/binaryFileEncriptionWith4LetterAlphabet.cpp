// binaryFileEncriptionWith4LetterAlphabet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Reading a file in hexadecimal and encoding it with 16 letter alphabet

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>

using namespace std;

#pragma warning(disable:4996)

void reverseString(string &stringToReverse)
{
	int numCharacters = stringToReverse.length();
	for (int i = 0; i < numCharacters / 2; i++)
	{
		std::swap(stringToReverse[i], stringToReverse[numCharacters - i - 1]);
	}
}

string toBin(int value)
{
	string binaryNum = "000000";

	int i = 0;
	while (value > 0) {

		binaryNum[i] = (value % 2) + '0';
		value = value / 2;
		i++;
	}
	reverseString(binaryNum);

	return binaryNum;
}

int cnvrt(string buf)
{
	if (buf.size() < 6)
	{
		int bufSize = buf.size();
		for (int i = 0; i < (6 - bufSize); i++)
		{
			buf += '0';
		}
	}
	int k = 0;
	int g = 32;
	for (int i = 0; i < 6; i++)
	{
		k += g * (buf[i] - '0');
		g /= 2;
	}
	return k;
	/*switch (buf) 
	{

	case 0: return 0;
	case 1: return 1;
	case 16: return 2;
	case 17: return 3;
	case 204: return -1;
	}*/
}

string getFileName(string fileName)
{
	std::size_t pos = fileName.find_last_of(".");      // position of "." in str

	return fileName.substr(0, pos);
}

string getFileExtension(string fileName)
{
	std::size_t pos = fileName.find_last_of(".");      // position of "." in str

	return fileName.substr(pos);
}

bool encrypt(string fileName) // test : fileName = "test.bin"
{
	FILE *file = fopen(fileName.c_str(), "r");
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL) return NULL; //could not open file
	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	code = (char*)malloc(f_size);

	while ((c = fgetc(file)) != EOF) {
		code[n++] = (char)c;
	}

	code[n] = '\0';

	cout << "Enter the alphabet (64 chars): " << endl;

	string alphabet[64];
	
	for (int i = 0; 64 - i; i++)
	{
		cout << i + 1 << ". ";
		cin >> alphabet[i];

		// commended code is for faster testing
		/*string c = ""; 
		if (i < 10)
			c += "0";
		c += to_string(i);
		alphabet[i] = c;*/
	}
	
	FILE * encripted = fopen((getFileName(fileName) + "_encripted.txt").c_str(), "w");
	
	string text = ""; //debugging

	int i = 0;
	while (i < n)
	{
		
		int j = 0;
		string s;
		if (i == 0)
		{
			s += code[0];
			j++;
		}

		while (j++ < 6)
		{
			i++;
			if (i >= n) break;
			s += code[i];
		}

		//if (i >= n) break;

		text += alphabet[cnvrt(s)];
	}

	fprintf(encripted, "%s", text.c_str());
	//fputs(text, encripted);

	fclose(encripted);
	return true;
}


bool decrypt(string fileName) // test : fileName = "test_encripted.txt"
{
	FILE *file = fopen(fileName.c_str(), "r");
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL) return NULL; //could not open file
	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	code = (char*)malloc(f_size);

	while ((c = fgetc(file)) != EOF) {
		code[n++] = (char)c;
	}

	code[n] = '\0';

	cout << "Enter the alphabet (64 pairs of chars, example: 'ab'): " << endl;

	unordered_map<string, int> alphabet;


	for (int i = 0; 64 - i; i++)
	{
		cout << i + 1 << ". ";
		char c;
		cin >> c;
		alphabet[c] = i;

		// commended code is for faster testing
		/*
		string c = "";
		if (i < 10)
			c += "0";
		c += to_string(i);
		alphabet[c] = i;*/
	}

	FILE *decripted;

	decripted = fopen((getFileName(fileName) + "_decripted.text").c_str(), "w");  // w for write, b for binary
	
	string text = "";

	for (int i = 0; i < n / 2; i++)
	{
		string s = "";
		s += code[i * 2];
		s += code[i * 2 + 1];
		int k = alphabet[s];
		text += toBin(k);
	}

	fprintf(decripted, "%s", text.c_str());
	return true;
}

int main()
{
	//cnvrt("1101");
	toBin(1);

	cout << "Enter file name:";
	string fileName;
	cin >> fileName;

	cout << "Do you want to encrypt (0) or decript (1) a file?" << endl;

	int type;
	cin >> type;

	bool success = type == 1 || type == 0 ? ( (type == 0) ? encrypt(fileName) : decrypt(fileName) ) : false;

	if (success)
		cout << "Successful" << endl;
	else
		cout << "Unsuccessful" << endl;

	return 0;
}

