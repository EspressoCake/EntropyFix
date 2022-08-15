#pragma once
#include <Windows.h>




PBYTE ReduceEntropy(unsigned char* Payload, SIZE_T PayloadSize, SIZE_T* NewPayloadSize);
PBYTE ReverseEntropy(unsigned char* Payload, SIZE_T PayloadSize, SIZE_T* pNewPayloadSize);
