CXX=g++
CXXFLAGS=-std=c++11 -lcurl

all: chat

chat: main.o FirebaseAuth.o FirestoreService.o
	$(CXX) -o chat main.o FirebaseAuth.o FirestoreService.o $(CXXFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CXXFLAGS)

FirebaseAuth.o: FirebaseAuth.cpp
	$(CXX) -c FirebaseAuth.cpp $(CXXFLAGS)

FirestoreService.o: FirestoreService.cpp
	$(CXX) -c FirestoreService.cpp $(CXXFLAGS)

clean:
	rm -f *.o chat
