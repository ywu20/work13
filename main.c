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

void split_str(char * split, char c, char ** arr){
  int i = 1;
  arr[0] = split;
  while ((split = strchr(split, c))!= NULL){
   * split = '\0';
   arr[i] = ++split;
   i++;
 }
}

void print_pop_entry(struct pop_entry * a){
  printf("year: %d, population: %d, boro: %s\n", a->year, a->population, a->boro);
}

void print_err(){
  if(errno != 0) printf("%s\n",strerror(errno));
}
// read data from csv file to another file
void read_csv(){
 char * lines[25];
 int fd = open ("pop.csv", O_RDONLY);
 char big_str[1000];

 read(fd, big_str, 1000);
close(fd);

 //printf("big_str: %s\n", big_str);
// split into lines
 char * split = big_str;

 split_str(split, '\n', lines);
int i = 0;
 /**test
 for(i=0;i<24;i++){
 char test [100];
 strcpy(test,lines[i]);
 printf("lines [%d]: %s\n ",i,test);
 }
*/
split = lines[0];
char * boro [6];
split_str(split,',',boro);

/*
for(i=0;i<6;i++){
char test [100];
strcpy(test,boro[i]);
printf("boro [%d]: %s\n ",i,test);
}
*/

//populate into struct array
struct pop_entry ** pop  = calloc(5*23+1, sizeof(struct pop_entry * ));

int pop_i = 0;
for(i=1;i<24;i++){
split = lines[i];
char * entry [6];
split_str(split, ',', entry);
int j;
for(j=1;j<6;j++){
pop[pop_i] = malloc(sizeof(struct pop_entry));
pop[pop_i]->year = atoi(entry[0]);
pop[pop_i] -> population = atoi(entry[j]);
strcpy(pop[pop_i] -> boro , boro[j]);
//print_pop_entry(pop[pop_i]);
pop_i++;
}
}
fd = open("struct_pop", O_CREAT | O_TRUNC |O_RDWR, 0644);

int a = write(fd, pop, 5*23 * sizeof(struct pop_entry));
/* test write
printf("bytes written: %d\n", a);

lseek(fd,0,SEEK_SET);
struct pop_entry ** test_pop=calloc(5*23+1, sizeof(struct pop_entry * ));
a = read(fd, test_pop, 5*23 * sizeof(struct pop_entry));
printf("bytes read: %d\n", a);
for(i = 0;i<5*23;i++){
  print_pop_entry(test_pop[i]);
}
*/
close(fd);
for(i=0;i< 5*23+1;i++){
  free(pop[i]);
}
free(pop);
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
