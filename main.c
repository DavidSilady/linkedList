#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void open(FILE *f_p, struct car_list **car_first, struct car_list **car_current, int *entryCount);

int countEntries(FILE *f_p);
void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]);
void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]);
void fill_node(struct car_list *car_current,char line[LINE_NUM][MAX_LINE_LENGTH]);
void add(struct car_list **car_current);
void add_node(struct car_list **car_current, struct car_list **car_new);

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
		printf("Car_first = NULL\n");
		alloc_first(car_first);
		read_lines(line);
		fill_node(*car_first, line);
		return;
	}
	
	while (car_new->next != NULL) {
		car_new = car_new->next;
	}
	alloc_next(&car_new);
	printf("Alloc. . .\n");
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
	char file_name[] = "car_list.txt";
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
	if (*entryCount == 0) {
		printf("Nacitalo sa 0 zaznamov.\n");
		return;
	}
	printf("Entries: %d\n", *entryCount);
	
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
	printf("\n");
}

void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i;
	for (i = 0; i < LINE_NUM; i++) {
		fgets(line[i], MAX_LINE_LENGTH, f_p);
		line[i][strcspn(line[i], "\n")] = 0;
	}
	return;
}

void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i, j = 0;
	scanf("%*c");
	for (i = 1; i < LINE_NUM; i++) {
		while ((line[i][j] = getchar()) != '\n')
			j++;
		line[i][strcspn(line[i], "\n")] = 0;
		j = 0;
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
	struct car_list **car_temp = car_first;
	while (*car_first != NULL) {
		*car_temp = (*car_first)->next;
		free(*car_first);
		*car_first = *car_temp;
	}
}

void free_node(struct car_list **car_current) {
	(*car_current)->prev->next = (*car_current)->next;
	(*car_current)->next->prev = (*car_current)->prev;
	free(*car_current);
}
/*
bicykel
Honda
Zavadska 14 Kovarce
12
2001
nerozprava
*/