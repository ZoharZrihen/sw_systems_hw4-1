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
