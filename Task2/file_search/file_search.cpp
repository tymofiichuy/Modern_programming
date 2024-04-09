#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

void file_search(wstring directory, wstring file) {
	WIN32_FIND_DATA data;
	HANDLE hfind;


	hfind = FindFirstFileW((directory + L"/*").c_str(), &data);
	if (hfind == INVALID_HANDLE_VALUE) {
		//>> stderr
	}
	else {
		if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			if (wcscmp(data.cFileName, L".") != 0 && wcscmp(data.cFileName, L"..") != 0) {
				file_search(directory + L"/" + data.cFileName, file);
			}
		}
		else {
			if (wcscmp(data.cFileName, file.c_str()) == 0) {
				wcout << directory << L"/" << data.cFileName << endl;
			}
		}
		while (FindNextFileW(hfind, &data) != 0) {
			wcout << directory << L"/" << data.cFileName << endl;
		}
		FindClose(hfind);
	}
}
int main(int argc, char* argv[]) {
	//Some code
}