#include "mbtilib.h"

int main(){

    struct Question *questlist[Q_NUM]; // 32 question for MBTI
    struct Tester *tlist[50];
    struct Tester *tester;
    int quit=0;
    int menu, tested=0, num, tcount=0;
    char c;
    
    load_question(questlist,tlist);        // load question from data.txt file into struct
    tcount = load_testlist(tlist);         // load testlist from testlist.txt;
    
    while(quit==0){
      menu = getMenu();

      switch(menu){
        case 1: 
          tester = (struct Tester*)malloc(sizeof(struct Tester));
          printf("\n이름? ");
          scanf("%s", tester->name);
          //tester->testdate = getDate();
          ask_question(questlist, tester); // ask question to the user
          tlist[tcount] = tester;
          tested = 1;
          tcount++;
          break;
        case 2: if(tested==0) printf("\n== 검사부터 하세요! ==\n");
          else printResult(tester);
          break;
        case 3: if(tested==0) printf("\n== 검사부터 하세요! ==\n");
          else showGraph(tester);
          break;
        case 4: 
          printTestList(tlist, tcount);
          if(tcount == 0){
            printf("\n== 결과가 없습니다! ==\n");
            break;
          }
          else{
            getchar();
            printf("결과확인 r / 삭제 d : ");
            scanf("%c",&c);
            getchar();
            if(c == 'r'){
              while(1){
                printf("결과를 확인하고 싶은 번호 입력 > ");
                scanf("%d", &num);
                if(num<=0 || num>tcount){
                  printf("잘못된 선택입니다, 다시 선택하세요\n");
                }
                else break;
              }
              printf("\n선택된 유저: %s", tlist[num-1]->name);
              tester = tlist[num-1];
              tested = 1;
              break;
            }
            else if(c == 'd'){
              printf("지울 결과의 번호를 입력하세요. ");
              scanf("%d",&num);
              free(tlist[num-1]);
              for(int i=num-1; i<tcount-1;i++){
                tlist[i] = tlist[i+1];
              }
              tcount--;
              break;
            }
            else{
              printf("잘못된 기입\n");
              break;
            }
          }
        default: 
          save_list(tlist,tcount);
          quit=1;
		  }    
      
    }
    
    for (int i = 0; i < Q_NUM; i++)
    {
        free(questlist[i]->common);
        free(questlist[i]->question1);
        free(questlist[i]->question2);
        free(questlist[i]);
    }
    return 0;
}