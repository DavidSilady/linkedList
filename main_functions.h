#ifndef MAIN_FUNCTIONS_H_INCLUDED
#define MAIN_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include "struct.h"

void delete_nodes(struct car_list **car_first);
void open(struct car_list **car_first);
void add(struct car_list **car_first);
void update(struct car_list **car_first);
void find(struct car_list **car_first);
void free_all(struct car_list **car_first);
void print_all(struct car_list **car_first);

#endif