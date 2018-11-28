#include <functions.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void delete_nodes(struct car_list **car_first);
void open(FILE *f_p, struct car_list **car_first, struct car_list **car_current, int *entryCount);
void add(struct car_list **car_first);
void update(struct car_list **car_first);
void find(struct car_list **car_first);
void free_all(struct car_list **car_first);
void print_all(struct car_list **car_first);

int main(int argc, char **argv) {
	FILE file_p;
	char input_command;
	int entryCount = 0;
	struct car_list *car_first = NULL;
	struct car_list *car_current = NULL;
	
	while ((input_command = getchar())) {
		switch (input_command) {
			case 'n' :
				open(&file_p, &car_first, &car_current, &entryCount);
				break;
			case 'v' :
				print_all(&car_first);
				break;
			case 'p' :
				add(&car_first);
				break;
			case 'k' :
				free_all(&car_first);
				return 0;
			case 'z' :
				delete_nodes(&car_first);
				break;
			case 'h' :
				find(&car_first);
				break;
			case 'a' :
				update(&car_first);
		}
	}
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
	
	if (*car_first == NULL) {
		alloc_first(car_first);
		read_lines(line);
		fill_node(*car_first, line);
		return;
	}
	
	while (car_new->next != NULL) {
		car_new = car_new->next;
	}
	alloc_next(&car_new);
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
	scanf("%*c");
	read_line(wanted_manufacturer);
	scanf("%d", &production_year);
	
	while (car_current != NULL) {
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

void open(FILE *f_p, struct car_list **car_first, struct car_list **car_current, int *entryCount) {
	char file_name[] = "auta.txt";
	int i;
	char line[LINE_NUM][MAX_LINE_LENGTH];
	f_p = fopen(file_name, "r");

	//Checks whether the file was found.
	if (f_p == NULL) {
		printf("Zaznamy neboli nacitane.\n");
		return;
	}
	if (*car_first != NULL) {
		free_all(car_first);
	}
	
	*entryCount = countEntries(f_p);
	printf("Nacitalo sa %d zaznamov.\n", *entryCount);
	if (*entryCount == 0) {
		return;
	}
	
	alloc_first(car_first);
	fread_lines(f_p, line);
	fill_node(*car_first, line);
	*car_current = *car_first;
	
	for (i = 1; i < *entryCount; i++) {
		alloc_next(car_current);
		fread_lines(f_p, line);
		fill_node(*car_current, line);
	}
	(*car_current)->next = NULL;
	
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