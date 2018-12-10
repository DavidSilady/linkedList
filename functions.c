#include <functions.h>
#include <struct.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void assign_all(FILE *f_p, struct car_list **car_first) {
	struct car_list *car_current;
	int entryCount;
	int i;
	char line[LINE_NUM][MAX_LINE_LENGTH];
	
	entryCount = countEntries(f_p);
	printf("Nacitalo sa %d zaznamov.\n", entryCount);
	if (entryCount == 0) {
		return;
	}
	
	alloc_first(car_first);
	fread_lines(f_p, line);
	fill_node(*car_first, line);
	car_current = *car_first;
	
	for (i = 1; i < entryCount; i++) {
		alloc_next(&car_current);
		fread_lines(f_p, line);
		fill_node(car_current, line);
	}
}

int found_substring(char *haystack, char *needle) {
	if (strstr(s_toupper(haystack), s_toupper(needle)) != NULL) {
		return 1;
	}
	return 0;
}

//Transforms and returns a copy of a string to UPPERCASE
char *s_toupper(char const *line) {
	char *temp_line;
	int i = 0, current_letter;
	
	temp_line = (char *)calloc(strlen(line), sizeof(char));
	strcpy(temp_line, line);
	
	while (temp_line[i] != '\0') {
		current_letter = temp_line[i];
		temp_line[i] = toupper(current_letter);
		i++;
	}
	
	return temp_line;
}

void add_node(struct car_list **car_current, struct car_list **car_new) {
	char line[LINE_NUM][MAX_LINE_LENGTH];
	read_lines(line);
	fill_node(*car_new, line);
	
	//Shifting pointers
	//If the new node isn't the last one, assign the ->next pointer
	if (*car_new != *car_current) {
		(*car_new)->next = *car_current;
	}
	(*car_new)->prev->next = NULL;
	(*car_new)->prev = (*car_current)->prev;
	
	//If the new node isn't the first node, assign the ->prev pointer
	if ((*car_new)->prev != NULL) {
		(*car_current)->prev->next = *car_new;
	}
	(*car_current)->prev = *car_new;
	//End of shifting
}

void alloc_first(struct car_list **car_current) {
	*car_current = malloc(sizeof(struct car_list));
	if (car_current == NULL) {
		printf("Insufficient memory.\n");
	}
	(*car_current)->prev = NULL;
	(*car_current)->next = NULL;
}

void alloc_next(struct car_list **car_current) {
	(*car_current)->next = malloc(sizeof(struct car_list));
	(*car_current)->next->prev = *car_current;
	*car_current = (*car_current)->next;
	//Makes sure the list doesn't try to go on beyond this point
	(*car_current)->next = NULL;
}

//Assigns all the individual values to an entry | from already 2x2Array - line (requires fread_lines/read_lines prior)
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

//Reads LINE_NUMx lines from a file to 2x2 array (line)
void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i;
	for (i = 0; i < LINE_NUM; i++) {
		fgets(line[i], MAX_LINE_LENGTH, f_p);
		line[i][strcspn(line[i], "\n")] = 0;
	}
	return;
}
//Reads LINE_NUMx lines from keyboard/terminal to 2x2 array (line)
void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]) {
	int i;
	scanf("%*c");
	for (i = 1; i < LINE_NUM; i++) {
		read_line(line[i]);
	}
	return;
}
//Reads an individual line (replaces '\n' with '\0')
void read_line(char *line) {
	int i = 0;
	while ((line[i] = getchar()) != '\n') {
		i++;
	}
	line[strcspn(line, "\n")] = 0;
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


void free_node(struct car_list **car_current) {
	struct car_list *car_temp;
	
	//If the current node isn't the first, assign
	if ((*car_current)->prev != NULL)
		(*car_current)->prev->next = (*car_current)->next;
	//If the current node isn't the last, assign 
	if ((*car_current)->next != NULL)
		(*car_current)->next->prev = (*car_current)->prev;
	
	//Fixes overflow dependency
	car_temp = *car_current;
	*car_current = (*car_current)->next;
	
	free(car_temp);
}
