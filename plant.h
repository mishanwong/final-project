#include <string>
#include <iostream>
#include <unordered_map>  
#include <glm/glm.hpp>    
#include <glm/gtc/matrix_transform.hpp> 
#include <stack>   

struct State {
	glm::vec3 position; 
	glm::vec3 dir;
	float len;
};

struct Plant {
	std::string initialWord;
	int maxIter;
	float angle; // in degree
	State initialState;
	std::unordered_map<char, std::string> rules;
	glm::vec3 color;  
    std::stack<State> s;
};