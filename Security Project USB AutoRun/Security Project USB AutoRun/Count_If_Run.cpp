/*
Count_If_Run.cpp
By Benjamin Lewis

This application is designed to keep track of the number of
times that it is run. The data is stored in a file
"data.txt" in the same folder as the executable.

For use with USB AutoRun to demonstrate that a computer is
vulnerable to AutoRun attack.
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <ratio>
#include <string>
#include <Windows.h>
#include <lmcons.h>
using namespace std;

int main() {

	//Determine Time and Date
	//borrowed code from http://www.cplusplus.com/reference/chrono/system_clock/now/
	using namespace std::chrono;
	duration<int, std::ratio<60 * 60 * 24> > one_day(1);
	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;
	time_t tt;
	tt = system_clock::to_time_t(today);


	//Get computer information
	//borrowed code from https://www.youtube.com/watch?v=Z7ahuHV5eXY&ab_channel=RabieHammoud
	TCHAR username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName((TCHAR*)username, &username_len);
	TCHAR compname[UNLEN + 1];
	DWORD compname_len = UNLEN + 1;
	GetComputerName((TCHAR*)compname, &compname_len);


	//Print new entry to file
	ofstream myfile;
	myfile.open("data.txt", ios_base::app);//borrowed from https://stackoverflow.com/questions/11754015/open-and-write-to-existing-fstream-without-overwrite-clearing-in-c
	myfile << endl << endl
		<< ctime(&tt)
		<< "USER NAME: " << username << endl 
		<< "COMPUTER NAME: " << compname;
	myfile.close();


	//Copy file from USB to the source computer
	//borrowed from http://www.cplusplus.com/forum/general/58562/
	char ch;
	ifstream ifin("E:\\data.txt");
	ofstream ofin("C:\\DELETEME.txt");
	if (!ifin)
		cout << "\n input file not opened successfully "<<endl<<endl;
	if (!ofin)
		cout << "\n output file not opened successfully"<<endl<<endl;
	while (ifin && ifin.get(ch))
		ofin.put(ch);

	

	//Signify to user that program has run
	cout<< "-----------------------------------------------------------------" <<endl
		<< "                      YOU'VE BEEN HACKED                         " <<endl
		<< "As a rule, you should never plug in a USB drive or CD of which   " <<endl
		<< "you are unsure about the origin.                                 " <<endl
		<< "This is a school project intended to study USB security. Learn   " <<endl
		<< "more at sites.google.com/ualr.edu/Ben/Projects                   " <<endl
		<< "-----------------------------------------------------------------";
	char endchar;
	cin >> endchar;

	return 0;
}