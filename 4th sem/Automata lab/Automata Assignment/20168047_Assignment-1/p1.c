#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{

    char keyword[32][10]={"auto","double","int","struct","break","else","long",
       "switch","case","enum","register","typedef","char",
       "extern","return","union","const","float","short",
       "unsigned","continue","for","signed","void","default",
       "goto","sizeof","volatile","do","if","static","while"} ;
        char string[10];
    int flag=0,i;

    printf("enter any string:");
    gets(string);
    for(i=0;i<32;i++)
    {
        if(strcmp(string,keyword[i])==0)
        {

            flag=1;
            break;
        }
    }

    if(flag==1)
        printf("%s is a keyword",string);

   else
        printf("%s is not a keyword",string);

        getch();

}
