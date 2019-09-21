/******************************
 *CO322 TRIE DS IMPLEMENTATION*
 *      AUTHOR - E/15/065     *
 ******************************/
 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>

#define SIZE 26 //size of the alphabet

int count=0; //for counting number of nodes

//structure for linking the string
typedef struct string{
	char letter;
	struct string *next;
}linkedString;

//function for creating linked string
linkedString* createString(char ltr){
    linkedString* temp = (linkedString*) malloc(sizeof(linkedString));
    temp-> letter = ltr;
    temp -> next = NULL;
    return temp;
}

//structure for a node
typedef struct radixNode{
	bool isEnd; //represent end of the word
  linkedString* lString;
  struct radixNode* childNode[SIZE];
}RadixNode;

//function for create a new node
RadixNode* createNode(){
    RadixNode* tempNode = (RadixNode*)malloc(sizeof(RadixNode)); // allocating dynamic memory
	//initializing elements in the node
	tempNode->isEnd = false;
    tempNode->lString = NULL;

    for (int i = 0 ; i < 26 ; i ++){
    	  tempNode->childNode[i] = NULL;
    }
    count ++;
    return tempNode;
}

//generate the position of the character
int getPosition(char character){
	int position;
	if(character>64 && character<91){
			position = 32 +(int)character - (int)'a';//if capital convert it into simple and generate index
	}else if(character>96 && character<123){
			position = (int)character - (int)'a';//generate index for sinple letters
	}
	return position;
}


//divide the string among previous and current node depend on the breakpoint
RadixNode* divideStr(linkedString* bPoint,RadixNode* prev,RadixNode* curr){
    linkedString* newStr = bPoint->next;
    bPoint->next = NULL;
	RadixNode* tempNode = createNode();
    int position1 = getPosition(newStr->letter),position2;

    tempNode->lString = curr->lString;
    curr->lString = newStr;
    tempNode->childNode[position1] = curr;
	position2 = getPosition(tempNode->lString->letter);
    prev->childNode[position2] = tempNode;

    return tempNode;
}

//append letters to a linkedstring
linkedString* AppendStr(int init,int end,char* str){
    linkedString* temp =NULL,*curr = createString(str[init]);
  	linkedString*new = curr;

    for(int i = init + 1 ; i < end ; i ++){
        temp = createString(str[i]);
        curr->next = temp;
        curr = curr->next;
    }
    return new;
}

//function to insert words in to radix tree
void insertWord(RadixNode* top,char* word){
    int position;
    RadixNode* curr = top,*new = NULL ,*prev = NULL;
    linkedString* currStr, *prevStr= NULL;
    currStr = curr->lString;

	//go through all the letters of the word
    for(int i = 0 ; i < strlen(word) ; i ++){
    	position = getPosition(word[i]);

    	if(currStr != NULL){
				if (currStr->letter == word[i]){
					prevStr = currStr;
					currStr = currStr->next;
				}else{
					curr = divideStr(prevStr,prev,curr);
					new = createNode();
					new->lString = AppendStr(i,strlen(word)-1,word);
					new->isEnd = true;
					curr->childNode[position] = new;
					break;
				}
    	}else{
				if(curr->childNode[position] == NULL){
					new = createNode();
					new->lString = AppendStr(i,strlen(word)-1,word);
					new->isEnd = true;
					curr->childNode[position] = new;
					break;
				}
				else{
					prev = curr;
					curr = curr->childNode[position];
					prevStr = curr->lString;
					currStr = curr->lString->next;
				}
    	}
    }
}

//function to search a word in the tree
RadixNode* searchWord(RadixNode* top,char* word){
    RadixNode* curr = top;
    linkedString* tempStr = curr->lString;
	int position, length = strlen(word);

    for(int i = 0 ; i < length; i ++)  {
    	position = getPosition(word[i]);

    	if(tempStr != NULL ){
			tempStr = tempStr->next;

    	}else {
			curr = curr->childNode[position];
		  	tempStr = curr->lString->next;
    	}

    }

   while(tempStr != NULL){
    	word[length] = tempStr->letter;
    	tempStr = tempStr->next;
    	length++;
    }
    word[length] = '\0';

    return curr;
}

////give set of words start with given word
void printSuggetions(RadixNode* top,char prefix[],int size){
    RadixNode* curr = top;
	linkedString *currStr=NULL,*tempStr;
    int newSize;
	char *str=prefix;

    if(curr->isEnd){
        for (int j = 0 ; j < size ; j ++){
            printf("%c",prefix[j]);
        }
        printf("\n");
    }

    for (int i=0;i<26;i++){
        if(curr->childNode[i]!=NULL){
				int newSize = size;
			    tempStr = curr->childNode[i]->lString;

			    while (tempStr != NULL){
			        str[newSize] = tempStr->letter;
			        newSize++;
			        tempStr = tempStr->next;
			    }
			    str[newSize] = '\0';
				printSuggetions(curr->childNode[i],prefix,newSize);
        }
    }
}

//main function
int main(int argc,char *argv[]){

    char str[100];
  	RadixNode* top = createNode();//create the root node
	clock_t start, time;
	double used_time;
	FILE *f; //poniter for reading the file
	int len;

	  //Check the existence of the file
	if((f=fopen(argv[1],"r"))==NULL){
	    printf("Cannot open the file...");
	    exit(1);
	 }

	  //read unitl meet the end of file and insertWord it into trie structure
	  start=clock();
	  while(!feof(f)){
	      fgets(str,100,f); //read the word
				char c[50];
				len = strlen(str);
				str[len-1]='\0';
				strcpy(c,str);
				insertWord(top,c);

	  }
	  time=clock()-start;

	  fclose(f);//close the opened file
	  
	  int oneNodeSize=sizeof(*top); //getting the single node size

	  printf("\nTime taken to store the list %f sec\n", ((double)time)/CLOCKS_PER_SEC);//display time taken to store
	  printf("no of nodes %d\n",count); //node count
	  printf("Size of a node %d\n ",oneNodeSize); //size of a one node size
	  printf("Memory need to store the list=%d Bytes\n",count*oneNodeSize); //used total memory

	  char s[50];
	  
    while(1){

			printf("\nEnter a prefix...\n");
			scanf("%s",s); //get user input
			printf("\n---------Suggestions----------\n");
			start = clock();
			RadixNode* suggestedNode = searchWord(top,s); //fnd the last node for the given prefix
			printSuggetions(suggestedNode,s,strlen(s)); //set of suggested words
			time = clock()-start;
			printf("\nTime taken to print a suggestions list %f sec\n",((double)time)/CLOCKS_PER_SEC); //display time taken to print suggestions list
			printf("------------------------------\n");
    }
    return 0;
}
