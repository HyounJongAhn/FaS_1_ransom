#pragma once
#ifndef TEST
#define TSET

// 헤더 파일의 내용


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


// AES


void GET_ALG_AES_HANDLE(BCRYPT_ALG_HANDLE* handle);
void AES_Enc_TEST(BCRYPT_ALG_HANDLE ALG_HANDLE, BYTE* plaintext, DWORD filesize);
#endif // MY_HEADER_H
