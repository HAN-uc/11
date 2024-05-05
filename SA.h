#pragma once
#ifndef __SA_H__
#define __SA_H__
#include <iostream>
#include <vector>
#include <iomanip>
#include<bitset>
#include <algorithm>
using namespace std;
struct Solution {
	double x1;
	double x2;
	double value = 0.0;
};

//相关变量
double start_t = 100; //初始温度
int num_iter = 1000; //马尔科夫链长度
double end_t = 0;  //终止温度
double k = 0.9;  //温度下降速率
const int length = 9; // 编码长度

//先定义一些容器存放用于输出的量
vector<Solution>every_bst_solu;
vector<double>curr_tempterature;

//相关函数
Solution initialize(int lower, int upper);  // 生成初始解
Solution change(Solution solu_temp); //扰动算子
Solution change_2(Solution solu_temp);
void cal_fitness(Solution &solu_temp); //计算目标函数值
void sa(double ini_t, double k, int l, double end_t, double kv); //模拟退火算法

#endif __ SA_H__
