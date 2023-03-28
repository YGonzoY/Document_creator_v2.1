#include "Document_manager.h"
#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
namespace fs = filesystem;


int Document_manager::check_files()
{
    //cout << "check_files() began";
    int counter = 0;
    for (auto& p : fs::recursive_directory_iterator(this->folder))
    {
        //cout << "loop began ";
        if (p.path().extension().string() == ".txt")                      //берем только .txt
        {                                                                //
            documents.push_back(Document(p.path().string()));           // кладем их в вектор
        }      
        counter++;
    }         
    show_files_to_user();
    return counter;
}

void Document_manager::show_files_to_user()
{
    //cout << "show_files_to_user() began";
    for(vector<Document>::iterator iter = documents.begin(); iter != documents.end(); ++iter)
    {
        cout << iter->get_name() << "\n";
    }
    get_file();
}

void Document_manager::get_file()
{
    int choice;
    cin >> choice;
    documents[choice].get_tags_value();
}

Document_manager::Document_manager(string folder_path) : folder(folder_path)
{
    //cout << "Document_manager() began ";
    check_files();
}