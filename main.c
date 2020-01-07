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

	trie = init();
	printf("Please enter words: \n");
	readWords();
	killTree(trie);	//free memory of tree


	return 0;
}

