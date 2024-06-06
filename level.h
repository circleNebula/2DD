#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
class level{
	public:
		int loadMap(const char* filename);
		int loadCoins();
		int loadMap2(const char* filename);
		int loadDecoration(const char* filename);
		int loadSlime(const char* filename);
		int loadLava(const char* filename);
		int falling1(bool boss);
		int falling2(bool boss);
		int falling3(bool boss);
		struct coordinate{
			float x,y,z;
			coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
		};
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
		
		std::vector<coordinate*> fVert1;
		std::vector<face*> fFaces1;
		std::vector<coordinate*> fVert2;
		std::vector<face*> fFaces2;
		std::vector<coordinate*> fVert3;
		std::vector<face*> fFaces3;
		
		int texture5;
		int texture3;
		int blankTexture;
		int partl;
		int lowestXl;
		int lowestZl;
		int furthestXl;
		int furthestZl;
		int furthestYl;
		bool shadowBooll;
	protected:
	private:

};
#endif