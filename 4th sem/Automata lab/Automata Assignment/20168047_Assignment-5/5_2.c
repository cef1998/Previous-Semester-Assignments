#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    char reg[20];
    int tr[20][3],len,i,j;
    for(i=0;i<20;j++)
    {
        for(j=0;j<3;j++)
        {
            tr[i][j]=0;
        }
    }
    printf("Enter the Regular expression: \n");
    scanf("%s",reg);
    len=strlen(reg);
    i=0;
    j=1;
    while(i<len)
    {
        if(reg[i]=='a'&&reg[i+1]!='/'&&reg[i+1]!='*')
        {
            tr[j][0]=j+1;
            j++;
        }
        if(reg[i]=='b'&&reg[i+1]!='/'&&reg[i+1]!='*')
        {
            tr[j][1]=j+1;
            j++;
        }
        if(reg[i]=='e'&&reg[i+1]!='/'&&reg[i+1]!='*')
        {
            tr[j][2]=j+1;
            j++;
        }
        if(reg[i]=='a'&&reg[i+1]=='/'&&reg[i+2]=='b')
        {
            tr[j][2]=((j+1)*10)+(j+3);
            j++;
            tr[j][0]=j+1;
            j++;
            tr[j][2]=j+3;
            j++;
            tr[j][1]=j+1;
            j++;
            tr[j][2]=j+1;
            j++;
            i=i+2;
        }
        if(reg[i]=='b'&&reg[i+1]=='/'&&reg[i+2]=='a')
        {
            tr[j][2]=((j+1)*10)+(j+3);
            j++;
            tr[j][1]=j+1;
            j++;
            tr[j][2]=j+3;
            j++;
            tr[j][0]=j+1;
            j++;
            tr[j][2]=j+1;
            j++;
            i=i+2;
        }
        if(reg[i]=='a'&&reg[i+1]=='*')
        {
            tr[j][2]=((j+1)*10)+(j+3);
            j++;
            tr[j][0]=j+1;
            j++;
            tr[j][2]=((j+1)*10)+(j-1);
            j++;
        }
        if(reg[i]=='b'&&reg[i+1]=='*')
        {
            tr[j][2]=((j+1)*10)+(j+3);
            j++;
            tr[j][1]=j+1;
            j++;
            tr[j][2]=((j+1)*10)+(j-1);
            j++;
        }
        if(reg[i]==')'&&reg[i+1]=='*')
        {
            tr[0][2]=((j+1)*10)+1;
            tr[j][2]=((j+1)*10)+1;
            j++;
        }
        i++;
    }
    printf("Transition function \n");
    for(i=0;i<=j;i++)
    {
        if(tr[i][0]!=0)
        printf("\n tr[%d,a]-->%d",i,tr[i][0]);
        if(tr[i][1]!=0)
        printf("\n tr[%d,b]-->%d",i,tr[i][1]);
        if(tr[i][2]!=0)
        {
            if(tr[i][2]<10)
                printf("\n tr[%d,e]-->%d",i,tr[i][2]);
            else
                printf("\n tr[%d,e]-->%d & %d",i,tr[i][2]/10,tr[i][2]%10);
        }
    }
}
