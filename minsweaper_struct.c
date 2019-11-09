
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

struct Cell
{
	char vissible_value [2];
	char actual_value [2];

};


int find(int move_x ,int move_y)
{
	int offset_bytes = (move_x + (move_y * VERTICAL_CELS)) * sizeof(struct Cell);    //hulpfunctie
	return offset_bytes;
}


void check_suroundings(struct Cell *ptr_field ,int x0,int y0 , int bombs_or_zeroes)
{
	if (bombs_or_zeroes == 1)    //check for bombs
	{
		int ctr = 0;
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{

				if (i < 0 || j < 0 || i > (HORIZONTAL_CELS - 1) || j > (VERTICAL_CELS - 1))
				{
					continue;
				}
				else if (*(ptr_field + find(i , j))->actual_value == 'B')
				{
					ctr++;
				}

			}
		}
		if (ctr == 0)
		{
			if (*(ptr_field + find(x0 , y0))->vissible_value == 'F')
			{
				mine_checker(ptr_field , x0 , y0);
			}
			else
			{
			*(ptr_field + find(x0 , y0))->vissible_value = '0';
			*(ptr_field + find(x0 , y0))->actual_value = ' ';
			mine_checker(ptr_field , x0 , y0);
			}

		}
		else
		{
			char return_value = ctr + '0';
			*(ptr_field + find(x0 , y0))->vissible_value = return_value;
			*(ptr_field + find(x0 , y0))->actual_value = return_value;
			 mine_checker(ptr_field , x0 , y0);
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
					*(ptr_field + find(i , j))->actual_value = ' ';
				}
				else if (i < 0 || j < 0 || i > (HORIZONTAL_CELS - 1) || j > (VERTICAL_CELS - 1))
				{
					continue;
				}
				else if (*(ptr_field + find(i , j))->vissible_value == 'F' ||*(ptr_field + find(i , j))->vissible_value == '0' || *(ptr_field + find(i , j))->actual_value == 'B')
				{
					continue;
				}
				else
				{
					check_suroundings(ptr_field , i , j , 1);
				}

			}
		}
	}
}
void mine_checker(struct Cell *ptr_field , int move_x, int move_y)
{

	if (*(ptr_field + find(move_x , move_y))->vissible_value == 'q' && !(*(ptr_field + find(move_x , move_y))->actual_value == 'B'))
	{
		check_suroundings(ptr_field , move_x , move_y , 1);
	}
	else if(*(ptr_field + find(move_x , move_y))->vissible_value == '0')
	{
		check_suroundings(ptr_field , move_x , move_y , 0);
	}
}

void update_field(struct Cell *ptr_field, int move_x, int move_y)
{
	if (*(ptr_field + find(move_x , move_y))->actual_value == 'B')
	{
				printf("you lost lost, play again Y/N");
				char action;
				scanf("%c", &action);
				if (action == 'Y')
				{
					print_grid(ptr_field, 1);
					int x , y;
					printf("\n choose an x coordinate \n");
					scanf("%d"  , &x);
					printf("\n choose an y coordinate \n");
					scanf("%d"  , &y);
					place_mines(x , y , ptr_field);
				}
				else if(action == 'N')
				{
					printf("\n bye bye");
				}
				else
				{
					printf("\n write correctly");
					update_field(ptr_field , move_x , move_y);
				}

	}
	else
	{
		mine_checker(ptr_field, move_x , move_y);
		print_grid(ptr_field, 0);
		make_move(ptr_field);


	}
}

int el_ctr(char el , struct Cell *ptr_field ,int vis_or_act)
{
	int ctr = 0;
	for (int i = 0 ; i < VERTICAL_CELS; i++)
	{
		for (int j = 0 ; j < HORIZONTAL_CELS; j++)
		{
			if (vis_or_act == 1)
			{
				if (el == *(ptr_field + find(i , j))->vissible_value)
				{
					ctr++;
				}
			}
			else if (vis_or_act == 2)
			{
				if (el == *(ptr_field + find(i , j))->vissible_value && *(ptr_field + find(i , j))->actual_value == 'B')
				{
					ctr++;
				}
			}
			else
			{
				if (el == *(ptr_field + find(i , j))->actual_value)
				{
					ctr++;
				}
			}

		}
	}
	return ctr;
}


void make_move(struct Cell *ptr_field)
{
	if (el_ctr('q' , ptr_field , 0) == 0 || el_ctr('F', ptr_field, 2) == TOTAL_BOMBS)
	{
		printf("\n you won , wanna play again, write Y/N?");
		char action;
		scanf("%c", &action);
		if (action == 'Y')
		{
			print_grid(ptr_field, 1);
			int x , y;
			printf("\n choose an x coordinate \n");
			scanf("%d"  , &x);
			printf("\n choose an y coordinate \n");
			scanf("%d"  , &y);
			place_mines(x , y , ptr_field);
		}
		else if(action == 'N')
		{
			printf("\n bye bye");
		}
		else
		{
			printf("\n write correctly");
			make_move(ptr_field);
		}


	}
	else
	{
		char action;
		printf("\n P will show field with bombs, N is for next move and F for a flag\n");
		printf("\n choose an action type F , P or R\n");
		scanf("%c", &action);
		if (action == 'F')
		{
			char   i , j ;
			int x , y ;
			printf("\n choose an x coordinate");
			getchar();
			i = getchar();
			printf("\n choose an y coordinate");
			getchar();
			j = getchar();
			x = i - '0';
			y = j - '0';
			printf("\n x=%d\n" , x);
			printf("\n y=%d\n" , y);
			if (*(ptr_field + find (x , y))->vissible_value == 'F')
			{
				if (*(ptr_field + find (x , y))->actual_value == 'B')
				{
					*(ptr_field + find (x , y))->vissible_value = 'q';
					print_grid(ptr_field , 0);
					make_move(ptr_field);
				}
				else if (*(ptr_field + find (x , y))->actual_value == 'q')
				{
					*(ptr_field + find (x , y))->vissible_value = 'q';
					print_grid(ptr_field , 0);
					make_move(ptr_field);
				}
				else if (*(ptr_field + find (x , y))->actual_value == ' ')
				{
					*(ptr_field + find (x , y))->vissible_value = '0';
					print_grid(ptr_field , 0);

					make_move(ptr_field);
				}
				else
				{
					*(ptr_field + find (x , y))->vissible_value = *(ptr_field + find (x , y))->actual_value;
					mine_checker(ptr_field , x, y);
					print_grid(ptr_field , 0);
					make_move(ptr_field);
				}

			}
			else if (el_ctr('F' , ptr_field, 1) > TOTAL_BOMBS)
			{
				printf("\n please remove a flag all flags are set, not all of them pinpoint bombs \n");
				make_move(ptr_field);
			}
			else
			{
				*(ptr_field + find(x , y))->vissible_value = 'F';
				print_grid(ptr_field , 0);
				make_move(ptr_field);
			}

		}

		if (action == 'P')
		{
			print_grid(ptr_field , 6896);
			make_move(ptr_field);
		}
		else if (action == 'R')
		{
			int x , y;
			printf("\n choose an x coordinate \n");
			scanf("%d"  , &x);
			printf("\n choose an y coordinate \n");
			scanf("%d"  , &y);
			update_field(ptr_field , x , y);
		}
		else
		{
			printf("\n write correctly \n");
			make_move(ptr_field);
		}


	}
}

void print_grid(struct Cell *ptr_field , int actual)
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
			if (actual == 0)
			{
			printf ("|%c|" , *(ptr_field + find(j, i))->vissible_value);
			}
			else if (actual == 1)
			{
				*(ptr_field + find(j, i))->vissible_value = 'q';
				*(ptr_field + find(j, i))->actual_value = 'q';
				printf ("|%c|" , *(ptr_field + find(j, i))->vissible_value);
			}
			else
			{
			printf ("|%c|" , *(ptr_field + find(j, i))->actual_value);
			}
		}

	}
	printf("\n");
	printf("printed");
	printf("\n \n");
}

 void place_mines(int first_move_x, int first_move_y, struct Cell *ptr_field)
{
	int i = 0;
	while (i != TOTAL_BOMBS)
	{
		int random_x = rand() % (HORIZONTAL_CELS);
		int random_y = rand() % (VERTICAL_CELS);
		if ((random_x == first_move_x  || random_x == first_move_x + 1 || random_x == first_move_x - 1) &&
			(random_y == first_move_y || random_y == first_move_y - 1 || random_y == first_move_y + 1 ))
		{
			continue;
		}
		else if (*(ptr_field + find(random_x , random_y))->actual_value == 'B')
		{
			continue;
		}
		else
		{
			*(ptr_field + find(random_x , random_y))->actual_value = 'B';
			*(ptr_field + find(random_x , random_y))->vissible_value = 'q';
			i++;
		}


	}
	update_field(ptr_field , first_move_x , first_move_y);


}


int main(void)
{
	srand(time(NULL));
	struct Cell field[HORIZONTAL_CELS][VERTICAL_CELS];
	print_grid(&field, 1);     //essential for adressing al characters
	int x , y;
	printf("\n choose an x coordinate \n");
	scanf("%d"  , &x);
	printf("\n choose an y coordinate \n");
	scanf("%d"  , &y);
	place_mines(x, y,&field);

	return 0;
}
//https://stackoverflow->com/questions/9653072/return-a-struct-from-a-function-in-c
