
#include "crng.h"
#include "print.h"
#include "main.h"

#define keyLength 32
#define NonceLength 8

// ===============================================================================
// GENkey
// ===============================================================================


void GET_ALG_KEY_HANDLE(BCRYPT_ALG_HANDLE* handle )
{
    NTSTATUS status = BCryptOpenAlgorithmProvider(
        handle,                 
        BCRYPT_RNG_ALGORITHM,  
        NULL,                   
        0);                    

    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptOpenAlgorithmProvider fail\n", status);
        return;
    }

    return;

}

void GEN_RANDOM(BCRYPT_ALG_HANDLE RNG_HANDLE, BYTE* AES256Key)
{
    NTSTATUS status = BCryptGenRandom(
        RNG_HANDLE,                           
        AES256Key,                                
        keyLength,     
        BCRYPT_RNG_USE_ENTROPY_IN_BUFFER);
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptGenRandom fail\n", status);
        return;
    }


    PRINT(AES256Key, keyLength, PRINT_RANDOM);
    return;

}

// =======================================================================
// GENkey FINISH
// =======================================================================




// =======================================================================
// GENNONCEH START
// =======================================================================


void GET_ALG_NONCE_HANDLE(BCRYPT_ALG_HANDLE* handle)
{
    NTSTATUS status = BCryptOpenAlgorithmProvider(
        handle,                 // Algorithm Handle pointer
        BCRYPT_RNG_ALGORITHM,   // Cryptographic Algorithm name
        NULL,                   //
        0);                     // Flags


    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptOpenAlgorithmProvider fail\n", status);
        return;
    }

    return;

}

void GEN_RANDOM_NONCE(BCRYPT_ALG_HANDLE RNG_HANDLE, BYTE* Nonce)
{
    NTSTATUS status = BCryptGenRandom(
        RNG_HANDLE,                       
        Nonce,                           
        NonceLength,                       
        BCRYPT_RNG_USE_ENTROPY_IN_BUFFER);   
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptGenRandom fail\n", status);
        return;
    }

    PRINT(Nonce, NonceLength, PRINT_NONCE);
    return;

}

// =======================================================================
// GENNONCE FINISH
// =======================================================================
