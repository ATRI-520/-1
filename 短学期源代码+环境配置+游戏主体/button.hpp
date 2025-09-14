#ifndef _button_HPP_
#define _button_HPP_

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
using namespace std;

//button按钮的文字（w_z）
class button_wen_zi
{
public:
    int xdwz;//字体的相对位置 0中间，1上顶部，-1底部
    SDL_Renderer *rd;
    pair<char *,int> font_zt_dx;//字体文件和大小
    TTF_Font *font = NULL;
    char *text = NULL;//文本
    SDL_Color color;//字体颜色
    SDL_Surface *sf = NULL;
    SDL_Texture *tx = NULL;
    //初始化构造
    button_wen_zi(char *text,pair<char *,int> font_zt_dx,SDL_Renderer *rd,SDL_Color color,int xdwz=0);
    //重载==运算符
    bool operator==(const button_wen_zi &p);
    //窗口缩放时改变字体大小
    void changed_font();
    //析构函数
    ~button_wen_zi();
private:
    //加载字体
    void Init_font();
};

//button按钮的背景图（t_p）
class button_tu_pian
{
public:
    SDL_Surface *sf[2]={NULL,NULL};
    SDL_Texture *tx[2]={NULL,NULL};
    //初始化构造
    button_tu_pian(SDL_Renderer *rd,char *sf1,char *sf2=NULL);
    //析构函数
    ~button_tu_pian();
private:

};

//button按钮类
class button
{
 public:
    bool if_in = false;//判断鼠标是否在按钮区域
    float bi_li;//按钮大小
    pair<float,float> p;//按钮位置
    button_tu_pian *t_p=NULL;//背景图类
    button_wen_zi *w_z=NULL;//文字类
    SDL_Renderer *rd=NULL;
    SDL_Window *win=NULL;
    SDL_Rect rt_w_z;//文字显示区域
    SDL_Rect rt_t_p;//背景图显示区域
    //构造函数
    button(SDL_Window *win,
        SDL_Renderer *rd,
        pair<float,float> p,
        button_tu_pian *t_p,
        button_wen_zi *w_z,
        float bi_li=1
        );
    //重载==运算符
    bool operator==(const button &p);
    //鼠标没在按钮区域时呈现
    void mei_cheng_xian();
    //鼠标在按钮区域时呈现
    void you_cheng_xian();
    //窗口缩放改变按钮大小
    void changed_wz_and_tp_rt();
    //析构函数
    ~button();
private:
    //加载文字区域和背景图区域
    void Init_wz_and_tp_rt();
};

#endif