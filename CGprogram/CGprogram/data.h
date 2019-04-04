#pragma once

#include "Angel.h"

const int NumPoints = 100;

//----------------------------------------------------------------------------
//*********************************
const int nLength = 1000;
const int nPoints = nLength * nLength;
vec2 pointsArr[nPoints];

//----------------------------------------------------------------------------
void makePointsArray(vec2 BL, vec2 TR)
{
	vec2 point = BL;
	float offset = 2.0 / nLength;
	for (size_t i = 0; i < nLength; i++)
	{
		point.y = BL.y + i * offset;
		for (size_t j = 0; j < nLength; j++)
		{
			point.x = BL.x + j * offset;
			pointsArr[i*nLength + j] = point;
		}

	}
}

