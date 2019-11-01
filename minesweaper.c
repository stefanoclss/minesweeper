/*
 ============================================================================
 Name        : minesweaper.c
 Author      : Stefano_Claes
 Version     :
 Copyright   : Your copyright notice
 Description : Minesweaper, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HORIZONTAL_CELS 10
#define VERTICAL_CELS 10
#define TOTAL_BOMBS 30

//enum Cell_posibilities
//	{
//	'0', '1' , '2', '3', '4', '5', '6', '7', '8', 'F', 'B'
//	};

struct cell
{
	char vissible_value;
	char actual_value;
	int x;
	int y;
};

//2)implement to see al vissible and actual values on the screen goto line 180





char make_start_grid(int rows, int columns, char grid[HORIZONTAL_CELS][HORIZONTAL_CELS])
{
	//int field[rows][columns];
	printf("   ");   //to align all stuff
	for (int n= 0; n < columns ; n++)      //print all column numbers
	{
		printf("|%d|", n);
	}
	printf("\n");
	printf("   ");   //to align all stuff
	for (int n= 0; n < columns ; n++)      //print a separating line
	{
		printf("|-|");
	}

	for (int i=0; i<rows; i++)
	{
		printf("\n");
		printf("%d |", i);
		for (int j=0; j<columns ; j++)
		{
			grid[i][j] = 'q';
			printf("|%c|", grid[i][j]);
		}
	}
	return grid;
}

void print_grid_with_mines(char grid[HORIZONTAL_CELS][VERTICAL_CELS])
{
	printf("   ");   //to align all stuff
	for (int n= 0; n < HORIZONTAL_CELS ; n++)      //print all column numbers
	{
		printf("|%d|", n);
	}
	printf("\n");
	printf("   ");   //to align all stuff
	for (int n= 0; n < HORIZONTAL_CELS ; n++)      //print a separating line
	{
		printf("|-|");
	}

	for (int i=0; i<VERTICAL_CELS; i++)
	{
		printf("\n");
		printf("%d |", i);
		for (int j=0; j< HORIZONTAL_CELS ; j++)
		{
			printf("|%c|", grid[i][j]);
		}
	}
	printf("\n");
	printf("\n");
	printf("\n");
}

char check_suroundings(char grid[HORIZONTAL_CELS][VERTICAL_CELS],int x0,int y0 , int bombs_or_zeroes)
{
	if (bombs_or_zeroes == 1)    //check for bombs
	{
		int ctr = 0;
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{

				if (i < 0 || j < 0 || i > (HORIZONTAL_CELS - 1 )|| j > (VERTICAL_CELS - 1))
				{
					continue;
				}
				else if (grid[i][j] == 'B')
				{
					ctr++;
				}

			}
		}
		if (ctr == 0)
		{
			grid[x0][y0] = '0';
			return mine_checker(grid , x0 , y0);

		}
		else
		{
			char return_value = ctr + '0';
			grid[x0][y0] = return_value;
			return mine_checker(grid , x0 , y0);
		}

	}
	else
	{
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{
				if (i == x0 && j == y0)
				{
					continue;
				}
				else if (i < 0 || j < 0 || i > HORIZONTAL_CELS || j > VERTICAL_CELS)
				{
					continue;
				}
				else if (grid[i][j] == '0' || grid[i][j] == 'B')
				{
					continue;
				}
				else
				{
					printf("\n hier \n");
					check_su(roundings(grid , i , j , 1);
				}
			}
		}
	}
}

void mine_checker(char grid[HORIZONTAL_CELS][VERTICAL_CELS], int move_x, int move_y)
{
	if (grid[move_x][move_y] == '0' || grid[move_x][move_y] == 'q')
	{
		check_suroundings(grid , move_x , move_y , 0);
	}
}

void update_field(char grid[HORIZONTAL_CELS][VERTICAL_CELS], int move_x, int move_y)
{
	if (grid[move_x][move_y] == 'B')
	{
		printf("you lost loser, make the loop complete");
	}
	else
	{
		mine_checker(grid, move_x , move_y);
		printf("\n update_field \n");
		print_grid_with_mines(grid);
		make_move(grid);


	}
}

void make_move(char grid[HORIZONTAL_CELS][VERTICAL_CELS])
{

	int x , y;
	printf("\n choose an x coordinate \n");
	scanf("%d"  , &x);
	printf("\n choose an y coordinate \n");
	scanf("%d"  , &y);
	update_field(grid , x , y);
}

void place_mines(int first_move_x, int first_move_y, char grid[HORIZONTAL_CELS][VERTICAL_CELS])
{
	int i = 0;
	while (i != TOTAL_BOMBS)
	{
		int random_x = rand() % (HORIZONTAL_CELS);
		int random_y = rand() % (VERTICAL_CELS);
		if ((random_x == first_move_x  || random_x == first_move_x + 1 || random_x == first_move_x - 1) &&
			(random_y == first_move_y || random_y == first_move_y - 1 || random_y == first_move_y + 1 ))
		{
			printf("\n");
			printf("recalculations_NUMBER");
			printf("\n");
		}
		else if (grid[random_x][random_y] == 'B')
		{
			printf("\n");
			printf("recalculations_BOMB");
			printf("\n");
		}
		else
		{
			grid[random_x][random_y] = 'B';
			i++;
		}


	}
	grid[first_move_x][first_move_y] = '0';
	print_grid_with_mines(grid);
	printf("\n");
	printf("\n");
	update_field(grid, first_move_x, first_move_y);




}




int main(void) {
//	char x;
//	char y;
	char grid[HORIZONTAL_CELS][VERTICAL_CELS];
	make_start_grid(HORIZONTAL_CELS, VERTICAL_CELS, grid);     //essential for adressing al characters
//	printf("\n");
//	printf("please choose your x starting point(between 1 , 5");
//	printf("\n");
//	x = getchar();     //write if to make more robust
//	int begin_x = x - '0';
//	printf("\n");
//	printf("please choose your y starting point(between 1 , 5");
//	printf("\n");
//	y = getchar();     //write if to make more robust
//	y = getchar();     //write if to make more robust
//	int begin_y = y - '0';
	place_mines(2, 2, grid);






	return 0;
}
