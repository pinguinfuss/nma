/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <abort@digitalise.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return J. Dijkstra (04/29/2010)
 * ----------------------------------------------------------------------------
 *  Modified by Adriano Maia (adriano@usk.bz)
 */
#include "nma.h"
#include <stdio.h>
#include <stdlib.h>

#define APP_NAME "NotifyMyAndroidExample"

int main(int argc, char** argv) {	
	if (argc < 4)
	{
		printf("Usage: nma <api_key> <priority-number> <event> <description>\n");
		return 1;
	}
	
	printf("Return code: %d\n", nma_push_msg(argv[1], atoi(argv[2]), APP_NAME, argv[3], argv[4]));

    return 0;
}
