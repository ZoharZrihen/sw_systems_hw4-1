/*
 * trie.c
 *
 *  Created on: 7 Jan 2020
 *      Author: r2rb
 */
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char letter;
	long unsigned int count;
	struct node* children[NUM_LETTERS];
} node;
node* trie;
boolean readWords(){
	char* word=NULL;
		char* temp=NULL;
		int i=0;
		int size=1;
		word = (char*)malloc(1);	//init input size of one char
		if (scanf("%c",&word[i])!=1) return FALSE;
		while (word[i]!= '\n'){
			size++;		//more chars in STDIN - increase size of string
			temp = (char*)realloc(word,size+1);
			if (temp == NULL){	//try to reallocate into new space
				free(word);
				return FALSE;	//realloc failed, return false
			}
			word = temp;
			i++;	//next index for char input
			scanf("%c",&word[i]);
			if (word[i] == ' ') {
				word[i] = '\0';	//set end of word
				insert (word);	//add word to tree
				free(word);	//free memory of last word
				size=1;
				i=0;	//set index and size for new word
				word = (char*)malloc(1);	//allocate memory for new word
				if(scanf("%c",&word[i])!=1) return FALSE;
			}

		}
		word[i]='\0';	//end of STDIN, set end of word
		insert(word);	//add last word
		free(word);	//free memory of last word
		return TRUE;
}
struct node* init(){
	node* nuNode = NULL;
	nuNode = (node *)malloc(sizeof(node));
	if (nuNode != NULL){
		nuNode->letter='\0';
		nuNode->count=0;
		for (int i=0;i<26;i++)
			nuNode->children[i]=NULL;
	}
	return nuNode;
}
boolean insert(char* word){
	node* pNode = trie;
	int i=0,index=0;
	while (word[i]!='\0'){
		index = word[i]-'a';	//convert alphabet index to array index
		if (index<0 || index>25) {	//char not small alphabet, check if upper case alphabet
			index+='a'-'A';
			word[i]+='a'-'A';
			if (index<0 || index>25){
			i++;	//ignore non small alphabet characters
			continue; }
		}
		if (!pNode->children[index]){	//char doesn't exist - create new node
			pNode->children[index]=init();
			pNode->children[index]->letter=word[i];
		}
		pNode=pNode->children[index];	// move to next node
		i++;
	}
	pNode->count++;	//new word, add to count

	return TRUE;
}
void killTree(node* root){
	if (root != NULL)
	{
		for (int i=0;i<NUM_LETTERS;i++)	//free children first
			killTree(root->children[i]);
		free(root);
	}

}
void printTrie(boolean r){
	char* word = NULL;
	word = (char*)malloc(2);	//allocate space for first char and end of word
	if (r == FALSE) {	//print lexicographically
	for (int i=0;i<NUM_LETTERS;i++){

		printTree(trie->children[i],word,2);
	}
	}
	else	//print reverse order
	{
		for (int i=NUM_LETTERS-1;i>=0;i--){
		printTreeR(trie->children[i],word,2);
		}
	}
	free(word);


}
void printTree(node* root,char* word,int size){
	char* temp =NULL;
	if (root == NULL)
		return;
	word[size-2]=root->letter;	//add current char to string and end word
	word[size-1]='\0';
	if (root->count > 0)	//node is end of word, print word
	{
		printf("%s %ld\n",word, root->count);
	}
	size++;
	temp = malloc(size);	//prepare string for next children
	for (int i=0;i<size-1;i++)	//deep copy of string, prevent memory conflicts
		temp[i]=word[i];
	for (int i=0;i<NUM_LETTERS;i++)	//recursive call lexico order
	{
		printTree(root->children[i],temp,size);
	}
	free(temp);	//finished with all sons of node, can release this string
}
void printTreeR(node* root,char* word,int size){
	char* temp =NULL;
		if (root == NULL)
			return;
		word[size-2]=root->letter;
		word[size-1]='\0';

		size++;
		temp = malloc(size);
		for (int i=0;i<size-1;i++)
			temp[i]=word[i];

		for (int i=NUM_LETTERS-1;i>=0;i--)
		{
			printTreeR(root->children[i],temp,size);
		}
		free(temp);

		if (root->count > 0)
				{
					printf("%s %ld\n",word, root->count);
				}
}
