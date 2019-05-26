/*-----------------------------------------------------------------------------------------------------
Ball / Object Hit: Before start create user of player with minimal information. The game is simple one
or more objects will be moving on the screen, user has to hit them with some specified object. For
each hit give points. After scoring some points, enter to next stage with increased speed of objects
and more no of objects. Store game and results into separate files.
-------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <process.h> 
#include <conio.h> 
#include <string> 
#include <fstream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
using namespace std;
int total_scores=0,high_scores=0,final_scores,lives=2;	//change the value of lives to anyone you want to change for whole game
												/*used global variables just because I had to pass them through each function,
												but there are too many arguments already used inmy function definitions. so i
												decided to declare them as global variables*/
void gotoxy(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}
#define LEFT 75			//limit for slider
#define RIGHT 77		
#define UPLIMIT 2		//limits for ball to bounce back
#define LOWLIMIT 40
#define LEFTLIMIT 1
#define RIGHTLIMIT 42
#define score1 100		//these are the scores limits for the levels of my game. I have included 5 stages with increasing speed
#define score2 200
#define score3 300
#define score4 400
#define score5 500
#define time 100

	void drawObject_01(int x, int y){			//i used this function to draw a static object to display the scores on the screen ata a fixed
	gotoxy(x, y);							//point. If i don't use this,,,,scores will also move on the screen
	cout << "|";
	}

	void drawObject(int x, int y){			//this function will draw the balls on the screen
		gotoxy(x, y);
		cout << "/\\";
		gotoxy(x, y+1);
		cout << "\\/";
	}
//-----------------------------------------------------------------	
	int instructions(char c)
	{
		string message="\n\t\t\t\t\tWelcome to ball hit game.\n\t\t\t\t\t_________________________\n\n\t\t\tPress space to skip instructions\n\n\n\t\t\tPress C to watch video tutorial\n\nInstructions:\n\t\tIn this game,different objects are moving on the screen with increasing speed.\nThey are trying to fall down,But you will have to prevent them from falling. \n\n>>>>you will have to use LEFT/RIGHT arrow keys to move the slab with normal speed or\n CTRL + LEFT/RIGHT with faster speed to prevent the ball from falling.\nEach hit of ball will increase your scores with a figure of \"10\"\n\n\nThere are 5 different levels with more and more difficulties. All you need to do is to pass \nthe level to break the record of highest scores.\n\n\n\nFollowing are the scores at which each of the level will be finished\nLevel 1 : 100 scores\nLevel 2 : 200 scores\nLevel 3 : 300 scores\nLevel 4 : 400 scores\nLevel 5 : 500 scores\n\n\n\t\t\t\t\tGood Luck!\n\n\t\t\t\t\tPress any key to play or Press C to watch video\n";
		char *array,q;		//declaring this array to show instructions character by character
		array=new char[message.length()];
		for(int i=0;i<message.length();i++)
		{
			array[i]=message[i];
		}
		for(int i=0;i<message.length();i++)
		{	
			cout<<array[i];
			Sleep(20);
			if (kbhit()){
			q=getch();
			if (q==' ')
			{
				system("cls");
				cout<<"Press any key to continue\n";
				break;
			}
			if (q=='c')
			{
				return true;
			}
			else continue;
			}
			if(i==309)
			system("pause>NUL");
			if(i==532)
			system("pause>NUL");
			if(i==675)
			system("pause>NUL");
		}
		delete []array;
		cout<<"\n\n\t\t\t\t";
		q=getch();
			if (q=='c')
			{
				system("cls");
				return true;
			}
			system("cls");
		return false;
	}
//-----------------------------------------------------------------	
	void hideObject(int x, int y){			//this function will hide the position of the balls for a moment until the loop
		gotoxy(x, y);						//completes its one cycle
		cout << "  ";
		gotoxy(x, y + 1);
		cout << "  ";
	}
//-----------------------------------------------------------------	
	void clear_record()						//this function is used to clear the previous record if the user is new
	{
		remove("records.txt");
		ofstream out("records.txt");
		out<<0;
		out.close();
	}
//-----------------------------------------------------------------	
	void reset_scores()						//this function will reset the values in the score files if the user is new
	{										//or want to play the game from start
		ofstream out("records.txt");
		out<<"0";
		out.close();
		ofstream out1("total_scores.txt");
		out1<<"0";
		out1.close();
	}
//-----------------------------------------------------------------	
	int check_scores(int runs)				//this function reads the score values if system has a previous user to play the game
	{
		int old_scores=0;
		ifstream in("records.txt");
		while (!in.eof())
		{
			in>>old_scores;
			runs=old_scores;
		}
		in.close();
		return runs;
	}
//-----------------------------------------------------------------	
	int check_total_scores(int total_scores)		//this function will check the total scores of a user in a sessoin
	{
		int old_scores=0;
		ifstream in("total_scores.txt");
		while (!in.eof())
		{
			in>>old_scores;
			total_scores=old_scores;
		}
		in.close();
		return total_scores;
	}
	int create_user(string name);
//-----------------------------------------------------------------	
	int check_high_scores(int high_scores,string user_name)		//this function will read the high_scores.txt file to read highest scores ever made by a user
	{
		int old_scores=0;
		ifstream in("high_scores.txt");
		if(!in)
		{
			system("cls");
			cout<<"\n\nhigh_scores.txt file is missing\nYou have lost your previous progress\nplease start the game again to play from start.\n";
			create_user(user_name);
			remove("users.txt");
			exit(0);
		}
		while (!in.eof())
		{
			in>>old_scores;
			high_scores=old_scores;
		}
		in.close();
		return high_scores;
	}
//-----------------------------------------------------------------	
	int create_user(string name)		//if there is no previous user or the user wants to play from start,this function will be used
	{									//to create a new user
		ofstream out("users.txt");
		out<<name;
		out.close();
		ofstream out1("high_scores.txt");
		out1<<"0";
		out1.close();
		reset_scores();
	}
//-----------------------------------------------------------------	
	int check_user(string name)			//when the user type his name,this function will check if the user exists previously or not
	{									//>>>>>if yes,then displays a message to continue or play from start
		string user_name;				//>>>>>if no then call creat_user function to create a new user
		ifstream in("users.txt");
		char option;
		while(!in.eof())
		{
			getline(in,user_name);
			if(user_name==name)
			{
				while(option!='y' || option!='Y' || option!='n' || option!='N')
				{
					cout<<"user name already exists\nDo you want to continue your previous game?(Y/N)\n";
					option=getch();
					if(option=='y' || option=='Y')
					break;
					else if (option=='n' || option=='N')
					{
						create_user(name);
						reset_scores();
						break;
					}
					else 
					system("cls");
				}
				break;
			}
			else 
			create_user(name);
			reset_scores();
			break;
		}
		in.close();
	}
//---------------------------------------------------------------------------------
	void game_over()			//this function will display the game over message if the user failed to pass the score limit of a level
	{
		system("cls");
		system("color 4e");		//changing the color of screen and text for an instant
string a,b,c,d,e,f,g;
	
a="######       ###    ##     ## ########     #######  ##     ## ######## ########  ";
b="##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## ";
c="##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## ";
d="##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########  ";
e="##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##   ";
f="##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##  ";
g="######    ##     ## ##     ## ########     #######     ###    ######## ##     ## ";
		
			for(int j=0;j<a.length();j++)
			{
				cout<<a[j];
			}
			cout<<'\n';
			Sleep(time);
			for(int j=0;j<b.length();j++)
			{
				cout<<b[j];
			}
			cout<<'\n';
			Sleep(time);
			for(int j=0;j<c.length();j++)
			{
				cout<<c[j];
			}
			cout<<'\n';
			Sleep(time);
			for(int j=0;j<d.length();j++)
			{
				cout<<d[j];
			}
			cout<<'\n';
			Sleep(time);
			for(int j=0;j<e.length();j++)
			{
				cout<<e[j];
			}
			cout<<'\n';
			Sleep(time);
			for(int j=0;j<f.length();j++)
			{
				cout<<f[j];
			}
			cout<<'\n';
			Sleep(time);
			for(int j=0;j<g.length();j++)
			{
				cout<<g[j];
			}
			cout<<'\n';
			Sleep(time);
			Sleep(time);
			
			
			for(int i=0;i<10;i++)//this loop is being used for blinking the strings
			{
				system("cls");
				Sleep(time);
				cout<<a<<'\n';
				cout<<b<<'\n';
				cout<<c<<'\n';
				cout<<d<<'\n';
				cout<<e<<'\n';
				cout<<f<<'\n';
				cout<<g<<'\n';
				Sleep(time);
			}
		system("pause>nul");
		system("color 0f");		//reverting the color back to orignal one
		system("cls");
	}
//---------------------------------------------------------------------------------
	int print_scores(int scores)//this function will be used to print the scores of a user either highest or total
	{
		cout<<"\t\t\t\t\t    |\t\t Scores in this level :\t"<<scores<<'\n';
		cout<<"|\t\t\t\t\t    |\t\t Overall Total Scores :\t"<<total_scores<<'\n';
		cout<<"|\t\t\t\t\t    |\t\t Highest ever Scores :\t"<<high_scores<<'\n';
		cout<<"|\t\t\t\t\t    |\t\t Lives Left :\t"<<lives-1<<'\n';
	}
//---------------------------------------------------------------------------------
	int level_start(int level,string user_name)	//this function is used to display the countdown before new level + makes the boundary of the area
	{
		system("CLS");
		for(int j=5;j>0;j--)
		{
			cout<< "\n\n\n\n\n_________________________________\n";
			cout<< "|                               |\n";
			cout<< "| level "<<level<<" starts in "<<j<<" seconds\t|\n";
			cout<< "|                               |\n";
			cout<< "_________________________________\n";
			Sleep(1000);
			system("CLS");
		}
	cout << "Press Arrow Keys to move, press q to quit\tWelcome "<<user_name<<"!\n";
	cout<< "_____________________________________________\n";
	for(int j=0;j<40;j++)
	cout<< "|                                           |\n";
	cout<< "_____________________________________________\n";
	}	
//---------------------------------------------------------------------------------
	int write_high_scores()		//if the total scores of a user becomes greater than previous high scores,this function will write them in a file
	{
		if(total_scores>high_scores)
		{
			high_scores=high_scores+10;
			ofstream out2("high_scores.txt");
			out2<<total_scores;
			out2.close();
		}
	}
//---------------------------------------------------------------------------------
	int level_5(string s,string h,string user_name,int scores,int x1,int x2,int x3,int x4,int x5,int y1,int y2,int y3,int y4, int y5,int incX,int incXX,int incXXX,
				int incXXXX,int incXXXXX,int incY,int incYY,int incYYY,int incYYYY,int incYYYYY,int x_hidden,int y_hidden,int x,int y,int i,int tries)
	{
		int level=5;
		tries=lives;
		level_start(level,user_name);
	int	speed=50;
	while (true){
		
		gotoxy(x, y);
		cout << s;
		if (kbhit())
		{
			gotoxy(x, y);
			cout << h;
			i = getch();
			if (i == 'q')	
			{
				break;
			}
			if(GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_CONTROL) && x>LEFTLIMIT+1) 
			{
				if(x-LEFTLIMIT<=7)
				x=x-3;
				else
				x=x-6;
			}
			else if(GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_CONTROL) && x<RIGHTLIMIT-7)
			{
				if(RIGHTLIMIT-x<=10)
				x=x+3;
				else
				x=x+6;
			}
			if (i == LEFT && x>LEFTLIMIT)
				{
					x = x - 3;
				}
			else if (i == RIGHT && x<RIGHTLIMIT-6)
			{
				x = x + 3;
			}
		}
		drawObject_01(x_hidden, y_hidden);
		print_scores(scores);
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(y2<LOWLIMIT)
		drawObject(x2, y2);
		if(y3<LOWLIMIT)
		drawObject(x3, y3);
		if(y4<LOWLIMIT)
		drawObject(x4, y4);
		if(y5<LOWLIMIT)
		drawObject(x5, y5);
		Sleep(speed);		
		hideObject(x1, y1);
		hideObject(x2, y2);
		hideObject(x3, y3);
		hideObject(x4, y4);
		hideObject(x5, y5);
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0; 
		if (x1>x-2 && x1<x+7) 
		{	
			if(x1>x-2 && x1<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1>x+3 && x1<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
	
		if (x2 == RIGHTLIMIT)	incXX = -1;
		if (x2 == LEFTLIMIT)	incXX = 1;
		if (y2 == LOWLIMIT )	incYY=0;
		if (x2>x-2 && x2<x+7)
		{	
			if(x2>x-2 && x2<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2>x+3 && x2<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y2 == UPLIMIT)	incYY = 1;
		x2 += incXX;
		y2 += incYY;
		
		if (x3 == RIGHTLIMIT)	incXXX = -1;
		if (x3 == LEFTLIMIT)	incXXX = 1;
		if (y3 == LOWLIMIT )	incYYY=0;
		if (x3>x-2 && x3<x+7) 
		{	
			if(x3>x-2 && x3<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					incXXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x3==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x3>x+3 && x3<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					incXXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y3 == UPLIMIT)	incYYY = 1;
		x3 += incXXX;
		y3 += incYYY;
		
		if (x4 == RIGHTLIMIT)	incXXXX = -1;
		if (x4 == LEFTLIMIT)	incXXXX = 1;
		if (y4 == LOWLIMIT )	incYYYY=0;
		if (x4 >x-2 && x4 <x+7) 
		{	
			if(x4>x-2 && x4<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y4==y-1)
				{
					incYYYY=-1;
					incXXXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x4==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y4==y-1)
				{
					incYYYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x4>x+3 && x4<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y4==y-1)
				{
					incYYYY=-1;
					incXXXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}

		if (y4 == UPLIMIT)	incYYYY = 1;
		x4 += incXXXX;
		y4 += incYYYY;
		
		if (x5 == RIGHTLIMIT)	incXXXXX = -1;
		if (x5 == LEFTLIMIT)	incXXXXX = 1;
		if (y5 == LOWLIMIT )	incYYYYY=0;
		if (x5 >x-2 && x5 <x+7) 
		{	
			if(x5>x-2 && x5<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y5==y-1)
				{
					incYYYYY=-1;
					incXXXXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x5==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y5==y-1)
				{
					incYYYYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x5>x+3 && x5<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y5==y-1)
				{
					incYYYYY=-1;
					incXXXXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}

		if (y5 == UPLIMIT)	incYYYY = 1;
		x5 += incXXXXX;
		y5 += incYYYYY;
		
		if(incY==0 || incYY==0 || incYYY==0 || incYYYY==0 || incYYYYY==0)
		speed=speed-1;
		if(speed<15)
		speed=15;
		
	if(incY==0 && incYY==0 &&incYYY==0 && incYYYY==0 && incYYYYY==0)
	{
		tries--;
		total_scores=final_scores;
		if(tries==0)
		{
			lives=0;
			system("color 3b");
			system("cls");
			cout<<"\n\n\t\tThanks for Playing the game\n\n\n\t\tPakistan zindabad\n";
			return 0;
		}
		else
		{
			lives=tries;
			game_over();
			break;
		}
	}
	write_high_scores();
	if(scores>=score5)
	{
				scores=0;
				final_scores=total_scores;
				remove("records.txt");
				remove("users.txt");
				break;
	}
	}

	return scores;
}	
//---------------------------------------------------------------------------------
	int level_4(string s,string h,string user_name,int scores,int x1,int x2,int x3,int x4,int y1,int y2,int y3,int y4,int incX,int incXX,int incXXX,
				int incXXXX,int incY,int incYY,int incYYY,int incYYYY,int x_hidden,int y_hidden,int x,int y,int i,int tries)
	{
		int level=4;
		tries=lives;
		level_start(level,user_name);	
	int speed=50;
	while (true){
		
		gotoxy(x, y);
		cout << s;
		if (kbhit())
		{
			gotoxy(x, y);
			cout << h;
			i = getch();
			if (i == 'q')	
			{
				break;
			}
			if(GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_CONTROL) && x>LEFTLIMIT+1) 
			{
				if(x-LEFTLIMIT<=7)
				x=x-3;
				else
				x=x-6;
			}
			else if(GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_CONTROL) && x<RIGHTLIMIT-7)
			{
				if(RIGHTLIMIT-x<=10)
				x=x+3;
				else
				x=x+6;
			}
			if (i == LEFT && x>LEFTLIMIT)
				{
					x = x - 3;
				}
			else if (i == RIGHT && x<RIGHTLIMIT-6)
			{
				x = x + 3;
			}
		}
		drawObject_01(x_hidden, y_hidden);
		print_scores(scores);
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(y2<LOWLIMIT)
		drawObject(x2, y2);
		if(y3<LOWLIMIT)
		drawObject(x3, y3);
		if(y4<LOWLIMIT)
		drawObject(x4, y4);
		
		Sleep(speed);
		
		hideObject(x1, y1);
		hideObject(x2, y2);
		hideObject(x3, y3);
		hideObject(x4, y4);
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0; 
		if (x1>x-2 && x1<x+7) 
		{	
			if(x1>x-2 && x1<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1>x+3 && x1<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
	
		if (x2 == RIGHTLIMIT)	incXX = -1;
		if (x2 == LEFTLIMIT)	incXX = 1;
		if (y2 == LOWLIMIT )	incYY=0;
		if (x2>x-2 && x2<x+7) 
		{	
			if(x2>x-2 && x2<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2>x+3 && x2<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y2 == UPLIMIT)	incYY = 1;
		x2 += incXX;
		y2 += incYY;
		
		if (x3 == RIGHTLIMIT)	incXXX = -1;
		if (x3 == LEFTLIMIT)	incXXX = 1;
		if (y3 == LOWLIMIT )	incYYY=0;
		if (x3>x-2 && x3<x+7) 
		{	
			if(x3>x-2 && x3<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					incXXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x3==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x3>x+3 && x3<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					incXXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}

		if (y3 == UPLIMIT)	incYYY = 1;
		x3 += incXXX;
		y3 += incYYY;
		
		if (x4 == RIGHTLIMIT)	incXXXX = -1;
		if (x4 == LEFTLIMIT)	incXXXX = 1;
		if (y4 == LOWLIMIT )	incYYYY=0;
		if (x4 >x-2 && x4 <x+7) 
		{	
			if(x4>x-2 && x4<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y4==y-1)
				{
					incYYYY=-1;
					incXXXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x4==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y4==y-1)
				{
					incYYYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x4>x+3 && x4<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y4==y-1)
				{
					incYYYY=-1;
					incXXXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}

		if (y4 == UPLIMIT)	incYYYY = 1;
		x4 += incXXXX;
		y4 += incYYYY;
		
		if(incY==0 || incYY==0 || incYYY==0 || incYYYY==0)
		speed=speed-1;
		if(speed<25)
		speed=25;
		
	if(incY==0 && incYY==0 &&incYYY==0 && incYYYY==0)
	{
		tries--;
		total_scores=final_scores;
		if(tries==0)
		{
			lives=0;
			system("color 3b");
			system("cls");
			cout<<"\n\n\t\tThanks for Playing the game\n\n\n\t\tPakistan zindabad\n";
			return 0;
		}
		else
		{
			lives=tries;
			game_over();
			break;
		}
	}
	write_high_scores();
	if(scores>=score4)
	{
		ofstream out("records.txt");
		out<<scores;
		out.close();
		final_scores=total_scores;
		ofstream out1("total_scores.txt");
		out1<<total_scores;
		out1.close();
		break;
	}
	}
	return scores;
}	
//---------------------------------------------------------------------------------
	int level_3(string s,string h,string user_name,int scores,int x1,int x2,int x3,int y1,int y2,int y3,int incX,int incXX,int incXXX,int incY,int incYY,
				int incYYY,int x_hidden,int y_hidden,int x,int y,int i,int tries)	
	{
			int level=3;
			tries=lives;
		level_start(level,user_name);	
	int speed=70;
	while (true){
		
		gotoxy(x, y);
		cout << s;
		if (kbhit())
		{
			gotoxy(x, y);
			cout << h;
			i = getch();
			if (i == 'q')	
			{
				break;
			}
			if(GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_CONTROL) && x>LEFTLIMIT+1) 
			{
				if(x-LEFTLIMIT<=7)
				x=x-3;
				else
				x=x-6;
			}
			else if(GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_CONTROL) && x<RIGHTLIMIT-7)
			{
				if(RIGHTLIMIT-x<=10)
				x=x+3;
				else
				x=x+6;
			}
			if (i == LEFT && x>LEFTLIMIT)
				{
					x = x - 3;
				}
			else if (i == RIGHT && x<RIGHTLIMIT-6)
			{
				x = x + 3;
			}
		}
		drawObject_01(x_hidden, y_hidden);
		print_scores(scores);
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(y2<LOWLIMIT)
		drawObject(x2, y2);
		if(y3<LOWLIMIT)
		drawObject(x3, y3);
		Sleep(speed);
		hideObject(x1, y1);
		hideObject(x2, y2);
		hideObject(x3, y3);
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0,incX=0;
		if (x1>x-2 && x1<x+7) 
		{	
			if(x1>x-2 && x1<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1>x+3 && x1<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
	
		if (x2 == RIGHTLIMIT)	incXX = -1;
		if (x2 == LEFTLIMIT)	incXX = 1;
		if (y2 == LOWLIMIT )	incYY=0;
		if (x2>x-2 && x2<x+7 )
		{	
			if(x2>x-2 && x2<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2>x+3 && x2<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y2 == UPLIMIT)	incYY = 1;
		x2 += incXX;
		y2 += incYY;
		
		if (x3 == RIGHTLIMIT)	incXXX = -1;
		if (x3 == LEFTLIMIT)	incXXX = 1;
		if (y3 == LOWLIMIT )	incYYY=0;
		if (x3>x-2 && x3<x+7) 
		{	
			if(x3>x-2 && x3<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					incXXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x3==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x3>x+3 && x3<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y3==y-1)
				{
					incYYY=-1;
					incXXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}

		if (y3 == UPLIMIT)	incYYY = 1;
		x3 += incXXX;
		y3 += incYYY;
		if(incY==0 || incYY==0 || incYYY==0)
		speed=speed-1;
		if(speed<25)
		speed=25;
		
	if(incY==0 && incYY==0 &&incYYY==0)
	{
		tries--;
		total_scores=final_scores;
		if(tries==0)
		{
			lives=0;
			system("color 3b");
			system("cls");
			cout<<"\n\n\t\tThanks for Playing the game\n\n\n\t\tPakistan zindabad\n";
			return 0;
		}
		else
		{
			lives=tries;
			game_over();
			break;
		}
	}
	write_high_scores();
	if(scores>=score3)
	{
		ofstream out("records.txt");
		out<<scores;
		out.close();
		final_scores=total_scores;
		ofstream out1("total_scores.txt");
		out1<<total_scores;
		out1.close();
		break;
	}
}
	return scores;
}
//---------------------------------------------------------------------------------
	int level_2(string s,string h,string user_name,int scores,int x1,int x2,int y1,int y2,int incX,int incXX,int incY,int incYY,int x_hidden,int y_hidden,
				int x,int y,int i,int tries)
	{
		int level=2;
		tries=lives;
		level_start(level,user_name);
	int speed=70;
	while (true){	
		gotoxy(x, y);
		cout << s;
		if (kbhit())
		{
			gotoxy(x, y);
			cout << h;
			i = getch();
			if (i == 'q')	
			{
				break;
			}
			if(GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_CONTROL) && x>LEFTLIMIT+1) 
			{
				if(x-LEFTLIMIT<=7)
				x=x-3;
				else
				x=x-6;
			}
			else if(GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_CONTROL) && x<RIGHTLIMIT-7)
			{
				if(RIGHTLIMIT-x<=10)
				x=x+3;
				else
				x=x+6;
			}
			if (i == LEFT && x>LEFTLIMIT)
				{
					x = x - 3;
				}
			else if (i == RIGHT && x<RIGHTLIMIT-6)
			{
				x = x + 3;
			}
		}
		drawObject_01(x_hidden, y_hidden);
		print_scores(scores);
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(y2<LOWLIMIT)
		drawObject(x2, y2);
		Sleep(speed);
		hideObject(x1, y1);
		hideObject(x2, y2);
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	
		{
			incY = 0;
			speed=40;
		}
		if (x1>x-2 && x1<x+7) 
		{	
			if(x1>x-2 && x1<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1>x+3 && x1<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
	
		if (x2 == RIGHTLIMIT)	incXX = -1;
		if (x2 == LEFTLIMIT)	incXX = 1;
		if (y2 == LOWLIMIT )
		{
			incYY = 0;
			speed=40;
		}
		if (x2>x-2 && x2<x+7) 
		{	
			if(x2>x-2 && x2<x+3)	//if the ball hits on the left side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2==x+3)		//if the ball hits on the center of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x2>x+3 && x2<x+7)		//if the ball hits on the right side of the paddle this condition will execute
			{
				if(y2==y-1)
				{
					incYY=-1;
					incXX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		if (y2 == UPLIMIT)	incYY = 1;
		x2 += incXX;
		y2 += incYY;
		
		speed=speed-1;
		if (speed<25)
		speed=25;
	if(incY==0 && incYY==0)
	{
		tries--;
		total_scores=final_scores;
		if(tries==0)
		{
			lives=0;
			system("color 3b");
			system("cls");
			cout<<"\n\n\t\tThanks for Playing the game\n\n\n\t\tPakistan zindabad\n";
			return 0;
		}
		else
		{
			lives=tries;
			game_over();
			break;
		}
	}
	write_high_scores();
	if(scores>=score2)
	{
		ofstream out("records.txt");
		out<<scores;
		out.close();
		final_scores=total_scores;
		ofstream out1("total_scores.txt");
		out1<<total_scores;
		out1.close();
		break;
	}
	}
	return scores;
}
//---------------------------------------------------------------------------------
	int level_1(string s,string h,string user_name,int scores,int x1,int y1,int incX,int incY,int x_hidden,int y_hidden,int x,int y,int i,int tries)
	{
		int level=1;
		tries=lives;
		level_start(level,user_name);
	int speed=80;
	while (true){	
		gotoxy(x, y);
		cout << s;
		if (kbhit())
		{
			gotoxy(x, y);
			cout << h;
			i = getch();
			if (i == 'q')	
			{
				break;
			}
			if(GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_CONTROL) && x>LEFTLIMIT+1) 
			{
				if(x-LEFTLIMIT<=7)
				x=x-3;
				else
				x=x-6;
			}
			else if(GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_CONTROL) && x<RIGHTLIMIT-7)
			{
				if(RIGHTLIMIT-x<=10)
				x=x+3;
				else
				x=x+6;
			}
			if (i == LEFT && x>LEFTLIMIT+1)
				{
					x = x - 3;
				}
			else if (i == RIGHT && x<RIGHTLIMIT-7)
			{
				x = x + 3;
			}
		}
		drawObject_01(x_hidden, y_hidden);
		print_scores(scores);
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		Sleep(speed);
		hideObject(x1, y1);
		
		if (x1>x-2 && x1<x+7) 
		{	
			if(x1>x-2 && x1<x+3)
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1==x+3)
			{
				if(y1==y-1)
				{
					incY=-1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
			else if(x1>x+3 && x1<x+7)
			{
				if(y1==y-1)
				{
					incY=-1;
					incX=1;
					scores=scores+10;
					total_scores=total_scores+10;
				}
			}
		}
		
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0;
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
	if(incY==0 )
	{
		tries--;
		total_scores=final_scores;
		if(tries==0)
		{
			lives=0;
			system("color 3b");
			system("cls");
			cout<<"\n\n\t\tThanks for Playing the game\n\n\n\t\tPakistan zindabad\n";
			return 0;
		}
		else
		{
			lives=tries;
			game_over();
			break;
		}
	}
	write_high_scores();
	if(scores>=score1)
	{
		ofstream out("records.txt");
		out<<scores;
		out.close();
		final_scores=total_scores;
		ofstream out1("total_scores.txt");
		out1<<total_scores;
		out1.close();	
		break;
	}
	}
	return scores;
}
//----------------------------------------------------------------------------------
	int call_level( string s,string h,string user_name,int scores,int x1,int x2,int x3,int x4,int x5,int y1,int y2,int y3,int y4,	
					int y5,int incX,int incXX,int incXXX,int incXXXX,int incXXXXX,int incY,int incYY,int incYYY,int incYYYY,
					int incYYYYY,int x_hidden,int y_hidden,int tries);		//this was a definition of a prototype function described below
	int play_again( string s,string h,string user_name,int scores,int x1,int x2,int x3,int x4,int x5,int y1,int y2,int y3,int y4,
					int y5,int incX,int incXX,int incXXX,int incXXXX,int incXXXXX,int incY,int incYY,int incYYY,int incYYYY,
					int incYYYYY,int x_hidden,int y_hidden,int tries)		//this function will ask user to play again if he/she failed to pass the level
	{
		char choice;
	while(choice!='y' || choice!='Y' || choice!='n' || choice!='N')
	{
		cout<<"\n\n\n\tDo you want to play again(Y/N)\n";
		choice=getch();
		if(choice=='Y' || choice=='y')
		{
			ifstream in("records.txt");
			in>>scores;
			in.close();
			call_level(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
			break;
		}
		else if(choice=='N' || choice=='n')
		{
			system("CLS");
			cout<<"\n\n\t\tThanks for playing such a nice game\n";
			system("PAUSE>nul");
			break;
		}
		else
			system("cls");
	}
	}
//----------------------------------------------------------------------------------
	int call_level( string s,string h,string user_name,int scores,int x1,int x2,int x3,int x4,int x5,int y1,int y2,int y3,int y4,
					int y5,int incX,int incXX,int incXXX,int incXXXX,int incXXXXX,int incY,int incYY,int incYYY,int incYYYY,
					int incYYYYY,int x_hidden,int y_hidden,int tries)		//this function will check the scores and take user to that specific level/stage
	{
	int i=5, x=13, y=38;
	if (scores>=0 && scores<score1)
	{
		scores=0;
		scores=level_1(s,h,user_name,scores,x1,y1,incX,incY,x_hidden,y_hidden,x,y,i,tries);
		if(lives==0) return 0;
		if(scores<score1)
		tries=play_again(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
	}
	if (scores>=score1 && scores<score2)
	{
		scores=0;
		scores=level_2(s,h,user_name,scores,x1,x2,y1,y2,incX,incXX,incY,incYY,x_hidden,y_hidden,x,y,i,tries);
		if(lives==0) return 0;
		if(scores<score2)
		play_again(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
	}
	
	if (scores>=score2 && scores<score3)
	{	
		scores=0;
		scores=level_3(s,h,user_name,scores,x1,x2,x3,y1,y2,y3,incX,incXX,incXXX,incY,incYY,incYYY,x_hidden,y_hidden,x,y,i,tries);
		if(lives==0) return 0;
		if(scores<score3)
		play_again(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
	}
	if (scores>=score3 && scores<score4)
	{
		scores=0;
		scores=level_4(s,h,user_name,scores,x1,x2,x3,x4,y1,y2,y3,y4,incX,incXX,incXXX,incXXXX,incY,incYY,incYYY,incYYYY,x_hidden,y_hidden,x,y,i,tries);
		if(lives==0) return 0;
		if(scores<score4)
		play_again(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
	}
	if (scores>=score4 && scores<score5)
	{
		scores=0;
		scores=level_5(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,x,y,i,tries);
		if(lives==0) return 0;
		if(scores<score5)
		play_again(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
	}
	if(scores>=score5)
	{
		system("CLS");
		cout<<"Congratulations\nYour have completed the game\n";
	}	
}
//-----------------------------------------------------------------------------
	void drawObject_left_ctrl(int x, int y){		//this function is showing pressed keys when showing video guide at start
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t\'\'\'\'\'\'\'\'\t\'\'\'\'\'\'\'\'\n|\t\t\t\t\t    |\t       |        |      | /      |\n|\t\t\t\t\t    |\t       |  CTRL  |      |<------ |\n|\t\t\t\t\t    |\t       |        |      | \\      |\n|\t\t\t\t\t    |\t\t\'\'\'\'\'\'\'\'\t\'\'\'\'\'\'\'\'\n|\n\n|\t\t\t\t\t    |\t\t\tPress CTRL + Left Arrow key to swipe Left with fast speed\n";
	}
//-----------------------------------------------------------------------------
	void drawObject_right_ctrl(int x, int y){		//same function as above but with different keys
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t\'\'\'\'\'\'\'\'\t\'\'\'\'\'\'\'\'\n|\t\t\t\t\t    |\t       |        |      |      \\ |\n|\t\t\t\t\t    |\t       |  CTRL  |  +   | ------>|\n|\t\t\t\t\t    |\t       |        |      |      / |\n|\t\t\t\t\t    |\t\t\'\'\'\'\'\'\'\'\t\'\'\'\'\'\'\'\'\n|\n\n|\t\t\t\t\t    |\t\tPress CTRL + Right Arrow key to swipe Right with fast speed\n";
	}
//-----------------------------------------------------------------------------
	void drawObject_right(int x, int y){			//same function as above but with different keys
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t--------\t\'\'\'\'\'\'\'\'\n|\t\t\t\t\t    |\t       | /      |      |      \\ |\n|\t\t\t\t\t    |\t       |<------ |      | ------>|\n|\t\t\t\t\t    |\t       | \\      |      |      / |\n|\t\t\t\t\t    |\t\t--------\t\'\'\'\'\'\'\'\'\n|\n\n|\t\t\t\t\t    |\t\t\tPress Right Arrow key to swipe Right\n";
	}
//-----------------------------------------------------------------------------
	void drawObject_left(int x, int y){				//same function as above but with different keys
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t\'\'\'\'\'\'\'\'\t--------\n|\t\t\t\t\t    |\t       | /      |      |      \\ |\n|\t\t\t\t\t    |\t       |<------ |      | ------>|\n|\t\t\t\t\t    |\t       | \\      |      |      / |\n|\t\t\t\t\t    |\t\t\'\'\'\'\'\'\'\'\t--------\n|\n\n|\t\t\t\t\t    |\t\t\tPress Left Arrow key to swipe Left\n";
	}
//-----------------------------------------------------------------------------
	void drawObject1(int x, int y){					//this function is drawing the buttons shown at start for video guide
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t--------\t--------\n|\t\t\t\t\t    |\t       | /      |      |      \\ |\n|\t\t\t\t\t    |\t       |<------ |      | ------>|\n|\t\t\t\t\t    |\t       | \\      |      |      / |\n|\t\t\t\t\t    |\t\t--------\t--------\n";
	}
//-----------------------------------------------------------------------------
	void drawObject2(int x, int y){					//this function is drawing the buttons shown at start for video guide
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t--------\t--------\n|\t\t\t\t\t    |\t       |        |      |      \\ |\n|\t\t\t\t\t    |\t       |  CTRL  |  +   | ------>|\n|\t\t\t\t\t    |\t       |        |      |      / |\n|\t\t\t\t\t    |\t\t--------\t--------\n";
	}
//-----------------------------------------------------------------------------
	void drawObject3(int x, int y){					//this function is drawing the buttons shown at start for video guide
	gotoxy(x, y);						
	cout << "|\t\t\t\t\t    |\t\t--------\t--------\n|\t\t\t\t\t    |\t       |        |      | /      |\n|\t\t\t\t\t    |\t       |  CTRL  |  +   |<------ |\n|\t\t\t\t\t    |\t       |        |      | \\      |\n|\t\t\t\t\t    |\t\t--------\t--------\n";
	}
//-----------------------------------------------------------------------------
	int level_start()			//this function is showing the border for each level outside the boundaries
	{
		system("CLS");
	cout<< "_____________________________________________\n";
	for(int j=0;j<40;j++)
	cout<< "|                                           |\n";
	cout<< "_____________________________________________\n";
	}

//-----------------------------------------------------------------------------
	int ctrl_left(string s,int scores,int x1,int y1,int x_hidden,int y_hidden) 		//showing ctrl+left video tutorial
	{
		int j=0;
		char i=5;int x=30, y=38;
   		int incX=1, incY=1;
		level_start();
		drawObject_left_ctrl(x_hidden,y_hidden);
		string h = "          ";
	int speed=80;
	while (true){		
		gotoxy(x, y);
		cout << s;		
		if (y1>=28 && x > LEFTLIMIT+12 && y1%4==0)
			{
				Sleep(10);
				gotoxy(x, y);
				cout<<h;
				x = x - 4;
			}	
		drawObject3(x_hidden, y_hidden);
		if(y1>=25 && y1%4==0)
		{
			Sleep(10);
			drawObject_left_ctrl(x_hidden, y_hidden);
			Sleep(20);
			drawObject3(x_hidden, y_hidden);
		}
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(j==25)
		{system("pause>nul");break;}
		Sleep(speed);
		hideObject(x1, y1);
		
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0,incX=0;
		if (x1>x-2 && x1<x+7) 
		{	if(y1==y-1)
			{
				incY=-1;
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
		j++;
		
	}
	system("cls");
}

//-----------------------------------------------------------------------------
	int ctrl_right(string s,int scores,int x1,int y1,int incX,int incY,int x_hidden,int y_hidden,int x,int y,char i)	//showing ctrl+right tutorial
	{
		int j=0;
		level_start();
		drawObject_right_ctrl(x_hidden,y_hidden);
		string h = "          ";
	int speed=80;
	while (true){		
		gotoxy(x, y);
		cout << s;		
		if (y1>=28 && x < RIGHTLIMIT-12)
			{
				if(y1%4==0)
				{
				Sleep(10);
				gotoxy(x, y);
				cout<<h;
				x = x + 5;
				}
			}	
		drawObject2(x_hidden, y_hidden);
		if(y1>=25 && y1%4==0)
		{
			Sleep(10);
			drawObject_right_ctrl(x_hidden, y_hidden);
			Sleep(20);

			drawObject2(x_hidden, y_hidden);
		}
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(j==61)
		{system("pause>nul");break;}
		Sleep(speed);
		hideObject(x1, y1);
		
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0,incX=0;
		if (x1>x-2 && x1<x+7) 
		{	if(y1==y-1)
			{
				incY=-1;
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
		j++;
		
	}
	system("cls");
}

//-----------------------------------------------------------------------------
	int move_left(string s,int scores,int x1,int y1,int incX,int incY,int x_hidden,int y_hidden,int x,int y,char i) //showing left button video tutorial
	{
		int j=0;
		level_start();
		drawObject_right(x_hidden,y_hidden);
		string h = "          ";
	int speed=80;
	while (true){		
		gotoxy(x, y);
		cout << s;		
		if (y1>=28 && x < RIGHTLIMIT-12)
			{
				Sleep(10);
				gotoxy(x, y);
				cout<<h;
				x = x + 2;
			}	
		drawObject1(x_hidden, y_hidden);
		if(y1>=25)
		{
			Sleep(10);
			drawObject_right(x_hidden, y_hidden);
			Sleep(20);	
			drawObject1(x_hidden, y_hidden);
		}
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(j==61)
		{system("pause>nul");break;}
		Sleep(speed);
		hideObject(x1, y1);
		
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0,incX=0;
		if (x1>x-2 && x1<x+7) 
		{	if(y1==y-1)
			{
				incY=-1;
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
		j++;
		
	}
	system("cls");
}
//-----------------------------------------------------------------------------
	int move_right(string s,int scores,int x1,int y1,int x_hidden,int y_hidden) //sjowing right button video tutorial
	{
		char i=5;int x=30, y=38;
		int j=0,incX=1, incY=1;
		drawObject_left(x_hidden,y_hidden);
		level_start();
		string h = "          ";
	int speed=80;
	while (true){		
		gotoxy(x, y);
		cout << s;		
		if (y1>=28 && x > LEFTLIMIT+17)
			{
				Sleep(10);
				gotoxy(x, y);
				cout<<h;
				x = x - 2;
			}	
		drawObject1(x_hidden, y_hidden);
		if(y1>=25)
		{
			Sleep(10);
			drawObject_left(x_hidden, y_hidden);
			Sleep(20);
			drawObject1(x_hidden, y_hidden);
		}
		if(y1<LOWLIMIT)
		drawObject(x1, y1);
		if(j==25)
		{system("pause>nul");break;}
		Sleep(speed);
		hideObject(x1, y1);
		
		if (x1 == RIGHTLIMIT)	incX = -1;
		if (x1 == LEFTLIMIT)	incX = 1;
		if (y1 == LOWLIMIT)	incY = 0,incX=0;
		if (x1>x-2 && x1<x+7) 
		{	if(y1==y-1)
			{
				incY=-1;
			}
		}
		if (y1 == UPLIMIT)	incY = 1;
		x1 += incX;
		y1 += incY;
		j++;
		
	}
	system("cls");
}
//-----------------------------------------------------------------------------
inline bool exists(const string& name) {			//I used this function to check the file if exist,If I don't use this to check and if there is no
    if (FILE *file = fopen(name.c_str(), "r")) {	//previous record, our system will be stuck there
        fclose(file);
        return true;
    } 
	else {
        return false;
    }
}
//-----------------------------------------------------------------------------
int main(){
	system("CLS");
	HWND console = GetConsoleWindow();								//setting best console colors and window size
  	RECT ConsoleRect;
  	GetWindowRect(console, &ConsoleRect); 
   	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1250, 750, TRUE);
   	
   	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("Color 0f");
	
	int scores;			//this is the core variable, Whole system is based upon this so this was the most important one
	string s = "=======";		//this is a slab shown in each stage to prevent falling of balls
	string h = "       ";		//this will replace the slab when a user enter a key to butify the program graphically
	int x1 = rand() % 19 + 1, y1 = rand() % 19+ 1, 	
		x2 = rand() % 19 + 1, y2 = rand() % 19 + 1,
		x3 = rand() % 19 + 1, y3 = rand() % 19 + 1,			//these are the variables to generate the random positions of the ball
		x4 = rand() % 19 + 1, y4 = rand() % 19 + 1,
		x5 = rand() % 19 + 1, y5 = rand() % 19 + 1,
			x_hidden=0,y_hidden=2, 					//these are static values not random because this is helpful to print scores on a fixed position
													//see drawObject_01 functoin for the detailed info about this
	incX=-1, incY=-1,
	incXX=1, incYY=1,
	incXXX=-1, incYYY=1,				//these will decide the initial direction of the balls
	incXXXX=1, incYYYY=-1,
	incXXXXX=1, incYYYYY=1;	
	char i=5;
	int x=13, y=38, tries=5;
	bool file_check=false;
	string user_name;
	bool c=false;
	c=instructions(c);
	if(c==true)
	{
		level_start();
		move_right(s,scores,x1,y1,x_hidden,y_hidden);
		move_left(s,scores,x1,y1,incX,incY,x_hidden,y_hidden,x,y,i);
		ctrl_right(s,scores,x1,y1,incX,incY,x_hidden,y_hidden,x,y,i);
		ctrl_left(s,scores,x1,y1,x_hidden,y_hidden);
	}
	cout<<"Enter your name\n";
	getline(cin,user_name);
	file_check=exists("users.txt");
	if (file_check==true)
	{
		check_user(user_name);				//if file users.txt exists
	}
	else if(file_check==false)
	{
		create_user(user_name);				//if the file do not exists
	}
	scores=check_scores(scores);
	total_scores=check_total_scores(total_scores);
	high_scores=check_high_scores(high_scores,user_name);
	system("pause");
	call_level(s,h,user_name,scores,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,incX,incXX,incXXX,incXXXX,incXXXXX,incY,incYY,incYYY,incYYYY,incYYYYY,x_hidden,y_hidden,tries);
	system("pause>nul");
}

