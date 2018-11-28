#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void delete_nodes(struct car_list **car_first);
void open(FILE *f_p, struct car_list **car_first, struct car_list **car_current, int *entryCount);
void add(struct car_list **car_first);
void update(struct car_list **car_first);
void find(struct car_list **car_first);
void free_all(struct car_list **car_first);
void print_all(struct car_list **car_first);

#endif