#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int countEntries(FILE *f_p);
void fread_lines(FILE *f_p, char line[LINE_NUM][MAX_LINE_LENGTH]);
void read_lines(char line[LINE_NUM][MAX_LINE_LENGTH]);
void fill_node(struct car_list *car_current,char line[LINE_NUM][MAX_LINE_LENGTH]);
void free_node(struct car_list **car_current);
char *s_toupper(char const *line);
int found_substring(char *haystack, char *needle);
void read_line(char *line);
void add_node(struct car_list **car_current, struct car_list **car_new);
void delete_nodes(struct car_list **car_first);
void print_all(struct car_list **car_first);
void print_node(struct car_list *car_current);
void alloc_first(struct car_list **car_current);
void alloc_next(struct car_list **car_current);

#endif