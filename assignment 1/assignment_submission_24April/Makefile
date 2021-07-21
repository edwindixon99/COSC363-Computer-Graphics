CXX = g++
CXXFLAGS = -Wall -g

cannon.o: cannon.cpp cannon.h
	$(CXX) $(CXXFLAGS) -c $< 

armyMen.o: armyMen.cpp armyMen.h
	$(CXX) $(CXXFLAGS) -c $< 

models.o: models.cpp models.h
	$(CXX) $(CXXFLAGS) -c $< 
	
muesuem.o: muesuem.cpp cannon.h armyMen.h models.h
	$(CXX) $(CXXFLAGS) -c $< 
	
	
muesuem: muesuem.o armyMen.o cannon.o models.o
	$(CXX) $(CXXFLAGS) $^ -o muesuem -lm -lGL -lGLU -lglut
	
clean:
	rm *.o 
	rm muesuem

run: muesuem
	./muesuem
