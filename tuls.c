#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (){

	DIR *dp;
	struct dirent *d;
	dp = opendir(".");
	while ((d = readdir(dp)) != 0){
		printf("%s\n", d->d_name);
	}
	return 0;
}
 
