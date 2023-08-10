#define _CRT_SECURE_NO_WARNINGS 1
#include "speechManager.h"    // 注意不能用 <> 要用 " " 

SpeechManager::SpeechManager() {
	//初始化属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//加载文件
	this->loadRecord();
}
//菜单
void SpeechManager::show_Menu(){
	cout << "**********************************" << endl;
	cout << "*********  欢迎参演讲比赛  *******" << endl;
	cout << "*********  1.开始演讲比赛  *******" << endl;
	cout << "*********  2.查看往届记录  *******" << endl;
	cout << "*********  3.清空比赛记录  *******" << endl;
	cout << "*********  0.退出比赛程序  *******" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
//初始化容器
void SpeechManager::initSpeech(){
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;

	//将记录的容器置空
	this->m_Record.clear();
}
//生成人员
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++){
			sp.m_Score[0] = 0;
		}
		//12名选手的编号
		this->v1.push_back(i+10001);
		//选手编号及对应的选手 放入到 map 容器中
		this->m_Speaker.insert(make_pair(i+10001,sp)); // map容器插入数据(key:value )
	}
}
//开始比赛
void SpeechManager::startSpeech() {
	//第一轮比赛开始

	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();
	//第二轮比赛开始
	this->m_Index++;
	//抽签
	this->speechDraw();
	//比赛
	this->speechContest();
	//显示晋级结果
	this->showScore();
	//保存分数到文件
	this->saveRecord();
	//重置比赛
	//初始化属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//获取往届记录
	this->loadRecord();

	cout<<"本届比赛已经结束" << endl;
	system("pause");
	system("cls");
}
//抽签
void SpeechManager::speechDraw() {
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签：" << endl;
	cout << "--------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();it++){
			cout << *it << " ";
		}
		cout << endl;
	}
	else{
		//第二轮比赛
		random_shuffle(v2.begin(),v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
}
void SpeechManager::speechContest() {
	cout << "---------第" << this->m_Index << "轮比赛正式开始-------" << endl;
	//准备一个临时容器用于存放小组的成绩
	multimap<double, int, greater<double>>groupScore;  //key是得分，value是编号，降序排序
	int num = 0; //统计六人为一组

	vector<int>v_Src;//存放 比赛选手的容器
	if (this->m_Index == 1){
		v_Src = v1;
	}
	else{
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin();it != v_Src.end(); it++)	{
		num++; // 人数
		//评委打分
		deque<double>d; //存的分数
		for (int i = 0; i < 10; i++){
			double score = (rand() % 401 + 600) / 10.f;//  0~400 + 600
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		//分数降序排序deque得到
		sort(d.begin(),d.end(),greater<double>());
		//去除最高分和最低分
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(),d.end(),0.0f); //总分
		double avg = sum / (double)d.size(); //平均分   （浮点除以整型还是整型，所以要加double强制转换）

		//将平均分放入 map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//打印平均分
		//cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 平均分：" << avg << endl;
		
		//将打分数据 放入到临时小组 当中
		groupScore.insert(make_pair(avg,*it));  // key是得分，value是编号
		//每六个人就 取出 前三人
		if (num%6 == 0) {
			cout << "第" << num / 6 << "小组的比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++) {
				cout << "编号："<< it->second <<" 姓名："<<this->m_Speaker[it->second].m_Name<<" 成绩："<< this->m_Speaker[it->second].m_Score[this->m_Index-1]<<endl;
			}
			//取走请前三名
			int count = 0;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&& count<3; it++,count++){
				if (this->m_Index == 1){
					v2.push_back((*it).second); // multimap中的 编号
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear(); //小组容器清空
		}
 	}
	cout << "---------------第" << this->m_Index << "轮比赛完毕----------" << endl;
	system("pause");
}
//显示得分
void SpeechManager::showScore() {
	cout << "-----第" << this->m_Index << "轮的晋级选手名单如下：----" << endl;
	vector<int>v;
	if (this->m_Index == 1){
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end(); it++){
		cout << "选手编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	system("pause");
	system("cls");
	this->show_Menu();
}
//保存文件
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//将每个选手的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();it++) {
		ofs << *it << ","  << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "文件记录已完成！" << endl;

	//更改文件不为空状态
	this->FileIsEmpty= false;
}
//加载文件
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv",ios::in);//读文件
	if (!ifs.is_open()){ //判断文件是否为空
		this->FileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof()){
		this->FileIsEmpty = true;
		cout << "文件为空" << endl;
		ifs.close();
		return;
	}
	//文件不为空
	this->FileIsEmpty = false;
	ifs.putback(ch);//因为之前检测是否为空，读取了一个，现在退还单个字符
	string data;
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		//10002,86.675,10009,81.3,10007,78.55,
		int pos = -1; //查找 , 的位置
		int start = 0;
		vector<string>v;//存放冠军数据
		while (true){
			pos = data.find(",", start);
			if (pos == -1) {
				//没有找到的情况
				break;
			}
			string temp;
			temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v)); //key是第几届，value是具体的编号+得分内容
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
		cout << "第" << it->first << "届比赛---冠军编号：" << it->second[0] << " 冠军得分：" << it->second[1] << endl;
	}*/
}
void SpeechManager::showRecord() {
	if (this->FileIsEmpty){
		cout << "文件为或者文件不存在" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++){
		cout << "第" << i + 1 << "届比赛 "
			<< "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
			<< "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
			<< "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}
//退出系统
void SpeechManager::exitSystem() {
	cout << "已退出系统，欢迎下次使用" << endl;
	exit(0);
	system("pause");
}
//清空操作
void SpeechManager::clearRecord() {
	cout << "是否清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1){
		//ios::trunc 的打开方式， 如果文件存在，则删除文件并重新创建
		ofstream ofs("speech.csv",ios::trunc);//清空
		ofs.close();

		//初始化属性
		this->initSpeech();
		//创建选手
		this->createSpeaker();
		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {


}
//关于vector数组越界，自己以txt方式打开csv文件看看数
//据中的最后一个“      ，     ”是否被修改或删除了，如果没有会报错，我的越界就是这么解决的