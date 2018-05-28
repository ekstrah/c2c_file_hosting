#include "my_header.h"

char menu_list[2][3][20] = {{"1. Login", "2. Create Account", "3. Exit"},{"1. Upload file", "2. Download file", "3. Logout"}};

int yMax, xMax;
WINDOW *menuwin;

void menu_open()
{
	/* NCURSES START */
	initscr();
	cbreak();

	getmaxyx(stdscr, yMax, xMax);
	menuwin = newwin(5, 0, 0, 0);
	
	wborder(menuwin,42,42,42,42,42,42,42,42);
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);
}

int select_menu(int menu_num)
{
	int choice;
	int highlight = 0;

	while(1)
	{
		for(int i = 0; i < 3; i++)
		{
			if(i == highlight)
				wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+1, 1, menu_list[menu_num][i]);
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3)
					highlight = 2;
				break;
			default:
				break;
		}
		if(choice == 10)
			break;
	}
	return highlight;	
}

void menu_close()
{
	endwin();
}

int main(int argc, char **argv)
{
	int menu_num;
	char str[20];
	for(;;){
		menu_open();
		menu_num = select_menu(0);	
//		mvprintw(yMax-1,0,"Your chocie was %d", menu_num+1);
		switch(menu_num){
			case 0: 
				menu_close();
				menu_open();
				mvprintw(2, 2, "ID : ");
				getstr(str);
				mvprintw(LINES - 2, 0, "You Entered: %s", str);
				if( login_server(str) < 0 ){
					mvprintw(LINES - 1, 0, "There is no ID : %s Press any key", str);
					getch();
					menu_close();
				}
				else{
					clear();
					menu_close();
					for(;;){
					menu_open();
					menu_num = select_menu(1);
					switch(menu_num){
						case 0:
							menu_close();
							menu_open();
							mvprintw(2, 2, "File name to upload : ");
							getstr(str);
							mvprintw(LINES - 2, 0, "You Entered: %s", str);
							if( file_transfer(str) < 0 )
								mvprintw(LINES - 1, 0, "Fail to upload file Press any key", str);
							else
								mvprintw(LINES - 1, 0, "Success to upload file Press any key", str);
							getch();
							menu_close();
							break;
						case 1:
							menu_close();
							menu_open();
							mvprintw(2, 2, "File name to download : ");
							getstr(str);
							mvprintw(LINES - 2, 0, "You Entered: %s", str);
							if(filename_send(str) < 0)
								mvprintw(LINES - 1, 0, "Fail to download file Press any key", str);
							else if( file_receive(str) < 0 )
								mvprintw(LINES - 1, 0, "Fail to download file Press any key", str);
							else
								mvprintw(LINES - 1, 0, "Success to download file Press any key", str);
							getch();
							menu_close();
							break;
						}
						clear();
						menu_close();
						if( menu_num == 2 )
							break;
					}
				}
				break;
			case 1:
				menu_close();
				menu_open();
				mvprintw(2, 2, "Please enter your ID : ");
				getstr(str);
				mvprintw(LINES - 2, 0, "You Entered: %s", str);
				add_account(str);
				mvprintw(LINES - 1, 0, "Press any key");
				getch();
				menu_close();
				break;
			case 2:
				menu_close();
				return 0;
		}
		clear();
		menu_close();
	}
	
}