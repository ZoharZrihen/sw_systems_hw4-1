/*
 * trie.h
 *
 *  Created on: 7 Jan 2020
 *      Author: r2rb
 */

#ifndef TRIE_H_
#define TRIE_H_
#define NUM_LETTERS 26
typedef struct node node;
typedef enum {FALSE=0, TRUE=1} boolean;
node* init();
boolean insert(node*,char*);
void killTree(node*);
#endif /* TRIE_H_ */
