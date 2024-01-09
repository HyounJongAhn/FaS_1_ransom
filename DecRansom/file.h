#pragma once
#ifndef TEST2
#define TEST2


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

#include "print.h"


#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

void ReadFileContents(const _TCHAR* filePath, BYTE*& fileContents, DWORD& fileSize);
void loadFile(const _TCHAR* originalFilePath);
void FileSetting();
void WriteOriginFile(const _TCHAR* originalFilePath);

#endif // !TEST