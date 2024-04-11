#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

void name_check(WIN32_FIND_DATA data, wstring directory, wstring file) {
	if (wcscmp(data.cFileName, file.c_str()) == 0) {
		wcout << directory << L"/" << data.cFileName << endl;
	}
}

void file_search(wstring directory, wstring file) {
	WIN32_FIND_DATA data;
	HANDLE hfind;

	hfind = FindFirstFileW((directory + L"/*").c_str(), &data);
	if (hfind == INVALID_HANDLE_VALUE) {
		//>> cerr
	}
	else {
		if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY 
			&& wcscmp(data.cFileName, L".") != 0 && wcscmp(data.cFileName, L"..") != 0) {
			file_search(directory + L"/" + data.cFileName, file);
		}
		else {
			name_check(data, directory, file);
		}
		while (FindNextFileW(hfind, &data) != 0) {
			if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY
				&& wcscmp(data.cFileName, L".") != 0 && wcscmp(data.cFileName, L"..") != 0) {
				file_search(directory + L"/" + data.cFileName, file);
			}
			else {
				name_check(data, directory, file);
			}
		}
		FindClose(hfind);
	}
}
int main() {
	auto begin = std::chrono::high_resolution_clock::now();
	//file_search(path , file);
	auto end = std::chrono::high_resolution_clock::now();
	wcout << L"\nSerch time:\n" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << L" ms";
}