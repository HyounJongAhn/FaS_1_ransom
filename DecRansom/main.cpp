#include "main.h"
#include "aes_dec.h"
#include "rsa_dec.h"
#include "file.h"


PBYTE plaintext = NULL;
DWORD plaintextLength = 0;
PBYTE decplaintext = NULL;
PBYTE decplaintext2 = NULL;

DWORD decplaintextLength = 0;

BYTE IV[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
BYTE AES256Key[32] = { 0x68, 0xFC, 0x87, 0x86, 0x1A, 0x7A, 0xC5, 0xEB, 0xA1, 0xB3, 0x57, 0x61,
    0x12, 0xFD, 0x66, 0x17, 0x4C, 0xF7, 0xC8, 0x90, 0x33, 0xF2, 0x89, 0x6E,
    0xE5, 0x46, 0xB3, 0x36, 0x55, 0x58, 0x4B, 0x69 };

PBYTE ciphertext = { 0, };
DWORD ciphertextLength = 0;
BYTE  cipherkey[512] = { 0, };
DWORD cipherkeyLength = 512;

PBYTE plainkey = { 0, };
DWORD plainkeyLength = 0;

BYTE NONCE[8] = { 0, };
PBYTE originfilesize = { 0, };
DWORD originfilelen = 0;
const _TCHAR* originalFilePath2;
int main()
{

    FileSetting();

    BYTE newcipherkey[512] = { 0, };
    memcpy(newcipherkey, &cipherkey, 512);
    PRINT(NONCE, 8, PRINT_NONCE);
    PRINT(newcipherkey, cipherkeyLength, PRINT_CIPHERKEY);
    PRINT(ciphertext, ciphertextLength, PRINT_CIPHERTEXT);

    for (int i = 0; i < originfilelen; i++) {
        printf("%c", originfilesize[i]);
    }


    BCRYPT_ALG_HANDLE RSA_ALG = NULL;
    GET_ALG_RSA_HANDLE(&RSA_ALG);
    RSA_4096_Test(RSA_ALG);
    BCryptCloseAlgorithmProvider(RSA_ALG, 0);

    PRINT(plainkey, plainkeyLength, PRINT_PLAINKEY);


    BCRYPT_ALG_HANDLE ALG_HANDLE = NULL;
    GET_ALG_HANDLE(&ALG_HANDLE);
    AES_Dec_TEST(ALG_HANDLE);
    BCryptCloseAlgorithmProvider(ALG_HANDLE, 0);

    
    PRINT(decplaintext, decplaintextLength, PRINT_PLAINTEXT);
    decplaintextLength = 0;
    WriteOriginFile(originalFilePath2);

    free(originfilesize); // file
    free(plainkey); // rsa_dec
    free(decplaintext);
    return 0;


}

