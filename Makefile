all: ind3xlite
ind3xlite: sqlite3.o main.c main.h
	/usr/bin/clang -o ind3xlite main.c sqlite3.o -lm
sqlite3.o: sqlite3.c sqlite3.h
	 /usr/bin/clang -o sqlite3.o -c -O3 -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_ENABLE_FTS5 sqlite3.c

