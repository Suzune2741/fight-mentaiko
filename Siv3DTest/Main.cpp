# include <Siv3D.hpp>
#define BALL 10
#define PLAYER_SIZE 60

namespace {
	class Balls
	{
	public:
		Balls();
		~Balls();
		void Reset();
		uint32 id_; //id
		double x; //x座標
		double y; //y座標
		double acceleration;//加速度
		bool is_falling; //現在落下しているか
		uint8 color[5];
	private:

	};

	Balls::Balls()
	{
		for (int i = 0; i <= BALL; i++)
		{
			id_ = i;
			x = Random(800.0);
			y = -10;
			acceleration = Random(1.0,3.0);
			if (Random(2) == 1)
				is_falling = true;
			else
				is_falling = false;
			switch (Random(2))//ボールの色決め
			{
			case 0:color[0] = 0; color[1] = 255; color[2] = 255; color[3] = 255;
				break;
			case 1:color[0] = 1; color[1] = 255; color[2] = 0; color[3] = 0;
				break;
			case 2:color[0] = 2; color[1] = 65; color[2] = 105; color[3] = 225;
				break;
			default:
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
		switch (Random(2))//ボールの色決め
		{
		case 0:color[0] = 0; color[1] = 255; color[2] = 255; color[3] = 255;
			break;
		case 1:color[0] = 1; color[1] = 255; color[2] = 0; color[3] = 0;
			break;
		case 2:color[0] = 2; color[1] = 65; color[2] = 105; color[3] = 225;
			break;
		default:
			break;
		}
	}
	Balls::~Balls()
	{
	}
}

void Main()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	Window::Resize(1000, 600);
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
	const Font Pointfont{ FontMethod::MSDF, 24, Typeface::Bold };
	constexpr Point Offset{ 80, 60 };
	Balls balls[BALL];
	double gravity = 2.0;
	const Image Player{ U"../img/miyawaki.png" };
	const Texture player{ Player };
	int x,y;
	int point = 0;
	while (System::Update())
	{
		ClearPrint();
		x = Cursor::Pos().x;
		y = Cursor::Pos().y;
		if (Cursor::Pos().x <= 30) {
			x = 30;
			player.resized(60).drawAt(30, 500);
		}
		else if (770 <= Cursor::Pos().x) {
			x = 770;
			player.resized(60).drawAt(770, 500);
		}
		else {
			player.resized(60).drawAt(x, 500);
		}
		for (int i = 0; i < BALL; i++)
		{
			if (balls[i].is_falling) {
				balls[i].y += gravity * balls[i].acceleration;
				Circle{ balls[i].x, balls[i].y, 10 }.draw(Color(balls[i].color[1], balls[i].color[2], balls[i].color[3]));
			}
			else {
				if (Random(1) == 1)
					balls[i].is_falling = true;
				else
					balls[i].is_falling = false;
			}
			if (x - 30 <= balls[i].x && balls[i].x <= x + 30 && 500 - 30 <= balls[i].y && balls[i].y <= 500 + 30)
			{
				if (balls[i].color[0] == 0)
					point += 1;
				if (balls[i].color[0] == 1)
					point -= 1;
				if (balls[i].color[0] == 2)
					point -= 2;
				balls[i].Reset();
			}
			if (600 <= balls[i].y) balls[i].Reset();
		}
		Rect{ 804,0,1000,600 }.draw(Palette::Pink);
		RoundRect{ 810,30,100,90,10 }.draw(HSV{ 160.0, 1.0, 1.0 });
		Pointfont(U"単位").draw(815,30);
		font(point).draw(820, 60);

	}
}
