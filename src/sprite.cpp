#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image) {
	this->image = image; 
	this->x = 0; 
	this->y = 0; 
	this->z = 0; 
	this->colx = 0;
	this->coly = 0; 
	this->colwidth = 0; 
	this->colheight = 0; 
	this->angle = 0; 
	this->scalex = 1;
	this->scaley = 1;
	this->radius = 0;
	this->animFPS = 0;
	this->firstFrame = 0; 
	this->lastFrame = 0; 
	this->currentFrame = 0;
	this->blendMode = Renderer::ALPHA;
	this->r = 255; 
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->collision = NULL; 
	this->colPixelData = NULL; 
	this->colSprite = NULL; 
	this->collided = false; 

	this->rotating = false; 
	this->toAngle = 0; 
	this->rotatingSpeed = 0; 
	this->degreesToRotate = 0; 

	this->moving = false; 
	this->toX = 0; 
	this->toY = 0; 
	this->movingSpeedX = 0; 
	this->movingSpeedY = 0; 
	this->prevX = 0; 
	this->prevY = 0; 

	this->userData = NULL; 
}

Sprite::~Sprite() {

}

void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
	return collided; 
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
	return collided;
}

void Sprite::RotateTo(int32 angle, double speed) {
	double wrapAngle = WrapValue(angle, 360); 
	if (wrapAngle == WrapValue(this->angle, 360) || speed == 0)
		this->rotating = false; 
	else {
		this->rotating = true;
		this->toAngle = wrapAngle; 

		uint16 wrapAngle = (uint16)WrapValue(this->angle, 360);
		double ccw = WrapValue(this->toAngle - wrapAngle, 360);
		double cw = WrapValue(wrapAngle - this->toAngle, 360);

		if (min(ccw, cw) == ccw) {
			this->degreesToRotate = ccw; 
			this->rotatingSpeed = fabs(speed); 
		}
		else {
			this->degreesToRotate = cw;
			this->rotatingSpeed = -fabs(speed);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speed) {
	if (this->x == x && this->y == y || speed == 0) {
		this->moving = false;
	}
	else {
		this->moving = true; 
		this->toX = x; 
		this->toY = y; 
		
		//double alpha = Angle(this->x, this->y, this->toX, this->toY);

		//this->movingSpeedX = speed * DegCos(alpha); 
		//this->movingSpeedY = speed * -1 * DegSin(alpha); 

		// MRU: d = v * t ---> t = d / v ----> v = d / t
		double d = Distance(this->x, this->y, this->toX, this->toY); 
		double t = d / speed; 

		this->movingSpeedX = (this->toX - this->x) / t;
		this->movingSpeedY = (this->toY - this->y) / t;
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// Actualizar animacion
	this->currentFrame += GetFPS() * elapsed; 
	if (this->currentFrame > this->lastFrame) {
		this->currentFrame -= (this->lastFrame - this->firstFrame); 
	}
	else if (this->currentFrame < this->firstFrame) {
		this->currentFrame += (this->lastFrame - this->firstFrame);
	}

	// Actualizar rotacion animada
	if (IsRotating()) {
		double rot = elapsed * this->rotatingSpeed; 
		if (rot < this->degreesToRotate) {
			SetAngle(this->angle + rot);
			this->degreesToRotate -= rot; 
		}
		else {
			SetAngle(this->toAngle);
		}
	}

	// Actualizar movimiento animado
	if (IsMoving()) {
		double despX = this->x + elapsed * this->movingSpeedX; 
		double despY = this->y + elapsed * this->movingSpeedY;

		// x
		if (this->x < this->toX) { // Right
			if (despX > this->toX) 
				despX = this->toX; 
		}
		else if (this->x > this->toX) { // Left
			if (despX < this->toX)
				despX = this->toX;
		}
		
		// y 
		if (this->y < this->toY) { // Down
			if (despY > this->toY) 
				despY = this->toY;
		}
		else if (this->y > this->toY) { // Up
			if (despY < this->toY)
				despY = this->toY;
		}
		SetPosition(despX, despY);
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().SetColor(this->r, this->g, this->b, this->a);
	Renderer::Instance().SetBlendMode(this->blendMode);
	Renderer::Instance().DrawImage(this->image, this->x, this->y, this->currentFrame, this->image->GetWidth()*this->scalex, image->GetHeight()*this->scaley, this->angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
 