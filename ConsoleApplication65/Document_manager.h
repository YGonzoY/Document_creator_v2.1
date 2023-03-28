#pragma once
#include <string>
#include <vector>
#include "Document.h"
using namespace std;


class Document_manager
{
private:
	string folder;
	vector<Document> documents;
public:
	int check_files();
	void show_files_to_user();
	void get_file();
	Document_manager(string folder_path);
};

