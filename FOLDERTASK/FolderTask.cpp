#include "FolderTask.h"

bool FolderTask::isExistFile(const char *path) {
    ifstream file(path, ios::binary);
    if (!file)
        return false;
    else
    {
        file.close();
        return true;
    }
}

bool FolderTask::deleteFile(const char *path) {
    bool result = remove(path);
    if (result != 0) {
        perror("Error deleting file");
        return false;
    } else {
        // printf("File deleted successfully\n");
        return true;
    }
}

bool FolderTask::deleteFolder(const char *path) {
    DIR *dir = opendir(path);
    if (dir == nullptr) {
        cout << "Direction: " << path << "\n";
        cout << "Cannot open Folder\n";
        return false;
    }

    bool status = true;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char subpath[1000];
        sprintf(subpath, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // Đệ quy xóa thư mục con
            status &= deleteFolder(subpath);
        } else {
            // Xóa tệp tin
            status &= remove(subpath);
        }
    }
    closedir(dir);

    // Xóa thư mục gốc (rỗng)
    if (rmdir(path) != 0) {
        perror("Error deleting folder");
        return false;
    }

    return status;
}

// Hàm duyệt thư mục và lấy danh sách các file và thư mục
vector<string> FolderTask::list_files(const char *path) {
    vector<string> files;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        cerr << "Error opening directory\n";
        return files;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            // Bỏ qua thư mục "." và ".."
            continue;
        }
        files.push_back(entry->d_name);
    }
    closedir(dir);
    return files;
}

vector<string> FolderTask::recursive_list_files(const char *path) {
    vector<string> files;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        cerr << "Error opening directory\n";
        return files;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            // Bỏ qua thư mục "." và ".."
            continue;
        }

        char subpath[1000];
        sprintf(subpath, "%s/%s", path, entry->d_name);

        // files.push_back(entry->d_name);
        files.push_back(subpath);

        if (entry->d_type == DT_DIR) {
            auto tmp = recursive_list_files(subpath);
            files.insert(files.end(), tmp.begin(), tmp.end());
        }
    }
    closedir(dir);
    return files;
}

bool FolderTask::createFile(const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error creating file");
        return false;
    } else {
        // printf("File created successfully");
        fclose(file);
    }
    return true;
}

bool FolderTask::createFolder(const char *path)
{
    cout << "Path: " << path << "\n";
    int result = mkdir(path);
    if (result == 0)
    {
        // printf("Folder created successfully\n");
        return true;
    }
    else
    {
        perror("Error creating folder");
        return false;
    }
}

bool FolderTask::renameFileFolder(const char *oldName, const char *newName)
{
    bool result = rename(oldName, newName);
    if (result == 0)
    {
        // printf("Rename successfully\n");
        return true;
    }
    else
    {
        perror("Error renaming");
        return false;
    }
}

bool FolderTask::copyFile(const char *sourcePath, const char *destPath)
{
    ifstream source(sourcePath, ios::binary);
    if (!source)
    {
        cout << "Cannot open source file\n";
        return false;
    }

    if (isExistFile(destPath))
    {
        cout << "Destination: " << destPath << "\n";
        cout << "Destination exist! Do you want to overwirte it? (Y = Yes)\n";
        char ch;
        cin >> ch;
        if (ch != 'Y')
            return false;
    }

    ofstream destination(destPath, ios::binary);
    if (!destination)
    {
        cout << "Cannot create copy file\n";
        return false;
    }

    // đọc nội dung tệp gốc
    destination << source.rdbuf();

    // đóng tệp
    source.close();
    destination.close();

    // cout << "File copied successfully\n";
    return true;
}

bool FolderTask::copyFolder(const char *sourcePath, const char *destPath)
{
    createFolder(destPath);
    DIR *dir = opendir(sourcePath);
    if (dir == NULL)
    {
        cerr << "Error opening source directory\n";
        return false;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            // Bỏ qua thư mục "." và ".."
            continue;
        }

        char subpath[1000];
        sprintf(subpath, "%s/%s", sourcePath, entry->d_name);

        char copypath[1000];
        sprintf(copypath, "%s/%s", destPath, entry->d_name);

        if (entry->d_type == DT_DIR)
        {
            copyFolder(subpath, copypath);
        }
        else
            copyFile(subpath, copypath);
    }
    closedir(dir);
    return true;
}
