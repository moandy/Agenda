#include <iostream>
#include "AgendaService.hpp"
#include <list>
#include <string>
using namespace std;
AgendaService::AgendaService() {
	startAgenda();
}
AgendaService::~AgendaService() {
	quitAgenda();
}
bool AgendaService::userLogIn(const std::string userName, const std::string password) {
	std::function<bool(const User &user)> test = [userName, password] (const User &user) {
		if (user.getName() == userName)
			if (user.getPassword() == password)
				return true;
		return false;
	};
	list<User> temp = m_storage->queryUser(test);
	if (temp.size() == 0)
		return false;
	return true;
}
bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
	std::function<bool(const User &user)> test = [userName] (const User &user) {
		if (user.getName() == userName)
			return true;
		return false;
	};
	list<User> temp = m_storage->queryUser(test);
	if (temp.size() == 0) {
		User newuser(userName, password, email, phone);
		m_storage->createUser(newuser);
		return true;
	} else {
		return false;
	}
}
bool AgendaService::deleteUser(const std::string userName, const std::string password) {
	std::function<bool(const User &user)> test = [userName, password] (const User &user) {
		if (user.getName() == userName)
			if (user.getPassword() == password)
				return true;
		return false;
	};
	list<User> temp = m_storage->queryUser(test);
	if (temp.size() == 0) {
		return false;
	} else {
		std::function<bool(const User &user)> test1 = [userName, password] (const User &user) {
		if (user.getName() == userName)
			if (user.getPassword() == password)
				return true;
		return false;
		};
		m_storage->deleteUser(test1);
		std::function<bool(const Meeting &meeting)> test2 = [userName] (const Meeting &meeting) {
			if (meeting.getSponsor() == userName)
				return true;
			return false;
		};
		m_storage->deleteMeeting(test2);
		return true;
	}
}
std::list<User> AgendaService::listAllUsers(void) const {
	std::function<bool(const User &user)> test = [] (const User &user) {
		return true;
	};
	list<User> temp = m_storage->queryUser(test);
	return temp;
}
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
	/*Date sdate = Date::stringToDate(startDate);
	Date edate = Date::stringToDate(endDate);
	std::function<bool(const User &user)> test = [userName, participator] (const User &user) {
		if (user.getName() == userName)
			return true;
		for (auto iter = participator.begin(); iter != participator.end(); iter++) {
			if (userName == *iter)
				return true;
		}
		return false;
	};
	list<User> temp = m_storage->queryUser(test);
	if (temp.size() >= 2) {
		std::function<bool(const Meeting &meeting)> test1 = [title] (const Meeting &meeting) {
			if (title == meeting.getTitle())
				return true;
			return false;
		};
		list<Meeting> temp1 = m_storage->queryMeeting(test1);
		if (temp1.size() == 0) {
			list<Meeting> m = meetingQuery(userName, startDate, endDate);
			if (m.size() == 0) {
				for (auto iter = participator.begin(); iter != participator.end(); iter++) {
					list<Meeting> m1 = meetingQuery(*iter, startDate, endDate);
					if (m1.size() != 0)
						return false;
				}
				if (Date::isValid(sdate)&&Date::isValid(edate)) {
					if (sdate < edate) {
						m_storage->createMeeting(Meeting(userName, participator, startDate, endDate, title));
						return true;
					}
				}
			}
		}
	}
	return false;*/
	/*Date sdate = Date::stringToDate(startDate);
	Date edate = Date::stringToDate(endDate);
	if (!Date::isValid(sdate)||!Date::isValid(edate)) {
		return false;
	}
	if (sdate >= edate)
		return false;
	vector<string> temp = participator;
	temp.push_back(userName);
	list<User> temp1 = listAllUsers();
	int t = 0;
	for (auto iter = temp1.begin(); iter != temp1.end(); iter++) {
		for (int i = 0;i < temp.size(); i++) {
			if (iter->getName() == temp[i]) {
				t++;
				break;2
			}
		}
	}
	if (t < temp.size()) {
		return false;
	}
	for (int i = 0; i < temp.size(); ++i) {
		list<Meeting> m = meetingQuery(temp[i], startDate, endDate);
		if (m.size() != 0)
			return false;
	}
	m_storage->createMeeting(Meeting(userName, participator, startDate, endDate, title));
	return true;*/
	Date sdate = Date::stringToDate(startDate);
	Date edate = Date::stringToDate(endDate);
	if (!Date::isValid(sdate)||!Date::isValid(edate)) {
		return false;
	}
	if (sdate >= edate)
		return false;
	int spo = 0, par = 0;
	function<bool(const User& a)> test = [&] (const User& a) {
		if (a.getName() == userName)
			return true;
		for (auto it = participator.begin(); it != participator.end(); it++) {
			if (a.getName() == *it)
				return true;
		}
		return false;
	};
	list<Meeting> temp = meetingQuery(userName, startDate, endDate);
	if (temp.size() >= 1)
		return false;
	for (auto it = participator.begin(); it != participator.end(); it++) {
		list<Meeting> temp1 = meetingQuery(*it, startDate, endDate);
		if (temp1.size() >= 1)
			return false;
	}
	function<bool(const Meeting &a)> test1 = [&] (const Meeting &a) {
		if (a.getTitle() == title) {
			return true;
		} else {
			return false;
		}
	};
	list<Meeting> temp2 = m_storage->queryMeeting(test1);
	if (temp2.size() >= 1)
		return false;
	list<User> temp3 = m_storage->queryUser(test);
	if (temp3.size() == 1 + participator.size()) {
		Meeting meeting(userName, participator, sdate, edate, title);
		m_storage->createMeeting(meeting);
		return true;
	} else {
		return false;
	}
}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
	std::function<bool(const Meeting &meeting)> test = [userName, title] (const Meeting &meeting) {
		if (meeting.getSponsor() == userName&&meeting.getTitle() == title)
			return true;
		/*for (auto iter = meeting.getParticipator().begin(); iter != meeting.getParticipator().end(); iter++) {
			if (userName == *iter&&meeting.getTitle() == title)
				return true;
		}*/
		for (int i = 0; i < meeting.getParticipator().size(); i++) {
			if (userName == meeting.getParticipator()[i]&&title == meeting.getTitle())
				return true;
		}
		return false;
	};
	list<Meeting> temp = m_storage->queryMeeting(test);
	return temp;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
	Date sdate = Date::stringToDate(startDate);
	Date edate = Date::stringToDate(endDate);
	std::function<bool(const Meeting &meeting)> test = [userName, sdate, edate] (const Meeting &meeting) {
		if (meeting.getSponsor() == userName) {
			if ((meeting.getStartDate() <= sdate&&meeting.getEndDate() >= edate)
				||(meeting.getStartDate() <= sdate&&meeting.getStartDate() > edate)
				||(meeting.getEndDate() < sdate&&meeting.getEndDate() >= edate))
				return true;
		}
		/*for (auto iter = meeting.getParticipator().begin(); iter != meeting.getParticipator().end(); iter++) {
			if (userName == *iter)
				if ((meeting.getStartDate() <= sdate&&meeting.getEndDate() > edate)
				||(meeting.getStartDate() < sdate&&meeting.getEndDate() >= edate)
				||(meeting.getStartDate() >= sdate&&meeting.getEndDate() <= edate))
				return true;
		}*/
		for (int i = 0; i < meeting.getParticipator().size(); i++) {
			if (userName == meeting.getParticipator()[i])
				/*if ((meeting.getStartDate() >= sdate&&meeting.getEndDate() <= edate)
				||(meeting.getStartDate() >= sdate&&meeting.getStartDate() < edate)
				||(meeting.getEndDate() > sdate&&meeting.getEndDate() <= edate))*/
				if ((meeting.getStartDate() <= sdate&&meeting.getEndDate() >= edate)
				||(meeting.getStartDate() <= sdate&&meeting.getStartDate() > edate)
				||(meeting.getEndDate() < sdate&&meeting.getEndDate() >= edate))
				return true;
		}
		return false;
	};
	list<Meeting> temp = m_storage->queryMeeting(test);
	return temp;
}
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
	function<bool(const Meeting &meeting)> test = [&] (const Meeting& meeting) {
		if (userName == meeting.getSponsor())
			return true;
		for (int i = 0; i < meeting.getParticipator().size(); i++) {
			if (meeting.getParticipator()[i] == userName)
				return true;
		}
		return false;
	};
	list<Meeting> temp = m_storage->queryMeeting(test);
	return temp;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
	std::function<bool(const Meeting &meeting)> test = [userName] (const Meeting &meeting) {
		if (userName == meeting.getSponsor())
			return true;
		return false;
	};
	list<Meeting> temp = m_storage->queryMeeting(test);
	return temp;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
	std::function<bool(const Meeting &meeting)> test = [userName] (const Meeting &meeting) {
		/*for (auto iter = (meeting.getParticipator()).begin(); iter != (meeting.getParticipator()).end(); iter++) {
			if (userName == *iter)
				return true;
		}
		return false;*/
		for (int i = 0; i < meeting.getParticipator().size(); i++) {
			if (meeting.getParticipator()[i] == userName)
				return true;
		}
		return false;
	};
	list<Meeting> temp = m_storage->queryMeeting(test);
	return temp;
}
bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
	std::function<bool(const Meeting &meeting)> test = [userName, title] (const Meeting &meeting) {
		if (userName == meeting.getSponsor()&&title == meeting.getTitle())
			return true;
		return false;
	};
	return m_storage->deleteMeeting(test);
}
bool AgendaService::deleteAllMeetings(const std::string userName) {
	std::function<bool(const Meeting &meeting)> test = [userName] (const Meeting &meeting) {
		if (userName == meeting.getSponsor())
			return true;
		return false;
	};
	return m_storage->deleteMeeting(test);
}
void AgendaService::startAgenda(void) {
	m_storage = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
	m_storage->sync();
}
