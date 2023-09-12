#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[] ){

	if (argc > 2){
		printf("%s", "Incorrect arguments. Exiting program.");
		exit(1);
	} else if (argc == 1){
		DIR *dp;
		struct dirent *d;
		dp = opendir(".");
		while ((d = readdir(dp)) != 0){
		printf("%s\n", d->d_name);
		}
	} else {


		printf("%s", "2 arguments");



	}
	return 0;
}
 
