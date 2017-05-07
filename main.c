#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include <sys/mmap.h>
#include "sqlite3.h"
#include "main.h"

/*//Scratchpads
char* spad1 = malloc(sizeof(char)* 1<<20);
char* spad2 = malloc(sizeof(char)* 1<<20);*/
sqlite3_stmt* stmt = NULL;
sqlite3* db = NULL;
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
	int effective_filelength  = sb->st_size;
	if(effective_filelength > SQLITE_MAX_LENGTH - 1) effective_filelength = SQLITE_MAX_LENGTH - 1;
	int fd = open(fpath, O_RDONLY | O_NOATIME);
	char * file_content = (char *) mmap(NULL, effective_filelength, PROT_READ, 0, fd, 0);
	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, fpath, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, file_content, effective_filelength, SQLITE_STATIC);
	while(sqlite3_step(stmt) != SQLITE_DONE);
	munmap((void *) file_content, effective_filelength);
	close(fd);
}
void add(char *in) {
	db = open_db('');
	sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL);
	sqlite3_prepare(db, "INSERT INTO files (path, content) VALUES (?, ?);", -1, &stmt, NULL)z;
	nftw(in, &add_callback, 10, 0);// traverse folder, and use prepared statement to add all of the folder in one transaction. TODO: insert debug macro for immediate transactions.
	sqlite3_finalize(stmt);
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
