#include"object.hpp"
#include"camera.hpp"

Uint8 temp;
object_base::object_base(){}
object_base::object_base(char *tu_pian 
                , SDL_Renderer *&rd
                , pair<int ,int> object_b_j_z_x 
                , pair<int ,int> w_h )
{
    this->rd = rd;
    this->object_b_j_z_x = object_b_j_z_x;
    set_rt_b_j(w_h);
    sf = IMG_Load(tu_pian);
    tx = SDL_CreateTextureFromSurface(rd,sf);
    SDL_SetTextureBlendMode(tx, SDL_BLENDMODE_BLEND);
}


void object_base::set_rt_b_j(pair<int ,int> w_h)
{
    rt_b_j.w = w_h.first;
    rt_b_j.h = w_h.second;
    rt_b_j.x = object_b_j_z_x.first - rt_b_j.w/2;
    rt_b_j.y = object_b_j_z_x.second - rt_b_j.h/2;
}


void object_base::set_object_z_x(camera *cam)
{
    object_z_x.first = (object_b_j_z_x.first - cam->rt_x_j.x) * (1.0 / cam->w_x_bi_li);
    object_z_x.second = (object_b_j_z_x.second - cam->rt_x_j.y) *(1.0 / cam->w_x_bi_li);
}


void object_base::set_object_mu_biao(double w_x_bi_li)
{
    object_mu_biao.w = rt_b_j.w *(1.0 / w_x_bi_li);
    object_mu_biao.h = rt_b_j.h *(1.0 / w_x_bi_li);
    object_mu_biao.x = object_z_x.first - object_mu_biao.w/2;
    object_mu_biao.y = object_z_x.second - object_mu_biao.h/2;
}

void object_base::xiang_ji_x_r()
{
    //SDL_SetTextureBlendMode(tx, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(rd,tx,NULL,&object_mu_biao);
}

//////
//////

object_can_pick::object_can_pick(char *name
                , char *tu_pian 
                , SDL_Renderer *rd
                , pair<int ,int> object_b_j_z_x 
                , pair<int ,int> w_h):
object_base(tu_pian,rd,object_b_j_z_x,w_h),
name(name)
{
    //this->name_hua = "afrsetgww";//"已获取"+ '\"' + *name + '\"';
    //SDL_Log(name_hua.data());
}


//////
//////

object_barrier::object_barrier(SDL_Rect barrier,int)
{
    have_tx = false;
    this->barrier = barrier;
    set_barrier_b_j_z_x();
}


object_barrier::object_barrier(SDL_Rect barrier
                            , char *tu_pian 
                            , SDL_Renderer *rd
                            , pair<int ,int> object_b_j_z_x
                            , pair<int ,int> w_h ):
object_base(tu_pian,rd,object_b_j_z_x,w_h)
{
    have_tx = true;
    this->barrier = barrier;
    set_barrier_b_j_z_x();
}


void object_barrier::change_tx(int tou_ming_du)
{
    SDL_SetTextureAlphaMod(tx , tou_ming_du);
}


void object_barrier::set_barrier_b_j_z_x()
{
    barrier_b_j_z_x.first = barrier.x + barrier.w/2;
    barrier_b_j_z_x.second = barrier.y + barrier.h/2;
}

