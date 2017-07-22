#include "stdafx.h"
#include "FileUtil.h"
#include "AtlBase.h"
#include "AtlConv.h"
#include <io.h>
CFileUtil::CFileUtil()
{
}

CFileUtil::~CFileUtil()
{
}

bool CFileUtil::FileExists(const wstring& fileName_in)
{
	DWORD dwAttrib = GetFileAttributes(fileName_in.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool CFileUtil::FileExists(const string& fileName_in)
{
	DWORD dwAttrib = GetFileAttributes(CA2W(fileName_in.c_str()));
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int CFileUtil::writeToFile(const wstring& fileName, const char* buffer, unsigned int size)
{
	return writeToFile(fileName.c_str(), buffer, size);
	//int ret = OK;
	//FILE *file = _wfopen(fileName.c_str(), L"wb");
	//if (file == nullptr)
	//{
	//	return -1;
	//}
	//size_t wsize = fwrite(buffer, 1, size, file);
	//if (wsize != (size_t)size)
	//{
	//	ret = -2;
	//}
	//int cret = fclose(file);
	//if (cret != 0)
	//{
	//	ret = -3;
	//}
	//return ret;
}

int CFileUtil::writeToFile(const string& fileName, const char* buffer, unsigned int size)
{
	return writeToFile(CA2W(fileName.c_str()), buffer, size);
	//int ret = OK;
	//FILE *file = fopen(fileName.c_str(), "wb");
	//if (file == nullptr)
	//{
	//	return -1;
	//}
	//size_t wsize = fwrite(buffer, 1, size, file);
	//if (wsize != (size_t)size)
	//{
	//	ret = -2;
	//}
	//int cret = fclose(file);
	//if (cret != 0)
	//{
	//	ret = -3;
	//}
	//return ret;
}

int CFileUtil::readFromFile(const string& fileName, char** buffer, unsigned int& size)
{
	return readFromFile(CA2W(fileName.c_str()), buffer, size);
}

int CFileUtil::readFromFile(const wstring& fileName, char** buffer, unsigned int& size)
{
	return readFromFile(fileName.c_str(), buffer, size);
}

int CFileUtil::readFromFile(const wchar_t* fileName, char** buffer, unsigned int& size)
{
	*buffer = nullptr;
	HANDLE hfile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	LARGE_INTEGER li;
	BOOL sret = GetFileSizeEx(hfile, &li);
	if (sret == FALSE)
	{
		CloseHandle(hfile);
		return -1;
	}
	long long bufSize = li.QuadPart;
	char* inBuf = nullptr;
	inBuf = new char[bufSize + 1];
	if (inBuf == nullptr)
	{
		CloseHandle(hfile);
		return -2;
	}
	DWORD dwBytesRead = 0;
	BOOL rret = ReadFile(hfile, inBuf, bufSize, &dwBytesRead, NULL);
	if (rret == FALSE || dwBytesRead != (DWORD)bufSize)
	{
		delete[]inBuf;
		CloseHandle(hfile);
		return -2;
	}
	inBuf[bufSize] = 0;
	*buffer = inBuf;
	size = dwBytesRead + 1;
	CloseHandle(hfile);
	//HANDLE hfile = (HANDLE)_get_osfhandle(_fileno(file));
	return OK;
}

int CFileUtil::writeToFile(const wchar_t* fileName, const char* buffer, unsigned int size)
{
	HANDLE hfile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	DWORD numberOfBytesWritten = 0;
	BOOL wret = WriteFile(hfile, buffer, (DWORD)size, &numberOfBytesWritten, NULL);
	if (wret == FALSE || numberOfBytesWritten != (DWORD)size)
	{
		CloseHandle(hfile);
		return -2;
	}
	CloseHandle(hfile);
	return OK;
}