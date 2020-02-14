// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>
#include <math.h>

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

// Sample unit test comparing against GLM.
bool unitTest0() {
    
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);
    return
        glmIdentityMatrix[0][0] == myIdentity[0][0] &&
        glmIdentityMatrix[0][1] == myIdentity[0][1] &&
        glmIdentityMatrix[0][2] == myIdentity[0][2] &&
        glmIdentityMatrix[0][3] == myIdentity[0][3] &&
        glmIdentityMatrix[1][0] == myIdentity[1][0] &&
        glmIdentityMatrix[1][1] == myIdentity[1][1] &&
        glmIdentityMatrix[1][2] == myIdentity[1][2] &&
        glmIdentityMatrix[1][3] == myIdentity[1][3] &&
        glmIdentityMatrix[2][0] == myIdentity[2][0] &&
        glmIdentityMatrix[2][1] == myIdentity[2][1] &&
        glmIdentityMatrix[2][2] == myIdentity[2][2] &&
        glmIdentityMatrix[2][3] == myIdentity[2][3] &&
        glmIdentityMatrix[3][0] == myIdentity[3][0] &&
        glmIdentityMatrix[3][1] == myIdentity[3][1] &&
        glmIdentityMatrix[3][2] == myIdentity[3][2] &&
        glmIdentityMatrix[3][3] == myIdentity[3][3];
}

bool unitTest1() {

	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    return
        glmIdentityMatrix[0][0] == myIdentity(0, 0) &&
        glmIdentityMatrix[0][1] == myIdentity(0, 1) &&
        glmIdentityMatrix[0][2] == myIdentity(0, 2) &&
        glmIdentityMatrix[0][3] == myIdentity(0, 3) &&
        glmIdentityMatrix[1][0] == myIdentity(1, 0) &&
        glmIdentityMatrix[1][1] == myIdentity(1, 1) &&
        glmIdentityMatrix[1][2] == myIdentity(1, 2) &&
        glmIdentityMatrix[1][3] == myIdentity(1, 3) &&
        glmIdentityMatrix[2][0] == myIdentity(2, 0) &&
        glmIdentityMatrix[2][1] == myIdentity(2, 1) &&
        glmIdentityMatrix[2][2] == myIdentity(2, 2) &&
        glmIdentityMatrix[2][3] == myIdentity(2, 3) &&
        glmIdentityMatrix[3][0] == myIdentity(3, 0) &&
        glmIdentityMatrix[3][1] == myIdentity(3, 1) &&
        glmIdentityMatrix[3][2] == myIdentity(3, 2) &&
        glmIdentityMatrix[3][3] == myIdentity(3, 3);
}

// Sample unit test comparing against GLM.
bool unitTest2() {

	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Vector4f a(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4f b(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4f c(0.0f, 0.0f, 1.0f, 0.0f);
	Vector4f d(0.0f, 0.0f, 0.0f, 1.0f);
	Matrix4f myIdentity(a,b,c,d);

    return
        glmIdentityMatrix[0][0] == myIdentity[0][0] &&
        glmIdentityMatrix[0][1] == myIdentity[0][1] &&
        glmIdentityMatrix[0][2] == myIdentity[0][2] &&
        glmIdentityMatrix[0][3] == myIdentity[0][3] &&
        glmIdentityMatrix[1][0] == myIdentity[1][0] &&
        glmIdentityMatrix[1][1] == myIdentity[1][1] &&
        glmIdentityMatrix[1][2] == myIdentity[1][2] &&
        glmIdentityMatrix[1][3] == myIdentity[1][3] &&
        glmIdentityMatrix[2][0] == myIdentity[2][0] &&
        glmIdentityMatrix[2][1] == myIdentity[2][1] &&
        glmIdentityMatrix[2][2] == myIdentity[2][2] &&
        glmIdentityMatrix[2][3] == myIdentity[2][3] &&
        glmIdentityMatrix[3][0] == myIdentity[3][0] &&
        glmIdentityMatrix[3][1] == myIdentity[3][1] &&
        glmIdentityMatrix[3][2] == myIdentity[3][2] &&
        glmIdentityMatrix[3][3] == myIdentity[3][3];
}

// Sample unit test comparing against GLM.
// TODO: Test against glm::scale
bool unitTest3() {

	glm::mat4 glmScale = glm::mat4(2.0f);

    glmScale[3][3] = 1.0f;

	Vector4f a(2.0f, 0, 0, 0);
	Vector4f b(0, 2.0f, 0, 0);
	Vector4f c(0, 0, 2.0f, 0);
	Vector4f d(0, 0, 0, 1.0f);

	Matrix4f myScaled(a,b,c,d);
    Matrix4f result = myScaled.MakeScale(2.0f, 2.0f, 2.0f);

    return 
        glmScale[0][0] == result[0][0] &&
        glmScale[0][1] == result[0][1] &&
        glmScale[0][2] == result[0][2] &&
        glmScale[0][3] == result[0][3] &&
        glmScale[1][0] == result[1][0] &&
        glmScale[1][1] == result[1][1] &&
        glmScale[1][2] == result[1][2] &&
        glmScale[1][3] == result[1][3] &&
        glmScale[2][0] == result[2][0] && 
        glmScale[2][1] == result[2][1] &&
        glmScale[2][2] == result[2][2] &&
        glmScale[2][3] == result[2][3] &&
        glmScale[3][0] == result[3][0] &&
        glmScale[3][1] == result[3][1] &&
        glmScale[3][2] == result[3][2] &&
        glmScale[3][3] == result[3][3];
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4() {

	glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

	Matrix4f myMatrix(0,0,0,0,
                      0,0,0,0,
                      0,0,0,0,
                      0,0,0,0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    return 
    glmTest[1][3] == myMatrix[1][3] && 
    glmTest[2][3] == myMatrix[2][3];
}

// Sample unit test testing your library
bool unitTest5() {

  Vector4f a(1, 1, 1, 1);
  Vector4f b(0, 0, 0, 0);
  Vector4f c = a + b;

  return c.x == 1 && 
  c.y == 1 && 
  c.z == 1 && 
  c.w == 1;
}


// unit test for vector dot product
bool vectorTestDotProduct() {
    Vector4f a(1, 1, 1, 1);
    Vector4f b(0, 0, 0, 0);
    float c = Dot(a, b);
    
    return c == 0;
}

// unit test for multiplication of a vector by a scalar values
bool vectorTestMultiplyByScalar() {
    Vector4f a(1, 1, 1, 1);
    Vector4f c = a * 2;
    
    return c.x == 2 && 
    c.y == 2 && 
    c.z == 2 && 
    c.w == 2;
}

//  unit test for division of a vector by a scalar value
bool vectorTestDivisionByScalar() {
    Vector4f a(1, 1, 1, 1);
    Vector4f c = a / 2;
    
    return c.x == 0.50 && 
    c.y == 0.50 && 
    c.z == 0.50 && 
    c.w == 0.50;
}

//  unit test for negation of a vector
bool vectorTestNegation() {
    Vector4f a(1, 1, 1, 1);
    Vector4f c = -a;
    
    return c.x == -1 && 
    c.y == -1 && 
    c.z == -1 && 
    c.w == -1;
}

//  unit test for magnitude of a vector
bool vectorTestMagnitude() {
    Vector4f a(1, 4, 2, 3);
    float c = Magnitude(a);
    float magnitude = sqrt(30);
    return c == magnitude;
}

//  unit test for addition of 2 vectors
bool vectorTestAddition() {
    Vector4f a(1, 1, 1, 1);
    Vector4f b(1, 2, 3, 4);
    Vector4f c = a + b;

    return c.x == 2 && 
    c.y == 3 && 
    c.z == 4 && 
    c.w == 5;
}

//  unit test for subtraction of 2 vectors
bool vectorTestSubtraction() {
    Vector4f a(5, 4, 3, 2);
    Vector4f b(1, 1, 1, 1);
    Vector4f c = a - b;

    return c.x == 4 && 
    c.y == 3 && 
    c.z == 2 && 
    c.w == 1;
}

//  unit test for vector projection
bool vectorTestVectorProjection() {
    const float EPSILON =  0.0001;

    Vector4f a(1, 2, 3, 4);
    Vector4f b(4, 3, 2, 1);
    Vector4f c = Project(a, b);

    float x = 2.0/3.0;
    float y = 4.0/3.0;
    float z = 2.0;
    float w = 8.0/3.0;

    return (c.x == x) < EPSILON && 
    (c.y == y) < EPSILON && 
    (c.z == z) < EPSILON && 
    (c.w == w) < EPSILON;
}

//  unit test for normalize
bool vectorTestVectorNormalize() {
    Vector4f a(1, 1, 1, 1);
    Vector4f c = Normalize(a);

    return c.x == 0.5 && 
    c.y == 0.5 && 
    c.z == 0.5 && 
    c.w == 0.5;
}

//  unit test for cross product
bool vectorTestVectorCrossProduct() {
    Vector4f a(1, 2, 3, 0);
    Vector4f b(3, 2, 1, 0);
    Vector4f c = CrossProduct(a, b);

    return c.x == -4 && 
    c.y == 8 && 
    c.z == -4 && 
    c.w == 0;
}

bool testMakeRotationX() {

    const float EPSILON = 0.0001;

    Matrix4f rotationX( 1.0f, 0, 0, 0,
        			    0, 1.0f, 0, 0,
		        	    0, 0, 1.0f, 0,
			            0, 0, 0, 1.0f);

    Matrix4f rotation = rotationX.MakeRotationX(M_PI);

    return rotation[0][0] == 1
        && rotation[1][1] + 1 < EPSILON
        && rotation[1][2] < EPSILON
        && rotation[2][1] < EPSILON
        && rotation[2][2] + 1 < EPSILON
        && rotation[3][3] == 1;

}

bool testMakeRotationY() {

    const float EPSILON = 0.0001;

     Matrix4f rotationY( 1.0f, 0, 0, 0,
        			    0, 1.0f, 0, 0,
		        	    0, 0, 1.0f, 0,
			            0, 0, 0, 1.0f);

    Matrix4f rotation = rotationY.MakeRotationY(M_PI);
    
    return rotation[1][1] == 1
        && rotation[3][3] == 1
        && rotation[0][0] + 1 < EPSILON
        && rotation[0][2] < EPSILON
        && rotation[2][0] < EPSILON
        && rotation[2][2] + 1 < EPSILON;
}

bool testMakeRotationZ() {

    const float EPSILON = 0.0001;

     Matrix4f rotationZ(1.0f, 0, 0, 0,
        			    0, 1.0f, 0, 0,
		        	    0, 0, 1.0f, 0,
			            0, 0, 0, 1.0f);

    Matrix4f rotation = rotationZ.MakeRotationZ(M_PI);
    
    return rotation[2][2] == 1
        && rotation[3][3] == 1
        && rotation[0][0] + 1 < EPSILON
        && rotation[0][1] < EPSILON
        && rotation[1][0] < EPSILON
        && rotation[1][1] + 1 < EPSILON;
}

bool testMakeScale() {

    Matrix4f scale(1.0f, 0, 0, 0,
        			0, 1.0f, 0, 0,
		        	0, 0, 1.0f, 0,
			        0, 0, 0, 1.0f);

    scale = scale.MakeScale(2, 2, 2);
    
    return scale[0][0] == 2
        && scale[1][1] == 2
        && scale[2][2] == 2
        && scale[3][3] == 1;
}

bool testMultiplyMatrices() {

    Matrix4f first(1.0f, 0, 0, 0,
                0, 0, 0, 1.0f,
                0, 1.0f, 0, 0,
                0, 0, 1.0f, 0);
    
    Matrix4f second(1.0f, 0, 0, 0,
                0, 1.0f, 0, 0,
                0, 0, 1.0f, 0,
                0, 0, 0, 1.0f);
    
    Matrix4f result = first * second;

    return result[0][0] ==  1
        && result[0][1] == 0
        && result[0][2] == 0
        && result[0][3] == 0
        && result[1][0] == 0
        && result[1][1] == 0
        && result[1][2] == 0
        && result[1][3] == 1
        && result[2][0] == 0
        && result[2][1] == 1
        && result[2][2] == 0
        && result[2][3] == 0
        && result[3][0] == 0
        && result[3][1] == 0
        && result[3][2] == 1
        && result[3][3] == 0;
}

bool testMultiplyMatrixWithVectors() {

    Matrix4f first(1.0f, 0, 0, 0,
                    0, 1.0f, 0, 0,
                    0, 0, 1.0f, 0,
                    0, 0, 0, 1.0f);

    Vector4f second(0, 1.0f, 0, 0);
    
    Vector4f result = first * second;

    return result[0] == 0
        && result[1] == 1
        && result[2] == 0
        && result[3] == 0;
}


int main() {
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 3: " << unitTest3() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";
    std::cout << "Passed 6: " << vectorTestDotProduct() << " \n";
    std::cout << "Passed 7: " << vectorTestMultiplyByScalar()  << " \n";
    std::cout << "Passed 8: " << vectorTestDivisionByScalar()  << " \n";
    std::cout << "Passed 9: " << vectorTestNegation() << " \n";
    std::cout << "Passed 10: " << vectorTestMagnitude() << " \n";
    std::cout << "Passed 11: " << vectorTestAddition() << " \n";
    std::cout << "Passed 12: " << vectorTestSubtraction() << " \n";
    std::cout << "Passed 13: " << vectorTestVectorProjection() << " \n";
    std::cout << "Passed 14: " << vectorTestVectorNormalize() << " \n";
    std::cout << "Passed 15: " << vectorTestVectorCrossProduct() << " \n";
    std::cout << "Passed 16: " << testMakeRotationX() << " \n";
    std::cout << "Passed 17: " << testMakeRotationY() << " \n";
    std::cout << "Passed 18: " << testMakeRotationZ() << " \n";
    std::cout << "Passed 19: " << testMakeScale() << " \n";
    std::cout << "Passed 20: " << testMultiplyMatrices() << " \n";
    std::cout << "Passed 21: " << testMultiplyMatrixWithVectors() << " \n";
    

    return 0;
}