#include <cstring>
#include <menu.h>
#include <cstdlib>
#include <unistd.h>
#include "func.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

const char *PATH ="./save.dat";

const char *Addquest[] = {
			"Enter hospital name : ",
			"Date :",
			"Enter count bed : ",
			"Enter hospital address: ",					
			};

const char *Datequest[] = {
			" day: ", 
			" month: ", 
			" year: ",
			};

const char *templcout[] = {
                        " id     name       date       count_bed         address    ",
                        (char *)NULL,
			};


void print_dbhead(int n)
{
	int row;

	row = 4+(n*2);	

	mvprintw(5, 19,"%s",templcout[0]);

	mvwhline(stdscr, 4, 19, ACS_HLINE, 60);
	mvwaddch(stdscr, 4, 18, ACS_ULCORNER);
	mvwaddch(stdscr, 4, 79, ACS_URCORNER);
	mvwhline(stdscr, 6, 19, ACS_HLINE, 60);
		
	mvwvline(stdscr, 5, 18, ACS_VLINE, row);
	mvwvline(stdscr, 5, 79, ACS_VLINE, row);


	mvwaddch(stdscr, 6, 18, ACS_LTEE);
	mvwaddch(stdscr, 6, 79, ACS_RTEE);

	mvwhline(stdscr, row+5, 19, ACS_HLINE, 60);
	mvwaddch(stdscr, row+5, 18, ACS_LLCORNER);
	mvwaddch(stdscr, row+5, 79, ACS_LRCORNER);
	
	refresh();
}

int clr_area(int y, int x)
{
	int yy;
	int xx;
	
	getmaxyx(stdscr,yy,xx);	

	for ( y ; y <= yy ;++y){
		move(y,x);
		clrtoeol();
	}
	refresh();
	return 0;
}

void Print_dbitem(DB_item x, int y)
{

	move(y,20);
	clrtoeol();
	
	mvprintw(y,20,"%d",y-6);
	mvprintw(y,27,"%s",x.name);	
	
	mvprintw(y,35,"%dd",x.b_date.day);
	mvprintw(y,38,"%dm",x.b_date.month);
	mvprintw(y,41,"%dy",x.b_date.year);


	mvprintw(y,52,"%d",x.count_bed);
	mvprintw(y,65,"%s",x.addres);	
}


void Print_alldb()
{
	clr_area(1,18);
	DB_item Rditem;
	
 
	FILE* fShow = fopen(PATH,"rb");
	if (fShow == NULL) 
		mvprintw(1,20,"Error with open");
	 else {
		int numbItem = 1;
		clr_area(1,18);
		while (fread(&Rditem, sizeof(DB_item), 1, fShow)) {
			Print_dbitem(Rditem,numbItem+6);
			numbItem++;
		}
		print_dbhead(numbItem);
		refresh();
		if (false) 
			mvprintw(1,20,"Error with open smt false");
		 else if (numbItem == 1) 
			mvprintw(1,20,"DB is empty");
	
		fclose(fShow);
	}

	
	refresh();
}

DB_item create_dbitem()
{
	DB_item NewItem;
	char d[2] = "";
	char m[2]= "";
	char y[4] = "";
	char bed[5] = "";
	
	echo();	
		
	for(int i = 0; i < ARRAY_SIZE(Addquest);++i){
		move(1,20);
		clrtoeol();
		mvprintw(1,20,"%s",Addquest[i]);
		refresh();

		switch (i)
		{
			case 0: scanw("%s", NewItem.name);
				break;
			case 1:	mvprintw(1,24,"%s",Datequest[0]);
				refresh();
				mvscanw(1,29,"%s",d);
				mvprintw(1,31,"%s",Datequest[1]);
				refresh();
				mvscanw(1,38,"%s",m);
				mvprintw(1,40,"%s",Datequest[2]);
				refresh();
				mvscanw(1,46,"%s",y);
				break;
			case 2: scanw("%s",bed);
				break;
			case 3: scanw("%s",NewItem.addres);
				break;
						
		}
	move(1,0);
	clrtoeol();		
	}

	NewItem.b_date.day = atoi(d);
	NewItem.b_date.month =atoi(m);
	NewItem.b_date.year = atoi(y);
	NewItem.count_bed = atoi(bed);

	
	
	refresh();
	noecho();
	return NewItem;	
}


int Select_item(int n)
{
	switch(n)
	{
		case 0:
			DB_item x;
			x = create_dbitem();
			writeinfile(x,PATH);
			Print_alldb();			
			refresh();
		break;
		case 1: 
			char rm[2];
			move(1,20);
			clrtoeol();
			printw("Enter record's id to remove ");
			echo();
			scanw("%s",rm);
			noecho();
			rmfromfile(atoi(rm),PATH);
			Print_alldb();
			refresh();
		break;
		case 2:	char ch[2];
			move(1,20);
			clrtoeol();
			printw("Enter record's id to change ");
			echo();
			scanw("%s",ch);
			noecho();
	
			DB_item Ch_item;
			Ch_item = create_dbitem();
			chinfile(Ch_item,atoi(ch),PATH);
			Print_alldb();
			refresh();
		break;
		case 3:
			Print_alldb();
			refresh();
		break;
		case 4:
				
		break;
	}
	return n;
}

