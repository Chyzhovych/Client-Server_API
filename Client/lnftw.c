#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "lnftw.h"
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define CONTINUE 0
#define STOP 1
#define ACTION_RETVAL 16
#define DIR_NAME_SIZE 256
// max num of sub dirs
#define MAX_LEVEL 20
#define START_DIR "/"

char dirName[DIR_NAME_SIZE];
char * dirPath;

int endsWith(const char * str, const char * word)
{
    if(str == NULL && word == NULL)
    {
        return FALSE;
    }
    int strLen = strlen(str);
    int wordLen = strlen(word);
    for(int i = wordLen; i >= 0; i--)
    {
        if(word[i] != str[strLen--])
        {
            return FALSE;
        }
    }
    if(str[strLen] != '/')
    {
        return FALSE;
    }
    return TRUE;
}

int filter(const char *fpath, const struct stat *sb,
            int tflag, struct FTW *ftwbuf)
{
   // if the depth is above the max sub dirs, continue to next file
   if (ftwbuf->level > MAX_LEVEL) 
   {
        printf("Max level reached\n");
        strcpy(dirPath,"Failure...\n");
        return STOP; 
   }
   if((tflag == FTW_D || tflag == FTW_DNR) && endsWith(fpath, dirName))
   {
       strcpy(dirPath, fpath);
       return STOP;
   }
   return CONTINUE;           /* To tell nftw() to continue */
}


int getDirPath(char * path, const char * name)
{
    int flags = 0;
    strcpy(dirName, name);
    dirPath = path;
    flags = FTW_PHYS | ACTION_RETVAL;
    return nftw(START_DIR, &filter, MAX_LEVEL, flags);
}

// This function uses for sending status of searching
void* sendMsg(void * arg)
{
    while(1)
	{
        usleep(500 * 1000);
        const char *msg = "Processing...\n";
        write(*(int*)arg, msg, strlen(msg));
    }
}
