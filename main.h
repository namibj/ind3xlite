#define MSG_NO_ARGS "Use at least 2 arguments, the first being a command (a[dd], s[earch], r[emove]), with add and remove treating the following armuments as paths and either adding or removing them from the index, recursively so for directories (performance is higher using built-in recursion), and the search command using the followig arguments to search with the FTS5 syntax from sqlite (and treating each argument as a seperate query), see documentation at https://www.sqlite.org/fts5.html#full_text_query_syntax\n"
#ifndef DB_FILENAME
#define DB_FILENAME ".ind3xlite.sqlite3"
#endif
#define SQL_SCHEMA_CHECK "CREATE VIRTUAL TABLE IF NOT EXISTS files USING fts5(path, content, prefix='3 5 7');"

