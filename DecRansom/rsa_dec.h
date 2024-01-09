#pragma once
#include <Windows.h>
#include <bcrypt.h> 
#include <stdio.h>
#include <stdlib.h> 
#include "main.h"
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

#define PRINT_PLAINTEXT 1
#define PRINT_CIPHERTEXT 2

#define SUCCESS 1 
#define FAIL 0

#define PrivateKeyBLOB_Size 1051



typedef struct _PrivateKey_BLOB {
    ULONG Magic;
    ULONG BitLength;
    ULONG cbPublicExp;
    ULONG cbModulus;
    ULONG cbPrime1;
    ULONG cbPrime2;
    BYTE PublicExponent[3];
    BYTE Modulus[512];
    BYTE p[256];
    BYTE q[256];
} PrivateKey_BLOB;

void GET_ALG_RSA_HANDLE(BCRYPT_ALG_HANDLE* handle);
int SettingPublicKeyBLOB(PrivateKey_BLOB** BLOB);
void FreePrivateKeyBLOB(PrivateKey_BLOB** BLOB);
void RSA_4096_Test(BCRYPT_ALG_HANDLE ALG_HANDLE);