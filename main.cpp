#include<iostream>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

struct search_result{
	filesystem::path file_path;
	int linenum;
	string Line;
};

bool check(filesystem::path directory){

	if (!filesystem::exists(directory)) {
        	 cout << "This directory does not exist" << endl;
                	return false ;}

	return true;
}

//filesystem::path is a C++ type specifically designed to represent file and directory paths
auto search_directory(filesystem::path directory){
	
	//goes through the directory and its subdirectories
        auto files = filesystem::recursive_directory_iterator(directory); 			

	return files;
}


vector<search_result> search_files(filesystem::recursive_directory_iterator FILES, string searchTerm){
	vector<search_result> results;


int files_searched=0;
string message="";
vector <filesystem::path> failed_files;
filesystem::path failed_f;
        for (auto entry : FILES) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			files_searched++;

			//open the current file so i can read its content
                        ifstream file(entry.path());

                        if (!file) {
			      message = "Could not open file\n";
			      failed_f =entry.path();
                              failed_files.push_back(entry.path());	
			      continue;
                        }

                        string line;
                        int line_number=0;

                        while (getline(file, line)) {
                                line_number++;

                                if (line.find(searchTerm) != string::npos) {
			 		search_result result;
					result.file_path = entry.path();
					result.linenum = line_number;
					result.Line = line;
					results.push_back(result);
                                        cout << "The file path: " << entry.path() << endl;
					cout<<endl;
                                        cout << "Line " << line_number << ": " << line << endl;
                          
      			}
                        }
   			}
        }
			if (message !=""){
                        	cout<<endl;
				cout<<message;
                                for (auto file : failed_files) {
   					 cout << file << endl;}
				          }

      	cout<<endl;
	cout<<"Number of searching files: "<<files_searched<<endl;
	return results;
}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "The argument count must be exactly 3!" << endl;
        cout << "Usage: ./fsearch <directory> <search-term>" << endl;
        return 1;
    }

    cout << endl;
    cout << "Searching for: " << argv[2] << endl;
    cout << "Directory : " << argv[1] << endl;
    cout << endl;
	
	bool success= true;
	bool directory_working=check(argv[1]);
	if (directory_working != success){
		return 1;  }

        auto files=search_directory(argv[1]);
	vector<search_result> answer= search_files(files, argv[2]);
	int SIZE=answer.size();

	cout<<"Number of matching lines: "<<SIZE<<endl;
        cout<<endl;

        return 0;
}

