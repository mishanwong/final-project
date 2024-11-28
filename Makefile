sample:		sample.cpp
		g++ -std=c++11 -framework OpenGL -framework GLUT sample.cpp -o sample -I. -Wno-deprecated
clean:
		rm -rf *.o sample