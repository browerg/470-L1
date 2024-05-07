#define _POSIX_SOURCE
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>
#include <stdint.h>
#include <thread>
#include <filesystem>



using namespace std;
namespace fs = std::filesystem;

string shell = "cwushell";
string prompt = "cwushell";



void removeDupWord(string str){
	string strWords[5];
	int counter = 0;
	for (short i = 0; i < str.length(); i++) {
		if (str[i] == ' ' || str[i] == '\t'){
			counter++;
		}else{
			strWords[counter] += str[i];
		}
	}

}

int checkSpace(int counter, int location, string word) {
	while (word[location] == ' ' || word[location] == '\t') {
		location++;
	}

	return (location-1);
}

//-------------------------------- HELP WITH ARGS
void help(string command) {
	if (command == "cpuinfo") {
		cout << "print on the screen different cpu related information based on the switch." << endl;
		cout << "Different Switches: " << endl << "-t : print the cpu type" << endl << "-c : print the cpu clock" << endl << "-n : print the number of cores" << endl;
	}
	if (command == "meminfo") {
		cout << "print on the screen different memory related information based on the switch." << endl;
		cout << "Different Switches: " << endl << "-t : will print the total RAM memory available in the system in bytes" << endl << "-u : print the used RAM in bytes" << endl << "-c : print the size of the L2 cache/core in bytes." << endl;

	}
	if (command == "prompt") {
		cout << "prompt [new_prompt] -- will change the current shell prompt to the new_prompt." << endl << "The default prompt should be cwushell>." << endl << "Typing prompt should restore the default shell prompt." << endl;
	}
	if (command == "pwd") {
	    cout << "pwd : shows current working directory." << endl;
	}
	if (command == "ls") {
	    cout << "ls : shows current files in directory." << endl;
	}
	if (command == "cat") {
	    cout << "cat : reads or writes to a file." << endl << "Different Switches:" << endl << endl << "cat [>>] [filename] : will create a file under the filename. You will then be able to enter information into the file." << endl << endl << "cat [filename] : will read the .txt file from filename" << endl;
	}
	if(command == "cd"){
	    cout << "cd [path] : changes current working directory. " << endl;
	}
}

//------------------------------------------------ HELP ()
void help() {
	cout << endl;

	cout << "cpuinfo [-switch]: print on the screen different cpu related information based on the switch." << endl;
	cout << endl << "Different Switches: " << endl << "-t : will print the total RAM memory available in the system in bytes" << endl << endl << "-u : print the used RAM in bytes" << endl << endl << "-c : print the size of the L2 cache/core in bytes." << endl;
	
	cout << "-----------------------------------------------"<< endl;

	cout << "meminfo [-switch]: print on the screen different memory related information based on the switch." << endl;
	cout << endl << "Different Switches: " << endl << "-t : will print the total RAM memory available in the system in bytes" << endl << endl << "-u : print the used RAM in bytes" << endl << endl << "-c : print the size of the L2 cache/core in bytes." << endl;
	cout << "-----------------------------------------------"<< endl;

	cout << "prompt [new_prompt] : -- changes the current shell prompt to the new_prompt." << endl << "Default prompt should be cwushell>." << endl << "Typing prompt restores the default shell prompt." << endl;

	cout << "-----------------------------------------------"<< endl;
	
	cout << "cat : reads or writes to a file." << endl << endl << "Different Switches:" << endl << "cat [>>] [filename] : will create a file under the filename. You will then be able to enter information into the file." << endl << endl << "cat [filename] : will read the .txt file from filename" << endl;
	
	cout << "-----------------------------------------------"<< endl;
	
	cout << "ls : shows current files in directory." << endl;
	
	cout << "-----------------------------------------------"<< endl;
	
	cout << "pwd : shows current working directory." << endl;
	
	cout << "-----------------------------------------------"<< endl;
	
	cout << "cd [path] : changes current working directory. " << endl;
	
	cout << "-----------------------------------------------"<< endl;
	
}
//----------------------------------------------------------------FUNCTIONS
//------------CPU INFO
void cpuinfo(string flag){
  int case1 = flag.find("t");
  int case1u = flag.find("T");
  int case2 = flag.find("n");
  int case2u = flag.find("N");
  int case3 = flag.find("c");
  int case3u = flag.find("C");
  
  if(case1 != string::npos  || case1u != string::npos){
    case1 = 1;
  }
  if(case2 != string::npos || case2u != string::npos){
    case2 = 1;
  }
  if(case3 != string::npos || case3u != string::npos){
    case3 = 1;
  }


  if(case2 == 1){
    const auto processor_count = std::thread::hardware_concurrency();
    cout << "Number of CPU cores: " << processor_count << endl;
  }
  if(case3 == 1){		
      auto ifs = ifstream("/proc/cpuinfo");
      string line;
      while( getline(ifs, line) ){
          if(line.find("GHz") != line.npos){
	      cout << "CPU frequency: " << line.substr(line.length() - 7) << '\n';
	      break;
          }
      }	
  }
  
  if(case1 == 1){
      auto ifs = ifstream("/proc/cpuinfo");
      string line;
      while( getline(ifs, line) ){
          if(line.find("model name") != line.npos){
	      cout << "CPU TYPE: " << line.substr(13, 13) << '\n';
	      break;
          }
      }
  }


}


//-----------MEMORY INFO
void meminfo(string flag){
    
  int case1 = flag.find("t");
  int case1u = flag.find("T");
  int case2 = flag.find("u");
  int case2u = flag.find("U");
  int case3 = flag.find("c");
  int case3u = flag.find("C");
  
  if(case1 != string::npos || case1u != string::npos){
    case1 = 1;
  }
  if(case2 != string::npos || case2u != string::npos){
    case2 = 1;
  }
  if(case3 != string::npos || case3u != string::npos){
    case3 = 1;
  }
  

    
    if(case1 == 1){
      auto ifs = ifstream("/proc/meminfo");
      string line;
      while( getline(ifs, line) ){
          if(line.find("MemAvailable") != line.npos){
	      cout << "RAM MEMORY AVAILABLE: " << stoi(line.substr(14))*100 << " bytes" << '\n';
	      break;
          }
      }
    }
    if(case2 == 1){
      auto ifs = ifstream("/proc/meminfo");
      string line;
      int total;
      int avail;
      string used;
      while( getline(ifs, line) ){
          if(line.find("MemAvailable") != line.npos){
	      avail = stoi(line.substr(14));
	      //cout << avail << endl;
	      
          }
          if(line.find("MemTotal") != line.npos){
	      total = stoi(line.substr(14));
	      //cout << total << endl;
	      
          }          
      }
      cout << "RAM MEMORY USED: " << (total - avail)*100 << " bytes" << endl;
    }
    
    if(case3 == 1){
      long l2 = sysconf(_SC_LEVEL2_CACHE_SIZE);
      cout << "L2 cache size: " << l2*1024 << " bytes" << endl;
  }
}

//--------------------LS directories


void ls(int flag, string name, string info){
  string directory[5];
  
  if(flag == 1){
    directory[1] = name;
    //cout << "Added file: " << name << endl;
    
    //cout <<  << endl;
    //fileInfo(info);
  }
}
//--------------------CAT function
void cat(string arr[]){
  //cout << arr[2] << endl;
  
  if(arr[1] == ">>"){
    string file = arr[2];
    string response;
    getline(cin, response);
    ls(1, arr[2], response);
    //cout << "we here" << endl;
  }
}

//-------------------------------- MAIN
int main()
{
	
	//fs::create_directory("home/user/");
	

        string directory[5];
	string response;
	

	while (response != "exitNow") {
		
		cout << prompt << ">";
		getline(cin, response);

		
	
		
		string strWords[5];
		int counter = 0;
		int arr = 0;
		int counter2 = 0;

		while (counter2 != 1) {
			if (response[arr] == ' ' || response[arr] == '\t') {
				arr++;
			}
			else {
				counter2++;
			}
		}

		for (short i = arr; i < response.length(); i++) {
			
			if (response[i] == ' ' || response[i] == '\t') {
				i = checkSpace(counter, i, response);
				counter++;
			}else {
				strWords[counter] += response[i];
			}
		}
		
				
		if (strWords[0] == "help" || strWords[0] == "--help" || strWords[0] == "-help" || strWords[0] == "man" || strWords[0] == "manual") {
			help();
		}


		if (strWords[0] == "exit") {
			if(strWords[1].empty()){
			  exit(0);
		        }else{
		          exit(stoi(strWords[1]));
		        }
		}
		if (strWords[0] == "prompt") {
			prompt = shell;
			if (strWords[1].empty()) {
				prompt = shell;
			}
			else if(strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help"){
				help(strWords[0]);
                        }else {
				prompt = strWords[1];
			}
		}

		
		if (strWords[0] == "cpuinfo") {
			if (strWords[1].empty()) {
				help(strWords[0]);
			}
			else if (strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help") {
				help(strWords[0]);

			}
			else {
			  cpuinfo(strWords[1]);
			}
              }
		if (strWords[0] == "meminfo") {
			if (strWords[1].empty()) {
				help(strWords[0]);
			}
			else if (strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help") {
				help(strWords[0]);

			}
			else {
			  meminfo(strWords[1]);
			}
		}

		if (strWords[0] == "pwd") {
		    
		        if (strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help") {
				help(strWords[0]);

			}else{
			cout << "Working Directory: " << fs::current_path() << endl;
			}
		}
		
		if(strWords[0] == "ls"){
		        if (strWords[1].empty()) {
				help(strWords[0]);
			}
			else 
			if (strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help") {
				help(strWords[0]);

			}
		        for (const auto & entry : fs::directory_iterator(fs::current_path())){
                          std::cout << entry.path() << std::endl;
                        }
		}
		if(strWords[0] == "cd"){
		        if (strWords[1].empty()) {
				help(strWords[0]);
			}
			else if (strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help") {
				help(strWords[0]);

			}else
		        if(strWords[1].empty()){
		          
		        }else{
		          fs::current_path(strWords[1]);
		        }
		}
		
		
		
		if (strWords[0] == "cat") {
		  if (strWords[1].empty()) {
				help(strWords[0]);
			}
			else if (strWords[1] == "help" || strWords[1] == "--help" || strWords[1] == "-help") {
				help(strWords[0]);

		  }else if(strWords[1] == ">>"){
                    string file = strWords[2] + ".txt";
                    string response;
                    
                    ofstream outfile (file);
                    
                    
                    getline(cin, response);
                    outfile << response << endl;
                    
                    //ls(1, strWords[2], response);
                    
                    
                    
                    outfile.close();
                    
                    
                    
                  }else{
                    fstream nf;
                    string file = strWords[1] + ".txt";
                    nf.open(file, ios::in);
                    
                    if(nf.is_open()){
                      string fp;
                      while(getline(nf, fp)){
                        cout << fp << endl;
                      }
                      nf.close();
                    }
                  }
			
		}
		
		


	}
}
