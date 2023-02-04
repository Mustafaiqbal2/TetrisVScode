/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "i22-1139_project_utils.h"
#include "i22-1139_project_pieces.h"
#include "i22-1139_project_functionality.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace sf;
int main(void)
{
//DECLARATION OF STRINGS TO BE USED FOR TEXT OBJECTS
	std::string string_scores="0";
	std::string word="SCORE";
	std::string nextShape="NEXT SHAPE";
	std::string mainM1="Start New Game";
	std::string mainM2="See HighScores";
	std::string mainM3="Help";
	std::string mainM4="Exit";
	std::string mainM5="Continue";

//DECLATION OF STRING STREAM FOR POINT SCORING
	std::stringstream scoring;
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9;
    Text scores, points, nextS, m1, m2, m3, m4, m5;
    Font font;

//FONTS LOADED
    font.loadFromFile(("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/fonts/arial.ttf"));

//ALL TEXT OBJECTS DECLARED
    scores.setFont(font);
    points.setFont(font);
    nextS.setFont(font);
    m1.setFont(font);
    m2.setFont(font);
    m3.setFont(font);
    m4.setFont(font);
    m5.setFont(font);

    scores.setString(string_scores);
    points.setString(word);
    nextS.setString(nextShape);
    m1.setString(mainM1);
    m2.setString(mainM2);
    m3.setString(mainM3);
    m4.setString(mainM4);
    m5.setString(mainM5);

    scores.setCharacterSize(35);
    points.setCharacterSize(24);
    nextS.setCharacterSize(14);
    m1.setCharacterSize(20);
    m2.setCharacterSize(20);
    m3.setCharacterSize(20);
    m4.setCharacterSize(20);
    m5.setCharacterSize(20);

    scores.setFillColor(sf::Color::White);
    points.setFillColor(sf::Color::White);
    nextS.setFillColor(sf::Color::White);
    m1.setFillColor(sf::Color::Black);
    m2.setFillColor(sf::Color::Black);
    m3.setFillColor(sf::Color::Black);
    m4.setFillColor(sf::Color::Black);
    m5.setFillColor(sf::Color::Black);

    scores.setStyle(sf::Text::Bold);
    points.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m1.setStyle(sf::Text::Bold);
    m2.setStyle(sf::Text::Bold);
    m3.setStyle(sf::Text::Bold);
    m4.setStyle(sf::Text::Bold);
    m5.setStyle(sf::Text::Bold);

//BACK GROUND RANDOMIZED
	int rnd_back=rand()%5;
	sf::SoundBuffer buffer;
	buffer.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/sounds/tetris.wav");  //MUSIC LOADED INTO BUFFER
//DECLARATION OF TEXTURE CLASS OBJECTS
	obj1.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/tiles.png");
	switch(rnd_back)
	{
		case 0:
			obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background.png");
			break;
		case 1:
			obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background1.png");
			break;
		case 2:
			obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background2.png");
			break;
		case 3:
			obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background3.png");
			break;
		case 4:
			obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background4.png");
			break;
		default:
			break;
	}
	obj3.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/frame.png");
	obj4.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/pause_menu.png");
    obj5.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/main_menu.png");
    obj6.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/help.png");
    obj7.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/hs.png");
    obj8.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/shadow.png");
    obj9.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/bombs.png");
//DECLARATION OF SPRITES
    Sprite sprite(obj1), background(obj2),frame(obj3),menu(obj4),mainM(obj5),help(obj6),high_scores(obj7), shadow(obj8), bomb(obj9);

//SOUND BUFFER LOADEDI INTO SOUND AND PUT INTO LOOP
    sf::Sound sound(buffer);
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.setPitch(1.0f);
	sound.play();

//ALL INITIAL VARIABLE DECLARED

	int nextColor=1+rand()%7;
	bool leave4=true,click1=false,click2=false,click3=false,click4=false,click5=false, overlap=true;
    Clock clock;
    int n=rand()%7;
    int highS;

//GAME LOOP INITIATED
	while (window.isOpen())
	{
		//////
		rnd_back=rand()%5;   //BACKGROUND RANDOMIZED FOR NEW GAME
		switch(rnd_back)
		{
			case 0:
				obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background.png");
				break;
			case 1:
				obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background1.png");
				break;
			case 2:
				obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background2.png");
				break;
			case 3:
				obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background3.png");
				break;
			case 4:
				obj2.loadFromFile("C:/Users/musta/OneDrive/Desktop/PF/Tetris/src/img/background4.png");
				break;
			default:
				break;
		}
//ALL VARIABLES AND ARRAYS TO BE USED IN THE GAME DECLARED
		int point_3[4][2];
		int bomb_rand=rand()%N;
		int point_4[4][2]={{0}};
		int next_point[4][2];
		int z;
		int r=0;
		int x_disp=0;
		int y_disp=0;
//BLOCKS RANDOMIZED
		for (int i=0;i<4;i++)
        {
        	point_1[i][0] = BLOCKS[n][i] % 2;
            point_1[i][1] = BLOCKS[n][i] / 2;
        }
//BOMB PLACED OUT OF FRAME UNTIL PROBABLITY RETURNS TRUE
		for(int i=0;i<4;i++)
		{
			point_4[i][0]=-10;
			point_4[i][1]=-10;
		}
//NEXT BLOCK DETEMINED USING RANDOMISED VALUE
		n=rand()%7;
	 	for (int i=0;i<4;i++)
   	    {
    	    next_point[i][0] = BLOCKS[n][i] % 2;
            next_point[i][1] = BLOCKS[n][i] / 2;
        }
//GRID INITIALIZED TO 0
		for(int i=0;i<M;i++)
			for(int j=0;j<N;j++)
				gameGrid[i][j] = 0;
//VARIABLES REDECALRED FOR ANOTHER GAME IF USER WISHES
		int delta_x=0, colorNum=1, bombColor=1,level=1,score=0,lines,lineCount=0;
  		float timer=0, delay=0.3,b_timer=0,K=0.3,pitch=0;
  		double b_delay=0.3;
  		bool rotate=0, leave=false, leave2=false,space=false,bomb_prob=false;

  		Clock clock;
  		clock.restart();
//EVENTS DECLARED
		Event f;
		Event e;
		Event k;
		Event l;
		window.clear(Color::Black);
//MAIN MENU AND TEXT OBJECTS DRAWN
		window.draw(mainM);

		m1.setPosition(80,240);
		m2.setPosition(80,280);
		m3.setPosition(130,320);
		m4.setPosition(130,360);

		window.draw(m1);
		window.draw(m2);
		window.draw(m3);
		window.draw(m4);
		window.display();
		//std::cout<<Mouse::getPosition().x<<" "<<Mouse::getPosition().y<<std::endl;

		//-----------------------------------------UNDERLINES THE TEXT OBJECT IF MOUSE HOVERS------------------------------------//
////////////////////////////////////////////
		if(Mouse::getPosition().x>=205 && Mouse::getPosition().x<=370 && Mouse::getPosition().y>=355 && Mouse::getPosition().y<380)
			m1.setStyle(sf::Text::Bold | sf::Text::Underlined);
		else
			m1.setStyle(sf::Text::Bold);
///////////////////////////////////////////
		if(Mouse::getPosition().x>=205 && Mouse::getPosition().x<=370 && Mouse::getPosition().y>=390 && Mouse::getPosition().y<420)
			m2.setStyle(sf::Text::Bold | sf::Text::Underlined);
		else
			m2.setStyle(sf::Text::Bold);
////////////////////////////////////////
		if(Mouse::getPosition().x>=255 && Mouse::getPosition().x<=300 && Mouse::getPosition().y>=435 && Mouse::getPosition().y<460)
			m3.setStyle(sf::Text::Bold | sf::Text::Underlined);
		else
			m3.setStyle(sf::Text::Bold);
//////////////////////////////////////////
		if(Mouse::getPosition().x>=255 && Mouse::getPosition().x<=300 && Mouse::getPosition().y>=480 && Mouse::getPosition().y<500)
			m4.setStyle(sf::Text::Bold | sf::Text::Underlined);
		else
			m4.setStyle(sf::Text::Bold);
////////////////////////////////////////
		//----------------------------------------------------------------------------------------------------------------------//

		//FIRST EVENT STARTED
		while(window.pollEvent(f))
		{
			//std::cout<<click1;
			if (f.type == Event::Closed)                  		 //If cross/close is clicked/pressed
		      window.close();                         			 //Opened window disposes

			if (f.type == Event::MouseButtonPressed)   			//EVENT CHECKS IF MOUSE BUTTON PRESSED
			{
				if (f.mouseButton.button == sf::Mouse::Left) 	//CONFIRMS IF LEFT MOUSE BUTTON WAS PRESSED
				{
					//std::cout << "mouse x: " << f.mouseButton.x << std::endl;
        			//std::cout << "mouse y: " << f.mouseButton.y << std::endl;

        			//------------CHECKS IF LEFT MOUSE BUTTON IS PRESSED ON A TEXT OBJECT AND CHANGES FLAG TO TRUE-----------------//
					if(f.mouseButton.x>=85 && f.mouseButton.x<=242 && f.mouseButton.y>=246 && f.mouseButton.y<263)
						click1=true;
					if(f.mouseButton.x>=82 && f.mouseButton.x<=239 && f.mouseButton.y>=277 && f.mouseButton.y<303)
						click2=true;
					if(f.mouseButton.x>=132 && f.mouseButton.x<=175 && f.mouseButton.y>=326 && f.mouseButton.y<343)
						click3=true;
					if(f.mouseButton.x>=132 && f.mouseButton.x<=175 && f.mouseButton.y>=367 && f.mouseButton.y<384)
						click4=true;
					//-------------------------------------------------------------------------------------------------------------//
				}
			}
			if (f.type == Event::KeyPressed || click1 || click2|| click3|| click4|| click5)//CHECKS IF KEY IS PRESSED OR MOUSE HAS BEEN CLICKED
			{

				if(((f.key.code == Keyboard::Num1)||((Keyboard::isKeyPressed(Keyboard::Num1))))||!leave4 || click1) //IF NUM 1 KEY is PRESSED OR OBJECT HAS BEEN CLICKED RETURNS TRUE
				{
					//leave4=true;
					while (1)
					{
						//SHADOW RESET TO BLOCK POSITION EVERY LOOP
						for(int i=0; i<4; i++)
						{
							point_3[i][0]=point_1[i][0];
							point_3[i][1]=point_1[i][1];
						}
						//IF GAME RESTARTED REINITIALIZES GRID
						if(!leave4)
						{
							for(int i=0;i<M;i++)
								for(int j=0;j<N;j++)
									gameGrid[i][j] = 0;
							leave4=true;
						}
						float time = clock.getElapsedTime().asSeconds();
						clock.restart();
						timer+=time;
						//ADDS TIME TO BOMB TIMER
						b_timer+=time;
					//---Event Listening Part---//
						//Event e;
						while (window.pollEvent(e))
						{                    //Event is occurring - until the game is in running state
							if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
								window.close();                            //Opened window disposes
							if (e.type == Event::KeyPressed)
							{             //If any other key (not cross) is pressed
								if (e.key.code == Keyboard::Up)           //Check if the other key pressed is UP key
								    rotate = true;                         //Rotation gets on
								else if (e.key.code == Keyboard::Left)    //Check if the other key pressed is LEFT key
								    delta_x = -1;                          //Change in X-Axis - Negative
								else if (e.key.code == Keyboard::Right)   //Check if the other key pressed is (e.key.code == Keyboard::Right) RIGHT key
								    delta_x = 1;                           //Change in X-Axis - Positive
							}
						}
						if(Keyboard::isKeyPressed(Keyboard::Space))
							space=true;
						if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
							delay=0.07;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.02

						if(e.key.code == Keyboard::P)//IF P KEY IS PRESSED STARTS EVENT
						while(window.pollEvent(k))
						{
							//std::cout<<click1;
							if (k.type == Event::Closed)                   //If cross/close is clicked/pressed
							  window.close();                            //Opened window disposes
							if(k.key.code == Keyboard::P)
							{
								do
								{
									//DRAWS ALL TEXT OBJECTS AND MENU
									window.clear(Color::Black);
									window.draw(mainM);
									m1.setPosition(80,240);
									m2.setPosition(80,280);
									m3.setPosition(130,320);
									m4.setPosition(130,360);
									m5.setPosition(105,400);

									window.draw(m1);
									window.draw(m2);
									window.draw(m3);
									window.draw(m4);
									window.draw(m5);

									//----UNDERLINES TEXT OBJECTS----//
									////////////////////////////////////////////
									if(Mouse::getPosition().x>=205 && Mouse::getPosition().x<=370 && Mouse::getPosition().y>=355 && Mouse::getPosition().y<380)
										m1.setStyle(sf::Text::Bold | sf::Text::Underlined);
									else
										m1.setStyle(sf::Text::Bold);
									///////////////////////////////////////////
									if(Mouse::getPosition().x>=205 && Mouse::getPosition().x<=370 && Mouse::getPosition().y>=390 && Mouse::getPosition().y<420)
										m2.setStyle(sf::Text::Bold | sf::Text::Underlined);
									else
										m2.setStyle(sf::Text::Bold);
									////////////////////////////////////////
									if(Mouse::getPosition().x>=255 && Mouse::getPosition().x<=300 && Mouse::getPosition().y>=435 && Mouse::getPosition().y<460)
										m3.setStyle(sf::Text::Bold | sf::Text::Underlined);
									else
										m3.setStyle(sf::Text::Bold);
									//////////////////////////////////////////
									if(Mouse::getPosition().x>=255 && Mouse::getPosition().x<=300 && Mouse::getPosition().y>=480 && Mouse::getPosition().y<500)
										m4.setStyle(sf::Text::Bold | sf::Text::Underlined);
									else
										m4.setStyle(sf::Text::Bold);
									////////////////////////////////////////
									if(Mouse::getPosition().x>=230 && Mouse::getPosition().x<=318 && Mouse::getPosition().y>=517 && Mouse::getPosition().y<537)
										m5.setStyle(sf::Text::Bold | sf::Text::Underlined);
									else
										m5.setStyle(sf::Text::Bold);
									////////////////////////////////////////
									window.display();

									//--NEW EVENT STARTED TO CHECK IF MOUSE BUTTON IS PRESSED--//
									while (window.pollEvent(l))
									{
										if (l.type == Event::Closed)
											window.close();
										if (l.type == Event::MouseButtonPressed)
										{
											if (l.mouseButton.button == sf::Mouse::Left)
											{
												//std::cout << "mouse x: " << l.mouseButton.x << std::endl;
												//std::cout << "mouse y: " << l.mouseButton.y << std::endl;
												if(l.mouseButton.x>=85 && l.mouseButton.x<=242 && l.mouseButton.y>=246 && l.mouseButton.y<263)
													click1=true;
												if(l.mouseButton.x>=82 && l.mouseButton.x<=239 && l.mouseButton.y>=277 && l.mouseButton.y<303)
													click2=true;
												if(l.mouseButton.x>=132 && l.mouseButton.x<=175 && l.mouseButton.y>=326 && l.mouseButton.y<343)
													click3=true;
												if(l.mouseButton.x>=132 && l.mouseButton.x<=175 && l.mouseButton.y>=367 && l.mouseButton.y<384)
													click4=true;
												if(l.mouseButton.x>=105 && l.mouseButton.x<=195 && l.mouseButton.y>=402 && l.mouseButton.y<420)
													click5=true;
											}
										}
									}
									//--CHECKS IF KEY IS PRESSED OR MOUSE CLICKED--//
									if(Keyboard::isKeyPressed(Keyboard::Num5)||click5)
									{
										click5=false;
										break;
									}
									else if((Keyboard::isKeyPressed(Keyboard::Num2))||click2)
				  				 	{
				  				 		window.clear(Color::Black);
										//high_scores.setPosition(20,20);
										window.draw(high_scores);
										click2=false;
				   						do
								   		{
											window.display();
										}
										while(!(Keyboard::isKeyPressed(Keyboard::Num0)));
								   	}
								   	else if((Keyboard::isKeyPressed(Keyboard::Num3))||click3)
								   	{
								   		window.clear(Color::Black);
										//help.setPosition(20,20);
										window.draw(help);
										click3=false;
								   		do
								   		{
											window.display();
										}
										while(!(Keyboard::isKeyPressed(Keyboard::Num0)));
								   	}
								   	else if((Keyboard::isKeyPressed(Keyboard::Num4))||click4)
								   	{
								   		click4=false;
								   		leave=true;
								   		break;
								   	}
								   	else if(Keyboard::isKeyPressed(Keyboard::Num1)|| click1)
								   	{
								   		//leave3=true;
								   		click1=false;
								   		leave4=false;
								   	}
								}
								while(((!(Keyboard::isKeyPressed(Keyboard::Num4)))&&(!(Keyboard::isKeyPressed(Keyboard::Num5))))&&((!(Keyboard::isKeyPressed(Keyboard::Num1)))));//BREAKS DISPLAY LOOP
							}
								/*
							if(leave3)
								break;
								*/
						}
						if(leave)//LEAVES THE GAME LOOP TO THE MAIN MENU
							break;
						///////////////////////////////////////////////
						///*** START CALLING YOUR FUNCTIONS HERE ***///
						//--ALL FUNCTION CALLED--//
						if(game_end())           //ENDS GAME IF FUNTION RETURN TRUE
					   	{
					   		break;
					   	}
					   	if(check_new_block())    //RESETS DISPLACEMENT AND ROTATION IF NEW BLOCK
					   	{
					   		y_disp=0;
					   		x_disp=0;
					   		r=0;
					   	}
						fallingPiece(timer, delay, colorNum, z, y_disp,point_4,K,n,next_point, nextColor);               //Example: fallingPiece() function is called here
						//destruction(point_4, bombColor,colorNum);

						if(!bomb_limit(point_4))//IF BOMB LIMIT HAS BEEN REACHED CHECKS NEW BOMB PROBALITY
						{
							bomb_prob=bomb_probability();
						}
						else
							bomb_prob=0;
						falling_bomb(point_4, b_timer, b_delay,bomb_rand, bomb_prob, bombColor);    //DROPS BOMB
						//destruction(point_4, bombColor,colorNum);

						//--CHECKS IF SHADOW HAS OVERLAPPED AND RESETS IT--//
						do
						{
							overlap=true;
							for(int i=0;i<4;i++)
							{
								if(gameGrid[point_3[i][1]][point_3[i][0]]>0 || point_3[i][0]>=N || point_3[i][1]>=M)
								{
									overlap=false;
									for(int i=0;i<4;i++)
										point_3[i][1]+=-1;
								}

							}
							if(!overlap)
								break;
							fallingPiece(point_3);
						}
						while(overlap);

						//FUNCTIONS FOR LEFT AND RIGHT DISPLACEMENT IN ACCORDANCE WITH DELTA VALUE
						if(delta_x<0)
							shiftL(delta_x, x_disp);
						else
							shiftR(delta_x, x_disp);
						(down(space,delay));
						//delay=0.3;

						//CALLS ROTATION FUNCTION IF ROTATE ON AND RESETS IT
						if(rotate)
						{
					  	 	rotating(z,r,x_disp,y_disp);
					  	 	rotate=false;
					  	}

					  	//CALCULATES LINES CLEARED
					  	lines=lineCheck();
					  	lineCount+=lines;//ADDS LINES TO COUNTER(FOR DIFFICULTY)

					  	//-----CALCULATES SCORE BASED ON LINES CLEARED AND LEVEL-----//
					  	switch(lines)
					  	{
					  		case 0:
					  			score+=0;
					  			break;
					  		case 1:
								score+=10*level;
								break;
							case 2:
								score+=30*level;
								break;
							case 3:
								score+=60*level;
								break;
							default:
								score+=100*level;
								break;
						}

						difficulty(lineCount,K,pitch); //CHANGES DIFFICULTY IF 5 LINES ARE CLEARED AND INCREASES AUDIO PITCH FOR INTENSITY

						sound.setPitch(pitch+1.0f);    //ADDS PITCH CONSTANT (DECIDE BY DIFFICULTY FUNCTION)

						scoring<<score<<" ";           //INSERTS SCORES TO STRING STREAM

						scoring>>string_scores;        //EXTRACTS STREAM INTO STRING VARIABLE

						scores.setString(string_scores);//PUTS NEW SCORE INTO TEXT OBJECT

						click1=false;					//RESETS CLICK1

						///*** YOUR CALLING STATEMENTS END HERE ***///
						//////////////////////////////////////////////


						window.clear(Color::Black);
						window.draw(background);

						//----DRAWS BOMB BASED ON CO ORDIANTED IN ARRAY
						for (int i=0; i<4; i++)
						{
							bomb.setTextureRect(IntRect(bombColor*18,0,18,18)); //DECIDED BOMB COLOR AND SEPARATES SPRITES
							bomb.setPosition(point_4[i][0]*18,point_4[i][1]*18);
							bomb.move(28,31);
							window.draw(bomb);
						}
						//----DRAWS SHADOW BASED ON POINT 3 COORDINATES
						for (int i=0; i<4; i++)
						{
							shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
							shadow.setPosition(point_3[i][0]*18,point_3[i][1]*18);
							shadow.move(28,31);
							window.draw(shadow);
						}
						for (int i=0; i<M; i++)
						{
							for (int j=0; j<N; j++)
							{
								if (gameGrid[i][j]==0)
								    continue;
								sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
								sprite.setPosition(j*18,i*18);
								sprite.move(28,31); //offset
								window.draw(sprite);
							}
						}
						for (int i=0; i<4; i++)
						{
							sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
							sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
							sprite.move(28,31);
							window.draw(sprite);
						}

						//--DRAWS NEXT BLOCK BASED ON NEXT COLOR AND COORDINATES
						for (int i=0; i<4; i++)
						{
							sprite.setTextureRect(IntRect(nextColor*18,0,18,18));
							sprite.setPosition(next_point[i][0]*18,next_point[i][1]*18);
							sprite.move(235,220);
							window.draw(sprite);
						}
						//---The Final on Which Everything is Drawn Over is Loaded---//
						scores.setPosition(225,150);
						window.draw(scores);

						points.setPosition(225,110);
						window.draw(points);

						nextS.setPosition(225,200);
						window.draw(nextS);

						window.draw(frame);
						//---The Window that now Contains the Frame is Displayed---//
						window.display();
						//return 0;
				  	}
				  	std::fstream input("highscores.txt");// LOADS TEXT FILE
					input >>highS;							//EXTRACTS TEXT FILE INTO INTEGER VARIABLE
					if(score>highS)							//COMPARES HIGH SCORE AND NEW SCORE
						input<<string_scores;
					else
						input<<highS;
			   	}

			   	//DISPLAYS REST OF THE MENU BASED ON INPUTS OR MOUSE CLICKS
			   	else if((Keyboard::isKeyPressed(Keyboard::Num2))||click2)
			   	{
			   		window.clear(Color::Black);
					//high_scores.setPosition(20,20);
					window.draw(high_scores);
					click2=false;
			   		do
			   		{
						window.display();
					}
					while(!(Keyboard::isKeyPressed(Keyboard::Num0)));
			   	}
			   	else if((Keyboard::isKeyPressed(Keyboard::Num3))||click3)
			   	{
			   		window.clear(Color::Black);
					//help.setPosition(20,20);
					click3=false;
			   		do
			   		{
			   			window.draw(help);
						window.display();
					}
					while(!(Keyboard::isKeyPressed(Keyboard::Num0)));
			   	}
			   	else if((Keyboard::isKeyPressed(Keyboard::Num4))||click4)
		   		{
		   			click4=false;
	 	  			leave2=true;
		   		}
		//return 0;
			}
		}
		if(leave2)//EXITS GAME IF USER PRESSES LEAVE BUTTON
			break;
	}
}
