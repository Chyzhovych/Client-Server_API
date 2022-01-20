#ifdef _WIN32
#ifndef  WINFUNC_H
#define  WINFUNC_H


int counter;

int ListDirectoryContents(const char *sPath, char * sDirName);

int endsWith(const char * str, const char * word);

DWORD WINAPI sendMsg(LPVOID  arg);

#endif  //WINFUNC_H
#endif
