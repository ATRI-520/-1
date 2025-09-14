#include"Flower.hpp"
//记录窗口的缩放比例
float win_changed = 1.0;
//时间之眼
float shi_jian = 1.0;
//主窗口函数
int WinMain()
{
    //初始化SDL库和其子库
    int Init = Init_all();
    if(Init == -1)
    {
        SDL_Log("有子系统初始化失败，程序退出");
        return -1;
    }
    //主窗口
    SDL_Window *win = SDL_CreateWindow("Flower",
                                        //居中
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        //宽800，高450
                                        960*win_changed,540*win_changed,
                                        //800*win_changed,450*win_changed,
                                        //捕获窗口外的鼠标输入
                                        SDL_WINDOW_MOUSE_CAPTURE
                                        //支持DPI
                                        |SDL_WINDOW_ALLOW_HIGHDPI
                                        //锁鼠标
                                        //|SDL_WINDOW_INPUT_GRABBED
                                        //显示在所有窗口之上
                                        //|SDL_WINDOW_ALWAYS_ON_TOP
                                        );

    //这四个函数提高渲染质量
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "opengl");
                                        

    //创建渲染器
    SDL_Renderer *rd=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(rd, SDL_BLENDMODE_BLEND);

    character_can_talk *npc = NULL;

    //主菜单
    xun_huan:
    mean(win , rd);
    //角色

    //待机动画
    char *dai_ji_t_p[4] ={"picture/dai_ji_w.png","picture/dai_ji_d.png","picture/dai_ji_s.png","picture/dai_ji_a.png"};

    //移动动画
    char *move_t_p[4] = {"picture/xing_zou_w.png","picture/xing_zou_d.png","picture/xing_zou_s.png","picture/xing_zou_a.png"};
    
    npc = new character_can_talk(dai_ji_t_p , rd , move_t_p ,make_pair(1000,799) , make_pair(100,146));
    npc->tag=-1;
    //待机帧率
    (npc->v_t).push_back(make_pair(SDL_GetTicks() , 1000/7));
   // SDL_Log("%d",npc->v_t[0].first);
    //移动帧率
    npc->v_t.push_back(make_pair(SDL_GetTicks() , 1000/8));

    npc->walk_speed = 10;



    // if(xuan_ze == 0)
    // {
    //     //fi();
    // }
    // switch (zhang_jie)
    // {
    //     case 0:
    //         break;
    
    // }

    zhang_jie_1(win , rd , npc);

    int xun_huan = jie_suan(win , rd);
    if(xun_huan == 1)
    {
        delete npc;
        npc = NULL;
        goto xun_huan;
    }

    
    SDL_DestroyWindow(win);
    //释放所有资源
    Quit_all();
    return 0;
}
//注意：分文件写是为了避免类的头文件相互包含！！！
//第一个困难，无法实现窗口等比例缩放。
