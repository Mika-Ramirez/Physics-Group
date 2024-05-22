#pragma once

#include "MyVector.hpp"

namespace P6 {
	class P6Particle {
		public:
			//Mass of particle to be used later.
			float mass = 0;
			//below, current Pos, V, A
			MyVector Position;
			MyVector Velocity;
			MyVector Acceleration;

		protected:
			//Update the pos/V of particle relative to time
			void UpdatePosition(float time);
			void UpdateVelocity(float time);

		public:
			void Update(float time);
	};
}