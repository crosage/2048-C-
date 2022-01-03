#include<cstdio>
#include<windows.h>
#include<cstring>
#include<time.h>
#include<string.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<map>
using namespace std;
#define ll long long
//绘图用，间隔
const ll DEVIDE = 16;
//每一块大小
const ll BLOCK_WIDE = 106;
#define $$ 111
//地图
ll mp[$$][$$], vis[$$];
//行，本来想做n行m列的
ll n;
//列，本来想做n行m列的
ll m;
//得分
ll fen;
//映射，将2的x次方映射成x
map<ll, ll> ys;

//2048每一块大小
PIMAGE block_image[20];
//背景板
PIMAGE background_image;
//开始界面
PIMAGE beginning;
//结束时retry
PIMAGE retry;
//开始游戏按钮
PIMAGE begin_play;
//继续游戏按钮
PIMAGE play_last;
//返回随机值
ll my_random(ll x)
{
    return rand() % x;
}
//随机添加4或者2,添加4的概率为0.2
void random_add()
{
    ll x1 = my_random(n) + 1, x2 = my_random(m) + 1;
    ll pan = my_random(10) + 1;
    //判断是否满了，如果满了就接着
    ll full = 1;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            if (!mp[i][j])
            {
                full = 0;
            }
        }
    }
    if (full == 1) return;
    else 
    {
        while (mp[x1][x2])
        {
            x1 = my_random(n) + 1, x2 = my_random(m) + 1;
        }
        if (pan <= 8)
            mp[x1][x2] = 2;
        else
            mp[x1][x2] = 4;
    }
}
//简单的上下左右移动
void change(string s)
{
    //维护队列sta1，sta2，sta1存起来该行/列信息，sta2进行合并
    ll sta1[$$], sta2[$$],vis[$$];
    ll top1, top2;
    if (s == "left")
    {
        for (ll i = 1; i <= n; i++)
        {
            memset(sta1, 0, sizeof(sta1));
            top1 = 0;
            memset(sta2, 0, sizeof(sta2));
            top2 = 0;
            memset(vis, 0, sizeof(vis));
            for (ll j = 1; j <= m; j++)
            {
                if (mp[i][j])
                {
                    sta1[++top1] = mp[i][j];
                }
            }
            for (ll j = 1; j <= top1; j++)
            {
                if (!vis[j])
                {
                    if (sta1[j] == sta1[j + 1])
                    {
                        sta2[++top2] = sta1[j] * 2;
                        fen += sta1[j] * 2;
                        vis[j] = 1;
                        vis[j + 1] = 1;
                    }
                    else
                    {
                        sta2[++top2] = sta1[j];
                        vis[j] = 1;
                    }
                }
            }
            for (ll j = 1; j <= m; j++)
            {
                mp[i][j] = sta2[j];
            }
        }
    }
    else if (s == "right")
    {
        for (ll i = 1; i <= n; i++)
        {
            memset(sta1, 0, sizeof(sta1));
            top1 = 0;
            memset(sta2, 0, sizeof(sta2));
            top2 = 0;
            memset(vis, 0, sizeof(vis));
            for (ll j = m; j >= 1; j--)
            {
                if (mp[i][j])
                {
                    sta1[++top1] = mp[i][j];
                }
            }
            for (ll j = 1; j <= top1; j++)
            {
                if (!vis[j])
                {
                    if (sta1[j] == sta1[j + 1])
                    {
                        sta2[++top2] = sta1[j] * 2;
                        fen += sta1[j] * 2;
                        vis[j] = 1;
                        vis[j + 1] = 1;
                    }
                    else
                    {
                        sta2[++top2] = sta1[j];
                        vis[j] = 1;
                    }
                }
            }
            for (ll j = m; j >= 1; j--)
            {
                mp[i][j] = sta2[m - j + 1];
            }
        }
    }
    else if (s == "up")
    {
        for (ll j = 1; j <= m; j++)
        {
            memset(sta1, 0, sizeof(sta1));
            top1 = 0;
            memset(sta2, 0, sizeof(sta2));
            top2 = 0;
            memset(vis, 0, sizeof(vis));
            for (ll i = 1; i <= n; i++)
            {
                if (mp[i][j])
                {
                    sta1[++top1] = mp[i][j];
                }
            }
            for (ll i = 1; i <= top1; i++)
            {
                if (!vis[i])
                {
                    if (sta1[i] == sta1[i + 1])
                    {
                        sta2[++top2] = sta1[i] * 2;
                        fen += sta1[i];
                        vis[i] = 1;
                        vis[i + 1] = 1;
                    }
                    else
                    {
                        sta2[++top2] = sta1[i];
                        vis[i] = 0;
                    }
                }
            }
            for (ll i = 1; i <= n; i++)
            {
                mp[i][j] = sta2[i];
            }
        }
    }
    else if (s == "down")
    {
        for (ll j = 1; j <= m; j++)
        {
            memset(sta1, 0, sizeof(sta1));
            top1 = 0;
            memset(sta2, 0, sizeof(sta2));
            top2 = 0;
            memset(vis, 0, sizeof(vis));
            for (ll i = n; i >= 1; i--)
            {
                if (mp[i][j])
                {
                    sta1[++top1] = mp[i][j];
                }
            }
            for (ll i = 1; i <= top1; i++)
            {
                if (!vis[i])
                {
                    if (sta1[i] == sta1[i + 1])
                    {
                        sta2[++top2] = sta1[i] * 2;
                        fen += sta1[i] * 2;
                        vis[i] = 1;
                        vis[i + 1] = 1;
                    }
                    else
                    {
                        sta2[++top2] = sta1[i];
                        vis[i] = 1;
                    }
                }
            }
            for (ll i = n; i >= 1; i--)
            {
                mp[i][j] = sta2[n - i + 1];
            }
        }
    }
}
//新建图片并且加载图片
void load_image()
{
    char name[100];
    for (ll i = 1, num = 2; i <= 17; i++, num *= 2)
    {
        block_image[i] = newimage();
        //sprintf_s用来读取批量图片名称,返回到那么里
        sprintf_s(name, "image\\block_%lld.png", num);
        getimage(block_image[i], name);
        ys[num] = i;
    }
    background_image = newimage();
    getimage(background_image, "image\\background.png");
    retry = newimage();
    getimage(retry, "image\\overplayagain.png");
    begin_play = newimage();
    ll x=getimage(begin_play, "image\\begin_.png");
    play_last = newimage();
    ll y=getimage(play_last, "image\\pausecontinuebtn.png");
    beginning = newimage(500,500);
    PIMAGE temp = newimage();
    getimage(temp, "image\\beginning.png");
    putimage(beginning, 0, 0, 500, 500, temp, 0, 0, getwidth(temp), getheight(temp));
}
//输出到窗口
//检查是否已满，满就死
ll check_die()
{
    ll full = 1;
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
        {
            if (!mp[i][j]) return 0;
        }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
        {
            //四个角不用判断(其他格子会判断到这四个角)
            if ((i == 1 || i == n) && (j == 1 || j == m)) continue;
            //如果在第一行或者第n行
            if (i == 1 || i == n)
            {
                if (i == 1 && mp[i][j] == mp[i + 1][j])
                {
                    return 0;
                }
                if ((mp[i][j] == mp[i][j - 1]) || (mp[i][j] == mp[i][j + 1]))
                {
                    return 0;
                }
                if (i == n && mp[i][j] == mp[i - 1][j])
                {
                    return 0;
                }
            }
            if (j == 1 || j == m)
            {
                if (j == 1 && mp[i][j] == mp[i][j + 1])
                {
                    return 0;
                }
                if ((mp[i][j] == mp[i - 1][j]) || (mp[i][j] == mp[i + 1][j]))
                {
                    return 0;
                }
                if (j == n && mp[i][j] == mp[i][j - 1])
                {
                    return 0;
                }
            }
        }
    remove("data.txt");
    return 1;
}
//运行过程中的界面
//flag为0时输出正常界面
//flag为1时输出结束界面
void draw(bool flag)
{
    if (flag == 0)
    {
        putimage_withalpha(NULL, background_image, 0, 0);
        for (ll i = 1; i <= n; i++)
        {
            for (ll j = 1; j <= m; j++)
            {
                ll xpos = (j)*DEVIDE + (j - 1) * BLOCK_WIDE;
                ll ypos = (i)*DEVIDE + (i - 1) * BLOCK_WIDE;
                if (mp[i][j] != 0)
                {
                    putimage_withalpha(NULL, block_image[ys[mp[i][j]]], xpos, ypos);
                }
            }
        }
    }
    else if (flag == 1)
    {
        putimage_withalpha(NULL,background_image, 0, 0);
        for (ll i = 1; i <= n; i++)
        {
            for (ll j = 1; j <= m; j++)
            {
                ll xpos = (j)*DEVIDE + (j - 1) * BLOCK_WIDE;
                ll ypos = (i)*DEVIDE + (i - 1) * BLOCK_WIDE;
                if (mp[i][j] != 0)
                {
                    putimage_withalpha(NULL,block_image[ys[mp[i][j]]], xpos, ypos);
                }
            }
        }
        ll ok= imagefilter_blurring(NULL,0xff, 0xcf, 0, 0, 0, 0);
    }
}
void predraw()
{
    putimage(90, 100, begin_play);
    putimage(90, 300, play_last);
}
//运行部分
void game()
{
    random_add();
    draw(0);
    ll  is_end = 0;
    mouse_msg m_msg;
    //窗口设置刷新率60
    ll cnt = 0;
    //每次draw完刷新之后才会显示在屏幕上
    for (; is_run(); delay_fps(60))
    {
        if (is_end)
        {
            draw(1);
            putimage(100, 100, retry);
            ll isclick = 0,xclick=0,yclick=0;
            while (mousemsg())
            {
                m_msg = getmouse();
                if (m_msg.is_down() && m_msg.is_left())
                {
                    isclick = 1;
                    xclick = m_msg.x;
                    yclick = m_msg.y;
                }
            }
            xyprintf(xclick, yclick, "%lld %lld", xclick, yclick);
            if (isclick)
            {
                if (xclick >= 100 && xclick <= 440 && yclick >= 100 && yclick <= 180)
                {
                    is_end = 0;
                    for(ll i=1;i<=n;i++)
                        for (ll j = 1; j <= m; j++)
                        {
                            mp[i][j] = 0;
                        }
                    draw(0);
                }
            }
            continue;
        }
        else if (kbhit())
        {
            cnt++;
            ll ch2 = getch();
            if (ch2 == 119)
                change("up");
            else if (ch2 == 115)
                change("down");
            else if (ch2 == 100)
                change("right");
            else if (ch2 == 97)
                change("left");
            else continue;
            FILE* fpc = NULL;
            fopen_s(&fpc, "data.txt", "w");
            for (ll i = 1; i <= n; i++)
            {
                for (ll j = 1; j <= m; j++)
                {
                    fprintf(fpc, "%lld ", mp[i][j]);
                }
                fprintf(fpc, "\n");
            }
            fclose(fpc);
            random_add();
            draw(0);
            if (check_die())
            {
                is_end = 1;
            }
        }   
        //接受死亡之前的鼠标信息
        while (mousemsg())
        {
            m_msg = getmouse();
        }
    }
}
//是否有存档
//有存档则可以继续游戏
//否则重开一局
void load_last()
{
    key_msg k_msg;
    mouse_msg m_msg;
    //开始界面如果按下任意键或者单机鼠标左键
    putimage(0,0,beginning);
    xyprintf(200, 0, "记得换输入法");
    for (; is_run(); delay_fps(60))
    {
        ll isclick = 0,keydown=0;
        while (mousemsg())
        {
            m_msg = getmouse();
            if (m_msg.is_left() && m_msg.is_down())
            {
                isclick = 1;
            }
        }
        while (kbmsg())
        {
            k_msg = getkey();
            if (k_msg.msg==KEYMSG_DOWN)
            {
                keydown = 1;
            }
        }
        if (isclick || keydown)
        {
            break;
        }
    }
    putimage(0, 0, background_image);
    FILE* fp = NULL;
    fopen_s(&fp, "data.txt", "r");
    if (fp != NULL)
    {
        predraw();
        for (; is_run(); delay_fps(60))
        {
            ll isclick = 0, xclick = 0, yclick = 0;
            while (mousemsg())
            {
                m_msg = getmouse();
                if (m_msg.is_left() && m_msg.is_down())
                {
                    isclick = 1;
                    xclick = m_msg.x;
                    yclick = m_msg.y;
                }
            }                
            if (isclick&&xclick>= 90 && xclick<= 430 && yclick>=100&&yclick<=175)
            {
                remove("data.txt");
                memset(mp, 0, sizeof(mp));
                break;
            }
            else if (isclick&&xclick >= 90 && xclick <= 430 && yclick >= 300 && yclick <= 380)
            {
                for (ll i = 1; i <= n; i++)
                {
                    for (ll j = 1; j <= m; j++)
                    {
                        fscanf_s(fp, "%lld", &mp[i][j]);
                    }
                }
                break;
            }
        }
    }
    else
    {
        putimage(90, 100, begin_play);
        for (; is_run(); delay_fps(60))
        {
            ll isclick = 0, xclick = 0, yclick = 0;
            while (mousemsg())
            {
                m_msg = getmouse();
                if (m_msg.is_left() && m_msg.is_down())
                {
                    isclick = 1;
                    xclick = m_msg.x;
                    yclick = m_msg.y;
                }
            }
            if (xclick >= 90 && xclick <= 430 && yclick >= 100 && yclick <= 180)
            {
                memset(mp, 0, sizeof(mp));
                break;
            }
        }
    }
    if(fp!=NULL)
        fclose(fp);
}

int main()
{
    srand(int(time(0)));
    initgraph(500, 500, 0);
    setcaption("cyberponk2048");
    setbkcolor(WHITE);  
    load_image(); 
    n = 4, m = 4;
    load_last();
    game();
}