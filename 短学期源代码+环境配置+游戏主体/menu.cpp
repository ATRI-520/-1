#include"menu.hpp"
extern float win_changed;
int mean(SDL_Window * &win , SDL_Renderer * &rd)
{
    jian_ru_jian_chu("picture/sheng_ya.png",rd,make_pair(960/2 , 540/2) , true);
    jian_ru_jian_chu("picture/logo.png",rd,make_pair(960/2 , 540/2) , true);
    jian_ru_jian_chu("picture/bei_jing.png",rd,make_pair(960/2 , 540/2) , false);
    Mix_Chunk* sound[2];
    sound[0] = Mix_LoadWAV("music/se900.ogg");
    sound[1] = Mix_LoadWAV("music/se901.ogg");
    
    //背景类创建和渲染                        
    map_b_g *j_b_g = new map_b_g(win,rd,"picture/bei_jing.png");
    j_b_g->bgm = Mix_LoadMUS("music/menu.mp3");
    j_b_g->jing_tai();
    SDL_RenderPresent(rd);

    //判断按钮是否渲染                        
    bool x_r=false;
    //所有按钮都装在这个容器里面                        
    vector<button *> v_b;
    v_b.push_back(new button(win,rd,
        pair<float, float>(0.078125,0.26639),
        new button_tu_pian(rd , "picture/button_1.png"),
        NULL));
    v_b.push_back(new button(win,rd,
        pair<float, float>(0.078125,0.45139),
        new button_tu_pian(rd , "picture/button_2.png"),
        NULL));
    v_b.push_back(new button(win,rd,
        pair<float, float>(0.078125,0.633681),
        new button_tu_pian(rd , "picture/button_3.png"),
        NULL));
    v_b.push_back(new button(win,rd,
        pair<float, float>(0.078125,0.815973),
        new button_tu_pian(rd , "picture/button_4.png"),
        NULL));
    SDL_RenderPresent(rd);


    //判断按钮的序号
    int n=0;

    //鼠标不在任何按钮里面
    int b_all_f=0;

    //鼠标上一个位置的按钮
    button *b_x_z=NULL;

    //捕获事件
    SDL_Event event;
    
    //主循环
    while(1)
    {
        button_mouse(b_all_f,x_r,b_x_z,v_b , sound[1]);

        if(x_r == true )
        {
            x_r = false;
            button_x_r(v_b , j_b_g);
            //npc->dai_ji_x_r();
            SDL_RenderPresent(rd);
        }

        //事件处理
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            //用户点×
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(b_x_z != NULL)
                {
                    Mix_PlayChannel(-1, sound[0], 0);
                    n = distance(v_b.begin(),find(v_b.begin(),v_b.end(),b_x_z));
                    switch (n)
                    {
                    case 0:
                        Mix_HaltMusic();
                        return 0;
                        break;
                    case 1:
                        //return 1;
                        break;
                    case 2:
                        //fi();
                        break;
                    case 3:
                        exit(0);
                        break;
                    }
                }
                break;
            }

        }
    }
}






void button_mouse(int &b_all_f , bool &x_r , button * &b_x_z , vector<button *> &v_b , Mix_Chunk *sound)
{
    
    SDL_Point pt={0,0};//获取鼠标位置
   
    b_all_f=0; //累加器，判断鼠标没有在任何一个按钮里

    SDL_GetMouseState(&(pt.x),&(pt.y));
    //循环判断鼠标是否在任意一个按钮里
    for(vector<button *>::iterator i = v_b.begin() ; i != v_b.end() ; i++)
    {
        if(SDL_PointInRect(&pt,&((*i)->rt_t_p)))
        {
            //如果在，且和鼠标上一个按钮不一样
            if(b_x_z != *i)
            {
                //播放音乐
                if (!Mix_Playing(1))
                {
                    Mix_Pause(1);
                    Mix_PlayChannel(1, sound, 0);
                } 

                x_r = true;//渲染启动
                if(b_x_z != NULL)
                {
                    b_x_z->if_in =false;
                }
                b_x_z = *i;//改变当前鼠标所在按钮
                b_x_z->if_in = true;
            }
        }
        //如果鼠标不在按钮里面，累加器加1
        else
        {
            b_all_f++;
        }
    }
    //如果累加器的数值是所有按钮的总和 且鼠标上一个在按钮里面
    if(b_x_z != NULL && b_all_f == v_b.size())
    {
        b_x_z->if_in=false;
        b_x_z = NULL;
        x_r = true;
    }
}


void button_x_r(vector<button *> &v_b,map_b_g * j_b_g)
{
    //绘制静态背景
    j_b_g->jing_tai();
    //根据按钮的if_in显示按钮
    for(vector<button *>::iterator i = v_b.begin() ; i != v_b.end() ; i++)
    {
        if((*i)->if_in)
        {
            (*i)->you_cheng_xian();
        }
        else
        {
            (*i)->mei_cheng_xian();
        }
    }
}


//渐入渐出动画
void jian_ru_jian_chu(char *tu_pian, SDL_Renderer *rd , pair<int ,int> z_x , bool is_black)
{
    SDL_SetRenderDrawColor(rd, 0, 0, 0, 255); 
    int tou_ming_du = 1;
    int zen_jia = 3;
    SDL_Surface *sf = IMG_Load(tu_pian);
    SDL_Texture *tx = SDL_CreateTextureFromSurface(rd,sf);
    SDL_SetTextureBlendMode(tx, SDL_BLENDMODE_BLEND);
    SDL_Rect rt = {z_x.first - sf->w /2 , z_x.second - sf->h /2,sf->w,sf->h};
    pair<int , int> z_l = make_pair(SDL_GetTicks() , 1);
    while(tou_ming_du > 0)
    {
        if(SDL_GetTicks() - z_l.first >= z_l.second)
        {
            z_l.first = SDL_GetTicks();
            SDL_SetTextureAlphaMod(tx , tou_ming_du);
            SDL_RenderClear(rd);
            SDL_RenderCopy(rd,tx,NULL,&rt);
            SDL_RenderPresent(rd);
            tou_ming_du = tou_ming_du + zen_jia;
            if(tou_ming_du>=255)
            {
                if(is_black == false)
                {
                    return;
                }
                SDL_Delay(1000);
                tou_ming_du = 255;
                zen_jia = -zen_jia;
            }
            
        }
    }
    SDL_FreeSurface(sf);
    SDL_DestroyTexture(tx);

}