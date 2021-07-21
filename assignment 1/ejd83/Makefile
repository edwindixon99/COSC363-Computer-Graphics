CXX = g++
CXXFLAGS = -Wall -g

cannon.o: cannon.cpp cannon.h
	$(CXX) $(CXXFLAGS) -c $< 

armyMen.o: armyMen.cpp armyMen.h
	$(CXX) $(CXXFLAGS) -c $< 

models.o: models.cpp models.h
	$(CXX) $(CXXFLAGS) -c $< 
	
musuem.o: musuem.cpp cannon.h armyMen.h models.h
	$(CXX) $(CXXFLAGS) -c $< 
	
	
musuem: musuem.o armyMen.o cannon.o models.o
	$(CXX) $(CXXFLAGS) $^ -o musuem -lm -lGL -lGLU -lglut
	
clean:
	rm *.o 
	rm musuem

run: musuem
	./musuem
