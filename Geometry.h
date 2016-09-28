#pragma once


class GeometricPoint
{
public:
	float x, y;
};

class GeometricVector
{
public:
	GeometricPoint start, end;

	void normalize();
	void getLength();
	
};