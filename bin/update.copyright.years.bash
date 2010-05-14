#/bin/bash

# The following line takes a file with the formate <num><space><num><space><filename/path> and looks for years that need updating.
#for f in $(perl -lne '/^\d+\s+\d+\s+(.*)/ && print $1' files.2009); do perl -i.bkp -lpe 's/2008 /2008, 2009 /g unless /2009/' "$f"; done
# update to new fliename, yearset etc before using, hence commented out. list generated with git diff --numstat hash1 hash2

