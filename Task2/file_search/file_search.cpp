#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

//to do
//1. input processing +
//2. error handling +
//3. basic tests, setting enviroment to run
//4. handling cyrillic symbols, additional tests -

void name_check(WIN32_FIND_DATAA data, string file, string directory) {
	if (strcmp(data.cFileName, file.c_str()) == 0) {
		cout << directory << "/" << data.cFileName << endl;
	}
}

void file_search(string file, string directory) {
	WIN32_FIND_DATAA data;
	HANDLE hfind;

	hfind = FindFirstFileA((directory + "/*").c_str(), &data);
	if (hfind == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_ACCESS_DENIED) {
			return;
		}
		else {
			throw runtime_error("Directory do not exist.");
		}
	}
	else {
		while (FindNextFileA(hfind, &data) != 0) {
			if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY
				&& strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0) {
				file_search(file, directory + "/" + data.cFileName);
			}
			else {
				name_check(data, file, directory);
			}
		}
		FindClose(hfind);
	}
}

int main(int argc, char** argv) {
	if (argc != 3 and argc != 2) {
		cerr << "Argument do not correspond signature.";
		return 1;
	}
	else if (argc == 2) {
		DWORD drives = GetLogicalDrives();
		if (drives == 0) {
			cerr << "Drives search failed. Error: " << GetLastError;
			return 1;
		}
		else {
			string file = string(argv[1], argv[1] + strlen(argv[1]));
			for (int i = 0; i < 26; i++) {
				if (drives & (1 << i)) {
					string drive(1, 'A' + i);
					file_search(file, drive + ":");
				}
			}
		}
	}
	else {
		string file = string(argv[1], argv[1] + strlen(argv[1]));
		string directory = string(argv[2], argv[2] + strlen(argv[2]));
		try {
			file_search(file, directory);
		}
		catch (runtime_error& e) {
			cerr << e.what();
			return 1;
		}
	}
	return 0;
}

//int main() {
//	file_search("Example-1.txt", "C:");
//	return 0;
//}