#include "aes.h"
#include "print.h"
#include "crng.h"
#include"main.h"

#define keyLength 32
#define NonceLength 8

void GET_ALG_AES_HANDLE(BCRYPT_ALG_HANDLE* handle)
{
    NTSTATUS status = BCryptOpenAlgorithmProvider(
        handle,                
        BCRYPT_AES_ALGORITHM,
        NULL,
        0);


    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptOpenAlgorithmProvider fail\n", status);
        BCryptCloseAlgorithmProvider(handle, 0);
        return;
    }

    return;
}

void AES_Enc_TEST(BCRYPT_ALG_HANDLE ALG_HANDLE, BYTE* plaintext, DWORD filesize)
{
    NTSTATUS status = 0;
    BCRYPT_KEY_HANDLE KEY_HANDLE = NULL;
    DWORD IVLength = 0;
    DWORD BlockLength = 0;
    DWORD bufferSize = 0;

    BYTE iv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    BYTE AES256KEY_CHANGE[keyLength] = { 0, };
    memcpy(AES256KEY_CHANGE, &AES256Key2, keyLength);

    //AES256KEY_CHANGE[24] = (BYTE)"0x50";
    //AES256KEY_CHANGE[25] = (BYTE)"0x48";
    //AES256KEY_CHANGE[26] = (BYTE)"0x50";
    //AES256KEY_CHANGE[27] = (BYTE)"0x52";
    //AES256KEY_CHANGE[28] = (BYTE)"0x95";
    //AES256KEY_CHANGE[29] = (BYTE)"0x70";
    //AES256KEY_CHANGE[30] = (BYTE)"0x97";
    //AES256KEY_CHANGE[31] = (BYTE)"0x83";

    PRINT(plaintext, filesize, PRINT_PLAINTEXT);
    printf("Asdasd");


    std::cout << "change" << "\n";
    PRINT(AES256KEY_CHANGE, keyLength, PRINT_PLAINKEY);

    status = BCryptGenerateSymmetricKey(
        ALG_HANDLE,        
        &KEY_HANDLE,      
        NULL,              
        0,                
        AES256KEY_CHANGE,        
        keyLength,  
        0);           
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptGenerateSymmetricKey fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }

    status = BCryptSetProperty(
        ALG_HANDLE,                    
        BCRYPT_CHAINING_MODE,           
        (PBYTE)BCRYPT_CHAIN_MODE_CBC,    
        sizeof(BCRYPT_CHAIN_MODE_CBC),  
        0);                          
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptSetProperty fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }

    status = BCryptGetProperty(
        ALG_HANDLE,             
        BCRYPT_BLOCK_LENGTH,     
        (PBYTE)&IVLength,       
        sizeof(DWORD),         
        &bufferSize,             
        0);                      
    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptGetProperty fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }

    status = BCryptEncrypt(                         
        KEY_HANDLE,              
        plaintext,              
        filesize,       
        NULL,                   
        iv,                      
        IVLength,              
        NULL,                    
        0,                      
        &ciphertextLength,     
        BCRYPT_BLOCK_PADDING);   

    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptEncrypt(Calculate ciphertextLength) fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }
    else
    {
        ciphertext = (PBYTE)calloc(ciphertextLength, sizeof(BYTE));        
        if (ciphertext == NULL)
        {
            printf("Memory Allocation(ciphertext) Fail...\n");
            BCryptDestroyKey(KEY_HANDLE);
            return;
        }
    }

    status = BCryptEncrypt(                        
        KEY_HANDLE,           
        plaintext,               
        filesize,       
        NULL,                   
        iv,                      
        IVLength,                
        ciphertext,             
        ciphertextLength,        
        &bufferSize,             
        BCRYPT_BLOCK_PADDING);  

    if (!NT_SUCCESS(status))
    {
        printf("Error Code : %x \n BCryptEncrypt(Encrypt Data) fail\n", status);
        BCryptDestroyKey(KEY_HANDLE);
        return;
    }

    printf("ciphertext1");    

    PRINT(ciphertext, ciphertextLength, PRINT_CIPHERTEXT);
    BCryptDestroyKey(KEY_HANDLE);

    return;
}