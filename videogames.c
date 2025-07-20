#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define NAME_LEN 100 //max length of each string
#define NUM_GAMES 1000 //max number of games that can be processed

struct game { //structure of the video games
	char title[NAME_LEN+1];
	char genre[NAME_LEN+1];
	int review_score;
	double used_price;
	char console[NAME_LEN+1];
	char rating[NAME_LEN+1];
};

int compare_games(const void*a, const void *b);
int read_line(char str[], int n); //function to read input from the user just in case it includes white spaces
int search(struct game collection[], int n, struct game result[], char *search_console); //function to search for the games in the collection array and capy them into the result array when they have the same console

int main(){

	char title[NAME_LEN+1];
        char genre[NAME_LEN+1];
        int review_score;
        double used_price;
        char console[NAME_LEN+1];
        char rating[NAME_LEN+1];

	int num_games=0;
	char title_in[NAME_LEN+1]; //name of the file that the user is going to input
	struct game collection[NUM_GAMES+1]; //array with game structures
	printf("Enter file name: ");
	read_line(title_in, NAME_LEN+1);

	FILE *in_file=fopen(title_in, "r"); //open users file input in mode read
	if (in_file == NULL) { //if no file is found create a message error
        	printf("Error opening file");
	        return 1;
	}
	
	for(int i=0;i<NUM_GAMES;i++){
		if(fscanf(in_file, "%[^,], %[^,], %d, %lf, %[^,], %[^\n]\n", title, genre, &review_score, &used_price, console, rating)==6){ //read line by line assigning each part of the line to the different components of the structure
			strcpy(collection[i].title, title);
			strcpy(collection[i].genre, genre);
			collection[i].review_score=review_score;
			collection[i].used_price=used_price;
			strcpy(collection[i].console, console);
			strcpy(collection[i].rating, rating);
			num_games++; //increment each time the variable that reads the number of games
		} 
	}
	fclose(in_file); //close file
        qsort(collection, num_games, sizeof(struct game), compare_games); //sort the collection by review score in descending order

	FILE *out_file=fopen("result.csv", "w"); // create and open the file that will have the contents of the array with the games that match consoles, in mode write
	for (int i=0;i<num_games;i++){
		fprintf(out_file, "%s,%s,%d,%.2lf,%s, %s\n", collection[i].title, collection[i].genre, collection[i].review_score, collection[i].used_price, collection[i].console, collection[i].rating); //printf in the file the contents of the array with the games structures
	}

	fclose(out_file); //close output file

return 0;
}

int compare_games(const void*a, const void *b){ //compare function to use for qsort
	const struct game *game_a=a; //make the generic pointers point to structures
	const struct game *game_b=b;
	if (game_a->review_score > game_b->review_score) //sort in descending order
		return -1;
	else if (game_a->review_score == game_b->review_score)
		return 0;
	else 
		return 1;
}

int read_line(char str[], int n){ //function to read the input from the user in case it is more than one word
	int ch, i = 0;
	while (isspace(ch = getchar()))
		;
	str[i++] = ch;
	while ((ch = getchar()) != '\n') {
		if (i < n)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}
