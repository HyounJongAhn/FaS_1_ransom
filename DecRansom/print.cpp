
#include "print.h"
#include "file.h"

void PRINT(BYTE* arr, DWORD size, int flag)
{
    if (flag == PRINT_NONCE) {
        printf("\nnonce : ");
        for (int i = 0; i < size; i++) {
            if (i % 4 == 0) printf("\n");
            printf("%02x\t", arr[i]);
        }
        printf("\n");
    }


    if (flag == PRINT_PLAINTEXT) {
        printf("\nplaintext : ");
        for (int i = 0; i < size; i++) {
            if (i % 4 == 0) printf("\n");
            printf("%02x\t", arr[i]);
        }
        printf("\n");
    }

    if (flag == PRINT_PLAINKEY) {
        printf("\nplainkey : ");
        for (int i = 0; i < size; i++) {
            if (i % 4 == 0) printf("\n");
            printf("%02x\t", arr[i]);
        }
        printf("\n");
    }

    if (flag == PRINT_CIPHERTEXT) {
        printf("\nciphertext : ");
        for (int i = 0; i < size; i++) {
            if (i % 4 == 0) printf("\n");
            printf("%02x\t", arr[i]);
        }
        printf("\n");
    }if (flag == PRINT_CIPHERKEY) {
        printf("\ncipherkey : ");
        for (int i = 0; i < size; i++) {
            if (i % 4 == 0) printf("\n");
            printf("%02x\t", arr[i]);
        }
        printf("\n");
    }

    if (flag == PRINT_DECRYPT) {
        printf("\ndecrypt : ");
        for (int i = 0; i < size; i++) {
            if (i % 4 == 0) printf("\n");
            printf("%02x\t", arr[i]);
        }
        printf("\n");
    }


}