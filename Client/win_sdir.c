#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include "win_sdir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
#define FAILURE 0
#define SUCCESS 1
#define TREE_DEPTH 25 // Maximum folder depth


int ListDirectoryContents(const char *sPath, char * sDirName)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	int counter = 0;
	char path[2048] = {0};


	//Specify a file mask. *.* = We want everything!
	sprintf(path, "%s\\*.*", sPath);

	if ((hFind = FindFirstFile(path, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		/*	printf("Path not found: [%s]\n", sPath);*/

		return FAILURE;
	}

	do
	{
		//Find first file will always return "."
		//    and ".." as the first two directories.
		if (strcmp(fdFile.cFileName, ".") != 0
			&& strcmp(fdFile.cFileName, "..") != 0)
		{
			//  [sPath] and the foldername we just found:
			sprintf(path, "%s\\%s", sPath, fdFile.cFileName);

			//Is the entity a Folder ?
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY
				&& endsWith(path, sDirName))
			{
				printf("Directory: %s\n", path);
				strcpy(sDirName, path);
				return SUCCESS;
			}
			else if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) {
				//printf("File: %s\n", sPath);
				if (ListDirectoryContents(path, sDirName) == SUCCESS) {
					return SUCCESS;//Recursion func()
				}
			}
		}
	} while (FindNextFile(hFind, &fdFile) && counter < TREE_DEPTH); //Find the next file.

	FindClose(hFind);
	return FAILURE;
}

int endsWith(const char * str, const char * word)
{
	if (str == NULL && word == NULL)
	{
		return FALSE;
	}
	int strLen = strlen(str);
	int wordLen = strlen(word);
	for (int i = wordLen; i >= 0; i--)
	{
		if (word[i] != str[strLen--])
		{
			return FALSE;
		}
	}
	if (str[strLen] != '\\')
	{
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI sendMsg(LPVOID  arg)
{
	while (1) {
		Sleep(500);
		const char *msg = "Processing...\n";
		send((SOCKET)arg, msg, strlen(msg) + 1, 0);
	}
	ExitThread(0);
}

#endif
