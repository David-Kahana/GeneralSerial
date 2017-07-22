#pragma once
#include <Windows.h>
#include <string>

using namespace std;

#define OK 1

class CFileUtil
{
public:
	CFileUtil();
	~CFileUtil();
	static bool FileExists(const wstring& fileName_in);
	static bool FileExists(const string& fileName_in);
	static int writeToFile(const wstring& fileName, const char* buffer, unsigned int size);
	static int writeToFile(const string& fileName, const char* buffer, unsigned int size);
	static int readFromFile(const wstring& fileName, char** buffer, unsigned int& size);
	static int readFromFile(const string& fileName, char** buffer, unsigned int& size);
private:
	static int readFromFile(const wchar_t* fileName, char** buffer, unsigned int& size);
	static int writeToFile(const wchar_t* fileName, const char* buffer, unsigned int size);
};

