#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(int argc,char ** argv)
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	char *op = argv[3];
	char op1 = op[0];
	int res;
	if(op1=='+')
		res = a + b;
	else if(op1=='-')
		res = a - b;
	return (res);
}
