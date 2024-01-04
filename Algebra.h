#pragma once

#include <cmath>

class v2;
class v3;
class v4;
class m4;

class v2 {
public:
	v2(float scalar);
	v2(float x, float y);
	v2(int x, int y);

	v2& operator+=(const v2& other);
	v2& operator-=(const v2& other);
	v2& operator*=(const v2& other);
	v2& operator/=(const v2& other);
	v2& operator=(const v2& other);

	v2& operator=(const v4& other);
	v2& operator+=(const v4& other);
	v2& operator-=(const v4& other);
	v2& operator*=(const v4& other);
	v2& operator/=(const v4& other);

	v2& operator=(const float other);
	v2& operator+=(const float other);
	v2& operator-=(const float other);
	v2& operator*=(const float other);
	v2& operator/=(const float other);

	v2& operator+=(const v3& other);
	v2& operator-=(const v3& other);
	v2& operator/=(const v3& other);
	v2& operator*=(const v3& other);
	v2& operator=(const v3& other);


	v2& operator+(const v2& other);
	v2& operator-(const v2& other);
	v2& operator*(const v2& other);
	v2& operator/(const v2& other);

	v2& operator+(const v4& other);
	v2& operator-(const v4& other);
	v2& operator*(const v4& other);
	v2& operator/(const v4& other);

	v2& operator+(const float other);
	v2& operator-(const float other);
	v2& operator*(const float other);
	v2& operator/(const float other);

	v2& operator+(const v3& other);
	v2& operator-(const v3& other);
	v2& operator/(const v3& other);
	v2& operator*(const v3& other);



	float operator&(const v2& other); // DOT PRODUCT

	bool operator==(const v2& other);
	bool operator>=(const v2& other);
	bool operator<=(const v2& other);
	bool operator!=(const v2& other);
	bool operator>(const v2& other);
	bool operator<(const v2& other);

	float length() const;

	float x, y;
};

class v3 {
public:
	v3(float scalar);
	v3(float x, float y, float z);
	v3(int x, int y, int z);
	v3(v2 v, float z);
	v3(float x, v2 v);

	v3& operator=(const v2& other);
	v3& operator+=(const v2& other);
	v3& operator-=(const v2& other);
	v3& operator*=(const v2& other);
	v3& operator/=(const v2& other);

	v3& operator=(const v4& other);
	v3& operator+=(const v4& other);
	v3& operator-=(const v4& other);
	v3& operator*=(const v4& other);
	v3& operator/=(const v4& other);

	v3& operator=(const float other);
	v3& operator+=(const float other);
	v3& operator-=(const float other);
	v3& operator*=(const float other);
	v3& operator/=(const float other);

	v3& operator+=(const v3& other);
	v3& operator-=(const v3& other);
	v3& operator/=(const v3& other);
	v3& operator*=(const v3& other);
	v3& operator=(const v3& other);


	v3& operator+(const v2& other);
	v3& operator-(const v2& other);
	v3& operator*(const v2& other);
	v3& operator/(const v2& other);

	v3& operator+(const v4& other);
	v3& operator-(const v4& other);
	v3& operator*(const v4& other);
	v3& operator/(const v4& other);

	v3& operator+(const float other);
	v3& operator-(const float other);
	v3& operator*(const float other);
	v3& operator/(const float other);

	v3& operator+(const v3& other);
	v3& operator-(const v3& other);
	v3& operator/(const v3& other);
	v3& operator*(const v3& other);


	float operator&(const v3& other); // DOT PRODUCT

	bool operator==(const v3& other);
	bool operator>=(const v3& other);
	bool operator<=(const v3& other);
	bool operator!=(const v3& other);
	bool operator>(const v3& other);
	bool operator<(const v3& other);

	float length() const;


	v2 xy() const;

	float x, y, z;
};

class v4 {
public:
	v4(float scalar);
	v4(float x, float y, float z, float w);
	v4(int x, int y, int z, int w);
	v4(v2 v_1, v2 v_2);
	v4(v2 v, float z, float w);
	v4(float x, float y, v2 v);
	v4(v3 v, float w);
	v4(float x, v3 v);

	v4& operator=(const v2& other);
	v4& operator+=(const v2& other);
	v4& operator-=(const v2& other);
	v4& operator*=(const v2& other);
	v4& operator/=(const v2& other);

	v4& operator=(const v3& other);
	v4& operator+=(const v3& other);
	v4& operator-=(const v3& other);
	v4& operator*=(const v3& other);
	v4& operator/=(const v3& other);

	v4& operator=(const float other);
	v4& operator+=(const float other);
	v4& operator-=(const float other);
	v4& operator*=(const float other);
	v4& operator/=(const float other);

	v4& operator+=(const v4& other);
	v4& operator-=(const v4& other);
	v4& operator/=(const v4& other);
	v4& operator*=(const v4& other);
	v4& operator=(const v4& other);

	v4& operator*=(const m4& other);

	float operator&(const v4& other); // DOT PRODUCT

	bool operator==(const v4& other);
	bool operator>=(const v4& other);
	bool operator<=(const v4& other);
	bool operator!=(const v4& other);
	bool operator>(const v4& other);
	bool operator<(const v4& other);

	float length() const;





	float x, y, z, w;


	v3 xyz() const;
	v2 xy() const;
	v2 zw() const;
};

class m4 {
public:
	m4(float val);

	v4& operator*(const v4& other);

	m4& operator*(const m4& other);

	float dat[16];
};
