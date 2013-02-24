/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <abort@digitalise.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return J. Dijkstra (04/29/2010)
 * ----------------------------------------------------------------------------
 *  Modified by Christian Heim (christian.heim@barfoo.org)
 */
#include "nma.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void usage(char *argv0) {
	printf("%s, version: %s\n", argv0, NMA_VERSION);
	printf("\n");
	printf("Required arguments:\n");
	printf("--apifile\n");
	printf("\tPath to the API key file (see below)\n");
	printf("\n--app\n");
	printf("\tName of the application submitting the notification.\n\tIf no value has been passed, it'll default to NMA-for-C.\n\tMax length: 256\n");
	printf("\n--priority\n");
	printf("\tPriority as an integer value\n\tPossible values: -2, ..., 2\n\tSee nma.h for the corresponding levels.\n");
	printf("\n--event\n");
	printf("\tSubject of the notification.\n\tMax length: 1000\n");
	printf("\n--description\n");
	printf("\tNotification text.\n\tMax length: 10000\n");
	printf("\nOther arguments:\n");
	printf("--help\n");
	printf("\tPrint this help message\n");
	printf("\n--verbose\n");
	printf("\tDisplay some debugging information.\n");
	printf("\nThe API key configration file should look like this:\n");
	printf("apikey = asehukf348cge1oxhd2ysvn06hlyq6y5kmzes604jr7fjdq7\n");
}

int main(int argc, char *argv[]) {

	int getopts;
	char *filename;
	char *app;
	unsigned int priority;
	char *event;
	char *description;
	char apikey[48];
	int verbose = 0;
	int getopt_index = 0;

	static struct option long_options[] =
	{
		{"apifile", required_argument, NULL, 'f'},
		{"app", required_argument, NULL, 'a'},
		{"priority", required_argument, NULL, 'p'},
		{"event", required_argument, NULL, 'e'},
		{"description", required_argument, NULL, 'd'},
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, NULL, 'h'}
	};

	while (( getopts = getopt_long(argc, argv, "f:a:p:e:d:vh", long_options, &getopt_index)) != -1)
	{
		switch (getopts)
		{
			case 'h':
				usage(argv[0]);
				exit(1);
			case 'v':
				verbose = 1;
				break;
			case 'f':
				filename = optarg;
				break;
			case 'a':
			app = optarg;
				break;
			case 'p':
				priority = atoi(optarg);
				break;
			case 'e':
				event = optarg;
				break;
			case 'd':
				description = optarg;
				break;
			default:
				usage(argv[0]);
				exit(1);
		}
	}

	if ( verbose > 0 )
	{
		printf("filename: %s\n", filename);
		printf("app: %s\n", app);
		printf("priority: %u\n", priority);
		printf("event: %s\n", event);
		printf("description: %s\n", description);
	}

	FILE *fp;
	if (( fp=fopen(filename, "r")) == NULL)
	{
		printf("Unable to open config file: %s\n", filename);
		return 1;
	}
	else
	{
		if ( fscanf(fp, "apikey = %s", &apikey) == 1 )
		{
			if ( verbose > 0 )
			{
				printf("apikey: %s\n", apikey);
				printf("Return code: %d\n", nma_push_msg(apikey, priority, app, event, description));
				return 0;
			}
			else
			{
				nma_push_msg(apikey, priority, app, event, description);
				return 0;
			}
		}
		else
		{
			printf("Invalid syntax config file: %s\n", filename);
			return 1;
		}
	}
	fclose(fp);
}
