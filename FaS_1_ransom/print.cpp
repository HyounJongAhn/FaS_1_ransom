
#include "print.h"
#include "aes.h"
#include "rsa.h"
#include "file.h"
#include "crng.h"
#include"main.h"

// GENKEY
#define keyLength 32
#define NonceLength 8
void PRINT(BYTE* arr, DWORD size, int flag)
{
    if (flag == PRINT_PLAINTEXT) {
        printf("\nplaintext : ");
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
    }

    if (flag == WRITE_PRINT_CIPHERTEXT) {
        printf("\nciphertext : ");
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

    if (flag == PRINT_RANDOM)
    {
        printf("\nrandom_key : ");
        for (int i = 0; i < size; i++) {
            if (i % 16 == 0) printf("\n");
            printf("%02x\t", arr[i]);
            AES256Key2[i] = arr[i];

        }
        printf("\n");
    }

    if (flag == PRINT_PLAINKEY) {
        printf("\nplain_aes_key : ");
        for (int i = 0; i < size; i++) {
            if (i % 16 == 0) printf("\n");
            printf("0x%02x\t", arr[i]);

        }
        printf("\n");
    }

    if (flag == PRINT_CIPHERKEY) {
        printf("\ncipher_aes_key : ");
        for (int i = 0; i < size; i++) {
            if (i % 16 == 0) printf("\n");
            printf("0x%02x\t", arr[i]);
        }
        printf("\n");
    }
    if (flag == PRINT_CIPHERKEYNEW) {
        printf("\ncipher_aes_key : ");
        for (int i = 0; i < size; i++) {
            if (i % 16 == 0) printf("\n");
            printf("0x%02x\t", arr[i]);
            savecipherkey[i] = arr[i];
        }
        printf("\n");
    }

    if (flag == PRINT_NONCE) {
        printf("\ndata_nonce : ");
        for (int i = 0; i < size; i++) {
            if (i % 16 == 0) printf("\n");
            printf("%02x\t", arr[i]);
            copyNonce[i] = arr[i];

        }
        printf("\n");
    }

}
