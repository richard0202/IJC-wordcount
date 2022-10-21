CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
MODULES = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
DYNMODULES = htab_bucket_count-dyn.o htab_clear-dyn.o htab_erase-dyn.o htab_find-dyn.o htab_for_each-dyn.o htab_free-dyn.o htab_hash_function-dyn.o htab_init-dyn.o htab_lookup_add-dyn.o htab_resize-dyn.o htab_size-dyn.o

.PHONY: clean all zip

all: tail wordcount-dynamic

################## Tail ##################
tail: tail.o
	gcc tail.o -o tail

tail.o: tail.c
	gcc $(CFLAGS) -c tail.c -o tail.o

################## Překlad modulů ##################
htab_bucket_count.o: htab_bucket_count.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_clear.o: htab_clear.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_erase.o: htab_erase.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_find.o: htab_find.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_for_each.o: htab_for_each.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_free.o: htab_free.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_hash_function.o: htab_hash_function.c htab.h
	gcc $(CFLAGS) -c $< -o $@

htab_init.o: htab_init.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_lookup_add.o: htab_lookup_add.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_resize.o: htab_resize.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@

htab_size.o: htab_size.c htab.h htab_struct.h
	gcc $(CFLAGS) -c $< -o $@
################## END Překlad modulů ##################

################## Statické sestavení ##################
libhtab.a: $(MODULES)
	ar -crs libhtab.a $^
	ranlib libhtab.a

wordcount: wordcount.c libhtab.a io.c
	gcc -o wordcount -static wordcount.c -L. -lhtab

################## Překlad modulů s fPIC ##################
htab_bucket_count-dyn.o: htab_bucket_count.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_clear-dyn.o: htab_clear.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_erase-dyn.o: htab_erase.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_find-dyn.o: htab_find.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_for_each-dyn.o: htab_for_each.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_free-dyn.o: htab_free.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_hash_function-dyn.o: htab_hash_function.c htab.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_init-dyn.o: htab_init.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_lookup_add-dyn.o: htab_lookup_add.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_resize-dyn.o: htab_resize.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@

htab_size-dyn.o: htab_size.c htab.h htab_struct.h
	gcc $(CFLAGS) -c -fPIC $< -o $@
################## END Překlad modulů s fPIC ##################

################## Dynamické sestavení ##################
libhtab.so: $(DYNMODULES)
	gcc -shared -fPIC $(DYNMODULES) -o libhtab.so

wordcount-dynamic: wordcount.c libhtab.so htab.h htab_struct.h io.c
	gcc -o wordcount-dynamic wordcount.c -L. -lhtab


wordcount-: wordcount-.cc
	g++ -std=c++17 -pedantic -Wall wordcount-.cc -o wordcount-

clean:
	rm -f *.o tail libhtab.a wordcount wordcount-dynamic wordcount- libhtab.so

zip:
	zip xkocia19.zip *.c *.cc *.h Makefile
