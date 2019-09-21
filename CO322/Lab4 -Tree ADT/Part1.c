/******************************
 *CO322 TRIE DS IMPLEMENTATION*
 *      AUTHOR - E/15/065     *
 ******************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 26 //maximum childNodes -alphabet size
int count=0;//for counting nodes

// trie node basic stucture
typedef struct trieNode{
	struct trieNode *childNode[SIZE];
	bool isEnd;
}TrieNode;

TrieNode *tempNode;

//initialzing and createNewNode
TrieNode *createNode(){
	TrieNode *temp = NULL;
	temp = (TrieNode *)malloc(sizeof(TrieNode));

	int i;
	temp->isEnd = false;
	for (i = 0; i < SIZE; i++){
    		temp->childNode[i] = NULL;
  }
	count++;
	return temp;
}

//inserting a word into TrieNode
void insertWord(TrieNode *top, const char *word){
	int i;
	int length = strlen(word);
	int position;

	TrieNode *temp = top;

	for (i = 0; i < length; i++){
    //check for capital letters,simple letters and other characters
		if(word[i]>64 && word[i]<91){
			position = 32 +(int)word[i] - (int)'a'; //if capital convert it into simple and generate index
		}else if(word[i]>96 && word[i]<123){
			position = (int)word[i] - (int)'a'; //generate index for simple letters
		}else{
			//top->symbol=word[i];
			//top=top;
			continue;
		}

    //represent the letter
		if (!temp->childNode[position])
			temp->childNode[position] = createNode();

		temp = temp->childNode[position];
	}
	temp->isEnd = true; // end of the word
}

//searching a word in trie
bool searchWord(TrieNode *top, const char *word){
	int i;
	int length = strlen(word);//get the word length
	int position;
  tempNode = NULL;
	tempNode = top;


	for (i = 0; i < length; i++){
    //check for capital letters,simple letters and other characters
    if(word[i]>64 && word[i]<91){
  			position = 32 +(int)word[i] - (int)'a';//if capital convert it into simple and generate index
  		}else if(word[i]>96 && word[i]<123){
  			position = (int)word[i] - (int)'a';//generate index
  		}else{
  			continue;
  		}

		if (!tempNode->childNode[position]){
      tempNode = NULL;
      return false; //word does not exists return false
    }

		tempNode = tempNode->childNode[position];
	}

	return (tempNode != NULL && tempNode->isEnd);//return true or false depend on index exists or not
}

//read the file
double fileRead_insert(char *fileName,TrieNode *top){
  clock_t start, time;
  double used_time;


  FILE *f; //poniter for reading the file
  char str[100];
  int len;

  //Check the existence of the file
  if((f=fopen(fileName,"r"))==NULL){
    printf("Cannot open the file...");
    exit(1);
  }

  //read unitl meet the end of file and insertWord it into trie structure
  start=clock();
  while(!feof(f)){
      fgets(str,100,f);
      len = strlen(str);
      char c[50];
      //str[len-2]='\0';
      insertWord(top, str);
      // /printf("%s\n",str);
  }
  time=clock()-start;

  fclose(f);//close the opened file
  int oneNodeSize=sizeof(*top); //getting the single node size

  printf("no of nodes %d\n",count); //node count
  printf("Size of a node %d\n",oneNodeSize); //size of a one node size
  printf("Memory need to store the list=%d Bytes\n",count*oneNodeSize); //used total memory


  return ((double)time)/CLOCKS_PER_SEC;
}

//give set of words start with given word
void printSuggestions(TrieNode *top, char str[],int size){
	 int i=0;
	 if (top->isEnd) { //print the word when meet the end
     for(i=0;i<size;i++){
            printf("%c",str[i]);
      }
        printf("\n");
    }

    for(i=0;i<26;i++){
        if(top->childNode[i]!=NULL) {
           str[size] = i+97; //assigning next letter to word to the next position
           printSuggestions(top->childNode[i],str,size+1);
        }
    }
}


//main function
int main(int argc, char *argv[]){
  TrieNode *top = createNode();
  clock_t start, time;
  //give an example to execute
  if(argc==1){
    printf("use syntax like this..\n./<excutable_file> <filename.txt>\n");
    exit(1);
  }
  double timeTaken=fileRead_insert(argv[1],top);//read the file

  printf("\nTime taken to store the list %f sec\n",timeTaken);//display time taken to store

  bool check;

  while(1){
	printf("\nEnter a prefix...\n");
    char str[100];
	scanf("%s",str); //get user input

    printf("\n---------Suggestions----------\n");
    start = clock();

	check = searchWord(top,str);//execute to detect the end node of prefix
	if(check==false && tempNode==NULL){ //check whether prefix does not exists or not
			printf("No word found\n");
	}else{
		  printSuggestions(tempNode,str,strlen(str)); //find word suggestions and print
		  time = clock()-start;
    	  printf("\nTime taken to print a suggestions list %f sec\n",((double)time)/CLOCKS_PER_SEC); //display time taken to print suggestions list
	}
		printf("------------------------------\n");

	}
	return 0;
}
