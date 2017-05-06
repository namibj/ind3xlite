#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include "sqlite3.h"
#include "main.h"

/*//Scratchpads
char* spad1 = malloc(sizeof(char)* 1<<20);
char* spad2 = malloc(sizeof(char)* 1<<20);*/
sqlite3* open_db(char mode){
	/*FILE* db = malloc(sizeof(FILE));
	bool root = false;
	int i = 0;
	do{
		memcpy(&(spad1[i]
		db = fopen(
		spad1[i++] = '.';
		spad1[i++] = '.';
		spad1[i++] = '/';
		spad1[i] = '\0';
		realpath(spad1, spad2);
		if(spad2[1] == '\0') root = true;
	*/
	sqlite3 *ret = NULL;
	sqlite3_open(DB_FILENAME, &ret);
	return ret;
}

void check_schma(sqlite3 *db){
	sqlite3_exec(db, SQL_SCHEMA_CHECK, NULL, NULL, NULL);
}

int add_callback(comst char* fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	;
}
void add(char *in) {
	sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL);
	nftw(in, &add_callback, 10, 0);// traverse folder, and use prepared statement to add all of the folder in one transaction. TODO: insert debug macro for immediate transactions.
	sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
}
 
int main(int argc, char* argv[]){
	if(argc != 3){
		printf(MSG_NO_ARGS);
		return -1;
	}else{
		if (!strcmp(argv[1], "add")) 
			add(argv[2]);
		else if(!strcmp(argv[1], "a"))
			add(argv[2]); 
		else printf("1st argument is\"%s\"", argv[1]);
		printf("Hi! %i\n", argc);
		return 0;
	}
}
