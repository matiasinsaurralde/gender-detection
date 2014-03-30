all: main	twitter_gender

main:	main.cpp
	g++ -lopencv_core -lopencv_highgui -lopencv_contrib main.cpp -o main

twitter_gender:	twitter_gender.cpp
	g++ -lopencv_core -lopencv_highgui -lopencv_contrib -lcurl twitter_gender.cpp -o twitter_gender

clean:
	rm -f main
