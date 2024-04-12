#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

// Fill out this structure
struct HashType
{
	struct RecordType* data;
	int data;
};

// Compute the hash function
int hash(int x, int hashSz)
{
	return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType* pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
	int i;
	struct RecordType* data;
	for (i = 0; i < hashSz; ++i)
	{
		if (pHashArray[i].data) {
			printf("%d, %c, %d\n", pHashArray[i].data->id, pHashArray[i].data->name, pHashArray[i].data->order);
		}
		// if index is occupied with any records, print all
	}
}

int main(void)
{
	struct RecordType* pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	int hashSz = 10;
	struct HashType* table = (struct HashType*)malloc(sizeof(struct HashType));
	int x = pRecords[hashSz].id;
	table[hash(x,hashSz)].data = 0;

	for (int i = 0; i < recordSz; ++i) {
		int x = pRecords[i].id;
		while (table[hash(x,hashSz)].data) {
			i += 1;
			i %= hashSz;
		}
		table[hash(x, hashSz)].data = 1;
	}

	displayRecordsInHash(table, hashSz);
	free(table);
}