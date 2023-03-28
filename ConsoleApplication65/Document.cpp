#include "Document.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <iostream>

int Document::get_tags()
{
    fstream file(this->file, 'r');
    string buf;
    bool is_tag_or_description = true;
    string tag_name;
    string description;
    if (get_template_name())
    {
        return 1;
    }
    while (file >> buf)
    {
        if (buf == "&tags&")
        {
            for (buf; buf != "&end&", file >> buf;)
            {
                if (is_tag_or_description)
                {
                    tag_name = buf;
                }
                else
                {
                    description = buf;
                    tags.push_back(Tag(tag_name, description));
                }
                is_tag_or_description = !is_tag_or_description;
            }
            return 0;
        }
    }
    return 2;
}

int Document::get_template_name()
{
    fstream file(this->file, 'r');
    string buf;
    regex label("&name&");
    getline(file, buf);
    if (regex_search(buf, label))
    {
        buf.replace(buf.begin(), buf.begin() + 6, "&name&");
        this->template_name = buf;
        file.close();
        return 0;
    }
    else
    {
        this->template_name = "can not get name for this template";
    }
    file.close();
    return 1;
}

void Document::get_tags_value()
{
    for (vector<Tag>::iterator iter; iter != tags.end(); ++iter)
    {
        cout << "Enter" << iter->description << "\n";
        cin >> iter->value;
    }
    write_in_file();
}

string Document::get_name()
{
    return this->template_name;
}

void Document::create_text()
{
}

void Document::write_in_file()
{
    fstream file(this->file);
    fstream new_file(template_name + "_31.12.2022.txt");
    if (!file.is_open())
    {
        cout << "File is not open\n\n";
        //return -1;
    }
    else
    {
        cout << "File is open\n\n";
        //return 1;
    }
    for (vector<Tag>::iterator iter; iter != tags.end(); ++iter)
    {

        string buf;
        regex r = regex(iter->name);
        //cout << "regex created\n";
        while (getline(file, buf))
        {
            //cout << "got line\n";
            //cout << regex_replace(buf, r, iter->value);
            new_file << regex_replace(buf, r, iter->value);
            new_file << "\n";
            //cout << "replaced\n";
        }
    }
    file.close();
}

Document::Document(string _file_path) : file(_file_path)
{
    //cout << "Document() began ";
    get_template_name();
    get_tags();
    //cout << "Document() ended ";
}