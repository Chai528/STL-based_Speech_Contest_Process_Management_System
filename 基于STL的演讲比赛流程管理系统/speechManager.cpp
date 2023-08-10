#define _CRT_SECURE_NO_WARNINGS 1
#include "speechManager.h"    // ע�ⲻ���� <> Ҫ�� " " 

SpeechManager::SpeechManager() {
	//��ʼ������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//�����ļ�
	this->loadRecord();
}
//�˵�
void SpeechManager::show_Menu(){
	cout << "**********************************" << endl;
	cout << "*********  ��ӭ���ݽ�����  *******" << endl;
	cout << "*********  1.��ʼ�ݽ�����  *******" << endl;
	cout << "*********  2.�鿴�����¼  *******" << endl;
	cout << "*********  3.��ձ�����¼  *******" << endl;
	cout << "*********  0.�˳���������  *******" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
//��ʼ������
void SpeechManager::initSpeech(){
	//������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//��ʼ����������
	this->m_Index = 1;

	//����¼�������ÿ�
	this->m_Record.clear();
}
//������Ա
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++){
			sp.m_Score[0] = 0;
		}
		//12��ѡ�ֵı��
		this->v1.push_back(i+10001);
		//ѡ�ֱ�ż���Ӧ��ѡ�� ���뵽 map ������
		this->m_Speaker.insert(make_pair(i+10001,sp)); // map������������(key:value )
	}
}
//��ʼ����
void SpeechManager::startSpeech() {
	//��һ�ֱ�����ʼ

	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ�����ʼ
	this->m_Index++;
	//��ǩ
	this->speechDraw();
	//����
	this->speechContest();
	//��ʾ�������
	this->showScore();
	//����������ļ�
	this->saveRecord();
	//���ñ���
	//��ʼ������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//��ȡ�����¼
	this->loadRecord();

	cout<<"��������Ѿ�����" << endl;
	system("pause");
	system("cls");
}
//��ǩ
void SpeechManager::speechDraw() {
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ��" << endl;
	cout << "--------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1) {
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();it++){
			cout << *it << " ";
		}
		cout << endl;
	}
	else{
		//�ڶ��ֱ���
		random_shuffle(v2.begin(),v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
}
void SpeechManager::speechContest() {
	cout << "---------��" << this->m_Index << "�ֱ�����ʽ��ʼ-------" << endl;
	//׼��һ����ʱ�������ڴ��С��ĳɼ�
	multimap<double, int, greater<double>>groupScore;  //key�ǵ÷֣�value�Ǳ�ţ���������
	int num = 0; //ͳ������Ϊһ��

	vector<int>v_Src;//��� ����ѡ�ֵ�����
	if (this->m_Index == 1){
		v_Src = v1;
	}
	else{
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin();it != v_Src.end(); it++)	{
		num++; // ����
		//��ί���
		deque<double>d; //��ķ���
		for (int i = 0; i < 10; i++){
			double score = (rand() % 401 + 600) / 10.f;//  0~400 + 600
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		//������������deque�õ�
		sort(d.begin(),d.end(),greater<double>());
		//ȥ����߷ֺ���ͷ�
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(),d.end(),0.0f); //�ܷ�
		double avg = sum / (double)d.size(); //ƽ����   ������������ͻ������ͣ�����Ҫ��doubleǿ��ת����

		//��ƽ���ַ��� map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//��ӡƽ����
		//cout << "��ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name << " ƽ���֣�" << avg << endl;
		
		//��������� ���뵽��ʱС�� ����
		groupScore.insert(make_pair(avg,*it));  // key�ǵ÷֣�value�Ǳ��
		//ÿ�����˾� ȡ�� ǰ����
		if (num%6 == 0) {
			cout << "��" << num / 6 << "С��ı������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++) {
				cout << "��ţ�"<< it->second <<" ������"<<this->m_Speaker[it->second].m_Name<<" �ɼ���"<< this->m_Speaker[it->second].m_Score[this->m_Index-1]<<endl;
			}
			//ȡ����ǰ����
			int count = 0;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&& count<3; it++,count++){
				if (this->m_Index == 1){
					v2.push_back((*it).second); // multimap�е� ���
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear(); //С���������
		}
 	}
	cout << "---------------��" << this->m_Index << "�ֱ������----------" << endl;
	system("pause");
}
//��ʾ�÷�
void SpeechManager::showScore() {
	cout << "-----��" << this->m_Index << "�ֵĽ���ѡ���������£�----" << endl;
	vector<int>v;
	if (this->m_Index == 1){
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end(); it++){
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name << " �÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	system("pause");
	system("cls");
	this->show_Menu();
}
//�����ļ�
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//��ÿ��ѡ�ֵ�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();it++) {
		ofs << *it << ","  << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ���¼����ɣ�" << endl;

	//�����ļ���Ϊ��״̬
	this->FileIsEmpty= false;
}
//�����ļ�
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv",ios::in);//���ļ�
	if (!ifs.is_open()){ //�ж��ļ��Ƿ�Ϊ��
		this->FileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()){
		this->FileIsEmpty = true;
		cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->FileIsEmpty = false;
	ifs.putback(ch);//��Ϊ֮ǰ����Ƿ�Ϊ�գ���ȡ��һ���������˻������ַ�
	string data;
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		//10002,86.675,10009,81.3,10007,78.55,
		int pos = -1; //���� , ��λ��
		int start = 0;
		vector<string>v;//��Źھ�����
		while (true){
			pos = data.find(",", start);
			if (pos == -1) {
				//û���ҵ������
				break;
			}
			string temp;
			temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v)); //key�ǵڼ��죬value�Ǿ���ı��+�÷�����
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
		cout << "��" << it->first << "�����---�ھ���ţ�" << it->second[0] << " �ھ��÷֣�" << it->second[1] << endl;
	}*/
}
void SpeechManager::showRecord() {
	if (this->FileIsEmpty){
		cout << "�ļ�Ϊ�����ļ�������" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++){
		cout << "��" << i + 1 << "����� "
			<< "�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
			<< "�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
			<< "������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}
//�˳�ϵͳ
void SpeechManager::exitSystem() {
	cout << "���˳�ϵͳ����ӭ�´�ʹ��" << endl;
	exit(0);
	system("pause");
}
//��ղ���
void SpeechManager::clearRecord() {
	cout << "�Ƿ���գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1){
		//ios::trunc �Ĵ򿪷�ʽ�� ����ļ����ڣ���ɾ���ļ������´���
		ofstream ofs("speech.csv",ios::trunc);//���
		ofs.close();

		//��ʼ������
		this->initSpeech();
		//����ѡ��
		this->createSpeaker();
		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {


}
//����vector����Խ�磬�Լ���txt��ʽ��csv�ļ�������
//���е����һ����      ��     ���Ƿ��޸Ļ�ɾ���ˣ����û�лᱨ���ҵ�Խ�������ô�����