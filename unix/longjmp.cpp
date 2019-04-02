#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

//全局变量，静态变量，易失变量不受优化的影响
//受编译器优化的影响，当自动变量满足以下条件时，其值在调用longjmp()之后是不可预料的
//1.局部变量
//2.在setjmp()和longjmp()之间改变了变量的值
//3.未被声明为volatile

static void f1(int, int, int , int);
static void f2(void);

static jmp_buf jmpbuffer;
static int     globval;

int main()
{
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;

    globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;
    
    if(setjmp(jmpbuffer) != 0)
    {
	printf("after longjmp:\n");
	printf("globval = %d, autoval = %d, regival = %d,"
	       "volaval = %d, statval = %d\n",
		globval, autoval, regival, volaval, statval);
	exit(0);
    }

    globval = 95; autoval = 96; regival = 97; volaval = 98;
    statval = 99;

    f1(autoval, regival, volaval, statval);
    exit(0);
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("globval = %d, autoval = %d, regival = %d,"
           "volaval = %d, statval = %d\n", globval, i, j, k, l);
    f2();
}

static void f2(void)
{
    longjmp(jmpbuffer, 1);
}
