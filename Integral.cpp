/**************************************************************
现阶段仅提供幂函数的积分
主要为3种方法，Simpson算法误差较小
计算机1705 indiewar
****************************************************************/
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

void Homepage()
{
    printf("*****************************************************************************\n");
    printf("*                                  积分                                     *\n");
    printf("*****************************************************************************\n");
    printf("*                               1.蒙特卡洛算法                              *\n");
    printf("*****************************************************************************\n");
    printf("*                               2.定义法                                    *\n");
    printf("*****************************************************************************\n");
    printf("*                               3.Simpson                                   *\n");
    printf("*****************************************************************************\n");
    printf("*                               4.退出系统                                  *\n");
    printf("*****************************************************************************\n");
}

int k =0;//幂函数的指数
double f(double x)
{
    double res = x;
    for(int i = 0; i<k-1; i++)
        res *= x;
    return res;
}

class basic_inte
{
protected:
    int lowLimit,upLimit;
    int num;
    double val;
public:
    basic_inte()
    {
        lowLimit = 0;
        upLimit = 0;
        num = 0;
    }
    void set_basic_inte(int le,int ri,int nu)
    {
        lowLimit = le;
        upLimit = ri;
        num = nu;
    }
    virtual void integrate()=0;
    void  show()
    {
        cout<<"The integrate is "<<val<<endl;;
    }
};

//蒙特卡洛算法(随机投点法)
class MonteCarlo : public basic_inte
{
public:
    void integrate()
    {
        double result = 0;
        int cont = 0;
        double yMin,yMax;
        yMin = f(lowLimit);
        yMax = f(upLimit);
        srand((unsigned)time(NULL));
        for (int i = 0; i < num; i++)
        {
            double   randx=rand() * 1.0 / RAND_MAX;
            double   randy=rand() * 1.0 / RAND_MAX;
            double x = lowLimit + (upLimit - lowLimit) * randx;
            double y = yMin + (yMax - yMin) * randy ;
            if (f(x) > 0 && f(x) >= y && y >= 0)
                cont++;
            if (f(x) < 0 && f(x) <= y && y <= 0)
                cont--;
        }
        result = fabs(((double)cont/num)*((yMax-yMin)*(upLimit-lowLimit)));
        val = result;
    }
};

//定义法
class DY : public basic_inte
{
public:
    void integrate()
    {

        double step = (upLimit - lowLimit) /((1.0)*num);
        double result = 0;
        for (int i = 0; i < num; i++)
        {
            result += f(lowLimit+step*i) * step;
        }
        val = result;
    }
};

//Simpson
class simpson: public basic_inte
{
public:
    void integrate()
    {
        double h,integral,x,result=0;
        int i;
        h=fabs(upLimit-lowLimit)/num;
        for(i=1; i<num; i++)
        {
            x=lowLimit+i*h;
            if(i%2==0)
            {
                result+=2*f(x);
            }
            else
            {
                result+=4*f(x);
            }
        }
        result=(h/3)*(f(lowLimit)+f(upLimit)+result);
        val = result;
    }
};

basic_inte *p;
MonteCarlo a;
DY b;
simpson c;

void Function(int ch)
{

    int up,low,n;
    string str;
    system("cls");

    if(ch==1)
        p = &a;
    else if(ch==2)
        p = &b;
    else
        p = &c;

    cout<<"现阶段仅支持幂函数，幂函数的指数(大于0)：";
    cin>>k;
    cout<<"被积分的函数为x^"<<k<<endl;
    cout<<"积分下限：";
    cin>>low;
    cout<<"积分上限：";
    cin>>up;
    cout<<"精度(越大误差越小，建议不超过10^7):";
    cin>>n;
    p->set_basic_inte(low,up,n);
    p->integrate();
    p->show();

    cout<<"是否使用其他方法进行积分(Y/N):";
    cin>>str;
    if(str[0]=='N'||str[0]=='n')
    {
        system("cls");
    }

    else if(str[0]=='Y'||str[0]=='y')
    {
        if(ch==1)
        {
            cout<<"定义法: ";
            p = &b;
        }
        else
        {
            cout<<"蒙特卡洛算法: ";
            p = &a;
        }
        p->set_basic_inte(low,up,n);
        p->integrate();
        p->show();
        if(ch==3)
        {
            cout<<"定义法: ";
            p = &b;
        }
        else
        {
            cout<<"Simpson算法: ";
            p = &c;
        }
        p->set_basic_inte(low,up,n);
        p->integrate();
        p->show();
        system("pause");
        system("cls");
    }

    else
    {
        printf("请输入正确的操作！\n");
        system("pause");
        system("cls");
    }
}

int main()
{
    while(1)
    {
        int choice;
        Homepage();
        cout<<"输入选择:"<<endl;
        cin>>choice;
        if(choice >= 1&&choice <= 3)
        {
            Function(choice);
        }
        else  if(choice==4)
        {
            exit(-1);
        }
        else
        {
            printf("请输入正确的编号！\n");
            system("pause");
            system("cls");
        }
    }
    return 0;
}
