CC = icpc
CFLAGS = -std=c++17
COPTFLAGS = -O3 -g -qopenmp
LDFLAGS =

lab4: src/main.o src/fun.o src/list.o
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f lab4 core src/*.o *~ mergesort-omp

# eof
