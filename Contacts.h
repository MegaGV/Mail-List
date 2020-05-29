#pragma once

#include <string>
#include <vector>
#include <assert.h>
#include <locale>
#include <algorithm>
#include <fstream>

//contact is used to save one contact's infomation
#ifndef contact
class contract
{
public:
	std::string name;
	std::string email;
	std::vector<std::string> phone_list;

	//constructors, the name is necessary, phone can only be added after constructed
	contract(const std::string& name) : name(name) {}
	contract(const std::string& name, const std::string& email) : name(name), email(email) {}
};
#endif // !contact

//used to sort by Chinese
#ifdef _MSC_VER
static const char *ZH_CN_LOCALE_STRING = "Chinese_china";
#else
static const char *ZH_CN_LOCALE_STRING = "zh_CN.utf8";
#endif
static const std::locale zh_CN_locale = std::locale(ZH_CN_LOCALE_STRING);
static const std::collate<char>& zh_CN_collate = std::use_facet<std::collate<char> >(zh_CN_locale);
bool zh_CN_less_than(const contract &s1, const contract &s2) {
	const char *pb1 = s1.name.data();
	const char *pb2 = s2.name.data();
	return (zh_CN_collate.compare(pb1, pb1 + s1.name.size(), pb2, pb2 + s2.name.size()) < 0);
}

//Contacts_list is used to save and manage all contacts
#ifndef Contacts_list
class Contacts_list
{
private:
	std::vector<contract> list;
	std::string name;
public:
	Contacts_list(const std::string& filename) : name(filename) {//constructor use file to get contacts's information
		std::ifstream mail(filename);
		assert(mail);
		std::string name;
		std::string email;
		int num_of_phone;
		int has_email;
		std::string phone;
		while (mail >> name) {//file's format : name hasEmail (email) numberOfPhone (phone)
			list.push_back(contract(name));
			mail >> has_email;
			if (has_email) {
				mail >> email;
				set_email(list.size() - 1, email);
			}
			mail >> num_of_phone;
			while (num_of_phone-- > 0) {
				mail >> phone;
				add_phone(list.size() - 1, phone);
			}
		}
	}

	~Contacts_list() {//destructor. when closed the data will be writen to the file automaticly
		std::ofstream mail(name);
		assert(mail);

		for (int i = 0; i < list.size(); i++) {
			mail << list[i].name;
			if (list[i].email != "")
				mail << ' ' << '1' << ' ' << list[i].email ;
			else
				mail << ' ' << '0';
			mail << ' ' << list[i].phone_list.size();
			for (int j = 0; j < list[i].phone_list.size(); j++)
				mail << ' ' <<list[i].phone_list[j];
			mail << '\n';
		}
	}
	//used to jump to the correct position when click button 
	int jump_bynav(const std::string& target) {
		for (int i = 0; i < list.size(); i++) {
			const char *pb1 = target.data();//compare the the clicked character with all contacts until find the position 
			const char *pb2 = list[i].name.data();
			if (zh_CN_collate.compare(pb1, pb1 + target.size(), pb2, pb2 + list[i].name.size()) <= 0)
				return i;
		}
		return list.size() - 1;
	}

	void sort_byname() {//sort by name's Chinese character, used the locale and std::sort
		sort(list.begin(), list.end(), zh_CN_less_than);
	}

	bool isnum(const std::string& s) const {//confirm the input is number, used when save the phone
		for (int i = 0; i < s.size(); i++) {
			if (!isdigit(s[i]))
				return false;
		}
		return true;
	}

	bool isemail(const std::string& email) const {//confirm the input is email, used when save the phone
		return email == ""||(//when is empty will still save it, to do this to allow the email can not exist.
			 email.find_first_of('@') != std::string::npos
			&& email.find_first_of('.') != std::string::npos
			&& email.find_first_of('@') == email.find_last_of('@')
			&& email.find_first_of('.') > email.find_first_of('@') + 1
			&& email.find_last_of('.') != email.size() - 1);
	}

	const int size() const { return list.size(); }

	const int phone_size(const int& i) const { return list[i].phone_list.size(); }

	//getters. all use assert to avoid the overrun action
	const std::string& get_name(const int& i) {
		assert(i >= 0 && i < list.size());
		return list[i].name;
	}
	const std::string& get_email(const int& i) {
		assert(i >= 0 && i < list.size());
		return list[i].email;
	}
	const std::string& get_phone(const int&i, const int&j) {
		assert(i >= 0 && i < list.size());
		assert(j >= 0 && j < list[i].phone_list.size());
		return list[i].phone_list[j];
	}

	//setters. when delete also use assert to avoid overrun action
	void add(const std::string& name) {
		list.push_back(contract(name));
	}
	void add(const std::string& name, const std::string& email) {
		list.push_back(contract(name, email));
	}
	void del(const int& pos) {
		assert(pos >= 0 && pos < list.size());
		std::vector<contract>::iterator i = list.begin();
		list.erase(i + pos);
	}
	void set_name(const int& i, const std::string& name) {
		assert(i >= 0 && i < list.size());
		list[i].name = name;
		sort_byname();
	}
	void set_email(const int& i, const std::string& email) {
		assert(i >= 0 && i < list.size());
		list[i].email = email;
	}
	void set_phone(const int& i, const std::string& phone, const int& j) {
		assert(i >= 0 && i < list.size());
		assert(j >= 0 && j < list[i].phone_list.size());
		assert(isnum(phone));
		list[i].phone_list[j] = phone;
	}
	void add_phone(const int& i, const std::string& phone) {
		assert(i >= 0 && i < list.size());
		assert(isnum(phone));
		list[i].phone_list.push_back(phone);
	}
	void del_phone(const int& pos, const int& pos2) {
		assert(pos >= 0 && pos < list.size());
		assert(pos2 >= 0 && pos2 < list[pos].phone_list.size());
		std::vector<std::string>::iterator i = list[pos].phone_list.begin();
		list[pos].phone_list.erase(i + pos2);
	}
	//according infomation to search. will search name¡¢email and phone to get contacts
	std::vector<int> search(const std::string& info) {
		std::vector<int> result;
		if (info == "") {// if infomation is empty. add all contacts to the list again
			for (int i = 0; i < list.size(); i++)
				result.push_back(i);
		}
		else for (int i = 0; i < list.size(); i++) {
			if (list[i].name.find(info) != std::string::npos || list[i].email.find(info) != std::string::npos)
				result.push_back(i);
			else {
				for (int j = 0; j < list[i].phone_list.size(); j++) {
					if (list[i].phone_list[j].find(info) != std::string::npos) {
						result.push_back(i);
						break;
					}
				}
			}
		}
		return result;
	}
};

#endif // !Contacts_list