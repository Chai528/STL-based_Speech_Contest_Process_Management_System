#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <ctime>
#include "speechManager.h"
using namespace std;
int main() {
	//随机数种子
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "选手编号：" << it->first
			<< " 姓名：" << it->second.m_Name
			<< " 成绩：" << it->second.m_Score[0] << endl;
	}*/
	int choice = 0;//存储用户输入
	while (true) {
		sm.show_Menu();
		cout << "请输入你的选择？" << endl;
		cin >> choice; //接收用户选项
		switch (choice) {
		case 1://开始演讲比赛
			sm.startSpeech();
			break;
		case 2://查看往届记录
			sm.showRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0: // 退出
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	system("pause");
	return 0;
}