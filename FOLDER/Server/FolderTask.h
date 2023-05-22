#ifndef FOLDERTASK_H
#define FOLDERTASK_H

#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <windows.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include <filesystem>

using namespace std;
//namespace fs = std::filesystem;

class FolderTask {
private:
public:
    bool isFolder(string path);
    bool isExistFile(const char* path);
    bool deleteFile(const char* path);
    bool deleteFolder(const char *path);
    vector<string> list_files(const char *path);
    vector<string> recursive_list_files(const char *path);
    bool createFile(const char* path);
     bool createFolder(const char* path);
     bool renameFileFolder(const char* oldName, const char* newName);
     bool copyFile(const char* sourcePath, const char* destPath);
     bool copyFolder(const char* sourcePath, const char* destPath);

     string tab_recursive_list_files(const char *path, int cntTab);
//    void getFileSystem(const char* path);
};

#endif // FOLDERTASK_H
