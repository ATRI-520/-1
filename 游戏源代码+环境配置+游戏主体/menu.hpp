#ifndef _mean_HPP_
#define _mean_HPP_

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include"button.hpp"
#include"map_and_background.hpp"
#include"character.hpp"
#include<vector>
#include<algorithm>
//#include<map>
using namespace std;
//主菜单函数
int mean(SDL_Window * &win , SDL_Renderer * &rd);
//判断鼠标和各个按钮的位置
void button_mouse(int &b_all_f , bool &x_r , button * &b_x_z , vector<button *> &v_b , Mix_Chunk *sound);
//按钮效果显示
void button_x_r(vector<button *> &v_b,map_b_g * j_b_g);

void jian_ru_jian_chu(char *tu_pian , SDL_Renderer *rd , pair<int ,int> z_x , bool is_black);

#endif