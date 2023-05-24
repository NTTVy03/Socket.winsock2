#include "server.h"

Server::Server() {
    // Set up WSA

    // Create server socket

    // Set up address & Bind server socket

}

// manage all connection & request - response
void Server::manage_All() {
    // Listen to Client request

    // (Connect Client) or (Push Client into Queue)
        // Connect Client -> set id of ac_socket

        // Connect accept socket (with 1 Client)

        // Do something with Client
        // call: manage_AcSocket(int id);
    
        // Close accept socket (with 1 Client)

    // Close server socket & WSA
}


// connect - classify message
void Server::manage_AcSocket(int id_AcSocket) {
    while (true) {
        // ========= RECV REQUEST =========
        // number of parameters
        int numPara;
        recvSize(id_AcSocket, numPara);
        
        // recv type of func
        int szType;
        recvSize(id_AcSocket, szType);
        char type[szType + 1];
        recvData(id_AcSocket, type);

        // recv parameters
        int szPara[numPara];
        char* para[numPara];
        for (int i = 0; i < numPara; i++) {
            // recv para[i]
            recvSize(id_AcSocket, szPara[i]);
            recvData(id_AcSocket, para[i]);
        }

        bool isContinue = callFuncAndSendResponse(id_AcSocket, type, para);
        if (!isContinue) return;
    }
}

// type --> func
// para (char*) --> para
// call function & send response
// return 1 -> continue
// return 0 -> close connect with Client[id_AcSocket]
bool callFuncAndSendResponse(int id_AcSocket, const char* type, char* para[]) {
    bool isContinue = true;
    if (type == APP_REQUEST_LIST) {
        // C1: chuyen vector<string> qua socket
        // vector<string> listApp = App::listAllAppDemo();
        // convert listApp to char* = ans
        // isContinue &= sendData(id_AcSocket, STATUS_SUCCESS);
        // isContinue &= sendSize(id_AcSocket, strlen(ans));
        // isContinue &= sendData(is_AcSocket, ans);

        // C2: luu vao 1 file
        // const char* filename = "..."
        // bool isSuccess = App::listAllAppToFile(filename);
        // isContinue &= sendData(id_AcSocket, STATUS_SUCCESS);
        // isContinue &= sendDatafromFile(id_AcSocket, filename);
    }
    else if (type == APP_REQUEST_START) {
        bool isSuccess = App::runApp(para[0]);

        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == APP_REQUEST_STOP) {
        bool isSuccess = App::TerminateProcessByName(para[0]);

        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == PRO_REQUEST_LIST) {

    }
    else if (type == PRO_REQUEST_START) {

    }
    else if (type == PRO_REQUEST_STOP) {

    }
    else if (type == SCR_REQUEST) {
        char filename[] = "scrShot.bmp";
        scrShot::SaveScreenShotToFile(filename);
        isContinue &= sendData(id_AcSocket, STATUS_SUCCESS);
        isContinue &= sendDatafromFile(id_AcSocket, filename);
    }
    else if (type == KEY_REQUEST_GET) {
        keyDown::catchCodeAlltoString(this, id_AcSocket);
    }
    else if (type == FOL_REQUEST_LIST) {
        string Sdata = FolderTask::tab_recursive_list_files(para[0], 0);
        const char* data = Sdata.c_str();

        isContinue &= sendData(id_AcSocket, (strlen(data) > 0 ? STATUS_SUCCESS : STATUS_FAIL));
        isContinue &= sendSize(id_AcSocket, strlen(data));
        isContinue &= sendData(id_AcSocket, data);
    }
    else if (type == FOL_REQUEST_COPY_FILE) {
        bool isSuccess = FolderTask::copyFile(para[0], para[1]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == FOL_REQUEST_COPY_FOLDER) {
        bool isSuccess = FolderTask::copyFolder(para[0], para[1]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == FOL_REQUEST_CREATE_FILE) {
        bool isSuccess = FolderTask::createFile(para[0]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == FOL_REQUEST_CREATE_FOLDER) {
        bool isSuccess = FolderTask::createFolder(para[0]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == FOL_REQUEST_DELETE_FILE) {
        bool isSuccess = FolderTask::deleteFile(para[0]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == FOL_REQUEST_DELETE_FOLDER) {
        bool isSuccess = FolderTask::deleteFolder(para[0]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }
    else if (type == FOL_REQUEST_RENAME) {
        bool isSuccess = FolderTask::renameFileFolder(para[0], para[1]);
        
        isContinue &= sendData(id_AcSocket, (isSuccess ? STATUS_SUCCESS : STATUS_FAIL));
    }

    return isContinue;
}

// send message
bool Server::sendSize(int id_AcSocket, int size) {

}

bool Server::sendData(int id_AcSocket, const char* message) {

}

bool Server::sendDatafromFile(int id_AcSocket, const char* filename) {

}

// recv message
bool Server::recvSize(int id_AcSocket, int &size) {

}

bool Server::recvData(int id_AcSocket, char* &message) {

}

bool Server::recvDataAndSaveToFile(int id_AcSocket, const char* filename) {

}