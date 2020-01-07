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
				insert (trie,word);	//add word to tree
				free(word);	//free memory of last word
				size=1;
				i=0;	//set index and size for new word
				word = (char*)malloc(1);	//allocate memory for new word
				if(scanf("%c",&word[i])!=1) return FALSE;
			}

		}
		word[i]='\0';	//end of STDIN, set end of word
		insert(trie,word);	//add last word
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

boolean insert(node* root,char* word){
	node* pNode = root;
	int i=0,index=0;
	while (word[i]!='\0'){
		index = (int)word[i]-(int)'a';	//convert alphabet index to array index
		if (index<0 || index>25) {i++;	//ignore non small alphabet characters
		continue;
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
