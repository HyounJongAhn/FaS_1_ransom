#pragma once
#include <Windows.h>
#include <bcrypt.h> 
#include <stdio.h>
#include <stdlib.h> 

#include <iostream>
#include <algorithm>
#include <iterator>
#include <fileapi.h>
#include <tchar.h>
#include <string.h>
#include <fstream>
#include <filesystem>

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

extern PBYTE plaintext;
extern DWORD plaintextLength;
extern PBYTE decplaintext;
extern PBYTE decplaintext2;

extern DWORD decplaintextLength;
extern BYTE IV[16];
extern BYTE AES256Key[32];

extern PBYTE ciphertext;
extern DWORD ciphertextLength;
extern PBYTE plaintext;
extern DWORD plaintextLength;

extern BYTE cipherkey[512];
extern PBYTE plainkey;
extern DWORD plainkeyLength;
extern BYTE NONCE[8];
extern PBYTE originfilesize;
extern DWORD originfilelen;
extern const _TCHAR* originalFilePath2;
