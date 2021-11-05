#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>

// struct for data
struct pop_entry {
  int year;
  int population;
  char boro[15];
};

// read data from csv file to another file
void read_csv(){
 char * lines[24];
 int fd = open ("pop.csv", O_RDONLY);
 char big_str[1000];
 
 read(fd, big_str, 1000);
 
 printf("big_str: %s\n", big_str);
 
 char * split;
 int i = 0;
 
 while ((split = strchr(big_str, '\n'))!= NULL){
 	split = NULL;
 	lines[i] = ++split;
 	i++;
 }
 
 /**test*/
 for(i=0;i<24;i++){
 char * test = lines[i];
 printf("lines [%d]: ",i);
 
 while(test!= NULL){
 //printf("%c", *test);
 test++;
 }
 
 printf("\n");
 }

}

// read data from csv, display it in the terminal
void read_data(){
}

// add data to the data file with appending
void add_data(){

}


// update a entry in data, prints data in terminal and 
// ask user to choose an entry they want to update

void update_data(){

}
int main(int argc, char * argv[]){
read_csv();
 return 0;
}
