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
	printf("\tPriority of this notification.\n\tPossible values are: 2 (EMERGENCY), 1 (HIGH), 0 (NORMAL), -1 (MODERATE), -2 (LOW)\n");
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
	char filename[1000];
	char *app;
	int priority;
	char *event;
	char *description;
	char apikey[48];
	int verbose = 0;
	int getopt_index = 0;

	static struct option long_options[] =
	{
		{"apifile",	required_argument,	0, 'f'},
		{"app",		required_argument,	0, 'a'},
		{"priority",	required_argument,	0, 'p'},
		{"event",	required_argument,	0, 'e'},
		{"description",	required_argument,	0, 'd'},
		{"verbose",	no_argument,		0, 'v'},
		{"help",	no_argument,		0, 'h'}
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
				strncpy(filename, optarg, sizeof(filename));
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

	if ( (filename == NULL) || (app == NULL) || (event == NULL) ||
		       (description == NULL) || (priority < -2) || (priority > 2))
	{
		usage(argv[0]);
		exit(1);
	}

	if ( verbose > 0 )
	{
		printf("filename: %s\n", filename);
		printf("app: %s\n", app);
		printf("priority: %i\n", priority);
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
