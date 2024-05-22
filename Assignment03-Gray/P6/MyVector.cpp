#include "MyVector.hpp"

using namespace P6;

/* Constructor */
MyVector::MyVector() {
	this->x = 0.f;
	this->y = 0.f;
	this->z = 0.f;
}

MyVector::MyVector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

/* Magnitude */
float MyVector::magnitude() {
	return std::sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

/* Direction */
MyVector MyVector::direction() {
	float fMagnitude = magnitude();

	if (fMagnitude == 0) {
		return MyVector(0, 0, 0);
	}

	return MyVector(this->x / fMagnitude, this->y / fMagnitude, this->z / fMagnitude);
}

/* Addition */
MyVector MyVector::operator+(MyVector CVector) const {
	return MyVector(this->x + CVector.x, this->y + CVector.y, this->z + CVector.z);
}

MyVector MyVector::operator+=(MyVector CVector) {
	this->x += CVector.x;
	this->y += CVector.y;
	this->z += CVector.z;
	return *this;
}

/* Subtraction */
MyVector MyVector::operator-(MyVector CVector) const {
	return MyVector(this->x - CVector.x, this->y - CVector.y, this->z - CVector.z);
}

MyVector MyVector::operator-=(MyVector CVector) {
	this->x -= CVector.x;
	this->y -= CVector.y;
	this->z -= CVector.z;
	return *this;
}

/* Scalar Multiplication */
MyVector MyVector::operator*(float fScalar) const {
	return MyVector(this->x * fScalar, this->y * fScalar, this->z * fScalar);
}

MyVector MyVector::operator*=(float fScalar) {
	this->x *= fScalar;
	this->y *= fScalar;
	this->z *= fScalar;
	return *this;
}


/* Component Product */
MyVector MyVector::componentMultiplication(MyVector CVector) {
	return MyVector(this->x * CVector.x, this->y * CVector.y, this->z * CVector.z);
}

/* Scalar/Dot Product*/
float MyVector::scalarProduct(MyVector CVector) {
	return (this->x * CVector.x) + (this->y * CVector.y) + (this->z * CVector.z);
}

/* Vector/Cross Product */
MyVector MyVector::vectorProduct(MyVector CVector) {
	float fX = (this->y * CVector.z) - (this->z * CVector.y);
	float fY = (this->z * CVector.x) - (this->x * CVector.z);
	float fZ = (this->x * CVector.y) - (this->y * CVector.x);
	return MyVector(fX, fY, fZ);
}

/* Getters and Setters */
float MyVector::getX() {
	return this->x;
}

float MyVector::getY() {
	return this->y;
}

float MyVector::getZ() {
	return this->z;
}

void MyVector::setX(float x) {
	this->x = x;
}

void MyVector::setY(float y) {
	this->y = y;
}

void MyVector::setZ(float z) {
	this->z = z;
}

MyVector MyVector::getVector() {
	return MyVector(this->x, this->y, this->z);
}