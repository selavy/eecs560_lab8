CC = g++
CFLAGS = -std=c++11 -Wall -Werror
#NUMBER_OF_TESTS = -DNUM_OF_TRIALS=20
#COUNT = -DCOUNT=1000000
TEST = -D_TEST
DEBUG = -g
ECHO = @echo
ID = 2208496

lab8: main.cpp
	$(CC) $(CFLAGS) $(NUMBER_OF_TESTS) $(COUNT) -o lab8 main.cpp
lab8-test: main.cpp
	$(CC) $(CFLAGS) $(TEST) $(NUMBER_OF_TESTS) -o lab8-test main.cpp
.PHONY: test
test: lab8 lab8-test
	./lab8 > lab8.out
	./lab8-test > lab8_test.out
	$(ECHO) "\nInstructions:\n_____________________________________________________________________________________________\n"
	$(ECHO) "lab8.out contains 10 trials using the two different heapsort methods with 1000 elements"
	$(ECHO) "lab8_test.out contains a test sorting 25 elements and compares the output of the two methods\n"
	$(ECHO) "to view use:\n"
	$(ECHO) "\$$bash> cat lab8.out\n\$$bash> cat lab8_test.out\n"
.PHONY: clean
clean:
	rm -rf *.o lab8 lab8-test *.out

.PHONY: tar
tar:
	@mkdir $(ID)_lab8
	@cp main.cpp README.md Makefile $(ID)_lab8
	@tar -cvzf $(ID)_lab8.tar.gz $(ID)_lab8
	@rm -rf $(ID)_lab8