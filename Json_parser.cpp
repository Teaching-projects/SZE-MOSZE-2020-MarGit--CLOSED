#include "Json_parser.h"

std::map<std::string, std::string> Json_parser::ParseContent (std::string& filecontent){
	std::stringstream content;
	content<<filecontent;
	std::string line;
	std::size_t begin, end;
	std::string key, val;
	std::map <std::string, std::string> data;
	while (std::getline(content,line)){
		if ((begin=line.find("\""))!=std::string ::npos){
			end=line.find("\"",begin+1);
			key=line.substr(begin+1,end-begin-1);
			if ((begin=line.find("\"",end+1))!=std::string::npos){
				end=line.find("\"",begin+1);
				val=line.substr(begin+1,end-begin-1);
			}
			else{
				begin=line.find(":");
				val=line.substr(begin+2,line.length()-1);
			}
			data.insert(std::pair <std::string,std::string>(key,val));
		}
	}
	return data;
}


std::map<std::string, std::string> Json_parser::Parse (const std::string& filename){
	std::ifstream file;
	std::string line;
	std::string filecontent="";
	file.open(filename);
	std::map <std::string, std::string> data;
	if (!file.is_open()) throw -99;
	else{
		while (std::getline(file,line)){
			filecontent+=line+"\n";
		}
		data=ParseContent(filecontent);
		file.close();
		return data;
	}
}

std::map<std::string, std::string> Json_parser::Parse (const std::istream& datastream){
	std::string filecontent;
	std::map <std::string, std::string> data;
	std::ostringstream os;
	os<<datastream.rdbuf();
	filecontent=os.str();
	data=ParseContent(filecontent);
	return data;
}