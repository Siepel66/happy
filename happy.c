#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>       
#include <unistd.h>

#include "wget_switch.h"

int main(int argc, char **argv) {
	WGET_SWITCH mySwitch;

	wget_switch_init(&mySwitch, "192.168.2.150", 80, 12);
	mySwitch.off(&mySwitch);
	usleep(1000000);
	mySwitch.on(&mySwitch);
}
