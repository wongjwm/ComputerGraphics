#ifndef PARSER
#define PARSER

#include <string>
#include <vector>
#include <QtOpenGL>

using namespace std;

class Parser {
    public:
        Parser();
        ~Parser();
        void parse(string filename);
        vector<GLfloat> getVertices();
        vector<GLfloat> getNormals();
        vector<GLuint> getVertexIndices();
        vector<GLuint> getNormalsIndices();
    private:
        vector<GLfloat> verticesList;
        vector<GLfloat> normalsList;
        vector<GLuint> vertexIndices;
        vector<GLuint> normalIndices;
};
#endif