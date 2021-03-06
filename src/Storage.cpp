#include<iostream>
#include"Storage.hpp"
#include"Path.hpp"
#include"Meeting.hpp"
#include"User.hpp"
#include<fstream>
#include<functional>
#include<list>
using namespace std;
std::shared_ptr<Storage> Storage::m_instance = NULL;
Storage::Storage() {
	m_userList.clear();
	m_meetingList.clear();
	m_dirty = 0;
	readFromFile();
}
bool Storage::readFromFile(void) {
	string a[1000], b[1000];
	ifstream file;
	int n = 0, m = 0;
	file.open(Path::userPath);
	if (!file)
		return false;
	while (getline(file, a[n++])) {
		string name = "", password = "", email = "", phone = "";
		int i = 1;
		for (int j = i; j < a[n-1].length(); ++j) {
			if (a[n - 1][j] == '\"') {
				break;
			} else {
				name += a[n-1][j];
			}
		}
		i += name.length() + 3;
		for (int j = i; j < a[n-1].length(); ++j) {
			if (a[n - 1][j] == '\"') {
				break;
			} else {
				password += a[n-1][j];
			}
		}
		i += password.length() + 3;
		for (int j = i; j < a[n-1].length(); ++j) {
			if (a[n - 1][j] == '\"') {
				break;
			} else {
				email += a[n-1][j];
			}
		}
		i += email.length() + 3;
		for (int j = i; j < a[n-1].length(); ++j) {
			if (a[n - 1][j] == '\"') {
				break;
			} else {
				phone += a[n-1][j];
			}
		}
		User u = User(name, password, email, phone);
		createUser(u);
	}
	file.close();
	file.open(Path::meetingPath);
	if (!file) {
		return false;
	}
	while (getline(file, b[m++])) {
		string sponsor = "", participator = "", startdate = "", enddate = "", title = "";
		int i = 1;
		for (int j = i; j < b[m -1].length(); ++j) {
			if (b[m - 1][j] == '\"') {
				break;
			} else {
				sponsor += b[m - 1][j];
			}
		}
		i += sponsor.length() + 3;
		for (int j = i; j < b[m -1].length(); ++j) {
			if (b[m - 1][j] == '\"') {
				break;
			} else {
				participator += b[m - 1][j];
			}
		}
		i += participator.length() + 3;
		for (int j = i; j < b[m -1].length(); ++j) {
			if (b[m - 1][j] == '\"')
				break;
			else
				startdate += b[m - 1][j];
		}
		i += startdate.length() + 3;
		for (int j = i; j < b[m -1].length(); ++j) {
			if (b[m - 1][j] == '\"')
				break;
			else
				enddate += b[m - 1][j];
		}
		i += enddate.length() + 3;
		for (int j = i; j < b[m -1].length(); ++j) {
			if (b[m - 1][j] == '\"')
				break;
			else;
				title += b[m - 1][j];
		}
		vector<string> temp;
		int count = 0;
		string a = "";
		for (int i = 0; i < participator.length(); ++i) {
			if (participator[i] == '&')
				count++;
		}
		if (count == 0) {
			temp.push_back(participator);
		} else {
			for (int i = 0; i < count; ++i) {
				if (participator[i] == '&') {
					temp.push_back(a);
					a = "";
					continue;
				} else {
					a += participator[i];
				}
			}
			temp.push_back(a);
		}
		Date s = Date::dateToString(startdate);
		Date e = Date::dateToString(enddate);
		createMeeting(Meeting(sponsor, temp, s, e, title));
	}
	file.close();
	return true;
}
bool Storage::writeToFile(void) {
	ofstream file;
	file.open(Path::userPath);
	if (!file) {
		return false;
	}
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		file << '"' << iter->getName() << '"' << ","
			 << '"' << iter->getPassword() << '"' << ","
			 << '"' << iter->getEmail() << '"' << ","
			 << '"' << iter->getPhone() << '"' << endl;
	}
	file.close();
	file.open(Path::meetingPath);
	if (!file) {
		return false;
	}
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		string p = "";
		int num = (iter->getParticipator()).size();
		if (num == 1) {
			p = (iter->getParticipator())[0];
		} else {
				p = (iter->getParticipator())[0];
			for (int i = 1; i < num; i++) {
				p += "&" + (iter->getParticipator())[i];
			}
		}
		file << '"' << iter->getSponsor() << '"' << ","
			 << '"' << p << '"' << ","
			 << '"' << Date::dateToString(iter->getStartDate()) << '"' << ","
			 << '"' << Date::dateToString(iter->getEndDate()) << '"' << ","
			 << '"' << iter->getTitle() << '"' << endl;
	}
	file.close();
	return true;
}
shared_ptr<Storage> Storage::getInstance(void) {
	if (m_instance == NULL) {
		m_instance = std::shared_ptr<Storage>(new Storage);
	}
	return m_instance;
}
Storage::~Storage() {
	m_dirty = 0;
	writeToFile();
}
void Storage:: createUser(const User & t_user) {
	m_userList.push_back(t_user);
	
	m_dirty = 1;
}
list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
	list<User> temp;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			temp.push_back(*iter);
		}
	}
	return temp;
}
int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
	int num = 0;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			switcher(*iter);
			num++;
		}
	}
	
	return num;
}
int Storage::deleteUser(std::function<bool(const User &)> filter) {
	int num = 0;
	for (auto iter = m_userList.begin(); iter !=m_userList.end(); ) {
		if (filter(*iter)) {
			iter = m_userList.erase(iter);
			num++;
		} else {
			iter++;
		}
	}
	m_dirty = true;
	
	return num;
}
void Storage::createMeeting(const Meeting & t_meeting) {
	m_meetingList.push_back(t_meeting);
	
	m_dirty = 1;
}
list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
	list<Meeting> temp;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			temp.push_back(*iter);
		}
	}
	return temp;
}
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	int num = 0;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			switcher(*iter);
			num++;
		}
	}
	
	return num;
}
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	int num = 0;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end();) {
		if (filter(*iter)) {
			iter = m_meetingList.erase(iter);
			num++;
		} else {
			iter++;
		}
	}
	m_dirty = true;
	return num;
}
bool Storage::sync(void) {
	return writeToFile();
}

