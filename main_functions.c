#include "main_functions.h"
#include "functions.h"
#include "struct.h"
#include <string.h>
#include <stdlib.h>


void delete_nodes(struct car_list **car_first) {
	struct car_list *car_current = *car_first;
	char deletion[MAX_LINE_LENGTH];
	int num_deletions = 0;
	scanf("%*c");
	read_line(deletion);
	
	while (car_current != NULL) {
		if (found_substring(car_current->manufacturer, deletion)) {
			num_deletions++;
			//Shifts the pointer to the first node, if the first node is about to be deleted
			if (car_current == *car_first) {
				*car_first = car_current->next;
			}
			
			free_node(&car_current);
		}
		car_current = car_current->next;
	}
	
	printf("Vymazalo sa %d zaznamov.\n", num_deletions);
}

void add(struct car_list **car_first) {
	int position = 0, i = 0;
	char line[LINE_NUM][MAX_LINE_LENGTH];
	struct car_list *car_current = *car_first;
	struct car_list *car_new = *car_first;
	
	scanf("%d", &position);
	if (position < 1) {
		return;
	}
	//If no list exists yet...
	if (*car_first == NULL) {
		alloc_first(car_first);
		read_lines(line);
		fill_node(*car_first, line);
		return;
	}
	//Find the end of the list
	while (car_new->next != NULL) {
		car_new = car_new->next;
	}
	
	alloc_next(&car_new);
	//Find new position
	for (i = 0; i < position - 1; i++) {
		if ((car_current)->next == NULL) {
			break;
		}
		car_current = car_current->next;
	}
	
	add_node(&car_current, &car_new);
	
	if (position == 1) {
		*car_first = car_new;
	}
}


void find(struct car_list **car_first) {
	struct car_list *car_current = *car_first;
	char wanted_manufacturer[MAX_LINE_LENGTH];
	int max_price, index = 1, isFound = 0;
	
	scanf("%*c");
	read_line(wanted_manufacturer);
	scanf("%d", &max_price);
	
	while (car_current != NULL) {
		//Finds the fitting node
		if (!(strcmp(s_toupper(wanted_manufacturer), s_toupper(car_current->manufacturer))) && car_current->price <= max_price) {
			
			printf("%d.\n", index++);
			print_node(car_current);
			isFound = 1;
		}
		car_current = car_current->next;
	}
	
	if (!isFound) {
		printf("V ponuke nie su pozadovane auta.\n");
	}
}

void update(struct car_list **car_first) {
	struct car_list *car_current = *car_first;
	char wanted_manufacturer[MAX_LINE_LENGTH];
	int production_year, num_changes = 0;
	
	scanf("%*c"); //skips the '\n' after input command character
	read_line(wanted_manufacturer);
	scanf("%d", &production_year);
	
	while (car_current != NULL) {
		//Finds a match to the requirements
		if (car_current->production_year == production_year && !strcmp(s_toupper(wanted_manufacturer), s_toupper(car_current->manufacturer))) {
			num_changes++;
			
			car_current->price -= 100;
			if (car_current->price < 0) {
				car_current->price = 0;
			}
		}
		
		car_current = car_current->next;
	}
	printf("Aktualizovalo sa %d zaznamov.\n", num_changes);
}

void print_all(struct car_list **car_first) {
	int i = 1;
	struct car_list *car_current = *car_first;
	
	while (car_current != NULL) {
		printf("%d.\n", i++);
		print_node(car_current);
		car_current = car_current->next;
	}
}

void open(struct car_list **car_first) {
	FILE *f_p;
	char file_name[] = "car_list.txt";
	f_p = fopen(file_name, "r");

	//Checks whether the file was found.
	if (f_p == NULL) {
		printf("Zaznamy neboli nacitane.\n");
		return;
	}
	
	//If a list already exists, delete it
	if (*car_first != NULL) {
		free_all(car_first);
	}
	assign_all(f_p, car_first);
	
	fclose(f_p);
	return;
}


void free_all(struct car_list **car_first) {
	struct car_list **car_next = car_first;
	
	while (*car_first != NULL) {
		*car_next = (*car_first)->next;
		free(*car_first);
		*car_first = *car_next;
	}
}