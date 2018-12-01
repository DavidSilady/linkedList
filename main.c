#include <functions.h>
#include <main_functions.h>
#include <ctype.h>


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