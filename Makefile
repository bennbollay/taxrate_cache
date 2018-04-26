test : test.cpp taxratelru.hpp
	g++ test.cpp -o test
	./test
	valgrind --leak-check=full ./test

test.cov : test.cpp taxratelru.hpp
	g++ test.cpp -o test.cov -fprofile-arcs -ftest-coverage --coverage
	lcov --base-directory . --directory . --zerocounters -q
	./test.cov
	lcov --base-directory . --directory . -c -o test.info
	lcov --remove test.info "/usr*" -o test.info # remove output for external libraries
	rm -rf test_coverage
	genhtml -o test_coverage -t "test coverage" --num-spaces 4 test.info

clean:
	rm -rf test.cov test test.gcda test.gcno test.info test_coverage


