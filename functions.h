#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

//Working w/ strings
char *s_toupper(char const *line);
int found_substring(char *haystack, char *needle);

//Adding/Filling
void add_node(struct car_list **car_current, struct car_list **car_new);
void fill_node(struct car_list *car_current,char line[LINE_NUM][MAX_LINE_LENGTH]);

//Reading
	//Read multiple lines
void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]);
void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]);

	//Reads 1 line
void read_line(char *line);
int countEntries(FILE *f_p);

//Deleting
void delete_nodes(struct car_list **car_first);
void free_node(struct car_list **car_current);

//Printing
void print_all(struct car_list **car_first);
void print_node(struct car_list *car_current);

//Alloc
void alloc_first(struct car_list **car_current);
void alloc_next(struct car_list **car_current);

#endif