#include <string>
#include <iostream>
#include <unordered_map>  
#include <glm/glm.hpp>    
#include <glm/gtc/matrix_transform.hpp> 
#include <stack>          
#include "plant.h"
#include <OpenGL/gl.h>
#include "osusphere.cpp"
#include "osucone.cpp"
#include "setmaterial.cpp"


class LSystem {
    Plant plant;
	State state;
	std::string word;
	GLuint SphereDL;

    glm::vec3 Xaxis = {1., 0., 0.};
    glm::vec3 Yaxis = {0., 1., 0.};
    glm::vec3 Zaxis = {0., 0., 1.};

    public:
    LSystem(Plant plant) : plant(plant), state(plant.initialState), word(plant.initialWord) {
		setSphereDL();
	}
    
	void setSphereDL() {
		SphereDL = glGenLists(1);
		glNewList(SphereDL, GL_COMPILE);
			OsuSphere(plant.sphereRadius, 20, 20);
		glEndList();
	}
	void resetWord() {
		word = plant.initialWord;
	}

    void generate(int numIter) {
	    if (numIter == 0 || numIter > plant.maxIter) return;

	    std::string newWord = "";
	    	for (int i = 0; i < word.length(); i++) {
	    		char c = word[i];
	    		if (plant.rules.count(c)) {
	    			newWord += plant.rules[c];
	    		} else {
	    			newWord += c;
	    		}
	    	}
		word = newWord;
		generate(numIter - 1);
    }; 


	int getMaxIter() {
		return plant.maxIter;
	}
    void drawLine() {
    	glm::vec3 endPoint = state.position + glm::normalize(state.dir) * state.len;

        glBegin(GL_LINES);
			glColor3f(0.8, 0.33, 0.10); // Line color
        	glVertex3f(state.position.x, state.position.y, state.position.z);  
        	glVertex3f(endPoint.x, endPoint.y, endPoint.z);  
        glEnd();

    	state.position = endPoint;
    
    }

    void rotate(float angle, glm::vec3 axis) {
    	glm::mat4 identity = glm::mat4(1.0f);
    	glm::mat4 rotationMatrix = glm::rotate(identity, glm::radians(angle), axis);

    	state.dir = glm::vec3(rotationMatrix * glm::vec4(state.dir, 0.0f));
    }

    
    // Draw the plant according to rules
    void draw(char rule) {
    	switch (rule) {
    		case 'F':
    			drawLine();
    			break;
    		case '-':
    			rotate(-plant.angle, Zaxis);
    			break;	
    		case '+':
    			rotate(+plant.angle, Zaxis);
    			break;
    		case '<':
    			rotate(+plant.angle, Yaxis);
    			break;
    		case '>':
    			rotate(-plant.angle, Yaxis);
    			break;
    		case '^':
    			rotate(plant.angle, Xaxis);
    			break;
    		case 'v':
    			rotate(-plant.angle, Xaxis);
    			break;
    		case '[':
    			plant.s.push(state);
    			break;
    		case ']':
				drawLeaf();
    			if (!plant.s.empty()) {
    				state = plant.s.top();
    				plant.s.pop();
    			}	
    			break;
    	}
    }

	void drawLeaf() {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		SetMaterial(plant.color.r, plant.color.g, plant.color.b, 10);
		glColor3f(plant.color.r, plant.color.g, plant.color.b);
		glPushMatrix();
			glTranslatef(state.position.x, state.position.y, state.position.z);
			glCallList(SphereDL);
		glPopMatrix();
		glDisable(GL_LIGHTING);
	}

    void drawPlant() {
    	for (int i = 0; i < word.length(); i++) {
    		char c = word[i];
    		draw(c);
    	};
		state = plant.initialState;
    }
};