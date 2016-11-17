//
//  Huffman.h
//  HuffmanCode
//
//  Created by Sang Gyeong Jo on 2016. 11. 16..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef Huffman_h
#define Huffman_h

#include "Essential.h"
#include "MinPriorityQueue.h"

typedef struct priority_queue m_queue;
m_queue *queue;
node *tbl;


int tbl_sz;


void make_heap(){
    queue = calloc(1,sizeof(m_queue));
    queue->size = 0;
    queue->heap = calloc(0,sizeof(node));
}

int find_node(m_queue *q, char C)
{
    for (int i = 0 ; i < q->size ; i++)
        if(q->heap[i]->c == C) return i;
    
    return -1;
}

void remove_node_zero(m_queue *q)
{
    if (q->heap[0]->freq == 0) extract_min(q);
}

node new_node()
{
    node n = calloc(1,sizeof(struct node));
    n->c = -1;
    n->freq = 1;
    n->left = NULL;
    n->right = NULL;
    n->is_leaf = 0;
    
    return n;
}

void build_data(FILE *fp)
{
    make_heap();
    char c;
    
    while(EOF != (c = fgetc(fp)))
    {
        int n = find_node(queue, c);
        if( n == -1)
        {
            node z = new_node();
            z->c = c;
            insert(queue, z);
        }
        else
        {
            increase_key(queue, c, 1);
        }

    }
    
    tbl_sz = queue->size;
    tbl = calloc(tbl_sz,sizeof(node));
    tbl_sz = 0;
    
    
    print_queue(queue);
    printf("\nsize : %d\n",queue->size);
    printf("\n");
    
    fclose(fp);
}

void huffman()
{
    for (int i = 0; i <= queue->size + 2 ; i++)
    {
        node z = new_node();
        node x = extract_min(queue);
        node y = extract_min(queue);
        z->left = x;
        z->right = y;
        z->freq = x->freq + y->freq;
        insert(queue, z);
    }
    
    for(int i=0; i<queue->size; i++) printf("%c, %5u\n",queue->heap[i]->c,queue->heap[i]->freq);
}

void tbl_push(node n)
{
    tbl_sz++;
    tbl[tbl_sz-1] = n;
}

void search(node n, char *bf, int d)
{
    if(n->left == NULL && n->right == NULL)
    {
        bf[d] = '\0';
        strcpy(n->vcwd, bf);
        tbl_push(n);
        return;
    }
    if(n->left != NULL)
    {
        bf[d] = '0';
        search(n->left, bf, d+1);
    }
    if(n->right != NULL)
    {
        bf[d] = '1';
        search(n->right, bf, d+1);
    }
}

void get_vcwd()
{
    char bf[256];
    node n = queue->heap[0];
    search(n, bf, 0);
}

void print_tbl()
{
    for(int i=0; i<tbl_sz; i++) printf("%c, %s\n",tbl[i]->c,tbl[i]->vcwd);
}

char *find_code(char c)
{
    for (int i = 0; i<tbl_sz; i++)
        if (tbl[i]->c == c) return tbl[i]->vcwd;
    
    return "NOCODE";
}

void encoding(FILE *fp, FILE *f_enc, FILE *f_table)
{
    huffman();
    get_vcwd();
    
    char c;
    
    for(int i=0; i<tbl_sz; i++)
    {
        fprintf(f_table,"%c,%s\n",tbl[i]->c,tbl[i]->vcwd);
        printf("%c,%s\n",tbl[i]->c,tbl[i]->vcwd);
    }
    
    while(EOF != (c = fgetc(fp)))
        fprintf(f_enc,"%s",find_code(c));
    
    fclose(fp);
    fclose(f_enc);
    fclose(f_table);
}

void f_print_tbl(FILE *fp)
{
    for(int i = 0 ; i<tbl_sz; i++)
        fprintf(fp,"%c, %s",tbl[i]->c,tbl[i]->vcwd);
    
    fclose(fp);
}

node read_table(FILE *fp)
{
    node n = new_node();
    node p;
    
    while(!feof(fp))
    {
        char trgt_c;
        char *line = NULL;
        char tmp[256];
        size_t len = 0;
        ssize_t read;
        
        fscanf(fp,"%c,%s\n",&trgt_c,tmp);
        p = n;
        
        //if ((read = getline(&line, &len, fp)) == -1) printf("read error!");
        
        int i = 0;
        char ch = tmp[0];
        
        while(ch != '\0')
        {
            ch = tmp[i];
            if ( ch == '0')
            {
                if (p->left == NULL)
                {
                    p->left = new_node();
                    p = p->left;
                }
                else
                    p = p->left;
            }
            else if ( ch == '1')
            {
                if (p->right == NULL)
                {
                    p->right = new_node();
                    p = p->right;
                }
                else
                    p = p->right;
            }
            i++;
        }
        p->c = trgt_c;
        p->is_leaf = 1;
    }
    
    fclose(fp);
    
    return n;   //return tree
}

void decoding(FILE *tbl, FILE *orgn, FILE *output)
{
    node tree = read_table(tbl);
    node p = tree;
    
    char c;
    
    while(EOF != (c = fgetc(orgn)))
    {
        if ( c == '0')
        {
            if (p->left->is_leaf)
            {
                printf("%c",p->left->c);
                fprintf(output,"%c",p->left->c);
                p = tree;
            }
            else
            {
                p = p->left;
            }
        }
        else if ( c == '1')
        {
            if (p->right->is_leaf)
            {
                printf("%c",p->right->c);
                fprintf(output,"%c",p->right->c);
                p = tree;
            }
            else
            {
                p = p->right;
            }
        }
        else
        {
            printf("Endoding format error!");
            exit(1);
        }
        
    }
    
    fclose(orgn);
    fclose(output);
}


#endif /* Huffman_h */
