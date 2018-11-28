#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

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

#endif