/*
 * main.c
 *
 *  Created on: 7 Jan 2020
 *      Author: r2rb
 */
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
	char* word=NULL;
	char* temp=NULL;
	node* trie = init();
	int i=0;
	int size=1;
	word = (char*)malloc(1);	//init input size of one char
	printf("Please enter words: \n");
	scanf("%c",&word[i]);
	while (word[i]!= '\n'){
		size++;		//more chars in STDIN - increase size of string
		temp = (char*)realloc(word,size+1);
		if (temp == NULL){	//try to reallocate into new space
			free(word);
			return 1;	//realloc failed, return 1
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
			scanf("%c",&word[i]);
		}

	}
	word[i]='\0';	//end of STDIN, set end of word
	insert(trie,word);	//add last word
	free(word);	//free memory of last word
	killTree(trie);	//free memory of tree


	return 0;
}

