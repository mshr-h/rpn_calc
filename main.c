#include "evalscheme.h"
#include "queue.h"
#include "stack.h"
#include "shared.h"
#include <ctype.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

typedef struct pointer_xy {
  int x;
  int y;
} POINTER;
POINTER p_max;

void autoScroll(POINTER *p) {
  if((p_max.y - 2) == p->y)
    scrl(1);
  else
    p->y++;
}

int checkScreenSize(POINTER p) {
  if((p.x < 80) || (p.y < 15))
    return FALSE;
  return TRUE;
}

void showHistory(POINTER *p) {
  QUEUE_TYPE x;
  FILE *fp;
  char tmp[SCHEME_SIZE];
  if((fp = fopen("history.txt", "r")) == NULL) {
    mvprintw(p->y, p->x, "can't find history.txt");
    autoScroll(p);
    return;
  }
  initQueue();
  while (fgets(tmp, SCHEME_SIZE, fp) != NULL) {
    strcpy(x.s, tmp);
    enqueue(x);
  }
  while(!isQueueEmpty()){
    x = dequeue();
    mvprintw(p->y, p->x, "  %s", x.s);
    autoScroll(p);
  }
  fclose(fp);
}

void showHelp(POINTER *p) {
  int i = 0;
  FILE *fp;
  char tmp[SCHEME_SIZE];
  char c;
  if((fp = fopen("help.txt", "r")) == NULL) {
    mvprintw(p->y, p->x, "can't findhelp.txt");
    autoScroll(p);
    return;
  }
  while (fgets(tmp, SCHEME_SIZE, fp) != NULL) {
    mvprintw(p->y, p->x, tmp);
    autoScroll(p);
    if(i >= p_max.y - 4) {
      attrset(COLOR_PAIR(COLOR_WHITE));
      mvprintw(p->y, p->x, "-- more --");
      attrset(COLOR_PAIR(0));
      c = getch();
      if(c == 'q')
        break;
    }
    i++;
  }
  deleteln();
  fclose(fp);
}

void recordScheme(char *scheme, char *result, POINTER *p) {
  FILE *fp;
  if((fp = fopen("history.txt", "a")) == NULL) {
    mvprintw(p->y, p->x,"can't write history.txt");
    autoScroll(p);
  } else {
    fprintf(fp, "> %s\n", scheme);
    fprintf(fp, "%s\n", result);
  }
  fclose(fp);
}

void clearScreen(POINTER *p) {
  clear();
  p->x = 0;
  p->y = 0;
}

void inputScreen(POINTER *p) {
  char scheme[SCHEME_SIZE];
  char result[SCHEME_SIZE];
  while(1) {
    mvprintw(p->y, p->x, "> ");
    refresh();
    wgetnstr(stdscr, scheme, SCHEME_SIZE);
    autoScroll(p);
    if(strcmp(scheme, "") == 0)
      continue;
    else if(strcmp(scheme, "exit") == 0)
      break;
    else if(strcmp(scheme, "history") == 0)
      showHistory(p);
    else if(strcmp(scheme, "help") == 0)
      showHelp(p);
    else if(strcmp(scheme, "clear") == 0) {
      clearScreen(p);
      continue;
    }
    else {
      strcpy(result, scheme);
      evalScheme(result);
      mvprintw(p->y, p->x, result);
      if(checkScheme(scheme)) {
        recordScheme(scheme, result, p);
      }
      autoScroll(p);
    }
    refresh();
  }
  return;
}

int main(int argc, char const* argv[]) {
  POINTER p = {0, 0};
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_color(COLOR_WHITE, 1000, 1000, 1000);
  init_pair(COLOR_WHITE, COLOR_BLACK, COLOR_WHITE);
  assume_default_colors(COLOR_WHITE, COLOR_BLACK);
  scrollok(stdscr, TRUE);
  getmaxyx(stdscr, p_max.y, p_max.x);
  if(!checkScreenSize(p_max)) {
    endwin();
    printf("window size should be larger than 80x15\n");
    exit(1);
  }
  inputScreen(&p);
  endwin();
  return 0;
}
