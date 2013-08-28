#include <iostream>
#include <string>

using namespace std;

class CompanyA {
public:
	void sendCleartext(const string& msg) { cout << "Company A send clear text: " << msg << endl; }
	void sendEncypted(const string& msg) { cout << "Company A send encrypted text: " << msg << endl; }
};

class CompanyB {
public:
	void sendCleartext(const string& msg) { cout << "Company B send clear text: " << msg << endl; }
	void sendEncypted(const string& msg) { cout << "Company B send encrypted text: " << msg << endl; }
};

class CompanyZ {
public:
	void sendEncypted(const string& msg) { cout << "Company Z send encrypted text: " << msg << endl; }
};

class MsgInfo {
public:
	MsgInfo() {}
	MsgInfo(const string& msg) : msg(msg) {}
	string getMsg() const { return msg; }
private:
	string msg;
};

template <typename Company>
class MsgSender {
public:
	void sendClear(const MsgInfo& info) {
		string msg = info.getMsg();
		Company c;
		c.sendCleartext(msg);
	}
	void sendSecret(const MsgInfo& info) {
		string msg = info.getMsg();
		Company c;
		c.sendEncypted(msg);
	}
};

/*template<>
class MsgSender<CompanyZ> {
public:
	void sendSecret(const MsgInfo& info) { 
		string msg = info.getMsg();
		CompanyZ cz;
		cz.sendEncypted(msg);
	}
};*/

template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info) {
		sendClear(info);
	}
};

int main() {
	MsgSender<CompanyA> *msa = new MsgSender<CompanyA>();
	MsgSender<CompanyB> *msb = new MsgSender<CompanyB>();
	MsgInfo info("a message");
	msa->sendClear(info);
	msb->sendSecret(info);
	LoggingMsgSender<CompanyA> * lms = new LoggingMsgSender<CompanyA>();
	lms->sendClearMsg(info);
}