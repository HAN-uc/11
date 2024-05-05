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

//��ر���
double start_t = 100; //��ʼ�¶�
int num_iter = 1000; //����Ʒ�������
double end_t = 0;  //��ֹ�¶�
double k = 0.9;  //�¶��½�����
const int length = 9; // ���볤��

//�ȶ���һЩ������������������
vector<Solution>every_bst_solu;
vector<double>curr_tempterature;

//��غ���
Solution initialize(int lower, int upper);  // ���ɳ�ʼ��
Solution change(Solution solu_temp); //�Ŷ�����
Solution change_2(Solution solu_temp);
void cal_fitness(Solution &solu_temp); //����Ŀ�꺯��ֵ
void sa(double ini_t, double k, int l, double end_t, double kv); //ģ���˻��㷨

#endif __ SA_H__
