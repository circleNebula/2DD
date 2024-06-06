#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include "rapidxml_ext.h"
//#include "rapidXml/rapidxml_iterators.hpp"

//#include "rapidXml/rapidxml_utils.hpp"

using namespace rapidxml;
using namespace std;
int main(){
	ofstream myfile;
	myfile.open ("saves.xml");
	
	std::string thePart = "<?xml version='1.0' encoding='UTF-8'?> \n ";
	thePart += "<part>"; 
	thePart+= "4";
	thePart+= "</part>"; 
	myfile << thePart;
	myfile.close();
	return 0;
}