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
	std::string word;
	int numIter;
	float angle; // in degree
	State initialState;
	std::unordered_map<char, std::string> rules;
    std::stack<State> s;  
};