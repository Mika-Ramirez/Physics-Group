#pragma once

#include <cmath>
#include <iostream>

namespace P6 {
	class MyVector {
		private:
			float x, y, z;

		public:
			MyVector();
			MyVector(float x, float y, float z);

		public:
			float magnitude();
			MyVector direction();

			MyVector operator+(MyVector CVector) const;
			MyVector operator+=(MyVector CVector);
			MyVector operator-(MyVector CVector) const;
			MyVector operator-=(MyVector CVector);
			MyVector operator*(float fScalar) const;
			MyVector operator*=(float fScalar);
			MyVector componentMultiplication(MyVector CVector);
			float scalarProduct(MyVector CVector);
			MyVector vectorProduct(MyVector CVector);

		public:
			float getX();
			float getY();
			float getZ();
			void setX(float x);
			void setY(float y);
			void setZ(float z);
			MyVector getVector();
	};
}