#include"map_and_background.hpp"
#include"character.hpp"
#include"camera.hpp"
#include"object.hpp"
extern float win_changed;
map_b_g::map_b_g (SDL_Window *win,
                SDL_Renderer *&rd,
                char *b_t
                )
{
    this->win = win;
    this->rd = rd;
    this->s = b_t;

    sf=IMG_Load(s.c_str());
    tx=SDL_CreateTextureFromSurface(rd,sf);
    //设置NPC
    //set_v_npc();
    //设置可拾取物
    //set_v_pick();
    //
    //set_v_barrier();


}
void map_b_g::jing_tai()
{
    bgm_play();
    SDL_RenderCopy(rd,tx,NULL,NULL);
}

void map_b_g::set_v_npc()
{
    //角色1
    char *dai_ji_t_p[4] ={"picture/dai_ji_w.png","picture/dai_ji_d.png","picture/dai_ji_s.png","picture/dai_ji_a.png"};
    char *move_t_p[4] = {"picture/xing_zou_w.png","picture/xing_zou_d.png","picture/xing_zou_s.png","picture/xing_zou_a.png"};
    vector <string> will_talk;
    will_talk.push_back("你过不了这关了，嘿嘿");
    will_talk.push_back("骗你的，嘿嘿");
    will_talk.push_back("赶紧去找道具吧");
    //v_npc.push_back(new character_can_talk(dai_ji_t_p , rd , move_t_p , make_pair(500,778)));
    v_npc.back()->tag=0;
    v_npc.back()->zou_xiang =  3;
    v_npc.back()->zhuang_tai = 0;
    v_npc.back()->set_sf(sf);
    v_npc.back()->set_will_talk(will_talk);
    v_npc.back()->wang_cheng = "afafaw";
    //
}


void map_b_g::set_v_pick()
{
    //拾取物1
    v_pick.push_back(new object_can_pick("54","picture/object.jpg",rd,make_pair(200,200),make_pair(50,50)));
}


void map_b_g::set_v_barrier()
{
    SDL_Rect temp = {1000,1000,2,1};//{1000,1000,200,120};
    v_barrier.push_back(new object_barrier(temp,"picture/object.jpg",rd,make_pair(1100,1100),make_pair(200,200)));
    //SDL_Log("%d %d %d %d",v_barrier.back()->rt_b_j.x,v_barrier.back()->rt_b_j.y,v_barrier.back()->rt_b_j.w,v_barrier.back()->rt_b_j.h);
}




void map_b_g::set_cam(double w_x_bi_li )
{
    cam = new camera(win , rd , sf , w_x_bi_li);
}





void map_b_g::zong_di_tu()
{
    bgm_play();
    if(SDL_GetTicks() - x_j_z_l.first >= x_j_z_l.second)
    {
        x_j_z_l.first = SDL_GetTicks();
        let_npc_move();


        //获取视野里面的障碍物
        cam->get_now_barrier(v_barrier);
        cam->get_v_sheng_bian_barrier();
        if(!cam->v_sheng_bian_barrier.empty())
        {
            cam->chater->yu_dao_barrier(cam->v_sheng_bian_barrier.back());
        }


        cam->follow_chater();


        //获取视野里的NPC
        cam->get_now_npc(v_npc);
        //获取视野里面的可拾取物
        cam->get_now_pick(v_pick);
        //获取视野里面的障碍物
        cam->get_now_barrier(v_barrier);
        cam->tx_change();


        cam->get_v_sheng_bian_barrier();
        cam->get_v_sheng_bian_pick();
        cam->get_v_sheng_bian_npc();

        cam->get_v_zhe_dang_npc();
        cam->get_v_zhe_dang_pick();
        cam->get_v_zhe_dang_barrier();
        
        
        cam->chater_talk();
        cam->xiang_ji();
    }
}


//NPC的移动和说话
void map_b_g::let_npc_move()
{
    
    {
        if( ! v_npc.empty())
        {
            for(vector <character_can_talk *>::iterator i =v_npc.begin() ; i < v_npc.end() ; i++)
            {
                (*i)->move_dong_hua();
                (*i)->move_rt(cam->sf->w ,cam->sf->h);
                if((*i)->is_talk == true && i != v_npc.end()-1)
                {
                    (*i)->talk_x_j();
                }
            }
        }
    }
}


void map_b_g::bgm_play()
{
    if(!Mix_PlayingMusic() && bgm != NULL)
    {
        Mix_PlayMusic(bgm, -1);
    }
}


// void map_b_g::ATK_let_npc_move()
// {

// }

// void map_b_g::ATK_zong_di_tu()
// {

// }




// void map_b_g::get_now_npc(vector <character_can_move *> &v_now_npc)
// {
//     if(! v_npc.empty())
//     {
//         v_now_npc.clear();
//         for(vector<character_can_move *>::iterator i = v_npc.begin() ; i<v_npc.end() ; i++)
//         {
//             if(SDL_HasIntersection(&(*i)->rt_b_j, &cam->rt_x_j))
//             {
//                 (*i)->set_ren_wu_z_x(cam);
//                 (*i)->set_rt_mu_biao(cam->w_x_bi_li);
//                 v_now_npc.push_back(*i);
//             }
//         }
//     }
// }