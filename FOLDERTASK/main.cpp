// cd D:\HK2_NAM2\MMT\SOCKET\FOLDERTASK\   
// g++ *.cpp -o main.exe -lws2_32; ./main

#include "FolderTask.h"

int main()
{
    char srcFile[] = "D:/DELETE_THIS_FOLDER/AnhYeu";
    char desFile[] = "D:/";

    FolderTask* FT = new FolderTask;
    FT->deleteFolder(srcFile);
    
    delete FT;
    return 0;
}