#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Q_NUM 32

struct Tester{
  char name[20];
  char mbti[5];
  int answer[32];
  int mbtiscore[4];
  struct tm *t;
};

struct Question{   
  int type;
  char *common;
  char *question1;
  char *question2;
};

void load_question(struct Question *p[],struct Tester *tlist[]);
int load_testlist(struct Tester *tlist[]);
void ask_question(struct Question *p[], struct Tester *tester);
void decide_mbti(struct Tester *tester);
void printResult(struct Tester *tester);
void showGraph(struct Tester *tester);
void printTestList(struct Tester *tlist[], int tcount);
void save_list(struct Tester *tlist[], int tcount);
int getMenu();