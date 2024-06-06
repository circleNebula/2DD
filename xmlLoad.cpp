#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "xmlLoad.h"
#include "rapidXml/rapidxml.hpp"


using namespace rapidxml;
using namespace std;
/*
	loadXml(void) Uses rapidXml API to open the saves.xml file and gets the integer as a string
	then atoi the string back into a integer and return the integer, this has to be done first
	as part variable is a very important variable.
*/
int xmlLoad::loadXml(){
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream theFile ("xml/saves.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("part");
	string thePart = root_node->value();
	cout << "thePart:" << thePart << endl;
	return std::atoi(thePart.c_str());
}
/*
	writeXml(int part) - saves the part into a file 
	and in a format that can be interpretated by rapidXml API
	using newPart as a input which is the actual part to be saved
*/
void xmlLoad::writeXml(int newPart){
	ofstream myfile;
	myfile.open ("xml/saves.xml");
	
	std::string out_string;
	std::stringstream ss;
	ss << newPart;
	out_string = ss.str();
	
	std::string thePart = "<?xml version='1.0' encoding='UTF-8'?> \n ";
	thePart += "<part>"; 
	thePart += out_string;
	thePart += "</part>"; 
	myfile << thePart;
	myfile.close();
}