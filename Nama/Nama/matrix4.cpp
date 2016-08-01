#include "matrix4.h"

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		data[i] = 0;

	data[0] = data[5] = data[10] = data[15] = 1;
}

Matrix4::~Matrix4()
{
}

Vector3 Matrix4::operator*( Vector3 &vector )
{
	float x2 = (vector.x * data[0] + vector.y * data[4] + vector.z * data[8] + data[12]);
	float y2 = (vector.x * data[1] + vector.y * data[5] + vector.z * data[9] + data[13]);
	float z2 = (vector.x * data[2] + vector.y * data[6] + vector.z * data[10] + data[14]);

	return Vector3(x2,y2,z2);
}

Matrix4 Matrix4::operator*( Matrix4 &other)
{
	Matrix4 result;

	for( int i = 0; i < 16; i++ )
	{
		result.data[i] = 0;
	}

	for( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			for ( int k = 0; k < 4; k++)
			{
				result.data[4*i + j] += this->data[4*k + j] * other.data[4*i + k];
			}
		}
	}

	return result;
}

Matrix4 Matrix4::GetInverse()
{
	Matrix4 i;

	float x = GetDeterminant();


	// May switch to LU Decomposition method
	i.data[0]= (-data[13]*data[10]*data[7] +data[9]*data[14]*data[7] +data[13]*data[6]*data[11]
	-data[5]*data[14]*data[11] -data[9]*data[6]*data[15] +data[5]*data[10]*data[15])/x;
	i.data[4]= ( data[12]*data[10]*data[7] -data[8]*data[14]*data[7] -data[12]*data[6]*data[11]
	+data[4]*data[14]*data[11] +data[8]*data[6]*data[15] -data[4]*data[10]*data[15])/x;
	i.data[8]= (-data[12]*data[9]* data[7] +data[8]*data[13]*data[7] +data[12]*data[5]*data[11]
	-data[4]*data[13]*data[11] -data[8]*data[5]*data[15] +data[4]*data[9]* data[15])/x;
	i.data[12]=( data[12]*data[9]* data[6] -data[8]*data[13]*data[6] -data[12]*data[5]*data[10]
	+data[4]*data[13]*data[10] +data[8]*data[5]*data[14] -data[4]*data[9]* data[14])/x;
	i.data[1]= ( data[13]*data[10]*data[3] -data[9]*data[14]*data[3] -data[13]*data[2]*data[11]
	+data[1]*data[14]*data[11] +data[9]*data[2]*data[15] -data[1]*data[10]*data[15])/x;
	i.data[5]= (-data[12]*data[10]*data[3] +data[8]*data[14]*data[3] +data[12]*data[2]*data[11]
	-data[0]*data[14]*data[11] -data[8]*data[2]*data[15] +data[0]*data[10]*data[15])/x;
	i.data[9]= ( data[12]*data[9]* data[3] -data[8]*data[13]*data[3] -data[12]*data[1]*data[11]
	+data[0]*data[13]*data[11] +data[8]*data[1]*data[15] -data[0]*data[9]* data[15])/x;
	i.data[13]=(-data[12]*data[9]* data[2] +data[8]*data[13]*data[2] +data[12]*data[1]*data[10]
	-data[0]*data[13]*data[10] -data[8]*data[1]*data[14] +data[0]*data[9]* data[14])/x;
	i.data[2]= (-data[13]*data[6]* data[3] +data[5]*data[14]*data[3] +data[13]*data[2]*data[7]
	-data[1]*data[14]*data[7] -data[5]*data[2]*data[15] +data[1]*data[6]* data[15])/x;
	i.data[6]= ( data[12]*data[6]* data[3] -data[4]*data[14]*data[3] -data[12]*data[2]*data[7]
	+data[0]*data[14]*data[7] +data[4]*data[2]*data[15] -data[0]*data[6]* data[15])/x;
	i.data[10]=(-data[12]*data[5]* data[3] +data[4]*data[13]*data[3] +data[12]*data[1]*data[7]
	-data[0]*data[13]*data[7] -data[4]*data[1]*data[15] +data[0]*data[5]* data[15])/x;
	i.data[14]=( data[12]*data[5]* data[2] -data[4]*data[13]*data[2] -data[12]*data[1]*data[6]
	+data[0]*data[13]*data[6] +data[4]*data[1]*data[14] -data[0]*data[5]* data[14])/x;
	i.data[3]= ( data[9]* data[6]* data[3] -data[5]*data[10]*data[3] -data[9]* data[2]*data[7]
	+data[1]*data[10]*data[7] +data[5]*data[2]*data[11] -data[1]*data[6]* data[11])/x;
	i.data[7]= (-data[8]* data[6]* data[3] +data[4]*data[10]*data[3] +data[8]* data[2]*data[7]
	-data[0]*data[10]*data[7] -data[4]*data[2]*data[11] +data[0]*data[6]* data[11])/x;
	i.data[11]=( data[8]* data[5]* data[3] -data[4]*data[9]* data[3] -data[8]* data[1]*data[7]
	+data[0]*data[9]* data[7] +data[4]*data[1]*data[11] -data[0]*data[5]* data[11])/x;
	i.data[15]=(-data[8]* data[5]* data[2] +data[4]*data[9]* data[2] +data[8]* data[1]*data[6]
	-data[0]*data[9]* data[6] -data[4]*data[1]*data[10] +data[0]*data[5]* data[10])/x;

	return i;
}

float Matrix4::GetDeterminant()
{
	// May switch to LU Decomposition method
	return
	data[12]*data[9]*data[6]*data[3]-
	data[8]*data[13]*data[6]*data[3]-
	data[12]*data[5]*data[10]*data[3]+
	data[4]*data[13]*data[10]*data[3]+
	data[8]*data[5]*data[14]*data[3]-
	data[4]*data[9]*data[14]*data[3]-
	data[12]*data[9]*data[2]*data[7]+
	data[8]*data[13]*data[2]*data[7]+
	data[12]*data[1]*data[10]*data[7]-
	data[0]*data[13]*data[10]*data[7]-
	data[8]*data[1]*data[14]*data[7]+
	data[0]*data[9]*data[14]*data[7]+
	data[12]*data[5]*data[2]*data[11]-
	data[4]*data[13]*data[2]*data[11]-
	data[12]*data[1]*data[6]*data[11]+
	data[0]*data[13]*data[6]*data[11]+
	data[4]*data[1]*data[14]*data[11]-
	data[0]*data[5]*data[14]*data[11]-
	data[8]*data[5]*data[2]*data[15]+
	data[4]*data[9]*data[2]*data[15]+
	data[8]*data[1]*data[6]*data[15]-
	data[0]*data[9]*data[6]*data[15]-
	data[4]*data[1]*data[10]*data[15]+
	data[0]*data[5]*data[10]*data[15];
}