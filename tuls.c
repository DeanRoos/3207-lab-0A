#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//prototypw for recursive function
void openAll(const char* name, int n);

//main
int main (int argc, char *argv[] ){

	if (argc > 2){ //dealing with too many arguments
		printf("%s", "tuls: incorrect arguments. Exiting program.\n");
		return 1;
	} 
	
	else if (argc == 1){ //no-args call to tuls

		DIR *directory; //initializing directory
		struct dirent *d; //initializing directory entry
		directory = opendir("."); //opening current directory

		if (directory == NULL){ //error checking
			closedir(directory);
			printf("%s", "tuls: cannot open directory\n");
			return 1;
		}


		d = readdir(directory); //assigning the next entry in the directory as d
		while (d != NULL){ //go through all of the entries
			printf("%s\n", d->d_name); //print the
			d = readdir(directory);
		}
		closedir(directory);
		return 0;
	} 
	
	else { //1-arg call to nulls
		DIR *directory; //setting up directory
    struct dirent *d;
    directory = opendir(".");

    if (directory == NULL){ //error checking
    	closedir(directory);
			printf("%s", "tuls: cannot open directory\n");
      return 1;
		}

		while ((d = readdir(directory)) != 0){ //going through each entry

			if (strcmp(d->d_name, argv[1]) == 0){ //checking to see if entry matches argument

				//this if statement checks that IF the argument matches the name of a file, that it is a directory and not just another file
				if (d->d_type != DT_DIR){ 
					printf("%s", "tuls: cannot open directory\n");
					closedir(directory);
					return 1;
				} 
				
				else { //if the argument matches a directory, calls recursive function
					printf("[%s]\n", d->d_name);
					openAll(d->d_name, 1);
				}
      } 
			
			else { //if not a directory, it just prints
				printf("%s\n", d->d_name);
			}
		}

		closedir(directory); //closing directory
	}

	return 0;
}


//recursive function - takes in name of directory and int n which keeps track of how many
//spaces to put in front of each line when printing out
void openAll(const char* name, int n){

	DIR *directory;
	struct dirent *d;
	directory = opendir(name);

	if (directory == NULL){
		printf("%s", "tuls: cannot open directory\n");
		return;
	} 

	while ((d = readdir(directory)) != 0){

		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".DS_Store") == 0){

		} 
		
		else if (d->d_type == DT_DIR){
			printf("%*c", 2*n, ' ');
      printf("[%s]\n", d->d_name);
			char newName[50];
			strcat(newName, name);
			strcat(newName, "/");
			strcat(newName, d->d_name);
			openAll(newName, n+1);
      } 
			
		else {
			printf("%*c", 2*n, ' ');
      printf("%s\n", d->d_name);
    }
	}
	closedir(directory);
	return;
} 
