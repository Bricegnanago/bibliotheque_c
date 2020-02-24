version : connection.c biblio.h
	gcc connection.c function.c -o version `mysql_config --cflags --libs`
