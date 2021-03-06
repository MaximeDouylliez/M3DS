#include "Airplane.h"
#include "GLTool.h"
#include "Tools.h"

using namespace p3d;
using namespace std;

Airplane::Airplane() {
  _increment=1.0;
  _accelerate=0.1;
  _velocity=0.0;
  _orientation.setIdentity();
  _position.set(0,0,0);
  _angleX=_angleY=_angleZ=0.0;
}

Airplane::~Airplane() {

}

void Airplane::initDraw() {
  _obj.initDraw();

}


/* Tracer l'objet :
Utilisez les attributs suivants :
  - _vertex : tableau de type Vector3 contenant les coordonnées des sommets (exemple : _vertex[3].x() = coordonnée x du sommet d'indice 3)
  - _face : un tableau d'entiers à deux dimensions (un tableau de tableau) contient les indices des sommets de chaque polygone :
      Exemple : _face[3] décrit la face 3; _face[3][4] donne l'indice (dans le tableau _vertex) du 5ième sommet de la face 3.
  - _face.size() et _vertex.size() donnent le nombre de faces et de sommets de l'objet.
  - _face[i].size() donne le nombre de sommets de la face i
*/
void Airplane::draw() {

  p3d::diffuseColor=Vector3(1,0,0);
  p3d::shaderLightPhong();
  _obj.draw();
}

void Airplane::drawWorld() {
  p3d::modelviewMatrix.push();

  modelviewMatrix.translate(_position);
    modelviewMatrix.rotate(_orientation);

  draw(); // tracé de l'avion dans son repère local


  p3d::modelviewMatrix.scale(2,2,2); // grossir un peu l'avion
  draw();

  p3d::modelviewMatrix.pop();
}

void Airplane::move() {


    _position.add(_orientation*Vector3(0,0,1)*_velocity);
}

void Airplane::pitchDown() {
  //_angleX+=_increment;
_orientation.rotate(_increment,Vector3(1,0,0)); // rotation autour de x, mais cette fois, à partir de l'orientation courante !

}

void:: Airplane::pitchUp() {
  //_angleX-=_increment;
  _orientation.rotate(_increment,Vector3(-1,0,0)); // rotation autour de x, mais cette fois, à partir de l'orientation courante !


}

void Airplane::rollRight() {
 // _angleZ+=_increment;

  _orientation.rotate(_increment,Vector3(0,0,1)); // rotation autour de x, mais cette fois, à partir de l'orientation courante !

}

void Airplane::rollLeft() {
 // _angleZ-=_increment;
  _orientation.rotate(_increment,Vector3(0,0,-1)); // rotation autour de x, mais cette fois, à partir de l'orientation courante !

}

void Airplane::yawLeft() {
  //_angleY+=_increment;
  _orientation.rotate(_increment,Vector3(0,1,0)); // rotation autour de x, mais cette fois, à partir de l'orientation courante !


}

void Airplane::yawRight() {
  //_angleY-=_increment;
  _orientation.rotate(_increment,Vector3(0,-1,0)); // rotation autour de x, mais cette fois, à partir de l'orientation courante !

}

void Airplane::accelerate() {
  _velocity+=_accelerate;
  if (_velocity>3) _velocity=3;
}

void Airplane::decelerate() {
  _velocity-=_accelerate;
  if (_velocity<0) _velocity=0;
}

// lecture fichier .obj
void Airplane::read(const string &filename) {
  _obj.readInit(filename);
  _obj.rotateY(90);
}



