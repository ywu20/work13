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
 int fd = open ("pop.csv", O_RDONLY);
 

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
	 
 return 0;
}
