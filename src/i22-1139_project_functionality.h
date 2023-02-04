/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
//PROTOTYPES FOR FUNCTIONS CALLED IN OTHER FUNCTIONS
bool shadow_limit(int point[][2]);
bool bomb_limit(int point_4[][2]);
///////////////////////////////////////////////////////
void fallingPiece(float& timer, float& delay, int& colorNum, int&z, int& y_disp, int point_3[][2],float K,int& n,int next_point[][2],int& nextColor);
void fallingPiece(float& timer, float& delay, int& colorNum, int&z, int& y_disp, int point_3[][2],float K,int& n,int next_point[][2],int& nextColor)
{
	//int z;
    if (timer>delay)
    {
   		//game_end();
        for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;
            //counter++;
                             //How much units downward
        }
        y_disp+=1;
        if (!anamoly())
        {
        	for(int i=0;i<4;i++)
        		gameGrid[point_2[i][1]][point_2[i][0]]= colorNum;
        	colorNum=nextColor;
        	nextColor=1+rand()%7;
        	srand(time(0));
            z=n;
            //--- Un-Comment this Part When You Make BLOCKS array---//

          	for (int i=0;i<4;i++)
            {
            	point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
            n=rand()%7;
			for (int i=0;i<4;i++)
   	 		{
    	  		    next_point[i][0] = BLOCKS[n][i] % 2;
       		        next_point[i][1] = BLOCKS[n][i] / 2;
        	}

            if (!shadow_limit(point_3))
        	{
			 	for (int i=0;i<4;i++)
		      	{
		      		point_3[i][0] = BLOCKS[z][i] % 2;
                  	point_3[i][1] = BLOCKS[z][i] / 2;
		      	}
			}
        }
        timer=0;
        delay=K;
       // counter++;
    }
}
/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

//....................DIFFICULTY FUNCTIONS DECREASES THE DELAY BY 20% AFTER 5 LINES CLEARED
void difficulty(int& lineCount,float& K, float& pitch);
void difficulty(int& lineCount,float& K, float& pitch)
{
	if(lineCount>=5)
	{
		K/=1.2;
		pitch+=0.1;
		lineCount=0;
	}
}

/*
bool levels(bool level)
{
	if(level)
		return 1;
	else
		return 0;
}
*/

// FUNCTION CALLED IN EVERY GAME LOOP TO DETERMINE IF BOMB IS FALLING
bool bomb_probability();
bool bomb_probability()
{
	int a=rand()%100000;
	if (a==0)
		return 1;
	else
		return 0;
}

//FUNCTION TO CHECK IF SHADOW OF THE BLOCK HAS REACHED A BLOCK OR GRID END
bool shadow_limit(int point_3[][2])
{
    for (int i=0;i<4;i++)
        if (point_3[i][0]<0 )
            return 0;
		else if (gameGrid[point_3[i][1]][point_3[i][0]])
            return 0;
    return 1;
}

//FUNCTION TO CHECK IF BOMB HAS GRID END
bool bomb_limit(int point_4[][2])
{
    for (int i=0;i<4;i++)
        if (point_4[i][0]<0 || point_4[i][0]>=M)
            return 0;
    return 1;
}

//FUNCTION TO CHECK IF BOMB HAS REACHED A BLOCK
bool bomb_touchdown(int point_4[][2]);
bool bomb_touchdown(int point_4[][2])
{
	for (int i=0;i<4;i++)
        if (gameGrid[point_4[i][1]][point_4[i][0]])
            return 0;
    return 1;
}

//OVERLOADED FUNCTION FOR FALLING SHADOW
void fallingPiece(int point_3[][2]);
void fallingPiece(int point_3[][2])
{
	for (int i=0;i<4;i++)
	{
		point_3[i][1]+=1;
    }
}

//FUNCTION TO DETERMINE HOW TO THE BOMB DESTROYS UPON TOUCHDOWN
bool destruction(int point_4[][2], int& bombColor);
bool destruction(int point_4[][2], int& bombColor)
{
	bool flag=false;
	if(!bomb_touchdown(point_4) && bomb_limit(point_4))
	{
		for (int i=0;i<4;i++)
		{
			if(bomb_limit(point_4))
			if(gameGrid[point_4[i][1]][point_4[i][0]]==bombColor)
			{
				flag=true;
			}
		}
		if(flag)
		{
			for(int i=0;i<M;i++)
				for(int j=0;j<N;j++)
					gameGrid[i][j] = 0;
			return 1;
		}
		else
		{
			if(bomb_limit(point_4))
				for (int i=0;i<4;i++)
				{
					gameGrid[point_4[i][1]][point_4[i][0]]=0;
					gameGrid[point_4[i][1]+1][point_4[i][0]]=0;
					gameGrid[point_4[i][1]+1][point_4[i][0]+1]=0;
					gameGrid[point_4[i][1]][point_4[i][0]+1]=0;
				}
			return 1;
		}
	}
	return 0;
}

//FUNCTION THAT DROPS BOMB AND DETERMINES ITS COLOR
void falling_bomb(int point_4[][2], float& b_timer,double& b_delay, int& bomb_rand, bool& bomb_prob, int& bombColor);
void falling_bomb(int point_4[][2], float& b_timer,double& b_delay, int& bomb_rand, bool& bomb_prob, int& bombColor)
{
	static int z=0;
	if (b_timer>b_delay)
	{
		for (int i=0;i<4;i++)
		{
		    point_4[i][1]+=1;
		}
		b_timer=0;
	}
	if(!bomb_limit(point_4) || destruction(point_4, bombColor))
	{
		for(int i=0;i<4;i++)
		{
			point_4[i][0]=-10;
			point_4[i][1]=-10;
		}
		bomb_rand=rand()%N;
		z++;
		if(bomb_prob)
		{
			for(int i=0;i<4;i++)
			{
				point_4[i][0]=bomb_rand;
				point_4[i][1]=0;
			}
			bombColor=1+rand()%7;
		}
	}
}

//LEFT SHIFT FUNCTION
void shiftL(int& delta_x,int& x_disp);
void shiftL(int& delta_x,int& x_disp)
{
	bool flag=false;
	for (int i=0;i<4;i++)
	{
        if (point_1[i][0]<1)
            flag=true;
    }
    if(!flag)
    {
		for (int i=0;i<4;i++)
		{
		        point_2[i][0]=point_1[i][0];
		        point_2[i][1]=point_1[i][1];
		        point_1[i][0]+=delta_x;                   //LEFT SHIFT
		}
		if(!anamoly())
		{
			for (int i=0;i<4;i++)
			{
			  	point_2[i][0]=point_1[i][0];
				point_2[i][1]=point_1[i][1];
			   	point_1[i][0]-=delta_x;
			}
		}
		else
			x_disp+=delta_x;
		delta_x=0;
	}

}

//RIGHT SHIFT FUNCTION
void shiftR(int& delta_x,int& x_disp);
void shiftR(int& delta_x,int& x_disp)
{
	bool flag=false;
	for (int i=0;i<4;i++)
	{
        if (point_1[i][0]>=N-1)
            flag=true;
    }
    if(!flag)
    {
		for (int i=0;i<4;i++)
		{
		        point_2[i][0]=point_1[i][0];
		        point_2[i][1]=point_1[i][1];
		        point_1[i][0]+=delta_x;                   //RIGHT SHIFT
		}
		if(!anamoly())
		{
			for (int i=0;i<4;i++)
			{
			  	point_2[i][0]=point_1[i][0];
				point_2[i][1]=point_1[i][1];
			   	point_1[i][0]-=delta_x;
			}
		}
		else
			x_disp+=delta_x;
		delta_x=0;
	}
}

//FUNCTION TO DETERMINE IF LINES HAVE BEEN CLEARED AND RE ADJUST THE GRID(also determines no of lines cleared)
int lineCheck();
int lineCheck()
{
	int lines=0;
	int count=0,temp;
	for (int i=0;i<M;i++)
	{
		count=0;
		for(int j=0;j<N;j++)
		{
			if(gameGrid[i][j]>0)
				count++;
		}
		if(count==N)
		{
			for(int j=0;j<N;j++)
			{
				gameGrid[i][j]=0;
				//reFlag=true;
			}
			for (int k=M;k>0;k--)
			{
				if(k>=i)
					continue;
				for(int l=0;l<N;l++)
				{
					if(gameGrid[k][l]>0)
					{
						temp=gameGrid[k][l];
						gameGrid[k][l]=0;
						gameGrid[k+1][l]=temp;
					}
				}
	  	  	}
	  	  	lines++;
		}
    }
    return lines;
}

//FUNCTION TO SEE IF BLOCK IS NEAR THE RIGHT
bool rotation_limit_R();
bool rotation_limit_R()
{
	for (int i=0;i<4;i++)
        if (point_1[i][0]>=N)
            return 0;
    return 1;
}

//FUNCTION TO SEE IF BLOCK IS NEAR THE LEFT
bool rotation_limit_L();
bool rotation_limit_L()
{
	for (int i=0;i<4;i++)
        if (point_1[i][0]<0)
            return 0;
    return 1;
}

//FUNCTION THAT USES ROTATION ARRAY TO ROTATE THE BLOACK AND ADD THE DISPLACEMENTS
void rotating(int z, int& r, int& x_disp, int& y_disp);
void rotating(int z, int& r, int& x_disp, int& y_disp)
{
	int x=0;
	int temp;
	for(int i=0;i<4;i++)
		if(point_1[i][1]<=0)
		{
			x_disp=0;
			y_disp=0;
		}
	switch(z)
	{
		case 0:
			if(r==0)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] =x++ ;
					point_1[i][1] =point_1[2][1];
				}
				r++;
				x=0;
			}
			else if(r==1)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][1] += x++ ;
					point_1[i][0] =point_1[2][0] ;
				}
				r++;
				x=0;
			}
			else if(r==2)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] =x++;
					point_1[i][1] =point_1[2][1] ;
				}
				r++;
				x=0;
			}
			else if(r==3)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][1] +=x++;
					point_1[i][0] =point_2[2][0];
				}
				r=0;
				x=0;
			}
			break;
		case 1:
			if(r==0)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = J[0][i] % 2;
               		point_1[i][1] = J[0][i] / 2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}

			else if(r==1)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = J[1][i]%2;
               		point_1[i][1] = J[1][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==2)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = J[2][i]%2;
               		point_1[i][1] = J[2][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==3)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = J[3][i]%2;
               		point_1[i][1] = J[3][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r=0;
				x=0;
				break;
			}
			break;
		case 2:
			if(r==0)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = L[0][i] % 2;
               		point_1[i][1] = L[0][i] / 2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}

			else if(r==1)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = L[1][i]%2;
               		point_1[i][1] = L[1][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==2)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = L[2][i]%2;
               		point_1[i][1] = L[2][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==3)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = L[3][i]%2;
               		point_1[i][1] = L[3][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r=0;
				x=0;
				break;
			}
			break;
		case 4:
			if(r==0)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = S[0][i] % 2;
               		point_1[i][1] = S[0][i] / 2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}

			else if(r==1)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = S[1][i]%2;
               		point_1[i][1] = S[1][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==2)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = S[2][i]%2;
               		point_1[i][1] = S[2][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==3)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = S[3][i]%2;
               		point_1[i][1] = S[3][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r=0;
				x=0;
				break;
			}
			break;
		case 5:
			if(r==0)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = Z[0][i] % 2;
               		point_1[i][1] = Z[0][i] / 2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}

			else if(r==1)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = Z[1][i]%2;
               		point_1[i][1] = Z[1][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==2)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = Z[2][i]%2;
               		point_1[i][1] = Z[2][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==3)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = Z[3][i]%2;
               		point_1[i][1] = Z[3][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r=0;
				x=0;
				break;
			}
			break;
		case 6:
			if(r==0)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = T[0][i] % 2;
               		point_1[i][1] = T[0][i] / 2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}

			else if(r==1)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = T[1][i]%2;
               		point_1[i][1] = T[1][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==2)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = T[2][i]%2;
               		point_1[i][1] = T[2][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					temp=point_1[i][1];
					point_1[i][1]=point_1[i][0];
					point_1[i][0]=temp;
               	}

               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r++;
				x=0;
				break;
			}
			else if(r==3)
			{
				for(int i=0;i<4;i++)
				{
					point_1[i][0] = T[3][i]%2;
               		point_1[i][1] = T[3][i]/2;
               	}
               	for(int i=0;i<4;i++)
				{
					point_1[i][0] += x_disp;
               		point_1[i][1] += y_disp;
               	}
				r=0;
				x=0;
				break;
			}
		default:
			break;


	}

}

//FUNCTION TO SEE IF GAME HAS ENDED
bool game_end();
bool game_end()
{
	bool flag=false;
	for(int i=0;i<N;i++)
	{
		if(gameGrid[1][i]>0)
			flag=true;
	}
	return flag;
}

//FUNCTION THAT DETERMINES IF A NEW BLOCK HAS BEEN DROPPED TO RESET DISPLACEMENTS AND ROTATIONS etc.
bool check_new_block();
bool check_new_block()
{
	bool a=false;
	for(int i=0;i<4;i++)
				if(point_1[i][1]<=0 )
					a=true;
	return a;
}

//FUNCTION THAT BRINGS THE BLOCK DOWN INSTANTLY IF SPACE IS PRESSED
void down(bool& space, float& delay);
void down(bool& space, float& delay)
{

    bool a=false;
	if(space)
	{
		delay=0.00000009;
		space=false;
		for(int i=0;i<4;i++)
			if(point_1[i][1]<=0)
				a=true;
	}
	if(a)
		delay=0.3;
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
