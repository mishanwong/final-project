#include <string>
#include <iostream>
#include <unordered_map>  
#include <glm/glm.hpp>    
#include <glm/gtc/matrix_transform.hpp> 
#include <stack>          
#include "plant.h"
#include <OpenGL/gl.h>


class LSystem {
    Plant plant;
	State state;
    glm::vec3 Xaxis = {1., 0., 0.};
    glm::vec3 Yaxis = {0., 1., 0.};
    glm::vec3 Zaxis = {0., 0., 1.};

    public:
    LSystem(Plant plant) : plant(plant), state(plant.initialState) {}
    
    std::string generate() {
	    if (plant.numIter == 0) return plant.word;

	    std::string newWord = "";
	    	for (int i = 0; i < plant.word.length(); i++) {
	    		char c = plant.word[i];
	    		if (plant.rules.count(c)) {
	    			newWord += plant.rules[c];
	    		} else {
	    			newWord += c;
	    		}
	    	}
        plant.numIter -= 1;
		plant.word = newWord;
	    return generate();
    }; 


	std::string getWord() {
		return plant.word;
	}
    void drawLine() {
    	glm::vec3 endPoint = state.position + glm::normalize(state.dir) * state.len;

        glBegin(GL_LINES);
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
    			if (!plant.s.empty()) {
    				state = plant.s.top();
    				plant.s.pop();
    			}	
    			break;
    	}
    }

    void drawPlant() {
    	for (int i = 0; i < plant.word.length(); i++) {
    		char c = plant.word[i];
    		draw(c);
    	};
		state = plant.initialState;
    }
};