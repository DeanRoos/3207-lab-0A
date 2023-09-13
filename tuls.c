#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void openAll(char* name, int n);

int main (int argc, char *argv[] ){

	if (argc > 2){
		printf("%s", "tuls: incorrect arguments. Exiting program.\n");
		return 1;
	} else if (argc == 1){
		DIR *dp;
		struct dirent *d;
		dp = opendir(".");
		if (dp == NULL){
			closedir(dp);
			printf("%s", "tuls: cannot open directory\n");
			return 1;
		}
		while ((d = readdir(dp)) != 0){
			printf("%s\n", d->d_name);
		}
	} else {

		DIR *dp;
                struct dirent *d;
                dp = opendir(".");
                if (dp == NULL){
                        printf("%s", "tuls: cannot open directory\n");
                	return 1;
		}
		while ((d = readdir(dp)) != 0){
			if (strcmp(d->d_name, argv[1]) == 0){
				if (d->d_type != DT_DIR){
					printf("%s", "tuls: cannot open directory\n");
				} else {
					printf("[%s]\n", d->d_name);
					openAll(d->d_name, 1);
				}
                	} else {
				printf("%s\n", d->d_name);
			}
		}

	}
	return 0;
}

void openAll(char* name, int n){
	printf("%s", "Hello\n");
} 
