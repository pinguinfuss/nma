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
	FILE * file = fopen( argv[1], "r");
	char apikey[48];

	if (argc < 4)
	{
		printf("Usage: nma /api/config/file <priority-number> <event> <description>\n");
		printf("\nThe API key configration file should look like this:\n");
		printf("apikey = asehukf348cge1oxhd2ysvn06hlyq6y5kmzes604jr7fjdq7\n");
		return 1;
	}

	if ( fscanf(file, "apikey = %s", &apikey) == 1 )
	{
		printf("Return code: %d\n", nma_push_msg(apikey, atoi(argv[2]), APP_NAME, argv[3], argv[4]));
		return 0;
	}
	else
	{
		printf("Unable to open/invalid syntax config file: %s", file);
		return 1;
	}
	

}
