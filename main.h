#define MSG_NO_ARGS "Use exactly 2 arguments, the first being a command (a[dd], s[earch], r[emove]), whith the first and last taking a path and either adding oir removing it from the index, recursivekly so for directories, and the search command using the second argument to search with the FTS5 syntax from sqlite, see documentation at https://www.sqlite.org/fts5.html#full_text_query_syntax\n"
#ifndef DB_FILENAME
#define DB_FILENAME ".ind3xlite.sqlite3"
#endif
#define SQL_SCHEMA_CHECK "CREATE VIRTUAL TABLE IF NOT EXISTS files USING fts5(path, content, prefix='3 5 7');"

