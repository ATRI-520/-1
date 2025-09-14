#ifndef _character_HPP_
#define _character_HPP_

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<vector>

class camera;
class object_barrier;
using namespace std;
class character_no_move
{
public:
    int tag;
    //图片播放跳度
    int tiao_jin=100;
    //面对方向
    int zou_xiang = 3;
    //人物相对于窗口的中心
    pair<int,int> ren_wu_z_x;
    //人物相对于大背景的中心
    pair<int ,int> ren_wu_b_j_z_x;

    //动画播放时间
    vector<pair <int,int> > v_t;

    //SDL_Window *win = NULL;
    SDL_Renderer *rd = NULL;
    SDL_Surface *sf_dai_ji[4]={NULL,NULL,NULL,NULL};
    SDL_Texture *tx_dai_ji[4]={NULL,NULL,NULL,NULL};
    //动画序列的源区域
    SDL_Rect rt_yuan = {0,0,tiao_jin,0};
    //人物播放到窗口的什么区域
    SDL_Rect rt_mu_biao;
    //大背景区域
    SDL_Rect rt_b_j;
    character_no_move();
    character_no_move(char **d_j 
                    , SDL_Renderer *rd 
                    , pair<int ,int> ren_wu_b_j_z_x
                    , pair<int,int> w_h
                    );
    //待机动画的跳度
    void dai_ji_w();
    void dai_ji_d();
    void dai_ji_s();
    void dai_ji_a();
    void dai_ji();
    //动作渲染
    void dong_zuo_x_r(SDL_Texture *tx);
    //设置人物相对于大背景的中心
    void set_ren_wu_b_j_z_x(pair<int ,int> ren_wu_b_j_z_x);
    //设置人物相对于大背景的区域
    void set_rt_b_j(pair<int ,int> w_h);
    //设置人物相对于窗口的中心
    void set_ren_wu_z_x(camera *cam);
    //设置人物相对于窗口的区域
    void set_rt_mu_biao(double w_x_bi_li);
    //用于相机调用待机
    void dai_ji_x_j();
    //~character_no_move();

};
class character_can_move : public character_no_move
{
public:
    //人物在哪个地图里边
    SDL_Surface *sf = NULL;
    //状态机
    int zhuang_tai = 0;
    //行走速度
    int walk_speed = 10;
    //四个移动动画
    SDL_Surface *sf_move[4]={NULL,NULL,NULL,NULL};
    SDL_Texture *tx_move[4]={NULL,NULL,NULL,NULL};
    character_can_move();
    character_can_move(char **d_j 
                    //, SDL_Window *win 
                    , SDL_Renderer *rd
                    , char **move_t_p
                    , pair<int ,int> ren_wu_b_j_z_x 
                    , pair<int ,int> w_h 
                    );
    //动画跳进
    void move_w();
    void move_d();
    void move_s();
    void move_a();
    //根据状态使哪个动画跳进
    void move_dong_hua();
    //如果角色在移动，根据状态进行区域移动
    void move_rt_w();
    void move_rt_d(int w);
    void move_rt_s(int h);
    void move_rt_a();
    void move_rt(int w ,int h);
    //用于相机调用的渲染
    void move_x_j();
    //设置人物在哪个地图里面
    void set_sf(SDL_Surface *sf);
    //遇到障碍物
    void yu_dao_barrier(object_barrier *barrier);

    //~character_can_move();
private:
};

class character_can_talk : public character_can_move
{
public:
    vector <string> will_talk;
    vector <string>::iterator it_will_talk;

    ////
    string wang_cheng;


    
    bool is_wang_cheng = false;
    bool dang_qian_hua = false;
    pair <int, int> talk_jian_ge =make_pair(SDL_GetTicks() , 3000);
    bool is_talk = false;
    SDL_Rect rt_text;
    SDL_Surface *sf_text = NULL;
    SDL_Texture *tx_text = NULL;
    //static TTF_Font *font;
    TTF_Font *font=TTF_OpenFont("SIMSUN.TTC",15);
    character_can_talk(char **d_j , 
                        SDL_Renderer *rd , 
                        char **move_t_p ,
                        pair<int ,int> ren_wu_b_j_z_x,
                        pair<int ,int> w_h);
    void talk(char *text);
    //渲染
    void talk_x_r();
    //相机调用
    void talk_x_j();

    void set_will_talk(vector <string> &will_talk);
    void set_rt_text();
};

// class character_can_ATK : public character_can_move
// {
// public:
//     double HP = 100;
//     double ATK = 10;
//     double DEF;
//     vector<SDL_Texture *> v_pu_tong_ATK;
//     SDL_Surface *sf_ATK_dai_ji[2] = {NULL,NULL};
//     SDL_Texture *tx_ATK_dai_ji[2] = {NULL,NULL};
//     SDL_Surface *sf_ATK_move[2] = {NULL,NULL};
//     SDL_Texture *tx_ATK_move[2] = {NULL,NULL};
//     character_can_ATK();
//     void ATK_dong_hua();
//     void HP_dong_hua();

//     void ATK_dai_ji();
//     void ATK_move_dong_hua();

    
//     void ATK_move_d();
//     void ATK_move_a();
//     void ATK_dai_ji_d();
//     void ATK_dai_ji_a();
// };

// class character_base : public character_can_ATK
// {
// public:
//     vector<SDL_Texture *> v_ji_neng;
// };

// class zhu_jue : public character_base
// {

// };

#endif


