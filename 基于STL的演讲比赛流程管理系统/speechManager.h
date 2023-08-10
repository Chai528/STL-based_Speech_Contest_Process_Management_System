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
	SpeechManager(); // ��ʵ��
	 
	//�˵�����
	void show_Menu(); 

	//�˳�����
	void exitSystem();  

	//��ʼ������
	void initSpeech();
	
	//����ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();
	
	//��ʾ�÷�
	void showScore();

	//�����ļ�
	void saveRecord();

	//�����ļ���Ϣ
	void loadRecord();

	//��ʾ����÷�
	void showRecord();
	
	//��ղ���
	void clearRecord();
	
	bool FileIsEmpty;//�ļ��Ƿ�Ϊ��

	map<int, vector<string>>m_Record;//��������¼��������key�ǵڼ��죬value��ѡ�ֵı�ź͵÷� 

	//��Ա����
	vector<int>v1; //��һ�� 12 ���˵ı�ź�����

	vector<int>v2; //�ڶ��� 6 ����

	vector<int>vVictory; //����ʤ������

	map<int,Speaker>m_Speaker; //��ű�ţ��Լ���Ӧ�ľ���ѡ�� ������

	int m_Index;// ��¼����������

	~SpeechManager(); // ��������
};