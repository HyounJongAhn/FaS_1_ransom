#pragma once
#pragma once
#ifndef TEST3
#define TEST3


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

#define PRINT_PLAINTEXT 2
#define PRINT_CIPHERTEXT 3
#define PRINT_DECRYPT 4
#define PRINT_RANDOM 5
#define PRINT_PLAINKEY 6
#define PRINT_CIPHERKEY 7
#define PRINT_NONCE 8
#define PRINT_CIPHERKEYNEW 9
#define WRITE_PRINT_CIPHERTEXT 10

void PRINT(BYTE* arr, DWORD size, int flag);

#endif // !1
