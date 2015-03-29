#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>

namespace flx {

	class Vector {

		public:

			double x, y;

			static Vector fromAngle(double ang, double mag);

			Vector(): x(0), y(0) {};
			Vector(double a, double b): x(a), y(b) {};

			/**
				Vector addition.
			*/
			Vector operator +(const Vector& v) const;
			
			/**
				Vector subtraction.
			*/
			Vector operator -(const Vector& v) const;
			
			/**
				Scale vector.
			*/
			Vector operator *(double s) const;
			
			/**
				Scale vector.
			*/			
			Vector operator /(double s) const;
			
			/**
				Vector addition.
			*/
			Vector& operator +=(const Vector& v);
			
			/**
				Vector subtraction.
			*/
			Vector& operator -=(const Vector& v);
			
			/**
				Scale vector.
			*/
			Vector& operator *=(double s);

			/**
				Scale vector.
			*/
			Vector& operator /=(double s);

			/**
				Assignment overator.
			*/
			Vector& operator =(std::initializer_list<double>);
			
			/**
				Inequality test.
			*/
			bool operator !=(const Vector& v) const;
			
			/**
				Returns the euclidian length of the vector.
			*/
			double length() const;
			
			/**
				Returns the angle of the vector in *degrees*.
			*/
			double angle() const;
			
			/**
				Rotate the vector.
				\param ang Angle in *degrees*.
			*/
			Vector rotate(double ang) const;

	};

}

#endif