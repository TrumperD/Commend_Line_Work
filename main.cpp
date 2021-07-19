#include <iostream>
#include "DataFile.h"
#include "Folder.h"
#include "AD_File.h"
#include <iostream>
#include <typeinfo>

bool FC(Folder& currentDir, string source, string dest);

using namespace std;
void main()
{
	Folder* root = Folder::root;
	root->mkdir("C:");
	root->mkdir("D:");
	Folder* curr = Folder::cd("C:");
	bool quit = false; string path;
	string command, p_command;
	char echoStream[256];
	do {
		std::cout << curr->getfullpath().substr(5) << ">";//deletes Root Folder Name
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> command;
		try {
			if (command == "cd") {
				cin.ignore(1);
				cin >> p_command;
				try { curr = Folder::cd(p_command); }
				catch (const char* ex) { cout << ex << endl; }
				continue;
			}
			if (command == "mkdir") {
				cin.ignore(1);
				cin >> p_command;
				curr->mkdir(p_command);
				continue;
			}
			if (command == "dir") {
				curr->dir();
				continue;
			}
			if (command == "echo") {
				cin.ignore(1);
				std::cin.getline(echoStream, 256);
				command = echoStream;
				curr->mkfile(command.substr(command.find('<') + 2),
					command.substr(0, command.find('<') - 1));
				continue;
			}
			if (command == "FC") {
				cin.ignore(1);
				cin >> p_command;
				cin.ignore(1);
				cin >> command;
				if (FC(*curr, p_command, command) == true)
					cout << " equals\n";
				else
					cout << " not equals\n";
				continue;
			}
			if (command == "break") { break; }
		
		}
		catch (const char* msg) { cout << msg << endl; }
		catch (...) {
			std::cout << "invalid choois"<<endl;
		};
		cout << "invalid choois\nto quit please enter -break-" << endl;
	} while (!quit);
	delete root;
}

	bool FC(Folder &currentDir, string source, string dest)
	{
		AD_File *tmp, *tmp2;

		if (source[0] != '/') tmp = currentDir.FindAddres(source, *Folder::root);
		else tmp = currentDir.FindAddres(source, currentDir);

		if (dest[0] != '/') tmp2 = currentDir.FindAddres(dest, *Folder::root);
		else tmp2 = currentDir.FindAddres(source, currentDir);

		return tmp->operator==(*tmp2);
	}

