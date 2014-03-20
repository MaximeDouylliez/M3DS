#include "GLApplication.h"

#include <iostream>

using namespace std;

GLApplication::~GLApplication() {
}
void GLApplication::initStrip(int nbSlice,float xmin,float xmax,float ymin,float ymax){
    float stepx;
    float xvar;
    float bcoef;
    float gcoef;

    _trianglePosition.clear();
    _trianglePosition.push_back(xmin);
    _trianglePosition.push_back(ymin);
    _trianglePosition.push_back(0.0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(1);
    stepx=((xmax-xmin)/nbSlice);



    _trianglePosition.push_back(xmin);
    _trianglePosition.push_back(ymax);
    _trianglePosition.push_back(0.0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(1);
    _triangleColor.push_back(1);
    xvar=xmin;

    for( int i=0;i<nbSlice-1;i++){
        xvar=xvar+stepx;
        bcoef=1-((float)(i+1)/nbSlice);
        gcoef=(float)(i+1)/nbSlice;
        _trianglePosition.push_back(xvar);
        _trianglePosition.push_back(ymin);
        _trianglePosition.push_back(0.0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(gcoef);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);

        _trianglePosition.push_back(xvar);
        _trianglePosition.push_back(ymax);
        _trianglePosition.push_back(0.0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(bcoef);
        _triangleColor.push_back(1);
    }
}


void GLApplication::initRing(int nbSlice,float r1,float r2){
    float pi=3.14159;
    float theta;
    float bcoef;
    float gcoef;
    float step;
    float r1coef;
    float r2coef;
    float c1;
    float s1;
    float c2;
    float s2;
    step=((2*pi)/nbSlice);
    theta=0;
    _trianglePosition.clear();
    _trianglePosition.push_back(r1*cos(theta));
    _trianglePosition.push_back(r1*sin(theta));
    _trianglePosition.push_back(0.0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(1);

    _triangleTexCoord.push_back(0.5+(r1/2));
    _triangleTexCoord.push_back(0.5);





    _trianglePosition.push_back(r2*cos(theta));
    _trianglePosition.push_back(r2*sin(theta));
    _trianglePosition.push_back(0.0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(0);
    _triangleColor.push_back(1);
    _triangleColor.push_back(1);

    _triangleTexCoord.push_back(0.5+(r2/2));
    _triangleTexCoord.push_back(0.5);



    for( int i=0;i<nbSlice;i++){
        theta=theta+step;
        // bcoef=1-((float)(i+1)/nbSlice);
        //gcoef=(float)(i+1)/nbSlice;
        r1coef=(float)(i+1)/nbSlice;
        r2coef=(float)(i+1)/nbSlice;
        c1=r1*cos(theta);
        s1=r1*sin(theta);
        c2=r2*cos(theta);
        s2=r2*sin(theta);
        _trianglePosition.push_back(r1*cos(theta));
        _trianglePosition.push_back(r1*sin(theta));
        _trianglePosition.push_back(0.0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);

        _triangleTexCoord.push_back((c1+1)/2);
        _triangleTexCoord.push_back(((0-s1)+1)/2);




        _trianglePosition.push_back(r2*cos(theta));
        _trianglePosition.push_back(r2*sin(theta));
        _trianglePosition.push_back(0.0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);
        _triangleColor.push_back(1);

        _triangleTexCoord.push_back((c2+1)/2);
        _triangleTexCoord.push_back(((0-s2)+1)/2);



    }
}

GLApplication::GLApplication() {

    initRing(150,0.2,0.9);

}
void GLApplication::initialize() {

    glClearColor(1,1,1,1);
    glLineWidth(2.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    _shader0=initProgram("simple");


    initTriangleBuffer();
    initTriangleVAO();
    initTexture();


}

void GLApplication::resize(int width,int height) {
    glViewport(0,0,width,height);
}

void GLApplication::update() {

    if(_coeff>(float)treshold){
        _coeff= (float)_coeff- 0.010;treshold=0.1;}
    else{
        _coeff=(float) _coeff+ 0.010;treshold=0.9;}

    snapshot();
}

void GLApplication::draw() {

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(_shader0);
    glBindVertexArray(_triangleVAO);

    glActiveTexture(GL_TEXTURE0); // on travaille avec l'unité de texture 0
    glBindTexture(GL_TEXTURE_2D,_textureId); // l'unité de texture 0 correspond à la texture _textureId (image lagoon.jpg).
    glUniform1f(glGetUniformLocation(_shader0,"texture"),0); // on affecte la valeur du sampler2D du fragment shader : c'est l'unité 0.
    glUniform1f(glGetUniformLocation(_shader0,"coeff"),_coeff);
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    //glDrawArrays(GL_TRIANGLES,0,6);
    glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);
    glBindVertexArray(0);
    glUseProgram(0);

}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
    cout << "GLApplication : button clicked " << i << " " << s << endl;
}


/** *********************************************************** **/
GLuint GLApplication::initProgram(const std::string &filename) {
    GLuint program;

    string vertexSource=p3d::readTextFile(filename+".vert");
    string fragmentSource=p3d::readTextFile(filename+".frag");

    program=glCreateProgram();
    GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);

    const char *source;
    source=vertexSource.c_str();
    glShaderSource(vertexShader,1,&source,NULL);
    source=fragmentSource.c_str();
    glShaderSource(fragmentShader,1,&source,NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glBindAttribLocation(program,0,"position");
    glBindAttribLocation(program,1,"color");
    glBindAttribLocation(program,2,"texCoord");



    glLinkProgram(program);
    return program;
}


void GLApplication::initTexture() {
    QImage img;
    img.load("../media/lagoon.jpg");
    img=img.convertToFormat(QImage::Format_ARGB32);

    glGenTextures(1,&_textureId);
    glBindTexture(GL_TEXTURE_2D,_textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width(),img.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.bits());

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}


void GLApplication::initTriangleBuffer() {

    glGenBuffers(1,&_trianglePositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
    glBufferData(GL_ARRAY_BUFFER,_trianglePosition.size()*sizeof(float),_trianglePosition.data(),GL_STATIC_DRAW);

    glGenBuffers(2,&_triangleColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
    glBufferData(GL_ARRAY_BUFFER,_triangleColor.size()*sizeof(float),_triangleColor.data(),GL_STATIC_DRAW);

    glGenBuffers(1,&_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,_elementData.size()*sizeof(unsigned int),_elementData.data(),GL_STATIC_DRAW);

    glGenBuffers(3,&_triangleTexCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER,_triangleTexCoord.size()*sizeof(float),_triangleTexCoord.data(),GL_STATIC_DRAW);



}


void GLApplication::initTriangleVAO() {
    glGenVertexArrays(1,&_triangleVAO);
    glBindVertexArray(_triangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);


    glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);

    glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
}



