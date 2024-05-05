# include <Siv3D.hpp>
# include"Balls.h"
#define BALL 10
#define PLAYER_SIZE 60
#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 600

namespace MotionGraphics
{
	/// @brief モーショングラフィックスで線を描く
	/// @param begin 線の始点
	/// @param end 線の終点
	/// @param thickness 線の太さ
	/// @param t 経過時間 [0.0, 1.0]
	/// @param interval モーションの開始前と開始後の何も表示しない時間 [0.0, 1.0)
	inline void DrawLine(const Vec2& begin, const Vec2& end, double thickness, double t, double interval = 0.0)
	{
		const double s = (0.5 - interval);
		const Line line = Line{ begin, end }.stretched(thickness * 0.5);

		if (InRange(t, interval, 0.5))
		{
			t = (t - interval) / s;
			const double e = Min((EaseOutExpo(t) * 1.03), 1.0);
			Line{ line.begin, line.begin.lerp(line.end, e) }
			.draw(LineStyle::Uncapped, thickness);
		}
		else if (t < (1.0 - interval))
		{
			t = (t - 0.5) / s;
			const double e = Min((EaseOutExpo(t) * 1.03), 1.0);
			Line{ line.begin.lerp(line.end, e), line.end }
			.draw(LineStyle::Uncapped, thickness);
		}
	}
}

void Personality_Window()
{
	using MotionGraphics::DrawLine;
	constexpr double period = 1.2;
	const Image IMG{ U"../img/miyawaki.png" };
	const Font font{ FontMethod::MSDF, 42, Typeface::Bold };
	const Texture game{ U"🎮"_emoji };
	const Texture MYWK{ IMG };
	int status = 0;
	while (System::Update()) {

		MYWK.resized(250).drawAt(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2 + 30);
		const RoundRect rr{ 50,WINDOW_SIZE_Y / 2 - 60,150,130,10 };
		rr.draw(ColorF{ 0,40,0.44,0.61 });
		if (rr.mouseOver()) {
			rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw(Palette::Lightgray);
			if (rr.leftClicked()) {
				status++;
			}

		}
		else {
			rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw();
		}
		font(U"勉強").draw(80, WINDOW_SIZE_Y / 2-60, Palette::Black);
		game.resized(60).drawAt(120,WINDOW_SIZE_Y/2+30);
	}
}
void Syllabus_Window()
{
	Scene::SetBackground(ColorF{ 0.996, 0.992, 0.918 });
	const Font headline{ FontMethod::MSDF, 60, Typeface::Bold };
	const Font font{ FontMethod::MSDF, 32, Typeface::Bold };
	const Image IMG{ U"../img/laminne.png" };
	const Texture Cursor{ IMG };
	while (System::Update())
	{
		Cursor::RequestStyle(CursorStyle::Hidden);
		headline(U"シラバス").draw(WINDOW_SIZE_X / 2 - 60 * 2, 20, ColorF{ 0.008, 0.208, 0.259 });
		const RoundRect rr{ WINDOW_SIZE_X / 2 - 150, 500, 300, 80, 40 };
		if (rr.mouseOver()) {
			rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw(Palette::Lightgray);
			if (rr.leftClicked()) return;
		}
		else {
			rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw();
		}
		Circle{ rr.rect.pos.movedBy(rr.r, rr.r), rr.r }
			.stretched(-5)
			.draw(HSV{ 40, 0.5, 1.0 });
		font(U"もどる").draw(WINDOW_SIZE_X / 2 - 50, 520, ColorF{ 0.008, 0.208, 0.259 });
		Cursor.resized(60).drawAt(Cursor::Pos().x, Cursor::Pos().y);

	}
}
void Menu_Window()
{
	Scene::SetBackground(ColorF{ 0.9, 0.95, 1.0 });
	const Font Pointfont{ FontMethod::MSDF, 60, Typeface::Bold };
	const Font font{ FontMethod::MSDF, 32, Typeface::Bold };
	const Image IMG{ U"../img/laminne.png" };
	const Texture Cursor{ IMG };
	while (System::Update())
	{
		Cursor::RequestStyle(CursorStyle::Hidden);
		Rect{ 450, 0, 100, 600 }
		.shearedX(150).draw(HSV{ 40, 0.5, 1.0 });

		Rect{ 550, 0, 400, 600 }
		.shearedX(150).draw(HSV{ 40, 0.8, 1.0 });

		for (auto i : step(5))
		{
			const RoundRect rr{ 50, (60 + i * 100), 350, 80, 40 };
			if (rr.mouseOver()) {
				rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
					.draw(Palette::Lightgray);
				if (rr.leftClicked() && i == 0) return;
				else if (rr.leftClicked() && i == 1) Personality_Window();
				else if (rr.leftClicked() && i == 2) Syllabus_Window();
				else if (rr.leftClicked() && i == 4)  System::Exit();
			}
			else {
				rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
					.draw();
			}
			Circle{ rr.rect.pos.movedBy(rr.r, rr.r), rr.r }
				.stretched(-5)
				.draw(HSV{ 40, 0.5, 1.0 });


		}
		Pointfont(U"それいけ！\nMYWKくん！").draw(600, 30);
		font(U"入学").draw(130, 75, Palette::Skyblue);
		font(U"性格設定").draw(130, 175, Palette::Skyblue);//勉強するとげーむするで難易度分ける
		font(U"シラバス").draw(130, 275, Palette::Skyblue);
		font(U"MYWKくん").draw(130, 375, Palette::Skyblue);
		font(U"退学").draw(130, 475, Palette::Skyblue);
		Cursor.resized(60).drawAt(Cursor::Pos().x, Cursor::Pos().y);

	}
}

void Main()
{
	Window::Resize(1000, 600);
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
	const Font Pointfont{ FontMethod::MSDF, 24, Typeface::Bold };
	constexpr Point Offset{ 80, 60 };
	Balls balls[BALL];
	double gravity = 2.0;
	const Image Player{ U"../img/miyawaki.png" };
	const Texture player{ Player };
	int x,y;
	int point = 0, month = 4,count=1;
	String day = U"4月";
	Stopwatch stopwatch{ StartImmediately::Yes };
	Menu_Window();
	Scene::SetBackground(ColorF{ 0.91, 0.95, 0.96 });
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
			if (InRange(balls[i].x, x - 30.0, x + 30.0) && InRange(balls[i].y,470.0,530.0))
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
			//if (30.41s <= stopwatch)
			//	return ;
		}
		Rect{ 804,0,1000,600 }.draw(ColorF{0.94,0.42,0.49});
		RoundRect{ 810,100,100,90,10 }.draw(ColorF{0,40,0.44,0.61});
		Pointfont(U"単位").draw(815,100);
		font(point).draw(820, 130);
		if (point <= -30) return;
		if (2.5 * count <= stopwatch.s())
		{
			month++,count++;
			day = Format(month%12 == 0 ? 12 : month%12);
			day << U'月';
		}
		font(day).draw(820, 30);

	}
}
