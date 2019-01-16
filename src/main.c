#include <stdio.h>
#include <stdlib.h>

#include <include/interface.h>

int main(void)
{
	interface_t *interface = NULL;

	interface = init_interface();

	if (interface != NULL) {
		fprintf(stdout, "Successfully initialized interface !\n");
		SDL_Delay(3000);
	} else {
		printf("error\n");
		return (EXIT_FAILURE);
	}

	destroy_interface(interface);
}
