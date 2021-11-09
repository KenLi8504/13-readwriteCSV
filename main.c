#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

struct pop_entry{
  int year;
  int pop;
  char boro[15];
};

void read_csv(char *fileName){
  printf("-read_csv\n");
  struct stat placeHolder;
  stat(fileName, &placeHolder);
  int size = placeHolder.st_size;
  printf("The size is %d\n",size);
  int goodFile = open(fileName,O_RDONLY);
  if (goodFile == -1){
    printf("Error Detected!\n");
    return;
  }
  else{
    char file[size];
    read(goodFile,file,size);
    int numLines = 0;
    for (int i = 0; i <= size;i++){
      if (file[i] == '\n'){
        numLines++;
      }
    }
    printf("There are %d lines\n",numLines);
    struct pop_entry entries[5*(numLines-1)];
    int index = 0;
    while(file[index]!= '\n'){
      index++;
    }
    index++;
    for (int i = 0; i < numLines; i++){
      while(file[index]!='\n'){
      index++;
      }
    index++;
    int year,man,brook,queens,bronx,staten;
    sscanf(file+i, "%d, %d, %d, %d, %d, %d\n", &year, &man, &brook, &queens, &bronx, &staten);
    for(int j = 0 ; j < 5; j++){
      entries[5*i + j].year = year;
      if (j == 0){
        strcpy(entries[5*i + j].boro, "Manhattan");
        entries[(5*i)+j].pop = man;
      }
      if (j == 1){
        strcpy(entries[(5*i)+j].boro, "Brooklyn");
        entries[(5*i)+j].pop = brook;
      }
      if (j == 2){
        strcpy(entries[(5*i)+j].boro, "Queens");
        entries[(5*i)+j].pop = queens;
      }
      if (j == 3){
        strcpy(entries[(5*i)+j].boro, "Bronx");
        entries[(5*i)+j].pop = bronx;
      }
      if (j == 4){
        strcpy(entries[(5*i)+j].boro, "Staten Island");
        entries[(5*i)+j].pop = staten;
      }
    }
    int output = open("newnyc_pop.csv", O_CREAT | O_WRONLY, 0644);
    if(output == -1){
        printf("Error!\n");
    }
    int status = write(output, entries, sizeof(entries));
    if(output == -1){
        printf("Error!\n");
    }
  }
  printf("Wrote %d bytes to nyc_pop.txt\n", size);
  printf("FINISHED READING CSV\n");
  }
}

void read_data(char *fileName){
  printf("-read_data\n");
  struct stat placeHolder;
  stat(fileName, &placeHolder);
  int size = placeHolder.st_size;
  printf("The size is %d\n",size);
  int goodFile = open(fileName,O_RDONLY);
  if (goodFile == -1){
    printf("Error Detected!\n");
    return;
  }
  struct pop_entry *entries = malloc(size);
  int err = read(goodFile, entries, size);
  if(err==-1){
    printf("Error Detected!");
    return;
  int totEntries = size / sizeof(struct pop_entry);
  for(int i=1;i<totEntries+1;i++){
    printf("%d:\t year: %d\t boro: %s\t pop: %d\n", i, entries[i].year, entries[i].boro, entries[i].pop);
  }
  free(entries);
}
printf("DONE\n");
}

void add_data(){
  printf("-add_data\n");
  struct pop_entry new;

  char input [50];
  printf("Enter year boro pop:");
  fgets(input,50,stdin);
  char tempboro[15];
  sscanf(input,"%d %s %d\n",&(new.year), tempboro, &(new.pop));
  strcpy(new.boro,tempboro);
  int file = open("nyc_pop.data", O_WRONLY | O_APPEND);
  if(file==-1){
      printf("Error!\n");
      return;
  }
  int err = write(file, &new, sizeof(new));
  if(err==-1){
      printf("Error:\n");
      return;
  }
}



int main (int argc, char ** argv){
  if (argc > 2){
    printf("TOO MANY ARGUMENTS! PLEASE INPUT ONLY ONE.\n");
  }
  else if (argc == 1){
    printf("NOT ENOUGH ARGUMENTS! PLEASE INPUT AT LEAST ONE.\n");
  }
  else{
    char function[20];
    strcpy(function,argv[1]);

    if (!strcmp(function,"-read_csv")){
      read_csv("nyc_pop.csv");
    }

    else if (!strcmp(function,"-read_data")){
      read_data("./newnyc_pop.csv");
    }

    else if (!strcmp(function,"-add_data")){
      add_data();
    }

    else if (!strcmp(function,"-update_data")){
      printf("-update_data\n");
    }

    else{
      printf("ERROR PLEASE INPUT A VALID ARGUMENT!\n");
    }
  }
  return 0;
}
