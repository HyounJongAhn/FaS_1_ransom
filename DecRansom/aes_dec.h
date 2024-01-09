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
#define PRINT_DECRYPT 3
void GET_ALG_HANDLE(BCRYPT_ALG_HANDLE* handle);
void AES_Dec_TEST(BCRYPT_ALG_HANDLE ALG_HANDLE);