#include <Windows.h>
#include <iostream>


HANDLE hHeapPrivate = HeapCreate(0, 0, 0);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD bWritten = 0;

struct FileNode{
    wchar_t fileName[MAX_PATH];// not using wstring because its an object and HeapAlloc doesnt run constructors so using wchar_t for fixed sized arrays
    ULONGLONG fileSize; // 64 bit integer to hold large file sizes accurately
    FileNode *left, *right;
};




FileNode* create_node(const wchar_t* name, ULONGLONG size){
    FileNode* new_node = (FileNode*)HeapAlloc(hHeapPrivate, HEAP_ZERO_MEMORY, sizeof(FileNode));
    if(new_node == nullptr){
        const wchar_t* errMsg = L"[!] heap allocation failed\n[!]exiting program...\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        HeapDestroy(hHeapPrivate);
        exit(4);
    }
    /*
        since fileName is fixed array type so doing performing 
        new_node->fileName = name will give compile time error as its trying to change the base address of the wchar_t fixed array type which is not possible
    */
    lstrcpynW(new_node->fileName, name, MAX_PATH);
    new_node->fileSize = size;
    return new_node;
}




void insertNodes(FileNode *&root, const wchar_t* fileName, ULONGLONG fileSize){
    if(root == nullptr){
        root = create_node(fileName, fileSize);
        return;
    }
    if(root->fileSize > fileSize)
        insertNodes(root->left, fileName, fileSize);
    else // taking filesizes >= root_filesize
        insertNodes(root->right, fileName, fileSize);
}



void printSortedFiles(FileNode *root){
    /*
        we are going to use the inorder traversal to do the sorting
        so we are going to take the root node(first file found using FindFirstFile) and use it as a reference point to print the left and right subtree

        inorder traversal => left -> root -> right
    */
    if(root == nullptr)
        return;
    printSortedFiles(root->left);
    std::wcout << L"--| " << root->fileName << L'\t' << (root->fileSize/1024.0) << " KBs" << std::endl;
    printSortedFiles(root->right);
}



int wmain(int argc, wchar_t* argv[]){ // since argv is editable so const wchar_t* not required. required only for read-only values
    if(argc != 2){
        /*
            we are specifically coding for windows unicode platform 
            lstrlen is used to calculate length of wide string characters
        */
        // const wchar_t* because wchar_* are read only when we want to store multiple characters
        const wchar_t* errMsg = L"[!] Usage: filesort.exe <DIRECTORY_PATH>\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        HeapDestroy(hHeapPrivate);
        return 1;
    }
    if(hHeapPrivate == INVALID_HANDLE_VALUE){
        const wchar_t* errMsg = L"[!] failed to create private heap\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        HeapDestroy(hHeapPrivate);
        return 2;
    }
    FileNode *root = nullptr;
    std::wstring searchPath = std::wstring(argv[1]) + L"\\*"; // appending the \* at the end of the directory path
    WIN32_FIND_DATAW fileData;
    // gives the first file found in the searchPath directory based on the file system's internal indexing
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &fileData); // searchPath is wstring so .c_str() is used to make it constant
    if(hFind == INVALID_HANDLE_VALUE){
        const wchar_t* errMsg = L"[!] failed to access directory path\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        HeapDestroy(hHeapPrivate);
        return 3;
    }
    do{
        if(!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
            const wchar_t* fileName = fileData.cFileName; // assigning filename
            /*
                nFileSizeHigh is upper 32 bits and nFileSizeLow is lower 32 bits
                so lets say number we get in upper bits 1234 and lower bits 5678
                we cannot do 1234 + 5678 ... that is wrong ... so we need to append it
                so we perform 32 bits shifting left side and bitwise or operation to form the 64 bit fileSize
            */
            ULONGLONG fileSize = ((ULONGLONG)fileData.nFileSizeHigh << 32) | fileData.nFileSizeLow; 
            insertNodes(root, fileName, fileSize);
        }
    }while(FindNextFileW(hFind, &fileData)); // the loop is going to continue as long as there is a consecutive file
    // FindNextFile() returns BOOL type (True/False)
    printSortedFiles(root);
    HeapDestroy(hHeapPrivate); // destroying the private heap container/region so manual freeing of allocated heap blocks using HeapFree()
    return 0;
}