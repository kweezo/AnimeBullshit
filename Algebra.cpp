#include "Algebra.h"

v2::v2(float scalar) {
	x = scalar;
	y = scalar;
}	
v2::v2(float x, float y) {
	this->x = x;
	this->y = y;
}
v2::v2(int x, int y) {
	this->x = (float)x;
	this->y = (float)y;
}



v3::v3(float scalar) {
	x = scalar;
	y = scalar;
	z = scalar;
}	
v3::v3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
v3::v3(int x, int y, int z) {
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;
}
v3::v3(v2 v, float z) {
	x = v.x;
	y = v.y;
	this->z = z;
}
v3::v3(float x, v2 v) {
	this->x = x;
	this->y = v.x;
	this->z = v.y;
}


v4::v4(float scalar) {
	x = scalar;
	y = scalar;
	z = scalar;
	w = scalar;
}	
v4::v4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
v4::v4(int x, int y, int z, int w) {
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;
	this->w = (float)w;
}
v4::v4(v2 v_1, v2 v_2) {
	x = v_1.x;
	y = v_1.y;
	z = v_2.x;
	w = v_2.y;
}
v4::v4(v2 v, float z, float w) {
	x = v.x;
	y = v.y;
	this->z = z;
	this->w = w;
}
v4::v4(float x, float y, v2 v) {
	this->x = x;
	this->y = y;
	z = v.x;
	w = v.y;
}
v4::v4(v3 v, float w) {
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
}
v4::v4(float x, v3 v) {
	this->x = x;
	y = v.x;
	z = v.y;
	w = v.z;
}

m4::m4(float scalar) {
	for (unsigned char i = 0; i < 3; i++) { dat[i*5] = scalar; }
}

v2& v2::operator+=(const v2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

v2& v2::operator-=(const v2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

v2& v2::operator*=(const v2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

v2& v2::operator/=(const v2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

v2& v2::operator+=(const v4& other) {
	x += other.x;
	y += other.y;
	return *this;
}

v2& v2::operator-=(const v4& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

v2& v2::operator*=(const v4& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

v2& v2::operator/=(const v4& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

v2& v2::operator=(const v4& other) {
	x = other.x;
	y = other.y;
	return *this;
}

v2& v2::operator+=(float other) {
	x += other;
	y += other;
	return *this;
}

v2& v2::operator-=(float other) {
	x -= other;
	y -= other;
	return *this;
}

v2& v2::operator*=(float other) {
	x *= other;
	y *= other;
	return *this;
}

v2& v2::operator/=(float other) {
	x /= other;
	y /= other;
	return *this;
}

v2& v2::operator=(float other) {
	x = other;
	y = other;
	return *this;
}

v2& v2::operator+=(const v3& other) {
	x += other.x;
	y += other.y;
	return *this;
}

v2& v2::operator-=(const v3& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

v2& v2::operator*=(const v3& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

v2& v2::operator/=(const v3& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

v2& v2::operator=(const v3& other) {
	x = other.x;
	y = other.y;
	return *this;
}

v2& v2::operator=(const v2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

float v2::length() const{
	return sqrt(x * x + y * y);
}

bool v2::operator==(const v2& other) {
	return x == other.x && y == other.y;
}

bool v2::operator>=(const v2& other) {
	return length() >= other.length();
}

bool v2::operator<=(const v2& other) {
	return length() <= other.length();
}

bool v2::operator>(const v2& other) {
	return length() > other.length();
}

bool v2::operator<(const v2& other) {
	return length() < other.length();
}

bool v2::operator!=(const v2& other) {
	return x != other.x && y != other.y;
}

float v2::operator&(const v2& other) {
	return x * other.x + y * other.y;
}

v3& v3::operator+=(const v2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

v3& v3::operator-=(const v2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

v3& v3::operator*=(const v2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

v3& v3::operator/=(const v2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

v3& v3::operator=(const v2& other) {
	x = other.x;
	y = other.y;
	z = 0.0f;
	return *this;
}

v3& v3::operator+=(const v4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

v3& v3::operator-=(const v4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

v3& v3::operator*=(const v4& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

v3& v3::operator/=(const v4& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

v3& v3::operator=(const v4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

v3& v3::operator+=(float other) {
	x += other;
	y += other;
	z += other;
	return *this;
}

v3& v3::operator-=(float other) {
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

v3& v3::operator*=(float other) {
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

v3& v3::operator/=(float other) {
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

v3& v3::operator=(float other) {
	x = other;
	y = other;
	z = other;
	return *this;
}

v3& v3::operator+=(const v3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

v3& v3::operator-=(const v3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

v3& v3::operator*=(const v3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

v3& v3::operator/=(const v3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

v3& v3::operator=(const v3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

float v3::length() const{
	return sqrt(x * x + y * y + z * z);
}

bool v3::operator==(const v3& other) {
	return x == other.x && y == other.y && z == other.z;
}

bool v3::operator>=(const v3& other) {
	return length() >= other.length();
}

bool v3::operator<=(const v3& other) {
	return length() <= other.length();
}

bool v3::operator>(const v3& other) {
	return length() > other.length();
}

bool v3::operator<(const v3& other) {
	return length() < other.length();
}

bool v3::operator!=(const v3& other) {
	return x != other.x && y != other.y && z != other.z;
}

float v3::operator&(const v3& other) {
	return x * other.x + y * other.y + z * other.z;
}

v4& v4::operator+=(const v2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

v4& v4::operator-=(const v2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

v4& v4::operator*=(const v2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

v4& v4::operator/=(const v2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

v4& v4::operator=(const v2& other) {
	x = other.x;
	y = other.y;
	z = 0.0f;
	w = 1.0f;
	return *this;
}

v4& v4::operator+=(const v4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

v4& v4::operator-=(const v4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

v4& v4::operator*=(const v4& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

v4& v4::operator/=(const v4& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

v4& v4::operator=(const v4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

v4& v4::operator+=(float other) {
	x += other;
	y += other;
	z += other;
	w += other;
	return *this;
}

v4& v4::operator-=(float other) {
	x -= other;
	y -= other;
	z -= other;
	w -= other;
	return *this;
}

v4& v4::operator*=(float other) {
	x *= other;
	y *= other;
	z *= other;
	w *= other;
	return *this;
}

v4& v4::operator/=(float other) {
	x /= other;
	y /= other;
	z /= other;
	w /= other;
	return *this;
}

v4& v4::operator=(float other) {
	x = other;
	y = other;
	z = other;
	w = other;
	return *this;
}

v4& v4::operator+=(const v3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

v4& v4::operator-=(const v3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

v4& v4::operator*=(const v3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}
v4& v4::operator/=(const v3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}
v4& v4::operator=(const v3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

float v4::length() const{
	return sqrt(x * x + y * y + z * z + w * w);
}

bool v4::operator==(const v4& other) {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool v4::operator>=(const v4& other) {
	return length() >= other.length();
}

bool v4::operator<=(const v4& other) {
	return length() <= other.length();
}

bool v4::operator>(const v4& other) {
	return length() > other.length();
}

bool v4::operator<(const v4& other) {
	return length() < other.length();
}

bool v4::operator!=(const v4& other) {
	return x != other.x && y != other.y && z != other.z && w != other.w;
}

float v4::operator&(const v4& other) {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

v2& v2::operator+(const v2& other) {
	v2 v = { x, y };
	v += other;

	return v;
}

v2& v2::operator-(const v2& other) {
	v2 v = { x, y };
	v -= other;

	return v;
}

v2& v2::operator/(const v2& other) {
	v2 v = { x, y };
	v /= other;

	return v;
}

v2& v2::operator*(const v2& other) {
	v2 v = { x, y };
	v *= other;

	return v;
}

v2& v2::operator+(const v4& other) {
	v2 v = { x, y };
	v += other.xy();

	return v;
}

v2& v2::operator-(const v4& other) {
	v2 v = { x, y };
	v -= other.xy();

	return v;
}

v2& v2::operator/(const v4& other) {
	v2 v = { x, y };
	v /= other.xy();

	return v;
}

v2& v2::operator*(const v4& other) {
	v2 v = { x, y };
	v *= other.xy();

	return v;
}

v2& v2::operator+(const float other) {
	v2 v = { x, y };
	v += other;

	return v;
}

v2& v2::operator-(const float other) {
	v2 v = { x, y };
	v -= other;

	return v;
}

v2& v2::operator/(const float other) {
	v2 v = { x, y };
	v /= other;

	return v;
}

v2& v2::operator*(const float other) {
	v2 v = { x, y };
	v *= other;

	return v;
}

v2& v2::operator+(const v3& other) {
	v2 v = { x, y };
	v += other.xy();

	return v;
}

v2& v2::operator-(const v3& other) {
	v2 v = { x, y };
	v -= other.xy();

	return v;
}

v2& v2::operator*(const v3& other) {
	v2 v = { x, y };
	v *= other.xy();

	return v;
}

v2& v2::operator/(const v3& other) {
	v2 v = { x, y };
	v /= other.xy();

	return v;
}

v3& v3::operator+(const v2& other) {
	v3 v = { x, y, z };
	v += other;

	return v;
}

v3& v3::operator-(const v2& other) {
	v3 v = { x, y, z };
	v -= other;

	return v;
}

v3& v3::operator/(const v2& other) {
	v3 v = { x, y, z };
	v /= other;

	return v;
}

v3& v3::operator*(const v2& other) {
	v3 v = { x, y, z };
	v *= other;

	return v;
}

v3& v3::operator+(const v4& other) {
	v3 v = { x, y, z };
	v += other;

	return v;
}

v3& v3::operator-(const v4& other) {
	v3 v = { x, y, z };
	v -= other;

	return v;
}

v3& v3::operator*(const v4& other) {
	v3 v = { x, y, z };
	v *= other;

	return v;
}

v3& v3::operator/(const v4& other) {
	v3 v = { x, y, z };
	v /= other;

	return v;
}

v3& v3::operator+(const float other) {
	v3 v = { x, y, z };

	v += other;

	return v;
}

v3& v3::operator-(const float other) {
	v3 v = { x, y, z };

	v -= other;

	return v;
}

v3& v3::operator/(const float other) {
	v3 v = { x, y, z };

	v /= other;

	return v;
}

v3& v3::operator*(const float other) {
	v3 v = { x, y, z };

	v *= other;

	return v;
}

v3& v3::operator+(const v3& other) {
	v3 v = { x, y, z };

	v += other;

	return v;
}

v3& v3::operator-(const v3& other) {
	v3 v = { x, y, z };

	v -= other;

	return v;
}

v3& v3::operator/(const v3& other) {
	v3 v = { x, y, z };

	v /= other;

	return v;
}

v3& v3::operator*(const v3& other) {
	v3 v = { x, y, z };

	v *= other;

	return v;
}

v4& v4::operator+(const v2& other) {
	v4 v = { x, y, z, w };

	v += other;

	return v;
}

v4& v4::operator-(const v2& other) {
	v4 v = { x, y, z, w };

	v -= other;

	return v;
}

v4& v4::operator/(const v2& other) {
	v4 v = { x, y, z, w };

	v /= other;

	return v;
}

v4& v4::operator*(const v2& other) {
	v4 v = { x, y, z, w };

	v *= other;

	return v;
}

v4& v4::operator+(const v4& other) {
	v4 v = { x, y, z, w };

	v += other;

	return v;
}

v4& v4::operator-(const v4& other) {
	v4 v = { x, y, z, w };

	v -= other;

	return v;
}

v4& v4::operator*(const v4& other) {
	v4 v = { x, y, z, w };

	v *= other;

	return v;
}

v4& v4::operator/(const v4& other) {
	v4 v = { x, y, z, w };

	v /= other;

	return v;
}

v4& v4::operator+(const float other) {
	v4 v = { x, y, z, w };

	v += other;

	return v;
}

v4& v4::operator-(const float other) {
	v4 v = { x, y, z, w };

	v -= other;

	return v;
}

v4& v4::operator*(const float other) {
	v4 v = { x, y, z, w };

	v *= other;

	return v;
}

v4& v4::operator/(const float other) {
	v4 v = { x, y, z, w };

	v /= other;

	return v;
}

v4& v4::operator+(const v3& other) {
	v4 v = { x, y, z, w };

	v += other;

	return v;
}

v4& v4::operator-(const v3& other) {
	v4 v = { x, y, z, w };

	v -= other;

	return v;
}

v4& v4::operator*(const v3& other) {
	v4 v = { x, y, z, w };

	v *= other;

	return v;
}

v4& v4::operator/(const v3& other) {
	v4 v = { x, y, z, w };

	v /= other;

	return v;
}


v2 v3::xy() const{
	return { x, y };
}

v3 v4::xyz() const{
	return { x, y, z };
}

v2 v4::xy() const{
	return { x, y };
}

v2 v4::zw() const{
	return { z, w };
}

v4& v4::operator*=(const m4& other) {
	float newX = other.dat[0] * x + other.dat[1] * x + other.dat[2] * x + other.dat[3] * x;
	float newY = other.dat[4] * y + other.dat[5] * y + other.dat[6] * y + other.dat[7] * y;
	float newZ = other.dat[8] * z + other.dat[9] * z + other.dat[10] * z + other.dat[11] * z;
	float newW = other.dat[12] * w + other.dat[13] * w + other.dat[14] * w + other.dat[15] * w;

	x = newX;
	y = newY;
	z = newZ;
	w = newW;

	return *this;
}

v4& m4::operator*(const v4& v) {
	
	v4 res = { 
		dat[0] * v.x + dat[4] * v.y + dat[8] * v.z +   dat[12] * v.w,
		dat[1] * v.x + dat[5] * v.y + dat[9] * v.z + dat[13] * v.w,
		dat[2] * v.x + dat[6] * v.y + dat[10] * v.z + dat[14] * v.w,
		dat[3] * v.x + dat[7] * v.y + dat[11] * v.z + dat[15] * v.w };
	return res;
}

m4& m4::operator*(const m4& other) {
	m4 m = m4(1.0f);

	for (unsigned char x = 0; x < 4; x++) {
		for (unsigned char y = 0; y < 4; y++) {
			m.dat[y * 4 + x] =
				dat[x] * other.dat[y * 4] +
				dat[x + 4] * other.dat[2 + y * 4] +
				dat[x + 12] * other.dat[3 + y * 4] +
				dat[x + 12] * other.dat[4 + y * 4];
		}
	}
	return m;
}

m4& m4::operator*=(const m4& other) {
	m4 m = this[0] * other;

	memcpy(dat, other.dat, 16 * sizeof(float));

	return *this;
}
