#include <Windows.h>
#include <stdio.h>

// DO NOT CHANGE [NewPayloadSize equation is based on these values]
#define NULL_CHUNKSIZE	5
#define PAYLOADCHUNK	10


PBYTE ReduceEntropy (unsigned char* Payload, SIZE_T PayloadSize, SIZE_T* pNewPayloadSize) {
	
	unsigned int	Loop			= PayloadSize / PAYLOADCHUNK;
	unsigned int	Remainder		= PayloadSize % NULL_CHUNKSIZE;
	unsigned int	NewPayloadSize  = (3 * PayloadSize ) / 2;		

	unsigned char*	NewPayload		= (unsigned char*)malloc(NewPayloadSize + Remainder);
	if (NewPayload == NULL)
		return NULL;
	//printf("[i] NewPayload : [ 0x%p ]  [ %d ] \n", NewPayload, NewPayloadSize);

	ZeroMemory(NewPayload, NewPayloadSize + Remainder);


	unsigned int NPcntr = 0, OPcntr = 0;

	for (size_t z = 0; z < Loop; z++){

		for (size_t i = 0; i < PAYLOADCHUNK; i++) {
			NewPayload[NPcntr] = Payload[OPcntr];
			NPcntr++;
			OPcntr++;
		}
		for (size_t j = 0; j < NULL_CHUNKSIZE; j++){
			NewPayload[NPcntr] = 0x00;
			NPcntr++;
		}
	}

	if (Remainder > 0) {
		for (size_t i = 0; i != Remainder; i++){
			NewPayload[NPcntr] = Payload[OPcntr];
			NPcntr++;
			OPcntr++;
		}
	}

	*pNewPayloadSize = NewPayloadSize;
	return (PBYTE)NewPayload;
}



PBYTE ReverseEntropy(unsigned char* Payload, SIZE_T PayloadSize, SIZE_T* pNewPayloadSize) {
	
	
	unsigned int Remainder			= PayloadSize % NULL_CHUNKSIZE;
	unsigned int NewPayloadSize		= ((PayloadSize / 3) * 2);
	unsigned int Loop				= NewPayloadSize / PAYLOADCHUNK;
	
	unsigned char* NewPayload		= (unsigned char*)malloc(NewPayloadSize + Remainder);
	if (NewPayload == NULL)
		return NULL;

	//printf("[i] NewPayload : [ 0x%p ]  [ %d ] \n", NewPayload, NewPayloadSize);
	ZeroMemory(NewPayload, NewPayloadSize + Remainder);
	unsigned int NPcntr = 0, OPcntr = 0;

	for (size_t i = 0; i < Loop; i++){

		for (size_t j = 0; j < PAYLOADCHUNK; j++){
			NewPayload[NPcntr] = Payload[OPcntr];
			NPcntr++;
			OPcntr++;
		}

		for (size_t z = 0; z < NULL_CHUNKSIZE; z++)
		{
			OPcntr++; // ignoring 5 bytes
		}
	}


	
	if (Remainder > 0) {
		for (size_t i = 0; i != Remainder; i++) {
			NewPayload[NPcntr] = Payload[OPcntr];
			NPcntr++;
			OPcntr++;
		}
	}
	

	*pNewPayloadSize = NewPayloadSize;
	return NewPayload;
}