all: main

main:	main.cpp
	g++ -lopencv_core -lopencv_highgui -lopencv_contrib main.cpp -o main

clean:
	rm -f main
