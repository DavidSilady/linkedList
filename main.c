#include "functions.h"
#include "main_functions.h"

int main(int argc, char **argv) {
	char input_command;
	struct car_list *car_first = NULL;
	
	while ((input_command = getchar())) {
		switch (input_command) {
			case 'n' :
				open(&car_first);
				break;
			case 'v' :
				print_all(&car_first);
				break;
			case 'p' :
				add(&car_first);
				break;
			case 'k' : //End
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