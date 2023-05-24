#pragma once

// App Manager
#define APP_REQUEST_LIST "List-App"
#define APP_REQUEST_START "Start-App"
#define APP_REQUEST_STOP "Stop-App"

// Process Manager
#define PRO_REQUEST_LIST "List-Pro"
#define PRO_REQUEST_START "Start-Pro"
#define PRO_REQUEST_STOP "Stop-Pro"

// Keydown Catching
#define KEY_REQUEST_GET "Get-Key"
#define KEY_REQUEST_STOP "Stop-Key"

// Folder Manager
#define FOL_REQUEST_LIST "List-Fol"
#define FOL_REQUEST_RENAME "Rename-Fol"

#define FOL_REQUEST_CREATE_FILE "Create-File-Fol"
#define FOL_REQUEST_CREATE_FOLDER "Create-Folder-Fol"

#define FOL_REQUEST_COPY_FILE "Copy-File-Fol"
#define FOL_REQUEST_COPY_FOLDER "Copy-Folder-Fol"

#define FOL_REQUEST_DELETE_FILE "Delete-File-Fol"
#define FOL_REQUEST_DELETE_FOLDER "Delete-Folder-Fol"

// Screen Shot
#define SCR_REQUEST "Scr"

// Response status
#define STATUS_SUCCESS "1"
#define STATUS_FAIL    "0"

#include "../app/app.h"
#include "../process/process.h"
#include "../folder/folder.h"
#include "../key/key.h"
#include "../scrsshot/scrshot.h"

