/*
 * trie.c
 *
 *  Created on: 7 Jan 2020
 *      Author: r2rb
 */
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	long unsigned int count;
	struct node *children[NUM_LETTERS];
} node;
node *trie;
struct node* init() {	//init empty node
	node *nuNode = NULL;
	nuNode = (node*) malloc(sizeof(node));	//allocate size of node struct
	if (nuNode != NULL) {
		nuNode->letter = '\0';
		nuNode->count = 0;
		for (int i = 0; i < NUM_LETTERS; i++)	//init children
			nuNode->children[i] = NULL;
	}
	return nuNode;
}
boolean insert(char *word) {
	node *pNode = trie;	//set pointer to root
	int i = 0, index = 0;
	while (word[i] != '\0') {
		index = word[i] - 'a';	//convert alphabet index to array index
		if (index < 0 || index >= NUM_LETTERS) {//char not small alphabet, check if upper case alphabet
			index += 'a' - 'A';	//if a capital letter, add ascii value and convert index
			word[i] += 'a' - 'A';
			if (index < 0 || index >= NUM_LETTERS) {
				i++;	//check next char
				continue;	//ignore non small alphabet characters
			}
		}
		if (pNode->children[index] == NULL) {//char doesn't exist - create new node and set letter
			pNode->children[index] = init();
			if (pNode->children[index] == NULL)
				return FALSE;	//fail to allocate memory
			pNode->children[index]->letter = word[i];
		}
		pNode = pNode->children[index];	// move to next child and check next char
		i++;
	}
	pNode->count++;	//new word, add to count

	return TRUE;
}
void readWords() {
	char *word = NULL;
	char *temp = NULL;
	int i = 0;
	int size = 1;
	word = (char*) malloc(1);	//init input size of one char
	if (scanf("%c", &word[i]) != 1) {
		free(word);
		return;
	}
	while (word[i] != EOF) {
		size++;		//more chars in STDIN - increase size of string
		temp = (char*) realloc(word, size + 1);
		if (temp == NULL) {	//try to reallocate into new space
			free(word);
			return;
		}
		word = temp;
		i++;	//next index for char input
		if (scanf("%c", &word[i]) != 1) {
			free(word);
			return;
		}
		if (word[i] == ' ' || word[i] == '\n') {
			word[i] = '\0';	//set end of word
			if (insert(word) == FALSE) {	//add word to tree
				printf("failed to add word to trie");
				free(word);
				return;
			}
			free(word);	//free memory of last word
			size = 1;
			i = 0;	//set index and size for new word
			word = (char*) malloc(1);	//allocate memory for new word
			if (scanf("%c", &word[i]) != 1) {
				free(word);
				return;
			}
		}

	}

}

void killTree(node *root) {
	if (root != NULL) {
		for (int i = 0; i < NUM_LETTERS; i++)	//free children first
			killTree(root->children[i]);
		free(root);
	}

}
void printTrie(boolean r) {
	char *word = NULL;
	word = (char*) malloc(2);	//allocate space for first char and end of word
	if (r == FALSE) {	//print lexicographically
		for (int i = 0; i < NUM_LETTERS; i++)
			printTree(trie->children[i], word, 2);
	} else {
		for (int i = NUM_LETTERS - 1; i >= 0; i--)	//print reverse order
			printTreeR(trie->children[i], word, 2);
	}
	free(word);

}
void printTree(node *pNode, char *word, int size) {
	char *temp = NULL;
	if (pNode == NULL)
		return;
	word[size - 2] = pNode->letter;	//add current char to string and end word
	word[size - 1] = '\0';
	if (pNode->count > 0)	//node is end of word, print word

		printf("%s\t%ld\n", word, pNode->count);

	size++;
	temp = malloc(size);	//prepare string for next children
	if (temp == NULL)
		return;
	for (int i = 0; i < size - 1; i++)//deep copy of string, prevent memory conflicts
		temp[i] = word[i];
	for (int i = 0; i < NUM_LETTERS; i++)	//recursive call lexico order

		printTree(pNode->children[i], temp, size);

	free(temp);	//finished with all sons of node, can release this string
}
void printTreeR(node *pNode, char *word, int size) {
	char *temp = NULL;
	if (pNode == NULL)	//check if node empty - nothing to print
		return;
	word[size - 2] = pNode->letter;	//add current char to string and end word
	word[size - 1] = '\0';
	size++;
	temp = malloc(size);	//prepare string for next children
	if (temp == NULL)
		return;
	for (int i = 0; i < size - 1; i++)	//copy string and send to children
		temp[i] = word[i];

	for (int i = NUM_LETTERS - 1; i >= 0; i--)	//recursive call reverse lexico

		printTreeR(pNode->children[i], temp, size);

	free(temp);	//finished with children - release copied string

	if (pNode->count > 0)	//if word ending - print word
		printf("%s\t%ld\n", word, pNode->count);

}
