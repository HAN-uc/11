// SA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//该程序为“我家公子Q”（公众号为：运筹帷幄Q）完成，未抄袭他人。完成日期：8月2日

#include <iostream>
#include "SA.h"
#include <bitset>
#include <random>
#include <cmath>
#include <vector>
#include <ctime>
#include <math.h>
using namespace std;

Solution initialize(int lower, int upper)
{
	double temp_solu[2];
	//srand(30);  // 设置随机种子
	for (int i = 0; i < 2; i++)
	{
		temp_solu[i] = static_cast<__int64>(rand() % (upper - lower + 1)) + lower;
	}
	Solution start_solu;
	start_solu.x1 = temp_solu[0];
	start_solu.x2 = temp_solu[1];
	return start_solu;
}

//扰动算子1，以二进制进行编码，随机选三位进行取反
Solution change(Solution solu_temp)
{
	// 编码
	bitset<length>x1Code(solu_temp.x1 * 10);
	bitset<length>x2Code(solu_temp.x2 * 10);
	//扰动
	int loci_1[3];  // 存放需要取反的两个位置
	int loci_2[3]; // 存放需要取反的两个位置
	for (int i = 0; i < 3; i++)
	{
		loci_1[i] = (rand() % (8)) + 1;
		loci_2[i] = (rand() % (8)) + 1;
	}
	for (int j = 0; j < 3; j++)
	{
		x1Code.flip(loci_1[j]);
		x2Code.flip(loci_2[j]);
	}
	//解码
	Solution new_solution;
	new_solution.x1 = x1Code.to_ulong() / 10;
	new_solution.x2 = x2Code.to_ulong() / 10;
	return new_solution;
}

//扰动算子2，以浮点数进行编码，随机变大或变小一个数
Solution change_2(Solution solu_temp)
{
	double judgment = 0.5;
	const int N = 999; // 精确到小数点后面三位
	double a = rand() % (N + 1) / (float)(N + 1);
	double b = rand() % (N + 1) / (float)(N + 1);
	double change_k[2];  // 存放两个放大或者缩小的系数

	change_k[0] = (rand() % (15) + 100) / (float)(100);  // 生成1-1.3之间的随机小数，精确到小数点后两位
	change_k[1] = (rand() % (15) + 85) / (float)(100);
	
	Solution new_solution;
	if (a >= judgment)
	{
		new_solution.x1 = solu_temp.x1 * change_k[0];
	}
	else
	{
		new_solution.x1 = solu_temp.x1 * change_k[1];
	}

	if (b >= judgment)
	{
		new_solution.x2 = solu_temp.x2 * change_k[0];
	}
	else
	{
		new_solution.x2 = solu_temp.x2 * change_k[1];
	}
	return new_solution;
}

//计算目标函数----一个非常好看的函数！！！！
void cal_fitness(Solution& solu_temp)
{
	double x = solu_temp.x1, y = solu_temp.x2;
	double fitness;
	//fitness = 3 * pow((1 - x), 2) * exp(-pow(x, 2) - pow((y + 1), 2)) - 10 * ((1.0 / 5.0) * x - pow(x, 3) - pow(y, 5)) * exp(-pow(x, 2) - pow(y, 2)) - (1.0 / 3.0) * exp(-pow((x + 1), 2) - pow(y, 2));
	fitness = (0.5 + double(pow(sin(pow((x * x + y * y), 0.5)), 2) - 0.5) / pow((1.0 + 0.001 * (x * x + y * y)), 2)) * 100;  // 好看的函数
	solu_temp.value = fitness;
}

//模拟退火算法（两个算子里面选择一个就可以啦，不过第一个算子力度有点轻，可以把初温稍微加大一点）
void sa(double ini_t, double k, int l, double end_t, double kv)  // 依次是初始温度、温度下降系数、终止温度、下降系数减小速率
{
	double x_lower =-1000;
	double x_upper = 1000;
	Solution solution = initialize(x_lower, x_upper);  // 初始化解
	cout << "调试1：输出初始化后的解" << endl;
	cout << solution.x1 << "       " << solution.x2 << endl;
	cal_fitness(solution);
	Solution curr_best_solu = solution;
	double curr_t = ini_t;
	double tk = k;
	while (curr_t > end_t)
	 {
		for (int i = 0; i < l; i++)
		{
			//Solution new_solu = change_2(curr_best_solu);
			Solution new_solu = change_2(curr_best_solu);
			if ((new_solu.x1 > -1000 && new_solu.x1 < 1000) && (new_solu.x2 > -1000 && new_solu.x2 < 1000)) // 定义域
			{
				cal_fitness(new_solu);
				if (new_solu.value < curr_best_solu.value)
				{
					curr_best_solu = new_solu;
				}
				else
				{
					//计算接受当前解的概率
					double proba = exp(-double(new_solu.value - curr_best_solu.value) / (tk * curr_t));
					//随机产生一个0-1的小数
					const int N = 999; // 精确到小数点后面三位
					double random_num = rand() % (N + 1) / (float)(N + 1);
					if (random_num <= proba)
					{
						curr_best_solu = new_solu;
					}
				}
			}
		}
		every_bst_solu.push_back(curr_best_solu);
		curr_tempterature.push_back(curr_t);
		curr_t = tk * curr_t;
		tk = kv * tk;
	 }
}

int main()
{
	every_bst_solu.clear();
	curr_tempterature.clear();
	double initial_tem = 100;
	double tem_k = 0.95;
	int iteration = 100;
	double kv = 0.995;
	double end_tem =0.5;
	time_t start_time = clock();
	sa(initial_tem, tem_k, iteration, end_tem, kv);
	time_t end_time = clock();
	//结果输出
	cout.setf(ios::left);
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3);
	cout << setw(15) << "X1" << setw(15) << "X2" << setw(15) << "Value"<< setw(15)<<"Temperature" << endl;
	for (int i = 0; i < every_bst_solu.size(); i++)
	{
		cout  << setw(15) << every_bst_solu[i].x1 << setw(15) << every_bst_solu[i].x2 << setw(15) << every_bst_solu[i].value << setw(15) << curr_tempterature[i] <<  endl;
	}
	cout << "算法总用时为：" << double(end_time - start_time) / CLOCKS_PER_SEC << "s.   " << endl;
}

