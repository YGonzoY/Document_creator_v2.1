#pragma once
#include <string>
#include <vector>
#include "Tag.h"

using namespace std;


class Document
{
private:
	string file;
	string text;
	string template_name;
	vector<Tag> tags;
public:
	int get_tags();
	int get_template_name();
	void create_text();
	void write_in_file();
	void get_tags_value();
	string get_name();
	Document(string _file_path);
};

