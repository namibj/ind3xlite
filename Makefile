all: ind3xlite
ind3xlite: sqlite3.o main.c main.h sqlite3.h
	/usr/bin/clang -o ind3xlite -g -DSQLITE_MAX_LENGTH=1000000000 main.c sqlite3.o -lm
sqlite3.o: sqlite3.c sqlite3.h
	 /usr/bin/clang -o sqlite3.o -c -g -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_ENABLE_FTS5 -DSQLITE_MAX_LENGTH=1000000000 sqlite3.c

