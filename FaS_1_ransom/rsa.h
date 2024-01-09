#pragma once
#ifndef TEST4
#define TEST4

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

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)


// RSA
#define SUCCESS 1
#define FAIL 0

#define PulbicKeyBLOB_Size 539

typedef struct _PublicKey_BLOB {
    ULONG Magic;               
    ULONG BitLength;           
    ULONG cbPublicExp;          
    ULONG cbModulus;          
    ULONG cbPrime1;        
    ULONG cbPrime2;             // The size(byte) of the q;
    BYTE PublicExponent[3];     // Array of Public Exponent e; e = 65537 = 0x01, 0x00, 0x01
    BYTE Modulus[512];          // Array of Modulus n; In RSA-4096, n = 4096-bit = 512-byte
} PublicKey_BLOB;

void GET_ALG_RSA_HANDLE(BCRYPT_ALG_HANDLE* handle);
int SettingPublicKeyBLOB(PublicKey_BLOB** BLOB);
void FreePublicKeyBLOB(PublicKey_BLOB** BLOB);
void RSA_4096_Enc(BCRYPT_ALG_HANDLE ALG_HANDLE);

#endif