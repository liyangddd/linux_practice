#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main() {
  initscr();
  move(5, 15);
  printw("%s", "Hello Word");
  refresh();
  endwin();
  exit(EXIT_SUCCESS);
}