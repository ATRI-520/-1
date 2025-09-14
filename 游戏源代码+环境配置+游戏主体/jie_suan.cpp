#include"jie_suan.hpp"

int jie_suan(SDL_Window * &win , SDL_Renderer * &rd)
{
    Mix_HaltMusic();
    jian_ru_jian_chu("picture/game_over.png",rd,make_pair(960/2 , 540/2),false);
    //背景类创建和渲染                        
    map_b_g *j_b_g = new map_b_g(win,rd,"picture/game_over.png");
    
    j_b_g->jing_tai();
    SDL_RenderPresent(rd);
    SDL_Delay(7000);
    //捕获事件
    SDL_Event event;

    
    //主循环
    while(1)
    {
    
        //事件处理
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            //用户点×
            case SDL_QUIT:
                return 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYDOWN:
                return 1;
                break;
            }

        }
    }
}
