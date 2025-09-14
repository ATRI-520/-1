#ifndef _map_and_background_HPP_
#define _map_and_background_HPP_

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<vector>
#include<algorithm>

class camera;
class character_can_talk;
class object_can_pick;
class object_barrier;
using namespace std;

class map_b_g
{
public:

    //出口
    vector<SDL_Rect> v_chu_kou;

    Mix_Music *bgm = NULL;
    //动态的字符串
    string s;

    //相机
    camera *cam = NULL;

    //地图显示帧率
    pair<int , int> x_j_z_l = make_pair(SDL_GetTicks() , 25);


    SDL_Window *win=NULL;
    SDL_Renderer *rd=NULL;
    //大地图
    SDL_Surface *sf=NULL;
    SDL_Texture *tx=NULL;


    //地图中NPC的容器
    vector <character_can_talk *> v_npc;

    //地图中的可拾取物容器
    vector <object_can_pick *> v_pick;

    //地图中的障碍物
    vector <object_barrier *> v_barrier;

    map_b_g(SDL_Window *win,
        SDL_Renderer * &rd,
        char *b_t);
    //将整个大地图渲染在窗口上
    void jing_tai();
    //
    void dong_tai();


    //设置NPC
    void set_v_npc();
    //设置可拾取物
    void set_v_pick();
    //设置障碍物
    void set_v_barrier();

    void zong_di_tu();


    void set_cam(double w_x_bi_li = 0.5);

    void let_npc_move();


    void bgm_play();
    //
    ~map_b_g();
};



#endif