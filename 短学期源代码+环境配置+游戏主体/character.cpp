#include"character.hpp"
#include"camera.hpp"
#include"object.hpp"
using namespace std;
extern float shi_jian;
extern float win_changed;
character_no_move::character_no_move(){}
character_no_move::character_no_move(char **d_j , 
                                    //SDL_Window *win , 
                                    SDL_Renderer *rd,
                                    pair<int ,int> ren_wu_b_j_z_x,
                                    pair<int,int> w_h)
{
    this->rd = rd;
    set_ren_wu_b_j_z_x(ren_wu_b_j_z_x);
    set_rt_b_j(w_h);
    for(int i = 0 ; i< 4 ; i++)
    {
        if(d_j[i] !=NULL)
        {
            sf_dai_ji[i] = IMG_Load(d_j[i]);
            tx_dai_ji[i] = SDL_CreateTextureFromSurface(rd,sf_dai_ji[i]);
        }
    }

    this->tiao_jin = w_h.first;
    rt_yuan.w = w_h.first;
    rt_yuan.h = w_h.second;
    //v_t.push_back(make_pair(SDL_GetTicks() , 1000/7));
    
}

void character_no_move::dai_ji()
{
    if(SDL_GetTicks() - v_t[0].first >= v_t[0].second * shi_jian)
    {
        //SDL_GetError();
        v_t[0].first = SDL_GetTicks();
        switch(zou_xiang)
        {
            case 1:
                dai_ji_w();
                break;
            case 2:
                dai_ji_d();
                break;
            case 3:
                dai_ji_s();
                break;
            case 4:
                dai_ji_a();
                break;
        }
    }

}

void character_no_move::dai_ji_w()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_dai_ji[0]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_no_move::dai_ji_d()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_dai_ji[1]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_no_move::dai_ji_s()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_dai_ji[2]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_no_move::dai_ji_a()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_dai_ji[3]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_no_move::dong_zuo_x_r(SDL_Texture *tx)
{
    SDL_RenderCopy(rd,tx,&rt_yuan,&rt_mu_biao);
}

void character_no_move::dai_ji_x_j()
{
    dong_zuo_x_r(tx_dai_ji[zou_xiang - 1]);
}

// void character_no_move::win_w_h_get()
// {
//     SDL_GetWindowSize(win,&(win_w_h.first),&(win_w_h.second));
// }

// void character_no_move::win_z_x_get()
// {
//     win_z_x.first = win_w_h.first/2;
//     win_z_x.second = win_w_h.second/2;
// }

void character_no_move::set_ren_wu_b_j_z_x(pair<int ,int> ren_wu_b_j_z_x)
{
    this->ren_wu_b_j_z_x = ren_wu_b_j_z_x;
}

void character_no_move::set_rt_b_j(pair<int ,int> w_h)
{
    rt_b_j.w = w_h.first;
    rt_b_j.h = w_h.second;
    rt_b_j.x = ren_wu_b_j_z_x.first - rt_b_j.w/2;
    rt_b_j.y = ren_wu_b_j_z_x.second - rt_b_j.h/2;
}

// void character_no_move::z_x_changed()
// {
//     // pair <int,int> temp;
//     // SDL_GetWindowSize(win,&temp.first,&temp.second);
//     win_z_x.first *=win_changed;
//     win_z_x.second *=win_changed;
//     ren_wu_z_x.first *=win_changed;
//     ren_wu_z_x.second *=win_changed;
//     SDL_GetWindowSize(win,&win_w_h.first,&win_w_h.second);
//     rt_mu_biao.w *= win_changed;
//     rt_mu_biao.h *= win_changed;
//     rt_mu_biao.x = ren_wu_z_x.first - rt_mu_biao.w/2;
//     rt_mu_biao.y = ren_wu_z_x.second - rt_mu_biao.h/2;
// }

void character_no_move::set_ren_wu_z_x(camera *cam)
{
    ren_wu_z_x.first = (ren_wu_b_j_z_x.first - cam->rt_x_j.x) * (1.0 / cam->w_x_bi_li);
    ren_wu_z_x.second = (ren_wu_b_j_z_x.second - cam->rt_x_j.y) *(1.0 / cam->w_x_bi_li);
}

void character_no_move::set_rt_mu_biao(double w_x_bi_li)
{
    rt_mu_biao.w = rt_b_j.w *(1.0 / w_x_bi_li);
    rt_mu_biao.h = rt_b_j.h *(1.0 / w_x_bi_li);
    rt_mu_biao.x = ren_wu_z_x.first - rt_mu_biao.w/2;
    rt_mu_biao.y = ren_wu_z_x.second - rt_mu_biao.h/2;
}



////
////
character_can_move::character_can_move(){}
character_can_move::character_can_move(char **d_j , 
                                        SDL_Renderer *rd , 
                                        char **move_t_p ,
                                        pair<int ,int> ren_wu_b_j_z_x,
                                        pair<int ,int> w_h
                                        ):
character_no_move(d_j,rd,ren_wu_b_j_z_x , w_h)
{
    zhuang_tai = 0 ;
    for(int i=0 ; i < 4 ; i++)
    {
        if(move_t_p[i] != NULL)
        {
            sf_move[i] = IMG_Load(move_t_p[i]);
            tx_move[i] = SDL_CreateTextureFromSurface(rd , sf_move[i]);
        }

    }
    //v_t.push_back(make_pair(SDL_GetTicks() , 1000/4));
}

void character_can_move::move_dong_hua()
{
    if(zhuang_tai == 0)
    {
        dai_ji();
    }
    else if(1 <= zhuang_tai && zhuang_tai <=4)
    {
        if(SDL_GetTicks() - v_t[1].first >= v_t[1].second * shi_jian)
        {
            v_t[1].first = SDL_GetTicks();
            switch(zou_xiang)
            {
                case 1:
                    move_w();
                    break;
                case 2:
                    move_d();
                    break;
                case 3:
                    move_s();
                    break;
                case 4:
                    move_a();
                    break;
            }
        }
    }
}

void character_can_move::move_w()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_move[0]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_can_move::move_d()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_move[1]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_can_move::move_s()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_move[2]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_can_move::move_a()
{
    rt_yuan.x += tiao_jin;
    if(rt_yuan.x >= sf_move[3]->w)
    {
        rt_yuan.x = 0;
    }
}

void character_can_move::move_rt_w()
{
    //rt_mu_biao.y -= walk_speed;
    //ren_wu_z_x.second -= walk_speed;
    rt_b_j.y -= walk_speed;
    ren_wu_b_j_z_x.second -= walk_speed;
    //if(rt_mu_biao.y < 0 && tag == -1)
    if(rt_b_j.y < 0 )
    {
        //rt_mu_biao.y += walk_speed;
        //ren_wu_z_x.second += walk_speed;
        //rt_b_j.y += walk_speed;
        rt_b_j.y = 0;
        ren_wu_b_j_z_x.second = rt_b_j.y +rt_b_j.h/2;
        // rt_mu_biao.y = 0;
        // ren_wu_z_x.second = rt_mu_biao.y + rt_mu_biao.h/2;
        // rt_b_j.y += walk_speed;
        // ren_wu_b_j_z_x.second += walk_speed;
        //close_w_w = true;
        
    }
    // if(tag == -1)
    // {
    //     dong_zuo_x_r(tx_move[0]);
    // }
}

void character_can_move::move_rt_d(int w)
{
    //rt_mu_biao.x += walk_speed;
    //ren_wu_z_x.first += walk_speed;
    rt_b_j.x +=walk_speed;
    ren_wu_b_j_z_x.first += walk_speed;
    //if(rt_mu_biao.x + rt_mu_biao.w > win_w_h.first && tag == -1)
    if(rt_b_j.x + rt_b_j.w > w)
    {
        //rt_mu_biao.x -= walk_speed;
        //ren_wu_z_x.first -= walk_speed;
        //rt_b_j.x -=walk_speed;
        //ren_wu_b_j_z_x.first -= walk_speed;
        rt_b_j.x = sf->w - rt_b_j.w;
        ren_wu_b_j_z_x.first = sf->w - rt_b_j.w/2;
        // rt_mu_biao.x = win_w_h.first -rt_mu_biao.w;
        // ren_wu_z_x.first = rt_mu_biao.x +rt_mu_biao.w/2;
        //close_h_d = true;
    }
    // if(tag == -1)
    // {
    //     dong_zuo_x_r(tx_move[1]);
    // }
}

void character_can_move::move_rt_s(int h)
{
    //rt_mu_biao.y += walk_speed;
    //ren_wu_z_x.second += walk_speed;
    rt_b_j.y += walk_speed;
    ren_wu_b_j_z_x.second += walk_speed;
    //if(rt_mu_biao.y + rt_mu_biao.h > win_w_h.second && tag == -1)
    if(rt_b_j.y + rt_b_j.h > h)
    {
        //rt_mu_biao.y -= walk_speed;
        //ren_wu_z_x.second -= walk_speed;
        //rt_b_j.y -= walk_speed;
        //ren_wu_b_j_z_x.second -= walk_speed;
        rt_b_j.y = sf->h - rt_b_j.h;
        ren_wu_b_j_z_x.second = sf->h - rt_b_j.h/2;
        // rt_mu_biao.y = win_w_h.second - rt_mu_biao.h;
        // ren_wu_z_x.second = rt_mu_biao.y + rt_mu_biao.h/2;
        //close_w_s = true;
    }
    // if(tag == -1)
    // {
    //     dong_zuo_x_r(tx_move[2]);
    // }
    
}

void character_can_move::move_rt_a()
{
    //rt_mu_biao.x -= walk_speed;
    //ren_wu_z_x.first -= walk_speed;
    rt_b_j.x -=walk_speed;
    ren_wu_b_j_z_x.first -= walk_speed;
    //if(rt_mu_biao.x < 0 && tag == -1)
    if(rt_b_j.x < 0)
    {
        // rt_mu_biao.x += walk_speed;
        // ren_wu_z_x.first += walk_speed;
        // rt_b_j.x +=walk_speed;
        // ren_wu_b_j_z_x.first += walk_speed;
        rt_b_j.x = 0;
        ren_wu_b_j_z_x.first = rt_b_j.x + rt_b_j.w/2;
        // rt_mu_biao.x = 0;
        // ren_wu_z_x.first = rt_mu_biao.x + rt_mu_biao.w/2;
        //close_h_a = true;
    }
    // if(tag == -1)
    // {
    //     dong_zuo_x_r(tx_move[3]);
    // }
    
}

void character_can_move::move_rt(int w ,int h)
{
    switch(zhuang_tai)
    {
        case 1:
            move_rt_w();
            break;
        case 2:
            move_rt_d(w);
            break;
        case 3:
            move_rt_s(h);
            break;
        case 4:
            move_rt_a();
            break;
    }
}

void character_can_move::set_sf(SDL_Surface *sf)
{
    this->sf = sf;
}

void character_can_move::move_x_j()
{
    if(zhuang_tai == 0)
    {
        dai_ji_x_j();
    }
    else if(1 <= zhuang_tai && zhuang_tai <=4)
    {
        dong_zuo_x_r(tx_move[zhuang_tai-1]);
    }

}

void character_can_move::yu_dao_barrier(object_barrier *barrier)
{
    //SDL_Rect temp_rect = {rt_b_j.x,rt_b_j.y+rt_b_j.h/5*4,rt_b_j.w,rt_b_j.h/5};
    switch (zou_xiang)
    {
    case 1:
        rt_b_j.y = barrier->barrier.y + barrier->barrier.h;
        ren_wu_b_j_z_x.second = barrier->barrier_b_j_z_x.second + barrier->barrier.h/2 + rt_b_j.h/2;
        break;
    case 2:
        rt_b_j.x = barrier->barrier.x - rt_b_j.w;
        ren_wu_b_j_z_x.first = barrier->barrier_b_j_z_x.first - barrier->barrier.w/2 - rt_b_j.w/2;
        break;
    case 3:
        rt_b_j.y = barrier->barrier.y - rt_b_j.h;
        ren_wu_b_j_z_x.second = barrier->barrier_b_j_z_x.second - barrier->barrier.h/2 - rt_b_j.h/2;     
        break;
    case 4:
        rt_b_j.x = barrier->barrier.x + barrier->barrier.w;
        ren_wu_b_j_z_x.first = barrier->barrier_b_j_z_x.first + barrier->barrier.w/2 + rt_b_j.w/2;
        break;
    }
}


/////
/////

//TTF_Font* character_can_talk::font = TTF_OpenFont("SIMSUN.TTC",10);
character_can_talk::character_can_talk(char **d_j , 
                                        SDL_Renderer *rd , 
                                        char **move_t_p ,
                                        pair<int ,int> ren_wu_b_j_z_x,
                                        pair<int ,int> w_h):
character_can_move(d_j,rd,move_t_p,ren_wu_b_j_z_x,w_h)                                        
{
    
}
void character_can_talk::talk(char *text)
{
    if(sf_text != NULL)
        SDL_FreeSurface(sf_text);
    if(tx_text != NULL)
        SDL_DestroyTexture(tx_text);
    sf_text = TTF_RenderUTF8_Blended_Wrapped(font,text,{0,0,0,255},150);
    rt_text.w = sf_text->w;
    rt_text.h = sf_text->h;
    tx_text = SDL_CreateTextureFromSurface(rd,sf_text);
}

void character_can_talk::set_rt_text()
{
    if(sf_text != NULL)
    {
        rt_text.y = rt_mu_biao.y - sf_text->h;
        rt_text.x = ren_wu_z_x.first - sf_text->w/2;
    }
}


void character_can_talk::talk_x_j()
{
    //
    if(SDL_GetTicks() - talk_jian_ge.first >= talk_jian_ge.second)
    {
        talk_jian_ge.first = SDL_GetTicks();
        if(dang_qian_hua == false)
        {
            is_talk = false;
            SDL_FreeSurface(sf_text);
            sf_text = NULL;
            SDL_DestroyTexture(tx_text);
            tx_text = NULL;
            return;
        }

        if(is_wang_cheng == true)
        {
            talk(wang_cheng.data());
            dang_qian_hua = false;
        }
        else
        {
            //SDL_Log(it_will_talk->data());
            talk(it_will_talk->data());
            it_will_talk++;
            if(it_will_talk == will_talk.end())
            {
                it_will_talk = will_talk.begin();
                dang_qian_hua = false;
            }
        }
    }
}

void character_can_talk::talk_x_r()
{
    SDL_RenderCopy(rd,tx_text,NULL,&rt_text);
}

void character_can_talk::set_will_talk(vector <string> &will_talk)
{
    this->will_talk = will_talk;
    it_will_talk = this->will_talk.begin();
}




// void character_can_ATK::ATK_move_d()
// {
//     rt_yuan.x += tiao_jin;
//     if(rt_yuan.x >= sf_ATK_move[0]->w)
//     {
//         rt_yuan.x = 0;
//     }
// }


// void character_can_ATK::ATK_move_a()
// {
//     rt_yuan.x += tiao_jin;
//     if(rt_yuan.x >= sf_ATK_move[1]->w)
//     {
//         rt_yuan.x = 0;
//     }
// }


// void character_can_ATK::ATK_dai_ji_d()
// {
//     rt_yuan.x += tiao_jin;
//     if(rt_yuan.x >= sf_ATK_dai_ji[0]->w)
//     {
//         rt_yuan.x = 0;
//     }
// }


// void character_can_ATK::ATK_dai_ji_a()
// {
//     rt_yuan.x += tiao_jin;
//     if(rt_yuan.x >= sf_ATK_dai_ji[1]->w)
//     {
//         rt_yuan.x = 0;
//     }
// }

// void character_can_ATK::ATK_dai_ji()
// {
//     if(SDL_GetTicks() - v_t[0].first >= v_t[0].second * shi_jian)
//     {
//         v_t[0].first = SDL_GetTicks();
//         switch(zou_xiang)
//         {
//             case 2:
//                 ATK_dai_ji_a();
//                 break;
//             case 4:
//                 ATK_dai_ji_d();
//         }
//     }
// }



// void character_can_ATK::ATK_move_dong_hua()
// {
//     if(SDL_GetTicks() - v_t[0].first >= v_t[0].second * shi_jian)
//     {
//         v_t[0].first = SDL_GetTicks();
//         switch(zhuang_tai)
//         {
//             case 0:
//                 ATK_dai_ji();
//             case 1:
//             case 2:
//             case 3:
//             case 4:
//                 switch (zou_xiang)
//                 {
//                 case 2:
//                     ATK_move_a();
//                     break;
//                 case 4:
//                     ATK_move_d();
//                     break;
//                 }
//         }
//     }
// }
