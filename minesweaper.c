
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
#define TOTAL_BOMBS 20

//enum Cell_posibilities
//	{
//	'0', '1' , '2', '3', '4', '5', '6', '7', '8', 'F', 'B'
//	};

struct Cell
{
	char vissible_value [2];
	char actual_value [2];

};







void check_suroundings(struct Cell *ptr_field ,int x0,int y0 , int bombs_or_zeroes)
{
	int offset_bytes;
	offset_bytes = (x0 + (y0 * VERTICAL_CELS)) * sizeof(struct Cell);
	if (bombs_or_zeroes == 1)    //check for bombs
	{
		int ctr = 0;
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{
				offset_bytes = (i + (j * VERTICAL_CELS)) * sizeof(struct Cell);     //zoekt de juiste buren op volgens de opbouw van de getekende matrix

				if (i < 0 || j < 0 || i > (HORIZONTAL_CELS - 1 )|| j > (VERTICAL_CELS - 1))
				{
					continue;
				}
				else if (*(ptr_field + offset_bytes)->actual_value == 'B')
				{
					ctr++;
				}

			}
		}
		offset_bytes = (x0 + (y0 * VERTICAL_CELS)) * sizeof(struct Cell);
		if (ctr == 0)
		{
			if (*(ptr_field + offset_bytes)->vissible_value == 'F')
			{
				mine_checker(ptr_field , x0 , y0);
			}
			else
			{
			*(ptr_field + offset_bytes)->vissible_value = '0';
			*(ptr_field + offset_bytes)->actual_value = ' ';
			mine_checker(ptr_field , x0 , y0);
			}

		}
		else
		{
			char return_value = ctr + '0';
			*(ptr_field + offset_bytes)->vissible_value = return_value;
			*(ptr_field + offset_bytes)->actual_value = return_value;
			 mine_checker(ptr_field , x0 , y0);
		}

	}
	else
	{
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{
				offset_bytes = (i + (j * VERTICAL_CELS)) * sizeof(struct Cell);
				if (i == x0 && j == y0)
				{
					*(ptr_field + offset_bytes)->actual_value = ' ';
				}
				else if (i < 0 || j < 0 || i > HORIZONTAL_CELS || j > VERTICAL_CELS)
				{
					continue;
				}
				else if (*(ptr_field + offset_bytes)->vissible_value == 'F' ||*(ptr_field + offset_bytes)->vissible_value == '0' || *(ptr_field + offset_bytes)->actual_value == 'B')
				{
					continue;
				}
				else
				{
					printf("\n hier \n");
					check_suroundings(ptr_field , i , j , 1);
				}

			}
		}
	}
}
void mine_checker(struct Cell *ptr_field , int move_x, int move_y)
{
	int offset_bytes;
	offset_bytes = (move_x + (move_y * VERTICAL_CELS)) * sizeof(struct Cell);
	if (*(ptr_field + offset_bytes)->vissible_value == 'q' && !(*(ptr_field + offset_bytes)->actual_value == 'B'))
	{
		check_suroundings(ptr_field , move_x , move_y , 0);
	}
	else if(*(ptr_field + offset_bytes)->vissible_value == '0' && !(*(ptr_field + offset_bytes)->actual_value == '0'))
	{
		check_suroundings(ptr_field , move_x , move_y , 0);
	}
}

void update_field(struct Cell *ptr_field, int move_x, int move_y)
{
	int offset_bytes;
	offset_bytes = (move_x + (move_y * VERTICAL_CELS)) * sizeof(struct Cell);
	printf("\n this is this value loser %c \n" ,*(ptr_field + offset_bytes)->actual_value);
	if (*(ptr_field + offset_bytes)->actual_value == 'B')
	{
				printf("you lost lost, play again Y/N");
				char action;
				scanf("%c", &action);
				if (action == 'Y')
				{
					make_start_grid(HORIZONTAL_CELS , VERTICAL_CELS , ptr_field);
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
		printf("\n update_field \n");
		print_grid(ptr_field, 0);
		make_move(ptr_field);


	}
}

int el_ctr(char el , struct Cell *ptr_field ,int vis_or_act)
{
	int ctr = 0;
	int offset_bytes;
	for (int i = 0 ; i < VERTICAL_CELS; i++)
	{
		for (int j = 0 ; j < HORIZONTAL_CELS; j++)
		{
			offset_bytes = (j + (i * VERTICAL_CELS)) * sizeof(struct Cell);
			if (vis_or_act == 1)
			{
				if (el == *(ptr_field + offset_bytes)->vissible_value)
				{
					ctr++;
				}
			}
			else
			{
				if (el == *(ptr_field + offset_bytes)->actual_value)
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
	if (el_ctr('q' , ptr_field , 0) == 0)
	{
		printf("\n you won , wanna play again, write Y/N? \n");
		char action;
		scanf("%c", &action);
		if (action == 'Y')
		{
			make_start_grid(HORIZONTAL_CELS , VERTICAL_CELS , ptr_field);
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
			int x , y , offset_bytes;
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
			offset_bytes = (x + (y * VERTICAL_CELS)) * sizeof(struct Cell);
			if (*(ptr_field + offset_bytes)->vissible_value == 'F')
			{
				if (*(ptr_field + offset_bytes)->actual_value == 'B')
				{
					*(ptr_field + offset_bytes)->vissible_value = 'q';
					print_grid(ptr_field , 0);
					printf("\n why don't you print1");
					make_move(ptr_field);
				}
				else if (*(ptr_field + offset_bytes)->actual_value == 'q')
				{
					*(ptr_field + offset_bytes)->vissible_value = 'q';
					print_grid(ptr_field , 0);
					printf("\n why don't you print2");
					make_move(ptr_field);
				}
				else
				{
					*(ptr_field + offset_bytes)->vissible_value = *(ptr_field + offset_bytes)->actual_value;
					mine_checker(ptr_field , x, y);
					print_grid(ptr_field , 0);
					printf("\n why don't you print3");
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
				*(ptr_field + offset_bytes)->vissible_value = 'F';
				print_grid(ptr_field , 0);
				make_move(ptr_field);
			}

		}

		if (action == 'P')
		{
			print_grid(ptr_field , 1);
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
	int offset_bytes;
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
			offset_bytes = (j + (i * VERTICAL_CELS)) * sizeof(struct Cell);
			if (actual == 0)
			{
			printf ("|%c|" , *(ptr_field + offset_bytes)->vissible_value);
			}
			else
			{
			printf ("|%c|" , *(ptr_field + offset_bytes)->actual_value);
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
	int offset_bytes;
	offset_bytes = (first_move_x + (first_move_y * VERTICAL_CELS)) * sizeof(struct Cell);
	while (i != TOTAL_BOMBS)
	{
		int random_x = rand() % (HORIZONTAL_CELS);
		int random_y = rand() % (VERTICAL_CELS);
		offset_bytes = (random_x + (random_y * VERTICAL_CELS)) * sizeof(struct Cell);



		if ((random_x == first_move_x  || random_x == first_move_x + 1 || random_x == first_move_x - 1) &&
			(random_y == first_move_y || random_y == first_move_y - 1 || random_y == first_move_y + 1 ))
		{
			printf("\n");
			printf("recalculations_NUMBER");
			printf("\n");
		}
		else if (*(ptr_field + offset_bytes)->actual_value == 'B')
		{
			printf("\n");
			printf("recalculations_BOMB");
			printf("\n");
		}
		else
		{
			*(ptr_field + offset_bytes)->actual_value = 'B';
			*(ptr_field + offset_bytes)->vissible_value = 'q';
			i++;
		}


	}
	update_field(ptr_field , first_move_x , first_move_y);


}

void  make_start_grid(int rows, int columns,struct Cell *ptr_field)
{
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


	for (int i=0; i < rows   ; i++)
	{
		printf("\n");
		printf("%d |", i);
		for (int j=0; j < columns   ; j++)
		{
			int offset_bytes = (j + (i * VERTICAL_CELS)) * sizeof(struct Cell);
			*(ptr_field + offset_bytes)->vissible_value = 'q';
			*(ptr_field + offset_bytes)->actual_value = 'q';
			printf ("|%c|" , *(ptr_field + offset_bytes)->vissible_value);
		}
	}
	printf("\n \n");

}




int main(void)
{

	struct Cell field[HORIZONTAL_CELS][VERTICAL_CELS];
	make_start_grid(HORIZONTAL_CELS , VERTICAL_CELS , &field);     //essential for adressing al characters
	int x , y;
	printf("\n choose an x coordinate \n");
	scanf("%d"  , &x);
	printf("\n choose an y coordinate \n");
	scanf("%d"  , &y);
	place_mines(x, y,&field);

	return 0;
}
//https://stackoverflow->com/questions/9653072/return-a-struct-from-a-function-in-c
