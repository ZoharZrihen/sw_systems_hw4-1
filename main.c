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
	boolean r=FALSE;
	if (argc > 2){
		printf("illegal input, only parameter possible is 'r'\n");
		return 1;
	}
	if (argc == 2 && argv[1][0] == 'r' && argv[1][1] == '\0')
		r=TRUE;
	else if (argc == 2){
		printf("illegal input, only parameter possible is 'r'\n");
		return 1;
	}
	trie = init();
	printf("Please enter words: \n");
	readWords();
	printTrie(r);
	killTree(trie);	//free memory of tree
	return 0;
}

