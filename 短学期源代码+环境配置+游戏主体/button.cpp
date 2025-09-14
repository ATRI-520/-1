#include"button.hpp"
//透明度
int tou_ming_du=128;
//记录窗口的缩放比例
extern float win_changed;
//SDL_Rect区域相等比较
bool operator==(SDL_Rect rt1,SDL_Rect rt2)
{
    if (rt1.x == rt2.x&&
        rt1.y == rt2.y&&
        rt1.w == rt2.w&&
        rt1.h == rt2.h)
        return true;
    else
        return false;
}

bool operator==(SDL_Color color1,SDL_Color color2)
{
    if (color1.a == color2.a&&
        color1.r == color2.r&&
        color1.b == color2.b&&
        color1.g == color2.g)
        return true;
    else
        return false;
}

button::button(SDL_Window *win,
                SDL_Renderer *rd,
                pair<float,float> p,
                button_tu_pian *t_p,
                button_wen_zi *w_z,
                float bi_li
                )
{
    this->p=p;
    this -> bi_li = bi_li;
    this -> win = win;
    this -> rd = rd;
    this-> t_p = t_p;
    this-> w_z = w_z;
    Init_wz_and_tp_rt();
    mei_cheng_xian();
    SDL_RenderPresent(rd);
}

bool button::operator==(const button &p)
{
    if ( this->bi_li == p.bi_li
        && this->p == p.p
        && *(this->w_z) == *(p.w_z)
        && this->rt_t_p == p.rt_t_p
        && this->rt_w_z == p.rt_w_z)
        return true;
    else
        return false;

}
void button::Init_wz_and_tp_rt()
{
    //获取窗口的宽和高
    SDL_GetWindowSize(win,&(rt_t_p.x),&(rt_t_p.y));
    rt_t_p.x *= p.first;//确定按钮的x位置
    rt_t_p.y *= p.second;//确定按钮的y位置
    //如果传入背景图片不为空
    if (t_p != NULL)
    {
        //确定按钮大小
        rt_t_p.w = ( t_p -> sf[0] ) -> w * bi_li * win_changed;
        rt_t_p.h = ( t_p -> sf[0] ) -> h * bi_li * win_changed;
        //如果传入文字集不为空
        if (w_z != NULL)
        {
            //确定文字显示区域
            rt_w_z.w = w_z->sf->w;
            rt_w_z.h = w_z->sf->h;
            //以下的if语句为根据xdwz确定文字在按钮什么地方显示
            rt_w_z.x = rt_t_p.x + ( rt_t_p.w - rt_w_z.w ) / 2;
            if (w_z -> xdwz == 0)
            {
                rt_w_z.y = rt_t_p.y + ( rt_t_p.h - rt_w_z.h ) / 2;
            }
            else if (w_z -> xdwz == 1)
            {
                rt_w_z.y = rt_t_p.y;
            }
            else if (w_z -> xdwz == -1)
            {
                rt_w_z.y = rt_t_p.y + ( rt_t_p.h - rt_w_z.h);
            }
        }
    }
    //如果背景图片为空，但文字集不为空
    else if(w_z!=NULL)
    {
        //文字将显示在整个按钮区域
        rt_t_p.w = ( ( w_z -> sf ) -> w + 6 );
        rt_t_p.h = ( ( w_z -> sf ) -> h + 6 );
        //文字区域大小比按钮区域稍微小3个像素，实现不贴边
        rt_w_z.w = w_z->sf->w;
        rt_w_z.h = w_z->sf->h;
        rt_w_z.x = rt_t_p.x + 3;
        rt_w_z.y = rt_t_p.y + 3;
    }
}

void button::changed_wz_and_tp_rt()
{
    //如果文字集不为空则调整字体大小
    if(w_z != NULL)
    {
        w_z->changed_font();
    }
    //改变按钮大小
    Init_wz_and_tp_rt();
}

void button::mei_cheng_xian()
{
    //if_in=false;
    if (t_p != NULL)
    {
        //如果背景图2为空，背景图1则改变透明度显示，
        //背景图2不为空，背景图1则不改变透明度显示，
        if (t_p->tx[1] == NULL)
        {
            SDL_SetTextureAlphaMod(t_p->tx[0] , tou_ming_du);
        }
        SDL_RenderCopy(rd , t_p->tx[0] , NULL , &rt_t_p);

        if (w_z != NULL)
        {
            //将文字的透明度改为和背景1一样，改变规则也是根据背景2为不为空
            if (t_p->tx[1] == NULL)
            {
                SDL_SetTextureAlphaMod(w_z->tx, tou_ming_du);
            }
            SDL_RenderCopy(rd , w_z->tx , NULL , &rt_w_z);
        }
    }
    //如果背景图片为空，但文字集不为空
    else if (w_z != NULL)
    {
        //如果只显示文字也会改变透明度
        SDL_SetTextureAlphaMod(w_z->tx , tou_ming_du);
        SDL_RenderCopy(rd,w_z->tx , NULL , &rt_w_z);
    }
}

void button::you_cheng_xian()
{
    //if_in=true;
    if (t_p != NULL)
    {
        //如果背景2为空，则显示不透明的背景1和文字
        if (t_p->tx[1] == NULL)
        {
            //设置透明度
            SDL_SetTextureAlphaMod(t_p->tx[0] , 255);
            SDL_RenderCopy(rd , t_p->tx[0] , NULL , &rt_t_p);
            if (w_z != NULL)
            {
                SDL_SetTextureAlphaMod(w_z->tx , 255);
                SDL_RenderCopy(rd , w_z->tx , NULL , &rt_w_z);
            }
        }
        //如果背景2不为空，则显示背景2和不透明文字
        else
        {
            SDL_RenderCopy(rd , t_p->tx[1] , NULL , &rt_t_p);
            if (w_z != NULL)
            {
            SDL_SetTextureAlphaMod(w_z->tx , 255);
            SDL_RenderCopy(rd , w_z->tx , NULL , &rt_w_z);
            }

        }
    }
    //只有文字集时
    else if (w_z != NULL)
    {
        SDL_SetTextureAlphaMod(w_z->tx , 255);
        SDL_RenderCopy(rd , w_z->tx , NULL , &rt_w_z);
    }
}

button::~button()
{
    delete t_p;
    delete w_z;
}
//////
//////
//////
button_wen_zi::button_wen_zi(char *text,
                            pair<char *,int> font_zt_dx,
                            SDL_Renderer *rd,
                            SDL_Color color,
                            int xdwz
                            )
{
    this->rd=rd;
    this->font_zt_dx=font_zt_dx;
    this->text=text;
    this->xdwz=xdwz;
    this->color=color;
    Init_font();

}

bool button_wen_zi::operator==(const button_wen_zi &p)
{
    char *text = NULL;//文本
    SDL_Color color;//字体颜色
    if (this->xdwz == p.xdwz&&
        this->font_zt_dx == p.font_zt_dx&&
        *(this->text) == *(p.text)&&
        this->color == p.color
        )
        return true;
    else
        return false;
}

void button_wen_zi::Init_font()
{
    //在因为窗口缩放时改变字体大小要先释放原来的字体指针
    if(font != NULL)
    {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont(font_zt_dx.first , font_zt_dx.second*win_changed);
    sf=TTF_RenderUTF8_Blended(this->font,text,color);
    tx=SDL_CreateTextureFromSurface(rd,sf);
}

void button_wen_zi::changed_font()
{
    Init_font();
}

button_wen_zi::~button_wen_zi()
{
    TTF_CloseFont(font);
    delete text;
    SDL_FreeSurface(sf);
    SDL_DestroyTexture(tx);

}
//////
//////
//////
button_tu_pian::button_tu_pian(SDL_Renderer *rd,
                                char *sf1,
                                char *sf2
                                )
{
    //加载背景图1和2
    if (sf1 != NULL)
    {
        sf[0] = IMG_Load(sf1);
        tx[0] = SDL_CreateTextureFromSurface(rd,sf[0]);
    }
    if(sf2 != NULL)
    {
        sf[1] = IMG_Load(sf2);
        tx[1] = SDL_CreateTextureFromSurface(rd,sf[1]);
    }
}

button_tu_pian::~button_tu_pian()
{
    SDL_free(sf[0]);
    SDL_free(sf[1]);
    SDL_DestroyTexture(tx[0]);
    SDL_DestroyTexture(tx[1]);
}
