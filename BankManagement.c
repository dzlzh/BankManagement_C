/*文件头*/
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*开户账号*/
#define initnumber 10001
/*结构体*/
typedef struct xingxi
{
    int zhanghao;
    char huming[9];
    char mima[6];
    float jine;
    int zhuangtai;
}xianshi;
/*自定义函数*/
void display(xianshi *x);/*显示*/
int save(xianshi* ap);/*保存*/
float getmoney1();/*金额限制1*/
float getmoney2();/*金额限制2*/
float getmoney3(float i);/*金额限制3*/
xianshi* docreatexianshi();/*执行开户*/
xianshi* getnumber(int number);/*获取账号*/
void welcome();/*欢迎界面*/
void tuichu();/*退出*/
void deposit();/*存款*/
void withdraw();/*取款*/
void openAnxianshi();/*开户*/
void closeAnAcount();/*销户*/
void query();/*查询*/
void queryall();/*查询全部*/
void mainmenu();/*系统菜单*/
/*主函数*/
void main()
{
    char name[9];
    char password[9];
    int i , flag=0;
    welcome();
    for(i=0;i<3;i++)
    {
        if (flag==0)
        {
            printf("请输入您的用户名：");
            scanf("%8s",&name);
            if (strcmp(name,"admin")!=0)
            {
                continue;
            }
            else
            {
                flag=1;
            }
        }
        printf("请输入您的密码：");
        scanf("%8s",&password);
        if (strcmp(password,"admin")!=0)
        {
            continue;
        }
        else
        {
            mainmenu();
            break;
        }
    }
    if (i==3)
    {
        printf("您输入错误已经超过3次。\n");
        tuichu();
    }
}
/*显示*/
void display(xianshi *x) 
{
    char *zt;
    if(x->zhuangtai==0)
    {
        zt="正常";
    }
    else
    {
        zt="销户";
    }
    printf("\n");
    printf("+----------------------------------------------+\n");
    printf("|    帐号|    户名|    密码|      余额|    状态|\n");
    printf("|%8d|%8s|%8s|%10.1f|%8s|\n",x->zhanghao,x->huming,x->mima,x->jine,zt);
    printf("+----------------------------------------------+\n");
}
/*保存*/
int save(xianshi* ap)
{
    xianshi* nap=(xianshi*)malloc(sizeof(xianshi));
    int flag=0,count=0;
    FILE *fp;
    fp=fopen("bank","rb+");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            count=fread(nap,sizeof(xianshi),1,fp);
            if(count>0)
            {
                if(ap->zhanghao==nap->zhanghao)
                {
                    fseek(fp,-((long)sizeof(xianshi)),1);
                    fwrite(ap,sizeof(xianshi),1,fp);
                    flag=1;
                    break;
                }
            }
        }
        fclose(fp);
    }
    return flag;
}
/*金额限制1*/
float getmoney1()
{
    float money=-1;
    while(1)
    {
        scanf("%f",&money);
        fflush(stdin);
        if(money<0)
        {
            printf("您输入的是无效金额！");
            continue;
        }
        else
        {
            break;
        }
    }
    return money;
}
/*金额限制2*/
float getmoney2()
{
    float money=-1;
    while(1)
    {
        scanf("%f",&money);
        fflush(stdin);
        if(money<=0)
        {
            printf("您输入的金额小于等于0！请从新输入......\n");
            continue;
        }
        else
        {
            break;
        }
    }
    return money;
}
/*金额限制3*/
float getmoney3(float i)
{
    float money=-1;
    while(1)
    {
        scanf("%f",&money);
        fflush(stdin);
        if(money<=0)
        {
            printf("您输入的金额小于等于0！请从新输入......\n");
            continue;
        }
        else
        {
            if(money<=i)
            {
                break;
            }
            else
            {
                printf("您的帐号余额已经不足您本次的取款！\n");
                getchar();
                mainmenu();
            }
        }
    }
    return money;
}
/*执行开户*/
xianshi* docreatexianshi()
{
    xianshi* xs=(xianshi*)malloc(sizeof(xianshi));
    int count=0;
    char name[9];
    char password[6];
    int   con;
    FILE *fp;
    int last=initnumber;
    fp=fopen("bank","ab+");
    if(fp!=NULL)
    {
        fseek(fp,-((long)sizeof(xianshi)),2);
        count=fread(xs,sizeof(xianshi),1,fp);
        if(count>0)
        {
            last=xs->zhanghao+1;
        }
        printf("请输入您的户名：");
        scanf("%s",name);
        fflush(stdin);
        printf("请输入您的密码：");
        scanf("%s",password);
        fflush(stdin);
        printf("请输入您要存入的金额:");
        xs->jine=getmoney1();
        con=0;
        xs->zhanghao=last;
        strcpy(xs->huming,name);
        strcpy(xs->mima,password);
        xs->zhuangtai=con;
        fseek(fp,0,2);
        fwrite(xs,sizeof(xianshi),1,fp);
        fclose(fp);
    }
    return xs;
}
/*获取账号*/
xianshi* getnumber(int number)
{
    xianshi *ap=(xianshi*)malloc(sizeof(xianshi));
    xianshi *tmp=(xianshi*)malloc(sizeof(xianshi));
    int flag=0,count=0;
    FILE *fp;
    fp=fopen("bank","rb");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            count=fread(tmp,sizeof(xianshi),1,fp);
            if(count>0)
            {
                if(tmp->zhanghao==number)
                {
                    flag=1;
                    break;
                }
            }
        }
        fclose(fp);
        if(flag)
        {
            ap->zhanghao=tmp->zhanghao;
            strcpy(ap->huming,tmp->huming);
            strcpy(ap->mima,tmp->mima);
            ap->jine=tmp->jine;
            ap->zhuangtai=tmp->zhuangtai;
        }
        else
        {
            ap->zhanghao=0;
            strcpy(ap->huming,"");
            strcpy(ap->mima,"");
            ap->jine=0 ;
            ap->zhuangtai=0;
        }
    }
    free (tmp);
    return ap;
}
/*欢迎界面*/
void welcome()
{
    printf("+-------------------------------+\n");
    printf("|                               |\n");
    printf("|   欢迎使用储蓄综合业务平台     |\n");
    printf("|                               |\n");
    printf("+-------------------------------+\n");
    
}
/*退出*/
void tuichu()
{
    exit(0);
}
/*存款*/
void deposit()
{
    int number=-1;
    xianshi *ap;
    float money=-1;
    int result=0;
    while(1)
    {
        printf("请输入您要存款的账号：");
        scanf("%d",&number);
        fflush(stdin);
        ap=getnumber(number);
        if(ap->zhanghao!=0)
        {
            if(ap->zhuangtai==1)
            {
                printf("您输入的账号已经销户！任意键回菜单.....\n");
                getchar();
                return;
            }
            else
            {
                display(ap);
                printf("请输入您的存款金额：");
                money=getmoney2();
                ap->jine+=money;
                result=save(ap);
                if(result!=0)
                {
                    display(ap);
                    printf("存款成功!任意键回菜单.....\n");
                    getchar();
                    break;
                }
            }
            free (ap);
        }
        else
        {
            printf("您输入的账号不存在！\n");
            getchar();
            return;
        }
    }
}
/*取款*/
void withdraw()
{
    int number=-1,i;
    char password[6];
    xianshi *ap;
    float money=-1;
    int result=0;
    while(1)
    {
        printf("请输入您要取款的账号：");
        scanf("%d",&number);
        fflush(stdin);
        ap=getnumber (number);
        if(ap->zhanghao!=0)
        {
            if(ap->zhuangtai==1)
            {
                printf("您输入的账号已经销户！任意键回菜单.....\n");
                getchar();
                break;
            }
            else
            {
                for(i=0;i<3;i++)
                {
                    printf("请输入您要取款的密码：");
                    scanf("%s",&password);
                    fflush(stdin);
                    if(strcmp(ap->mima,password)==0)
                    {
                        display(ap);
                        printf("请输入您的取款金额：");
                        money=getmoney3(ap->jine);
                        ap->jine-=money;
                        result=save(ap);
                        if(result!=0)
                        {
                            display(ap);
                            printf("取款成功！任意键回菜单.....\n");
                            getchar();
                            break;
                        }
                    }
                    else
                    {
                        printf("您输入的密码不正确！\n");
                        continue;
                    }
                }
                if (i==3)
                {
                    printf("您输入错误已经超过3次。\n");
                    getchar();
                    break;
                }
                else
                {
                    break;
                }
            }
            free (ap);
        }
        else
        {
            printf("您输入的账号不存在！\n");
            getchar();
            return;
        }
    }
}
/*开户*/
void openAnxianshi()
{
    xianshi* xs;
    fflush(stdout);
    xs=docreatexianshi();
    if(xs->zhanghao!=0)
    {
        display(xs);
        printf("开户成功！任意键回菜单.....\n");
        getchar();
    }
    free(xs);
}
/*销户*/
void closeAnAcount()
{
    int number=-1,flag=0,i;
    char password[6];
    xianshi *ap;
    int result=0;
    while(1)
    {
        printf("请输入您要销户的账号：");
        scanf("%d",&number);
        fflush(stdin);
        ap=getnumber (number);
        if(ap->zhanghao!=0)
        {
            for(i=0;i<3;i++)
            {
                printf("请输入您要销户的密码：");
                scanf("%s",&password);
                fflush(stdin);
                if(strcmp(ap->mima,password)==0)
                {
                    display(ap);
                                        if(ap->jine>0)
                    {
                        printf("您的帐户里还有余额请记得取出！\n");
                    }
                    printf("确定要将帐户%d销户吗？[1：销户|其它：不销户]",ap->zhanghao);
                    scanf("%d",&flag);
                    fflush(stdin);
                    if(flag==1)
                    {
                        ap->zhuangtai=1;
                        ap->jine=0;
                        result=save(ap);
                        if(result!=0)
                        {
                            display(ap);
                            printf("销户成功！任意键回菜单.....\n");
                            getchar();
                            break;
                        }
                    }
                    else
                    {
                        printf("您已经成功取消销户！任意键回菜单.....\n");
                        getchar();
                        break;
                    }
                }
                else
                {
                    printf("您输入的密码不正确！\n");
                    continue;
                }
            }
                        if (i==3)
            {
                printf("您输入错误已经超过3次。\n");
                getchar();
                break;
            }
            else
            {
                break;
            }
            free (ap);
        }
        else
        {
            printf("您输入的账号不存在！\n");
            getchar();
            return;
        }
    }
}
/*查询*/
void query()
{
    int number=-1,i;
    char password[6];
    xianshi *ap;
    while(1)
    {
        printf("请输入您要查询的账号：");
        scanf("%d",&number);
        fflush(stdin);
        ap=getnumber (number);
        if(ap->zhanghao!=0)
        {
            for(i=0;i<3;i++)
            {
                printf("请输入您要查询的密码：");
                scanf("%s",&password);
                fflush(stdin);
                if(strcmp(ap->mima,password)==0)
                {
                    display(ap);
                    printf("查询成功！任意键回菜单.....\n");
                    getchar();
                    break;
                }
                else
                {
                    printf("您输入的密码不正确！\n");
                    continue;
                }
            }
            if (i==3)
            {
                printf("您输入错误已经超过3次。\n");
                getchar();
                break;
            }
            else
            {
                break;
            }
                free (ap);
            }
         else
        {
            printf("您输入的账号不存在！\n");
            getchar();
            return;
        }
    }
}
/*查询全部*/
void queryall()
{
    char name[9];
    char password[9];
    int flag=0,i,count=0;
    xianshi *tmp=(xianshi*)malloc(sizeof(xianshi));
    for(i=0;i<3;i++)
    {
        if (flag==0)
        {
            printf("请输入您的用户名：");
            scanf("%8s",&name);
            if (strcmp(name,"admin")!=0)
            {
                continue;
            }
            else
            {
                flag=1;
            }
        }
        printf("请输入您的密码：");
        scanf("%8s",&password);
        if (strcmp(password,"admin")!=0)
        {
            continue;
        }
        else
        {
            FILE *fp;
            fp=fopen("bank","rb");
            if(fp!=NULL)
            {
                while(!feof(fp))
                {
                    count=fread(tmp,sizeof(xianshi),1,fp);
                    if(count>0)
                    {
                        display(tmp);
                    }
                }
                getchar();
                return;
            }
            fclose(fp);
        }
    }
    if (i==3)
    {
        printf("您输入错误已经超过3次。\n");
        tuichu();
    }
}
/*系统菜单*/
void mainmenu()
{
    int xuanze;
    do
    {
        xuanze=-1;
        printf("+-------------------------------+\n");
        printf("| 存款  请按 1     开户  请按 4 |\n");
        printf("| 取款  请按 2     销户  请按 5 |\n");
        printf("| 查询  请按 3     退出  请按 0 |\n");
        printf("| 查询全部         请按 6       |\n");
        printf("+-------------------------------+\n");
        printf("请选择：");
        scanf("%d",&xuanze);
        fflush(stdin);
        switch(xuanze)
        {
            case 1: deposit();      break;
            case 2: withdraw();       break;
            case 3: query();       break;
            case 4: openAnxianshi();        break;
            case 5: closeAnAcount();       break;
            case 6: queryall();           break;
            case 0: tuichu();
            default: printf("您输入的有误！\n");
        }
    }while(1);
}
