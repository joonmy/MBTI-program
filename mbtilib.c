#include "mbtilib.h"

void load_question(struct Question *p[], struct Tester *tlist[])
{
    FILE *fp;
    fp = fopen("data.txt", "r");
    int i = 0;

    while (!feof(fp))
    {
        char temp[300];

        p[i] = (struct Question *)malloc(sizeof(struct Question));

        fscanf(fp, "%d", &(p[i]->type));
        fgetc(fp);

        fgets(temp, 300, fp); //get common sentence
        temp[strlen(temp) - 1] = '\0';
        p[i]->common = (char *)malloc(sizeof(char) * strlen(temp) + 1);
        strcpy(p[i]->common, temp);

        fgets(temp, 300, fp); //get question1
        temp[strlen(temp) - 1] = '\0';
        p[i]->question1 = (char *)malloc(sizeof(char) * strlen(temp) + 1);
        strcpy(p[i]->question1, temp);

        fgets(temp, 300, fp); //get question2
        temp[strlen(temp) - 1] = '\0';
        p[i]->question2 = (char *)malloc(sizeof(char) * strlen(temp) + 1);
        strcpy(p[i]->question2, temp);

        i++;
    }
    printf("%d Questions are loaded!\n",i);
    fclose(fp);
}

int load_testlist(struct Tester *tlist[]){
    FILE *fp;
    fp = fopen("testlist.txt", "r");
    int i=0;
    if(fgetc(fp)=='\n') return 0;
    while (!feof(fp))
    {
        tlist[i] = (struct Tester *)malloc(sizeof(struct Tester));

        fscanf(fp,"%s %s %d/%d/%d/%d",tlist[i]->name,tlist[i]->mbti,&(tlist[i]->mbtiscore[0]),&(tlist[i]->mbtiscore[1]),&(tlist[i]->mbtiscore[2]),&(tlist[i]->mbtiscore[3]));

        i++;
    }
    printf("%d test are loaded!\n",i);
    fclose(fp);
    return i;
}

void ask_question(struct Question *p[], struct Tester *tester)
{
    int num;
    time_t timer;
    timer = time(NULL); // 1970년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초
    tester-> t = localtime(&timer);
    printf("%d",tester->t->tm_year+1900);
    printf("\nLet's start!\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < Q_NUM; i++)
    {
        printf("(%d) ", p[i]->type);
        printf("%s\n", p[i]->common);
        printf("%s\n", p[i]->question1);
        printf("%s\n", p[i]->question2);
        printf("5 4 3 2 1\n");
        printf("Enter(1~5) > ");
        scanf("%d", &(tester->answer[i])); // assign point to answer array
        printf("\n");
    }
    decide_mbti(tester);
}

void decide_mbti(struct Tester *tester){
    int i, j;
    int sum;
    
    for(i=0; i<4; i++){
      sum=0;
      for(j=0; j<32; j+=4){
        sum += tester->answer[i+j];
      }
      tester->mbtiscore[i] = sum;
      //printf("%d",tester->mbtiscore[i]);
      if (i == 0){
        if (sum >= 20) tester->mbti[i] = 'E';
        else tester->mbti[i] = 'I';
      }
      else if (i == 1){
        if (sum >= 20) tester->mbti[i] = 'S';
        else tester->mbti[i] = 'N';
      }
      else if (i == 2){
        if (sum >= 20) tester->mbti[i] = 'T';
        else tester->mbti[i] = 'F';
      }
      else{
        if (sum >= 20) tester->mbti[i] = 'J';
        else tester->mbti[i] = 'P';
      }
    }
    tester->mbti[4]='\0';
}

void printResult(struct Tester *tester){
  char filename[20];
  char line[500];
  sprintf(filename,"%s.txt",tester->mbti);
  
  FILE *fp;
  fp = fopen(filename,"r");

  printf("\n\n");
  printf("당신의 MBTI는 >> %s\n", tester->mbti);
  
  while(!feof(fp)){
    fgets(line,500,fp);
    printf("%s",line);
  }

  printf("\n\n\n");
  fclose(fp);
}

void showGraph(struct Tester *tester){
  printf("\n\n");
  for(int i=0; i<4; i++){
    if(i==0) printf("E ");
    if(i==1) printf("S ");
    if(i==2) printf("T ");
    if(i==3) printf("J ");
    for(int j=1; j<=40; j++){
      if(j==41-tester->mbtiscore[i]){
        printf("|*|");
        continue;
      }
      printf("=");
    }
    if(i==0) printf("I");
    if(i==1) printf("N");
    if(i==2) printf("F");
    if(i==3) printf("P");
    printf("\n");
  }
}

void printTestList(struct Tester *tlist[], int tcount){
  for(int i=0; i<tcount; i++){
    printf("%d. %s ",i+1,tlist[i]->name);
    printf("- %s\n",tlist[i]->mbti);
    //printf("%d\n",tlist[i]->t->tm_year);
  }
}

void save_list(struct Tester *tlist[], int tcount){
  FILE *fp;
  fp = fopen("testlist.txt", "w");

  for(int i=0; i<tcount; i++){
    fprintf(fp,"%s %s %d/%d/%d/%d",tlist[i]->name,tlist[i]->mbti,tlist[i]->mbtiscore[0],tlist[i]->mbtiscore[1],tlist[i]->mbtiscore[2],tlist[i]->mbtiscore[3]);
    if(i==tcount-1);
    else fprintf(fp,"\n");
  }

  fclose(fp);
}

int getMenu(){
  printf("\n");
  int a;
  printf("확인하고 싶은 목록 번호 입력\n");
  printf("1.새 검사 2. 검사 결과 3.그래프로 보기 4.결과 목록 0.종료 및 저장 >> ");
  scanf("%d",&a);
  return a;
}