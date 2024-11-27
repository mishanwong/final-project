sample:		sample.cpp
		g++ -framework OpenGL -framework GLUT sample.cpp -o sample -I. -Wno-deprecated
clean:
		rm -rf *.o sample