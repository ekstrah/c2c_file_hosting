#include "my_header.h"
#include "color.h"

char menu_list[2][3][30] = {{"1. LAN sharing", "2. Broad sharing", "3. Quit"},
	{"1. Upload file", "2. Download file", "3. Back to previous menu"}};

int yMax, xMax;
WINDOW *menuwin;

void menu_open()
{
	/* NCURSES START */
	initscr();
//	cbreak();

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
	int menu_num1, menu_num2;
	char target[3][20];
	for(;;){
		menu_open();
		menu_num1 = select_menu(0);
		switch(menu_num1){
			case 0: // LAN sharing
				clear();
				menu_close();
				for(;;){
					menu_open();
					menu_num2 = select_menu(1);
					switch(menu_num2){
						case 0: // file upload
							menu_close();
							menu_open();
							mvprintw(1, 2, "(ex ./folder/)");
							mvprintw(2, 2, "Enter the file path : ");
							getstr(target[0]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[0]);
							menu_close();
							menu_open();
							mvprintw(1, 2, "(ex cat.jpg)");
							mvprintw(2, 2, "Enter the file name : ");
							getstr(target[1]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[1]);
							menu_close();
							menu_open();
							mvprintw(1, 2, "(ex 192.168.0.1)");
							mvprintw(2, 2, "Enter target IP address : ");
							getstr(target[2]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[2]);
							if( file_upload(target[0], target[1], target[2]) < 0  )
								mvprintw(LINES - 1, 0, "Fail to upload file Press any key");
							else
								mvprintw(LINES - 1, 0, "Success to upload file Press any key");
							getch();
							menu_close();
							break;
						case 1: // file download
							menu_close();
							menu_open();
							mvprintw(1, 2, "(ex ./folder/)");
							mvprintw(2, 2, "Enter the file path : ");
							getstr(target[0]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[0]);
							file_download(target[0]);
							mvprintw(LINES - 1, 0, "Success to download file Press any key");
							getch();
							menu_close();
							break;
					}
					if( menu_num2 == 2 )
						break;
				}
				break;
			case 1: // broad sharing
				clear();
				menu_close();
				for(;;){
					menu_open();
					menu_num2 = select_menu(1);
					switch(menu_num2){
						case 0: // file upload
							menu_close();
							menu_open();
							mvprintw(2, 2, "(ex ./folder/)");
							mvprintw(3, 2, "Enter the file path  : ");
							getstr(target[0]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[0]);
							menu_close();
							menu_open();
							mvprintw(2, 2, "(ex cat.jpg)");
							mvprintw(3, 2, "Enter the file name  : ");
							getstr(target[1]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[1]);
							menu_close();
							menu_open();
							mvprintw(2, 2, "(ex 192.168.0.1)");
							mvprintw(3, 2, "Enter target IP address  : ");
							getstr(target[2]);
							mvprintw(LINES - 2, 0, "You Entered: %s", target[2]);
							if( file_upload(target[0], target[1], target[2]) < 0  )
								mvprintw(LINES - 1, 0, "Fail to upload file Press any key");
							else
								mvprintw(LINES - 1, 0, "Success to upload file Press any key");
							getch();
							menu_close();
							break;
						case 1: // file download
							break;
						case 2: // back to previous menu
							break;
					}
					clear();
					menu_close();
				}
				break;
			}
		if( menu_num1 == 2 )
			break;
		clear();
		menu_close();
	}
	clear();
	menu_close();
}

