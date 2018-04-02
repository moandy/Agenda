#include<iostream>
#include<iomanip>
#include"AgendaUI.hpp"
using namespace std;
AgendaUI::AgendaUI() {
	startAgenda();
}

void AgendaUI::OperationLoop(void) {
	bool test = true;
	string ss;
	while (test) {
		ss = getOperation();
		test = executeOperation(ss);
	}
}
void nonlogprint() {
	cout << "----------------------- Agenda -----------------------" << endl;
	cout << "Action : " << endl;
	cout << "l   - log in Agenda by user name and password" << endl;
	cout << "r   - register an Agenda account" << endl;
	cout << "q   - quit Agenda" << endl;
	cout << "------------------------------------------------------" << endl << endl;
	cout << "Agenda : ~$ ";
}
void logedprint(string m_userName) {
	cout << endl;
	cout << "----------------------- Agenda -----------------------" << endl;
	cout << "o   - log out Agenda" << endl;
	cout << "dc  - delete Agenda account" << endl;
	cout << "lu  - list all Agenda user" << endl;
	cout << "cm  - creat a meeting" << endl;
	cout << "la  - list all meetings" << endl;
	cout << "las - list all sponsor meetings" << endl;
	cout << "lap - list all participate meetings" << endl;
	cout << "qm  - query meeting by title" << endl;
	cout << "qt  - query meeting by time interval" << endl;
	cout << "dm  - delete meeting by title" << endl;
	cout << "da  - delete all meeting" << endl;
	cout << "------------------------------------------------------" << endl << endl;
	cout << "Agenda@" << m_userName << " : #";
}
void AgendaUI::startAgenda(void) {
	m_userName.clear();
	m_userPassword.clear();
}
std::string AgendaUI::getOperation() { //////////////////////////////////there is some question
	string ss;
	bool test = true;
	while (test) {                          ///yiwen??
		if (m_userName.empty()) {
			nonlogprint();
		} else {
			logedprint(m_userName);
		}
		cin >> ss; 
		if (m_userName.empty()) {
			if (ss == "l"||ss == "r"||ss == "q")
				test = false;
		} else {
			if (ss == "o"||ss == "dc"||ss == "lu"||ss == "cm"||ss == "la"
				||ss == "las"||ss == "lap"||ss == "qm"||ss == "qt"|| ss == "dm"||ss == "da") {
				test = false;
			}
		}
	}
	return ss;
}
bool AgendaUI::executeOperation(std::string t_operation) {
	if (t_operation == "l") {
		userLogIn();
		return true;
	} else if (t_operation == "r") {
		userRegister();
		return true;
	} else if (t_operation == "q") {
		quitAgenda();
		return false;
	} else if (t_operation == "o") {
		userLogOut();
		return true;
	} else if (t_operation == "dc") {
		deleteUser();
		return true;
	} else if (t_operation == "lu") {
		listAllUsers();
		return true;
	} else if (t_operation == "cm") {
		createMeeting();
		return true;
	} else if (t_operation == "la") {
		listAllMeetings();
		return true;
	} else if (t_operation == "las") {
		listAllSponsorMeetings();
		return true;
	} else if (t_operation == "lap") {
		listAllParticipateMeetings();
		return true;
	} else if (t_operation == "qm") {
		queryMeetingByTitle();
		return true;
	} else if (t_operation == "qt") {
		queryMeetingByTimeInterval();
		return true;
	} else if (t_operation == "dm") {
		deleteMeetingByTitle();
		return true;
	} else if (t_operation == "da") {
		deleteAllMeetings();
		return true;
	}
}
void AgendaUI::userLogIn(void) {
	cout << "[log in] [user name] [password]" << endl;
	cout << "[log in] ";
	string name, ps;
	cin >> name >> ps;
	if (m_agendaService.userLogIn(name, ps)) {
		cout << "[log in] succeed!" << endl;
		m_userName = name;
		m_userPassword = ps;
	} else {
		cout << "[error] log in fail!" << endl;
	}
}
void AgendaUI::userRegister(void) {
	cout << "[register] [user name] [password] [email] [phone]" << endl;
	cout << "[register] ";
	string name, password, email, phone;
	cin >> name >> password >> email >> phone;
	if (m_agendaService.userRegister(name, password, email, phone)) {
		cout << "[register] succeed!" << endl;
	} else {
		cout << "[error] register fail" << endl;
	}
}
void AgendaUI::userLogOut(void) {
	quitAgenda();
	startAgenda();
}
void AgendaUI::quitAgenda(void) {
	m_agendaService.quitAgenda();
	m_userName.clear();
	m_userPassword.clear();
}
void AgendaUI::deleteUser(void) {
	m_agendaService.deleteUser(m_userName, m_userPassword);
	cout << "[delete agenda account] succeed!" << endl;
	userLogOut();
}
void AgendaUI::listAllUsers(void) {
	cout << "[list all users]" << endl << endl;
	cout << "name      email               phone" << endl;
	list<User> temp = m_agendaService.listAllUsers();
	for (auto iter = temp.begin(); iter != temp.end(); iter++) {
		cout << setw(10) << left << iter->getName() << setw(20) << left << iter->getEmail() << iter->getPhone() << endl;
	}
}
void AgendaUI::createMeeting(void) {
	cout << "[create Meeting] [the number of participators]" << endl;
	cout << "[create Meeting] ";
	int num;
	cin >> num;
	vector<string> participators;
	for (int i = 1; i <= num; ++i) {
		string ss;
		cout << "[create Meeting] [please enter the participators " << i << " ]" << endl;
		cout << "[create Meeting] ";
		cin >> ss;
		participators.push_back(ss);
	}
	cout << "[create Meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[create Meeting] ";
	string title, starttime, endtime;
	cin >> title >> starttime >> endtime;
	if (m_agendaService.createMeeting(m_userName, title, starttime, endtime, participators)) {
		cout << "[create Meeting] succeed!" << endl;
	} else {
		cout << "[create Meeting] error!" << endl;
	}
}
void AgendaUI::listAllMeetings(void) {
	cout << "[list all meetings]" << endl << endl;
	list<Meeting> temp = m_agendaService.listAllMeetings(m_userName);
	printMeetings(temp);
}
void AgendaUI::listAllSponsorMeetings(void) {
	cout << "[list all sponsor meetings]" << endl << endl;
	list<Meeting> temp = m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(temp);
}
void AgendaUI::listAllParticipateMeetings(void) {
	cout << "[list all participate meetings]" << endl << endl;
	list<Meeting> temp = m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(temp);

}
void AgendaUI::queryMeetingByTitle(void) {
	cout << "[query meeting] [title]:" << endl;
	cout << "[query meeting] ";
	string title;
	cin >> title;
	list<Meeting> temp = m_agendaService.meetingQuery(m_userName, title);
	printMeetings(temp);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
	cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[query meetings] ";
	string starttime, endtime;
	cin >> starttime >> endtime;
	list<Meeting> temp = m_agendaService.meetingQuery(m_userName, starttime, endtime);
	printMeetings(temp);
}
void AgendaUI::deleteMeetingByTitle(void) {
	cout << "[delete meeting] [title]" << endl;
	cout << "[delete meeting] ";
	string title;
	cin >> title;
	cout << endl;
	if (m_agendaService.deleteMeeting(m_userName, title)) {
		cout << "[delete meeting by title] succeed!" << endl;
	} else {
		cout << "[error] delete meeting fail!" << endl;
	}
}
void AgendaUI::deleteAllMeetings(void) {
	m_agendaService.deleteAllMeetings(m_userName);
	cout << "[delete all meetings] succeed!" << endl;
}
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
	cout << "title               sponsor             start time          end time           participator" << endl;
	for (auto iter = t_meetings.begin(); iter != t_meetings.end(); iter++) {
		string ss;
		ss = iter->getParticipator()[0];
		if (iter->getParticipator().size() == 0) {

		} else {
			for (int i = 1; i < iter->getParticipator().size(); ++i) {
				ss += "," + iter->getParticipator()[i];
			}
		}
		cout << left << setw(20) << iter->getTitle() << setw(20) << left << iter->getSponsor()
			 << left << setw(20)  << Date::dateToString(iter->getStartDate())
			 << left << setw(20) << Date::dateToString(iter->getEndDate()) << ss << endl;
	}
}
