# libKongfig #

Gorilla configuration methods using 
	Symbolic links as keys and  Target as Value.

	get_kongfig(application,key);
	set_kongfig(application,key,value);

	Kept in $HOME/.kongfig or by environment variable KONGFIG
	kongfig -k name -v "Fred Flintstone"
	kongfig -k city -v "Bedrock"

Use File Utilities(ls,rm,find,...) to Manage configuration

## Example ##

```sh
kongfig -k name -v 'Fred Flintstone'
Fred Flintstone
kongfig -k wife -v 'Wilma'
Wilma
kongfig -k children -v 1
1
kongfig -n child1 -k name -v Pebbles
Pebbles
kongfig -k city -v Bedrock
Bedrock

$ cd ~/.kongfig && find . -ls | cut -c72-122
 .
 ./child1
 ./child1/name -> Pebbles
 ./wife -> Wilma
 ./name -> Fred\ Flintstone
 ./children -> 1
 ./city -> Bedrock
```

## ToDo ##

	* Rename kongfig kongfig test
	* Create kongfig as shell script
	* Inconsistencies between name(path) and names like name.first (depth)

## Enhancement Ideas ##

	* key.selection -> file containing allowed values
	* key.exec      -> script to execute on change.
	* use files to store Target for Binary or large Values

## More Ideas ##

	* create web page to edit config for process
  
## Files ##

| File                 | 🧿 | Description                                |
|----------------------|----|--------------------------------------------|
| k5f2.h               | 📑 | Libk5f2                                    |
| kongfig              | 🔩 | Shell Version                              |
| kongfigtest          | 🔨 | Test Program                               |
| kongfigtest.c        | 📄 | Test Program                               |
| libkongfig.c         | 📄 | Functions                                  |
| libkongfig.h         | 📑 | Definitions                                |
| makefile             | 🚂 | Instructions                               |
