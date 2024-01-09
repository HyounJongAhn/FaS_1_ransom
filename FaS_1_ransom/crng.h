#pragma once

#ifndef TEST1
#define TEST1


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

void GET_ALG_KEY_HANDLE(BCRYPT_ALG_HANDLE* handle);
void GEN_RANDOM(BCRYPT_ALG_HANDLE RNG_HANDLE, BYTE* AES256Key);
void GET_ALG_NONCE_HANDLE(BCRYPT_ALG_HANDLE* handle);
void GEN_RANDOM_NONCE(BCRYPT_ALG_HANDLE RNG_HANDLE, BYTE* Nonce);

#endif // !TEST