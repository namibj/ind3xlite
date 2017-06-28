# ind3xlite
Sqlite3-based commandline fulltext indexer/searcher

## Usage
### Add
`ind3xlite a PATH [PATH]...`

Add the specified `PATH`'s to the index, creating it if not existing.

### Search
`ind3xlite s QUERY [QUERY]...`

Search the index with the specified [FTS5 query](https://www.sqlite.org/fts5.html#full_text_query_syntax), with the column `path` containing the filepath and the column `content` the file itself.

### Remove
`ind3xlite r PATH [PATH]...`

Remove the specified `PATH`'s from the index.

### Treatment of `PATH`'s
If `PATH` specifies a file, it will be operated on normally, if `PATH` is a directory, it will be traversed recursively and all containing files will be operated on. 
