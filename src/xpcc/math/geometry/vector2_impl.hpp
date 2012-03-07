// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: vector2_impl.hpp 611 2011-09-29 13:09:43Z dergraaf $
 */
// ----------------------------------------------------------------------------

#ifndef XPCC__VECTOR2_HPP
	#error	"Don't include this file directly, use 'vector2.hpp' instead!"
#endif

#include <cmath>

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector() :
	x(),
	y()
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(const T& inX, const T& inY) :
	x(inX),
	y(inY)
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(
		const xpcc::Vector<T, 1> &inX,
		const xpcc::Vector<T, 1> &inY) :
	x(inX.x),
	y(inY.x)
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(const T &inX, const xpcc::Vector<T, 1> &inY) :
	x(inX),
	y(inY.x)
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(const xpcc::Vector<T, 1> &inX, const T &inY) :
	x(inX.x),
	y(inY)
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(T inVal) :
	x(inVal),
	y(inVal)
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(const xpcc::Matrix<T, 2, 1> &rhs) :
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1])
{
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>::Vector(const Vector &rhs) :
	x(rhs.x),
	y(rhs.y)
{
}

// ----------------------------------------------------------------------------
template<typename T>
void
xpcc::Vector<T, 2>::set(const T& newX, const T& newY)
{
	this->x = newX;
	this->y = newY;
}

// ----------------------------------------------------------------------------
template<typename T>
void
xpcc::Vector<T, 2>::setX(const T& value)
{
	this->x = value;
}

template<typename T>
void
xpcc::Vector<T, 2>::setY(const T& value)
{
	this->y = value;
}

// ----------------------------------------------------------------------------
template<typename T>
const T&
xpcc::Vector<T, 2>::getX() const
{
	return this->x;
}

template<typename T>
const T&
xpcc::Vector<T, 2>::getY() const
{
	return this->y;
}

// ----------------------------------------------------------------------------
template<typename T>
T
xpcc::Vector<T, 2>::getLength() const
{
	float tx = this->x;
	float ty = this->y;
	
	return GeometricTraits<T>::round(std::sqrt(tx*tx + ty*ty));
}

// ----------------------------------------------------------------------------
template<typename T>
typename xpcc::Vector<T, 2>::WideType
xpcc::Vector<T, 2>::getLengthSquared() const
{
	WideType tx = static_cast<WideType>(this->x);
	WideType ty = static_cast<WideType>(this->y);
	
	return tx * tx + ty * ty;
}

// ----------------------------------------------------------------------------
template<typename T>
float
xpcc::Vector<T, 2>::getAngle() const
{
	return std::atan2(this->y, this->x);
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::normalize()
{
	T length = this->getLength();
	
	this->x = this->x / length;
	this->y = this->y / length;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::normalized() const
{
	Vector a(*this);
	a.normalize();
	return a;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::scale(float length)
{
	float factor = length / getLength();
	
	this->x = this->x * factor;
	this->y = this->y * factor;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::scaled(float length) const
{
	Vector a(*this);
	a.scale(length);
	return a;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::rotate(float phi)
{
	float c = std::cos(phi);
	float s = std::sin(phi);
	
	// without rounding the result might be false for T = integer
	T tx =    GeometricTraits<T>::round(c * this->x - s * this->y);
	this->y = GeometricTraits<T>::round(s * this->x + c * this->y);
	this->x = tx;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::translate(const Vector<T, 2>& vector)
{
	this->x += vector.x;
	this->y += vector.y;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
typename xpcc::Vector<T, 2>::WideType
xpcc::Vector<T, 2>::getDistanceTo(const Vector<T, 2>& other) const
{
	return (other - *this).getLength();
}

// ----------------------------------------------------------------------------
template<typename T>
float
xpcc::Vector<T, 2>::getAngleTo(const Vector<T, 2>& other) const
{
	return (other - *this).getAngle();
}

// ----------------------------------------------------------------------------
template<typename T>
typename xpcc::Vector<T, 2>::WideType
xpcc::Vector<T, 2>::dot(const xpcc::Vector<T, 2>& other) const
{
	return (static_cast<WideType>(this->x) * static_cast<WideType>(other.x) +
			static_cast<WideType>(this->y) * static_cast<WideType>(other.y));
}

// ----------------------------------------------------------------------------
template<typename T>
typename xpcc::Vector<T, 2>::WideType
xpcc::Vector<T, 2>::cross(const xpcc::Vector<T, 2>& other) const
{
	return (static_cast<WideType>(this->x) * static_cast<WideType>(other.y) -
			static_cast<WideType>(this->y) * static_cast<WideType>(other.x));
}

// ----------------------------------------------------------------------------
template<typename T> template<typename U>
xpcc::Vector<U, 2>
xpcc::Vector<T, 2>::convert() const
{
	return Vector<U, 2>(static_cast<U>(this->x), static_cast<U>(this->y));
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::toOrthogonalVector() const
{
	return xpcc::Vector<T, 2>(y, -x);
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::perpendicular() const
{
	return xpcc::Vector<T, 2>(y, -x);
}

// ----------------------------------------------------------------------------
template<typename T>
int_fast8_t
xpcc::Vector<T, 2>::ccw(const Vector& a, const Vector& b,
		const Vector& c)
{
	WideType dx1 = b.x - a.x;
	WideType dy1 = b.y - a.y;
	WideType dx2 = c.x - a.x;
	WideType dy2 = c.y - a.y;
	
	WideType d1 = dx1 * dy2;
	WideType d2 = dy1 * dx2;
	
	if (d1 > d2) {
		return 1;
	}
	else if (d1 < d2) {
		return -1;
	}
	else
	{
		if ((dx1 * dx2 < 0) || (dy1 * dy2 < 0)) {
			return -1;
		}
		else
		{
			if ((dx1 * dx1 + dy1 * dy1) >= (dx2 * dx2 + dy2 * dy2)) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>& xpcc::Vector<T, 2>::operator = (const xpcc::Vector<T, 2> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>& xpcc::Vector<T, 2>::operator = (const xpcc::Matrix<T, 2, 1> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
bool xpcc::Vector<T, 2>::operator == (const xpcc::Vector<T, 2> &rhs) const
{
	return ((rhs.x == x) && (rhs.y == y));
}

// ----------------------------------------------------------------------------
template<typename T>
bool xpcc::Vector<T, 2>::operator != (const xpcc::Vector<T, 2> &rhs) const
{
	return ((rhs.x != x) || (rhs.y != y));
}

// ----------------------------------------------------------------------------
template<typename T>
bool xpcc::Vector<T, 2>::operator < (const xpcc::Vector<T, 2> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y));
}

// ----------------------------------------------------------------------------
template<typename T>
bool xpcc::Vector<T, 2>::operator <= (const xpcc::Vector<T, 2> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && (y <= rhs.y));
}

// ----------------------------------------------------------------------------
template<typename T>
bool
xpcc::Vector<T, 2>::operator > (const xpcc::Vector<T, 2> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && (y > rhs.y));
}

// ----------------------------------------------------------------------------
template<typename T>
bool
xpcc::Vector<T, 2>::operator >= (const xpcc::Vector<T, 2> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && (y >= rhs.y));
}

// ----------------------------------------------------------------------------
template<typename T>
const T&
xpcc::Vector<T, 2>::operator [] (uint8_t index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

// ----------------------------------------------------------------------------
template<typename T>
T&
xpcc::Vector<T, 2>::operator [] (uint8_t index)
{
	return reinterpret_cast<T*>(this)[index];
}

// ----------------------------------------------------------------------------
template<typename T>
T*
xpcc::Vector<T, 2>::ptr()
{
	return reinterpret_cast<T*>(this);
}

// ----------------------------------------------------------------------------
template<typename T>
const T*
xpcc::Vector<T, 2>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::operator - () const
{
	return Vector<T, 2>(-x, -y);
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::operator - (const xpcc::Vector<T, 2> &rhs) const
{
	return xpcc::Vector<T, 2>(x - rhs.x, y - rhs.y);
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::operator + (const xpcc::Vector<T, 2> &rhs) const
{
	return xpcc::Vector<T, 2>(x + rhs.x, y + rhs.y);
}

// ----------------------------------------------------------------------------
template<typename T>
T
xpcc::Vector<T, 2>::operator * (const xpcc::Vector<T, 2> &rhs) const
{
	return (x * rhs.x + y * rhs.y);
}

// ----------------------------------------------------------------------------
template<typename T>
T
xpcc::Vector<T, 2>::operator ^ (const xpcc::Vector<T, 2> &rhs) const
{
	return (x * rhs.y - y * rhs.x);
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::operator * (float scale) const
{
	return Vector<T, 2>(GeometricTraits<T>::round(this->x * scale),
						GeometricTraits<T>::round(this->y * scale));
}

template<typename T>
xpcc::Vector<T, 2>
xpcc::Vector<T, 2>::operator / (float scale) const
{
	return Vector<T, 2>(GeometricTraits<T>::round(this->x / scale),
						GeometricTraits<T>::round(this->y / scale));
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::operator += (const xpcc::Vector<T, 2> &rhs)
{
	x += rhs.x;
	y += rhs.y;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::operator -= (const xpcc::Vector<T, 2> &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::operator *= (const T &rhs)
{
	x *= rhs;
	y *= rhs;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::operator /= (const T &rhs)
{
	x /= rhs;
	y /= rhs;
	
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Vector<T, 2>&
xpcc::Vector<T, 2>::operator ~ ()
{
	*this = perpendicular();
	return *this;
}

// ----------------------------------------------------------------------------
template<typename T>
xpcc::Matrix<T, 2, 1>&
xpcc::Vector<T, 2>::asMatrix()
{
	return *((xpcc::Matrix<T, 2, 1> *) this);
}

template<typename T>
const xpcc::Matrix<T, 2, 1>&
xpcc::Vector<T, 2>::asMatrix() const
{
	return *((xpcc::Matrix<T, 2, 1> *) this);
}
//-----------------------------------------------------------------------------
template<typename T>
xpcc::Matrix<T, 1, 2>&
xpcc::Vector<T, 2>::asTransposedMatrix()
{
	return *((xpcc::Matrix<T, 1, 2> *) this);
}

template<typename T>
const xpcc::Matrix<T, 1, 2>&
xpcc::Vector<T, 2>::asTransposedMatrix() const
{
	return *((xpcc::Matrix<T, 1, 2> *) this);
}

// ----------------------------------------------------------------------------
template<typename T>
bool xpcc::Vector<T, 2>::hasNan() const
{
	return std::isnan(x) || std::isnan(y);
}

// ----------------------------------------------------------------------------
template<typename T>
bool xpcc::Vector<T, 2>::hasInf() const
{
	return std::isinf(x) || std::isinf(y);
}

// ----------------------------------------------------------------------------
// Global functions
// ----------------------------------------------------------------------------
template <typename U>
xpcc::IOStream&
xpcc::operator << (xpcc::IOStream& s, const xpcc::Vector<U, 2>& c)
{
	s << "x=" << c.x << ", y=" << c.y;
	return s;
}

// ----------------------------------------------------------------------------
template<typename U>
xpcc::Vector<U, 2>
xpcc::operator * (float scale, const Vector<U, 2> &vector)
{
	// invoke member function
	return vector * scale;
}

template<typename U>
xpcc::Vector<U, 2>
xpcc::operator / (float scale, const Vector<U, 2> &vector)
{
	// invoke member function
	return vector / scale;
}

