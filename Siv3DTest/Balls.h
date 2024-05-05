#pragma once
#include<iostream>
#define BALL 10

class Balls
{
public:
	Balls();
	~Balls();
	void Reset();
	double x; //x座標
	double y; //y座標
	double acceleration;//加速度
	bool is_falling; //現在落下しているか
	uint8 color[5];//色のid,r,g,b,a(aは現在使用していない)
private:
	uint32 id_; //id
};

