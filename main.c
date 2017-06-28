#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sqlite3.h"
#include "main.h"

#ifndef O_NOATIME
#define O_NOATIME 0
#endif

void check_schema(sqlite3 *);

sqlite3_stmt* stmt = NULL;
sqlite3* db = NULL;
sqlite3* open_db(char mode){
	sqlite3 *ret = NULL;
	sqlite3_open(DB_FILENAME, &ret);
	check_schema(ret);
	return ret;
}

void check_schema(sqlite3 *db){
	sqlite3_exec(db, SQL_SCHEMA_CHECK, NULL, NULL, NULL);
}

int add_callback(const char* fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	if(typeflag != FTW_F) return 0;
	int effective_filelength  = sb->st_size;
	if(effective_filelength > SQLITE_MAX_LENGTH - 1) effective_filelength = SQLITE_MAX_LENGTH - 1;
	int fd = open(fpath, O_RDONLY | O_NOATIME);
	char * file_content = (char *) mmap(NULL, effective_filelength, PROT_READ, MAP_SHARED, fd, 0);
	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, fpath, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, file_content, effective_filelength, SQLITE_STATIC);
	while(sqlite3_step(stmt) != SQLITE_DONE);
	munmap((void *) file_content, effective_filelength);
	close(fd);
	return 0;
}
void add(char *in) {
	db = open_db('\0');
	sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL);
	sqlite3_prepare(db, "INSERT INTO files (path, content) VALUES (?, ?);", -1, &stmt, NULL);
	nftw(in, &add_callback, 10, 0);// traverse folder, and use prepared statement to add all of the folder in one transaction. TODO: insert debug macro for immediate transactions.
	sqlite3_finalize(stmt);
	sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
}
void search(char *in) {
	db = open_db('\0');
	sqlite3_prepare(db, "SELECT '\n' || path || '\t' || snippet(files, 1, '\033[1m', '\033[0m', '\e[3m$\033[0m', 64) FROM files WHERE files MATCH ? ORDER BY rank;", -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, in, -1, SQLITE_STATIC);
	while(sqlite3_step(stmt) == SQLITE_ROW)
		printf("%s", sqlite3_column_text(stmt, 0));
	sqlite3_finalize(stmt);
	return;
}
int main(int argc, char* argv[]){
	int action = 0;
	if(argc != 3){
		printf(MSG_NO_ARGS);
		return -1;
	}else{
		if (!strcmp(argv[1], "add"))        action = 1;
		else if(!strcmp(argv[1], "a"))      action = 1;
		else if(!strcmp(argv[1], "search")) action = 2;
		else if(!strcmp(argv[1], "s"))      action = 2;
		else if(!strcmp(argv[1], "remove")) action = 2;
		else if(!strcmp(argv[1], "r"))      action = 2;
	switch(action){
		case 1:
			add(argv[2]);
			break;
		case 2:
			search(argv[2]);
			break;
		case 3:
			printf("Removing is not yet supported");
			break;
		default:
			printf(MSG_NO_ARGS);
			return -1;
	}
		return 0;
	}
}
