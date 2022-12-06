#include "easing.h"
#include<math.h>
const float PI = 3.1415;
float SineEaseIn(float x)
{
	return 1.0f-cosf(x*PI/2.0f);
}
float SineEaseOut(float x)
{
	return sinf(x*PI / 2.0f);
}
float SineEaseInOut(float x)
{
	return -(cosf(PI*x)-1)/2;
}
float QuatEaseIn(float x)
{
	return powf(x,2);
}
float QuatEaseOut(float x)
{
	return 0.0f;
}
float QuatEaseInOut(float x)
{
	return 0.0f;
}
float CubicEaseIn(float x)
{
	return 0.0f;
}
float CubicEaseOut(float x)
{
	return 0.0f;
}
float CubicEaseInOut(float x)
{
	return 0.0f;
}
float BackEaseIn(float x)
{
	float c1 = 1.70158f;
	float c3 = c1+1.0f;

	return c3*powf(x,3)-c1*powf(x,2);
}
float BackEaseOut(float x)
{
	float c1 = 1.70158f;
	//float c1 = 1.0f;
	float c3 = c1 + 1.0f;

	return 1.0f+c3 * powf(x-1, 3) + c1 * powf(x-1, 2);
}
float BackEaseInOut(float x)
{
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;

	float n= x < 0.5f ?
		(pow(2 * x, 2)* ((c2 + 1) * 2 * x - c2)) / 2
		: (pow(2 * x - 2, 2)* ((c2 + 1) * (x * 2 - 2) + c2)) / 2;
	return n;
}
