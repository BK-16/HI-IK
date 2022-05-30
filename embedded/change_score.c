#include <stdio.h>
#include "student.h"
#define START_ID 201901700


int main(int argc,char* argv[])
{
    struct student record;
    char c;
    int id;
    FILE *fp;
    
    if(argc!=2) 
    {
        fprintf(stderr,"사용법 : %s 파일이름\n",argv[0]);
        return 1;
    }

    if((fp=fopen(argv[1],"rb+"))==NULL)
    {
        fprintf(stderr,"파일이 없습니다.\n");
        return 2;
    }

    do {
        printf("검색할 학생의 학번을 입력하시오 : ");

        if(scanf("%d",&id)==1)
        {
            fseek(fp,(id-START_ID)*sizeof(record),SEEK_SET);
            if((fread(&record,sizeof(record),1,fp)>0)&&(record.id!=0))
            {
                printf(" 학번 : %8d  이름 : %4s  점수 : %4d \n",record.id,record.name,record.score);
                printf("수정할 점수를 입력하시오 : ");
                scanf("%d",&record.score);

                fseek(fp,(id-START_ID+1)*sizeof(record)-sizeof(record.score),SEEK_SET); 
                fwrite(&record.score,sizeof(record.score),1,fp);

                printf("\n -----------수정 후 결과----------\n");
                fseek(fp,(id-START_ID)*sizeof(record),SEEK_SET);
                printf(" 학번 : %8d  이름 : %4s  점수 : %4d \n",record.id,record.name,record.score);
                printf("------------------------\n");
            }
            else
                printf("레코드 %d는 없습니다.\n",id);
        }
        else
            printf("입력 오류입니다.");

        printf("계속하시겠습니까? (Y/N)");
        scanf(" %c",&c);

    } while(c=='Y');

    fclose(fp);
    return 0;
}