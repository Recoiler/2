#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "func.h"
#include <menu.h>


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4



const char *choices[] = {
                        "Add item",
                        "Rm item",
                        "Change item",
			"Refresh",
                        "Exit",
                        (char *)NULL,
                  };

int main()
{		
	ITEM **my_items;				
	MENU *my_menu;
	int c;
        WINDOW *my_menu_win;
        int n_choices, i;
	
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], NULL);

	my_menu = new_menu((ITEM **)my_items);
	
        my_menu_win = newwin(8, 15, 7, 0);
        keypad(my_menu_win, TRUE);
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 8, 15, 7, 0));
        set_menu_mark(my_menu, " * ");
      
	post_menu(my_menu);
	Print_alldb();
	wrefresh(my_menu_win);

	int ex = 0;

	while ((ex != 4) && ((c = wgetch(my_menu_win)) != KEY_F(1)))
	{       switch(c)
	        {	case KEY_DOWN:{
				menu_driver(my_menu, REQ_DOWN_ITEM);
				refresh();
				break;
				}
			case KEY_UP:{
				menu_driver(my_menu, REQ_UP_ITEM);		
				refresh();
				break;
				}
			case 10:{
				ex = Select_item(item_index(current_item(my_menu)));
				break;
				}						
		}
                wrefresh(my_menu_win);
	}	

        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
}

