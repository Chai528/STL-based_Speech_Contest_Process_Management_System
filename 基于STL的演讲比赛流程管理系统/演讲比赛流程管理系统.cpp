#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <ctime>
#include "speechManager.h"
using namespace std;
int main() {
	//���������
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "ѡ�ֱ�ţ�" << it->first
			<< " ������" << it->second.m_Name
			<< " �ɼ���" << it->second.m_Score[0] << endl;
	}*/
	int choice = 0;//�洢�û�����
	while (true) {
		sm.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice; //�����û�ѡ��
		switch (choice) {
		case 1://��ʼ�ݽ�����
			sm.startSpeech();
			break;
		case 2://�鿴�����¼
			sm.showRecord();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0: // �˳�
			sm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}
	}
	system("pause");
	return 0;
}