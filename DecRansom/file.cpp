#include "file.h"
#include"main.h"

#define keyLength 32
#define NonceLength 8


void ReadFileContents(const _TCHAR* filePath, BYTE*& fileContents, DWORD& fileSize) {
    HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile != INVALID_HANDLE_VALUE) {
        // 파일 크기 가져오기
        fileSize = GetFileSize(hFile, NULL);
        if (fileSize == INVALID_FILE_SIZE) {
            fprintf(stderr, "File Size error (Error: %lu)\n", GetLastError());
            CloseHandle(hFile);
        }

        // 파일 내용을 담을 메모리 할당
        fileContents = new BYTE[fileSize];

        // 원본 파일 내용을 BYTE 배열로 읽어오기
        DWORD bytesRead;
        while (ReadFile(hFile, fileContents, fileSize, &bytesRead, NULL) && bytesRead > 0) {
            //printf("\n\nplainsize %s\n\n", fileContents);

        }

        CloseHandle(hFile);
    }
    else {
        fprintf(stderr, "open file error: %s (Error: %lu)\n", filePath, GetLastError());
    }

}

void loadFile(const _TCHAR* originalFilePath) {
    HANDLE hOriginalFile = CreateFile(originalFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    BYTE* plaintext = nullptr;
    DWORD fileSize = 0;

    // 파일 내용을 BYTE 배열로 읽어오기
    ReadFileContents(originalFilePath, plaintext, fileSize);
    if (plaintext != nullptr) {
        originalFilePath2 = originalFilePath;
        std::string contentStr(reinterpret_cast<char*>(plaintext), fileSize);
        size_t index = contentStr.find("CBC100");

        if (index != std::string::npos) {
            std::cout << "Found 'CBC100' at index: " << index << " in file: " << originalFilePath << std::endl;
        }
        else {
            std::cout << "'CBC100' not found in file: " << originalFilePath << std::endl;
        }
        PRINT(plaintext, fileSize, PRINT_PLAINTEXT);

        ciphertext = (PBYTE)calloc(index-520, sizeof(BYTE));
        originfilesize = (PBYTE)calloc(fileSize - index + 6, sizeof(BYTE));        


        for (int i = 0; i < 8; i++) {
            NONCE[i] = plaintext[i];
        }
        for (int i = 8; i < index - 511; i++) {
            ciphertext[i-8] = plaintext[i];
        }
        ciphertextLength = index - 520;
        for (int i = index - 1, j = 511; i > index - 513; i--, j--) {
            cipherkey[j] = plaintext[i];
        }

        for (int i = index + 6, j = 0; i < fileSize; i++, j++) {
            originfilesize[j] = plaintext[i];
        }
        originfilelen = fileSize - index + 6;

    }
    else {
        fprintf(stderr, "Origin File Read Error: %s (Error: %lu)\n", originalFilePath, GetLastError());
    }
}
namespace fs = std::filesystem;

void WriteOriginFile(const _TCHAR* originalFilePath) {
    // Remove ".fas" extension from the original file name
    fs::path originalPath(originalFilePath);
    _TCHAR newFilePath[MAX_PATH] = { 0, };
    _tcscat_s(newFilePath, _T("rec_"));  // Append a new extension, for example, "_new.txt"
    _tcscpy_s(newFilePath, originalPath.stem().c_str());  // Use stem() to get the file name without extension

    // Write the file with the modified name
    std::ofstream newWriteFile(newFilePath, std::ios_base::out | std::ios_base::binary);
    //decplaintext2 = (PBYTE)calloc(decplaintextLength, sizeof(BYTE));
    //memcpy(decplaintext2, &decplaintext, decplaintextLength);

    if (newWriteFile.is_open()) {
        newWriteFile << decplaintext;


        std::cout << "File written successfully: " << newFilePath << std::endl;
        newWriteFile.close();
    }
    else {
        std::cerr << "Error opening file for writing: " << newFilePath << std::endl;
    }
}



void FileSetting() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(_T("*.fas"), &findFileData);  // 검색 패턴을 "*.fas"로 업데이트

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << ".fas 파일을 찾을 수 없습니다.\n";
        return;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // 파일 이름 출력
            _tprintf(TEXT("file: %s\n"), findFileData.cFileName);
            _TCHAR filePath[MAX_PATH];
            _stprintf_s(filePath, _T("%s%s"), _T("."), findFileData.cFileName);
            loadFile(findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

// // ===============================================================================
// READ FILE FINISH
// ===============================================================================
