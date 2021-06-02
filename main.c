/*
 ============================================================================
 Name        : Prompt.c
 Author      : Felipe Sousa Barbosa
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Implemented:
        - put
        - list
        - remove
        - first
        - last
        - sort (bubble sort)
*/


typedef struct node {
    int num;
    struct node* next;
} node;

void sort_list(node *l){
    if(l == NULL)
        return;
    
    int aux_num;
    node *aux_l = l;
    node *aux_nxt;

    while(aux_l->next != NULL)
    {
        aux_nxt = aux_l->next;

        while(aux_nxt != NULL)
        {
            if(aux_l->num > aux_nxt->num)
            {                    
                aux_num = aux_l->num;
                aux_l->num = aux_nxt->num;
                aux_nxt->num = aux_num;
            }
            aux_nxt = aux_nxt->next;
        }

        aux_l = aux_l->next;
    }

    show_list(l);
}

void show_list(node *l){
    node *aux_l = l;

    while(aux_l != NULL){
        printf("%d ", aux_l->num);
        aux_l = aux_l->next;
    }
    printf("\n");

}

void first(node *l){
    printf("%d\n", l->num);
}

void last(node *l){
        node* aux_l = l;

        while(aux_l->next != NULL){
            aux_l = aux_l->next;
        }
        printf("%d\n", aux_l->num);
}

void remove_node(node **l, int position){
        if(position < 1)
            return;

        if(position == 1){
            node* aux = *l;
            printf("%d\n", aux->num);
            *l = (*l)->next;
            free(aux);
            return;
        }

        node* prev_node = *l;
        node* curr_node = prev_node->next;

        int i = 2;

        while(i != position && curr_node != NULL){
            prev_node = curr_node;
            curr_node = curr_node->next;
            i++;
        }

        if(curr_node != NULL){
            node* aux = curr_node;
            printf("%d\n", curr_node->num);
            prev_node->next = curr_node->next;
            free(aux);
        }
}

void put(node** l, int num){
    node *n = (node*)malloc(sizeof(node));
    n->num = num;

    if(*l == NULL){
        *l = n;
        (*l)->next = NULL;
    }
    else{
        node* aux_l = *l;

        while(aux_l->next != NULL){
            aux_l = aux_l->next;
        }

        n->next = aux_l->next;
        aux_l->next = n;
    }

    show_list(*l);

}

void print_entry(char *entry) {
	printf("You entered: %s\n", entry);
}

int main(int argc, char *argv[]) {
	char input[201];
    char delimiter[2] = " ";
    char *command;
    char *operand_str;
    int operand;

    node* my_list = NULL;

	while(1) {
		printf("prompt> ");
		if (fgets(input, 200, stdin) == NULL) {
			printf("An error ocurred.\n");
			break;
		}

		if (strncmp(input, "exit\n", 5) == 0) {
			printf("Leaving. Good bye.\n");
			break;
		}

        command = strtok(input, delimiter);
        operand_str =  strtok(NULL, delimiter);

        if(strncmp(input, "put", 4) == 0){
            operand = strtol(operand_str, NULL, 10);
            put(&my_list, operand);
        }
        else if(strncmp(input, "first", 5) == 0){
            first(my_list);
        }
        else if(strncmp(input, "last", 4) == 0){
            last(my_list);
        }
        else if(strncmp(input, "remove", 4) == 0){
            operand = strtol(operand_str, NULL, 10);
            remove_node(&my_list, operand);
        }
        else if(strncmp(input, "list", 4) == 0){
            show_list(my_list);
        }
        else if(strncmp(input, "sort", 4) == 0){
            sort_list(my_list);
        }

		// print_entry(input);
	}

	return EXIT_SUCCESS;
}