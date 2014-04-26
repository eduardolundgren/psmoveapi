
 /**
 * tracking.js PS Move API
 * Copyright (c) 2012 Eduardo Lundgren <eduardolundgren@gmail.com>
 * All rights reserved.
 **/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "psmove.h"

 int ui_set_controller(PSMove *move) {
	int buttons,
		data = psmove_poll(move);

	if (data) {
		buttons = psmove_get_buttons(move);

		if (buttons) {
			if (buttons & Btn_TRIANGLE) {
				psmove_set_leds(move, 0, 255, 255);
			}
			else if (buttons & Btn_CIRCLE) {
				psmove_set_leds(move, 0, 180, 0);
			}
			else if (buttons & Btn_CROSS) {
				psmove_set_leds(move, 255, 255, 0);
			}
			else if (buttons & Btn_SQUARE) {
				psmove_set_leds(move, 255, 0, 255);
			}

			// printf("Controller buttons: %x\n", buttons);
		}
		else {
			psmove_set_leds(move, 0, 0, 0);
		}

		psmove_update_leds(move);
	}

	 return 1;
 }

int main(int argc, char* argv[]) {
	PSMove *move1, *move2;

	printf("=> tracking.js PSMove Controller (Eduardo Lundgren)");
	printf("\n=> Connected controllers: %d\n", psmove_count_connected());
	printf("\n\thelp:");
	printf("\n\t\tBtn_TRIANGLE: Cyan");
	printf("\n\t\tBtn_CIRCLE: Off");
	printf("\n\t\tBtn_CROSS: Blue");
	printf("\n\t\tBtn_SQUARE: Magenta");
	printf("\n");

	move1 = psmove_connect_by_id(0);
	move2 = psmove_connect_by_id(1);

	while (1) {
		ui_set_controller(move1);
		ui_set_controller(move2);
	}

	psmove_disconnect(move1);
	psmove_disconnect(move2);

	return 0;
}

