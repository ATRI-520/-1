#ifndef _camera_HPP_
#define _camera_HPP_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>

using namespace  std;
 
class character_can_talk;
class object_barrier;
class object_can_pick;

class camera
{
public:
    //相机窗口比例
    double w_x_bi_li;
    //相机区域
    SDL_Rect rt_x_j;
    //相机中心在大地图的位置
    pair<int,int> rt_x_j_z_x;

    //大地图背景的sf
    SDL_Surface *sf = NULL;
    //大地图背景的tx
    SDL_Texture *tx = NULL;

    SDL_Window *win = NULL;
    SDL_Renderer *rd = NULL;

    //相机跟随的角色
    character_can_talk *chater = NULL;

    //在视野里面的NPC
    vector <character_can_talk *> v_now_npc;
    //在视野里面的障碍物
    vector <object_barrier *> v_now_barrier;
    //在视野里面的可拾取物
    vector <object_can_pick *> v_now_pick;

    //主角身边可交互的NPC
    vector <character_can_talk *> v_sheng_bian_npc;
    //主角身边的可拾取物
    vector <object_can_pick *> v_sheng_bian_pick;
    //主角身边的障碍物
    vector <object_barrier *> v_sheng_bian_barrier;

    //遮挡的NPC
    vector <character_can_talk *> v_zhe_dang_npc;
    //遮挡的可拾取物
    vector <object_can_pick *> v_zhe_dang_pick;
    //遮挡的障碍物
    vector <object_barrier *> v_zhe_dang_barrier;


    camera(SDL_Window *win , SDL_Renderer *rd ,SDL_Surface *sf , double w_x_bil_li = 0.5);

    //设置相机相对于大背景的中心
    void set_rt_x_j_z_x(pair<int,int> rt_x_j_z_x);
    //设置相机区域
    void set_rt_x_j();
    //设置相机跟随的人物
    void set_chater(character_can_talk *chater);

    //相机只渲染背景
    void xiang_ji_b_j_x_r();
    //相机总渲染
    void xiang_ji();
    //相机跟随角色
    void follow_chater();

    //获取在视野里面的NPC
    void get_now_npc(vector <character_can_talk *> &v_npc);
    //获取视野里面的障碍物
    void get_now_barrier(vector <object_barrier *> &v_barrier);
    //获取视野里面的可拾取物
    void get_now_pick(vector <object_can_pick *> v_pick);

    //获取身边的可拾取物
    void get_v_sheng_bian_pick();
    //获取主角身边的NPC
    void get_v_sheng_bian_npc();
    //获取主角身边的障碍物
    void get_v_sheng_bian_barrier();

    //获取遮挡的可拾取物
    void get_v_zhe_dang_pick();
    //获取主角遮挡的NPC
    void get_v_zhe_dang_npc();
    //获取主角遮挡的障碍物
    void get_v_zhe_dang_barrier();

    //判断主角身边有没有NPC或者可拾取物
    void chater_talk();


    //
    void tx_change();


    //测试模板函数
    // template <typename T1 , typename T2>
    // void get_now(T1 &befor,T2 &now);

    //渲染NPC
    void now_npc_x_r();
    //渲染可拾取
    void now_pick_x_r();
    //渲染障碍物
    void now_barrier_x_r();

    //渲染未遮挡的NPC
    void zhe_dang_npc_x_r();
    //渲染未遮挡的可拾取物
    void zhe_dang_pick_x_r();
    //渲染未遮挡的障碍物
    void zhe_dang_barrier_x_r();


    bool bao_han(SDL_Rect* outer, SDL_Rect* inner);

};


// template <typename T1 , typename T2>
// void camera::get_now(T1 &befor,T2 &now)
// {
//     if(! befor.empty())
//     {
//         now.clear();
//         for(auto i = befor.begin() ; i<befor.end() ; i++)
//         {
//             if(SDL_HasIntersection(&(*i)->rt_b_j, &rt_x_j))
//             {
//                 (*i)->set_object_z_x(this);
//                 (*i)->set_object_mu_biao(this->w_x_bi_li);
//                 now.push_back(*i);
//             }
//         }
//     }
// }

#endif