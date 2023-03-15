test: target/test
	./target/test

build: target/build/tensor.o

target/test: target/build/tests/test_tensor.o target/build/tests/main.o target/build/tensor.o
	cc $^ -o target/test

target/build/tests/main.o: tests/main.c
	cc -c $? -o $@ -pedantic -Wall -Wextra

target/build/tests/test_tensor.o: tests/test_tensor.c
	cc -c $? -o $@ -pedantic -Wall -Wextra

target/build/tensor.o: tensor.c
	cc -c $? -o $@ -pedantic -Wall -Wextra

init:
	mkdir -p ./target/build/tests

clean:
	rm -f ./target/build/*.o
	rm -f ./target/test
