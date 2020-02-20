#include "Parser.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<string> split(const std::string& str, char delim = ' ') {
    
    vector<string> vector;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim)) {
        vector.push_back(token);
    }

    return vector;
}

Parser::Parser() {}

Parser::~Parser() {}

void Parser::parse(string fileName) {

    ifstream inFile;
    string line;
    vector<string> tokens;

    inFile.open(fileName);

    while (!inFile.eof()) {
        
        getline(inFile, line);
        tokens = split(line);
        
        if (tokens.size() > 0) {

            if (tokens[0].compare("v") == 0) {

                verticesList.push_back(stof(tokens[1]));
                verticesList.push_back(stof(tokens[2]));
                verticesList.push_back(stof(tokens[3]));

            } else if (tokens[0].compare("vn") == 0) {

                normalsList.push_back(stof(tokens[1]));
                normalsList.push_back(stof(tokens[2]));
                normalsList.push_back(stof(tokens[3]));

            } else if (tokens[0].compare("f") == 0) {

                for (unsigned int i = 1; i < 4; i++) {
                    vector<string> indices = split(tokens[i], '/');
                    for (unsigned int j = 0; j < indices.size(); j++) {
                        if (j == 0) {
                            vertexIndices.push_back(stoi(indices[j]) - 1);
                        } else if (j == 2) {
                            normalIndices.push_back(stoi(indices[j]) - 1);
                        }
                    }
                }

            } 
        }
    }

}

vector<GLfloat> Parser::getVertices() {
    return verticesList;
}

vector<GLfloat> Parser::getNormals() {
    return normalsList;
}

vector<GLuint> Parser::getVertexIndices() {
    return vertexIndices;
}

vector<GLuint> Parser::getNormalsIndices() {
    return normalIndices;
}