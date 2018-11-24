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


void open(FILE *f_p, struct car_list **car_current, int *entryCount);
void read_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]);
void fill_node(struct car_list *car_current,char line[LINE_NUM][MAX_LINE_LENGTH]);
int countEntries(FILE *f_p);
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
			car_first = car_current;

			case 'n' :
				open(&file_p, &car_current, &entryCount);
				break;
		}
	}
	
	return 0;
}

void open(FILE *f_p, struct car_list **car_current, int *entryCount) {
	char file_name[] = "car_list.txt";
	int i = 0;
	f_p = fopen(file_name, "r");

	//Checks whether the file was found.
	if (f_p == NULL) {
		printf("Zaznamy neboli nacitane.\n");
		return;
	}

	*entryCount = countEntries(f_p);
	if (*entryCount == 0) {
		printf("Nacitalo sa 0 zaznamov.\n");
		return;
	}

	alloc_first(car_current);
	//car_current = car_current->next;
	/*for (i = 1; i < *entryCount; i++) {
		printf("%d", i);
		alloc_next(car_current);
		*car_current = *car_current->next;
	}*/
	
	char line[LINE_NUM][MAX_LINE_LENGTH];
	read_lines(f_p, line);
	fill_node(*car_current, line);
	print_node(*car_current);
	
	fclose(f_p);
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

void alloc_first(struct car_list **car_current) {
	*car_current = malloc(sizeof(struct car_list));
	if (car_current == NULL) {
		printf("Insufficient memory.\n");
	}
	//car_current->prev = NULL;
}
/*
void alloc_next(struct car_list **car_current) {
	car_current->next = malloc(sizeof(struct car_list));
	printf("Allocated. . .\n");
	car_current->next->prev = car_current;
}
*/
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
	printf("%s", car_current->category);
	printf("%s", car_current->manufacturer);
	printf("%s", car_current->seller);
	printf("%d", car_current->price);
	printf("%d", car_current->production_year);
	printf("%s", car_current->condition);
}

/*
char line[LINE_NUM][MAX_LINE_LENGTH];
*/

void read_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]) {

	int i;
	for (i = 0; i < LINE_NUM; i++) {
		fgets(line[i], MAX_LINE_LENGTH, f_p);
	}
	return;
}
