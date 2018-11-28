#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_NUM 7
#define MAX_LINE_LENGTH 200

struct car_list {
	char category[50];
	char manufacturer[50];
	char seller[100];
	int price;
	int production_year;
	char condition[200];
	struct car_list *next;
	struct car_list *prev;
};

void free_all(struct car_list **car_first);
void free_node(struct car_list **car_current);

char *s_toupper(char const *line);
int found_substring(char *haystack, char *needle);

void read_line(char *line);

void open(FILE *f_p, struct car_list **car_first, struct car_list **car_current, int *entryCount);

int countEntries(FILE *f_p);
void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]);
void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]);
void fill_node(struct car_list *car_current,char line[LINE_NUM][MAX_LINE_LENGTH]);
void add(struct car_list **car_current);
void add_node(struct car_list **car_current, struct car_list **car_new);
void delete_nodes(struct car_list **car_first);
void find(struct car_list **car_first);
void update(struct car_list **car_first);

void print_all(struct car_list **car_first);
void print_node(struct car_list *car_current);

void alloc_first(struct car_list **car_current);
void alloc_next(struct car_list **car_current);

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

void delete_nodes(struct car_list **car_first) {
	struct car_list *car_current = *car_first;
	char deletion[MAX_LINE_LENGTH];
	int num_deletions = 0;
	scanf("%*c");
	read_line(deletion);
	
	while (car_current != NULL) {
		if (found_substring(car_current->manufacturer, deletion)) {
			num_deletions++;
			if (car_current == *car_first) {
				*car_first = car_current->next;
			}
			free_node(&car_current);
		}
		car_current = car_current->next;
	}
	printf("Vymazalo sa %d zaznamov.\n", num_deletions);
}

int found_substring(char *haystack, char *needle) {
	if (strstr(s_toupper(haystack), s_toupper(needle)) != NULL) {
		return 1;
	}
	return 0;
}

char *s_toupper(char const *line) {
	char *temp_line;
	temp_line = (char *)calloc(strlen(line), sizeof(char));
	strcpy(temp_line, line);
	int i = 0, current_letter;
	while (temp_line[i] != '\0') {
		current_letter = temp_line[i];
		temp_line[i] = toupper(current_letter);
		i++;
	}
	return temp_line;
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

void add_node(struct car_list **car_current, struct car_list **car_new) {
	char line[LINE_NUM][MAX_LINE_LENGTH];
	read_lines(line);
	fill_node(*car_new, line);
	if (*car_new != *car_current) {
		(*car_new)->next = *car_current;
	}
	(*car_new)->prev->next = NULL;
	(*car_new)->prev = (*car_current)->prev;
	if ((*car_new)->prev != NULL) {
		(*car_current)->prev->next = *car_new;
	}
	(*car_current)->prev = *car_new;
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

void alloc_first(struct car_list **car_current) {
	*car_current = malloc(sizeof(struct car_list));
	if (car_current == NULL) {
		printf("Insufficient memory.\n");
	}
	(*car_current)->prev = NULL;
}

void alloc_next(struct car_list **car_current) {
	(*car_current)->next = malloc(sizeof(struct car_list));
	(*car_current)->next->prev = *car_current;
	*car_current = (*car_current)->next;
	(*car_current)->next = NULL;
}

void fill_node(struct car_list *car_current, char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i = 1; //line[0] = '$' ALWAYS
	strcpy(car_current->category, line[i++]);
	strcpy(car_current->manufacturer, line[i++]);
	strcpy(car_current->seller, line[i++]);
	car_current->price = atoi(line[i++]);
	car_current->production_year = atoi(line[i++]);
	strcpy(car_current->condition, line[i++]);
}

void print_node(struct car_list *car_current) {
	printf("Kategoria: %s\n", car_current->category);
	printf("Znacka: %s\n", car_current->manufacturer);
	printf("Predajca: %s\n", car_current->seller);
	printf("Cena: %d\n", car_current->price);
	printf("Rok_Vyroby: %d\n", car_current->production_year);
	printf("Stav_vozidla: %s\n", car_current->condition);
}

void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i;
	for (i = 0; i < LINE_NUM; i++) {
		fgets(line[i], MAX_LINE_LENGTH, f_p);
		line[i][strcspn(line[i], "\n")] = 0;
	}
	return;
}

void read_line(char *line) {
	int i = 0;
	while ((line[i] = getchar()) != '\n') {
		i++;
	}
	line[strcspn(line, "\n")] = 0;
	return;
}

void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i;
	scanf("%*c");
	for (i = 1; i < LINE_NUM; i++) {
		read_line(line[i]);
	}
	return;
}

int countEntries(FILE *f_p) {
	int entryCount = 0;
	char line[50];

	while(!feof(f_p)) {
		fgets(line, 50, f_p);
		if (line[0] == '$') {
			entryCount++;
		}
	}
	rewind(f_p);
	return entryCount;
}

void free_all(struct car_list **car_first) {
	struct car_list **car_next = car_first;
	while (*car_first != NULL) {
		*car_next = (*car_first)->next;
		free(*car_first);
		*car_first = *car_next;
	}
}

void free_node(struct car_list **car_current) {
	if ((*car_current)->prev != NULL)
		(*car_current)->prev->next = (*car_current)->next;
	if ((*car_current)->next != NULL)
		(*car_current)->next->prev = (*car_current)->prev;
	free(*car_current);
}
