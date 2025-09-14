#include"camera.hpp"
#include"character.hpp"
#include"object.hpp"


camera::camera(SDL_Window *win , SDL_Renderer *rd ,SDL_Surface *sf , double w_x_bi_li):
win(win), rd(rd) ,sf(sf) ,w_x_bi_li(w_x_bi_li)
{
    tx = SDL_CreateTextureFromSurface(rd, sf);
    set_rt_x_j();
    //默认相机中心为大地图中心
    set_rt_x_j_z_x(make_pair(sf->w/2,sf->h/2));
    
}



void camera::set_chater(character_can_talk *chater)
{
    this->chater = chater;
    set_rt_x_j_z_x(chater->ren_wu_b_j_z_x);
}

void camera::set_rt_x_j_z_x(pair<int,int> rt_x_j_z_x)
{
    if(rt_x_j.w / 2 > rt_x_j_z_x.first )
    {
        this->rt_x_j_z_x.first = rt_x_j.w / 2;
    }
    else if(rt_x_j_z_x.first > sf->w -rt_x_j.w / 2)
    {
        this->rt_x_j_z_x.first = sf->w -rt_x_j.w / 2;
    }
    else
    {
        this->rt_x_j_z_x.first = rt_x_j_z_x.first;
    }
    if(rt_x_j.h / 2 >rt_x_j_z_x.second)
    {
        this->rt_x_j_z_x.second = rt_x_j.h / 2;
    }
    else if(rt_x_j_z_x.second > sf->h - rt_x_j.h / 2)
    {
        this->rt_x_j_z_x.second = sf->h - rt_x_j.h / 2;
    }
    else
    {
        this->rt_x_j_z_x.second = rt_x_j_z_x.second;
    }
    rt_x_j.x = this->rt_x_j_z_x.first - rt_x_j.w / 2;
    rt_x_j.y = this->rt_x_j_z_x.second - rt_x_j.h / 2;
    //SDL_Log("%d %d\n",chater->ren_wu_z_x.first,chater->ren_wu_z_x.second);
    //SDL_Log("%d %d\n",rt_x_j_z_x.first,rt_x_j_z_x.second);
    //SDL_Log("%d %d\n",rt_x_j.w,rt_x_j.h);
}

void camera::set_rt_x_j()
{
    SDL_GetWindowSize(win ,&rt_x_j.w,&rt_x_j.h);
    rt_x_j.w *= w_x_bi_li;
    rt_x_j.h *= w_x_bi_li;
    //SDL_Log("%d %d\n",rt_x_j.w,rt_x_j.h);
}

void camera::xiang_ji()
{
    xiang_ji_b_j_x_r();


    now_pick_x_r();
    now_barrier_x_r();
    now_npc_x_r();
    
    
    
    zhe_dang_pick_x_r();
    zhe_dang_barrier_x_r();
    zhe_dang_npc_x_r();
    
    

}

void camera::xiang_ji_b_j_x_r()
{
    SDL_RenderCopy(rd,tx,&rt_x_j,NULL);
}

//////
void camera::get_v_zhe_dang_npc()
{
    if(! v_sheng_bian_npc.empty())
    {
        v_zhe_dang_npc.clear();
        for(auto i = v_sheng_bian_npc.begin() ; i<v_sheng_bian_npc.end();i++)
        {
            if((*i)->rt_b_j.y + (*i)->rt_b_j.h > chater->rt_b_j.y + chater->rt_b_j.h)
            {
                v_zhe_dang_npc.push_back(*i);
            }
        }
    }
}

void camera::get_v_zhe_dang_pick()
{
    if(! v_sheng_bian_pick.empty())
    {
        v_zhe_dang_pick.clear();
        for(auto i = v_sheng_bian_pick.begin() ; i<v_sheng_bian_pick.end();i++)
        {
            if((*i)->rt_b_j.y + (*i)->rt_b_j.h > chater->rt_b_j.y + chater->rt_b_j.h)
            {
                v_zhe_dang_pick.push_back(*i);
            }
        }
    }
}

void camera::get_v_zhe_dang_barrier()
{
    if(! v_now_barrier.empty())
    {
        v_zhe_dang_barrier.clear();
        for(auto i = v_now_barrier.begin() ; i<v_now_barrier.end() ; i++)
        {
            if((*i)->have_tx == true)
            {
                if((*i)->rt_b_j.y + (*i)->rt_b_j.h > chater->rt_b_j.y + chater->rt_b_j.h)
                {
                    v_zhe_dang_barrier.push_back(*i);
                }
            }
        }
    }
}

///////

void camera::get_v_sheng_bian_npc()
{
    if(! v_now_npc.empty())
    {
        v_sheng_bian_npc.clear();
        for(vector<character_can_talk *>::iterator i = v_now_npc.begin() ; i<v_now_npc.end()-1 ; i++)
        {
            if(SDL_HasIntersection(&(*i)->rt_b_j, &(chater->rt_b_j)))
            {
                v_sheng_bian_npc.push_back(*i);
            }
        }
    }  
}

void camera::get_v_sheng_bian_pick()
{
    if(! v_now_pick.empty())
    {
        v_sheng_bian_pick.clear();
        for(auto i = v_now_pick.begin() ; i<v_now_pick.end() ; i++)
        {
            if(SDL_HasIntersection(&(*i)->rt_b_j, &(chater->rt_b_j)))
            {
                v_sheng_bian_pick.push_back(*i);
            }
        }
    }  
}

void camera::get_v_sheng_bian_barrier()
{
    if(! v_now_barrier.empty())
    {
        v_sheng_bian_barrier.clear();
        for(auto i = v_now_barrier.begin() ; i<v_now_barrier.end() ; i++)
        {
            if(SDL_HasIntersection(&(*i)->barrier, &(chater->rt_b_j)))
            {
                v_sheng_bian_barrier.push_back(*i);
            }
        }
    }  
}


////////

void camera::get_now_npc(vector <character_can_talk *> &v_npc)
{
    if(! v_npc.empty())
    {
        v_now_npc.clear();
        for(vector<character_can_talk *>::iterator i = v_npc.begin() ; i<v_npc.end() ; i++)
        {
            if(SDL_HasIntersection(&(*i)->rt_b_j, &rt_x_j))
            {
                (*i)->set_ren_wu_z_x(this);
                (*i)->set_rt_mu_biao(this->w_x_bi_li);
                v_now_npc.push_back(*i);
            }
        }
    }
}

void camera::get_now_barrier(vector <object_barrier *> &v_barrier)
{
    if(!v_barrier.empty())
    {
        v_now_barrier.clear();
        for(auto i = v_barrier.begin() ; i<v_barrier.end() ; i++)
        {
            if((*i)->have_tx == true)
            {
                if(SDL_HasIntersection(&(*i)->rt_b_j, &rt_x_j))
                {
                    (*i)->set_object_z_x(this);
                    (*i)->set_object_mu_biao(this->w_x_bi_li);
                    v_now_barrier.push_back(*i);
                }
            }
            else
            {
                if(SDL_HasIntersection(&(*i)->barrier, &rt_x_j))
                {
                    (*i)->set_object_z_x(this);
                    (*i)->set_object_mu_biao(this->w_x_bi_li);
                    v_now_barrier.push_back(*i);                    
                }
            }
        }
    }
}

void camera::get_now_pick(vector <object_can_pick *> v_pick)
{
    if(!v_pick.empty())
    {
        v_now_pick.clear();
        for(auto i = v_pick.begin() ; i<v_pick.end() ; i++)
        {
            if((*i)->is_pick == false)
            {
                if(SDL_HasIntersection(&(*i)->rt_b_j, &rt_x_j))
                {
                    (*i)->set_object_z_x(this);
                    (*i)->set_object_mu_biao(this->w_x_bi_li);
                    v_now_pick.push_back(*i);
                }
            }
        }
    }    
}


///////


void camera::now_npc_x_r()
{
    if( ! v_now_npc.empty())
    {
        for(vector<character_can_talk *>::iterator i = v_now_npc.begin() ; i<v_now_npc.end() ; i++)
        {
            (*i)->move_x_j();
            if((*i)->is_talk==true)
            {
                (*i)->set_rt_text();
                (*i)->talk_x_r();
            }
        }
    }
}

void camera::now_pick_x_r()
{
    if( ! v_now_pick.empty())
    {
        for(auto i = v_now_pick.begin() ; i<v_now_pick.end() ; i++)
        {
            if((*i)->is_pick == false)
            {
                (*i)->xiang_ji_x_r();
            }
            
        }
    }
}

void camera::now_barrier_x_r()
{
    if( ! v_now_barrier.empty())
    {
        for(auto i = v_now_barrier.begin() ; i<v_now_barrier.end() ; i++)
        {
            if((*i)->have_tx == true)
            {
                (*i)->xiang_ji_x_r();
            }
        }
    }
}

////////
void camera::zhe_dang_npc_x_r()
{
    if(! v_zhe_dang_npc.empty())
    {
        for(auto i = v_zhe_dang_npc.begin(); i<v_zhe_dang_npc.end(); i++)
        {
            (*i)->move_x_j();
            if((*i)->is_talk==true)
            {
                (*i)->set_rt_text();
                (*i)->talk_x_r();
            }
        }
    }
}

void camera::zhe_dang_pick_x_r()
{
    if( ! v_zhe_dang_pick.empty())
    {
        for(auto i = v_zhe_dang_pick.begin() ; i<v_zhe_dang_pick.end() ; i++)
        {
            if((*i)->is_pick == false)
            {
                (*i)->xiang_ji_x_r();
            }
            
        }
    }
}

void camera::zhe_dang_barrier_x_r()
{
    if( ! v_zhe_dang_barrier.empty())
    {
        for(auto i = v_zhe_dang_barrier.begin() ; i<v_zhe_dang_barrier.end() ; i++)
        {
            (*i)->xiang_ji_x_r();
        }
    }    
}


///////


void camera::follow_chater()
{
    if(chater != NULL)
    {
        set_rt_x_j_z_x(chater->ren_wu_b_j_z_x);
    }
}

void camera::chater_talk()
{
    if(!v_sheng_bian_npc.empty() && v_sheng_bian_npc.back()->is_talk == false)
    {
        chater->is_talk = true;
        chater->talk("交谈");
        return;
    }
    if(!v_sheng_bian_pick.empty())
    {
        chater->is_talk = true;
        chater->talk("拾取");
        return;
    }
    if(chater->sf_text != NULL)
    {
        SDL_FreeSurface(chater->sf_text);
        SDL_DestroyTexture(chater->tx_text);
        chater->sf_text = NULL;
        chater->tx_text = NULL;
    }
    chater->is_talk = false;
}

void camera::tx_change()
{
    if( ! v_now_barrier.empty())
    {
        for(auto i = v_now_barrier.begin() ; i<v_now_barrier.end() ; i++)
        {
            if(bao_han(&(*i)->rt_b_j , &chater->rt_b_j))
            {
                SDL_SetTextureAlphaMod((*i)->tx , 70);
            }
            else
            {
                SDL_SetTextureAlphaMod((*i)->tx , 255);
            }
        }
    }
}






bool camera::bao_han(SDL_Rect* outer, SDL_Rect* inner) {
    return (inner->x >= outer->x) &&
           (inner->y >= outer->y) &&
           (inner->x + inner->w <= outer->x + outer->w) &&
           (inner->y + inner->h <= outer->y + outer->h);
}