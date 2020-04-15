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
        void parse(string objFile);
        QVector<QVector3D> getVertices();
        QVector<QVector2D> getTextures();
        QVector<QVector3D> getNormals();
        QVector<GLuint> getVertexIndices();
        QVector<GLuint> getTextureIndices();
        QVector<GLuint> getNormalsIndices();
        string getPPMFile() const;
        QVector<float> getFinalData() const;
        QVector<GLuint> getFinalIndices() const;
    private:
        void parseMtlFile(string mtlFile, string objFile);
        void loadData();
        string ppmFile;
        QVector<float> finalData;
        QVector<GLuint> finalIndices;
        QVector<QVector3D> vertices;
        QVector<QVector2D> textures;
        QVector<QVector3D> normals;
        QVector<GLuint> vertexIndices;
        QVector<GLuint> normalIndices;
        QVector<GLuint> textureIndices;
};
#endif
