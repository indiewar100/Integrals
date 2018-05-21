#include<bits/stdc++.h>
using namespace std;


//以 y = x*x为例子
double f(double x)
{
    return x*x;
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
        //cout<<"count :"<<cont<<endl;
        result = fabs(((double)cont/num)*((yMax-yMin)*(upLimit-lowLimit)));
        //  cout<<"val :"<<result<<endl;
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
        //cout<<"step:"<<step<<endl;
        double result = 0;
        for (int i = 0; i < num; i++)
        {
            result += f(lowLimit+step*i) * step;
        }
        // cout<<"val :"<<result<<endl;
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

int main()
{
    basic_inte *p;
    MonteCarlo a;
    DY b;
    simpson c;
    p = &a;
    p->set_basic_inte(0,1,100000);
    p->integrate();
    p->show();
    p = &b;
    p->set_basic_inte(0,1,100000);
    p->integrate();
    p->show();
    p = &c;
    p->set_basic_inte(0,1,100000);
    p->integrate();
    p->show();

    return 0;
}
