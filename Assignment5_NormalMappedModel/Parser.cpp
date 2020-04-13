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

void Parser::parse(string objFile) {

    ifstream inFile;
    string line;
    vector<string> tokens;

    inFile.open(objFile);

    while (!inFile.eof()) {
        
        getline(inFile, line);
        tokens = split(line);

        if (tokens.size() > 0) {

            if (tokens[0].compare("v") == 0) {
                vertices.push_back(QVector3D(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
            } else if (tokens[0].compare("vn") == 0) {
                normals.push_back(QVector3D(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
            } else if (tokens[0].compare("f") == 0) {
                for (unsigned int i = 1; i < 4; i++) {
                    vector<string> indices = split(tokens[i], '/');
                    vertexIndices.push_back(stoi(indices[0]) - 1);
                    textureIndices.push_back(stoi(indices[1]) - 1);
                    normalIndices.push_back(stoi(indices[2]) - 1);
                }
            } else if (tokens[0].compare("vt") == 0) {
                textures.push_back(QVector2D(stof(tokens[1]), stof(tokens[2])));
            } else if (tokens[0].compare("mtllib") == 0) {
                parseMtlFile(tokens[1], objFile);
            }
        }
    }

    loadData();

    inFile.close();
}

void Parser::loadData() {

    QVector<QVector<float>> visited;

	for (int i = 0; i < vertexIndices.size(); ++i) {
		QVector3D curVertex = vertices.at(vertexIndices.at(i));
		QVector2D curTexture = textures.at(textureIndices.at(i));

		QVector<float> vec;
		vec.push_back(curVertex.x());
		vec.push_back(curVertex.y());
		vec.push_back(curVertex.z());
		vec.push_back(curTexture.x());
		vec.push_back(curTexture.y());

		int idx = visited.indexOf(vec);
		if (idx == -1) {
			visited.push_back(vec);
			finalData.append(vec);
            idx = visited.size() - 1;
		}

		finalIndices.push_back(idx);
	}
}

void Parser::parseMtlFile(string mtlFile, string objFile) {

    ifstream inFile;
    string line;
    vector<string> tokens;

    string relPath = objFile.substr(0, objFile.find_last_of("\\/"));

    inFile.open(relPath + "/" + mtlFile);

    while (!inFile.eof()) {
        
        getline(inFile, line);
        tokens = split(line);
        if (tokens.size() > 0) {
            if (tokens[0].compare("map_Kd") == 0) {
                cout << endl << "got to the ppm file: " << tokens[1] << endl;
                ppmFile = relPath + "/" + tokens[1];
            }
        }
        if (tokens.size() > 0) {
            if (tokens[0].compare("map_Bump") == 0) {
                cout << endl << "got to the ppm file: " << tokens[1] << endl;
                ppmFile = relPath + "/" + tokens[1];
            }
        }
    }
}

string Parser::getPPMFile() const {
    return ppmFile;
}

QVector<QVector3D> Parser::getVertices() {
    return vertices;
}

QVector<QVector2D> Parser::getTextures() {
    return textures;
}

QVector<QVector3D> Parser::getNormals() {
    return normals;
}

QVector<GLuint> Parser::getVertexIndices() {
    return vertexIndices;
}

QVector<GLuint> Parser::getTextureIndices() {
    return textureIndices;
}

QVector<GLuint> Parser::getNormalsIndices() {
    return normalIndices;
}

QVector<float> Parser::getFinalData() const {
    return finalData;
}

QVector<GLuint> Parser::getFinalIndices() const {
    return finalIndices;
}