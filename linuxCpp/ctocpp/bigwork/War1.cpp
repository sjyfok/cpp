#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <memory>

using namespace std;
//定义各种变量
int M, N, K, T;//每个司令部的初始生命元数量,城市数量，忠诚衰减量，截止时间量
int r_n, b_n, r_w = 1, b_w = 1;//红蓝双方的生命元数，红蓝双方要制造的武士类型
int d_str, n_str, i_str, l_str, w_str;//初始生命值
int d_for, n_for, i_for, l_for, w_for;//攻击力
int strmin;//几种武士中最小的生命值
int hour, minute, _hour, _minute;//没有_是现在时间，有_是限定时间
int flag_redcreate, flag_bluecreate, flag_redtaken, flag_bluetaken;
//武器
class weapon {
public:
    int num;
    string name;
};
//司令部
class base
{
public:
    string type;
    int warriors;
    int locat;//所处地
    int d_n, n_n, i_n, l_n, w_n;
    int source;//生命元
};
//武士
class warrior {
public:
    int str;//生命值
    int id;//编号
    int forcew[4];
    string type;//种类
    weapon weapons[4];//三种类型的武器的数量 第四种是用过的arrow
    int force;//战力
    int posi;//当前所在地点编号
    base*mast;//司令部
    int state;//状态0：逃逸或死亡 1：存活
    int loyalty;//忠诚值
                //总体初始化
    void mainset(base*a) {
        mast = a;
        id = (*a).warriors;
        posi = (*a).locat;
        state = 1;
        loyalty = 0;
        for (int i = 0; i <= 3; i++)
        {
            weapons[i].num = 0;
        }
    }
    void subset2() {
        for (int i = 0; i <= 3; i++)
            switch (i) {
            case 0: {weapons[i].name = "sword"; forcew[i] = force * 2 / 10; break; }
            case 1: {weapons[i].name = "bomb"; forcew[i] = force * 4 / 10;  break; }
            case 2: {weapons[i].name = "arrow"; forcew[i] = force * 3 / 10;  break; }
            case 3: {weapons[i].name = "arrow";  forcew[i] = force * 3 / 10; break; }
            }
    }
    //细化初始化
    virtual void rob(warrior*sb) {}
    virtual void subset() = 0;
    virtual void yell() {};
    virtual void attack(warrior*sb, int weaponid) {
        weapons[weaponid].num--;
        switch (weaponid) {
        case 0: {sb->str -= force * 2 / 10; weapons[weaponid].num++;  break; }
        case 1: {sb->str -= force * 4 / 10; str -= (force * 4 / 10) / 2; break; }
        case 2: {sb->str -= force * 3 / 10; weapons[3].num++; break; }
        case 3: {sb->str -= force * 3 / 10;  break; }
        }
    }
    virtual void toescape() {}
    //行军
    void march();
    void die();
    void getweapon(warrior*sb) {
        int max0 = 10;
        for (int i = 0; i <= 3; i++)max0 -= weapons[i].num;
        for (int i = 0; i <= 3 && max0>0; i++) {
            for (int j = 1; j <= sb->weapons[i].num&&max0>0; j++) {
                max0--;
                weapons[i].num++;
            }
        }
    }
};
//城市
class city {
public:
    int soldier_n;
    warrior* red;
    warrior* blue;
}allcity[30];
//行军
void warrior::march() {
    if (type == "iceman")
    {
        str -= str / 10;
        if (str <= 0)
            die();
    }
    if (type == "lion")
        loyalty -= K;
    if ((*mast).type == "red"&&state)
        posi++;
    else if ((*mast).type == "blue"&&state)
        posi--;
}
void warrior::die() {
    allcity[posi].soldier_n--;
    if ((*mast).type == "red")
        allcity[posi].red = NULL;
    if ((*mast).type == "blue")
        allcity[posi].blue = NULL;
    posi = -1;
    state = 0;
}
//武士-dragon
class dragon :public warrior {
public:
    void subset() {
        str = d_str;
        type = "dragon";
        weapons[id % 3].num++;
        force = d_for;
    }
    void yell() {
        printf("%03d:%02d %s dragon %d yelled in city %d\n", hour, minute, (*mast).type.c_str(), id, posi);
    }
};
//武士-ninja
class ninja :public warrior {
public:
    void subset() {
        str = n_str;
        type = "ninja";
        weapons[id % 3].num++;
        weapons[(id + 1) % 3].num++;
        force = n_for;
    }
    void attack(warrior*sb, int weaponid) {
        weapons[weaponid].num--;
        switch (weaponid) {
        case 0: {sb->str -= force * 2 / 10; weapons[weaponid].num++;   break; }
        case 1: {sb->str -= force * 4 / 10;  break; }
        case 2: {sb->str -= force * 3 / 10; weapons[3].num++; break; }
        case 3: {sb->str -= force * 3 / 10;  break; }
        }
    }
};
//武士-iceman
class iceman :public warrior {
public:
    void subset() {
        str = i_str;
        type = "iceman";
        weapons[id % 3].num++;
        force = i_for;
    }
    void yell() {}
};
//武士-wolf
class wolf :public warrior {
public:
    void subset() {
        str = w_str;
        type = "wolf";
        force = w_for;
    }
    void rob(warrior*sb)//抢夺武器
    {
        int max0 = 10;
        for (int i = 0; i <= 3; i++)max0 -= weapons[i].num;
        if (max0 && (sb->weapons[0].num + sb->weapons[1].num + sb->weapons[2].num + sb->weapons[3].num))
        {
            for (int i = 0; i <= 2; i++)
            {
                if ((i == 0 || i == 1) && sb->weapons[i].num != 0) {
                    int get = min(max0, sb->weapons[i].num);
                    sb->weapons[i].num -= get;
                    weapons[i].num += get;
                    printf("%03d:%02d %s wolf %d took %d %s from %s %s %d in city %d\n", hour, minute, ((*mast).type).c_str(), id, get, weapons[i].name.c_str(), ((*(sb->mast)).type).c_str(), (sb->type).c_str(), sb->id, posi);
                    break;
                }
                else if (i == 2) {
                    int get = min(max0, sb->weapons[i].num + sb->weapons[i + 1].num);
                    int extra = get - sb->weapons[i].num;
                    if (extra > 0) {
                        weapons[i].num += sb->weapons[i].num;
                        weapons[3].num += extra;
                        sb->weapons[i].num = 0;
                        sb->weapons[i + 1].num -= extra;
                    }
                    else {
                        sb->weapons[i].num -= get;
                        weapons[i].num += get;
                    }
                    printf("%03d:%02d %s wolf %d took %d %s from %s %s %d in city %d\n", hour, minute, ((*mast).type).c_str(), id, get, weapons[i].name.c_str(), ((*(sb->mast)).type).c_str(), (sb->type).c_str(), sb->id, posi);
                }
            }
        }
    }
    void yell() {}
};
//武士-lion
class lion :public warrior
{
public:
    void subset() {
        str = l_str;
        type = "lion";
        force = l_for;
        weapons[id % 3].num++;
        loyalty = (*mast).source;
    }
    //逃跑
    void toescape() {
        state = 0;
        if (posi <= N&&posi >= 1)
        {
            if ((*mast).type == "red")
                allcity[posi].red = NULL;
            else if ((*mast).type == "blue")
                allcity[posi].blue = NULL;
            allcity[posi].soldier_n--;
        }
        posi = -1;
        printf("%03d:%02d ", hour, minute);
        cout << (*mast).type;
        printf(" lion %d ran away\n", id);
    }
    void yell() {}
};
//循环链表：制造武士
struct node {
    char type;
    node*next;
};
//又一波定义
warrior*redwaror[1000];
warrior*bluewaror[1000];
dragon d_r[100], d_b[100];
ninja n_r[100], n_b[100];
iceman i_r[100], i_b[100];
lion l_r[100], l_b[100];
wolf w_r[100], w_b[100];
base r;
base b;
node*red, *blue;
node redline, redline1, redline2, redline3, redline4, blueline, blueline1, blueline2, blueline3, blueline4;
void lineset() {
    redline.type = 'i';
    redline1.type = 'l';
    redline2.type = 'w';
    redline3.type = 'n';
    redline4.type = 'd';
    redline.next = &redline1;
    redline1.next = &redline2;
    redline2.next = &redline3;
    redline3.next = &redline4;
    redline4.next = &redline;
    blueline.type = 'l';
    blueline1.type = 'd';
    blueline2.type = 'n';
    blueline3.type = 'i';
    blueline4.type = 'w';
    blueline.next = &blueline1;
    blueline1.next = &blueline2;
    blueline2.next = &blueline3;
    blueline3.next = &blueline4;
    blueline4.next = &blueline;
    red = &redline;
    blue = &blueline;
}
//初始化
void mem() {
    //司令部初始化
    red = &redline;
    blue = &blueline;
    flag_bluecreate = 1, flag_redcreate = 1;
    r.type = "red", b.type = "blue";
    r.warriors = 0, b.warriors = 0;
    r.locat = 0, b.locat = N + 1;
    r.d_n = 0, r.i_n = 0, r.l_n = 0, r.n_n = 0, r.w_n = 0;
    b.d_n = 0, b.i_n = 0, b.l_n = 0, b.n_n = 0, b.w_n = 0;
    r.source = M, b.source = M;
    flag_bluetaken = 0, flag_redtaken = 0;
    //最小初始生命值初始化
    strmin = min(d_str, i_str);
    strmin = min(strmin, n_str);
    strmin = min(strmin, l_str);
    strmin = min(strmin, w_str);
    //城市初始化
    for (int i = 0; i <= N + 1; i++)
    {
        allcity[i].soldier_n = 0;
        allcity[i].red = NULL;
        allcity[i].blue = NULL;
    }
    //时间初始化
    hour = 0, minute = 0;
    _hour = T / 60, _minute = T % 60;
}
//输入
void init() {
    cin >> M >> N >> K >> T;
    cin >> d_str >> n_str >> i_str >> l_str >> w_str;
    cin >> d_for >> n_for >> i_for >> l_for >> w_for;
}
//制造武士
void createwarriors() {
    if (flag_redcreate) {
        switch ((*red).type) {
        case 'i':
            if (r.source >= i_str) {
                r.source -= i_str;
                r.i_n++;
                r.warriors++;
                i_r[r.i_n].mainset(&r);
                i_r[r.i_n].subset(); i_r[r.i_n].subset2();
                redwaror[r.warriors] = &i_r[r.i_n];
                printf("%03d:%02d red iceman %d born\n", hour, minute, r.warriors);
                allcity[0].soldier_n = 1;
                allcity[0].red = &i_r[r.i_n];
                break;
            }
            else {
                flag_redcreate = 0;
                break;
            }
        case 'l':
            if (r.source >= l_str) {
                r.source -= l_str;
                r.l_n++;
                r.warriors++;
                l_r[r.l_n].mainset(&r);
                l_r[r.l_n].subset(); l_r[r.l_n].subset2();
                redwaror[r.warriors] = &l_r[r.l_n];
                printf("%03d:%02d red lion %d born\n", hour, minute, r.warriors);
                printf("Its loyalty is %d\n", l_r[r.l_n].loyalty);
                allcity[0].soldier_n = 1;
                allcity[0].red = &l_r[r.l_n];
                break;
            }
            else {
                flag_redcreate = 0;
                break;
            }
        case 'w':
            if (r.source >= w_str) {
                r.source -= w_str;
                r.w_n++;
                r.warriors++;
                w_r[r.w_n].mainset(&r);
                w_r[r.w_n].subset(); w_r[r.w_n].subset2();
                redwaror[r.warriors] = &w_r[r.w_n];
                printf("%03d:%02d red wolf %d born\n", hour, minute, r.warriors);
                allcity[0].soldier_n = 1;
                allcity[0].red = &w_r[r.w_n];
                break;
            }
            else {
                flag_redcreate = 0;
                break;
            }
        case 'n':
            if (r.source >= n_str) {
                r.source -= n_str;
                r.n_n++;
                r.warriors++;
                n_r[r.n_n].mainset(&r);
                n_r[r.n_n].subset(); n_r[r.n_n].subset2();
                redwaror[r.warriors] = &n_r[r.n_n];
                printf("%03d:%02d red ninja %d born\n", hour, minute, r.warriors);
                allcity[0].soldier_n = 1;
                allcity[0].red = &n_r[r.n_n];
                break;
            }
            else {
                flag_redcreate = 0;
                break;
            }
        case 'd':
            if (r.source >= d_str) {
                r.source -= d_str;
                r.d_n++;
                r.warriors++;
                d_r[r.d_n].mainset(&r);
                d_r[r.d_n].subset(); d_r[r.d_n].subset2();
                redwaror[r.warriors] = &d_r[r.d_n];
                allcity[0].soldier_n = 1;
                allcity[0].red = &d_r[r.d_n];
                printf("%03d:%02d red dragon %d born\n", hour, minute, r.warriors);
                break;
            }
            else {
                flag_redcreate = 0;
                break;
            }
        }
        red = red->next;
    }
    if (flag_bluecreate) {
        switch ((*blue).type) {
        case 'i':
            if (b.source >= i_str) {
                b.source -= i_str;
                b.i_n++;
                b.warriors++;
                i_b[b.i_n].mainset(&b);
                i_b[b.i_n].subset(); i_b[b.i_n].subset2();
                bluewaror[b.warriors] = &i_b[b.i_n];
                printf("%03d:%02d blue iceman %d born\n", hour, minute, b.warriors);
                allcity[N + 1].soldier_n = 1;
                allcity[N + 1].blue = &i_b[b.i_n];
                break;
            }
            else {
                flag_bluecreate = 0;
                break;
            }
        case 'l':
            if (b.source >= l_str) {
                b.source -= l_str;
                b.l_n++;
                b.warriors++;
                l_b[b.l_n].mainset(&b);
                l_b[b.l_n].subset(); l_b[b.l_n].subset2();
                bluewaror[b.warriors] = &l_b[b.l_n];
                printf("%03d:%02d blue lion %d born\n", hour, minute, b.warriors);
                printf("Its loyalty is %d\n", l_b[b.l_n].loyalty);
                allcity[N + 1].soldier_n = 1;
                allcity[N + 1].blue = &l_b[b.l_n];
                break;
            }
            else {
                flag_bluecreate = 0;
                break;
            }
        case 'w':
            if (b.source >= w_str) {
                b.source -= w_str;
                b.w_n++;
                b.warriors++;
                w_b[b.w_n].mainset(&b);
                w_b[b.w_n].subset(); w_b[b.w_n].subset2();
                bluewaror[b.warriors] = &w_b[b.w_n];
                printf("%03d:%02d blue wolf %d born\n", hour, minute, b.warriors);
                allcity[N + 1].soldier_n = 1;
                allcity[N + 1].blue = &w_b[b.w_n];
                break;
            }
            else {
                flag_bluecreate = 0;
                break;
            }
        case 'n':
            if (b.source >= n_str) {
                b.source -= n_str;
                b.n_n++;
                b.warriors++;
                n_b[b.n_n].mainset(&b);
                n_b[b.n_n].subset(); n_b[b.n_n].subset2();
                bluewaror[b.warriors] = &n_b[b.n_n];
                printf("%03d:%02d blue ninja %d born\n", hour, minute, b.warriors);
                allcity[N + 1].soldier_n = 1;
                allcity[N + 1].blue = &n_b[b.n_n];
                break;
            }
            else {
                flag_bluecreate = 0;
                break;
            }
        case 'd':
            if (b.source >= d_str) {
                b.source -= d_str;
                b.d_n++;
                b.warriors++;
                d_b[b.d_n].mainset(&b);
                d_b[b.d_n].subset(); d_b[b.d_n].subset2();
                bluewaror[b.warriors] = &d_b[b.d_n];
                printf("%03d:%02d blue dragon %d born\n", hour, minute, b.warriors);
                allcity[N + 1].soldier_n = 1;
                allcity[N + 1].blue = &d_b[b.d_n];
                break;
            }
            else {
                flag_bluecreate = 0;
                break;
            }
        }
        blue = blue->next;
    }
}
//狮子逃跑
void lionsescape() {
    for (int i = 0; i <= N + 1; i++) {
        if (allcity[i].red != NULL)
        {
            if ((*allcity[i].red).type == "lion" && (*allcity[i].red).loyalty <= 0)
                (*allcity[i].red).toescape();
        }
        if (allcity[i].blue != NULL)
        {
            if ((*allcity[i].blue).type == "lion" && (*allcity[i].blue).loyalty <= 0)
                (*allcity[i].blue).toescape();
        }
    }
}
//行军
void marching() {
    for (int i = 0; i <= N + 1; i++) {
        if (allcity[i].red)
            allcity[i].red->march();
        if (allcity[i].blue)
            allcity[i].blue->march();
    }
    //清空城市指针
    for (int i = 0; i <= N + 1; i++)
        allcity[i].soldier_n = 0, allcity[i].blue = NULL, allcity[i].red = NULL;
    for (int i = 1; i <= r.warriors; i++)
    {
        allcity[redwaror[i]->posi].soldier_n++;
        allcity[redwaror[i]->posi].red = redwaror[i];
    }
    for (int i = 1; i <= b.warriors; i++)
    {
        allcity[bluewaror[i]->posi].soldier_n++;
        allcity[bluewaror[i]->posi].blue = bluewaror[i];
    }
    for (int i = 0; i <= N + 1; i++) {
        if (i == 0 && allcity[i].soldier_n) {
            printf("%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, allcity[i].blue->str, allcity[i].blue->force);
            printf("%03d:%02d red headquarter was taken\n", hour, minute);
        }
        else if (i == N + 1 && allcity[i].soldier_n) {
            printf("%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].red->str, allcity[i].red->force);
            printf("%03d:%02d blue headquarter was taken\n", hour, minute);
        }
        else {
            if (allcity[i].red)
                printf("%03d:%02d red %s %d marched to city %d with %d elements and force %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, i, allcity[i].red->str, allcity[i].red->force);
            if (allcity[i].blue)
                printf("%03d:%02d blue %s %d marched to city %d with %d elements and force %d\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, i, allcity[i].blue->str, allcity[i].blue->force);
        }
    }
}
//wolf抢武器 dangerous!
void wolfrobbing() {
    for (int i = 1; i <= N; i++)
    {
        if (allcity[i].soldier_n == 2)
        {
            if (allcity[i].red&&allcity[i].red->type == "wolf")
            {
                if (allcity[i].blue->type != "wolf")
                    allcity[i].red->rob(allcity[i].blue);
            }
            else if (allcity[i].blue&&allcity[i].blue->type == "wolf")
            {
                allcity[i].blue->rob(allcity[i].red);
            }
        }
    }
}
//战斗
void battle() {
    for (int i = 1; i <= N; i++)
    {
        if (allcity[i].soldier_n == 2) {
            int countr[4] = { allcity[i].red->weapons[0].num,allcity[i].red->weapons[1].num,allcity[i].red->weapons[2].num ,allcity[i].red->weapons[3].num };
            int countb[4] = { allcity[i].blue->weapons[0].num,allcity[i].blue->weapons[1].num,allcity[i].blue->weapons[2].num ,allcity[i].blue->weapons[3].num };
            while (1) {
                int weapr = -1, weapb = -1;
                int flagr = 0, flagb = 0;
                if (countr[0] + countr[1] + countr[2] + countr[3] == 0)
                    for (int j = 0; j <= 3; j++)countr[j] = allcity[i].red->weapons[j].num;
                if (countr[1] + countr[2] + countr[3] == 0)flagr = 1;
                if (countb[0] + countb[1] + countb[2] + countb[3] == 0)
                    for (int j = 0; j <= 3; j++)countb[j] = allcity[i].blue->weapons[j].num;
                if (countb[1] + countb[2] + countb[3] == 0)flagb = 1;
                for (int j = 0; j <= 1; j++) {
                    if (countr[j])
                    {
                        weapr = j;
                        countr[j]--;
                        break;
                    }
                }
                if (weapr == -1) {
                    if (countr[3])
                    {
                        weapr = 3; countr[3]--;
                    }
                    else if (countr[2])
                    {
                        weapr = 2; countr[2]--;
                    }
                }
                for (int j = 0; j <= 1; j++) {
                    if (countb[j])
                    {
                        weapb = j;
                        countb[j]--;
                        break;
                    }
                }
                if (weapb == -1) {
                    if (countb[3])
                    {
                        weapb = 3; countb[3]--;
                    }
                    else if (countb[2])
                    {
                        weapb = 2; countb[2]--;
                    }
                }
                if ((weapb == -1 && weapr == -1) || (weapr == 0 && weapb == 0 && allcity[i].red->forcew[weapr] == 0 && allcity[i].blue->forcew[weapb] == 0 && flagr&&flagb) || (flagb&&weapb == 0 && weapr == -1 && allcity[i].blue->forcew[weapb] == 0) || (flagr&&weapr == 0 && weapb == -1 && allcity[i].red->forcew[weapr] == 0))
                {
                    printf("%03d:%02d both red %s %d and blue %s %d were alive in city %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i);
                    break;
                }
                if (i % 2)
                {
                    if (weapr >= 0)
                    {
                        allcity[i].red->attack(allcity[i].blue, weapr);
                        if (allcity[i].blue->str <= 0 && allcity[i].red->str <= 0) {
                            printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i);
                            allcity[i].blue->die();
                            allcity[i].red->die();
                            break;
                        }
                        if (allcity[i].blue->str <= 0) {
                            allcity[i].red->getweapon(allcity[i].blue);
                            printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i, allcity[i].red->str);
                            allcity[i].blue->die();
                            break;
                        }
                        if (allcity[i].red->str <= 0) {
                            allcity[i].blue->getweapon(allcity[i].red);
                            printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, allcity[i].red->type.c_str(), allcity[i].red->id, i, allcity[i].blue->str);
                            allcity[i].red->die();
                            break;
                        }
                    }
                    if (allcity[i].blue->str > 0 && weapb >= 0)
                    {
                        allcity[i].blue->attack(allcity[i].red, weapb);
                        if (allcity[i].blue->str <= 0 && allcity[i].red->str <= 0) {
                            printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i);
                            allcity[i].blue->die();
                            allcity[i].red->die();
                            break;
                        }
                        if (allcity[i].red->str <= 0) {
                            allcity[i].blue->getweapon(allcity[i].red);
                            printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, allcity[i].red->type.c_str(), allcity[i].red->id, i, allcity[i].blue->str);
                            allcity[i].red->die();
                            break;
                        }
                        if (allcity[i].blue->str <= 0) {
                            allcity[i].red->getweapon(allcity[i].blue);
                            printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i, allcity[i].red->str);
                            allcity[i].blue->die();
                            break;
                        }
                    }
                }
                else {
                    if (weapb >= 0)
                    {
                        allcity[i].blue->attack(allcity[i].red, weapb);
                        if (allcity[i].blue->str <= 0 && allcity[i].red->str <= 0) {
                            printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i);
                            allcity[i].blue->die();
                            allcity[i].red->die();
                            break;
                        }
                        if (allcity[i].red->str <= 0) {
                            allcity[i].blue->getweapon(allcity[i].red);
                            printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, allcity[i].red->type.c_str(), allcity[i].red->id, i, allcity[i].blue->str);
                            allcity[i].red->die();
                            break;
                        }
                        if (allcity[i].blue->str <= 0) {
                            allcity[i].red->getweapon(allcity[i].blue);
                            printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i, allcity[i].red->str);
                            allcity[i].blue->die();
                            break;
                        }
                    }
                    if (allcity[i].red->str > 0 && weapr >= 0)
                    {
                        allcity[i].red->attack(allcity[i].blue, weapr);
                        if (allcity[i].blue->str <= 0 && allcity[i].red->str <= 0) {
                            printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i);
                            allcity[i].blue->die();
                            allcity[i].red->die();
                            break;
                        }
                        if (allcity[i].blue->str <= 0) {
                            allcity[i].red->getweapon(allcity[i].blue);
                            printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].blue->type.c_str(), allcity[i].blue->id, i, allcity[i].red->str);
                            allcity[i].blue->die();
                            break;
                        }
                        if (allcity[i].red->str <= 0) {
                            allcity[i].blue->getweapon(allcity[i].red);
                            printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, allcity[i].red->type.c_str(), allcity[i].red->id, i, allcity[i].blue->str);
                            allcity[i].red->die();
                            break;
                        }
                    }
                }
            }
            if (allcity[i].red && (allcity[i].red)->type == "dragon")
                allcity[i].red->yell();
            if (allcity[i].blue && (allcity[i].blue)->type == "dragon")
                allcity[i].blue->yell();
        }
    }
}
//报告生命元数
void reportsource() {
    printf("%03d:%02d %d elements in red headquarter\n", hour, minute, r.source);
    printf("%03d:%02d %d elements in blue headquarter\n", hour, minute, b.source);
}
//武士报告
void reportwaror() {
    for (int i = 0; i <= N + 1; i++) {
        if (allcity[i].red)
            printf("%03d:%02d red %s %d has %d sword %d bomb %d arrow and %d elements\n", hour, minute, allcity[i].red->type.c_str(), allcity[i].red->id, allcity[i].red->weapons[0].num, allcity[i].red->weapons[1].num, allcity[i].red->weapons[2].num + allcity[i].red->weapons[3].num, allcity[i].red->str);
        if (allcity[i].blue)
            printf("%03d:%02d blue %s %d has %d sword %d bomb %d arrow and %d elements\n", hour, minute, allcity[i].blue->type.c_str(), allcity[i].blue->id, allcity[i].blue->weapons[0].num, allcity[i].blue->weapons[1].num, allcity[i].blue->weapons[2].num + allcity[i].blue->weapons[3].num, allcity[i].blue->str);
    }
}
int main()
{
    int n;//case数
    cin >> n;
    lineset();
    for (int c = 1; c <= n; c++) {
        int a = 1;
        init();
        mem();
        printf("Case %d:\n", c);
        while (1) {
            //0min
            minute = 0;
            if (hour == _hour&&minute > _minute)
                break;
            createwarriors();
            //5min
            minute = 5;
            if (hour == _hour&&minute > _minute)
                break;
            lionsescape();
            //10min
            minute = 10;
            if (hour == _hour&&minute > _minute)
                break;
            marching();
            if (allcity[0].soldier_n || allcity[N + 1].soldier_n)
                break;
            //35min
            minute = 35;
            if (hour == _hour&&minute > _minute)
                break;
            wolfrobbing();
            //40min
            minute = 40;
            if (hour == _hour&&minute > _minute)
                break;
            battle();
            //50min
            minute = 50;
            if (hour == _hour&&minute > _minute)
                break;
            reportsource();
            //55min
            minute = 55;
            if (hour == _hour&&minute > _minute)
                break;
            reportwaror();
            hour++;
        }
    }
    return 0;
}