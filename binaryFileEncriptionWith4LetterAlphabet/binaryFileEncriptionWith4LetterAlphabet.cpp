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

int cnvrt(int buf)
{
	switch (buf) 
	{
	case 0: return 0;
	case 1: return 1;
	case 16: return 2;
	case 17: return 3;
	case 204: return -1;
	}
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
	unsigned char buffer[1000];
	FILE *ptr;

	ptr = fopen(fileName.c_str(), "rb");  // r for read, b for binary

	cout << "Enter the alphabet (4 chars): " << endl;

	char alphabet[16];
	
	for (int i = 0; 4 - i; i++)
	{
		cout << i + 1 << ". ";
		cin >> alphabet[i];
	}

	fread(buffer, sizeof(buffer), 4, ptr);
	
	FILE * encripted = fopen((getFileName(fileName) + "_encripted.txt").c_str(), "w");
	
	for (int i = 0; i < 100; i++)
	{
		int cvr = cnvrt(buffer[i]);
		cvr = cvr < 0 ? -1 : fprintf(encripted, "%c", alphabet[cnvrt(buffer[i])]);
	}

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

	cout << "Enter the alphabet (4 chars): " << endl;

	unordered_map<char, int> alphabet;


	for (int i = 0; 4 - i; i++)
	{
		cout << i + 1 << ". ";
		char c;
		cin >> c;
		alphabet[c] = i;
	}

	FILE *decripted;

	decripted = fopen((getFileName(fileName) + "_decripted.text").c_str(), "w");  // w for write, b for binary
	
	for (int i = 0; i < n; i++)
	{
		int k = alphabet[code[i]];
		if (k != 204)
		{
			if (k / 2 == 0)
			{
				fprintf(decripted, "%i", 0);
			}
			else
			{
				fprintf(decripted, "%i", 1);
			}

			if (k % 2 == 0)
			{
				fprintf(decripted, "%i", 0);
			}
			else
			{
				fprintf(decripted, "%i", 1);
			}
		}		
	}

	return true;
}

int main()
{
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

