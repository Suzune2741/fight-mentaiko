# include "Balls.h"
Balls::Balls()
{
	for (int i = 0; i <= BALL; i++)
	{
		id_ = i;
		x = Random(800.0);
		y = -10;
		acceleration = Random(1.0, 3.0);
		if (Random(2) == 1)
			is_falling = true;
		else
			is_falling = false;
		switch (Random(5))//ボールの色決め
		{
		case 0:color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 0;
			break;
		case 1:color[0] = 1; color[1] = 255; color[2] = 0; color[3] = 0;
			break;
		case 2:color[0] = 2; color[1] = 65; color[2] = 105; color[3] = 225;
			break;
		default:color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 0;
			break;
		}
	}
}
void Balls::Reset() {
	x = Random(800.0);
	acceleration = Random(1.0, 3.0);
	y = -10;
	if (Random(2) == 1)
		is_falling = true;
	else
		is_falling = false;
	switch (Random(4))//ボールの色決め
	{
	case 0:color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 0;
		break;
	case 1:color[0] = 1; color[1] = 255; color[2] = 0; color[3] = 0;
		break;
	case 2:color[0] = 2; color[1] = 65; color[2] = 105; color[3] = 225;
		break;
	default:color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 0;
		break;
	}
}
Balls::~Balls()
{
}
