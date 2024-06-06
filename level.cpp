#include "GL/glu.h"
#include <GL/gl.h>
#include "level.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

//create object for coordinates
struct coordinate{
	float x,y,z;
	coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};
int texture5;
int texture3;
int blankTexture;
int partl = 1;
int lowestXl;
int lowestZl;
int furthestXl;
int furthestZl;
int furthestYl;
bool shadowBooll;
//for faces, it can contain triangles and quads as well, the four variable contain which is that
struct face{
	int facenum;
	bool four;
	int* faces = (int *) malloc(4 * sizeof(int));
	face(int facen,int f1,int f2,int f3) : facenum(facen){	//constructor for triangle
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		four=false;
	}
	face(int facen,int f1,int f2,int f3,int f4) : facenum(facen){ //overloaded constructor for quad
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		four=true;
	}
};

std::vector<coordinate*> lVert;
std::vector<face*> lFaces;
std::vector<coordinate*> lNormals;

std::vector<coordinate*> sVert;
std::vector<face*> sFaces;
std::vector<coordinate*> sNormals;

std::vector<coordinate*> fVert1;
std::vector<face*> fFaces1;
std::vector<coordinate*> fVert2;
std::vector<face*> fFaces2;
std::vector<coordinate*> fVert3;
std::vector<face*> fFaces3;

std::vector<coordinate*> mVert;
std::vector<face*> mFaces;

std::vector<coordinate*> dVert;
std::vector<face*> dFaces;
std::vector<coordinate*> dNormals;

std::vector<coordinate*> coinV;
std::vector<face*> coinF;
std::vector<coordinate*> coinN;


std::vector<coordinate*> mVert2;
std::vector<face*> mFaces2;

int level::loadSlime(const char* filename){
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open Map" << std::endl;
		return -1;
	}
	char* buf = (char *)malloc(256 * sizeof(char));
	//read in every line to coord
	while(!in.eof()){
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
//	std::cout << "here" << std::endl;
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++){
		if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	//if face
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
			{
		  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
	}
	sVert = vertex;
	sNormals = normals;
	sFaces = faces;
}

int level::falling1(bool boss){
	//if(falling){
		std::string decS= "";
		if(boss){
			decS = "Objects/Boss/boss";
			decS += std::to_string(partl);
			decS += "/three2.obj";
		}else{
			decS = "Objects/structures/line.obj";
		}
		char * filename = (char*)decS.c_str();
		std::vector<std::string*> coord;	//read every single line of the obj file as a string
		std::vector<coordinate*> vertex;
		std::vector<face*> faces;
		std::vector<coordinate*> normals;	//normal vectors for every face
		std::ifstream in(filename);	//open the .obj file
		
		if(!in.is_open()){	//if not opened, exit with -1
			std::cout << "Unable to open Falling 1" << partl<< std::endl;
			return -1;
		}
		char* buf = (char *)malloc(256 * sizeof(char));
		//read in every line to coord
		while(!in.eof()){
			in.getline(buf,256);
			coord.push_back(new std::string(buf));
		}
	//	std::cout << "here" << std::endl;
		//go through all of the elements of coord, and decide what kind of element is that
		for(int i=0;i<coord.size();i++){
			if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
				continue;	//we don't care about that
			}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
				float tmpx,tmpy,tmpz;
				sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
				if(tmpy < furthestYl){
					furthestYl = tmpy;	
				}
				vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
			}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
				float tmpx,tmpy,tmpz;	//do the same thing
				sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
				if(tmpy < furthestYl){
					furthestYl = tmpy;	
				}
				normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
			}else if(coord[i]->c_str()[0]=='f'){	//if face
				int a,b,c,d,e;
				if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
				{
			  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
					faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
				}else{
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
					faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
				}
			}
		}
		fVert1 = vertex;
		fFaces1 = faces;
	//}
}
int level::falling3(bool boss){
	//if(falling){
		std::string decS= "";
		if(boss){
			decS = "Objects/Boss/boss";
			decS += std::to_string(partl);
			decS += "/three.obj";
		}else{
			decS = "Objects/structures/u.obj";
		}
		char * filename = (char*)decS.c_str();
		std::vector<std::string*> coord;	//read every single line of the obj file as a string
		std::vector<coordinate*> vertex;
		std::vector<face*> faces;
		std::vector<coordinate*> normals;	//normal vectors for every face
		std::ifstream in(filename);	//open the .obj file
		
		if(!in.is_open()){	//if not opened, exit with -1
			std::cout << "Unable to open Falling 3" << partl << std::endl;
			return -1;
		}
		char* buf = (char *)malloc(256 * sizeof(char));
		//read in every line to coord
		while(!in.eof()){
			in.getline(buf,256);
			coord.push_back(new std::string(buf));
		}
	//	std::cout << "here" << std::endl;
		//go through all of the elements of coord, and decide what kind of element is that
		for(int i=0;i<coord.size();i++){
			if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
				continue;	//we don't care about that
			}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
				float tmpx,tmpy,tmpz;
				sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
				if(tmpy < furthestYl){
					furthestYl = tmpy;	
				}
				vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
			}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
				float tmpx,tmpy,tmpz;	//do the same thing
				sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
				if(tmpy < furthestYl){
					furthestYl = tmpy;	
				}
				normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
			}else if(coord[i]->c_str()[0]=='f'){	//if face
				int a,b,c,d,e;
				if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
				{
			  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
					faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
				}else{
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
					faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
				}
			}
		}
		fVert3 = vertex;
		fFaces3 = faces;
	//}
}

int level::falling2(bool boss){
	//if(falling){
		std::string decS= "";
		if(boss){
			decS = "Objects/Boss/boss";
			decS += std::to_string(partl);
			decS += "/three3.obj";
		}else{
			decS = "Objects/structures/duelLine.obj";
		}
		char * filename = (char*)decS.c_str();
		std::vector<std::string*> coord;	//read every single line of the obj file as a string
		std::vector<coordinate*> vertex;
		std::vector<face*> faces;
		std::vector<coordinate*> normals;	//normal vectors for every face
		std::ifstream in(filename);	//open the .obj file
		
		if(!in.is_open()){	//if not opened, exit with -1
			std::cout << "Unable to open falling 2" << partl << std::endl;
			return -1;
		}
		char* buf = (char *)malloc(256 * sizeof(char));
		//read in every line to coord
		while(!in.eof()){
			in.getline(buf,256);
			coord.push_back(new std::string(buf));
		}
	//	std::cout << "here" << std::endl;
		//go through all of the elements of coord, and decide what kind of element is that
		for(int i=0;i<coord.size();i++){
			if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
				continue;	//we don't care about that
			}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
				float tmpx,tmpy,tmpz;
				sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
				if(tmpy < furthestYl){
					furthestYl = tmpy;	
				}
				vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
			}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
				float tmpx,tmpy,tmpz;	//do the same thing
				sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
				if(tmpy < furthestYl){
					furthestYl = tmpy;	
				}
				normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
			}else if(coord[i]->c_str()[0]=='f'){	//if face
				int a,b,c,d,e;
				if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
				{
			  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
					faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
				}else{
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
					faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
				}
			}
		}
		fVert2 = vertex;
		fFaces2 = faces;
	//}
}

int level::loadDecoration(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open decoration" <<  std::endl;
		dVert = vertex;
		dFaces = faces;
		dNormals = normals;
		return -1;
	}
	char* buf = (char *)malloc(256 * sizeof(char));
	//read in every line to coord
	while(!in.eof()){
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
//	std::cout << "here" << std::endl;
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++){
		if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	//if face
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
			{
		  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
	}
	
//raw


//	memcpy(&level.mFaces, &faces, faces.size());
	dFaces = faces;
	dVert = vertex;
	dNormals = normals;
	
	//memcpy(&level.mVert, &vertex, vertex.size());
//	std::cout << "here" << std::endl;
	int num;	//the id for the list
	num=glGenLists(3);	//generate a uniqe
	glNewList(num,GL_COMPILE);	//and create it
	
	
	glEndList();
//	std::cout << "here" << std::endl;
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	//for(int i=0;i<faces.size();i++)
	//	delete faces[i];
	//for(int i=0;i<normals.size();i++)
	//	delete normals[i];
	//for(int i=0;i<vertex.size();i++)
	//	delete vertex[i];
	return num;	//return with the id
}
int level::loadLava(const char* filename){
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open Map" << std::endl;
		return -1;
	}
	char* buf = (char *)malloc(256 * sizeof(char));
	//read in every line to coord
	while(!in.eof()){
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
//	std::cout << "here" << std::endl;
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++){
		if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	//if face
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
			{
		  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
	}
	lVert = vertex;
	lNormals = normals;
	lFaces = faces;
}
int level::loadMap(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open Map" << std::endl;
		return -1;
	}
	char* buf = (char *)malloc(256 * sizeof(char));
	//read in every line to coord
	while(!in.eof()){
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
//	std::cout << "here" << std::endl;
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++){
		if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	//if face
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
			{
		  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
	}
	
//raw
	furthestXl = -1000;
	furthestZl = -1000;
	lowestXl = 1000;
	lowestZl = 1000;
	for(int i = 0; i < faces.size();i++){
		
		if(vertex[faces[i]->faces[1]-1]->x > furthestXl){
			furthestXl =	vertex[faces[i]->faces[1]-1]->x;
		}
		if(vertex[faces[i]->faces[1]-1]->x < lowestXl){
			lowestXl = vertex[faces[i]->faces[1]-1]->x;
		}
		if(vertex[faces[i]->faces[1]-1]->z < lowestZl){
			lowestZl = vertex[faces[i]->faces[1]-1]->z;
		}
		if(vertex[faces[i]->faces[1]-1]->z > furthestZl){
			furthestZl =	vertex[faces[i]->faces[1]-1]->z;
		}

	}

//	memcpy(&mFaces, &faces, faces.size());
	mFaces = faces;
	mVert = vertex;
	//memcpy(&mVert, &vertex, vertex.size());
//	std::cout << "here" << std::endl;
	int num;	//the id for the list
	num=glGenLists(1);	//generate a uniqe
	glNewList(num,GL_COMPILE);	//and create it
	glBindTexture(GL_TEXTURE_2D, texture3);
	for(int i=0;i<mFaces.size();i++){	
	
		if(mFaces[i]->four){	//if it's a quad draw a quad
			if((i+1) % 6 != 0 && shadowBooll){
			//	std::cout << "here 1" << std::endl;
				glBegin(GL_QUADS);
					//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
					//I subtract 1 because the index start from 0 in C++
					
					glNormal3f(normals[mFaces[i]->facenum-1]->x,normals[mFaces[i]->facenum-1]->y,normals[mFaces[i]->facenum-1]->z);
					//draw the faces
					glTexCoord2f(1.0, 1.0);glVertex3f(mVert[mFaces[i]->faces[0]-1]->x,mVert[mFaces[i]->faces[0]-1]->y,mVert[mFaces[i]->faces[0]-1]->z);
					glTexCoord2f(1.0, 0.0);glVertex3f(mVert[mFaces[i]->faces[1]-1]->x,mVert[mFaces[i]->faces[1]-1]->y,mVert[mFaces[i]->faces[1]-1]->z);
					glTexCoord2f(0.0, 0.0);glVertex3f(mVert[mFaces[i]->faces[2]-1]->x,mVert[mFaces[i]->faces[2]-1]->y,mVert[mFaces[i]->faces[2]-1]->z);
					glTexCoord2f(0.0, 1.0);glVertex3f(mVert[mFaces[i]->faces[3]-1]->x,mVert[mFaces[i]->faces[3]-1]->y,mVert[mFaces[i]->faces[3]-1]->z);
				glEnd();
			}else{
				
				//char path[] = "Images/block3.png";
				//treeText1= loadTexture(path,3);
				glBindTexture(GL_TEXTURE_2D, texture5);
				glBegin(GL_QUADS);
					//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
					//I subtract 1 because the index start from 0 in C++
					
					glNormal3f(normals[mFaces[i]->facenum-1]->x,normals[mFaces[i]->facenum-1]->y,normals[mFaces[i]->facenum-1]->z);
					//draw the faces
					glTexCoord2f(1.0, 1.0);glVertex3f(mVert[mFaces[i]->faces[0]-1]->x,mVert[mFaces[i]->faces[0]-1]->y,mVert[mFaces[i]->faces[0]-1]->z);
					glTexCoord2f(1.0, 0.0);glVertex3f(mVert[mFaces[i]->faces[1]-1]->x,mVert[mFaces[i]->faces[1]-1]->y,mVert[mFaces[i]->faces[1]-1]->z);
					glTexCoord2f(0.0, 0.0);glVertex3f(mVert[mFaces[i]->faces[2]-1]->x,mVert[mFaces[i]->faces[2]-1]->y,mVert[mFaces[i]->faces[2]-1]->z);
					glTexCoord2f(0.0, 1.0);glVertex3f(mVert[mFaces[i]->faces[3]-1]->x,mVert[mFaces[i]->faces[3]-1]->y,mVert[mFaces[i]->faces[3]-1]->z);
				glEnd();	
				//char path2[] = "Images/Plants/tree1.png";
				//treeText1 = loadTexture(path2, 3);
				glBindTexture(GL_TEXTURE_2D, texture3);
			}
		}else{
		//	std::cout << cVertex[mFaces[i]->faces[0]-1]->x << cVertex[mFaces[i]->faces[0]-1]->y << cVertex[mFaces[i]->faces[0]-1]->z << std::endl;
			//std::cout << vertex[mFaces[i]->faces[1]-1]->x << vertex[mFaces[i]->faces[1]-1]->y << vertex[mFaces[i]->faces[1]-1]->z << std::endl;
			//std::cout << vertex[mFaces[i]->faces[2]-1]->x << vertex[mFaces[i]->faces[2]-1]->y << vertex[mFaces[i]->faces[2]-1]->z << std::endl;
			glBegin(GL_TRIANGLES);
				glBindTexture(GL_TEXTURE_2D, texture3);
				glNormal3f(normals[mFaces[i]->facenum-1]->x,normals[mFaces[i]->facenum-1]->y,normals[mFaces[i]->facenum-1]->z);
				glTexCoord2f(0.0, 0.0);glVertex3f(mVert[mFaces[i]->faces[0]-1]->x,mVert[mFaces[i]->faces[0]-1]->y,mVert[mFaces[i]->faces[0]-1]->z);
				glTexCoord2f(1.0, 0.0);glVertex3f(mVert[mFaces[i]->faces[1]-1]->x,mVert[mFaces[i]->faces[1]-1]->y,mVert[mFaces[i]->faces[1]-1]->z);
				glTexCoord2f(0.0, 1.0);glVertex3f(mVert[mFaces[i]->faces[2]-1]->x,mVert[mFaces[i]->faces[2]-1]->y,mVert[mFaces[i]->faces[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
//	std::cout << "here" << std::endl;
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	//for(int i=0;i<faces.size();i++)
	//	delete faces[i];
	for(int i=0;i<normals.size();i++)
		delete normals[i];
	//for(int i=0;i<vertex.size();i++)
	//	delete vertex[i];
	return num;	//return with the id
}
int level::loadMap2(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open Map" << partl << std::endl;
		return -1;
	}
	char* buf = (char *)malloc(256 * sizeof(char));
	//read in every line to coord
	while(!in.eof()){
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
//	std::cout << "here" << std::endl;
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++){
		if(coord[i]->c_str()[0]=='#'){	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	//if face
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
			{
		  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
		
	}
	
//raw


//	memcpy(&level.mFaces, &faces, faces.size());
	mFaces2 = faces;
	mVert2 = vertex;
	//memcpy(&level.mVert, &vertex, vertex.size());
//	std::cout << "here" << std::endl;
	int num;	//the id for the list
	num=glGenLists(2);	//generate a uniqe
	glNewList(num,GL_COMPILE);	//and create it
	//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, blankTexture);
	for(int i=0;i<mFaces2.size();i++){	
	
		if(mFaces2[i]->four){	//if it's a quad draw a quad
			if((i+1) % 6 != 0 || partl <9){
			//	std::cout << "here 1" << std::endl;
				glBegin(GL_QUADS);
					//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
					//I subtract 1 because the index start from 0 in C++
					
					glNormal3f(normals[mFaces2[i]->facenum-1]->x,normals[mFaces2[i]->facenum-1]->y,normals[mFaces2[i]->facenum-1]->z);
					//draw the faces
					glTexCoord2f(1.0, 1.0);glVertex3f(mVert2[mFaces2[i]->faces[0]-1]->x,mVert2[mFaces2[i]->faces[0]-1]->y,mVert2[mFaces2[i]->faces[0]-1]->z);
					glTexCoord2f(1.0, 0.0);glVertex3f(mVert2[mFaces2[i]->faces[1]-1]->x,mVert2[mFaces2[i]->faces[1]-1]->y,mVert2[mFaces2[i]->faces[1]-1]->z);
					glTexCoord2f(0.0, 0.0);glVertex3f(mVert2[mFaces2[i]->faces[2]-1]->x,mVert2[mFaces2[i]->faces[2]-1]->y,mVert2[mFaces2[i]->faces[2]-1]->z);
					glTexCoord2f(0.0, 1.0);glVertex3f(mVert2[mFaces2[i]->faces[3]-1]->x,mVert2[mFaces2[i]->faces[3]-1]->y,mVert2[mFaces2[i]->faces[3]-1]->z);
				glEnd();
			}else{
				
				//char path[] = "Images/block3.png";
				//treeText1= loadTexture(path,3);
				//glBindTexture(GL_TEXTURE_2D, levelLoad.texture5);
				glBegin(GL_QUADS);
					//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
					//I subtract 1 because the index start from 0 in C++
					
					glNormal3f(normals[mFaces2[i]->facenum-1]->x,normals[mFaces2[i]->facenum-1]->y,normals[mFaces2[i]->facenum-1]->z);
					//draw the faces
					glTexCoord2f(1.0, 1.0);glVertex3f(mVert2[mFaces2[i]->faces[0]-1]->x,mVert2[mFaces2[i]->faces[0]-1]->y,mVert2[mFaces2[i]->faces[0]-1]->z);
					glTexCoord2f(1.0, 0.0);glVertex3f(mVert2[mFaces2[i]->faces[1]-1]->x,mVert2[mFaces2[i]->faces[1]-1]->y,mVert2[mFaces2[i]->faces[1]-1]->z);
					glTexCoord2f(0.0, 0.0);glVertex3f(mVert2[mFaces2[i]->faces[2]-1]->x,mVert2[mFaces2[i]->faces[2]-1]->y,mVert2[mFaces2[i]->faces[2]-1]->z);
					glTexCoord2f(0.0, 1.0);glVertex3f(mVert2[mFaces2[i]->faces[3]-1]->x,mVert2[mFaces2[i]->faces[3]-1]->y,mVert2[mFaces2[i]->faces[3]-1]->z);
				glEnd();	
				//char path2[] = "Images/Plants/tree1.png";
				//treeText1 = loadTexture(path2, 3);
				//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
			}
		}else{
		//	std::cout << cVertex[level.mFaces[i]->faces[0]-1]->x << cVertex[level.mFaces[i]->faces[0]-1]->y << cVertex[level.mFaces[i]->faces[0]-1]->z << std::endl;
			//std::cout << vertex[level.mFaces[i]->faces[1]-1]->x << vertex[level.mFaces[i]->faces[1]-1]->y << vertex[level.mFaces[i]->faces[1]-1]->z << std::endl;
			//std::cout << vertex[level.mFaces[i]->faces[2]-1]->x << vertex[level.mFaces[i]->faces[2]-1]->y << vertex[level.mFaces[i]->faces[2]-1]->z << std::endl;
			glBegin(GL_TRIANGLES);
				//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
				glNormal3f(normals[mFaces2[i]->facenum-1]->x,normals[mFaces2[i]->facenum-1]->y,normals[mFaces2[i]->facenum-1]->z);
				glTexCoord2f(0.0, 0.0);glVertex3f(mVert2[mFaces2[i]->faces[0]-1]->x,mVert2[mFaces2[i]->faces[0]-1]->y,mVert2[mFaces2[i]->faces[0]-1]->z);
				glTexCoord2f(1.0, 0.0);glVertex3f(mVert2[mFaces2[i]->faces[1]-1]->x,mVert2[mFaces2[i]->faces[1]-1]->y,mVert2[mFaces2[i]->faces[1]-1]->z);
				glTexCoord2f(0.0, 1.0);glVertex3f(mVert2[mFaces2[i]->faces[2]-1]->x,mVert2[mFaces2[i]->faces[2]-1]->y,mVert2[mFaces2[i]->faces[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
//	std::cout << "here" << std::endl;
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	//for(int i=0;i<faces.size();i++)
	//	delete faces[i];
	for(int i=0;i<normals.size();i++)
		delete normals[i];
	//for(int i=0;i<vertex.size();i++)
	//	delete vertex[i];
	return num;	//return with the id
}
int level::loadCoins()
{
	std::vector<std::string*> coord;
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in("Objects/coins.obj");	//open the .obj file
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Not opened" << std::endl;
		return -1;
	}
	char* buf = (char *)malloc(256 * sizeof(char));
	//read in every line to coord
	while(!in.eof()){
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
//	std::cout << "here" << std::endl;
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++){
		if(coord[i]->c_str()[0]=='#')	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){	//if vector
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < furthestYl){
				furthestYl = tmpy;	
			}
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	//if face
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3){	//if it is a triangle (it has 3 space in it)
		  		sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
	}
	for(int i=0;i<coinF.size();i++)
		delete coinF[i];
	for(int i=0;i<coinV.size();i++)
		delete coinV[i];
	
	coinV = vertex;
	coinF = faces;
	coinN = normals;
//raw
//	std::cout << "here" << std::endl;

//	std::cout << "here" << std::endl;
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	//for(int i=0;i<faces.size();i++)
	//	delete faces[i];
	//for(int i=0;i<normals.size();i++)
		//delete normals[i];
	//for(int i=0;i<vertex.size();i++)
	//	delete vertex[i];

	return 0;	//return with the id
}
