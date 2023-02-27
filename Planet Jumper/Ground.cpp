#include "Ground.h"

#define SIZE	(2056)

GROUND::GROUND() {
	pos.y = 250 + SIZE / 2;	//1278
	pos.x = X_MAX / 2-200;	//440
}

void GROUND::PointerInit(DRAW* pdraw) {
	this->pdraw = pdraw;
}

void GROUND::Draw(float camera) {
	this->camera = pos;
	this->camera.y += camera;
	pdraw->CircleDraw(this->camera);
}

void GROUND::Draw(VECTOR2 camera) {
	this->camera = pos;
	this->camera = this->camera-camera;
	pdraw->CircleDraw(this->camera);
}
