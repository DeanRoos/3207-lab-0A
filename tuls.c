#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//prototype for recursive function
void openAll(const char* name, int n);
char *fileCombine(const char *a, char *b);

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

		//assigning the next entry in the directory as d
		while ((d = readdir(directory)) != 0){ //go through all of the entries
			printf("%s\n", d->d_name); //print name of each entry
		}
		closedir(directory);
		return 0;
	} 
	
	else { //1-arg call to nulls
		DIR *directory; //setting up directory
    struct dirent *d;
    directory = opendir("."); //opening current directory
		int check = 0; //check to make sure the file was found in the directory

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
					check = 1;
				}
      } 
			
			else { //if not a directory, it just prints
				printf("%s\n", d->d_name);
			}
		}

		closedir(directory); //closing directory

		if (check == 0){ //checking to see if entire function ran without finding a directory with the name of the argument
			printf("tuls: directory %s not found\n", argv[1]);
			return 1;
		}
	}	
	return 0; //exiting the program with no errors
}


//recursive function - takes in name of directory and int n which keeps track of how many
//spaces to put in front of each line when printing out
void openAll(const char* name, int n){

	DIR *directory; //setting up directory and entries as before
	struct dirent *d;
	directory = opendir(name);

	if (directory == NULL){ //error handling
		printf("%s", "tuls: cannot open directory\n");
		return;
	} 

	while ((d = readdir(directory)) != 0){

		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0){
			//Don't print out the . and .. each time
		} 
		
		//if it gets to a directory
		else if (d->d_type == DT_DIR){
			printf("%*c", 2*n, ' '); //print spaces 
      printf("[%s]\n", d->d_name); //print the name
			
			//now creating a new string that contains the path of the new folder
			//did this through a function with malloc because an array was giving me issues
			char* newName = fileCombine(name, d->d_name); 
			openAll(newName, n+1); //calling function recursively on new name
			free(newName); //freeing the memeory
      } 
			
		else { //if it's just a file, print with correct spaces
			printf("%*c", 2*n, ' ');
      printf("->%s\n", d->d_name);
    }
	}
	closedir(directory); //closing directory
	return;
}

//made a program to dynamically allocate the memory for the new path name
//because doing it with an array gave me issues
char *fileCombine(const char *a, char *b) {
	char *ret = malloc(strlen(a) + strlen(b) + 2);
	int x = 0;
	int y = 0;

	for (x = 0; (ret[y] = a[x]) != '\0'; ++x, ++y);//copying first string to array
	ret[y] = '/'; //adding a /
	y++;
	for (x = 0; (ret[y] = b[x]) != '\0'; ++x, ++y); //copying second string to array
	return ret; //returning
}
