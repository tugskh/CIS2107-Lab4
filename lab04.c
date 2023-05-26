#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

char* make_rand_key(int, char*);
void encrypt(char*, char*, char *);
void decrypt(char*, char*, char*);

int main(){
	
	int input = 0;
	
	while(input != 3){
		printf("Choose a number to execute the program.\n");
		printf("Encrypt a file: 1\nDecrypt a file: 2\nExit: 3\nEnter a choice: ");
		scanf("%d", &input);
		if(input == 1){
			char file_name[50];
			printf("\nEnter the name of the file to be encrypted: ");
			scanf("%s", file_name);
			encrypt(file_name,"key_file.txt","cipher_file.txt");
			printf("\nThe file has been encrypted.\n\n");
			printf("//------------------------------//\n\n");
		}
		if(input == 2){
			char key_file[50];
			char cipher_file[50];
			printf("\nEnter the name of the key file: ");
			scanf("%s", key_file);
			printf("\nEnter the name of the cipher file: ");
			scanf("%s", cipher_file);
			decrypt(key_file,cipher_file,"message_file.txt");
			printf("\nThe file has been decrypted.\n\n");
			printf("//------------------------------//\n\n");
		}
	}
	//printf("//------------------------------//\n\n");
	//decrypt("key_file.txt","cipher_file.txt","message_file.txt");
	
	
	
	

}


char * make_rand_key(int len, char* key){
	int i;
	srand(time(NULL));
	
	for(i = 0; i < len; i++){
		char c = rand()%255+1;
		//printf("%c\n", n);
		key[i] = c;
	}
	return key;
	
}

void encrypt(char* clear_file, char* key_file, char* cipher_file){
	
	FILE *fid1 = fopen(clear_file, "r");
	FILE *fid2 = fopen(key_file, "w");
	FILE *fid3 = fopen(cipher_file, "w");
	
	
	if(fid1 == NULL | fid2 == NULL | fid3 == NULL){
		printf("File cannot be opened\n");
		exit(0);
	}
	
	int len = 0;
	
	while(getc(fid1) != EOF) // calculates the length
		len++;
	//printf("len = %d\n", len);
	
	char read_array[len+1]; 
	
	rewind(fid1);
	
	int i;
	for(i = 0; i< len; i++)
		read_array[i] = getc(fid1);
		
	read_array[i] = '\0';
	
	//printf("%s", read_array);
	
	fclose(fid1);
	
	char key_array[len];
	
	make_rand_key(len, key_array); // generating random key
	
	//printf("%s\n", key_array);
	
	for(i = 0; i < len; i++){
		putc(key_array[i], fid2); // writes key file
		putc(read_array[i]+key_array[i], fid3); // writes cipher file
	}
	fclose(fid2);
	fclose(fid3);
}

void decrypt(char* key_file, char* cipher_file, char* message_file){

	FILE *fid1 = fopen(key_file, "r");
	FILE *fid2 = fopen(cipher_file, "r");
	FILE *fid3 = fopen(message_file, "w");
	
	
	if(fid1 == NULL | fid2 == NULL | fid3 == NULL){
		printf("File cannot be opened\n");
		exit(0);
	}
	
	int len = 0;
	
	while(getc(fid1) != EOF)
		len++;
	//printf("len = %d\n", len);
	
	char read_key[len+1]; //Dynamic array
	char read_cipher[len+1];
	
	rewind(fid1);
	
	int i;
	for(i = 0; i< len; i++){
		read_key[i] = getc(fid1);
		read_cipher[i] = getc(fid2);
	}
		
	read_key[i] = '\0';
	read_cipher[i] = '\0';
	
	//printf("%s\n", read_key);
	//printf("%s\n", read_cipher);
	
	fclose(fid1);
	fclose(fid2);
	
	for(i=0; i < len; i++)
		putc(read_cipher[i] - read_key[i], fid3);
		
	fclose(fid3);
	

}

void read_file(char* file_name){

	FILE *fid = fopen(file_name, "r");
	
	if(fid == NULL){
		printf("File cannot be opened\n");
		exit(0);
	}
	
	int len = 0;
	
	while(getc(fid) != EOF)
		len++;
	printf("len = %d\n", len);
	
	char read_array[len+1];
	
	rewind(fid);
	
	int i;
	for(i = 0; i< len; i++)
		read_array[i] = getc(fid);
		
	read_array[i] = '\0';
	
	printf("%s", read_array);
	
	fclose(fid);

}

void write_file(char* str, char* file_name){

	FILE *fid = fopen(file_name, "w");
	
	if (fid == NULL){
		printf("The write file cannot be opened\n");
		exit(0);
	}
	int i;
	for(i=0; i<strlen(str); i++)
		putc(str[i], fid);
	fclose(fid);

}




