#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
};

// Node for linked list in hash table
struct ListNode {
    struct RecordType data;
    struct ListNode* next;
};

// HashType structure with an array of list pointers
struct HashType {
    struct ListNode** buckets;
    int size;
};

// Compute the hash function
int hash(int x, int tableSize) {
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);
        }
        fclose(inFile);
    }
    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// Initializes a HashType structure
struct HashType* initHash(int size) {
    struct HashType* hashTable = malloc(sizeof(struct HashType));
    hashTable->buckets = malloc(sizeof(struct ListNode*) * size);
    hashTable->size = size;
    for (int i = 0; i < size; i++) {
        hashTable->buckets[i] = NULL;
    }
    return hashTable;
}

// Inserts a record into the hash table
void insertHash(struct HashType* hashTable, struct RecordType record) {
    int index = hash(record.id, hashTable->size);
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    newNode->data = record;
    newNode->next = hashTable->buckets[index];
    hashTable->buckets[index] = newNode;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray) {
    for (int i = 0; i < pHashArray->size; ++i) {
        struct ListNode* node = pHashArray->buckets[i];
        if (node != NULL) {
            printf("Index %d ->", i);
            while (node != NULL) {
                printf(" %d, %c, %d ->", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf(" NULL\n");
        }
    }
    printf("\n");
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    int hashSize = 10; // Size of the hash table
    struct HashType* hashTable = initHash(hashSize);
    for (int i = 0; i < recordSz; ++i) {
        insertHash(hashTable, pRecords[i]);
    }
    displayRecordsInHash(hashTable);

    return 0;
}