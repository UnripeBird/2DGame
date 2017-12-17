#pragma once

//디그리 1도의 라디안 값
#define DEG_TO_RAD	0.017453f
#define PI			3.141592654f	
#define PI2			6.283185308f

#define FLOAT_EPSILON		0.001f;
//실수를 정수형으로 변환
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
//두 실수가 같은지 비교
//fabs는 소수점 차의 절대값을 반환
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)	

namespace MY_UTIL
{
	//두 점 사이의 거리를 구한다
	float getDistance(float startX, float startY, float endX, float endY);

	//Start부터 End까지의 각을 라디안으로 구한다
	float getAngle(float startX, float startY, float endX, float endY);
}

