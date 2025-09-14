#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;
class camera;
class object_base
{
public:
    //目标区域的中心
    pair <int,int>object_z_x;
    pair <int,int>object_b_j_z_x;
    SDL_Surface *di_tu_sf =NULL;
    SDL_Surface *sf = NULL;
    SDL_Texture *tx = NULL;
    //SDL_Rect rt_yuan;
    SDL_Rect object_mu_biao;
    //大背景区域
    SDL_Rect rt_b_j;
    SDL_Renderer *rd = NULL;
    object_base();
    object_base(char *tu_pian 
                , SDL_Renderer *&rd
                , pair<int ,int> object_b_j_z_x = make_pair(0, 0)
                , pair<int ,int> w_h = make_pair(100, 100)
                );
                
    void set_rt_b_j(pair<int ,int> w_h);
    //相对于窗口的中心
    void set_object_z_x(camera *cam);
    //窗口的什么区域
    void set_object_mu_biao(double w_x_bi_li);
    void xiang_ji_x_r();

};

class object_can_pick : public object_base
{
public:
    //物品名称
    char *name = NULL;
    bool is_pick = false;
    //string name_hua;
    object_can_pick(char *name
                , char *tu_pian 
                , SDL_Renderer *rd
                , pair<int ,int> object_b_j_z_x = make_pair(0, 0)
                , pair<int ,int> w_h = make_pair(100, 100));
};


class object_barrier : public object_base
{
public:
    bool have_tx;
    SDL_Rect barrier;
    pair <int,int> barrier_b_j_z_x;
    void change_tx(int tou_ming_du);
    object_barrier(SDL_Rect barrier
                , char *tu_pian =NULL 
                , SDL_Renderer *rd =NULL
                , pair<int ,int> object_b_j_z_x = make_pair(0, 0)
                , pair<int ,int> w_h = make_pair(100, 100)
                );
    object_barrier(SDL_Rect barrier,int);
    //
    void set_barrier_b_j_z_x();
};