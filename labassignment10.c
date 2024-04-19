#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count;
	struct Trie* node[26];
};

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
	struct Trie* current = pTrie;
	for (int i = 0; i < strlen(word); i++) {
		if (current->node[word[i]] == NULL) {
			current->node[word[i]] = malloc(sizeof(struct Trie));
			pTrie->node[word[i]]->count = 0;
			for (int i = 0; i < 26; i++) {
				pTrie->node[i] = NULL;
			}
		}
		current = current->node[word[i]];
	}
	current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
	struct Trie* current = pTrie;
	while (pTrie != NULL || word != NULL) {
		for (int i = 0; i < strlen(word); i++) {
			if (current->node[word[i]] == NULL) {
				return 0;
			}
			current = current->node[word[i]];
		}
	}
	return current->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
	if (pTrie == NULL) {
		return NULL;
	}
	if (pTrie != NULL) {
		for (int i = 0; i < 26; i++) {
			if (pTrie->node[i]) {
				deallocateTrie(pTrie->node[i]);
			}
		}
		free(pTrie);
	}
	return 0;
}

// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
	if (pTrie != NULL) {
		pTrie->count = 0;
		for (int i = 0; i < 26; i++) {
			pTrie->node[i] = NULL;
		}
	}
	return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
	FILE* file = fopen(filename, "r");
	if (file != NULL) {
		return 0;
	}

	int inWords = 256;
	int numWords;
	fscanf(file, "%d", &numWords);

	for (int i = 0; i < numWords; i++) {
		pInWords[i] = (char*)malloc(sizeof(char) * inWords);
		fscanf(file, "%s", pInWords[i]);
	}

	fclose(file);
	return numWords;
}

int main(void)
{
	char* inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n", inWords[i]);
	}

	struct Trie* pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}