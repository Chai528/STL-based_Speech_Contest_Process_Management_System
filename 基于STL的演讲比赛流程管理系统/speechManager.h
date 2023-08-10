#pragma once
#include <iostream>
#include <vector>
#include "speaker.h"
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <deque>
#include <fstream>
using namespace std;
class SpeechManager {
public:
	SpeechManager(); // 空实现
	 
	//菜单功能
	void show_Menu(); 

	//退出功能
	void exitSystem();  

	//初始化属性
	void initSpeech();
	
	//创建选手
	void createSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();
	
	//显示得分
	void showScore();

	//保存文件
	void saveRecord();

	//加载文件信息
	void loadRecord();

	//显示往届得分
	void showRecord();
	
	//清空操作
	void clearRecord();
	
	bool FileIsEmpty;//文件是否为空

	map<int, vector<string>>m_Record;//存放往届记录的容器，key是第几届，value是选手的编号和得分 

	//成员属性
	vector<int>v1; //第一轮 12 个人的编号和容器

	vector<int>v2; //第二轮 6 个人

	vector<int>vVictory; //最后的胜利三人

	map<int,Speaker>m_Speaker; //存放编号，以及对应的具体选手 的容器

	int m_Index;// 记录比赛论轮数

	~SpeechManager(); // 析构函数
};