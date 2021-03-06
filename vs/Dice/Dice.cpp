#include <Windows.h>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
/*#include <thread>
#include <queue>
#include <atomic>
#include <chrono>
#include <mutex>*/
#include "APPINFO.h"
#include "RD.h"
#include "..\..\src\CQSDK\CQEVE_ALL.h"
#include "..\..\src\CQSDK\CQTools.h"

using namespace std;
using namespace CQ;
/*struct MSGSendT {
	long long target;
	string msg;
	int type;
	//0-Private 1-Group 2-Discuss
};
queue<MSGSendT> SendMsgQueue;
mutex mutexMsg;*/
/*thread MsgSend
{ [&]
	{
		while (1) {
			
			while(!SendMsgQueue.empty()) {
				if (SendMsgQueue.front().type == 0) {
					sendPrivateMsg(SendMsgQueue.front().target, SendMsgQueue.front().msg);
				}
				else if (SendMsgQueue.front().type == 1) {
					sendGroupMsg(SendMsgQueue.front().target, SendMsgQueue.front().msg);
				}
				else {
					sendDiscussMsg(SendMsgQueue.front().target, SendMsgQueue.front().msg);
				}
				SendMsgQueue.pop();
			}
			
			this_thread::sleep_for(chrono::milliseconds(50));
		}
	}
};*/
map<long long, RP> JRRP;
map<long long, int> DefaultDice;
map<pair<long long, long long>, string> GroupName;
map<pair<long long, long long>, string> DiscussName;
set<long long> DisabledGroup;
set<long long> DisabledDiscuss;
set<long long> DisabledJRRPGroup;
set<long long> DisabledJRRPDiscuss;
set<long long> DisabledMEGroup;
set<long long> DisabledMEDiscuss;
set<long long> DisabledOBGroup;
set<long long> DisabledOBDiscuss;
multimap<long long, long long> ObserveGroup;
multimap<long long, long long> ObserveDiscuss;
string strFileLoc;

EVE_Startup(__eventStartup) {
	//MsgSend.detach();
	strFileLoc = getAppDirectory();
	ifstream ifstreamGroupName(strFileLoc + "GroupName.RDconf");
	if (ifstreamGroupName) {
		long long QQ;
		long long Group;
		string name;
		pair<long long, long long> pairQQGroup;
		while (ifstreamGroupName >> QQ) {
			ifstreamGroupName >> Group >> name;
			pairQQGroup.first = QQ;
			pairQQGroup.second = Group;
			GroupName[pairQQGroup] = name;
		}
	}
	ifstreamGroupName.close();
	ifstream ifstreamDiscussName(strFileLoc + "DiscussName.RDconf");
	if (ifstreamDiscussName) {
		long long QQ;
		long long Discuss;
		string name;
		pair<long long, long long> pairQQDiscuss;
		while (ifstreamDiscussName >> QQ) {
			ifstreamDiscussName >> Discuss >> name;
			pairQQDiscuss.first = QQ;
			pairQQDiscuss.second = Discuss;
			DiscussName[pairQQDiscuss] = name;
		}
	}
	ifstreamDiscussName.close();
	ifstream ifstreamDisabledGroup(strFileLoc + "DisabledGroup.RDconf");
	if (ifstreamDisabledGroup) {
		long long Group;
		while (ifstreamDisabledGroup >> Group) {
			DisabledGroup.insert(Group);
		}
	}
	ifstreamDisabledGroup.close();
	ifstream ifstreamDisabledDiscuss(strFileLoc + "DisabledDiscuss.RDconf");
	if (ifstreamDisabledDiscuss) {
		long long Discuss;
		while (ifstreamDisabledDiscuss >> Discuss) {
			DisabledDiscuss.insert(Discuss);
		}
	}
	ifstreamDisabledDiscuss.close();
	ifstream ifstreamDisabledJRRPGroup(strFileLoc + "DisabledJRRPGroup.RDconf");
	if (ifstreamDisabledJRRPGroup) {
		long long Group;
		while (ifstreamDisabledJRRPGroup >> Group) {
			DisabledJRRPGroup.insert(Group);
		}
	}
	ifstreamDisabledJRRPGroup.close();
	ifstream ifstreamDisabledJRRPDiscuss(strFileLoc + "DisabledJRRPDiscuss.RDconf");
	if (ifstreamDisabledJRRPDiscuss) {
		long long Discuss;
		while (ifstreamDisabledJRRPDiscuss >> Discuss) {
			DisabledJRRPDiscuss.insert(Discuss);
		}
	}
	ifstreamDisabledJRRPDiscuss.close();
	ifstream ifstreamDisabledMEGroup(strFileLoc + "DisabledMEGroup.RDconf");
	if (ifstreamDisabledMEGroup) {
		long long Group;
		while (ifstreamDisabledMEGroup >> Group) {
			DisabledMEGroup.insert(Group);
		}
	}
	ifstreamDisabledMEGroup.close();
	ifstream ifstreamDisabledMEDiscuss(strFileLoc + "DisabledMEDiscuss.RDconf");
	if (ifstreamDisabledMEDiscuss) {
		long long Discuss;
		while (ifstreamDisabledMEDiscuss >> Discuss) {
			DisabledMEDiscuss.insert(Discuss);
		}
	}
	ifstreamDisabledMEDiscuss.close();
	ifstream ifstreamDisabledOBGroup(strFileLoc + "DisabledOBGroup.RDconf");
	if (ifstreamDisabledOBGroup) {
		long long Group;
		while (ifstreamDisabledOBGroup >> Group) {
			DisabledOBGroup.insert(Group);
		}
	}
	ifstreamDisabledOBGroup.close();
	ifstream ifstreamDisabledOBDiscuss(strFileLoc + "DisabledOBDiscuss.RDconf");
	if (ifstreamDisabledOBDiscuss) {
		long long Discuss;
		while (ifstreamDisabledOBDiscuss >> Discuss) {
			DisabledOBDiscuss.insert(Discuss);
		}
	}
	ifstreamDisabledOBDiscuss.close();
	ifstream ifstreamObserveGroup(strFileLoc + "ObserveGroup.RDconf");
	if (ifstreamObserveGroup) {
		long long Group, QQ;
		while (ifstreamObserveGroup >> Group >> QQ) {
			ObserveGroup.insert(make_pair(Group, QQ));
		}
	}
	ifstreamObserveGroup.close();

	ifstream ifstreamObserveDiscuss(strFileLoc + "ObserveDiscuss.RDconf");
	if (ifstreamObserveDiscuss) {
		long long Discuss, QQ;
		while (ifstreamObserveDiscuss >> Discuss >> QQ) {
			ObserveDiscuss.insert(make_pair(Discuss, QQ));
		}
	}
	ifstreamObserveDiscuss.close();
	ifstream ifstreamJRRP(strFileLoc + "JRRP.RDconf");
	if (ifstreamJRRP) {
		long long QQ;
		int Val;
		string strDate;
		while (ifstreamJRRP >> QQ >> strDate >> Val) {
			JRRP[QQ].Date = strDate;
			JRRP[QQ].RPVal = Val;
		}
	}
	ifstreamJRRP.close();
	ifstream ifstreamDefault(strFileLoc + "Default.RDconf");
	if (ifstreamDefault) {
		long long QQ;
		int DefVal;
		while (ifstreamDefault >> QQ >> DefVal) {
			DefaultDice[QQ] = DefVal;
		}
	}
	ifstreamDefault.close();
	return 0;
}


EVE_PrivateMsg_EX(__eventPrivateMsg) {
	init(eve.message);
	if (eve.message[0] != '.')return;
	int intMsgCnt = 1;
	while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
	eve.message_block();
	string strNickName = getStrangerInfo(eve.fromQQ).nick;
	string strLowerMessage = eve.message;
	transform(strLowerMessage.begin(), strLowerMessage.end(), strLowerMessage.begin(), tolower);
	if (strLowerMessage.find("help") == intMsgCnt) {
		
		sendPrivateMsg(eve.fromQQ,strHlpMsg);
		
	}
	else if (strLowerMessage.find("ti") == intMsgCnt) {
		string strAns = strNickName + "的临时性疯狂:\n";
		TempInsane(strAns);
		
		sendPrivateMsg(eve.fromQQ,strAns);
		
	}
	else if (strLowerMessage.find("li") == intMsgCnt) {
		string strAns = strNickName + "的不定性疯狂:\n";
		LongInsane(strAns);
		
		sendPrivateMsg(eve.fromQQ,strAns);
		
	}
	else if (strLowerMessage.find("sc") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string SanCost = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		intMsgCnt += SanCost.length();
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string San = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (SanCost == "" || SanCost.find("/") == string::npos) {
			
			sendPrivateMsg(eve.fromQQ,strSCInvalid);
			
			return;
		}
		if (San == "") {
			
			sendPrivateMsg(eve.fromQQ,strSanInvalid);
			
			return;
		}
		RD rdTest1(SanCost.substr(0, SanCost.find("/")));
		RD rdTest2(SanCost.substr(SanCost.find("/") + 1));
		if (rdTest1.Roll() != 0 || rdTest2.Roll() != 0) {
			
			sendPrivateMsg(eve.fromQQ,strSCInvalid);
			
			return;
		}
		for (auto i : San)
			if (!isdigit(i)) {
				
				sendPrivateMsg(eve.fromQQ,strSanInvalid);
				
				return;
			}
		if (San.length() >= 3) {
			
			sendPrivateMsg(eve.fromQQ,strSanInvalid);
			
			return;
		}
		int intSan = Convert<int> (San);
		if (intSan == 0) {
			
			sendPrivateMsg(eve.fromQQ,strSanInvalid);
			
			return;
		}
		string strAns = strNickName + "的Sancheck:\n1D100=";
		RD rdD100("D100");
		rdD100.Roll();
		strAns += to_string(rdD100.intTotal);

		if (rdD100.intTotal <= intSan) {
			strAns += " 成功\n你的San值减少" + SanCost.substr(0, SanCost.find("/"));
			RD rdSan(SanCost.substr(0, SanCost.find("/")));
			rdSan.Roll();
			if (SanCost.substr(0, SanCost.find("/")).find("d") != string::npos)strAns += "=" + to_string(rdSan.intTotal);
			strAns += +"点,当前剩余" + to_string(intSan - rdSan.intTotal) + "点";
		}
		else {
			strAns += " 失败\n你的San值减少" + SanCost.substr(SanCost.find("/") + 1);
			RD rdSan(SanCost.substr(SanCost.find("/") + 1));
			rdSan.Roll();
			if (SanCost.substr(SanCost.find("/") + 1).find("d") != string::npos)strAns += "=" + to_string(rdSan.intTotal);
			strAns += +"点,当前剩余" + to_string(intSan - rdSan.intTotal) + "点";
		}
		
		sendPrivateMsg(eve.fromQQ,strAns);
		
	}
	else if (strLowerMessage.find("en") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strSkillName;
		while (intMsgCnt != eve.message.length()&&!isdigit(eve.message[intMsgCnt]) && !isspace(eve.message[intMsgCnt])) {
			strSkillName += eve.message[intMsgCnt];
			intMsgCnt++;
		}
		while (isspace(eve.message[intMsgCnt]))intMsgCnt++;
		string strCurrentValue;
		while (isdigit(eve.message[intMsgCnt])) {
			strCurrentValue += eve.message[intMsgCnt];
			intMsgCnt++;
		}
		if (strCurrentValue.empty()) {
			
			sendPrivateMsg(eve.fromQQ,strEnValInvalid);
			
			return;
		}
		if (strCurrentValue.length() >= 3) {
			
			sendPrivateMsg(eve.fromQQ,strEnValInvalid);
			
			return;
		}
		int intCurrentVal = Convert<int>(strCurrentValue);
		if (intCurrentVal == 0) {
			
			sendPrivateMsg(eve.fromQQ,strEnValInvalid);
			
			return;
		}
		string strAns = strNickName + "的"+ strSkillName +"增强或成长检定:\n1D100=";
		RD rdD100("D100");
		rdD100.Roll();
		strAns += to_string(rdD100.intTotal);

		if (rdD100.intTotal <= intCurrentVal) {
			strAns += " 失败!\n你的" + (strSkillName.empty() ? "属性或技能值" : strSkillName) + "没有变化!";
		}
		else {
			strAns += " 成功!\n你的" + (strSkillName.empty() ? "属性或技能值" : strSkillName) + "增加1D10=";
			RD rdAddVal("D10");
			rdAddVal.Roll();
			strAns += to_string(rdAddVal.intTotal) + "点,当前为" + to_string(intCurrentVal + rdAddVal.intTotal) + "点";
		}
		
		sendPrivateMsg(eve.fromQQ,strAns);
		
	}
	else if (strLowerMessage.find("jrrp") == intMsgCnt) {
		char cstrDate[100] = {};
		time_t time_tTime = 0;
		time(&time_tTime);
		tm tmTime;
		localtime_s(&tmTime, &time_tTime);
		strftime(cstrDate, 100, "%F", &tmTime);
		if (JRRP.count(eve.fromQQ) && JRRP[eve.fromQQ].Date == cstrDate) {
			string strReply = strNickName + "今天的人品值是:" + to_string(JRRP[eve.fromQQ].RPVal);
			
			sendPrivateMsg(eve.fromQQ,strReply);
			
		}
		else {
			normal_distribution<double> NormalDistribution(60, 15);
			mt19937 Generator(static_cast<unsigned int> (GetCycleCount()));
			int JRRPRes;
			do {
				JRRPRes = static_cast<int> (NormalDistribution(Generator));
			} while (JRRPRes <= 0 || JRRPRes > 100);
			JRRP[eve.fromQQ].Date = cstrDate;
			JRRP[eve.fromQQ].RPVal = JRRPRes;
			string strReply(strNickName + "今天的人品值是:" + to_string(JRRP[eve.fromQQ].RPVal));
			
			sendPrivateMsg(eve.fromQQ,strReply);
			
		}
	}
	else if (strLowerMessage.find("rules") == intMsgCnt) {
		intMsgCnt += 5;
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
		string strSearch = eve.message.substr(intMsgCnt);
		for (auto &n : strSearch)n = toupper(n);
		for (int i = 0; i != strSearch.length(); ++i)if (strSearch[i] == ' ') {
			strSearch.erase(strSearch.begin() + i);
			i--;
		}
		strSearch = "||" + strSearch + "||";
		int Loc = strRules.find(strSearch);
		if (Loc != string::npos || strSearch == "||战斗||" || strSearch == "||战斗流程||" || strSearch == "||战斗伤害||") {
			if (strSearch == "||战斗||" || strSearch == "||战斗流程||") {
				string IMAGE = "[CQ:image,file=";
				string IMAGENAME = "Combat.jpg";
				IMAGE += msg_encode(IMAGENAME, true) + "]";
				int res = sendPrivateMsg(eve.fromQQ, IMAGE);
				if (res < 0)sendPrivateMsg(eve.fromQQ, "未找到对应的规则信息!");
			}
			else if (strSearch == "||战斗伤害||") {
				string IMAGE = "[CQ:image,file=";
				string IMAGENAME = "Combat1.jpg";
				IMAGE += msg_encode(IMAGENAME, true) + "]";
				int res = sendPrivateMsg(eve.fromQQ, IMAGE);
				if (res < 0)sendPrivateMsg(eve.fromQQ, "未找到对应的规则信息!");
			}
			else {
				int LocStart = strRules.find("]", Loc) + 1;
				string strReply = strRules.substr(LocStart, strRules.find("[", LocStart) - LocStart - 1);
				
				sendPrivateMsg(eve.fromQQ,strReply);
				
			}
		}
		else {
			
			sendPrivateMsg(eve.fromQQ,"未找到对应的规则信息!");
			
		}
	}
	else if (strLowerMessage.find("me") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strGroupID;
		while (isdigit(strLowerMessage[intMsgCnt])) {
			strGroupID += strLowerMessage[intMsgCnt];
			intMsgCnt++;
		}
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strAction = strLowerMessage.substr(intMsgCnt);

		for (auto i : strGroupID) {
			if (!isdigit(i)) {
				sendPrivateMsg(eve.fromQQ, strGroupIDInvalid);
				return;
			}
		}
		if (strGroupID.empty()) {
			sendPrivateMsg(eve.fromQQ, "群号不能为空!");
			return;
		}
		if (strAction.empty()) {
			sendPrivateMsg(eve.fromQQ, "动作不能为空!");
			return;
		}
		long long llGroupID = Convert<long long>(strGroupID);
		if (DisabledGroup.count(llGroupID)) {
			sendPrivateMsg(eve.fromQQ, strDisabledErr);
			return;
		}
		if (DisabledMEGroup.count(llGroupID)) {
			sendPrivateMsg(eve.fromQQ, strMEDisabledErr);
			return;
		}
		pair<long long, long long>pairQQGroup(eve.fromQQ, llGroupID);
		string strReply = (GroupName.count(pairQQGroup) ? GroupName[pairQQGroup] : getGroupMemberInfo(llGroupID, eve.fromQQ).名片.empty() ? getStrangerInfo(eve.fromQQ).nick : getGroupMemberInfo(llGroupID, eve.fromQQ).名片) + strAction;
		int intSendRes = sendGroupMsg(llGroupID, strReply);
		if (intSendRes < 0)sendPrivateMsg(eve.fromQQ, strSendErr);
		else sendPrivateMsg(eve.fromQQ, "命令执行成功!");
	}
	else if (strLowerMessage.find("set") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strDefaultDice = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strDefaultDice[0] == '0')strDefaultDice.erase(strDefaultDice.begin());
		if (strDefaultDice.empty())strDefaultDice = "100";
		for (auto charNumElement:strDefaultDice)
			if (!isdigit(charNumElement)) {
				sendPrivateMsg(eve.fromQQ, strSetInvalid);
				return;
			}
		if (strDefaultDice.length() > 5) {
			sendPrivateMsg(eve.fromQQ, strSetTooBig);
			return;
		}
		int intDefaultDice = Convert<int>(strDefaultDice);
		if (intDefaultDice == 100)DefaultDice.erase(eve.fromQQ);
		else DefaultDice[eve.fromQQ] = intDefaultDice;
		string strSetSuccessReply = "已将" + strNickName + "的默认骰类型更改为D" + strDefaultDice;
		sendPrivateMsg(eve.fromQQ, strSetSuccessReply);
	}
	else if (strLowerMessage.find("coc6d") == intMsgCnt) {
		string strReply = strNickName;
		COC6D(strReply);
		sendPrivateMsg(eve.fromQQ, strReply);
	}
	else if (strLowerMessage.find("coc6") == intMsgCnt) {
		intMsgCnt += 4;
		if (strLowerMessage[intMsgCnt] == 's')intMsgCnt++;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendPrivateMsg(eve.fromQQ, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendPrivateMsg(eve.fromQQ, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendPrivateMsg(eve.fromQQ, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendPrivateMsg(eve.fromQQ, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		COC6(strReply, intNum);
		sendPrivateMsg(eve.fromQQ, strReply);
	}
	else if (strLowerMessage.find("dnd") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendPrivateMsg(eve.fromQQ, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendPrivateMsg(eve.fromQQ, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendPrivateMsg(eve.fromQQ, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendPrivateMsg(eve.fromQQ, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		DND(strReply, intNum);
		sendPrivateMsg(eve.fromQQ, strReply);
	}
	else if (strLowerMessage.find("coc7d") == intMsgCnt|| strLowerMessage.find("cocd") == intMsgCnt) {
		string strReply = strNickName;
		COC7D(strReply);
		sendPrivateMsg(eve.fromQQ, strReply);
	}
	else if (strLowerMessage.find("coc") == intMsgCnt) {
		intMsgCnt += 3;
		if (strLowerMessage[intMsgCnt] == '7')intMsgCnt++;
		if (strLowerMessage[intMsgCnt] == 's')intMsgCnt++;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendPrivateMsg(eve.fromQQ, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendPrivateMsg(eve.fromQQ, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendPrivateMsg(eve.fromQQ, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendPrivateMsg(eve.fromQQ, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		COC7(strReply, intNum);
		sendPrivateMsg(eve.fromQQ, strReply);
	}
	else if (strLowerMessage[intMsgCnt] == 'r' || strLowerMessage[intMsgCnt] == 'o' || strLowerMessage[intMsgCnt]=='d') {
		intMsgCnt += 1;
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;

		string strMainDice;
		string strReason;
		bool tmpContainD = false;
		int intTmpMsgCnt;
		for (intTmpMsgCnt =intMsgCnt; intTmpMsgCnt!=eve.message.length() && eve.message[intTmpMsgCnt] != ' '; intTmpMsgCnt++) {
			if (strLowerMessage[intTmpMsgCnt]=='d'|| strLowerMessage[intTmpMsgCnt] == 'p'|| strLowerMessage[intTmpMsgCnt] == 'b' || strLowerMessage[intTmpMsgCnt] == '#')tmpContainD = true;
			if (!isdigit(strLowerMessage[intTmpMsgCnt]) && strLowerMessage[intTmpMsgCnt] != 'd' &&strLowerMessage[intTmpMsgCnt] != 'k'&&strLowerMessage[intTmpMsgCnt] != 'p'&&strLowerMessage[intTmpMsgCnt] != 'b'&& strLowerMessage[intTmpMsgCnt] != '+'&&strLowerMessage[intTmpMsgCnt] != '-' && strLowerMessage[intTmpMsgCnt] != '#') {
				break;
			}
		}
		if (tmpContainD) {
			strMainDice = strLowerMessage.substr(intMsgCnt, intTmpMsgCnt - intMsgCnt);
			while (eve.message[intTmpMsgCnt] == ' ')intTmpMsgCnt++;
			strReason = eve.message.substr(intTmpMsgCnt);
		}
		else strReason = eve.message.substr(intMsgCnt);

		int intTurnCnt = 1;
		if (strMainDice.find("#") != string::npos) {
			string strTurnCnt = strMainDice.substr(0, strMainDice.find("#"));
			strMainDice = strMainDice.substr(strMainDice.find("#") + 1);
			RD rdTurnCnt(strTurnCnt, eve.fromQQ);
			int intRdTurnCntRes = rdTurnCnt.Roll();
			if (intRdTurnCntRes == Value_Err) {
				sendPrivateMsg(eve.fromQQ, strValueErr);
				return;
			}
			else if (intRdTurnCntRes == Input_Err) {
				sendPrivateMsg(eve.fromQQ, strInputErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroDice_Err) {
				sendPrivateMsg(eve.fromQQ, strZeroDiceErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroType_Err) {
				sendPrivateMsg(eve.fromQQ, strZeroTypeErr);
				return;
			}
			else if (intRdTurnCntRes == DiceTooBig_Err) {
				sendPrivateMsg(eve.fromQQ, strDiceTooBigErr);
				return;
			}
			else if (intRdTurnCntRes == TypeTooBig_Err) {
				sendPrivateMsg(eve.fromQQ, strTypeTooBigErr);
				return;
			}
			else if (intRdTurnCntRes != 0) {
				sendPrivateMsg(eve.fromQQ, "发生了未知错误!");
				return;
			}
			if (rdTurnCnt.intTotal > 10) {
				sendPrivateMsg(eve.fromQQ, "掷骰轮数超过了最大限制10次!");
				return;
			}
			else if (rdTurnCnt.intTotal <= 0) {
				sendPrivateMsg(eve.fromQQ, "异常的掷骰轮数");
				return;
			}
			intTurnCnt = rdTurnCnt.intTotal;
			if (strTurnCnt.find("d") != string::npos) {
				string strTurnNotice = strNickName + "的掷骰轮数: " + rdTurnCnt.FormCompleteString() + "轮";
				
				sendPrivateMsg(eve.fromQQ, strTurnNotice);
				
			}
		}

		RD rdMainDice(strMainDice, eve.fromQQ);
		while (intTurnCnt--) {
			int intRdTurnCntRes = rdMainDice.Roll();
			if (intRdTurnCntRes == Value_Err) {
				sendPrivateMsg(eve.fromQQ, strValueErr);
				return;
			}
			else if (intRdTurnCntRes == Input_Err) {
				sendPrivateMsg(eve.fromQQ, strInputErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroDice_Err) {
				sendPrivateMsg(eve.fromQQ, strZeroDiceErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroType_Err) {
				sendPrivateMsg(eve.fromQQ, strZeroTypeErr);
				return;
			}
			else if (intRdTurnCntRes == DiceTooBig_Err) {
				sendPrivateMsg(eve.fromQQ, strDiceTooBigErr);
				return;
			}
			else if (intRdTurnCntRes == TypeTooBig_Err) {
				sendPrivateMsg(eve.fromQQ, strTypeTooBigErr);
				return;
			}
			else if (intRdTurnCntRes != 0) {
				sendPrivateMsg(eve.fromQQ, "发生了未知错误!");
				return;
			}
			string strAns = strNickName + "骰出了: " + rdMainDice.FormCompleteString();
			if (!strReason.empty())strAns.insert(0, "由于" + strReason + " ");
			
			sendPrivateMsg(eve.fromQQ,strAns);
			
		}
	}
	else {
		if(eve.message[intMsgCnt]!='.'&&eve.message!="."&&eve.message[intMsgCnt] != '!'&&eve.message!="!"&&eve.message.find("。")!=intMsgCnt)sendPrivateMsg(eve.fromQQ, "命令输入错误!");
	}
}
EVE_GroupMsg_EX(__eventGroupMsg) {
	init(eve.message);
	if (eve.message[0] != '.')return;
	int intMsgCnt = 1;
	while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
	eve.message_block();
	pair<long long, long long>pairQQGroup(eve.fromQQ, eve.fromGroup);
	string strNickName = GroupName.count(pairQQGroup)? GroupName[pairQQGroup]: (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).名片.empty() ? getStrangerInfo(eve.fromQQ).nick : getGroupMemberInfo(eve.fromGroup, eve.fromQQ).名片);
	string strLowerMessage = eve.message;
	transform(strLowerMessage.begin(), strLowerMessage.end(), strLowerMessage.begin(), tolower);
	if (strLowerMessage.find("bot") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string Command;
		while (intMsgCnt != strLowerMessage.length()&&!isdigit(strLowerMessage[intMsgCnt])&&!isspace(strLowerMessage[intMsgCnt])) {
			Command += strLowerMessage[intMsgCnt];
			intMsgCnt++;
		}
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string QQNum = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (Command == "on") {
			if (QQNum.empty() || QQNum == to_string(getLoginQQ())) {
				if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
					if (DisabledGroup.count(eve.fromGroup)) {
						DisabledGroup.erase(eve.fromGroup);
						sendGroupMsg(eve.fromGroup, "成功开启本机器人!");
					}
					else sendGroupMsg(eve.fromGroup, "本机器人已经处于开启状态!");
				}
				else sendGroupMsg(eve.fromGroup, "访问被拒绝,您没有足够的权限!");
			}
		}
		else if (Command == "off") {
			if (QQNum.empty() || QQNum == to_string(getLoginQQ())) {
				if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
					if (!DisabledGroup.count(eve.fromGroup)) {
						DisabledGroup.insert(eve.fromGroup);
						sendGroupMsg(eve.fromGroup, "成功关闭本机器人!");
					}
					else sendGroupMsg(eve.fromGroup, "本机器人已经处于关闭状态!");
				}
				else sendGroupMsg(eve.fromGroup, "访问被拒绝,您没有足够的权限!");
			}
		}
		else{
			if (QQNum == "" || QQNum == to_string(getLoginQQ())) {
				if (DisabledGroup.count(eve.fromGroup)) sendGroupMsg(eve.fromGroup, "机器人处于关闭状态!");
				else sendGroupMsg(eve.fromGroup, "机器人处于开启状态!");
			}
		}
		return;
	}
	if (DisabledGroup.count(eve.fromGroup))return;
	if (strLowerMessage.find("help") == intMsgCnt) {
		sendGroupMsg(eve.fromGroup, strHlpMsg);
	}
	else if (strLowerMessage.find("ob") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string Command = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (Command == "on") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				if (DisabledOBGroup.count(eve.fromGroup)) {
					DisabledOBGroup.erase(eve.fromGroup);
					sendGroupMsg(eve.fromGroup, "成功在本群中启用旁观模式!");
				}
				else {
					sendGroupMsg(eve.fromGroup, "在本群中旁观模式没有被禁用!");
				}
			}
			else {
				sendGroupMsg(eve.fromGroup, "你没有权限执行此命令!");
			}
			return;
		}
		else if (Command == "off") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				if (!DisabledOBGroup.count(eve.fromGroup)) {
					DisabledOBGroup.insert(eve.fromGroup);
					ObserveGroup.clear();
					sendGroupMsg(eve.fromGroup, "成功在本群中禁用旁观模式!");
				}
				else {
					sendGroupMsg(eve.fromGroup, "在本群中旁观模式没有被启用!");
				}
			}
			else {
				sendGroupMsg(eve.fromGroup, "你没有权限执行此命令!");
			}
			return;
		}
		if (DisabledOBGroup.count(eve.fromGroup)) {
			sendGroupMsg(eve.fromGroup, "在本群中旁观模式已被禁用!");
		}
		if (Command == "list") {
			string Msg = "当前的旁观者有:";
			auto Range = ObserveGroup.equal_range(eve.fromGroup);
			for (auto it = Range.first; it != Range.second; ++it) {
				pair<long long, long long> ObGroup;
				ObGroup.first = it->second;
				ObGroup.second = eve.fromGroup;
				Msg += "\n" + (GroupName.count(ObGroup) ? GroupName[ObGroup] : getGroupMemberInfo(eve.fromGroup, it->second).名片.empty() ? getStrangerInfo(it->second).nick : getGroupMemberInfo(eve.fromGroup, it->second).名片) + "(" + to_string(it->second) + ")";
			}
			string strReply = Msg == "当前的旁观者有:" ? "当前暂无旁观者" : Msg;
			sendGroupMsg(eve.fromGroup, strReply);
		}
		else if (Command == "clr") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				ObserveGroup.erase(eve.fromGroup);
				sendGroupMsg(eve.fromGroup, "成功删除所有旁观者!");
			}
			else {
				sendGroupMsg(eve.fromGroup, "你没有权限执行此命令!");
			}
		}
		else if (Command == "exit") {
			auto Range = ObserveGroup.equal_range(eve.fromGroup);
			for (auto it = Range.first; it != Range.second; ++it) {
				if (it->second == eve.fromQQ) {
					ObserveGroup.erase(it);
					string strReply = strNickName + "成功退出旁观模式!";
					sendGroupMsg(eve.fromGroup, strReply);
					eve.message_block();
					return;
				}
			}
			string strReply = strNickName + "没有加入旁观模式!";
			sendGroupMsg(eve.fromGroup, strReply);
		}
		else {
			auto Range = ObserveGroup.equal_range(eve.fromGroup);
			for (auto it = Range.first; it != Range.second; ++it) {
				if (it->second == eve.fromQQ) {
					string strReply = strNickName + "已经处于旁观模式!";
					sendGroupMsg(eve.fromGroup, strReply);
					eve.message_block();
					return;
				}
			}
			ObserveGroup.insert(make_pair(eve.fromGroup, eve.fromQQ));
			string strReply = strNickName + "成功加入旁观模式!";
			sendGroupMsg(eve.fromGroup, strReply);
		}
	}
	else if (strLowerMessage.find("ti") == intMsgCnt) {
		string strAns = strNickName + "的临时性疯狂:\n";
		TempInsane(strAns);
		sendGroupMsg(eve.fromGroup, strAns);
	}
	else if (strLowerMessage.find("li") == intMsgCnt) {
		string strAns = strNickName + "的不定性疯狂:\n";
		LongInsane(strAns);
		sendGroupMsg(eve.fromGroup, strAns);
	}
	else if (strLowerMessage.find("sc") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string SanCost = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		intMsgCnt += SanCost.length();
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string San = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (SanCost == "" || SanCost.find("/") == string::npos) {
			sendGroupMsg(eve.fromGroup, strSCInvalid);
			return;
		}
		if (San == "") {
			sendGroupMsg(eve.fromGroup, strSanInvalid);
			return;
		}
		RD rdTest1(SanCost.substr(0, SanCost.find("/")));
		RD rdTest2(SanCost.substr(SanCost.find("/") + 1));
		if (rdTest1.Roll() != 0 || rdTest2.Roll() != 0) {
			sendGroupMsg(eve.fromGroup, strSCInvalid);
			return;
		}
		for (auto i : San)
			if (!isdigit(i)) {
				sendGroupMsg(eve.fromGroup, strSanInvalid);
				return;
			}
		if (San.length() >= 3) {
			sendGroupMsg(eve.fromGroup, strSanInvalid);
			return;
		}
		int intSan = Convert<int>(San);
		if (intSan == 0) {
			sendGroupMsg(eve.fromGroup, strSanInvalid);
			return;
		}
		string strAns = strNickName + "的Sancheck:\n1D100=";
		RD rdD100("D100");
		rdD100.Roll();
		strAns += to_string(rdD100.intTotal);

		if (rdD100.intTotal <= intSan) {
			strAns += " 成功\n你的San值减少" + SanCost.substr(0, SanCost.find("/"));
			RD rdSan(SanCost.substr(0, SanCost.find("/")));
			rdSan.Roll();
			if (SanCost.substr(0, SanCost.find("/")).find("d") != string::npos)strAns += "=" + to_string(rdSan.intTotal);
			strAns += +"点,当前剩余" + to_string(intSan - rdSan.intTotal) + "点";
		}
		else {
			strAns += " 失败\n你的San值减少" + SanCost.substr(SanCost.find("/") + 1);
			RD rdSan(SanCost.substr(SanCost.find("/") + 1));
			rdSan.Roll();
			if (SanCost.substr(SanCost.find("/") + 1).find("d") != string::npos)strAns += "=" + to_string(rdSan.intTotal);
			strAns += +"点,当前剩余" + to_string(intSan - rdSan.intTotal) + "点";
		}
		sendGroupMsg(eve.fromGroup, strAns);
	}
	else if (strLowerMessage.find("en") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strSkillName;
		while (intMsgCnt != eve.message.length()&&!isdigit(eve.message[intMsgCnt]) && !isspace(eve.message[intMsgCnt])) {
			strSkillName += eve.message[intMsgCnt];
			intMsgCnt++;
		}
		while (isspace(eve.message[intMsgCnt]))intMsgCnt++;
		string strCurrentValue;
		while (isdigit(eve.message[intMsgCnt])) {
			strCurrentValue += eve.message[intMsgCnt];
			intMsgCnt++;
		}
		if (strCurrentValue.empty()) {
			sendGroupMsg(eve.fromGroup, strEnValInvalid);
			return;
		}
		if (strCurrentValue.length() >= 3) {
			sendGroupMsg(eve.fromGroup, strEnValInvalid);
			return;
		}
		int intCurrentVal = Convert<int>(strCurrentValue);
		if (intCurrentVal == 0) {
			sendGroupMsg(eve.fromGroup, strEnValInvalid);
			return;
		}
		string strAns = strNickName + "的" + strSkillName + "增强或成长检定:\n1D100=";
		RD rdD100("D100");
		rdD100.Roll();
		strAns += to_string(rdD100.intTotal);

		if (rdD100.intTotal <= intCurrentVal) {
			strAns += " 失败!\n你的" + (strSkillName.empty() ? "属性或技能值" : strSkillName) + "没有变化!";
		}
		else {
			strAns += " 成功!\n你的" + (strSkillName.empty() ? "属性或技能值" : strSkillName) + "增加1D10=";
			RD rdAddVal("D10");
			rdAddVal.Roll();
			strAns += to_string(rdAddVal.intTotal) + "点,当前为" + to_string(intCurrentVal + rdAddVal.intTotal) + "点";
		}
		sendGroupMsg(eve.fromGroup, strAns);
	}
	else if (strLowerMessage.find("jrrp") == intMsgCnt) {
		intMsgCnt += 4;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string Command = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (Command == "on") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				if (DisabledJRRPGroup.count(eve.fromGroup)) {
					DisabledJRRPGroup.erase(eve.fromGroup);
					sendGroupMsg(eve.fromGroup, "成功在本群中启用JRRP!");
				}
				else {
					sendGroupMsg(eve.fromGroup, "在本群中JRRP没有被禁用!");
				}
			}
			else sendGroupMsg(eve.fromGroup, "您没有权限执行此命令!");
			return;
		}
		else if (Command == "off") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				if (!DisabledJRRPGroup.count(eve.fromGroup)) {
					DisabledJRRPGroup.insert(eve.fromGroup);
					sendGroupMsg(eve.fromGroup, "成功在本群中禁用JRRP!");
				}
				else {
					sendGroupMsg(eve.fromGroup, "在本群中JRRP没有被启用!");
				}
			}
			else sendGroupMsg(eve.fromGroup, "您没有权限执行此命令!");
			return;
		}
		if (DisabledJRRPGroup.count(eve.fromGroup)) {
			sendGroupMsg(eve.fromGroup, "在本群中JRRP功能已被禁用");
			return;
		}
		char cstrDate[100] = {};
		time_t time_tTime = 0;
		time(&time_tTime);
		tm tmTime;
		localtime_s(&tmTime, &time_tTime);
		strftime(cstrDate, 100, "%F", &tmTime);
		if (JRRP.count(eve.fromQQ) && JRRP[eve.fromQQ].Date == cstrDate) {
			string strReply = strNickName + "今天的人品值是:" + to_string(JRRP[eve.fromQQ].RPVal);
			sendGroupMsg(eve.fromGroup, strReply);
		}
		else {
			normal_distribution<double> NormalDistribution(60, 15);
			mt19937 Generator(static_cast<unsigned int> (GetCycleCount()));
			int JRRPRes;
			do {
				JRRPRes = static_cast<int> (NormalDistribution(Generator));
			} while (JRRPRes <= 0 || JRRPRes > 100);
			JRRP[eve.fromQQ].Date = cstrDate;
			JRRP[eve.fromQQ].RPVal = JRRPRes;
			string strReply(strNickName + "今天的人品值是:" + to_string(JRRP[eve.fromQQ].RPVal));
			sendGroupMsg(eve.fromGroup, strReply);
		}
	}
	else if (strLowerMessage.find("nn") == intMsgCnt) {
		intMsgCnt += 2;
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
		string name = eve.message.substr(intMsgCnt);
		if (!name.empty()) {
			GroupName[pairQQGroup] = name;
			string strReply = "已将" + strNickName + "的名称更改为" + name;
			sendGroupMsg(eve.fromGroup, strReply);
		}
		else {
			if (GroupName.count(pairQQGroup)) {
				GroupName.erase(pairQQGroup);
				string strReply = "已将" + strNickName + "的名称删除";
				sendGroupMsg(eve.fromGroup, strReply);
			}
			else {
				string strReply = strNickName + strNameDelErr;
				sendGroupMsg(eve.fromGroup, strReply);
			}
		}
	}
	else if (strLowerMessage.find("rules") == intMsgCnt) {
		intMsgCnt += 5;
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
		string strSearch = eve.message.substr(intMsgCnt);
		for (auto &n : strSearch)n = toupper(n);
		for (int i = 0; i != strSearch.length(); ++i)if (strSearch[i] == ' ') {
			strSearch.erase(strSearch.begin() + i);
			i--;
		}
		strSearch = "||" + strSearch + "||";
		int Loc = strRules.find(strSearch);
		if (Loc != string::npos || strSearch == "||战斗||" || strSearch == "||战斗流程||" || strSearch == "||战斗伤害||") {
			if (strSearch == "||战斗||" || strSearch == "||战斗流程||") {
				string IMAGE = "[CQ:image,file=";
				string IMAGENAME = "Combat.jpg";
				IMAGE += msg_encode(IMAGENAME, true) + "]";
				int res = sendGroupMsg(eve.fromGroup, IMAGE);
				if (res < 0)sendGroupMsg(eve.fromGroup, "未找到对应的规则信息!");
			}
			else if (strSearch == "||战斗伤害||") {
				string IMAGE = "[CQ:image,file=";
				string IMAGENAME = "Combat1.jpg";
				IMAGE += msg_encode(IMAGENAME, true) + "]";
				int res = sendGroupMsg(eve.fromGroup, IMAGE);
				if (res < 0)sendGroupMsg(eve.fromGroup, "未找到对应的规则信息!");
			}
			else {
				int LocStart = strRules.find("]", Loc) + 1;
				string strReply = strRules.substr(LocStart, strRules.find("[", LocStart) - LocStart - 1);
				sendGroupMsg(eve.fromGroup, strReply);
			}
		}
		else {
			sendGroupMsg(eve.fromGroup, "未找到对应的规则信息!");
		}
	}
	else if (strLowerMessage.find("me") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strAction = strLowerMessage.substr(intMsgCnt);
		if (strAction == "on") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				if (DisabledMEGroup.count(eve.fromGroup)) {
					DisabledMEGroup.erase(eve.fromGroup);
					sendGroupMsg(eve.fromGroup, "成功在本群中启用.me命令!");
				}
				else {
					sendGroupMsg(eve.fromGroup, "在本群中.me命令没有被禁用!");
				}
			}
			else sendGroupMsg(eve.fromGroup, "您没有权限执行此命令!");
			return;
		}
		else if (strAction == "off") {
			if (getGroupMemberInfo(eve.fromGroup, eve.fromQQ).permissions >= 2) {
				if (!DisabledMEGroup.count(eve.fromGroup)) {
					DisabledMEGroup.insert(eve.fromGroup);
					sendGroupMsg(eve.fromGroup, "成功在本群中禁用.me命令!");
				}
				else {
					sendGroupMsg(eve.fromGroup, "在本群中.me命令没有被启用!");
				}
			}
			else sendGroupMsg(eve.fromGroup, "您没有权限执行此命令!");
			return;
		}
		if (DisabledMEGroup.count(eve.fromGroup)) {
			sendGroupMsg(eve.fromGroup, "在本群中.me命令已被禁用!");
			return;
		}
		if (strAction.empty()) {
			sendGroupMsg(eve.fromGroup, "动作不能为空!");
			return;
		}
		if (DisabledMEGroup.count(eve.fromGroup)) {
			sendGroupMsg(eve.fromGroup, strMEDisabledErr);
			return;
		}
		string strReply = strNickName + strAction;
		sendGroupMsg(eve.fromGroup, strReply);
	}
	else if (strLowerMessage.find("set") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strDefaultDice = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strDefaultDice[0] == '0')strDefaultDice.erase(strDefaultDice.begin());
			if (strDefaultDice.empty())strDefaultDice = "100";
		for (auto charNumElement : strDefaultDice)
			if (!isdigit(charNumElement)) {
				sendGroupMsg(eve.fromGroup, strSetInvalid);
				return;
			}
		if (strDefaultDice.length() > 5) {
			sendGroupMsg(eve.fromGroup, strSetTooBig);
			return;
		}
		int intDefaultDice = Convert<int>(strDefaultDice);
		if (intDefaultDice == 100)DefaultDice.erase(eve.fromQQ);
		else DefaultDice[eve.fromQQ] = intDefaultDice;
		string strSetSuccessReply = "已将" + strNickName + "的默认骰类型更改为D" + strDefaultDice;
		sendGroupMsg(eve.fromGroup, strSetSuccessReply);
	}
	else if (strLowerMessage.find("coc6d") == intMsgCnt) {
		string strReply = strNickName;
		COC6D(strReply);
		sendGroupMsg(eve.fromGroup, strReply);
	}
	else if (strLowerMessage.find("coc6") == intMsgCnt) {
		intMsgCnt += 4;
		if (strLowerMessage[intMsgCnt] == 's')intMsgCnt++;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendGroupMsg(eve.fromGroup, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendGroupMsg(eve.fromGroup, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendGroupMsg(eve.fromGroup, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendGroupMsg(eve.fromGroup, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		COC6(strReply, intNum);
		sendGroupMsg(eve.fromGroup, strReply);
	}
	else if (strLowerMessage.find("dnd") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendGroupMsg(eve.fromGroup, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendGroupMsg(eve.fromGroup, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendGroupMsg(eve.fromGroup, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendGroupMsg(eve.fromGroup, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		DND(strReply, intNum);
		sendGroupMsg(eve.fromGroup, strReply);
	}
	else if (strLowerMessage.find("coc7d") == intMsgCnt || strLowerMessage.find("cocd") == intMsgCnt) {
		string strReply = strNickName;
		COC7D(strReply);
		sendGroupMsg(eve.fromGroup, strReply);
	}
	else if (strLowerMessage.find("coc") == intMsgCnt) {
		intMsgCnt += 3;
		if (strLowerMessage[intMsgCnt] == '7')intMsgCnt++;
		if (strLowerMessage[intMsgCnt] == 's')intMsgCnt++;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendGroupMsg(eve.fromGroup, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendGroupMsg(eve.fromGroup, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendGroupMsg(eve.fromGroup, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendGroupMsg(eve.fromGroup, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		COC7(strReply, intNum);
		sendGroupMsg(eve.fromGroup, strReply);
	}
	else if (strLowerMessage[intMsgCnt] == 'r' || strLowerMessage[intMsgCnt] == 'o'|| strLowerMessage[intMsgCnt] == 'h' || strLowerMessage[intMsgCnt] == 'd') {
		bool isHidden = false;
		if (strLowerMessage[intMsgCnt] == 'h')isHidden = true;
		intMsgCnt += 1;
		if (strLowerMessage[intMsgCnt] == 'h') {
			isHidden = true;
			intMsgCnt += 1;
		}
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;

		string strMainDice;
		string strReason;

		bool tmpContainD = false;
		int intTmpMsgCnt;
		for (intTmpMsgCnt = intMsgCnt; intTmpMsgCnt != eve.message.length() && eve.message[intTmpMsgCnt] != ' '; intTmpMsgCnt++) {
			if (strLowerMessage[intTmpMsgCnt] == 'd' || strLowerMessage[intTmpMsgCnt] == 'p' || strLowerMessage[intTmpMsgCnt] == 'b' || strLowerMessage[intTmpMsgCnt] == '#')tmpContainD = true;
			if (!isdigit(strLowerMessage[intTmpMsgCnt]) && strLowerMessage[intTmpMsgCnt] != 'd' &&strLowerMessage[intTmpMsgCnt] != 'k'&&strLowerMessage[intTmpMsgCnt] != 'p'&&strLowerMessage[intTmpMsgCnt] != 'b'&& strLowerMessage[intTmpMsgCnt] != '+'&&strLowerMessage[intTmpMsgCnt] != '-' && strLowerMessage[intTmpMsgCnt] != '#') {
				break;
			}
		}
		if (tmpContainD) {
			strMainDice = strLowerMessage.substr(intMsgCnt, intTmpMsgCnt - intMsgCnt);
			while (eve.message[intTmpMsgCnt] == ' ')intTmpMsgCnt++;
			strReason = eve.message.substr(intTmpMsgCnt);
		}
		else strReason = eve.message.substr(intMsgCnt);
		int intTurnCnt = 1;
		if (strMainDice.find("#") != string::npos) {
			string strTurnCnt = strMainDice.substr(0, strMainDice.find("#"));
			strMainDice = strMainDice.substr(strMainDice.find("#") + 1);
			RD rdTurnCnt(strTurnCnt, eve.fromQQ);
			int intRdTurnCntRes = rdTurnCnt.Roll();
			if (intRdTurnCntRes == Value_Err) {
				sendGroupMsg(eve.fromGroup, strValueErr);
				return;
			}
			else if (intRdTurnCntRes == Input_Err) {
				sendGroupMsg(eve.fromGroup, strInputErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroDice_Err) {
				sendGroupMsg(eve.fromGroup, strZeroDiceErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroType_Err) {
				sendGroupMsg(eve.fromGroup, strZeroTypeErr);
				return;
			}
			else if (intRdTurnCntRes == DiceTooBig_Err) {
				sendGroupMsg(eve.fromGroup, strDiceTooBigErr);
				return;
			}
			else if (intRdTurnCntRes == TypeTooBig_Err) {
				sendGroupMsg(eve.fromGroup, strTypeTooBigErr);
				return;
			}
			else if (intRdTurnCntRes != 0) {
				sendGroupMsg(eve.fromGroup, "发生了未知错误!");
				return;
			}
			if (rdTurnCnt.intTotal > 10) {
				sendGroupMsg(eve.fromGroup, "掷骰轮数超过了最大限制10次!");
				return;
			}
			else if (rdTurnCnt.intTotal <= 0) {
				sendGroupMsg(eve.fromGroup, "异常的掷骰轮数");
				return;
			}
			intTurnCnt = rdTurnCnt.intTotal;
			if (strTurnCnt.find("d") != string::npos) {
				string strTurnNotice = strNickName + "的掷骰轮数: " + rdTurnCnt.FormCompleteString() + "轮";
				if (isHidden) {
					strTurnNotice.insert(0, "在群\"" + getGroupList().at(eve.fromGroup) + "\"中 ");
					sendPrivateMsg(eve.fromQQ, strTurnNotice);
					auto Range = ObserveGroup.equal_range(eve.fromGroup);
					for (auto it = Range.first; it != Range.second; ++it) {
						if (it->second != eve.fromQQ)sendPrivateMsg(it->second, strTurnNotice);
					}
				}
				else sendGroupMsg(eve.fromGroup, strTurnNotice);
			}
		}

		RD rdMainDice(strMainDice, eve.fromQQ);
		while (intTurnCnt--) {
			int intRdTurnCntRes = rdMainDice.Roll();
			if (intRdTurnCntRes == Value_Err) {
				sendGroupMsg(eve.fromGroup, strValueErr);
				return;
			}
			else if (intRdTurnCntRes == Input_Err) {
				sendGroupMsg(eve.fromGroup, strInputErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroDice_Err) {
				sendGroupMsg(eve.fromGroup, strZeroDiceErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroType_Err) {
				sendGroupMsg(eve.fromGroup, strZeroTypeErr);
				return;
			}
			else if (intRdTurnCntRes == DiceTooBig_Err) {
				sendGroupMsg(eve.fromGroup, strDiceTooBigErr);
				return;
			}
			else if (intRdTurnCntRes == TypeTooBig_Err) {
				sendGroupMsg(eve.fromGroup, strTypeTooBigErr);
				return;
			}
			else if (intRdTurnCntRes != 0) {
				sendGroupMsg(eve.fromGroup, "发生了未知错误!");
				return;
			}
			string strAns = strNickName + "骰出了: " + rdMainDice.FormCompleteString();
			if (!strReason.empty())strAns.insert(0, "由于" + strReason + " ");
			if (isHidden) {
				strAns.insert(0, "在群\"" + getGroupList().at(eve.fromGroup) + "\"中 ");
				sendPrivateMsg(eve.fromQQ, strAns);
				auto Range = ObserveGroup.equal_range(eve.fromGroup);
				for (auto it = Range.first; it != Range.second; ++it) {
					if (it->second != eve.fromQQ)sendPrivateMsg(it->second, strAns);
				}
			}
			else sendGroupMsg(eve.fromGroup, strAns);
		}
		if (isHidden) {
			string strReply = strNickName + "进行了一次暗骰";
			sendGroupMsg(eve.fromGroup, strReply);
		}
	}
	else {
		if (eve.message[intMsgCnt] != '.'&&eve.message != "."&&eve.message[intMsgCnt] != '!'&&eve.message != "!"&&eve.message.find("。") != intMsgCnt)sendGroupMsg(eve.fromGroup, "命令输入错误!");
	}
}
EVE_DiscussMsg_EX(__eventDiscussMsg) {
	init(eve.message);
	if (eve.message[0] != '.')return;
	int intMsgCnt = 1;
	while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
	eve.message_block();
	pair<long long, long long>pairQQDiscuss(eve.fromQQ, eve.fromDiscuss);
	string strNickName = DiscussName.count(pairQQDiscuss) ? DiscussName[pairQQDiscuss] : getStrangerInfo(eve.fromQQ).nick;
	string strLowerMessage = eve.message;
	transform(strLowerMessage.begin(), strLowerMessage.end(), strLowerMessage.begin(), tolower);
	if (strLowerMessage.find("bot") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string Command;
		while (intMsgCnt!= strLowerMessage.length()&&!isdigit(strLowerMessage[intMsgCnt]) && !isspace(strLowerMessage[intMsgCnt])) {
			Command += strLowerMessage[intMsgCnt];
			intMsgCnt++;
		}
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string QQNum = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (Command == "on") {
			if (QQNum.empty() || QQNum == to_string(getLoginQQ())) {
				if (DisabledDiscuss.count(eve.fromDiscuss)) {
					DisabledDiscuss.erase(eve.fromDiscuss);
					sendDiscussMsg(eve.fromDiscuss, "成功开启本机器人!");
				}
				else sendDiscussMsg(eve.fromDiscuss, "本机器人已经处于开启状态!");
			}
		}
		else if (Command == "off") {
			if (QQNum.empty() || QQNum == to_string(getLoginQQ())) {
				if (!DisabledDiscuss.count(eve.fromDiscuss)) {
					DisabledDiscuss.insert(eve.fromDiscuss);
					sendDiscussMsg(eve.fromDiscuss, "成功关闭本机器人!");
				}
				else sendDiscussMsg(eve.fromDiscuss, "本机器人已经处于关闭状态!");
			}
		}
		else {
			if (QQNum == "" || QQNum == to_string(getLoginQQ())) {
				if (DisabledDiscuss.count(eve.fromDiscuss)) sendDiscussMsg(eve.fromDiscuss, "机器人处于关闭状态!");
				else sendDiscussMsg(eve.fromDiscuss, "机器人处于开启状态!");
			}
		}
		return;
	}
	if (DisabledDiscuss.count(eve.fromDiscuss))return;
	if (strLowerMessage.find("help") == intMsgCnt) {
		sendDiscussMsg(eve.fromDiscuss, strHlpMsg);
	}
	else if (strLowerMessage.find("ob") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string Command = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (Command == "on") {
			if (DisabledOBDiscuss.count(eve.fromDiscuss)) {
				DisabledOBDiscuss.erase(eve.fromDiscuss);
				sendDiscussMsg(eve.fromDiscuss, "成功在本群中启用旁观模式!");
			}
			else {
				sendDiscussMsg(eve.fromDiscuss, "在本群中旁观模式没有被禁用!");
			}
			return;
		}
		else if (Command == "off") {
			if (!DisabledOBDiscuss.count(eve.fromDiscuss)) {
				DisabledOBDiscuss.insert(eve.fromDiscuss);
				ObserveDiscuss.clear();
				sendDiscussMsg(eve.fromDiscuss, "成功在本群中禁用旁观模式!");
			}
			else {
				sendDiscussMsg(eve.fromDiscuss, "在本群中旁观模式没有被启用!");
			}
			return;
		}
		if (DisabledOBDiscuss.count(eve.fromDiscuss)) {
			sendDiscussMsg(eve.fromDiscuss, "在本群中旁观模式已被禁用!");
		}
		if (Command == "list") {
			string Msg = "当前的旁观者有:";
			auto Range = ObserveDiscuss.equal_range(eve.fromDiscuss);
			for (auto it = Range.first; it != Range.second; ++it) {
				pair<long long, long long> ObDiscuss;
				ObDiscuss.first = it->second;
				ObDiscuss.second = eve.fromDiscuss;
				Msg += "\n" + (DiscussName.count(ObDiscuss) ? DiscussName[ObDiscuss] : getStrangerInfo(it->second).nick) + "(" + to_string(it->second) + ")";
			}
			string strReply = Msg == "当前的旁观者有:" ? "当前暂无旁观者" : Msg;
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
		else if (Command == "clr") {
			ObserveDiscuss.erase(eve.fromDiscuss);
			sendDiscussMsg(eve.fromDiscuss, "成功删除所有旁观者!");
		}
		else if (Command == "exit") {
			auto Range = ObserveDiscuss.equal_range(eve.fromDiscuss);
			for (auto it = Range.first; it != Range.second; ++it) {
				if (it->second == eve.fromQQ) {
					ObserveDiscuss.erase(it);
					string strReply = strNickName + "成功退出旁观模式!";
					sendDiscussMsg(eve.fromDiscuss, strReply);
					eve.message_block();
					return;
				}
			}
			string strReply = strNickName + "没有加入旁观模式!";
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
		else {
			auto Range = ObserveDiscuss.equal_range(eve.fromDiscuss);
			for (auto it = Range.first; it != Range.second; ++it) {
				if (it->second == eve.fromQQ) {
					string strReply = strNickName + "已经处于旁观模式!";
					sendDiscussMsg(eve.fromDiscuss, strReply);
					eve.message_block();
					return;
				}
			}
			ObserveDiscuss.insert(make_pair(eve.fromDiscuss, eve.fromQQ));
			string strReply = strNickName + "成功加入旁观模式!";
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
	}
	else if (strLowerMessage.find("ti") == intMsgCnt) {
		string strAns = strNickName + "的临时性疯狂:\n";
		TempInsane(strAns);
		sendDiscussMsg(eve.fromDiscuss, strAns);
	}
	else if (strLowerMessage.find("li") == intMsgCnt) {
		string strAns = strNickName + "的不定性疯狂:\n";
		LongInsane(strAns);
		sendDiscussMsg(eve.fromDiscuss, strAns);
	}
	else if (strLowerMessage.find("sc") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string SanCost = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		intMsgCnt += SanCost.length();
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string San = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (SanCost == "" || SanCost.find("/") == string::npos) {
			sendDiscussMsg(eve.fromDiscuss, strSCInvalid);
			return;
		}
		if (San == "") {
			sendDiscussMsg(eve.fromDiscuss, strSCInvalid);
			return;
		}
		RD rdTest1(SanCost.substr(0, SanCost.find("/")));
		RD rdTest2(SanCost.substr(SanCost.find("/") + 1));
		if (rdTest1.Roll() != 0 || rdTest2.Roll() != 0) {
			sendDiscussMsg(eve.fromDiscuss, strSCInvalid);
			return;
		}
		for (auto i : San)
			if (!isdigit(i)) {
				sendDiscussMsg(eve.fromDiscuss, strSanInvalid);
				return;
			}
		if (San.length() >= 3) {
			sendDiscussMsg(eve.fromDiscuss, strSanInvalid);
			return;
		}
		int intSan = Convert<int>(San);
		if (intSan == 0) {
			sendDiscussMsg(eve.fromDiscuss, strSanInvalid);
			return;
		}
		string strAns = strNickName + "的Sancheck:\n1D100=";
		RD rdD100("D100");
		rdD100.Roll();
		strAns += to_string(rdD100.intTotal);

		if (rdD100.intTotal <= intSan) {
			strAns += " 成功\n你的San值减少" + SanCost.substr(0, SanCost.find("/"));
			RD rdSan(SanCost.substr(0, SanCost.find("/")));
			rdSan.Roll();
			if (SanCost.substr(0, SanCost.find("/")).find("d") != string::npos)strAns += "=" + to_string(rdSan.intTotal);
			strAns += +"点,当前剩余" + to_string(intSan - rdSan.intTotal) + "点";
		}
		else {
			strAns += " 失败\n你的San值减少" + SanCost.substr(SanCost.find("/") + 1);
			RD rdSan(SanCost.substr(SanCost.find("/") + 1));
			rdSan.Roll();
			if (SanCost.substr(SanCost.find("/") + 1).find("d") != string::npos)strAns += "=" + to_string(rdSan.intTotal);
			strAns += +"点,当前剩余" + to_string(intSan - rdSan.intTotal) + "点";
		}
		sendDiscussMsg(eve.fromDiscuss, strAns);
	}
	else if (strLowerMessage.find("en") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strSkillName;
		while (intMsgCnt != eve.message.length()&&!isdigit(eve.message[intMsgCnt]) && !isspace(eve.message[intMsgCnt])) {
			strSkillName += eve.message[intMsgCnt];
			intMsgCnt++;
		}
		while (isspace(eve.message[intMsgCnt]))intMsgCnt++;
		string strCurrentValue;
		while (isdigit(eve.message[intMsgCnt])) {
			strCurrentValue += eve.message[intMsgCnt];
			intMsgCnt++;
		}
		if (strCurrentValue.empty()) {
			sendDiscussMsg(eve.fromDiscuss, strEnValInvalid);
			return;
		}
		if (strCurrentValue.length() >= 3) {
			sendDiscussMsg(eve.fromDiscuss, strEnValInvalid);
			return;
		}
		int intCurrentVal = Convert<int>(strCurrentValue);
		if (intCurrentVal == 0) {
			sendDiscussMsg(eve.fromDiscuss, strEnValInvalid);
			return;
		}
		string strAns = strNickName + "的" + strSkillName + "增强或成长检定:\n1D100=";
		RD rdD100("D100");
		rdD100.Roll();
		strAns += to_string(rdD100.intTotal);

		if (rdD100.intTotal <= intCurrentVal) {
			strAns += " 失败!\n你的" + (strSkillName.empty() ? "属性或技能值" : strSkillName) + "没有变化!";
		}
		else {
			strAns += " 成功!\n你的" + (strSkillName.empty() ? "属性或技能值" : strSkillName) + "增加1D10=";
			RD rdAddVal("D10");
			rdAddVal.Roll();
			strAns += to_string(rdAddVal.intTotal) + "点,当前为" + to_string(intCurrentVal + rdAddVal.intTotal) + "点";
		}
		sendDiscussMsg(eve.fromDiscuss, strAns);
	}
	else if (strLowerMessage.find("jrrp") == intMsgCnt) {
		intMsgCnt += 4;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string Command = strLowerMessage.substr(intMsgCnt, eve.message.find(' ', intMsgCnt) - intMsgCnt);
		if (Command == "on") {
			if (DisabledJRRPDiscuss.count(eve.fromDiscuss)) {
				DisabledJRRPDiscuss.erase(eve.fromDiscuss);
				sendDiscussMsg(eve.fromDiscuss, "成功在本群中启用JRRP!");
			}
			else {
				sendDiscussMsg(eve.fromDiscuss, "在本群中JRRP没有被禁用!");
			}
			return;
		}
		else if (Command == "off") {
			if (!DisabledJRRPDiscuss.count(eve.fromDiscuss)) {
				DisabledJRRPDiscuss.insert(eve.fromDiscuss);
				sendDiscussMsg(eve.fromDiscuss, "成功在本群中禁用JRRP!");
			}
			else {
				sendDiscussMsg(eve.fromDiscuss, "在本群中JRRP没有被启用!");
			}
			return;
		}
		if (DisabledJRRPDiscuss.count(eve.fromDiscuss)) {
			sendDiscussMsg(eve.fromDiscuss, "在本群中JRRP功能已被禁用");
			return;
		}
		char cstrDate[100] = {};
		time_t time_tTime = 0;
		time(&time_tTime);
		tm tmTime;
		localtime_s(&tmTime, &time_tTime);
		strftime(cstrDate, 100, "%F", &tmTime);
		if (JRRP.count(eve.fromQQ) && JRRP[eve.fromQQ].Date == cstrDate) {
			string strReply = strNickName + "今天的人品值是:" + to_string(JRRP[eve.fromQQ].RPVal);
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
		else {
			normal_distribution<double> NormalDistribution(60, 15);
			mt19937 Generator(static_cast<unsigned int> (GetCycleCount()));
			int JRRPRes;
			do {
				JRRPRes = static_cast<int> (NormalDistribution(Generator));
			} while (JRRPRes <= 0 || JRRPRes > 100);
			JRRP[eve.fromQQ].Date = cstrDate;
			JRRP[eve.fromQQ].RPVal = JRRPRes;
			string strReply(strNickName + "今天的人品值是:" + to_string(JRRP[eve.fromQQ].RPVal));
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
	}
	else if (strLowerMessage.find("nn") == intMsgCnt) {
		intMsgCnt += 2;
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
		string name = eve.message.substr(intMsgCnt);
		if (!name.empty()) {
			DiscussName[pairQQDiscuss] = name;
			string strReply = "已将" + strNickName + "的名称更改为" + name;
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
		else {
			if (DiscussName.count(pairQQDiscuss)) {
				DiscussName.erase(pairQQDiscuss);
				string strReply = "已将" + strNickName + "的名称删除";
				sendDiscussMsg(eve.fromDiscuss, strReply);
			}
			else {
				string strReply = strNickName + strNameDelErr;
				sendDiscussMsg(eve.fromDiscuss, strReply);
			}
		}
	}
	else if (strLowerMessage.find("rules") == intMsgCnt) {
		intMsgCnt += 5;
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;
		string strSearch = eve.message.substr(intMsgCnt);
		for (auto &n : strSearch)n = toupper(n);
		for (int i = 0; i != strSearch.length(); ++i)if (strSearch[i] == ' ') {
			strSearch.erase(strSearch.begin() + i);
			i--;
		}
		strSearch = "||" + strSearch + "||";
		int Loc = strRules.find(strSearch);
		if (Loc != string::npos || strSearch == "||战斗||" || strSearch == "||战斗流程||" || strSearch == "||战斗伤害||") {
			if (strSearch == "||战斗||" || strSearch == "||战斗流程||") {
				string IMAGE = "[CQ:image,file=";
				string IMAGENAME = "Combat.jpg";
				IMAGE += msg_encode(IMAGENAME, true) + "]";
				int res = sendDiscussMsg(eve.fromDiscuss, IMAGE);
				if (res < 0)sendDiscussMsg(eve.fromDiscuss, "未找到对应的规则信息!");
			}
			else if (strSearch == "||战斗伤害||") {
				string IMAGE = "[CQ:image,file=";
				string IMAGENAME = "Combat1.jpg";
				IMAGE += msg_encode(IMAGENAME, true) + "]";
				int res = sendDiscussMsg(eve.fromDiscuss, IMAGE);
				if (res < 0)sendDiscussMsg(eve.fromDiscuss, "未找到对应的规则信息!");
			}
			else {
				int LocStart = strRules.find("]", Loc) + 1;
				string strReply = strRules.substr(LocStart, strRules.find("[", LocStart) - LocStart - 1);
				sendDiscussMsg(eve.fromDiscuss, strReply);
			}
		}
		else {
			sendDiscussMsg(eve.fromDiscuss, "未找到对应的规则信息!");
		}
	}
	else if (strLowerMessage.find("me") == intMsgCnt) {
		intMsgCnt += 2;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strAction = strLowerMessage.substr(intMsgCnt);
		if (strAction == "on") {
			if (DisabledMEDiscuss.count(eve.fromDiscuss)) {
				DisabledMEDiscuss.erase(eve.fromDiscuss);
				sendDiscussMsg(eve.fromDiscuss, "成功在本群中启用.me命令!");
			}
			else {
				sendDiscussMsg(eve.fromDiscuss, "在本群中.me命令没有被禁用!");
			}
			return;
		}
		else if (strAction == "off") {
			if (!DisabledMEDiscuss.count(eve.fromDiscuss)) {
				DisabledMEDiscuss.insert(eve.fromDiscuss);
				sendDiscussMsg(eve.fromDiscuss, "成功在本群中禁用.me命令!");
			}
			else {
				sendDiscussMsg(eve.fromDiscuss, "在本群中.me命令没有被启用!");
			}
			return;
		}
		if (DisabledMEDiscuss.count(eve.fromDiscuss)) {
			sendDiscussMsg(eve.fromDiscuss, "在本群中.me命令已被禁用!");
			return;
		}
		if (strAction.empty()) {
			sendDiscussMsg(eve.fromDiscuss, "动作不能为空!");
			return;
		}
		if (DisabledMEDiscuss.count(eve.fromDiscuss)) {
			sendDiscussMsg(eve.fromDiscuss, strMEDisabledErr);
			return;
		}
		string strReply = strNickName + strAction;
		sendDiscussMsg(eve.fromDiscuss, strReply);
	}
	else if (strLowerMessage.find("set") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strDefaultDice = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strDefaultDice[0] == '0')strDefaultDice.erase(strDefaultDice.begin());
		if (strDefaultDice.empty())strDefaultDice = "100";
		for (auto charNumElement : strDefaultDice)
			if (!isdigit(charNumElement)) {
				sendDiscussMsg(eve.fromDiscuss, strSetInvalid);
				return;
			}
		if (strDefaultDice.length() > 5) {
			sendDiscussMsg(eve.fromDiscuss, strSetTooBig);
			return;
		}
		int intDefaultDice = Convert<int>(strDefaultDice);
		if (intDefaultDice == 100)DefaultDice.erase(eve.fromQQ);
		else DefaultDice[eve.fromQQ] = intDefaultDice;
		string strSetSuccessReply = "已将" + strNickName + "的默认骰类型更改为D" + strDefaultDice;
		sendDiscussMsg(eve.fromDiscuss, strSetSuccessReply);
	}
	else if (strLowerMessage.find("coc6d") == intMsgCnt) {
		string strReply = strNickName;
		COC6D(strReply);
		sendDiscussMsg(eve.fromDiscuss, strReply);
	}
	else if (strLowerMessage.find("coc6") == intMsgCnt) {
		intMsgCnt += 4;
		if (strLowerMessage[intMsgCnt] == 's')intMsgCnt++;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendDiscussMsg(eve.fromDiscuss, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		COC6(strReply, intNum);
		sendDiscussMsg(eve.fromDiscuss, strReply);
	}
	else if (strLowerMessage.find("dnd") == intMsgCnt) {
		intMsgCnt += 3;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendDiscussMsg(eve.fromDiscuss, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		DND(strReply, intNum);
		sendDiscussMsg(eve.fromDiscuss, strReply);
	}
	else if (strLowerMessage.find("coc7d") == intMsgCnt || strLowerMessage.find("cocd") == intMsgCnt) {
		string strReply = strNickName;
		COC7D(strReply);
		sendDiscussMsg(eve.fromDiscuss, strReply);
	}
	else if (strLowerMessage.find("coc") == intMsgCnt) {
		intMsgCnt += 3;
		if (strLowerMessage[intMsgCnt] == '7')intMsgCnt++;
		if (strLowerMessage[intMsgCnt] == 's')intMsgCnt++;
		while (strLowerMessage[intMsgCnt] == ' ')intMsgCnt++;
		string strNum = strLowerMessage.substr(intMsgCnt, strLowerMessage.find(" ", intMsgCnt) - intMsgCnt);
		while (strNum[0] == '0')strNum.erase(strNum.begin());
		for (auto i : strNum)
			if (!isdigit(i)) {
				sendDiscussMsg(eve.fromDiscuss, strCharacterInvalid);
				return;
			}
		if (strNum.length() > 2) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterTooBig);
			return;
		}
		int intNum = Convert<int>(strNum);
		if (strNum.empty())intNum = 1;
		if (intNum > 10) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterTooBig);
			return;
		}
		if (intNum == 0) {
			sendDiscussMsg(eve.fromDiscuss, strCharacterCannotBeZero);
			return;
		}
		string strReply = strNickName;
		COC7(strReply, intNum);
		sendDiscussMsg(eve.fromDiscuss, strReply);
	}
	else if (strLowerMessage[intMsgCnt] == 'r' || strLowerMessage[intMsgCnt] == 'o' || strLowerMessage[intMsgCnt] == 'h' || strLowerMessage[intMsgCnt] == 'd') {
		bool isHidden = false;
		if (strLowerMessage[intMsgCnt] == 'h')isHidden = true;
		intMsgCnt += 1;
		if (strLowerMessage[intMsgCnt] == 'h') {
			isHidden = true;
			intMsgCnt += 1;
		}
		while (eve.message[intMsgCnt] == ' ')intMsgCnt++;

		string strMainDice;
		string strReason;

		bool tmpContainD = false;
		int intTmpMsgCnt;
		for (intTmpMsgCnt = intMsgCnt; intTmpMsgCnt != eve.message.length() && eve.message[intTmpMsgCnt] != ' '; intTmpMsgCnt++) {
			if (strLowerMessage[intTmpMsgCnt] == 'd' || strLowerMessage[intTmpMsgCnt] == 'p' || strLowerMessage[intTmpMsgCnt] == 'b' || strLowerMessage[intTmpMsgCnt] == '#')tmpContainD = true;
			if (!isdigit(strLowerMessage[intTmpMsgCnt]) && strLowerMessage[intTmpMsgCnt] != 'd' &&strLowerMessage[intTmpMsgCnt] != 'k'&&strLowerMessage[intTmpMsgCnt] != 'p'&&strLowerMessage[intTmpMsgCnt] != 'b'&& strLowerMessage[intTmpMsgCnt] != '+'&&strLowerMessage[intTmpMsgCnt] != '-' && strLowerMessage[intTmpMsgCnt] != '#') {
				break;
			}
		}
		if (tmpContainD) {
			strMainDice = strLowerMessage.substr(intMsgCnt, intTmpMsgCnt - intMsgCnt);
			while (eve.message[intTmpMsgCnt] == ' ')intTmpMsgCnt++;
			strReason = eve.message.substr(intTmpMsgCnt);
		}
		else strReason = eve.message.substr(intMsgCnt);
		int intTurnCnt = 1;
		if (strMainDice.find("#") != string::npos) {
			string strTurnCnt = strMainDice.substr(0, strMainDice.find("#"));
			strMainDice = strMainDice.substr(strMainDice.find("#") + 1);
			RD rdTurnCnt(strTurnCnt, eve.fromQQ);
			int intRdTurnCntRes = rdTurnCnt.Roll();
			if (intRdTurnCntRes == Value_Err) {
				sendDiscussMsg(eve.fromDiscuss, strValueErr);
				return;
			}
			else if (intRdTurnCntRes == Input_Err) {
				sendDiscussMsg(eve.fromDiscuss, strInputErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroDice_Err) {
				sendDiscussMsg(eve.fromDiscuss, strZeroDiceErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroType_Err) {
				sendDiscussMsg(eve.fromDiscuss, strZeroTypeErr);
				return;
			}
			else if (intRdTurnCntRes == DiceTooBig_Err) {
				sendDiscussMsg(eve.fromDiscuss, strDiceTooBigErr);
				return;
			}
			else if (intRdTurnCntRes == TypeTooBig_Err) {
				sendDiscussMsg(eve.fromDiscuss, strTypeTooBigErr);
				return;
			}
			else if (intRdTurnCntRes != 0) {
				sendDiscussMsg(eve.fromDiscuss, "发生了未知错误!");
				return;
			}
			if (rdTurnCnt.intTotal > 10) {
				sendDiscussMsg(eve.fromDiscuss, "掷骰轮数超过了最大限制10次!");
				return;
			}
			else if (rdTurnCnt.intTotal <= 0) {
				sendDiscussMsg(eve.fromDiscuss, "异常的掷骰轮数");
				return;
			}
			intTurnCnt = rdTurnCnt.intTotal;
			if (strTurnCnt.find("d") != string::npos) {
				string strTurnNotice = strNickName + "的掷骰轮数: " + rdTurnCnt.FormCompleteString() + "轮";
				if (isHidden) {
					strTurnNotice.insert(0, "在多人聊天中 ");
					sendPrivateMsg(eve.fromQQ, strTurnNotice);
					auto Range = ObserveDiscuss.equal_range(eve.fromDiscuss);
					for (auto it = Range.first; it != Range.second; ++it) {
						if (it->second != eve.fromQQ)sendPrivateMsg(it->second, strTurnNotice);
					}
				}
				else sendDiscussMsg(eve.fromDiscuss, strTurnNotice);
			}
		}

		RD rdMainDice(strMainDice, eve.fromQQ);
		while (intTurnCnt--) {
			int intRdTurnCntRes = rdMainDice.Roll();
			if (intRdTurnCntRes == Value_Err) {
				sendDiscussMsg(eve.fromDiscuss, strValueErr);
				return;
			}
			else if (intRdTurnCntRes == Input_Err) {
				sendDiscussMsg(eve.fromDiscuss, strInputErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroDice_Err) {
				sendDiscussMsg(eve.fromDiscuss, strZeroDiceErr);
				return;
			}
			else if (intRdTurnCntRes == ZeroType_Err) {
				sendDiscussMsg(eve.fromDiscuss, strZeroTypeErr);
				return;
			}
			else if (intRdTurnCntRes == DiceTooBig_Err) {
				sendDiscussMsg(eve.fromDiscuss, strDiceTooBigErr);
				return;
			}
			else if (intRdTurnCntRes == TypeTooBig_Err) {
				sendDiscussMsg(eve.fromDiscuss, strTypeTooBigErr);
				return;
			}
			else if (intRdTurnCntRes != 0) {
				sendDiscussMsg(eve.fromDiscuss, "发生了未知错误!");
				return;
			}
			string strAns = strNickName + "骰出了: " + rdMainDice.FormCompleteString();
			if (!strReason.empty())strAns.insert(0, "由于" + strReason + " ");
			if (isHidden) {
				strAns.insert(0, "在多人聊天中 ");
				sendPrivateMsg(eve.fromQQ, strAns);
				auto Range = ObserveDiscuss.equal_range(eve.fromDiscuss);
				for (auto it = Range.first; it != Range.second; ++it) {
					if (it->second != eve.fromQQ)sendPrivateMsg(it->second, strAns);
				}
			}
			else sendDiscussMsg(eve.fromDiscuss, strAns);
		}
		if (isHidden) {
			string strReply = strNickName + "进行了一次暗骰";
			sendDiscussMsg(eve.fromDiscuss, strReply);
		}
	}
	else {
		if (eve.message[intMsgCnt] != '.'&&eve.message != "."&&eve.message[intMsgCnt] != '!'&&eve.message != "!"&&eve.message.find("。") != intMsgCnt)sendDiscussMsg(eve.fromDiscuss, "命令输入错误!");
	}
}
EVE_Exit(__eventExit) {
	ofstream ofstreamGroupName(strFileLoc + "GroupName.RDconf", ios::in | ios::trunc);
	for (auto it = GroupName.begin(); it != GroupName.end(); it++) {
		if (!(it->second).empty())
			ofstreamGroupName << it->first.first << " " << it->first.second << " " << it->second << endl;
	}
	ofstreamGroupName.close();
	ofstream ofstreamDiscussName(strFileLoc + "DiscussName.RDconf", ios::in | ios::trunc);
	for (auto it = DiscussName.begin(); it != DiscussName.end(); it++) {
		if (!(it->second).empty())
			ofstreamDiscussName << it->first.first << " " << it->first.second << " " << it->second << endl;
	}
	ofstreamDiscussName.close();

	ofstream ofstreamDisabledGroup(strFileLoc + "DisabledGroup.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledGroup.begin(); it != DisabledGroup.end(); it++) {
		ofstreamDisabledGroup << *it << endl;
	}
	ofstreamDisabledGroup.close();

	ofstream ofstreamDisabledDiscuss(strFileLoc + "DisabledDiscuss.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledDiscuss.begin(); it != DisabledDiscuss.end(); it++) {
		ofstreamDisabledDiscuss << *it << endl;
	}
	ofstreamDisabledDiscuss.close();
	ofstream ofstreamDisabledJRRPGroup(strFileLoc + "DisabledJRRPGroup.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledJRRPGroup.begin(); it != DisabledJRRPGroup.end(); it++) {
		ofstreamDisabledJRRPGroup << *it << endl;
	}
	ofstreamDisabledJRRPGroup.close();

	ofstream ofstreamDisabledJRRPDiscuss(strFileLoc + "DisabledJRRPDiscuss.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledJRRPDiscuss.begin(); it != DisabledJRRPDiscuss.end(); it++) {
		ofstreamDisabledJRRPDiscuss << *it << endl;
	}
	ofstreamDisabledJRRPDiscuss.close();

	ofstream ofstreamDisabledMEGroup(strFileLoc + "DisabledMEGroup.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledMEGroup.begin(); it != DisabledMEGroup.end(); it++) {
		ofstreamDisabledMEGroup << *it << endl;
	}
	ofstreamDisabledMEGroup.close();

	ofstream ofstreamDisabledMEDiscuss(strFileLoc + "DisabledMEDiscuss.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledMEDiscuss.begin(); it != DisabledMEDiscuss.end(); it++) {
		ofstreamDisabledMEDiscuss << *it << endl;
	}
	ofstreamDisabledMEDiscuss.close();

	ofstream ofstreamDisabledOBGroup(strFileLoc + "DisabledOBGroup.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledOBGroup.begin(); it != DisabledOBGroup.end(); it++) {
		ofstreamDisabledOBGroup << *it << endl;
	}
	ofstreamDisabledOBGroup.close();

	ofstream ofstreamDisabledOBDiscuss(strFileLoc + "DisabledOBDiscuss.RDconf", ios::in | ios::trunc);
	for (auto it = DisabledOBDiscuss.begin(); it != DisabledOBDiscuss.end(); it++) {
		ofstreamDisabledOBDiscuss << *it << endl;
	}
	ofstreamDisabledOBDiscuss.close();

	ofstream ofstreamObserveGroup(strFileLoc + "ObserveGroup.RDconf", ios::in | ios::trunc);
	for (auto it = ObserveGroup.begin(); it != ObserveGroup.end(); it++) {
		ofstreamObserveGroup << it->first << " " << it->second << endl;
	}
	ofstreamObserveGroup.close();

	ofstream ofstreamObserveDiscuss(strFileLoc + "ObserveDiscuss.RDconf", ios::in | ios::trunc);
	for (auto it = ObserveDiscuss.begin(); it != ObserveDiscuss.end(); it++) {
		ofstreamObserveDiscuss << it->first << " " << it->second << endl;
	}
	ofstreamObserveDiscuss.close();
	ofstream ofstreamJRRP(strFileLoc + "JRRP.RDconf", ios::in | ios::trunc);
	for (auto it = JRRP.begin(); it != JRRP.end(); it++) {
		ofstreamJRRP << it->first << " " << it->second.Date << " " << it->second.RPVal << endl;
	}
	ofstreamJRRP.close();

	ofstream ofstreamDefault(strFileLoc + "Default.RDconf", ios::in | ios::trunc);
	for (auto it = DefaultDice.begin(); it != DefaultDice.end(); it++) {
		ofstreamDefault << it->first << " " << it->second << endl;
	}
	ofstreamDefault.close();
	return 0;
}
MUST_AppInfo_RETURN(CQAPPID);