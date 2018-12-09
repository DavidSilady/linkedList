#include <functions.h>
#include <main_functions.h>
#include <ctype.h>


int main(int argc, char **argv) {
	FILE file_p;
	char input_command;
	struct car_list *car_first = NULL;
	
	while ((input_command = getchar())) {
		switch (input_command) {
			case 'n' :
				open(&file_p, &car_first);
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