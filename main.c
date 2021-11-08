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

struct pop_entry ** init_struct(){
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

 return pop;
}

void free_struct(struct pop_entry ** pop){
  int i;
  for(i=0;i< 5*23+1;i++){
    free(pop[i]);
  }
  free(pop);
}
// read data from csv file to another file
void read_csv(){
 //struct pop_entry pop[5*23+1]= init_struct();
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
struct pop_entry pop[5*23+1];

int pop_i = 0;
for(i=1;i<24;i++){
split = lines[i];
char * entry [6];
split_str(split, ',', entry);
int j;
for(j=1;j<6;j++){
//pop[pop_i] = malloc(sizeof(struct pop_entry));
pop[pop_i].year = atoi(entry[0]);
pop[pop_i].population = atoi(entry[j]);
strcpy(pop[pop_i].boro , boro[j]);
print_pop_entry(&pop[pop_i]);
pop_i++;
}
}

fd = open("struct_pop", O_CREAT | O_TRUNC |O_RDWR, 0644);

int a = write(fd, pop, sizeof(pop));
//* test write
printf("wrote %d bytes to struct_pop\n", a);
close(fd);
/*
print_err();
fd = open("struct_pop", O_RDONLY);
printf("%d\n",fd);
print_err();

//lseek(fd,0,SEEK_SET);
struct pop_entry ** test_pop=calloc(5*23+1, sizeof(struct pop_entry * ));
print_err();
a = read(fd, test_pop, 5*23 * sizeof(struct pop_entry));
print_err();
printf("bytes read: %d\n", a);
for(i = 0;i<5*23;i++){
  print_pop_entry(test_pop[i]);
}

close(fd);
*/
//free_struct(pop);
}

// read data from csv, display it in the terminal
void read_data(){
struct stat file;
stat("struct_pop",&file);
int fd = open("struct_pop", O_RDONLY);
//struct pop_entry pop[file.st_size/sizeof(struct pop_entry)];
struct pop_entry *pop = calloc (1, sizeof(struct pop_entry)+file.st_size);
print_err();
int a = read(fd, pop, file.st_size);
print_err();
printf("bytes read: %d\n", a);
int i;
for(i = 0;i<file.st_size/sizeof(struct pop_entry)-1;i++){
  printf("%d: ",i);
  print_pop_entry(&pop[i]);
}
free(pop);
}

// add data to the data file with appending
void add_data(){
  printf("Enter year boro pop:\n");
  char data[100];
  fgets(data, sizeof(data),stdin);
  printf("data: %s\n", data);
  char *data_arr[3];
  split_str(data,' ',data_arr);
  int fd = open("struct_pop", O_WRONLY|O_APPEND);

  struct pop_entry appnd;

  char yr [16];
  strcpy(yr, data_arr[0]);
  //printf("year: %s\n", yr);
  char boro[15];
  strcpy(appnd.boro, data_arr[1]);
  //printf("boro: %s\n", boro);
  char pop[16];
  strcpy(pop, data_arr[2]);
//  printf("pop: %s\n", pop);

appnd.year =  atoi(yr);

appnd.population = atoi(pop);
//print_pop_entry(&appnd);
  int a = write(fd, &appnd,sizeof(appnd));
  printf("bytes written: %d\n", a);
  print_err();

  close(fd);

}


// update a entry in data, prints data in terminal and
// ask user to choose an entry they want to update

void update_data(){
  read_data();
  struct pop_entry pop [1000];
  int fd = open("struct_pop", O_RDWR);
  struct stat file;
  stat("struct_pop",&file);
  int a = read(fd, pop, file.st_size);
  printf("bytes read: %d",a);

  printf("Entry to update: \n");
  char entry[5];
  fgets(entry, 4, stdin);
}
int main(int argc, char * argv[]){
read_csv();
read_data();
//add_data();
update_data();
//read_data();
 return 0;
}
