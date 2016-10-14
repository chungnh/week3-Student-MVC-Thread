#include "Student.h"
#include "View.h"
#include "StudentCtr.h"
#include "DAO.h"
#include <iostream>
#include <list>
#include <Windows.h>
#include <ctime>
#include <thread>

using namespace std;
string checkPoint;

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tstruct);
	string date_now = (string)buf;
	return date_now;
}

list<string> load() {//load source form "path" to list
	list<string> list;
	string path = "C:\\Users\\hongc\\Documents\\Visual Studio 2015\\Projects\\Student\\Student\\Content\\";
	string filter = "*.txt";
	string full = path + filter;

	WIN32_FIND_DATA fileName;
	HANDLE hFile;
	hFile = FindFirstFile(full.c_str(), &fileName);
	do {
		string link = path + fileName.cFileName;
		list.push_back(link);

	} while (FindNextFile(hFile, &fileName) > 0);
	return list;
}

void checkNewFile() {// if have new file , update to note.txt
	DAO dao;
	list<string> listSourceFile = load();
	char timeStr[100] = "";
	struct stat buf;
	string dateBuf;
	string timeBuf;
	while (!listSourceFile.empty()) {
		string str = listSourceFile.back();//lay 1 link de so sanh
		listSourceFile.pop_back();
		const char* cstr = str.c_str();
		if (!stat(cstr, &buf)) {
			strftime(timeStr, 100, "%Y%m%d%H%M%S", localtime(&buf.st_mtime));
			string s(timeStr);
			StudentCtr ctr;
			if (s > checkPoint) {
				system("cls");
				//cout << str << endl;
				string data = dao.readFile(str);
				if (data == "") {
					cout << "new file is empty" << endl;
				}
				else {
					//dao.writeFileThread("output.txt", data);
					list<Student> list1 = dao.readList(str);
					list<Student>::iterator it;
					for (it = list1.begin(); it != list1.end(); it++) {
						if (ctr.checkID((*it).getID())) {
							continue;
						}
						else {
							dao.writeFile((*it), "output.txt");
						}
					}
				}
			}
		}
		else {
			continue;
		}
	}
	checkPoint = currentDateTime();
	Sleep(10000);
	checkNewFile();
}

int main() {
	checkPoint = currentDateTime();
	thread reload(checkNewFile);
	string path = "C:\\Users\\hongc\\Documents\\Visual Studio 2015\\Projects\\Student\\Student\\output.txt";
	View v;
	StudentCtr sc;

	int choice;
	while (1) {
		choice = v.showMenu();
		switch (choice)
		{
		case 1: {//show all
			system("cls");
			sc.showAll();
			break;
		}
		case 2: {//add
			system("cls");
			sc.add(path);
			break;
		}
		case 3: {//edit
			system("cls");
			sc.edit();
			break;
		}
		case 4: {//delete
			system("cls");
			sc.del();
			break;
		}
		case 5: {//search
			system("cls");
			switch (v.showSearch())
			{
			case 1: {//search id
				system("cls");
				sc.searchID();
				break;
			}
			case 2: {//search name
				system("cls");
				sc.searchName();
				break;
			}
			case 3: {//search sum
				system("cls");
				sc.searchSum();
				break;
			}
			case 4: {//search math
				system("cls");
				sc.searchMath();
				break;
			}
			case 5: {//search phys
				system("cls");
				sc.searchPhys();
				break;
			}
			case 6: {//search chem
				system("cls");
				sc.searchChem();
				break;
			}
			default:
				break;
			}
			break;
		}
		case 6: {//thong ke
			system("cls");
			sc.thongke();
			break;
		}
		default:
			break;
		}
		system("pause");
	}
}