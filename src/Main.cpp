#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

using namespace sf;
const int M = 9;
const int N = 8;
int animalNum = 6;
int gameGrid[M][N];
int p1[8] = { 0 }, p2[7] = { 0 }, p3[6] = { 0 }, p4[5] = { 0 }, p5[4] = { 0 }, p6[3] = { 0 }, p7[2] = { 0 };
int pr[7] = { 0 };
bool swap = false;

int check_hor();
int check_vert();
void prog_update();
bool win_check();
void check_8();

int main()
{
	srand(time(0));
	Vector2i offset(48, 24);							// OFFSET VALUE FOR GAME GRID(ALLIGNMENT)
	srand(time(0));										// RADOM VALUE FOR GRID
	RenderWindow app(VideoMode(740, 480), "Menagerie"); // MAIN WINDOW OF GAME
	app.setFramerateLimit(60);
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;							 // TEXTURE CLASS OBJECTS MADE
	t1.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\background.png"); // LOADED FROM THESE PNG's
	t2.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\animals.png");
	t3.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\cursor.png");
	t4.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\menu.png");
	t5.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\level.png");
	t6.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\pause_menu.png");
	t7.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\gameOver.png");
	t8.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\turq.png");
	t9.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\green.png");
	t10.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\blue.png");
	t11.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\pink.png");
	t12.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\red.png");
	t13.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\yellow.png");
	t14.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\purple.png");
	t15.loadFromFile("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\sprites\\win.png");

	Sprite background(t1), gems(t2), cursor(t3), menu(t4), level(t5), pause(t6), gameOver(t7), prog1(t8), prog2(t9), prog3(t10), prog4(t11), prog5(t12), prog6(t13), prog7(t14), win(t15); // USED AS SPRITES FOR GAME

	std::string moves = "MOVES", left, score = "SCORE", int_time, scor;
	std::stringstream s_move;

	Text mov, num_mov, scores, time_disp, integer_scores;
	Font font;

	font.loadFromFile(("C:\\Users\\musta\\OneDrive\\Desktop\\PF\\Menagerie\\src\\fonts\\arial.ttf"));

	mov.setFont(font);
	num_mov.setFont(font);
	scores.setFont(font);
	time_disp.setFont(font);
	integer_scores.setFont(font);

	mov.setString(moves);
	num_mov.setString(left);
	scores.setString(score);
	time_disp.setString(int_time);
	integer_scores.setString(scor);

	mov.setCharacterSize(30);
	num_mov.setCharacterSize(30);
	time_disp.setCharacterSize(30);
	scores.setCharacterSize(30);
	integer_scores.setCharacterSize(30);

	mov.setFillColor(sf::Color::Black);
	num_mov.setFillColor(sf::Color::Black);
	time_disp.setFillColor(sf::Color::Black);
	scores.setFillColor(sf::Color::Black);
	integer_scores.setFillColor(sf::Color::Black);

	mov.setStyle(sf::Text::Bold);
	num_mov.setStyle(sf::Text::Bold);
	time_disp.setStyle(sf::Text::Bold);
	scores.setStyle(sf::Text::Bold);
	integer_scores.setStyle(sf::Text::Bold);
	int temp;
	int move = 1000;
	int pos_x, pos2_x;
	int pos_y, pos2_y;
	int row1, row2;
	int col1, col2;
	int lvl;
	bool drag = false;
	int blocks;
	float time;
	float timer;
	float game_time = 300;
	int int_score = 0;
	bool choice1 = false, choice2 = false, flag = false, change = false;
	int animalNum; // LOOP ASSIGNS RANDOM VALUE TO GAME GRID
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			animalNum = rand() % 7;
			gameGrid[i][j] = animalNum;
			// std::cout<<"value: "<<gameGrid[i][j]<<" rows: "<<i<<" col: "<<j<<std::endl;
		}
	}
	for (int i = 0; i < 1000; i++)
	{
		blocks = check_vert() + check_hor();
		check_8();
	}
	int_score = 0;
	for (int i = 0; i < 7; i++)
		pr[i] = 0;
	p1[8] = { 0 };
	p2[7] = { 0 };
	p3[6] = { 0 };
	p4[5] = { 0 };
	p5[4] = { 0 };
	p6[3] = { 0 };
	p7[2] = { 0 };
	blocks = 0;
	// check_an();
	// POLLING EVENT STARTED TO FOR USEWR TO DO SOMETHING
	Event e;
	Event f;
	Event g;
	Event h;
	while (app.isOpen())
	{
		app.draw(menu);
		app.display();
		while (app.pollEvent(f))
		{
			if (f.type == Event::Closed)
				app.close();
			if (f.type == Event::KeyPressed)
			{
				if (f.key.code == Keyboard::Num1)
					choice1 = true;
				else if (f.key.code == Keyboard::Num2)
					return 0;
				if (choice1)
				{
					while (1)
					{
						app.draw(level);
						app.display();
						while (app.pollEvent(g))
						{
							if (g.type == Event::Closed)
								app.close();
							if (g.type == Event::KeyPressed)
							{
								if (g.key.code == Keyboard::Num1)
								{
									lvl = 1;
									choice2 = true;
									break;
								}
								else if ((g.key.code == Keyboard::Num2))
								{
									lvl = 2;
									choice2 = true;
									break;
								}
								else
									return 0;
							}
						}
						if (choice2)
							break;
					}
				}
			}
		}
		if (choice2)
		{
			// if(lvl==2)
			Clock clock;
			swap = false;
			while (1)
			{
				if (lvl == 2)
				{
					time = clock.getElapsedTime().asSeconds();
					// std::cout<<timer<<std::endl;
					timer += time;
					clock.restart();

					s_move << ((int)(game_time - timer)) / 60 << ":" << (int)(game_time - timer) % (60) << " ";
					s_move >> int_time;
				}
				time_disp.setString(int_time);
				change = false;
				while (app.pollEvent(e))
				{
					if (e.type == Event::Closed)
						app.close();
					if (e.type == Event::MouseButtonPressed)
					{
						if (e.mouseButton.button == Mouse::Left)
						{
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								drag = true;
								pos_x = e.mouseButton.x;
								pos_y = e.mouseButton.y;
								row1 = pos_y / 50;
								col1 = pos_x / 50;
							}
							else
								drag = false;
						}
					}
					if (e.type == Event::MouseButtonReleased)
					{
						if (drag)
						{
							pos2_x = e.mouseButton.x;
							pos2_y = e.mouseButton.y;
							row2 = pos2_y / 50;
							col2 = pos2_x / 50;
							if (((row1 + 1 == row2 || row1 - 1 == row2) && (col1 == col2)) || ((col1 + 1 == col2 || col1 - 1 == col2) && (row1 == row2)))
							{
								temp = gameGrid[row2][col2 - 1];
								gameGrid[row2][col2 - 1] = gameGrid[row1][col1 - 1];
								gameGrid[row1][col1 - 1] = temp;
								change = true;
								swap = false;
							}
						}
					}
					if (e.type == Event::Closed)
						app.close();
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::P)
						{
							while (1)
							{
								app.draw(pause);
								app.display();
								while (app.pollEvent(h))
								{
									if (h.type == Event::Closed)
										app.close();
									if (h.type == Event::KeyPressed)
									{
										if (h.key.code == Keyboard::Num1)
										{
											flag = true;
											break;
										}
										else if (h.key.code == Keyboard::Num2)
											return 0;
									}
								}
								if (flag)
								{
									flag = false;
									break;
								}
							}
						}
					}
				}
				// MAIN GAME OPERATIONS DONE BELOW
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				blocks = check_vert() + check_hor();

				// std::cout<<blocks<<std::endl;
				prog_update();
				check_8();
				if (blocks > 0)
				{
					if (blocks > 3 && blocks < 6 && swap)
						int_score += (blocks % 3) * 150 * lvl;
					if (blocks > 3 && blocks == 6 && swap)
						int_score += (blocks / 3) * 200 * lvl;
					if (blocks > 3 && blocks >= 6 && swap)
						int_score += (blocks / 3) * 250 * lvl;
					else
						int_score += (blocks / 3) * 100 * lvl;
				}
				s_move << int_score << " ";
				s_move >> scor;
				integer_scores.setString(scor);
				s_move << move << " ";
				s_move >> left;
				num_mov.setString(left);
				if (change)
					move--;
				if (move == 0 || (lvl == 2 && timer >= game_time))
				{
					app.clear(Color::White);
					app.draw(gameOver);
					for (int i = 0; i < 300; i++)
					{
						app.display();
					}
					return 0;
				}
				if (win_check() && lvl == 1)
				{
					lvl = 2;
					for (int i = 0; i < 7; i++)
						pr[i] = 0;
					///////////////////////
					for (int i = 0; i < 8; i++)
						p1[i] = 0;
					for (int i = 0; i < 7; i++)
						p2[i] = 0;
					for (int i = 0; i < 6; i++)
						p3[i] = 0;
					for (int i = 0; i < 5; i++)
						p4[i] = 0;
					for (int i = 0; i < 4; i++)
						p5[i] = 0;
					for (int i = 0; i < 3; i++)
						p6[i] = 0;
					for (int i = 0; i < 2; i++)
						p7[i] = 0;
					////////////////////////////////////
					for (int i = 0; i < 4; i++)
						p1[i] = 1;
					for (int i = 0; i < 4; i++)
						p2[i] = 1;
					for (int i = 0; i < 3; i++)
						p3[i] = 1;
					for (int i = 0; i < 3; i++)
						p4[i] = 1;
					for (int i = 0; i < 2; i++)
						p5[i] = 1;
					for (int i = 0; i < 2; i++)
						p6[i] = 1;
					for (int i = 0; i < 1; i++)
						p7[i] = 1;
					// Clock clock;
					clock.restart();
					time = 0;
					timer = 0;
				}
				// std::cout<<lvl<<std::endl;
				if (win_check() && lvl == 2)
				{
					app.clear(Color::Black);
					app.draw(win);
					for (int i = 0; i < 300; i++)
					{
						app.display();
					}
					return 0;
				}
				// clock.restart();
				//  WRITE BETWEEN THESE LINES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				app.draw(background); // DRAWS BACKGROUND

				// DRAWS ANIMALS DEPENDING ON THE VALUES ASSIGNED TO GAMEGRID
				for (int i = 0; i < M; i++)
				{
					for (int j = 0; j < N; j++)
					{
						gems.setTextureRect(IntRect(gameGrid[i][j] * 49, 0, 45, 45));
						gems.setPosition(j * 49, i * 49);
						gems.move(48, 24); // offset
						app.draw(gems);
					}
				}
				//////////////////////////////
				for (int i = 0; i < 8; i++)
				{
					if (p1[i] == 0)
						continue;
					prog1.setTextureRect(IntRect(p1[i] * 10, 0, 10, 10));
					prog1.setPosition(610 + (i * 11), 210);
					app.draw(prog1);
				}
				for (int i = 0; i < 7; i++)
				{
					if (p2[i] == 0)
						continue;
					prog2.setTextureRect(IntRect(p2[i] * 10, 0, 10, 10));
					prog2.setPosition(610 + (i * 11), 225);
					app.draw(prog2);
				}
				for (int i = 0; i < 6; i++)
				{
					if (p3[i] == 0)
						continue;
					prog3.setTextureRect(IntRect(p3[i] * 10, 0, 10, 10));
					prog3.setPosition(610 + (i * 11), 240);
					app.draw(prog3);
				}
				for (int i = 0; i < 5; i++)
				{
					if (p4[i] == 0)
						continue;
					prog4.setTextureRect(IntRect(p4[i] * 10, 0, 10, 10));
					prog4.setPosition(610 + (i * 11), 255);
					app.draw(prog4);
				}
				for (int i = 0; i < 4; i++)
				{
					if (p5[i] == 0)
						continue;
					prog5.setTextureRect(IntRect(p5[i] * 10, 0, 10, 10));
					prog5.setPosition(610 + (i * 11), 270);
					app.draw(prog5);
				}
				for (int i = 0; i < 3; i++)
				{
					if (p6[i] == 0)
						continue;
					prog6.setTextureRect(IntRect(p6[i] * 10, 0, 10, 10));
					prog6.setPosition(610 + (i * 11), 285);
					app.draw(prog6);
				}
				for (int i = 0; i < 2; i++)
				{
					if (p7[i] == 0)
						continue;
					prog7.setTextureRect(IntRect(p7[i] * 10, 0, 10, 10));
					prog7.setPosition(610 + (i * 11), 300);
					app.draw(prog7);
				}

				// DISPLAYS THE FINAL DRAFT
				cursor.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
				cursor.move(-100, -100);
				mov.setPosition(600, 40);
				scores.setPosition(600, 105);
				integer_scores.setPosition(600, 135);
				num_mov.setPosition(600, 65);
				time_disp.setPosition(500, 150);
				if (lvl == 2)
					app.draw(time_disp);
				app.draw(scores);
				app.draw(integer_scores);
				app.draw(num_mov);
				app.draw(mov);
				app.draw(cursor);
				app.display();
			}
		}
	}
	return 0;
}
int check_hor()
{
	int count = 0;
	int blocks = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			// std::cout<<i<<" "<<j<<" "<<count<<std::endl;
			if (gameGrid[i][j] == gameGrid[i][j + 1])
				count++;
			else if (!(count > 1))
				count = 0;
			if (count >= 2)
			{
				if (gameGrid[i][j] == gameGrid[i][j + 1])
					continue;
				else
				{
					if (i == 0)
					{
						for (int k = 0; k <= count; k++)
						{
							// if(j-k<0)
							// break;

							pr[gameGrid[i][j - k]] += 1;
							gameGrid[i][j - k] = rand() % 7;
							blocks++;
						}
					}
					// else
					//{
					for (int l = 0; l < i; l++)
					{
						for (int k = 0; k <= count; k++)
						{
							// if(j-k<0)
							// break;
							// if(i-l-1<0)
							// break;
							pr[gameGrid[i][j - k]] += 1;
							gameGrid[i - l][j - k] = gameGrid[i - l - 1][j - k];
							blocks++;
						}
					}
					for (int k = 0; k <= count; k++)
					{
						// if(j-k<0)
						// break;
						gameGrid[0][j - k] = 8;
					}
					// swap=true;
					// count=0;
					//}
					swap = true;
					count = 0;
				}
			}
		}
	}
	return blocks;
}
int check_vert()
{
	int count = 0;
	int blocks = 0;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M - 1; i++)
		{
			// std::cout<<i<<" "<<j<<" "<<count<<std::endl;
			if (gameGrid[i][j] == gameGrid[i + 1][j])
				count++;
			else if (!(count > 1))
				count = 0;
			if (count >= 2)
			{
				if (gameGrid[i][j] == gameGrid[i + 1][j] && i != M - 2)
					continue;
				else if (i == M - 2)
				{
					for (int l = 0; l <= count; l++)
					{
						pr[gameGrid[i + 1 - l][j]] += 1;
						gameGrid[i + 1 - l][j] = rand() % 7;
						blocks++;
					}
					count = 0;
					swap = true;
				}
				else
				{
					for (int l = count, k = 0; k <= count; l++, k++)
					{
						if (i - l - 1 < 0)
							break;
						pr[gameGrid[i - k][j]] += 1;
						gameGrid[i - k][j] = gameGrid[i - l - 1][j];
						blocks++;
					}
					for (int l = 0; l < count; l++)
					{
						gameGrid[l][j] = 8;
					}
					count = 0;
					swap = true;
				}
			}
		}
	}
	return blocks;
}
void check_8()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (gameGrid[i][j] == 8)
				gameGrid[i][j] = rand() % 7;
}
void prog_update()
{
	int a = pr[6] / 10;
	switch (a)
	{
		case 1:
			p1[0] = 1;
			break;
		case 2:
			p1[1] = 1;
			break;
		case 3:
			p1[2] = 1;
			break;
		case 4:
			p1[3] = 1;
			break;
		case 5:
			p1[4] = 1;
			break;
		case 6:
			p1[5] = 1;
			break;
		case 7:
			p1[6] = 1;
			break;
		case 8:
			p1[7] = 1;
			break;
		default:
			break;
	}
	a = pr[1] / 10;
	switch (a)
	{
		case 1:
			p2[0] = 1;
			break;
		case 2:
			p2[1] = 1;
			break;
		case 3:
			p2[2] = 1;
			break;
		case 4:
			p2[3] = 1;
			break;
		case 5:
			p2[4] = 1;
			break;
		case 6:
			p2[5] = 1;
			break;
		case 7:
			p2[6] = 1;
			break;
		default:
			break;
	}
	a = pr[2] / 10;
	switch (a)
	{
		case 1:
			p3[0] = 1;
			break;
		case 2:
			p3[1] = 1;
			break;
		case 3:
			p3[2] = 1;
			break;
		case 4:
			p3[3] = 1;
			break;
		case 5:
			p3[4] = 1;
			break;
		case 6:
			p3[5] = 1;
			break;
		default:
			break;
	}
	a = pr[3] / 10;
	switch (a)
	{
		case 1:
			p4[0] = 1;
			break;
		case 2:
			p4[1] = 1;
			break;
		case 3:
			p4[2] = 1;
			break;
		case 4:
			p4[3] = 1;
			break;
		case 5:
			p4[4] = 1;
			break;
		default:
			break;
	}
	a = pr[4] / 10;
	switch (a)
	{
		case 1:
			p5[0] = 1;
			break;
		case 2:
			p5[1] = 1;
			break;
		case 3:
			p5[2] = 1;
			break;
		case 4:
			p5[3] = 1;
			break;
		default:
			break;
	}
	a = pr[5] / 10;
	switch (a)
	{
		case 1:
			p6[0] = 1;
			break;
		case 2:
			p6[1] = 1;
			break;
		case 3:
			p6[2] = 1;
			break;
		default:
			break;
	}
	a = pr[6] / 10;
	switch (a)
	{
		case 1:
			p7[0] = 1;
			break;
		case 2:
			p7[1] = 1;
			break;
		default:
			break;
	}
}
bool win_check()
{
	bool flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1, flag5 = 1, flag6 = 1, flag7 = 1;

	for (int i = 0; i < 8; i++)
		if (p1[i] == 0)
			flag1 = false;

	for (int i = 0; i < 7; i++)
		if (p2[i] == 0)
			flag2 = false;

	for (int i = 0; i < 6; i++)
		if (p3[i] == 0)
			flag3 = false;

	for (int i = 0; i < 5; i++)
		if (p4[i] == 0)
			flag4 = false;

	for (int i = 0; i < 4; i++)
		if (p5[i] == 0)
			flag5 = false;

	for (int i = 0; i < 3; i++)
		if (p6[i] == 0)
			flag6 = false;

	for (int i = 0; i < 2; i++)
		if (p7[i] == 0)
			flag7 = false;

	if (flag1 && flag2 && flag3 && flag4 && flag5 && flag6 && flag7)
		return true;
	else
		return false;
}
