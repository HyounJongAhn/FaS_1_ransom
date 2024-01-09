#include <Windows.h>
#include <bcrypt.h> 
#include <stdio.h>
#include <stdlib.h> 
#include "aes_dec.h"
#include "print.h"
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)




void GET_ALG_HANDLE(BCRYPT_ALG_HANDLE* handle)
{
    NTSTATUS status = BCryptOpenAlgorithmProvider(
        handle,                 // Algorithm Handle pointer 
        BCRYPT_AES_ALGORITHM,   // Cryptographic Algorithm name 
        NULL,                   // 
        0);                     // Flags 

    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptOpenAlgorithmProvider fail\n", status);
        BCryptCloseAlgorithmProvider(handle, 0);
        return;
    }

    return;
}


void AES_Dec_TEST(BCRYPT_ALG_HANDLE ALG_HANDLE)
{
    NTSTATUS status = 0;
    BCRYPT_KEY_HANDLE KEY_HANDLE = NULL;        // AES Key Handle
    DWORD IVLength = 0;                         // IV Length 
    DWORD BlockLength = 0;                      // Block Length 
    DWORD bufferSize = 0;                       // Size of buffer 
    BYTE iv[16] = { 0, };
    memcpy(iv, IV, 16);

    PBYTE ciphertextsave;
    ciphertextsave = (PBYTE)calloc(ciphertextLength, sizeof(BYTE));
    memcpy(ciphertextsave, ciphertext, ciphertextLength);


    BYTE AES256KEY_CHANGE[32] = { 0, };
    memcpy(AES256KEY_CHANGE, plainkey, 32);
    

    printf("\nin aes\n");
    PRINT(ciphertextsave, ciphertextLength, PRINT_CIPHERTEXT);


    status = BCryptGenerateSymmetricKey(
        ALG_HANDLE,         // Algorithm Provider Handle
        &KEY_HANDLE,        // A pointer to Key Handle
        NULL,               // 
        0,                  // 
        AES256KEY_CHANGE,          // A pointer to a buffer that contains the key material 
        sizeof(AES256KEY_CHANGE),  // Size of the buffer that contains the key material 
        0);                 // Flags 
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptGenerateSymmetricKey fail\n");
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }


    status = BCryptSetProperty(
        ALG_HANDLE,                      // CNG HANDLE
        BCRYPT_CHAINING_MODE,            // Property name 
        (PBYTE)BCRYPT_CHAIN_MODE_CBC,    // Buffer that contains new property value 
        sizeof(BCRYPT_CHAIN_MODE_CBC),   // Size of the buffer that contains new propety value 
        0);                              // Flags 
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptSetProperty fail\n",status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }


    status = BCryptGetProperty(
        ALG_HANDLE,              // CNG HANDLE
        BCRYPT_BLOCK_LENGTH,     // Property name 
        (PBYTE)&IVLength,       // Buffer which receives the property value 
        sizeof(DWORD),           // Size of the buffer which receives the property value 
        &bufferSize,             // Number of bytes that wer copied into the buffer 
        0);                      // Flags 
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptGetProperty fail\n",status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }

    status = BCryptDecrypt(                         // Calculate plaintext length
        KEY_HANDLE,              // KEY HANDLE 
        ciphertextsave,              // Address of the buffer that contains the ciphertext 
        ciphertextLength,        // Size of the buufer that contains the ciphertext 
        NULL,                    // A pointer to padding info used with asymetric
        iv,                      // Address of the buffer that contains the Initial Vector 
        IVLength,                // Size of the buffer that contains the Initial Vector
        NULL,                    // Address of the buffer that receives the plaintext. 
        0,                       // Size of the buffer that receives the plaintext 
        &decplaintextLength,        // Variable that receives number of bytes copied to plaintext buffer
        BCRYPT_BLOCK_PADDING);   // Flags : Block Padding
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptDecrypt(Calculate plaintextLength) fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }
    else
    {
        decplaintext = (PBYTE)calloc(decplaintextLength, sizeof(BYTE));        // Free neededa
        if (decplaintext == NULL)
        {
            printf("Memory Allocation(plaintext) Fail...\n");
            BCryptDestroyKey(KEY_HANDLE);
            return;
        }
    }


    status = BCryptDecrypt(                         // Decrypt Data
        KEY_HANDLE,              // KEY HANDLE 
        ciphertextsave,              // Address of the buffer that contains the ciphertext 
        ciphertextLength,      // Size of the buufer that contains the ciphertext 
        NULL,                    // A pointer to padding info used with asymetric
        IV,                      // Address of the buffer that contains the Initial Vector 
        IVLength,                // Size of the buffer that contains the Initial Vector
        decplaintext,               // Address of the buffer that receives the plaintext. 
        decplaintextLength,         // Size of the buffer that receives the plaintext 
        &decplaintextLength,        // Variable that receives number of bytes copied to plaintext buffer
        BCRYPT_BLOCK_PADDING);   // Flags : Block Padding 
    if (!NT_SUCCESS(status))
    {
        printf("%s", plaintext);
        printf("Error Code : %x \n BCryptDecrypt(Decrypt Data) fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }

    PRINT(decplaintext, decplaintextLength, PRINT_PLAINTEXT);
    BCryptDestroyKey(KEY_HANDLE);
    free(ciphertextsave);
    free(ciphertext); // file

}