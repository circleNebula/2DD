



#include "GL/glu.h"
#include <GL/gl.h>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "stb_image.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <time.h>
#include <string.h>
#include "client2.h"
#include "xmlLoad.h"
#include "coin.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "level.h"
#include "player1.h"
#include <sstream>

int coinX;
bool* eSwitched;
int titleTimer = 0;
bool onceShown = false;
int part = 9;
bool onFire = false;
bool fireAllowed = true;
int fireCounter = 0;
int fireCoolDown = 0;
bool falling = false;
bool boss = false;
bool slime = false;
bool lava = false;
float bossXSkew = 0;
float bossYSkew = 0;
float bDirectionFlip = false;
float bFallingFlip = false;
int bFallingCounter = 1000;
bool coop = false;
bool ice = false;
bool breaks = false;
bool under1 = false;
int onlineCounter = 0;
bool trline = false;
bool shadowBool = false;

float iceLSlowCounter2 = 0.18;
float iceRSlowCounter2 = 0.18;
float breakingSpeed = 0.5;
int treeText1;
bool shadow = false;
bool shadow2 = false;
bool waitTillRotate= false;
bool waitTillRotate2 = false;
float terminalIceSpeed = 0.35;
int cube;
int cube2;
int decoration;
int coinT;
int coinM;
int coinTT;
int renderText;
float z;
float indent =0;

int* decStone;
int* decImages;
bool* renderSplit;
bool* angle90Split;
bool* angle180Split;
bool* angle270Split;


float highestFallingY;
float highestFalling2Y;
float highestFalling3Y;

float fallingCountY;
float fallingCount2Y;
float fallingCount3Y;

bool falling1M = false;
bool falling2M = false;
bool falling3M = false;
int fallingNumber = 0;

bool notLoading = true;
bool online = true;

using namespace std;

string clientLine;
string cName;
string name;
float onlineX[10];
float onlineY[10];
int onlineMCounter[10];
float onlineRotation[10];
string onlineName[10];


/* Programmer Alexander Elvis Johnson
*/
//create object for coordinates
struct coordinate{
	float x,y,z;
	coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};

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
//define variables
float angle;
float highestY = 1000;


float playerX2 = 0;
float playerY2 = 0;
float playerZ2 = 0;

bool rotateAllowed = true;
int rotateCounter = 0;

int mCounter;
int mCounter2;
float speed = 0.1;
float speed2 = 0.1;
bool rot=false;
float rotateSpeed = 5;
float* breakIncrease;
bool ground = false;
bool ground2 = false;


float eRotation = 0;
bool enemies = false;
float* enemyX;
float* eSpawnZ;
float* eSpawnY;

std::vector<coordinate*> cVertex;
std::vector<face*> cFaces;






std::vector<coordinate*> bossVert;
std::vector<face*> bossFaces;
std::vector<coordinate*> bossNormals;

std::vector<coordinate*> tVert;
std::vector<face*> tFaces;

std::vector<coordinate*>eVert;
std::vector<face*>eFaces;

std::vector<coordinate*>bVert;
std::vector<face*>bFaces;

//falling vectors



float fallingSpeed = 0.01;
float falling2Speed = 0.05;
float falling3Speed = 0.02;

int falling1Count=0;
float* falling1Y;

int falling2Count =0;
float* falling2Y;

int falling3Count =0;
float* falling3Y;

//define furthest and lowest as numbers that will be overwritten. For use when rotation, and keeping the player in the correct 3d space.
float furthestX = -1000;
float furthestZ = -1000;
float lowestX = 1000;
float lowestZ = 1000;

bool left_allowed =	true;
bool right_allowed = true;
int minimap;
int listCounter = 1;
int texture4;
unsigned int* textures1;
float bobCounter = 0;
float bobCounter2 = 0;
bool switchBob = false;
bool switchBob2 = false;
int count_semi(string s) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
    if (s[i] == ':') count++;

  return count;
}
void preLoadTexture(){
	textures1 =  (unsigned int*) calloc (20,sizeof(unsigned int));
    glGenTextures(20, textures1);
}
int dieCounter = 0;
float dieWidth = 0.0f;
void die2(){
	playerY2 = -3.5;
	playerX2 = 0;
}
bool dying = false;
void die(player1 &Player1){
	if(dieCounter < 30){
		dieCounter++;
		dieWidth+= 0.5;
	}else{
	//Player1.playerY = -3.5;	
		dieCounter = 0;
		dieWidth = 0;
		die2();
		Player1.playerY =0;
		Player1.playerX = 0; //reset player1 variables involving motion
		dying = false;
		if(!online){ //only if not online should the angle be changed
			angle = 0;
		}
	}
}

int loadTexture(char filename[], int number)
{
 	
	
   // glGenTextures(number, &texture);
    glBindTexture(GL_TEXTURE_2D, textures1[number]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
	
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    }else{
        std::cout << "Failed to load texture" << std::endl;
    }	
	stbi_image_free(data);
	
	return textures1[number];
}
int lavaCollisions(level &level, player1 &Player){
	if(!rot){
		float px = Player.playerX;
		float py = ((Player.playerY) *-1) + 1.1;
		
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		if(under1){
			height -= (height*2);
		}
		if(theAngle == 360){
			angle = 0;	
		}else if(theAngle==270){
			if(mCounter != 1000 && shadowBool){
				pz = -level.lVert[level.lFaces[mCounter]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px) && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.lVert[level.lFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.lVert[level.lFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.lVert[level.lFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.lVert[level.lFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.lVert[level.lFaces[i]->faces[1]-1]->z + width && px + width/2 > -level.lVert[level.lFaces[i]->faces[1]-1]->z +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.lVert[level.lFaces[i]->faces[1]-1]->z && px + width < -level.lVert[level.lFaces[i]->faces[1]-1]->z +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((Player.playerY) *-1) + 1.1;

			for(int i = 0; i < level.lFaces.size(); i++){

				if(-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px)  && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						//if(level.lVert[level.lFaces[i]->faces[1]-1]->x + height > pz && level.lVert[level.lFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
						bool inway = false;
						shadow = false;
						if(shadowBool){	
							for(int v =0;v < level.dFaces.size(); v++){
								
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate){
										shadow = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
									inway = true;
									//break;
									//if(!waitTillRotate){
									//	shadow = true;
									//}
								}
							}
						}
						if(!shadow){
							waitTillRotate = true;
						}
					if(inway == false || shadow){
							playerZ2 = -level.lVert[level.lFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
						//}	
					}
				}

			}
			
			return 0;
		}else if(theAngle ==0){
			pz = furthestZ;
			if(mCounter != 1000 && shadowBool){
				
				pz = level.lVert[level.lFaces[mCounter]->faces[1]-1]->z;
			}
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				if(level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.lVert[level.lFaces[i]->faces[1]-1]->z && (level.lVert[level.lFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.lVert[level.lFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}			
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.lVert[level.lFaces[i]->faces[1]-1]->z && (level.lVert[level.lFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.lVert[level.lFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}
								}
							}							
						}	
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.lVert[level.lFaces[i]->faces[1]-1]->x + width && px + width/2 > level.lVert[level.lFaces[i]->faces[1]-1]->x +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > level.lVert[level.lFaces[i]->faces[1]-1]->x && px + width < level.lVert[level.lFaces[i]->faces[1]-1]->x +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
								
							}
						}
					}
				}
				//std::cout << i << std::endl;
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((Player.playerY) *-1) + 1.1;

			for(int i = 0; i < level.lFaces.size(); i++){
				if(level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate){
										shadow = true;
									}
								}
							
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.lVert[level.lFaces[i]->faces[1]-1]->z && (level.lVert[level.lFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.lVert[level.lFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + (width))){
									inway = true;
									//break;		
								}							
							}	
						}
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false|| shadow){
							playerZ2 = level.lVert[level.lFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
					}
				}
			}
		}else if(theAngle ==90){
			pz = lowestX;
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				
				if(level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height+ (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.lVert[level.lFaces[i]->faces[1]-1]->x && (level.lVert[level.lFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.lVert[level.lFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.lVert[level.lFaces[i]->faces[1]-1]->x && (level.lVert[level.lFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.lVert[level.lFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.lVert[level.lFaces[i]->faces[1]-1]->z + width && px + width/2 > level.lVert[level.lFaces[i]->faces[1]-1]->z +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
								}else if(px + width > level.lVert[level.lFaces[i]->faces[1]-1]->z && px + width < level.lVert[level.lFaces[i]->faces[1]-1]->z +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			} 
			py  =((Player.playerY) *-1) + 1.1;

			if(mCounter != 1000 && shadowBool){
				pz = level.lVert[level.dFaces[mCounter]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.lFaces.size(); i++){

				if(level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(!shadow){

								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
							  
							//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
									if(!waitTillRotate){
										shadow = true;
									}
								
							}
								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.lVert[level.lFaces[i]->faces[1]-1]->x && (level.lVert[level.lFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.lVert[level.lFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){	
									inway = true;
									//if(!waitTillRotate){
								//		shadow = true;
									//}
									//break;
								}
							}
						}	
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false || shadow){
							
							playerZ2 = level.lVert[level.lFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow){
								
								return 0;
							}
							return 1;	
						}						
					}
				}
			}
		}else if(theAngle ==180){
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.lVert[level.lFaces[i]->faces[1]-1]->z && (-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.lVert[level.lFaces[i]->faces[1]-1]->z && (-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}
							}
						}
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.lVert[level.lFaces[i]->faces[1]-1]->x + width && px + width/2 > -level.lVert[level.lFaces[i]->faces[1]-1]->x +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.lVert[level.lFaces[i]->faces[1]-1]->x && px + width < -level.lVert[level.lFaces[i]->faces[1]-1]->x +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((Player.playerY) *-1) + 1.1;
			if(mCounter != 1000 && shadowBool){
				pz = -level.lVert[level.lFaces[mCounter]->faces[1]-1]->z;
			}


			for(int i = 0; i < level.lFaces.size(); i++){

				if(-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(!waitTillRotate){
										shadow = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.lVert[level.lFaces[i]->faces[1]-1]->z && (-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
									
									inway = true;
								//	if(!waitTillRotate){
								//		shadow = true;
								//	}
									//break;
								}
							}
						}
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false || shadow){
							playerZ2 = -level.lVert[level.lFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
					}
				}

			}
		}
	}else{

		return 2;
		
	}
	return 2;
}
int lavaCollision2(level &level){
	if(!rot){
		float px = playerX2;
		float py = ((playerY2) *-1) + 1.1;
		
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		if(under1){
			height -= (height*2);
		}
		if(theAngle == 360){
			angle = 0;	
		}else if(theAngle==270){
			if(mCounter2 != 1000 && shadowBool){
				pz = -level.lVert[level.lFaces[mCounter2]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px) && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.lVert[level.lFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.lVert[level.lFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.lVert[level.lFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.lVert[level.lFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.lVert[level.lFaces[i]->faces[1]-1]->z + width && px + width/2 > -level.lVert[level.lFaces[i]->faces[1]-1]->z +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.lVert[level.lFaces[i]->faces[1]-1]->z && px + width < -level.lVert[level.lFaces[i]->faces[1]-1]->z +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;

			for(int i = 0; i < level.lFaces.size(); i++){

				if(-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px)  && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						//if(level.lVert[level.lFaces[i]->faces[1]-1]->x + height > pz && level.lVert[level.lFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){	
							for(int v =0;v < level.dFaces.size(); v++){
								
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.lVert[level.lFaces[i]->faces[1]-1]->x && (-level.lVert[level.lFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.lVert[level.lFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
									inway = true;
									//break;
									//if(!waitTillRotate2){
									//	shadow2 = true;
									//}
								}
							}
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
					if(inway == false || shadow2){
							playerZ2 = -level.lVert[level.lFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
						//}	
					}
				}

			}
			
			return 0;
		}else if(theAngle ==0){
			pz = furthestZ;
			if(mCounter2 != 1000 && shadowBool){
				
				pz = level.lVert[level.lFaces[mCounter2]->faces[1]-1]->z;
			}
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				if(level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.lVert[level.lFaces[i]->faces[1]-1]->z && (level.lVert[level.lFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.lVert[level.lFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}			
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.lVert[level.lFaces[i]->faces[1]-1]->z && (level.lVert[level.lFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.lVert[level.lFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}
								}
							}							
						}	
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.lVert[level.lFaces[i]->faces[1]-1]->x + width && px + width/2 > level.lVert[level.lFaces[i]->faces[1]-1]->x +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > level.lVert[level.lFaces[i]->faces[1]-1]->x && px + width < level.lVert[level.lFaces[i]->faces[1]-1]->x +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
								
							}
						}
					}
				}
				//std::cout << i << std::endl;
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;

			for(int i = 0; i < level.lFaces.size(); i++){
				if(level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
							
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.lVert[level.lFaces[i]->faces[1]-1]->z && (level.lVert[level.lFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.lVert[level.lFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + (width))){
									inway = true;
									//break;		
								}							
							}	
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false|| shadow2){
							playerZ2 = level.lVert[level.lFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
					}
				}
			}
		}else if(theAngle ==90){
			pz = lowestX;
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				
				if(level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height+ (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.lVert[level.lFaces[i]->faces[1]-1]->x && (level.lVert[level.lFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.lVert[level.lFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.lVert[level.lFaces[i]->faces[1]-1]->x && (level.lVert[level.lFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.lVert[level.lFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.lVert[level.lFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.lVert[level.lFaces[i]->faces[1]-1]->z + width && px + width/2 > level.lVert[level.lFaces[i]->faces[1]-1]->z +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
								}else if(px + width > level.lVert[level.lFaces[i]->faces[1]-1]->z && px + width < level.lVert[level.lFaces[i]->faces[1]-1]->z +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			} 
			py  =((playerY2) *-1) + 1.1;

			if(mCounter2 != 1000 && shadowBool){
				pz = level.lVert[level.dFaces[mCounter2]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.lFaces.size(); i++){

				if(level.lVert[level.lFaces[i]->faces[1]-1]->z +width > (px) && level.lVert[level.lFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(!shadow2){

								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
							  
							//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
									if(!waitTillRotate2){
										shadow2 = true;
									}
								
							}
								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.lVert[level.lFaces[i]->faces[1]-1]->x && (level.lVert[level.lFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.lVert[level.lFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){	
									inway = true;
									//if(!waitTillRotate2){
								//		shadow2 = true;
									//}
									//break;
								}
							}
						}	
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false || shadow2){
							
							playerZ2 = level.lVert[level.lFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow2){
								
								return 0;
							}
							return 1;	
						}						
					}
				}
			}
		}else if(theAngle ==180){
			for(int i = 0; i < level.lFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.lVert[level.lFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.lVert[level.lFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.lVert[level.lFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.lVert[level.lFaces[i]->faces[1]-1]->z && (-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.lVert[level.lFaces[i]->faces[1]-1]->z && (-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}
							}
						}
						if(!inway){
							if(-level.lVert[level.lFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.lVert[level.lFaces[i]->faces[1]-1]->x + width && px + width/2 > -level.lVert[level.lFaces[i]->faces[1]-1]->x +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.lVert[level.lFaces[i]->faces[1]-1]->x && px + width < -level.lVert[level.lFaces[i]->faces[1]-1]->x +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.lVert[level.lFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;
			if(mCounter2 != 1000 && shadowBool){
				pz = -level.lVert[level.lFaces[mCounter2]->faces[1]-1]->z;
			}


			for(int i = 0; i < level.lFaces.size(); i++){

				if(-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > (px) && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.lVert[level.lFaces[i]->faces[1]-1]->y + height > py && level.lVert[level.lFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.lVert[level.lFaces[i]->faces[1]-1]->z && (-level.lVert[level.lFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.lVert[level.lFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.lVert[level.lFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.lVert[level.lFaces[i]->faces[1]-1]->y + width)){
									
									inway = true;
								//	if(!waitTillRotate2){
								//		shadow2 = true;
								//	}
									//break;
								}
							}
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false || shadow2){
							playerZ2 = -level.lVert[level.lFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
					}
				}

			}
		}
	}else{

		return 2;
		
	}
	return 2;
}
int slimeCollision2(level &level){
	if(!rot){
		float px = playerX2;
		float py = ((playerY2) *-1) + 1.1;
		
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		if(under1){
			height -= (height*2);
		}
		if(theAngle == 360){
			angle = 0;	
		}else if(theAngle==270){
			if(mCounter2 != 1000 && shadowBool){
				pz = -level.sVert[level.sFaces[mCounter2]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px) && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.sVert[level.sFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.sVert[level.sFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.sVert[level.sFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.sVert[level.sFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.sVert[level.sFaces[i]->faces[1]-1]->z + width && px + width/2 > -level.sVert[level.sFaces[i]->faces[1]-1]->z +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.sVert[level.sFaces[i]->faces[1]-1]->z && px + width < -level.sVert[level.sFaces[i]->faces[1]-1]->z +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;

			for(int i = 0; i < level.sFaces.size(); i++){

				if(-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px)  && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						//if(level.sVert[level.sFaces[i]->faces[1]-1]->x + height > pz && level.sVert[level.sFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){	
							for(int v =0;v < level.dFaces.size(); v++){
								
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
									inway = true;
									//break;
									//if(!waitTillRotate2){
									//	shadow2 = true;
									//}
								}
							}
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
					if(inway == false || shadow2){
							playerZ2 = -level.sVert[level.sFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
						//}	
					}
				}

			}
			
			return 0;
		}else if(theAngle ==0){
			pz = furthestZ;
			if(mCounter2 != 1000 && shadowBool){
				
				pz = level.sVert[level.sFaces[mCounter2]->faces[1]-1]->z;
			}
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				if(level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.sVert[level.sFaces[i]->faces[1]-1]->z && (level.sVert[level.sFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.sVert[level.sFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}			
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.sVert[level.sFaces[i]->faces[1]-1]->z && (level.sVert[level.sFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.sVert[level.sFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}
								}
							}							
						}	
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.sVert[level.sFaces[i]->faces[1]-1]->x + width && px + width/2 > level.sVert[level.sFaces[i]->faces[1]-1]->x +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > level.sVert[level.sFaces[i]->faces[1]-1]->x && px + width < level.sVert[level.sFaces[i]->faces[1]-1]->x +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
								
							}
						}
					}
				}
				//std::cout << i << std::endl;
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;

			for(int i = 0; i < level.sFaces.size(); i++){
				if(level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
							
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.sVert[level.sFaces[i]->faces[1]-1]->z && (level.sVert[level.sFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.sVert[level.sFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + (width))){
									inway = true;
									//break;		
								}							
							}	
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false|| shadow2){
							playerZ2 = level.sVert[level.sFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
					}
				}
			}
		}else if(theAngle ==90){
			pz = lowestX;
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				
				if(level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height+ (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.sVert[level.sFaces[i]->faces[1]-1]->x && (level.sVert[level.sFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.sVert[level.sFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.sVert[level.sFaces[i]->faces[1]-1]->x && (level.sVert[level.sFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.sVert[level.sFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.sVert[level.sFaces[i]->faces[1]-1]->z + width && px + width/2 > level.sVert[level.sFaces[i]->faces[1]-1]->z +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
								}else if(px + width > level.sVert[level.sFaces[i]->faces[1]-1]->z && px + width < level.sVert[level.sFaces[i]->faces[1]-1]->z +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			} 
			py  =((playerY2) *-1) + 1.1;

			if(mCounter2 != 1000 && shadowBool){
				pz = level.sVert[level.dFaces[mCounter2]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.sFaces.size(); i++){

				if(level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(!shadow2){

								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
							  
							//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
									if(!waitTillRotate2){
										shadow2 = true;
									}
								
							}
								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.sVert[level.sFaces[i]->faces[1]-1]->x && (level.sVert[level.sFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.sVert[level.sFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){	
									inway = true;
									//if(!waitTillRotate2){
								//		shadow2 = true;
									//}
									//break;
								}
							}
						}	
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false || shadow2){
							
							playerZ2 = level.sVert[level.sFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow2){
								
								return 0;
							}
							return 1;	
						}						
					}
				}
			}
		}else if(theAngle ==180){
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.sVert[level.sFaces[i]->faces[1]-1]->z && (-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.sVert[level.sFaces[i]->faces[1]-1]->z && (-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}
							}
						}
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.sVert[level.sFaces[i]->faces[1]-1]->x + width && px + width/2 > -level.sVert[level.sFaces[i]->faces[1]-1]->x +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.sVert[level.sFaces[i]->faces[1]-1]->x && px + width < -level.sVert[level.sFaces[i]->faces[1]-1]->x +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;
			if(mCounter2 != 1000 && shadowBool){
				pz = -level.sVert[level.sFaces[mCounter2]->faces[1]-1]->z;
			}


			for(int i = 0; i < level.sFaces.size(); i++){

				if(-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.sVert[level.sFaces[i]->faces[1]-1]->z && (-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
									
									inway = true;
								//	if(!waitTillRotate2){
								//		shadow2 = true;
								//	}
									//break;
								}
							}
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false || shadow2){
							playerZ2 = -level.sVert[level.sFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
					}
				}

			}
		}
	}else{

		return 2;
		
	}
	return 2;
}
int slimeCollisions(level &level, player1 &Player){
	if(!rot){
		float px = Player.playerX;
		float py = ((Player.playerY) *-1) + 1.1;
		
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		if(under1){
			height -= (height*2);
		}
		if(theAngle == 360){
			angle = 0;	
		}else if(theAngle==270){
			if(mCounter != 1000 && shadowBool){
				pz = -level.sVert[level.sFaces[mCounter]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px) && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.sVert[level.sFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.sVert[level.sFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.sVert[level.sFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.sVert[level.sFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.sVert[level.sFaces[i]->faces[1]-1]->z + width && px + width/2 > -level.sVert[level.sFaces[i]->faces[1]-1]->z +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.sVert[level.sFaces[i]->faces[1]-1]->z && px + width < -level.sVert[level.sFaces[i]->faces[1]-1]->z +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((Player.playerY) *-1) + 1.1;

			for(int i = 0; i < level.sFaces.size(); i++){

				if(-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px)  && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						//if(level.sVert[level.sFaces[i]->faces[1]-1]->x + height > pz && level.sVert[level.sFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
						bool inway = false;
						shadow = false;
						if(shadowBool){	
							for(int v =0;v < level.dFaces.size(); v++){
								
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate){
										shadow = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.sVert[level.sFaces[i]->faces[1]-1]->x && (-level.sVert[level.sFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.sVert[level.sFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
									inway = true;
									//break;
									//if(!waitTillRotate){
									//	shadow = true;
									//}
								}
							}
						}
						if(!shadow){
							waitTillRotate = true;
						}
					if(inway == false || shadow){
							playerZ2 = -level.sVert[level.sFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
						//}	
					}
				}

			}
			
			return 0;
		}else if(theAngle ==0){
			pz = furthestZ;
			if(mCounter != 1000 && shadowBool){
				
				pz = level.sVert[level.sFaces[mCounter]->faces[1]-1]->z;
			}
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				if(level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.sVert[level.sFaces[i]->faces[1]-1]->z && (level.sVert[level.sFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.sVert[level.sFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}			
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.sVert[level.sFaces[i]->faces[1]-1]->z && (level.sVert[level.sFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.sVert[level.sFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}
								}
							}							
						}	
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.sVert[level.sFaces[i]->faces[1]-1]->x + width && px + width/2 > level.sVert[level.sFaces[i]->faces[1]-1]->x +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > level.sVert[level.sFaces[i]->faces[1]-1]->x && px + width < level.sVert[level.sFaces[i]->faces[1]-1]->x +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
								
							}
						}
					}
				}
				//std::cout << i << std::endl;
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((Player.playerY) *-1) + 1.1;

			for(int i = 0; i < level.sFaces.size(); i++){
				if(level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate){
										shadow = true;
									}
								}
							
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.sVert[level.sFaces[i]->faces[1]-1]->z && (level.sVert[level.sFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.sVert[level.sFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + (width))){
									inway = true;
									//break;		
								}							
							}	
						}
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false|| shadow){
							playerZ2 = level.sVert[level.sFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
					}
				}
			}
		}else if(theAngle ==90){
			pz = lowestX;
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				
				if(level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height+ (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.sVert[level.sFaces[i]->faces[1]-1]->x && (level.sVert[level.sFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.sVert[level.sFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.sVert[level.sFaces[i]->faces[1]-1]->x && (level.sVert[level.sFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.sVert[level.sFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.sVert[level.sFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.sVert[level.sFaces[i]->faces[1]-1]->z + width && px + width/2 > level.sVert[level.sFaces[i]->faces[1]-1]->z +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
								}else if(px + width > level.sVert[level.sFaces[i]->faces[1]-1]->z && px + width < level.sVert[level.sFaces[i]->faces[1]-1]->z +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			} 
			py  =((Player.playerY) *-1) + 1.1;

			if(mCounter != 1000 && shadowBool){
				pz = level.sVert[level.dFaces[mCounter]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.sFaces.size(); i++){

				if(level.sVert[level.sFaces[i]->faces[1]-1]->z +width > (px) && level.sVert[level.sFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(!shadow){

								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
							  
							//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
									if(!waitTillRotate){
										shadow = true;
									}
								
							}
								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.sVert[level.sFaces[i]->faces[1]-1]->x && (level.sVert[level.sFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.sVert[level.sFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){	
									inway = true;
									//if(!waitTillRotate){
								//		shadow = true;
									//}
									//break;
								}
							}
						}	
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false || shadow){
							
							playerZ2 = level.sVert[level.sFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow){
								
								return 0;
							}
							return 1;	
						}						
					}
				}
			}
		}else if(theAngle ==180){
			for(int i = 0; i < level.sFaces.size(); i++){
				py =((Player.playerY)) -1.1 ;
				level.sVert[level.sFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.sVert[level.sFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.sVert[level.sFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.sVert[level.sFaces[i]->faces[1]-1]->z && (-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.sVert[level.sFaces[i]->faces[1]-1]->z && (-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}
							}
						}
						if(!inway){
							if(-level.sVert[level.sFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.sVert[level.sFaces[i]->faces[1]-1]->x + width && px + width/2 > -level.sVert[level.sFaces[i]->faces[1]-1]->x +width){
									Player.playerX +=0.4;
									if(ice){
											Player.playerX += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.sVert[level.sFaces[i]->faces[1]-1]->x && px + width < -level.sVert[level.sFaces[i]->faces[1]-1]->x +(width/3 *2)){
									Player.playerX -=0.3;	
									if(ice){
											Player.playerX -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.sVert[level.sFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((Player.playerY) *-1) + 1.1;
			if(mCounter != 1000 && shadowBool){
				pz = -level.sVert[level.sFaces[mCounter]->faces[1]-1]->z;
			}


			for(int i = 0; i < level.sFaces.size(); i++){

				if(-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > (px) && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.sVert[level.sFaces[i]->faces[1]-1]->y + height > py && level.sVert[level.sFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(!waitTillRotate){
										shadow = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.sVert[level.sFaces[i]->faces[1]-1]->z && (-level.sVert[level.sFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.sVert[level.sFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.sVert[level.sFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.sVert[level.sFaces[i]->faces[1]-1]->y + width)){
									
									inway = true;
								//	if(!waitTillRotate){
								//		shadow = true;
								//	}
									//break;
								}
							}
						}
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false || shadow){
							playerZ2 = -level.sVert[level.sFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
					}
				}

			}
		}
	}else{

		return 2;
		
	}
	return 2;
}
void deciferP(coin &Coin){
	vector<string> coords;
	//cout << clientLine << endl;
	
		
	
	char delimiter = '/';
	string acc = "";
	
	if(clientLine.find("ROTATE") == std::string::npos && clientLine.find("Q") == std::string::npos){
		
		for(int i = 0; i < clientLine.size(); i++)
		{
			if(clientLine[i] == delimiter)
			{
				coords.push_back(acc);
				acc = "";
			}
			else
			{
				acc += clientLine[i];
			}
		}
		for(int v = 0; v < coords.size(); v++){
			if(count_semi(coords[v]) == 3){
			char delimiter = ':';
			acc = "";
			vector<string> str;
			//cout << coords[v] << endl;
			for(int i = 0; i < coords[v].size(); i++)
			{
				if(coords[v][i] == delimiter)
				{
					str.push_back(acc);
					acc = "";
				}
				else
				{
					acc += coords[v][i];
				}
			}
			//if(!name.compare(str[0]) || !cName.compare(str[0])){
			//cout << input << endl;
			//cout << str[0] << " " << str[1] << " "<< str[2] << endl;// " " <<str[3] << endl;
			//for(int i = 0; i < coords.size(); i++){
				if(str[0].find("COOP") != std::string::npos || str[0].find("PLAYER") != std::string::npos){
					if(str[0].find("HELLO") == std::string::npos){
						if(str[0].compare(cName) != 0){
							if(str[0].compare(name) != 0 && str[0].find("FINISHED") == std::string::npos){
								
								//cout << "the name" << name << endl;
							bool foundPlayer = false;
							int playerI;
						//if(str[0].compare(name) !=0 && str[0].compare(cName) != 0){
							for(int c = 0; c < onlineCounter; c++){
								if(str[0].compare(onlineName[c]) ==0){
									foundPlayer = true;
									playerI = c;
								}
							}
							if(foundPlayer ==1){
								onlineX[playerI] = strtof((str[1]).c_str(),0);
								onlineY[playerI] = strtof((str[2]).c_str(),0);
								//cout << onlineName[playerI] << " ";
								//cout << str[0] << str[1] << str[2] << "updating" << endl;
										//cout << "coords sent" << endl;
										//onlineRotation[i] = std::stof(str[3]);
							}else{
								onlineName[onlineCounter] = str[0];
								onlineX[onlineCounter] = strtof((str[1]).c_str(),0);
								onlineY[onlineCounter] = strtof((str[2]).c_str(),0);
										//onlineRotation[onlineCounter] = std::stof(str[3]);
								if(onlineCounter < 10){
									onlineCounter++;
								}
								cout << "adding new player " << str[0]<<  endl;
							}
						}
					}
				}
				}
			//}
			}
			//}
			//}
		}
	}else if(clientLine.find("Q") != std::string::npos){
		bool hasCoin = false;
		int CoinCounter = 0;
		for(int i = 0; i < 5; i++){
			if(Coin.coinsB[i]){ // if coin is found + of out 5
				CoinCounter++;
			}
		}
		if(CoinCounter == 5){
			notLoading = false;
		}
	}else{
		rotateAllowed = false;
		rotateCounter = 0;
		rot = true;
	}
    //boost::split(coord, clientLine, boost::is_any_of("-"));
	//for(int v = 0; v < sizeof(coord); v++){
	//cout << input << endl;
	//cout << coord[v] << endl;
	//boost::split(result, coord[v], boost::is_any_of(":"));
	/*
	if(!name.compare(result[0]) || !cName.compare(result[0])){
		//cout << input << endl;
		for(int i = 0; i < onlineCounter; i++){
			if(result[0].compare(onlineName[i])){
				onlineX[i] = std::stof(result[1]);
				onlineY[i] = std::stof(result[2]);
				onlineRotation[i] = std::stof(result[3]);
			}else{
				onlineName[onlineCounter] = result[0];
				onlineX[onlineCounter] = std::stof(result[1]);
				onlineY[onlineCounter] = std::stof(result[2]);
				onlineRotation[onlineCounter] = std::stof(result[3]);
				onlineCounter++;
				i = 10;
			}
		}
	}*/
}
int breakTerrainCollision2(){
	float px = playerX2;
	float py = ((playerY2) *-1) + 1.1; //the player is far away so we flip the number so it correctly coresponds to the floor x,y
	float pz;
	float width = 0.595634; //dimensions of the cubes being collided,
	float height = 0.595634;
	int theAngle = (int) angle; //cannot compare int to float, so the comparision will be too ints
	if(theAngle == 270){
		for(int i = 0; i < bFaces.size(); i++){
			if(-bVert[bFaces[i]->faces[0]-1]->z +width > (px) && -bVert[bFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
					int number = bFaces.size() /6;
					if(i % number ==0){ //break the object as a cube, not a shard.
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}else if(theAngle == 0){
		for(int i = 0; i < bFaces.size(); i++){
			if(bVert[bFaces[i]->faces[0]-1]->x +width > (px) && bVert[bFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
						int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}else if(theAngle == 90){
		for(int i = 0; i < bFaces.size(); i++){
			if(bVert[bFaces[i]->faces[0]-1]->z +width > (px) && bVert[bFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
					int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}else if(theAngle == 180){
		for(int i = 0; i < bFaces.size(); i++){
			if(-bVert[bFaces[i]->faces[0]-1]->x +width > (px) && -bVert[bFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
						int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

int breakTerrainCollision(player1 &player1){
	float px = player1.playerX;
	float py = ((player1.playerY) *-1) + 1.1; //the player is far away so we flip the number so it correctly coresponds to the floor x,y
	float pz;
	float width = 0.595634; //dimensions of the cubes being collided,
	float height = 0.595634;
	int theAngle = (int) angle; //cannot compare int to float, so the comparision will be two ints
	if(theAngle == 270){
		for(int i = 0; i < bFaces.size(); i++){
			if(-bVert[bFaces[i]->faces[0]-1]->z +width > (px) && -bVert[bFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
					int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}else if(theAngle == 0){
		for(int i = 0; i < bFaces.size(); i++){
			if(bVert[bFaces[i]->faces[0]-1]->x +width > (px) && bVert[bFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
						int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}else if(theAngle == 90){
		for(int i = 0; i < bFaces.size(); i++){
			if(bVert[bFaces[i]->faces[0]-1]->z +width > (px) && bVert[bFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
					int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
			/*if(bVert[bFaces[i]->faces[1]-1]->z +width > (px) && bVert[bFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[1]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[1]-1]->y + breakIncrease[i] < py - height + 0.25){
					int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}else if(bVert[bFaces[i]->faces[2]-1]->z +width > (px) && bVert[bFaces[i]->faces[2]-1]->z  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[2]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[2]-1]->y + breakIncrease[i] < py - height + 0.25){
					int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}*/
		}
	}else if(theAngle == 180){
		for(int i = 0; i < bFaces.size(); i++){
			if(-bVert[bFaces[i]->faces[0]-1]->x +width > (px) && -bVert[bFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
				if(bVert[bFaces[i]->faces[0]-1]->y + height + breakIncrease[i] > py && bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i] < py - height + 0.25){
						int number = bFaces.size() /6;
					if(i % number ==0){
						for(int x = i; x < i+6; x++){
							breakIncrease[x] -= breakingSpeed;
						}
					}else{
						int newI = i % 6;
						for(int x = i - newI; x < i - newI + 6; x++){
							breakIncrease[x] -= breakingSpeed;
						}	
					}
					return 1;
				}
			}
		}
	}
	return 0;
}
bool trampCollisions2(level &level){
	if(!rot){
		float px = playerX2;
		float py = ((playerY2) *-1) + 1.1; //the player is far away so we flip the number so it correctly coresponds to the floor x,y
		float pz;
		float width = 0.595634; //dimensions of the cubes being collided,
		float height = 0.595634;
		int theAngle = (int) angle; //cannot compare int to float, so the comparision will be two ints
		
		if(theAngle == 360){
			angle = 0;	//rest angle
		}else if(theAngle==270){
			pz = level.furthestXl; //the furthest x will be the z coordinate, when flipped 270 degrees
			//the coordinates must be flipped horizontally, to fit with the rendering, so -variableX will be sufficient 
			//the coin is collided when the player is on the correct x, y, and z.
			// the shape is made of triangle vertexes so it would be wise to check everypoint, by turning it into a little cube.
			
			
			for(int i = 0; i < tFaces.size(); i++){
				if(-tVert[tFaces[i]->faces[0]-1]->z +width > (px) && -tVert[tFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[0]-1]->x + height > pz && tVert[tFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}
					}
				}
				if(-tVert[tFaces[i]->faces[1]-1]->z +width > (px) && -tVert[tFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->x + height > pz && tVert[tFaces[i]->faces[2]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(-tVert[tFaces[i]->faces[2]-1]->z +width > (px) && -tVert[tFaces[i]->faces[2]-1]->z  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->x + height > pz && tVert[tFaces[i]->faces[2]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}
					}
				}
			}
			
			return false;
		}else if(theAngle ==0){
			pz = level.furthestZl;
			for(int i = 0; i < tFaces.size(); i++){
				if(tVert[tFaces[i]->faces[0]-1]->x +width > (px) && tVert[tFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[0]-1]->z + height > pz && tVert[tFaces[i]->faces[0]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;		
						}
					}
				}
				if(tVert[tFaces[i]->faces[1]-1]->x +width > (px) && tVert[tFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->z + height > pz && tVert[tFaces[i]->faces[1]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;			
						}	
					}
				}
				if(tVert[tFaces[i]->faces[2]-1]->x +width > (px) && tVert[tFaces[i]->faces[2]-1]->x  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->z + height > pz && tVert[tFaces[i]->faces[2]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}else if(theAngle ==90){
			pz = level.lowestXl;
			for(int i = 0; i < tFaces.size(); i++){
				if(tVert[tFaces[i]->faces[0]-1]->z +width > (px) && tVert[tFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[0]-1]->x +width > (pz) && tVert[tFaces[i]->faces[0]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(tVert[tFaces[i]->faces[1]-1]->z +width > (px) && tVert[tFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->x +width > (pz) && tVert[tFaces[i]->faces[1]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(tVert[tFaces[i]->faces[2]-1]->z +width > (px) && tVert[tFaces[i]->faces[2]-1]->z  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->x +width > (pz) && tVert[tFaces[i]->faces[2]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}else if(theAngle ==180){
			pz = level.lowestZl;
			for(int i = 0; i < tFaces.size(); i++){
				if(-tVert[tFaces[i]->faces[0]-1]->x +width > (px) && -tVert[tFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->z +width > (pz) && tVert[tFaces[i]->faces[1]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}		
					}
				}
				if(-tVert[tFaces[i]->faces[1]-1]->x +width > (px) && -tVert[tFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->z +width > (pz) && tVert[tFaces[i]->faces[1]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(-tVert[tFaces[i]->faces[2]-1]->x +width > (px) && -tVert[tFaces[i]->faces[2]-1]->x  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->z +width > (pz) && tVert[tFaces[i]->faces[2]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}
	}else{

		return false;
		
	}
}
//function to return true when player collides with the finish cone
bool trampCollisions(player1 &player1, level &level){
	if(!rot){
		float px = player1.playerX;
		float py = ((player1.playerY) *-1) + 1.1; //the player is far away so we flip the number so it correctly coresponds to the floor x,y
		float pz;
		float width = 0.595634; //dimensions of the cubes being collided,
		float height = 0.595634;
		int theAngle = (int) angle; //cannot compare int to float, so the comparision will be two ints
		
		if(theAngle == 360){
			angle = 0;	//rest angle
		}else if(theAngle==270){
			pz = level.furthestXl; //the furthest x will be the z coordinate, when flipped 270 degrees
			//the coordinates must be flipped horizontally, to fit with the rendering, so -variableX will be sufficient 
			//the coin is collided when the player is on the correct x, y, and z.
			// the shape is made of triangle vertexes so it would be wise to check everypoint, by turning it into a little cube.
			
			
			for(int i = 0; i < tFaces.size(); i++){
				if(-tVert[tFaces[i]->faces[0]-1]->z +width > (px) && -tVert[tFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[0]-1]->x + height > pz && tVert[tFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}
					}
				}
				if(-tVert[tFaces[i]->faces[1]-1]->z +width > (px) && -tVert[tFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->x + height > pz && tVert[tFaces[i]->faces[2]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(-tVert[tFaces[i]->faces[2]-1]->z +width > (px) && -tVert[tFaces[i]->faces[2]-1]->z  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->x + height > pz && tVert[tFaces[i]->faces[2]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}
					}
				}
			}
			
			return false;
		}else if(theAngle ==0){
			pz = level.furthestZl;
			for(int i = 0; i < tFaces.size(); i++){
				if(tVert[tFaces[i]->faces[0]-1]->x +width > (px) && tVert[tFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[0]-1]->z + height > pz && tVert[tFaces[i]->faces[0]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;		
						}
					}
				}
				if(tVert[tFaces[i]->faces[1]-1]->x +width > (px) && tVert[tFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->z + height > pz && tVert[tFaces[i]->faces[1]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;			
						}	
					}
				}
				if(tVert[tFaces[i]->faces[2]-1]->x +width > (px) && tVert[tFaces[i]->faces[2]-1]->x  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->z + height > pz && tVert[tFaces[i]->faces[2]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}else if(theAngle ==90){
			pz = level.lowestXl;
			for(int i = 0; i < tFaces.size(); i++){
				if(tVert[tFaces[i]->faces[0]-1]->z +width > (px) && tVert[tFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[0]-1]->x +width > (pz) && tVert[tFaces[i]->faces[0]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(tVert[tFaces[i]->faces[1]-1]->z +width > (px) && tVert[tFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->x +width > (pz) && tVert[tFaces[i]->faces[1]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(tVert[tFaces[i]->faces[2]-1]->z +width > (px) && tVert[tFaces[i]->faces[2]-1]->z  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->x +width > (pz) && tVert[tFaces[i]->faces[2]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}else if(theAngle ==180){
			pz = level.lowestZl;
			for(int i = 0; i < tFaces.size(); i++){
				if(-tVert[tFaces[i]->faces[0]-1]->x +width > (px) && -tVert[tFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[0]-1]->y + height > py && tVert[tFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->z +width > (pz) && tVert[tFaces[i]->faces[1]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}		
					}
				}
				if(-tVert[tFaces[i]->faces[1]-1]->x +width > (px) && -tVert[tFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[1]-1]->y + height > py && tVert[tFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[1]-1]->z +width > (pz) && tVert[tFaces[i]->faces[1]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(-tVert[tFaces[i]->faces[2]-1]->x +width > (px) && -tVert[tFaces[i]->faces[2]-1]->x  <(px + width/4)  + (width/4*3)){
					if(tVert[tFaces[i]->faces[2]-1]->y + height > py && tVert[tFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(tVert[tFaces[i]->faces[2]-1]->z +width > (pz) && tVert[tFaces[i]->faces[2]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}
	}else{

		return false;
		
	}
}

//function to return true when player collides with the finish cone
bool coinCollisions(player1 &player1, level &level){
	if(!rot){
		float px = player1.playerX;
		float py = ((player1.playerY) *-1) + 1.1; //the player is far away so we flip the number so it correctly coresponds to the floor x,y
		float pz;
		float width = 0.595634; //dimensions of the cubes being collided,
		float height = 0.595634;
		int theAngle = (int) angle; //cannot compare int to float, so the comparision will be two ints
		
		if(theAngle == 360){
			angle = 0;	//rest angle
		}else if(theAngle==270){
			pz = level.furthestXl; //the furthest x will be the z coordinate, when flipped 270 degrees
			//the coordinates must be flipped horizontally, to fit with the rendering, so -variableX will be sufficient 
			//the coin is collided when the player is on the correct x, y, and z.
			// the shape is made of triangle vertexes so it would be wise to check everypoint, by turning it into a little cube.
			
			
			for(int i = 0; i < cFaces.size(); i++){
				if(-cVertex[cFaces[i]->faces[0]-1]->z +width > (px) && -cVertex[cFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[0]-1]->y + height > py && cVertex[cFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[0]-1]->x + height > pz && cVertex[cFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}
					}
				}
				if(-cVertex[cFaces[i]->faces[1]-1]->z +width > (px) && -cVertex[cFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[1]-1]->y + height > py && cVertex[cFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[2]-1]->x + height > pz && cVertex[cFaces[i]->faces[2]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(-cVertex[cFaces[i]->faces[2]-1]->z +width > (px) && -cVertex[cFaces[i]->faces[2]-1]->z  <(px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[2]-1]->y + height > py && cVertex[cFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[2]-1]->x + height > pz && cVertex[cFaces[i]->faces[2]-1]->x < (pz + width/4)  + (width/4*3)){
							return true;	
						}
					}
				}
			}
			
			return false;
		}else if(theAngle ==0){
			pz = level.furthestZl;
			for(int i = 0; i < cFaces.size(); i++){
				if(cVertex[cFaces[i]->faces[0]-1]->x +width > (px) && cVertex[cFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[0]-1]->y + height > py && cVertex[cFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[0]-1]->z + height > pz && cVertex[cFaces[i]->faces[0]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;		
						}
					}
				}
				if(cVertex[cFaces[i]->faces[1]-1]->x +width > (px) && cVertex[cFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[1]-1]->y + height > py && cVertex[cFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[1]-1]->z + height > pz && cVertex[cFaces[i]->faces[1]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;			
						}	
					}
				}
				if(cVertex[cFaces[i]->faces[2]-1]->x +width > (px) && cVertex[cFaces[i]->faces[2]-1]->x  <(px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[2]-1]->y + height > py && cVertex[cFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[2]-1]->z + height > pz && cVertex[cFaces[i]->faces[2]-1]->z < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}else if(theAngle ==90){
			pz = level.lowestXl;
			for(int i = 0; i < cFaces.size(); i++){
				if(cVertex[cFaces[i]->faces[0]-1]->z +width > (px) && cVertex[cFaces[i]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[0]-1]->y + height > py && cVertex[cFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[0]-1]->x +width > (pz) && cVertex[cFaces[i]->faces[0]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(cVertex[cFaces[i]->faces[1]-1]->z +width > (px) && cVertex[cFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[1]-1]->y + height > py && cVertex[cFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[1]-1]->x +width > (pz) && cVertex[cFaces[i]->faces[1]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(cVertex[cFaces[i]->faces[2]-1]->z +width > (px) && cVertex[cFaces[i]->faces[2]-1]->z  <(px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[2]-1]->y + height > py && cVertex[cFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[2]-1]->x +width > (pz) && cVertex[cFaces[i]->faces[2]-1]->x  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}else if(theAngle ==180){
			pz = level.lowestZl;
			for(int i = 0; i < cFaces.size(); i++){
				if(-cVertex[cFaces[i]->faces[0]-1]->x +width > (px) && -cVertex[cFaces[i]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[0]-1]->y + height > py && cVertex[cFaces[i]->faces[0]-1]->y < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[1]-1]->z +width > (pz) && cVertex[cFaces[i]->faces[1]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}		
					}
				}
				if(-cVertex[cFaces[i]->faces[1]-1]->x +width > (px) && -cVertex[cFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[1]-1]->y + height > py && cVertex[cFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[1]-1]->z +width > (pz) && cVertex[cFaces[i]->faces[1]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
				if(-cVertex[cFaces[i]->faces[2]-1]->x +width > (px) && -cVertex[cFaces[i]->faces[2]-1]->x  <(px + width/4)  + (width/4*3)){
					if(cVertex[cFaces[i]->faces[2]-1]->y + height > py && cVertex[cFaces[i]->faces[2]-1]->y  < py - height + 0.25){
						if(cVertex[cFaces[i]->faces[2]-1]->z +width > (pz) && cVertex[cFaces[i]->faces[2]-1]->z  < (pz + width/4)  + (width/4*3)){
							return true;	
						}	
					}
				}
			}
			return false;
		}
	}else{

		return false;
		
	}
}

void enemyMovement(level &level){
	//enemy movement will move across colliding objects, and once there is no collision, the enemy will stop and change direction
	float width = 0.595634;
	float height = 0.595634;
	for(int x = 0; x < sizeof(enemyX); x++){
		float ex = enemyX[x] + eVert[eFaces[x]->faces[1]-1]->x;
		float ey = eSpawnY[x] + eVert[eFaces[x]->faces[1]-1]->y;
		float ez = eSpawnZ[x] + eVert[eFaces[x]->faces[1]-1]->z;
		bool colliding = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (ex) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (ex + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > ey && level.mVert[level.mFaces[i]->faces[1]-1]->y  < ey + height){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->z + height > ez && level.mVert[level.mFaces[i]->faces[1]-1]->z  < ez + height){	
						colliding = true;
					}					
				}
			}
		}
		if(!colliding){
			eSwitched[x] = !eSwitched[x];
		}
		if(eSwitched[x]){
			enemyX[x] += 0.1;
		}else{
			enemyX[x] -= 0.1;
		}
	}
}
bool enemyCollisions(player1 &player1){
	//check the collisions of enemy to player throughout the different game angles.
	float width = 0.595634;
	float height = 0.7;
	int theAngle = (int) angle;
	float px = player1.playerX;
	float py = ((player1.playerY) *-1) + 1.1;
	//float pz;
	for(int x = 0;x < sizeof(enemyX); x++){
		float ex = enemyX[x] + eVert[eFaces[x]->faces[1]-1]->x;
		float ey = eSpawnY[x] + eVert[eFaces[x]->faces[1]-1]->y;
		float ez = eSpawnZ[x] + eVert[eFaces[x]->faces[1]-1]->z;
		if(theAngle ==90){
			//pz = lowestX;
			if(ez +width > (px) && ez  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ex + height > pz && ex < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle == 0){
			//pz = furthestZ;
			if(ex +width > (px) && ex  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ez + height > pz && ez < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle == 180){
			//pz = lowestZ;
			if(-ex +width > (px) && -ex < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ez + height > pz && ez < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle ==270){
			//pz = furthestX;
			if(-ez +width > (px) && -ez  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ex + height > pz && ex < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}
		ex = enemyX[x] + eVert[eFaces[x]->faces[0]-1]->x;
		ey = eSpawnY[x] + eVert[eFaces[x]->faces[0]-1]->y;
		ez = eSpawnZ[x] + eVert[eFaces[x]->faces[0]-1]->z;
		if(theAngle ==90){
			//pz = lowestX;
			if(ez +width > (px) && ez  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ex + height > pz && ex < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle == 0){
			//pz = furthestZ;
			if(ex +width > (px) && ex  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ez + height > pz && ez < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle == 180){
			//pz = lowestZ;
			if(-ex +width > (px) && -ex < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ez + height > pz && ez < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle ==270){
			//pz = furthestX;
			if(-ez +width > (px) && -ez  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ex + height > pz && ex < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}
		ex = enemyX[x] + eVert[eFaces[x]->faces[2]-1]->x;
		ey = eSpawnY[x] + eVert[eFaces[x]->faces[2]-1]->y;
		ez = eSpawnZ[x] + eVert[eFaces[x]->faces[2]-1]->z;
		if(theAngle ==90){
			//pz = lowestX;
			if(ez +width > (px) && ez  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ex + height > pz && ex < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle == 0){
			//pz = furthestZ;
			if(ex +width > (px) && ex  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ez + height > pz && ez < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle == 180){
			//pz = lowestZ;
			if(-ex +width > (px) && -ex < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ez + height > pz && ez < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}else if(theAngle ==270){
			//pz = furthestX;
			if(-ez +width > (px) && -ez  < (px + width/4)  + (width/4*3)){
				if(ey + height > py && ey < py - height + 0.25){
					//if(ex + height > pz && ex < (pz + width/4)  + (width/4*3)){
						return true;	
					//}
				}
			}
		}
	}
	return false;
}

int mapCollision2(level &level){
	float px = playerX2;
	float py = ((playerY2) *-1) + 1.1;
	float pz;
	float width = 0.595634;
	float height = 0.595634;
	int theAngle = (int) angle;
	mCounter2 = 1000;
	fallingNumber = -1;
	if(theAngle == 90){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
					return i;		
				}
			}
		}
		if(falling){
			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + height  + falling1Y[c]> py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height + falling2Y[c]> py  && level.fVert2[level.fFaces2[i]->faces[1]-1]->y  + falling2Y[c] < py - height + 0.25){
							falling2M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height  + falling3Y[c]> py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
		}
		
	}else if(theAngle ==0){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
					return i;			
					//	}	
				}
			}
		}
		if(falling){
			
			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + height + falling1Y[c] > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height + falling2Y[c]> py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y  + falling2Y[c] < py - height + 0.25){
							falling2M = true; 
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height  + falling3Y[c]> py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y  + falling3Y[c] < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
		}
	}else if(theAngle == 180){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
					return i;		
				}
			}
		}
		if(falling){

			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height  + falling2Y[c]> py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y   + falling2Y[c]< py - height + 0.25){
							falling2M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height + falling3Y[c]> py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y  + falling3Y[c] < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
		}
	}else if(theAngle == 270){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px)  && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
					//if(level.mVert[level.mFaces[i]->faces[1]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
					return i;	
						//}	
				}
			}
		}
		if(falling){
			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + height + falling1Y[c] > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height + falling2Y[c] > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y  + falling2Y[c] < py - height + 0.25){
							falling2M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height + falling3Y[c] > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
		}
	}
	return 1000;
}
// collision check for main .obj file. Will return true when feet collide with floor,and will stop player from walking into objects.
int collision2(level &level, coin &Coin){
	if(falling){
		if(!rot){
			float px = playerX2;
		float py = ((playerY2) *-1) + 1.1;
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		for(int c = 0; c < falling1Count; c++){
			if(theAngle == 360){
				angle = 0;	
			}else if(theAngle==270){
				if(mCounter2 != 1000 && shadowBool){
					pz = -level.fVert1[level.fFaces1[mCounter2]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height + (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											
										inway = true;
											//break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											
										inway = true;
											//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z + width && px + width/2 > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && px + width < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;

				for(int i = 0; i < level.fFaces1.size(); i++){

					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px)  && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25){
							//if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x + height > pz && level.fVert1[level.fFaces1[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){	
								for(int v =0;v < level.dFaces.size(); v++){
									
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
										inway = true;
										//break;
										//if(!waitTillRotate2){
										//	shadow2 = true;
										//}
									}
								}
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
						if(inway == false || shadow2){
								playerZ2 = -level.fVert1[level.fFaces1[i]->faces[1]-1]->x;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
							//}	
						}
					}

				}
			}else if(theAngle ==0){
				pz = furthestZ;
				if(mCounter2 != 1000 && shadowBool){
					
					pz = level.fVert1[level.fFaces1[mCounter2]->faces[1]-1]->z;
				}
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height + (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + (width))){
											inway = true;
											//break;
										}			
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + (width))){
											inway = true;
											//break;
										}
									}
								}							
							}	
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < level.fVert1[level.fFaces1[i]->faces[1]-1]->x + width && px + width/2 > level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > level.fVert1[level.fFaces1[i]->faces[1]-1]->x && px + width < level.fVert1[level.fFaces1[i]->faces[1]-1]->x +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
									break;
									
								}
							}
						}
					}
					//std::cout << i << std::endl;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;

				for(int i = 0; i < level.fFaces1.size(); i++){
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25 ){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
								
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + (width))){
										inway = true;
										//break;		
									}							
								}	
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false|| shadow2){
								playerZ2 = level.fVert1[level.fFaces1[i]->faces[1]-1]->z;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
						}
					}
				}
			}else if(theAngle ==90){
				pz = lowestX;
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height+ (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){	
											inway = true;
										//break;
										}
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){	
											inway = true;
										//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < level.fVert1[level.fFaces1[i]->faces[1]-1]->z + width && px + width/2 > level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
											
									}else if(px + width > level.fVert1[level.fFaces1[i]->faces[1]-1]->z && px + width < level.fVert1[level.fFaces1[i]->faces[1]-1]->z +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
									break;
								}
							}
						}
					}
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
				} 
				py  =((playerY2) *-1) + 1.1;

				if(mCounter2 != 1000 && shadowBool){
					pz = level.fVert1[level.fFaces1[mCounter2]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces1.size(); i++){

					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(!shadow2){

									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								  
								//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										
										if(!waitTillRotate2){
											shadow2 = true;
										}
									
								}
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){	
										inway = true;
										//if(!waitTillRotate2){
									//		shadow2 = true;
										//}
										//break;
									}
								}
							}	
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false || shadow2){
								
								playerZ2 = level.fVert1[level.fFaces1[i]->faces[1]-1]->x;
								if(inway == false && shadow2){
									
									return 0;
								}
								return 1;	
							}						
						}
					}
				}
			}else if(theAngle ==180){
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height + (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											inway = true;
											break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											inway = true;
											break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x + width && px + width/2 > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && px + width < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x +(width/3 *2)){
										playerX2 -=0.3;
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}										
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;
				if(mCounter2 != 1000 && shadowBool){
					pz = -level.fVert1[level.fFaces1[mCounter2]->faces[1]-1]->z;
				}

				for(int i = 0; i < level.fFaces1.size(); i++){

					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
										
										inway = true;
									//	if(!waitTillRotate2){
									//		shadow2 = true;
									//	}
										//break;
									}
								}
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false || shadow2){
								playerZ2 = -level.fVert1[level.fFaces1[i]->faces[1]-1]->z;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
						}
					}

				}
			}
		}
		for(int c = 0; c < falling2Count; c++){
			if(theAngle == 360){
				angle = 0;	
			}else if(theAngle==270){
				if(mCounter2 != 1000 && shadowBool){
					pz = -level.fVert2[level.fFaces2[mCounter2]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height + (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											
										inway = true;
											//break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											
										inway = true;
											//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z + width && px + width/2 > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && px + width < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;

				for(int i = 0; i < level.fFaces2.size(); i++){

					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px)  && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py - height + 0.25){
							//if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x + height > pz && level.fVert2[level.fFaces2[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){	
								for(int v =0;v < level.dFaces.size(); v++){
									
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
										inway = true;
										//break;
										//if(!waitTillRotate2){
										//	shadow2 = true;
										//}
									}
								}
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
						if(inway == false || shadow2){
								playerZ2 = -level.fVert2[level.fFaces2[i]->faces[1]-1]->x;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
							//}	
						}
					}

				}
			}else if(theAngle ==0){
				pz = furthestZ;
				if(mCounter2 != 1000 && shadowBool){
					
					pz = level.fVert2[level.fFaces2[mCounter2]->faces[1]-1]->z;
				}
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height + (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + (width))){
											inway = true;
											//break;
										}			
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + (width))){
											inway = true;
											//break;
										}
									}
								}							
							}	
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < level.fVert2[level.fFaces2[i]->faces[1]-1]->x + width && px + width/2 > level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > level.fVert2[level.fFaces2[i]->faces[1]-1]->x && px + width < level.fVert2[level.fFaces2[i]->faces[1]-1]->x +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
									break;
									
								}
							}
						}
					}
					//std::cout << i << std::endl;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;

				for(int i = 0; i < level.fFaces2.size(); i++){
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py - height + 0.25 ){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
								
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + (width))){
										inway = true;
										//break;		
									}							
								}	
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false|| shadow2){
								playerZ2 = level.fVert2[level.fFaces2[i]->faces[1]-1]->z;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
						}
					}
				}
			}else if(theAngle ==90){
				pz = lowestX;
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height+ (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){	
											inway = true;
										//break;
										}
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){	
											inway = true;
										//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < level.fVert2[level.fFaces2[i]->faces[1]-1]->z + width && px + width/2 > level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
											
									}else if(px + width > level.fVert2[level.fFaces2[i]->faces[1]-1]->z && px + width < level.fVert2[level.fFaces2[i]->faces[1]-1]->z +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
									break;
								}
							}
						}
					}
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
				} 
				py  =((playerY2) *-1) + 1.1;

				if(mCounter2 != 1000 && shadowBool){
					pz = level.fVert2[level.fFaces2[mCounter2]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces2.size(); i++){

					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(!shadow2){

									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								  
								//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										
										if(!waitTillRotate2){
											shadow2 = true;
										}
									
								}
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){	
										inway = true;
										//if(!waitTillRotate2){
									//		shadow2 = true;
										//}
										//break;
									}
								}
							}	
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false || shadow2){
								
								playerZ2 = level.fVert2[level.fFaces2[i]->faces[1]-1]->x;
								if(inway == false && shadow2){
									
									return 0;
								}
								return 1;	
							}						
						}
					}
				}
			}else if(theAngle ==180){
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height + (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											inway = true;
											break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											inway = true;
											break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x + width && px + width/2 > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && px + width < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;
				if(mCounter2 != 1000 && shadowBool){
					pz = -level.fVert2[level.fFaces2[mCounter2]->faces[1]-1]->z;
				}

				for(int i = 0; i < level.fFaces2.size(); i++){

					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py - height + 0.25){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
										
										inway = true;
									//	if(!waitTillRotate2){
									//		shadow2 = true;
									//	}
										//break;
									}
								}
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false || shadow2){
								playerZ2 = -level.fVert2[level.fFaces2[i]->faces[1]-1]->z;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
						}
					}

				}
			}
		}
		for(int c = 0; c < falling3Count; c++){
			if(theAngle == 360){
				angle = 0;	
			}else if(theAngle==270){
				if(mCounter2 != 1000 && shadowBool){
					pz = -level.fVert3[level.fFaces3[mCounter2]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height + (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											
										inway = true;
											//break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											
										inway = true;
											//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z + width && px + width/2 > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && px + width < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;

				for(int i = 0; i < level.fFaces3.size(); i++){

					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px)  && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							//if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x + height > pz && level.fVert3[level.fFaces3[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){	
								for(int v =0;v < level.dFaces.size(); v++){
									
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
										inway = true;
										//break;
										//if(!waitTillRotate2){
										//	shadow2 = true;
										//}
									}
								}
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
						if(inway == false || shadow2){
								playerZ2 = -level.fVert3[level.fFaces3[i]->faces[1]-1]->x;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
							//}	
						}
					}

				}
			}else if(theAngle ==0){
				pz = furthestZ;
				if(mCounter2 != 1000 && shadowBool){
					
					pz = level.fVert3[level.fFaces3[mCounter2]->faces[1]-1]->z;
				}
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height + (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + (width))){
											inway = true;
											//break;
										}			
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + (width))){
											inway = true;
											//break;
										}
									}
								}							
							}	
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < level.fVert3[level.fFaces3[i]->faces[1]-1]->x + width && px + width/2 > level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > level.fVert3[level.fFaces3[i]->faces[1]-1]->x && px + width < level.fVert3[level.fFaces3[i]->faces[1]-1]->x +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
									break;
									
								}
							}
						}
					}
					//std::cout << i << std::endl;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;

				for(int i = 0; i < level.fFaces3.size(); i++){
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25 ){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
								
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + (width))){
										inway = true;
										//break;		
									}							
								}	
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false|| shadow2){
								playerZ2 = level.fVert3[level.fFaces3[i]->faces[1]-1]->z;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
						}
					}
				}
			}else if(theAngle ==90){
				pz = lowestX;
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height+ (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){	
											inway = true;
										//break;
										}
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){	
											inway = true;
										//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < level.fVert3[level.fFaces3[i]->faces[1]-1]->z + width && px + width/2 > level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									}else if(px + width > level.fVert3[level.fFaces3[i]->faces[1]-1]->z && px + width < level.fVert3[level.fFaces3[i]->faces[1]-1]->z +(width/3 *2)){
										playerX2 -=0.3;	
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}										
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
									break;
								}
							}
						}
					}
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
				} 
				py  =((playerY2) *-1) + 1.1;

				if(mCounter2 != 1000 && shadowBool){
					pz = level.fVert3[level.fFaces3[mCounter2]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces3.size(); i++){

					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(!shadow2){

									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								  
								//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										
										if(!waitTillRotate2){
											shadow2 = true;
										}
									
								}
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){	
										inway = true;
										//if(!waitTillRotate2){
									//		shadow2 = true;
										//}
										//break;
									}
								}
							}	
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false || shadow2){
								
								playerZ2 = level.fVert3[level.fFaces3[i]->faces[1]-1]->x;
								if(inway == false && shadow2){
									
									return 0;
								}
								return 1;	
							}						
						}
					}
				}
			}else if(theAngle ==180){
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((playerY2)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height + (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow2){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											inway = true;
											break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											inway = true;
											break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x + width && px + width/2 > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width){
										playerX2 +=0.4;
										if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
									}else if(px + width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && px + width < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x +(width/3 *2)){
										playerX2 -=0.3;
										if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}										
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((playerY2) *-1) + 1.1;
				if(mCounter2 != 1000 && shadowBool){
					pz = -level.fVert3[level.fFaces3[mCounter2]->faces[1]-1]->z;
				}

				for(int i = 0; i < level.fFaces3.size(); i++){

					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							bool inway = false;
							shadow2 = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										if(!waitTillRotate2){
											shadow2 = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
										
										inway = true;
									//	if(!waitTillRotate2){
									//		shadow2 = true;
									//	}
										//break;
									}
								}
							}
							if(!shadow2){
								waitTillRotate2 = true;
							}
							if(inway == false || shadow2){
								playerZ2 = -level.fVert3[level.fFaces3[i]->faces[1]-1]->z;
								if(inway == false && shadow2){
									return 0;
								}
								return 1;
							}
						}
					}

				}
			}
		}
		
		}
	}
	if(!rot){
		float px = playerX2;
		float py = ((playerY2) *-1) + 1.1;
		
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		if(under1){
			height -= (height*2);
		}
		if(theAngle == 360){
			angle = 0;	
		}else if(theAngle==270){
			if(mCounter2 != 1000 && shadowBool){
				pz = -level.mVert[level.mFaces[mCounter2]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.mVert[level.mFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.mVert[level.mFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.mVert[level.mFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.mVert[level.mFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.mVert[level.mFaces[i]->faces[1]-1]->z + width && px + width/2 > -level.mVert[level.mFaces[i]->faces[1]-1]->z +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.mVert[level.mFaces[i]->faces[1]-1]->z && px + width < -level.mVert[level.mFaces[i]->faces[1]-1]->z +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;
			for(int i = 0; i < 5; i++){
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + + Coin.increaseC[i] + height  > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}
			for(int i = 0; i < level.mFaces.size(); i++){

				if(-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px)  && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						//if(level.mVert[level.mFaces[i]->faces[1]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){	
							for(int v =0;v < level.dFaces.size(); v++){
								
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
									inway = true;
									//break;
									//if(!waitTillRotate2){
									//	shadow2 = true;
									//}
								}
							}
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
					if(inway == false || shadow2){
							playerZ2 = -level.mVert[level.mFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
						//}	
					}
				}

			}
			
			return 0;
		}else if(theAngle ==0){
			pz = furthestZ;
			if(mCounter2 != 1000 && shadowBool){
				
				pz = level.mVert[level.mFaces[mCounter2]->faces[1]-1]->z;
			}
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.mVert[level.mFaces[i]->faces[1]-1]->z && (level.mVert[level.mFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.mVert[level.mFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}			
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.mVert[level.mFaces[i]->faces[1]-1]->z && (level.mVert[level.mFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.mVert[level.mFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}
								}
							}							
						}	
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.mVert[level.mFaces[i]->faces[1]-1]->x + width && px + width/2 > level.mVert[level.mFaces[i]->faces[1]-1]->x +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > level.mVert[level.mFaces[i]->faces[1]-1]->x && px + width < level.mVert[level.mFaces[i]->faces[1]-1]->x +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
								
							}
						}
					}
				}
				//std::cout << i << std::endl;
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;
			for(int i = 0; i < 5; i++){
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + height  + Coin.increaseC[i]> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] + height> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + height  + Coin.increaseC[i]> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}
			for(int i = 0; i < level.mFaces.size(); i++){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
							
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.mVert[level.mFaces[i]->faces[1]-1]->z && (level.mVert[level.mFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.mVert[level.mFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + (width))){
									inway = true;
									//break;		
								}							
							}	
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false|| shadow2){
							playerZ2 = level.mVert[level.mFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
					}
				}
			}
		}else if(theAngle ==90){
			pz = lowestX;
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				
				if(level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height+ (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.mVert[level.mFaces[i]->faces[1]-1]->x && (level.mVert[level.mFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.mVert[level.mFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.mVert[level.mFaces[i]->faces[1]-1]->x && (level.mVert[level.mFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.mVert[level.mFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.mVert[level.mFaces[i]->faces[1]-1]->z + width && px + width/2 > level.mVert[level.mFaces[i]->faces[1]-1]->z +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
										
								}else if(px + width > level.mVert[level.mFaces[i]->faces[1]-1]->z && px + width < level.mVert[level.mFaces[i]->faces[1]-1]->z +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			} 
			py  =((playerY2) *-1) + 1.1;
			for(int i = 0; i < 5; i++){
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i]< py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y +Coin.increaseC[i] + height > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i]< py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i]< py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}
			if(mCounter2 != 1000 && shadowBool){
				pz = level.mVert[level.mFaces[mCounter2]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.mFaces.size(); i++){

				if(level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(!shadow2){

								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
							  
							//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
									if(!waitTillRotate2){
										shadow2 = true;
									}
								
							}
								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.mVert[level.mFaces[i]->faces[1]-1]->x && (level.mVert[level.mFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.mVert[level.mFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){	
									inway = true;
									//if(!waitTillRotate2){
								//		shadow2 = true;
									//}
									//break;
								}
							}
						}	
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false || shadow2){
							
							playerZ2 = level.mVert[level.mFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow2){
								
								return 0;
							}
							return 1;	
						}						
					}
				}
			}
		}else if(theAngle ==180){
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((playerY2)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow2){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.mVert[level.mFaces[i]->faces[1]-1]->z && (-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.mVert[level.mFaces[i]->faces[1]-1]->z && (-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}
							}
						}
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.mVert[level.mFaces[i]->faces[1]-1]->x + width && px + width/2 > -level.mVert[level.mFaces[i]->faces[1]-1]->x +width){
									playerX2 +=0.4;
									if(ice){
											playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
											
										}
									
								}else if(px + width > -level.mVert[level.mFaces[i]->faces[1]-1]->x && px + width < -level.mVert[level.mFaces[i]->faces[1]-1]->x +(width/3 *2)){
									playerX2 -=0.3;	
									if(ice){
											playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((playerY2) *-1) + 1.1;
			if(mCounter2 != 1000 && shadowBool){
				pz = -level.mVert[level.mFaces[mCounter2]->faces[1]-1]->z;
			}
			for(int i = 0; i < 5; i++){
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y +height + Coin.increaseC[i]> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] + height > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] + height > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}

			for(int i = 0; i < level.mFaces.size(); i++){

				if(-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						bool inway = false;
						shadow2 = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(!waitTillRotate2){
										shadow2 = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.mVert[level.mFaces[i]->faces[1]-1]->z && (-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
									
									inway = true;
								//	if(!waitTillRotate2){
								//		shadow2 = true;
								//	}
									//break;
								}
							}
						}
						if(!shadow2){
							waitTillRotate2 = true;
						}
						if(inway == false || shadow2){
							playerZ2 = -level.mVert[level.mFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow2){
								return 0;
							}
							return 1;
						}
					}
				}

			}
		}
	}else{

		return 2;
		
	}
	return 0;
}
int collision(level &level, coin &Coin, player1 &player){
	if(falling){
		if(!rot){
			float px = player.playerX;
		float py = ((player.playerY) *-1) + 1.1;
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		for(int c = 0; c < falling1Count; c++){
			if(theAngle == 360){
				angle = 0;	
			}else if(theAngle==270){
				if(mCounter != 1000 && shadowBool){
					pz = -level.fVert1[level.fFaces1[mCounter]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height + (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											
										inway = true;
											//break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											
										inway = true;
											//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z + width && px + width/2 > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && px + width < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;

				for(int i = 0; i < level.fFaces1.size(); i++){

					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px)  && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25){
							//if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x + height > pz && level.fVert1[level.fFaces1[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
							bool inway = false;
							shadow = false;
							if(shadowBool){	
								for(int v =0;v < level.dFaces.size(); v++){
									
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate){
											shadow = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
										inway = true;
										//break;
										//if(!waitTillRotate){
										//	shadow = true;
										//}
									}
								}
							}
							if(!shadow){
								waitTillRotate = true;
							}
						if(inway == false || shadow){
								player.playerZ = -level.fVert1[level.fFaces1[i]->faces[1]-1]->x;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
							//}	
						}
					}

				}
			}else if(theAngle ==0){
				pz = furthestZ;
				if(mCounter != 1000 && shadowBool){
					
					pz = level.fVert1[level.fFaces1[mCounter]->faces[1]-1]->z;
				}
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height + (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + (width))){
											inway = true;
											//break;
										}			
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + (width))){
											inway = true;
											//break;
										}
									}
								}							
							}	
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < level.fVert1[level.fFaces1[i]->faces[1]-1]->x + width && px + width/2 > level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > level.fVert1[level.fFaces1[i]->faces[1]-1]->x && px + width < level.fVert1[level.fFaces1[i]->faces[1]-1]->x +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
									break;
									
								}
							}
						}
					}
					//std::cout << i << std::endl;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;

				for(int i = 0; i < level.fFaces1.size(); i++){
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25 ){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate){
											shadow = true;
										}
									}
								
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + (width))){
										inway = true;
										//break;		
									}							
								}	
							}
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false|| shadow){
								player.playerZ = level.fVert1[level.fFaces1[i]->faces[1]-1]->z;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
						}
					}
				}
			}else if(theAngle ==90){
				pz = lowestX;
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height+ (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){	
											inway = true;
										//break;
										}
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){	
											inway = true;
										//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < level.fVert1[level.fFaces1[i]->faces[1]-1]->z + width && px + width/2 > level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
											
									}else if(px + width > level.fVert1[level.fFaces1[i]->faces[1]-1]->z && px + width < level.fVert1[level.fFaces1[i]->faces[1]-1]->z +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
									break;
								}
							}
						}
					}
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
				} 
				py  =((player.playerY) *-1) + 1.1;

				if(mCounter != 1000 && shadowBool){
					pz = level.fVert1[level.fFaces1[mCounter]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces1.size(); i++){

					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(!shadow){

									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								  
								//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										
										if(!waitTillRotate){
											shadow = true;
										}
									
								}
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert1[level.fFaces1[i]->faces[1]-1]->x && (level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){	
										inway = true;
										//if(!waitTillRotate){
									//		shadow = true;
										//}
										//break;
									}
								}
							}	
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false || shadow){
								
								player.playerZ = level.fVert1[level.fFaces1[i]->faces[1]-1]->x;
								if(inway == false && shadow){
									
									return 0;
								}
								return 1;	
							}						
						}
					}
				}
			}else if(theAngle ==180){
				for(int i = 0; i < level.fFaces1.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] +(height + (height)) > py && -level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											inway = true;
											break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
											inway = true;
											break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py ){
									if(px < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x + width && px + width/2 > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > -level.fVert1[level.fFaces1[i]->faces[1]-1]->x && px + width < -level.fVert1[level.fFaces1[i]->faces[1]-1]->x +(width/3 *2)){
										player.playerX -=0.3;
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}										
									}
									level.fVert1[level.fFaces1[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert1[level.fFaces1[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;
				if(mCounter != 1000 && shadowBool){
					pz = -level.fVert1[level.fFaces1[mCounter]->faces[1]-1]->z;
				}

				for(int i = 0; i < level.fFaces1.size(); i++){

					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										if(!waitTillRotate){
											shadow = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert1[level.fFaces1[i]->faces[1]-1]->z && (-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c] + width)){
										
										inway = true;
									//	if(!waitTillRotate){
									//		shadow = true;
									//	}
										//break;
									}
								}
							}
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false || shadow){
								player.playerZ = -level.fVert1[level.fFaces1[i]->faces[1]-1]->z;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
						}
					}

				}
			}
		}
		for(int c = 0; c < falling2Count; c++){
			if(theAngle == 360){
				angle = 0;	
			}else if(theAngle==270){
				if(mCounter != 1000 && shadowBool){
					pz = -level.fVert2[level.fFaces2[mCounter]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height + (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											
										inway = true;
											//break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											
										inway = true;
											//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z + width && px + width/2 > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && px + width < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;

				for(int i = 0; i < level.fFaces2.size(); i++){

					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px)  && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py - height + 0.25){
							//if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x + height > pz && level.fVert2[level.fFaces2[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
							bool inway = false;
							shadow = false;
							if(shadowBool){	
								for(int v =0;v < level.dFaces.size(); v++){
									
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate){
											shadow = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
										inway = true;
										//break;
										//if(!waitTillRotate){
										//	shadow = true;
										//}
									}
								}
							}
							if(!shadow){
								waitTillRotate = true;
							}
						if(inway == false || shadow){
								player.playerZ = -level.fVert2[level.fFaces2[i]->faces[1]-1]->x;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
							//}	
						}
					}

				}
			}else if(theAngle ==0){
				pz = furthestZ;
				if(mCounter != 1000 && shadowBool){
					
					pz = level.fVert2[level.fFaces2[mCounter]->faces[1]-1]->z;
				}
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height + (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + (width))){
											inway = true;
											//break;
										}			
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + (width))){
											inway = true;
											//break;
										}
									}
								}							
							}	
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < level.fVert2[level.fFaces2[i]->faces[1]-1]->x + width && px + width/2 > level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > level.fVert2[level.fFaces2[i]->faces[1]-1]->x && px + width < level.fVert2[level.fFaces2[i]->faces[1]-1]->x +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
									break;
									
								}
							}
						}
					}
					//std::cout << i << std::endl;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;

				for(int i = 0; i < level.fFaces2.size(); i++){
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py - height + 0.25 ){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate){
											shadow = true;
										}
									}
								
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + (width))){
										inway = true;
										//break;		
									}							
								}	
							}
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false|| shadow){
								player.playerZ = level.fVert2[level.fFaces2[i]->faces[1]-1]->z;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
						}
					}
				}
			}else if(theAngle ==90){
				pz = lowestX;
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height+ (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){	
											inway = true;
										//break;
										}
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){	
											inway = true;
										//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < level.fVert2[level.fFaces2[i]->faces[1]-1]->z + width && px + width/2 > level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
											
									}else if(px + width > level.fVert2[level.fFaces2[i]->faces[1]-1]->z && px + width < level.fVert2[level.fFaces2[i]->faces[1]-1]->z +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
									break;
								}
							}
						}
					}
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
				} 
				py  =((player.playerY) *-1) + 1.1;

				if(mCounter != 1000 && shadowBool){
					pz = level.fVert2[level.fFaces2[mCounter]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces2.size(); i++){

					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(!shadow){

									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								  
								//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										
										if(!waitTillRotate){
											shadow = true;
										}
									
								}
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert2[level.fFaces2[i]->faces[1]-1]->x && (level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){	
										inway = true;
										//if(!waitTillRotate){
									//		shadow = true;
										//}
										//break;
									}
								}
							}	
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false || shadow){
								
								player.playerZ = level.fVert2[level.fFaces2[i]->faces[1]-1]->x;
								if(inway == false && shadow){
									
									return 0;
								}
								return 1;	
							}						
						}
					}
				}
			}else if(theAngle ==180){
				for(int i = 0; i < level.fFaces2.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] +(height + (height)) > py && -level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											inway = true;
											break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
											inway = true;
											break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py ){
									if(px < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x + width && px + width/2 > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > -level.fVert2[level.fFaces2[i]->faces[1]-1]->x && px + width < -level.fVert2[level.fFaces2[i]->faces[1]-1]->x +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert2[level.fFaces2[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert2[level.fFaces2[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;
				if(mCounter != 1000 && shadowBool){
					pz = -level.fVert2[level.fFaces2[mCounter]->faces[1]-1]->z;
				}

				for(int i = 0; i < level.fFaces2.size(); i++){

					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + height > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c]  < py - height + 0.25){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										if(!waitTillRotate){
											shadow = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert2[level.fFaces2[i]->faces[1]-1]->z && (-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert2[level.fFaces2[i]->faces[1]-1]->y + falling2Y[c] + width)){
										
										inway = true;
									//	if(!waitTillRotate){
									//		shadow = true;
									//	}
										//break;
									}
								}
							}
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false || shadow){
								player.playerZ = -level.fVert2[level.fFaces2[i]->faces[1]-1]->z;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
						}
					}

				}
			}
		}
		for(int c = 0; c < falling3Count; c++){
			if(theAngle == 360){
				angle = 0;	
			}else if(theAngle==270){
				if(mCounter != 1000 && shadowBool){
					pz = -level.fVert3[level.fFaces3[mCounter]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height + (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											
										inway = true;
											//break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											
										inway = true;
											//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z + width && px + width/2 > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && px + width < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;

				for(int i = 0; i < level.fFaces3.size(); i++){

					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px)  && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							//if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x + height > pz && level.fVert3[level.fFaces3[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
							bool inway = false;
							shadow = false;
							if(shadowBool){	
								for(int v =0;v < level.dFaces.size(); v++){
									
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate){
											shadow = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
										inway = true;
										//break;
										//if(!waitTillRotate){
										//	shadow = true;
										//}
									}
								}
							}
							if(!shadow){
								waitTillRotate = true;
							}
						if(inway == false || shadow){
								player.playerZ = -level.fVert3[level.fFaces3[i]->faces[1]-1]->x;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
							//}	
						}
					}

				}
			}else if(theAngle ==0){
				pz = furthestZ;
				if(mCounter != 1000 && shadowBool){
					
					pz = level.fVert3[level.fFaces3[mCounter]->faces[1]-1]->z;
				}
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height + (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + (width))){
											inway = true;
											//break;
										}			
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + (width))){
											inway = true;
											//break;
										}
									}
								}							
							}	
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < level.fVert3[level.fFaces3[i]->faces[1]-1]->x + width && px + width/2 > level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > level.fVert3[level.fFaces3[i]->faces[1]-1]->x && px + width < level.fVert3[level.fFaces3[i]->faces[1]-1]->x +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
									break;
									
								}
							}
						}
					}
					//std::cout << i << std::endl;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;

				for(int i = 0; i < level.fFaces3.size(); i++){
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25 ){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
										if(!waitTillRotate){
											shadow = true;
										}
									}
								
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + (width))){
										inway = true;
										//break;		
									}							
								}	
							}
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false|| shadow){
								player.playerZ = level.fVert3[level.fFaces3[i]->faces[1]-1]->z;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
						}
					}
				}
			}else if(theAngle ==90){
				pz = lowestX;
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height+ (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){	
											inway = true;
										//break;
										}
									}else{
										if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){	
											inway = true;
										//break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < level.fVert3[level.fFaces3[i]->faces[1]-1]->z + width && px + width/2 > level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
									}else if(px + width > level.fVert3[level.fFaces3[i]->faces[1]-1]->z && px + width < level.fVert3[level.fFaces3[i]->faces[1]-1]->z +(width/3 *2)){
										player.playerX -=0.3;	
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}										
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
									break;
								}
							}
						}
					}
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
				} 
				py  =((player.playerY) *-1) + 1.1;

				if(mCounter != 1000 && shadowBool){
					pz = level.fVert3[level.fFaces3[mCounter]->faces[1]-1]->x;
				}
				for(int i = 0; i < level.fFaces3.size(); i++){

					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
								//if(!shadow){

									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								  
								//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										
										if(!waitTillRotate){
											shadow = true;
										}
									
								}
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.fVert3[level.fFaces3[i]->faces[1]-1]->x && (level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){	
										inway = true;
										//if(!waitTillRotate){
									//		shadow = true;
										//}
										//break;
									}
								}
							}	
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false || shadow){
								
								player.playerZ = level.fVert3[level.fFaces3[i]->faces[1]-1]->x;
								if(inway == false && shadow){
									
									return 0;
								}
								return 1;	
							}						
						}
					}
				}
			}else if(theAngle ==180){
				for(int i = 0; i < level.fFaces3.size(); i++){
					py =((player.playerY)) -1.1 ;
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  -= 0.1;
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px) + width/2){
						if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] +(height + (height)) > py && -level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py + height){
							bool inway = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									if(shadow){
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											inway = true;
											break;
										}
									}else{
										if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
											inway = true;
											break;
										}
									}
								}
							}
							if(!inway){
								if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py ){
									if(px < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x + width && px + width/2 > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width){
										player.playerX +=0.4;
										if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
									}else if(px + width > -level.fVert3[level.fFaces3[i]->faces[1]-1]->x && px + width < -level.fVert3[level.fFaces3[i]->faces[1]-1]->x +(width/3 *2)){
										player.playerX -=0.3;
										if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}										
									}
									level.fVert3[level.fFaces3[i]->faces[1]-1]->y += 0.1;
									break;
								}
							}
						}
					}
					level.fVert3[level.fFaces3[i]->faces[1]-1]->y  += 0.1;
				}
				py  =((player.playerY) *-1) + 1.1;
				if(mCounter != 1000 && shadowBool){
					pz = -level.fVert3[level.fFaces3[mCounter]->faces[1]-1]->z;
				}

				for(int i = 0; i < level.fFaces3.size(); i++){

					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + height > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							bool inway = false;
							shadow = false;
							if(shadowBool){
								for(int v =0;v < level.dFaces.size(); v++){
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
										if(!waitTillRotate){
											shadow = true;
										}
									}
									
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.fVert3[level.fFaces3[i]->faces[1]-1]->z && (-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c] + width)){
										
										inway = true;
									//	if(!waitTillRotate){
									//		shadow = true;
									//	}
										//break;
									}
								}
							}
							if(!shadow){
								waitTillRotate = true;
							}
							if(inway == false || shadow){
								player.playerZ = -level.fVert3[level.fFaces3[i]->faces[1]-1]->z;
								if(inway == false && shadow){
									return 0;
								}
								return 1;
							}
						}
					}

				}
			}
		}
		
		}
	}
	if(!rot){
		float px = player.playerX;
		float py = ((player.playerY) *-1) + 1.1;
		
		float pz;
		float width = 0.595634;
		float height = 0.595634;
		int theAngle = (int) angle;
		if(under1){
			height -= (height*2);
		}
		if(theAngle == 360){
			angle = 0;	
		}else if(theAngle==270){
			if(mCounter != 1000 && shadowBool){
				pz = -level.mVert[level.mFaces[mCounter]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((player.playerY)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.mVert[level.mFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.mVert[level.mFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										//if(-level.dVert[level.dFaces[v]->faces[1]-1]->x > -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > -level.mVert[level.mFaces[i]->faces[1]-1]->z && -level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.mVert[level.mFaces[i]->faces[1]-1]->z  + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y < -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										
									inway = true;
										//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.mVert[level.mFaces[i]->faces[1]-1]->z + width && px + width/2 > -level.mVert[level.mFaces[i]->faces[1]-1]->z +width){
									player.playerX +=0.4;
									if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
									
								}else if(px + width > -level.mVert[level.mFaces[i]->faces[1]-1]->z && px + width < -level.mVert[level.mFaces[i]->faces[1]-1]->z +(width/3 *2)){
									player.playerX -=0.3;	
									if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((player.playerY) *-1) + 1.1;
			for(int i = 0; i < 5; i++){
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + + Coin.increaseC[i] + height  > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}
			for(int i = 0; i < level.mFaces.size(); i++){

				if(-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px)  && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						//if(level.mVert[level.mFaces[i]->faces[1]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
						bool inway = false;
						shadow = false;
						if(shadowBool){	
							for(int v =0;v < level.dFaces.size(); v++){
								
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->z +width > px &&  -level.dVert[level.dFaces[v]->faces[1]-1]->z < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									//if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && px < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate){
										shadow = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->x < -level.mVert[level.mFaces[i]->faces[1]-1]->x && (-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > -level.dVert[level.dFaces[v]->faces[1]-1]->z && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < -level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
									inway = true;
									//break;
									//if(!waitTillRotate){
									//	shadow = true;
									//}
								}
							}
						}
						if(!shadow){
							waitTillRotate = true;
						}
					if(inway == false || shadow){
							player.playerZ = -level.mVert[level.mFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
						//}	
					}
				}

			}
			
			return 0;
		}else if(theAngle ==0){
			pz = furthestZ;
			if(mCounter != 1000 && shadowBool){
				
				pz = level.mVert[level.mFaces[mCounter]->faces[1]-1]->z;
			}
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((player.playerY)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z < level.mVert[level.mFaces[i]->faces[1]-1]->z && (level.mVert[level.mFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.mVert[level.mFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}			
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.mVert[level.mFaces[i]->faces[1]-1]->z && (level.mVert[level.mFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.mVert[level.mFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + (width))){
										inway = true;
										//break;
									}
								}
							}							
						}	
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.mVert[level.mFaces[i]->faces[1]-1]->x + width && px + width/2 > level.mVert[level.mFaces[i]->faces[1]-1]->x +width){
									player.playerX +=0.4;
									if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
									
								}else if(px + width > level.mVert[level.mFaces[i]->faces[1]-1]->x && px + width < level.mVert[level.mFaces[i]->faces[1]-1]->x +(width/3 *2)){
									player.playerX -=0.3;	
									if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
								
							}
						}
					}
				}
				//std::cout << i << std::endl;
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((player.playerY) *-1) + 1.1;
			for(int i = 0; i < 5; i++){
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + height  + Coin.increaseC[i]> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] + height> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + height  + Coin.increaseC[i]> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}
			for(int i = 0; i < level.mFaces.size(); i++){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && px  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && -level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
								
									if(!waitTillRotate){
										shadow = true;
									}
								}
							
								if(level.dVert[level.dFaces[v]->faces[1]-1]->z > level.mVert[level.mFaces[i]->faces[1]-1]->z && (level.mVert[level.mFaces[i]->faces[1]-1]->x +width > level.dVert[level.dFaces[v]->faces[1]-1]->x && level.mVert[level.mFaces[i]->faces[1]-1]->x  < level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + (width) >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + (width))){
									inway = true;
									//break;		
								}							
							}	
						}
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false|| shadow){
							player.playerZ = level.mVert[level.mFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
					}
				}
			}
		}else if(theAngle ==90){
			pz = lowestX;
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((player.playerY)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				
				if(level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height+ (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x > level.mVert[level.mFaces[i]->faces[1]-1]->x && (level.mVert[level.mFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.mVert[level.mFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}else{
									if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.mVert[level.mFaces[i]->faces[1]-1]->x && (level.mVert[level.mFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.mVert[level.mFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(-level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  -level.mVert[level.mFaces[i]->faces[1]-1]->y && -level.dVert[level.dFaces[v]->faces[1]-1]->y <  -level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){	
										inway = true;
									//break;
									}
								}
							}
						}
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < level.mVert[level.mFaces[i]->faces[1]-1]->z + width && px + width/2 > level.mVert[level.mFaces[i]->faces[1]-1]->z +width){
									player.playerX +=0.4;
									if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
										
								}else if(px + width > level.mVert[level.mFaces[i]->faces[1]-1]->z && px + width < level.mVert[level.mFaces[i]->faces[1]-1]->z +(width/3 *2)){
									player.playerX -=0.3;	
									if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			} 
			py  =((player.playerY) *-1) + 1.1;
			for(int i = 0; i < 5; i++){
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i]< py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y +Coin.increaseC[i] + height > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i]< py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z +width > (px) && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + height + Coin.increaseC[i] > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i]< py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}
			if(mCounter != 1000 && shadowBool){
				pz = level.mVert[level.mFaces[mCounter]->faces[1]-1]->x;
			}
			for(int i = 0; i < level.mFaces.size(); i++){

				if(level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
							//if(!shadow){

								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (level.dVert[level.dFaces[v]->faces[1]-1]->z  +width > px && level.dVert[level.dFaces[v]->faces[1]-1]->z < px+ width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
							  
							//	if(level.dVert[level.dFaces[v]->faces[1]-1]->x < pz && (px +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && px < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y <  py+ width)){	
									//if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									
									if(!waitTillRotate){
										shadow = true;
									}
								
							}
								if(level.dVert[level.dFaces[v]->faces[1]-1]->x < level.mVert[level.mFaces[i]->faces[1]-1]->x && (level.mVert[level.mFaces[i]->faces[1]-1]->z +width > level.dVert[level.dFaces[v]->faces[1]-1]->z && level.mVert[level.mFaces[i]->faces[1]-1]->z  < level.dVert[level.dFaces[v]->faces[1]-1]->z + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){	
									inway = true;
									//if(!waitTillRotate){
								//		shadow = true;
									//}
									//break;
								}
							}
						}	
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false || shadow){
							
							player.playerZ = level.mVert[level.mFaces[i]->faces[1]-1]->x;
							if(inway == false && shadow){
								
								return 0;
							}
							return 1;	
						}						
					}
				}
			}
		}else if(theAngle ==180){
			for(int i = 0; i < level.mFaces.size(); i++){
				py =((player.playerY)) -1.1 ;
				level.mVert[level.mFaces[i]->faces[1]-1]->y -= 0.1;
				if(-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px) + width/2){
					if(-level.mVert[level.mFaces[i]->faces[1]-1]->y +(height + (height)) > py && -level.mVert[level.mFaces[i]->faces[1]-1]->y  < py + height){
						bool inway = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								if(shadow){
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z < -level.mVert[level.mFaces[i]->faces[1]-1]->z && (-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}else{
									if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.mVert[level.mFaces[i]->faces[1]-1]->z && (-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
										inway = true;
										break;
									}
								}
							}
						}
						if(!inway){
							if(-level.mVert[level.mFaces[i]->faces[1]-1]->y  < py ){
								if(px < -level.mVert[level.mFaces[i]->faces[1]-1]->x + width && px + width/2 > -level.mVert[level.mFaces[i]->faces[1]-1]->x +width){
									player.playerX +=0.4;
									if(ice){
											player.playerX += player.iceRSlowCounter + 0.1;	player.iceRSlowCounter =0;
											
										}
									
								}else if(px + width > -level.mVert[level.mFaces[i]->faces[1]-1]->x && px + width < -level.mVert[level.mFaces[i]->faces[1]-1]->x +(width/3 *2)){
									player.playerX -=0.3;	
									if(ice){
											player.playerX -= player.iceLSlowCounter + 0.1;	player.iceLSlowCounter =0;
											
										}
								}
								level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
								break;
							}
						}
					}
				}
				level.mVert[level.mFaces[i]->faces[1]-1]->y += 0.1;
			}
			py  =((player.playerY) *-1) + 1.1;
			if(mCounter != 1000 && shadowBool){
				pz = -level.mVert[level.mFaces[mCounter]->faces[1]-1]->z;
			}
			for(int i = 0; i < 5; i++){
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y +height + Coin.increaseC[i]> py && level.mVert[level.mFaces[Coin.coins[i]]->faces[1]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] + height > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[2]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
				if(-level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x +width > (px) && -level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] + height > py && level.mVert[level.mFaces[Coin.coins[i]]->faces[0]-1]->y + Coin.increaseC[i] < py - height + 0.25){
					//	if(level.mVert[level.mFaces[i]->faces[0]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[0]-1]->x < (pz + width/4)  + (width/4*3)){
							Coin.coinsB[i] = true;	
						}
					//}
				}
			}

			for(int i = 0; i < level.mFaces.size(); i++){

				if(-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
					if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
						bool inway = false;
						shadow = false;
						if(shadowBool){
							for(int v =0;v < level.dFaces.size(); v++){
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > pz && (-level.dVert[level.dFaces[v]->faces[1]-1]->x +width > px && -level.dVert[level.dFaces[v]->faces[1]-1]->x < px  + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  py && level.dVert[level.dFaces[v]->faces[1]-1]->y < py + width)){
									if(!waitTillRotate){
										shadow = true;
									}
								}
								
								if(-level.dVert[level.dFaces[v]->faces[1]-1]->z > -level.mVert[level.mFaces[i]->faces[1]-1]->z && (-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > -level.dVert[level.dFaces[v]->faces[1]-1]->x && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < -level.dVert[level.dFaces[v]->faces[1]-1]->x + width )&&(level.dVert[level.dFaces[v]->faces[1]-1]->y + width >  level.mVert[level.mFaces[i]->faces[1]-1]->y && level.dVert[level.dFaces[v]->faces[1]-1]->y <  level.mVert[level.mFaces[i]->faces[1]-1]->y + width)){
									
									inway = true;
								//	if(!waitTillRotate){
								//		shadow = true;
								//	}
									//break;
								}
							}
						}
						if(!shadow){
							waitTillRotate = true;
						}
						if(inway == false || shadow){
							player.playerZ = -level.mVert[level.mFaces[i]->faces[1]-1]->z;
							if(inway == false && shadow){
								return 0;
							}
							return 1;
						}
					}
				}

			}
		}
	}else{

		return 2;
		
	}
	return 0;
}
int mapCollision(level &level, player1 &player1){
	float px = player1.playerX;
	float py = ((player1.playerY) *-1) + 1.1;
	float pz;
	float width = 0.595634;
	float height = 0.595634;
	int theAngle = (int) angle;
	mCounter = 1000;
	fallingNumber = -1;
	if(theAngle == 90){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
					return i;		
				}
			}
		}
		if(falling){
			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + height  + falling1Y[c]> py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}	
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height + falling2Y[c]> py  && level.fVert2[level.fFaces2[i]->faces[1]-1]->y  + falling2Y[c] < py - height + 0.25){
							falling2M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height  + falling3Y[c]> py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
		}
		
	}else if(theAngle ==0){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25 ){
					return i;			
					//	}	
				}
			}
		}
		if(falling){
			
			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + height + falling1Y[c] > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height + falling2Y[c]> py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y  + falling2Y[c] < py - height + 0.25){
							falling2M = true; 
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height  + falling3Y[c]> py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y  + falling3Y[c] < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
		}
	}else if(theAngle == 180){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(-level.mVert[level.mFaces[i]->faces[1]-1]->x +width > (px) && -level.mVert[level.mFaces[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
					return i;		
				}
			}
		}
		if(falling){

			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->x +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] + height > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y + falling1Y[c]  < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->x +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height  + falling2Y[c]> py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y   + falling2Y[c]< py - height + 0.25){
							falling2M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->x +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->x  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height + falling3Y[c]> py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y  + falling3Y[c] < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
		}
	}else if(theAngle == 270){
		falling2M = false;
		falling1M = false;
		falling3M = false;
		for(int i = 0; i < level.mFaces.size(); i++){
			if(-level.mVert[level.mFaces[i]->faces[1]-1]->z +width > (px)  && -level.mVert[level.mFaces[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
				if(level.mVert[level.mFaces[i]->faces[1]-1]->y + height > py && level.mVert[level.mFaces[i]->faces[1]-1]->y  < py - height + 0.25){
					//if(level.mVert[level.mFaces[i]->faces[1]-1]->x + height > pz && level.mVert[level.mFaces[i]->faces[1]-1]->x < (pz + width/4)  + (width/4*3)){
					return i;	
						//}	
				}
			}
		}
		if(falling){
			for(int c = 0;c < falling1Count; c++){
				for(int i = 0; i < level.fFaces1.size(); i++){
					if(-level.fVert1[level.fFaces1[i]->faces[1]-1]->z +width > (px) && -level.fVert1[level.fFaces1[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert1[level.fFaces1[i]->faces[1]-1]->y + height + falling1Y[c] > py && level.fVert1[level.fFaces1[i]->faces[1]-1]->y  + falling1Y[c] < py - height + 0.25){
							falling1M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}		
						}
					}
				}
			}
			for(int c = 0;c < falling2Count; c++){
				for(int i = 0; i < level.fFaces2.size(); i++){
					if(-level.fVert2[level.fFaces2[i]->faces[1]-1]->z +width > (px) && -level.fVert2[level.fFaces2[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert2[level.fFaces2[i]->faces[1]-1]->y + height + falling2Y[c] > py && level.fVert2[level.fFaces2[i]->faces[1]-1]->y  + falling2Y[c] < py - height + 0.25){
							falling2M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}			
						}
					}
				}
			}
			for(int c = 0;c < falling3Count; c++){
				for(int i = 0; i < level.fFaces3.size(); i++){
					if(-level.fVert3[level.fFaces3[i]->faces[1]-1]->z +width > (px) && -level.fVert3[level.fFaces3[i]->faces[1]-1]->z  < (px + width/4)  + (width/4*3)){
						if(level.fVert3[level.fFaces3[i]->faces[1]-1]->y + height + falling3Y[c] > py && level.fVert3[level.fFaces3[i]->faces[1]-1]->y + falling3Y[c]  < py - height + 0.25){
							falling3M = true;
							fallingNumber = c;
							if(!boss){	
								return i;
							}else{
								return 1001;
							}			
						}
					}
				}
			}
		}
	}
	return 1000;
}


int loadBreakable(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open Breakable" << part<< std::endl;
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
			if(tmpy < highestY){
				highestY = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < highestY){
				highestY = tmpy;	
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
	
	bFaces = faces;
	bVert = vertex;
	breakIncrease = (float*) malloc(bFaces.size() * sizeof(float));
	for(int i = 0;i < bFaces.size(); i++){
		breakIncrease[i] = 0;
	}
	//memcpy(&level.mVert, &vertex, vertex.size());
//	std::cout << "here" << std::endl;

//	std::cout << "here" << std::endl;
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	//for(int i=0;i<faces.size();i++)
	//	delete faces[i];
	for(int i=0;i<normals.size();i++)
		delete normals[i];
	//for(int i=0;i<vertex.size();i++)

}
int loadEnemies(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open decoration" << part<< std::endl;
		eVert = vertex;
		eFaces = faces;
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
			if(tmpy < highestY){
				highestY = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < highestY){
				highestY = tmpy;	
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
	eFaces = faces;
	eVert = vertex;
}
int loadBoss(const char* filename){
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open decoration" << part<< std::endl;
		bossVert = vertex;
		bossFaces = faces;
		bossNormals = normals;
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
			if(tmpy < highestY){
				highestY = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < highestY){
				highestY = tmpy;	
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
	bossVert = vertex;
	bossFaces = faces;
	bossNormals = normals;
}





int loadFalling(level &level){
	if(falling){
		
		int done = 0;
		done+= level.falling1(boss);
		falling1Count = 4;
		fallingSpeed = 0.01;
		free(falling1Y);
		falling1Y = (float*) malloc(falling1Count * sizeof(float));
		falling1Y[0] = 24;
		falling1Y[1] = 32;
		falling1Y[2] = 28;
		falling1Y[3] = 8;
		highestFallingY = 32;
		
		done+= level.falling2(boss);
		falling2Count = 4;
		falling2Speed = 0.02;
		free(falling2Y);
		falling2Y = (float*) malloc(falling2Count * sizeof(float));
		falling2Y[0] = 26;
		falling2Y[1] = 36;
		falling2Y[2] = 24;
		falling2Y[3] = 10;
		highestFalling2Y =36;
		
		done+= level.falling3(boss);
		free(falling3Y);
		falling3Count = 4;
		falling3Speed = 0.02;
		falling3Y = (float*) malloc(falling3Count * sizeof(float));
		falling3Y[0] = 22;
		falling3Y[1] = 28;
		falling3Y[2] = 16;
		falling3Y[3] = 4;
		highestFalling3Y = 28;

		fallingNumber = -1;
		if(done ==3){
			return 1;
		}
	}
}
void resetFalling(int counter){
	if(falling){
		if(counter ==1){
			falling1Y[0] = 24;
			falling1Y[1] = 32;
			falling1Y[2] = 20;
			falling1Y[3] = 8;
		}else if(counter ==2){
			falling2Y[0] = 26;
			falling2Y[1] = 36;
			falling2Y[2] = 24;
			falling2Y[3] = 10;
		}else if(counter ==3){
			falling3Y[0] = 22;
			falling3Y[1] = 28;
			falling3Y[2] = 16;
			falling3Y[3] = 4;
		}
	}
}
int loadtrline(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	
	if(!in.is_open()){	//if not opened, exit with -1
		std::cout << "Unable to open Map" << part<< std::endl;
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
			if(tmpy < highestY){
				highestY = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < highestY){
				highestY = tmpy;	
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
	tFaces = faces;
	tVert = vertex;
	return 1;
}



int loadCoin(const char* filename)
{
	std::vector<std::string*> coord;
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
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
			if(tmpy < highestY){
				highestY = tmpy;	
			}
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){	//if normal vector
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			if(tmpy < highestY){
				highestY = tmpy;	
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
	for(int i=0;i<cFaces.size();i++)
		delete cFaces[i];
	for(int i=0;i<cVertex.size();i++)
		delete cVertex[i];
	
	cFaces = faces;
	cVertex = vertex;
//raw
//	std::cout << "here" << std::endl;
	int num;	//the id for the list
	num=glGenLists(2);	//generate a uniqe
	glNewList(num,GL_COMPILE);	//and create it
	
	glBindTexture(GL_TEXTURE_2D, coinT);
	for(int i=0;i<faces.size();i++)	{
		if(faces[i]->four){	//if it's a quad draw a quad
		//	std::cout << "here 1" << std::endl;
			if(i % 2 ==0){
				glBindTexture(GL_TEXTURE_2D, coinT);
				glBegin(GL_QUADS);
					//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
					//I subtract 1 because the index start from 0 in C++
					
					glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
					//draw the faces
					glTexCoord2f(1.0, 1.0);glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
					glTexCoord2f(1.0, 0.0);glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
					glTexCoord2f(0.0, 0.0);glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
					glTexCoord2f(0.0, 1.0);glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
					
					//glTexCoord2f(1.0, 1.0);glVertex3f(level.mVert[level.mFaces[i]->faces[0]-1]->x,level.mVert[level.mFaces[i]->faces[0]-1]->y,level.mVert[level.mFaces[i]->faces[0]-1]->z);
					//	glTexCoord2f(1.0, 0.0);glVertex3f(level.mVert[level.mFaces[i]->faces[1]-1]->x,level.mVert[level.mFaces[i]->faces[1]-1]->y,level.mVert[level.mFaces[i]->faces[1]-1]->z);
					//	glTexCoord2f(0.0, 0.0);glVertex3f(level.mVert[level.mFaces[i]->faces[2]-1]->x,level.mVert[level.mFaces[i]->faces[2]-1]->y,level.mVert[level.mFaces[i]->faces[2]-1]->z);
					//	glTexCoord2f(0.0, 1.0);glVertex3f(level.mVert[level.mFaces[i]->faces[3]-1]->x,level.mVert[level.mFaces[i]->faces[3]-1]->y,level.mVert[level.mFaces[i]->faces[3]-1]->z);
				glEnd();
			}else{
				glBindTexture(GL_TEXTURE_2D, coinTT);
				glBegin(GL_QUADS);
					//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
					//I subtract 1 because the index start from 0 in C++
					
					glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
					//draw the faces
					glTexCoord2f(1.0, 1.0);glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
					glTexCoord2f(1.0, 0.0);glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
					glTexCoord2f(0.0, 0.0);glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
					glTexCoord2f(0.0, 1.0);glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
					
					//glTexCoord2f(1.0, 1.0);glVertex3f(level.mVert[level.mFaces[i]->faces[0]-1]->x,level.mVert[level.mFaces[i]->faces[0]-1]->y,level.mVert[level.mFaces[i]->faces[0]-1]->z);
					//	glTexCoord2f(1.0, 0.0);glVertex3f(level.mVert[level.mFaces[i]->faces[1]-1]->x,level.mVert[level.mFaces[i]->faces[1]-1]->y,level.mVert[level.mFaces[i]->faces[1]-1]->z);
					//	glTexCoord2f(0.0, 0.0);glVertex3f(level.mVert[level.mFaces[i]->faces[2]-1]->x,level.mVert[level.mFaces[i]->faces[2]-1]->y,level.mVert[level.mFaces[i]->faces[2]-1]->z);
					//	glTexCoord2f(0.0, 1.0);glVertex3f(level.mVert[level.mFaces[i]->faces[3]-1]->x,level.mVert[level.mFaces[i]->faces[3]-1]->y,level.mVert[level.mFaces[i]->faces[3]-1]->z);
				glEnd();
			}
		}else{
		//	std::cout << vertex[faces[i]->faces[0]-1]->x << vertex[faces[i]->faces[0]-1]->y << vertex[faces[i]->faces[0]-1]->z << std::endl;
			//std::cout << vertex[faces[i]->faces[1]-1]->x << vertex[faces[i]->faces[1]-1]->y << vertex[faces[i]->faces[1]-1]->z << std::endl;
			//std::cout << vertex[faces[i]->faces[2]-1]->x << vertex[faces[i]->faces[2]-1]->y << vertex[faces[i]->faces[2]-1]->z << std::endl;
			glBegin(GL_TRIANGLES);
				glBindTexture(GL_TEXTURE_2D, coinT);
				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
				glTexCoord2f(0.0, 0.0);glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
				glTexCoord2f(1.0, 0.0);glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
				glTexCoord2f(0.0, 1.0);glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
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

int main()
{
	player1 Player1;
	level levelLoad;
	coin Coin;
	Coin.init();
	bool gFlip = false;
	bool rFlip = false;
	bool bFlip = false;
	levelLoad.partl = part;
	client2 * client = new client2();
	xmlLoad * xLoad = new xmlLoad();
	
	part = xLoad->loadXml();
	int success = client->init();
	//int success = 0;
	if(success ==1){
		online = true;
	}else{
		online = false;
	}
	for(int i =0; i < 10; i++){
		onlineX[i] = -1000;
		onlineY[i] = -1000;
		onlineRotation[i] = 0;
		//onlineMCounter[i] = 1000;
	}
	
	minimap = 0;
	sf::Music music;
	sf::Sound collect;
	sf::SoundBuffer Cbuffer;
	if(!Cbuffer.loadFromFile("Music/collection.ogg")){
		std::cout << "Could not load sound" << std::endl;
	}
	if (!music.openFromFile("Music/music.ogg")){
		std::cout <<"Could not load music"<< std::endl;
	}
	collect.setBuffer(Cbuffer);
	music.setLoop(true);         // make it loop
	music.play();
	highestY = -3.5;
	Player1.playerY += highestY;
	sf::ContextSettings window_settings;
	window_settings.depthBits         = 24; // Request a 24-bit depth buffer
	window_settings.stencilBits       = 8;  // Request a 8 bits stencil buffer
	window_settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
	srand (time(NULL));
	int randnumber = rand() % 250;
	srand (1);
	name = "PLAYER";
	name += std::to_string(randnumber);
	cName = "COOP";
	cName += std::to_string(randnumber);
    // Create the main window
	 sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
	//sf::RenderWindow window(desktop, "SFML works!", sf::Style::None);
    sf::RenderWindow App(desktop, "OpenGL", sf::Style::Resize | sf::Style::Close, window_settings);

	glEnable(GL_DEPTH_TEST);
    // Create a clock for measuring time elapsed
	 
    sf::Clock Clock;
	
	
    //prepare OpenGL sufaces for HSR
	//glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);


    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.f, 1024.f / 768.f, 1.0f, 100);//fov, aspect, zNear, zFar
	char textN[] = "Images/player1.tga";
	char textF[] = "Images/pFire.tga";
	preLoadTexture();
	//cout << "hello" << endl;
	char textS[] = "Images/slime.png";
	char textL[] = "Images/lava.png";
	char textN2[] = "Images/player2.tga";
	char textBoss[] = "Images/coin.png";
	int bossT = loadTexture(textBoss, 15);
	int fireSprite = loadTexture(textF, 19);
	int player2T = loadTexture(textN2, 11);
	char textNO[] = "Images/onlinePlayer.tga";
	int onlineP = loadTexture(textNO, 12);
	int texture = loadTexture(textN, 0);
	char textU1[] = "Images/player1U.tga";
	int pU = loadTexture(textU1, 13);
	char textU2[] = "Images/player2U.tga";
	int pU2 = loadTexture(textU2,14);
	
	//glGenerateMipmap(GL_TEXTURE_2D);
	char text1[] = "Images/title.png";
	char text2[] = "Images/block.png";
	char bText2[] = "Images/block2.png";
	char bText3[] = "Images/block3.png";
	char text3[] = "Images/playerR.tga";
	char text4[] = "Images/gate.png";
	char tree1[] = "Images/Plants/tree1.png";
	char tree2[] = "Images/Plants/tree2.png";
	char tree3[] = "Images/Plants/tree4.png";
	char theCoin[] = "Images/gateSide.png";
	char stone[] = "Images/stone/stone.png";
	char decStoneI[]= "Images/stone/decStone.png";
	char EmptyB[] = "Images/blankB.png";
	int texture2 = loadTexture(text1, 1);
	levelLoad.texture3 = loadTexture(text2, 4);
	treeText1 = loadTexture(tree1,3);
	bool hasCoin = false;
	coinT = loadTexture(text4, 2);
	coinTT = loadTexture(theCoin,18);
	int theRand = (rand() % 3) + 1;
	if(theRand==1){
		levelLoad.texture3 = loadTexture(text2,4);
		treeText1 = loadTexture(tree1, 3);
		levelLoad.texture5 = loadTexture(text2,5);
	}else if(theRand ==2){
		treeText1 = loadTexture(tree2, 3);
		levelLoad.texture3 = loadTexture(bText2, 4);
		levelLoad.texture5 = loadTexture(bText2, 5);
	}else if(theRand ==3){
		treeText1 = loadTexture(tree3, 3);
		levelLoad.texture3 = loadTexture(bText3, 4);
		levelLoad.texture5 = loadTexture(bText3, 5);
	}
	cout << "helloworld" << endl;
	if(part ==3 || part == 6 || part ==8){
		shadowBool = true;
		levelLoad.shadowBooll = true;
		coinT = loadTexture(text4, 2);
		levelLoad.texture3 = loadTexture(stone, 4);
		//treeText1 = loadTexture(bText3, 3);
		levelLoad.texture5 = loadTexture(bText3,5);
	}else{
		shadowBool = false;
		levelLoad.shadowBooll = false;
	}
	
	if(part ==9){
		slime = true;
		std::string sMap = "Objects/misc/slime";
		sMap += std::to_string(part);
		sMap += ".obj";
		char * sArray = (char*)sMap.c_str();
		levelLoad.loadSlime(sArray);
	}else{
		slime = false;
	}
	if(part == 10){
		lava = true;
		std::string lMap = "Objects/misc/lava";
		lMap += std::to_string(part);
		lMap += ".obj";
		char * lArray = (char*)lMap.c_str();
		levelLoad.loadLava(lArray);
	}else{
		lava = false;
	}

	std::string map = "Objects/part";
	map += std::to_string(part);
	map += ".obj";
	char * mapArray = (char*)map.c_str();
	cube = levelLoad.loadMap(mapArray);
	levelLoad.blankTexture = loadTexture(EmptyB,9);
	std::string map2 = "Objects/part";
	int newPart = part+1;
	map2 += std::to_string(newPart);
	map2 += ".obj";
	char * mapArray2 = (char*)map2.c_str();
	cube2 = levelLoad.loadMap2(mapArray2);
	
	decImages = (int*) malloc(3* sizeof(int));
	char dec1[] = "Images/stone/decStone.png";
	char dec2[] = "Images/stone/decStone2.png";
	char dec3[] = "Images/stone/decStone3.png";
	decImages[0] = loadTexture(dec1, 6);
	decImages[1]= loadTexture(dec2, 7);
	decImages[2] = loadTexture(dec3, 8);
	int slimeTexture = loadTexture(textS, 16);
	int lavaTexture = loadTexture(textL, 17);
	if(part ==5){
		falling = true;
		loadFalling(levelLoad);
	}else{
		falling = false;
		falling1Y = (float*) malloc(falling1Count * sizeof(float));
		falling2Y = (float*) malloc(falling1Count * sizeof(float));
		falling3Y = (float*) malloc(falling1Count * sizeof(float));
	}
	/*if(part ==10){
		boss = true;
		std::string bossC = "Objects/Boss/boss";
		bossC += std::to_string(part);
		bossC += ".obj";
		char* bossArray = (char*)bossC.c_str();
		loadBoss(bossArray);
		falling = true;
		loadFalling(levelLoad);
	}else{
		boss = false;
		if(part != 5){
			falling = false;
		}
		falling1Y = (float*) malloc(falling1Count * sizeof(float));
		falling2Y = (float*) malloc(falling1Count * sizeof(float));
		falling3Y = (float*) malloc(falling1Count * sizeof(float));
	}*/
	if(part > 7 && !boss){
		loadEnemies("Objects/Enemies/enemy.obj");
		enemyX = (float*)malloc(sizeof(float) * 3);
		eSpawnZ = (float*) malloc(sizeof(float)*3);
		eSpawnY = (float*) malloc(sizeof(float)*3);
		eSwitched = (bool*) malloc(sizeof(bool)*3);
		for(int i = 0; i < sizeof(enemyX); i++){
				int randCounter = rand() % levelLoad.mFaces.size();
				eSwitched[i] = false;
				eSpawnY[i] = levelLoad.mVert[levelLoad.mFaces[randCounter]->faces[0]-1]->y;
				enemyX[i] = levelLoad.mVert[levelLoad.mFaces[randCounter]->faces[0]-1]->x; 
				eSpawnZ[i] =levelLoad.mVert[levelLoad.mFaces[randCounter]->faces[0]-1]->z; 
		}
		enemies = true;
	}
	
	if(shadowBool){		
		std::string decS = "Objects/decoration";
		decS += std::to_string(part);
		decS += ".obj";
		char * decArray = (char*)decS.c_str();
		decoration = levelLoad.loadDecoration(decArray);
			
		decStone = (int*) malloc(levelLoad.dFaces.size() * sizeof(int));
		for(int i =0;i < levelLoad.dFaces.size(); i++){
			int random = rand() % 3;
			decStone[i]= random;
		}	
	}
	
	if(part == 7){
		trline = true;
		std::string tr = "Objects/Misc/tr";
		tr += std::to_string(part);
		tr += ".obj";
		char * trampArray = (char*) tr.c_str();
		loadtrline(trampArray);
	}else{
		trline = false;
	}
	ice = false;
	if(part ==6){
		ice = true;
		
		char ice[] = "Images/ice.png";
		levelLoad.texture3 = loadTexture(ice,4);
		levelLoad.texture5 = loadTexture(ice,5);
		treeText1 = loadTexture(tree3, 3);
	}
	breaks = false;
	int breakCubes = 0;
	if(part ==7){
		breaks = true;
		std::string breakable = "Objects/break";
		breakable += std::to_string(part);
		breakable += ".obj";
		char * breakArray = (char*)breakable.c_str();
		breakCubes = loadBreakable(breakArray);
	}
	std::string coinS = "Objects/coin";
	coinS += std::to_string(part);
	coinS += ".obj";
	char * coinArray= (char *)coinS.c_str();
	coinX = loadCoin(coinArray);
	// Start game loop
	App.setFramerateLimit(30);
	notLoading = true;
	bool jump_allowed = true;
	bool jump_allowed2 = false;
	int jumpCounter2 = 0;
	int jumpCounter = 0;
	bool left = false;
	bool left2 = false;
	bool right2 = false;
	bool right = false;
	bool jumping = false;
	bool jumping2 = false;
	int* trees = (int *)malloc(levelLoad.mFaces.size() * sizeof(int));
	Coin.coins = (int *)malloc(5 *sizeof(int));
	for(int i  =0;i < levelLoad.mFaces.size(); i++){
		trees[i] = 1000;
	}
	int treeCounter =0;
	furthestZ = -1000;
	for(int i  =0;i < levelLoad.mFaces.size(); i++){
		int random  =rand() % levelLoad.mFaces.size();
		if(random %6 ==0){
			if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z >= furthestZ){
				furthestZ = levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z;
				trees[treeCounter] = random;
				treeCounter++;
			}
		}
	}
	for(int v = 0; v < 5; v++){
			Coin.increaseC[v] = 0;
			int random = rand() % levelLoad.mFaces.size();
			//std::cout << random << levelLoad.mFaces.size() << std::endl;
			bool found = true;
			while(random % 6 !=0){
				random = rand() % levelLoad.mFaces.size();
			}
			while(found){
				found = false;
				float width = 0.7;
				float height = 0.7;
				for(int i = 0; i < levelLoad.mFaces.size(); i++){	
					//if(i != random){

						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(found){
							i = levelLoad.mFaces.size()+1;
							Coin.increaseC[v] += 0.1;
							//std::cout << Coin.increaseC[v] << std::endl;
						}
					//}
				}
			}
			Coin.coins[v] = random;
		}
		for(int i = 0; i < 5; i++){
			Coin.coinsB[i] = false;
			Coin.coinsPlayed[i] = false;
		}
		coinM = levelLoad.loadCoins();
	for(int v = 0; v < 5; v++){
			Coin.increaseC[v] = 0;
			int random = rand() % levelLoad.mFaces.size();
			//std::cout << random << levelLoad.mFaces.size() << std::endl;
			bool found = true;
			while(random % 6 !=0){
				random = rand() % levelLoad.mFaces.size();
			}
			while(found){
				found = false;
				float width = 0.7;
				float height = 0.7;
				for(int i = 0; i < levelLoad.mFaces.size(); i++){	
					//if(i != random){

						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(found){
							i = levelLoad.mFaces.size()+1;
							Coin.increaseC[v] += 0.1;
							//std::cout << Coin.increaseC[v] << std::endl;
						}
					//}
				}
			}
			Coin.coins[v] = random;
		}
	int theStart = 0;
	
	coinM = levelLoad.loadCoins();
	float coinR = 0;
	bool rising = false;
	float gravityCounter =0.01;
	float gravityCounter2 = 0.01;
	float jumpingCounter2 = 0.01;
	float jumpingCounter = 0.01;
	float lightCounterR = 1;
	float lightCounterG = 1;
	float lightCounterB = 1;
	float lightRl = 1;
	float lightGl = 1;
	float lightBl = 1;
	bool lightFlip= false;
	playerY2 = -3.5;
	int hittingSlime = 0;
	int hittingSlime2 = 0;
	int hittingLava = 0;
	int hittingLava2 = 0;
	float lavaCounter2 = 0;
	float lavaCounter = 0;
	
	while (App.isOpen())
    {
		if(theRand ==1){
			//glColor4f(1,1,0.1,1);
			lightCounterR = 1;
			lightCounterG = 1;
			lightCounterB = 0.1;
		}else if(theRand ==2){
			//glColor4f(0.5,0.2,0.5,1);
			lightCounterR = 0.5;
			lightCounterG = 0.2;
			lightCounterB = 0.5;
		}else if(theRand ==3){
			//glColor4f(0,0.5,1,1);
			lightCounterR = 0;
			lightCounterG = 0.5;
			lightCounterB = 1;
		}
		
		while(notLoading){
			if(!App.isOpen()){
				notLoading = false;	
			}
			coinR+=0.5;
			if(enemies){
				eRotation += 2;
			}
			ground = collision(levelLoad, Coin, Player1);//Player1.collision(levelLoad,Coin, angle, mCounter, shadowBool, falling, falling1Count, falling2Count, falling3Count, ice, rot, shadow, waitTillRotate, falling1Y, falling2Y, falling3Y, under1);
			
			if(coop){
				ground2 = collision2(levelLoad, Coin);
			}
			if(lava){
				hittingLava2 = lavaCollision2(levelLoad);
				hittingLava = lavaCollisions(levelLoad, Player1);
				if(hittingLava2 ==1){
					ground2 = 1;
					if(lavaCounter2 < 2){
						playerY2 += 0.01;
						lavaCounter2 += 0.1;
					}else{
						playerX2 = 0;
						playerY2 = 0;
						lavaCounter2 = 0;
					}
				}
				if(hittingLava ==1){
					ground = 1;
					if(lavaCounter < 2){
						Player1.playerY += 0.01;
						lavaCounter += 0.1;
					}else{
						dying = true;
						lavaCounter = 0;
					}
				}
			}
			if(slime){
				hittingSlime = slimeCollisions(levelLoad, Player1);
				hittingSlime2 = slimeCollision2(levelLoad);
				if(hittingSlime ==1){
					ground = 1;
					speed = 0.05;
				}else{
					speed = 0.1;
				}
				if(hittingSlime2 ==1){
					ground2 = 1;
					speed2 = 0.05;
				}else{
					speed2 = 0.1;
				}
			}
			//cout << ground2 << endl;
			//if there are enemies and the, use the movement function and check if hit by enemy
			if(enemies){
				enemyMovement(levelLoad);
				bool hitByEnemy = enemyCollisions(Player1);
				if(onFire){
					hitByEnemy = false;
				}
				if(hitByEnemy){ //if enemy then reset the players' variables 
					dying = true;
					if(breaks){
						std::string breakable = "Objects/break";
						breakable += std::to_string(part);
						breakable += ".obj";
						char * breakArray = (char*)breakable.c_str();
						breakCubes = loadBreakable(breakArray);
					}
					/*
					if(ice){
						Player1.playerX -= iceLSlowCounter + 0.1;	iceLSlowCounter =0;
						Player1.playerX += iceRSlowCounter + 0.1;	iceRSlowCounter =0;
					}*/
					gravityCounter = 0.01;
				}
			}
			if(breaks && ground != 1){ //if break is allowed, check whether player is colliding (also comes into main collisions to stop falling 
				ground = breakTerrainCollision(Player1);
			}
			if(breaks && ground2 != 1){
				ground2 = breakTerrainCollision2();
			}
			if(ground2 ==1){ // if player 2 is hitting something reset player 2 jumping mechanic and stop player2 falling
				if(hittingLava2 != 1){
					jump_allowed2 = true;
				}				
				jumpCounter2 = 0;
				gravityCounter2 = 0.01;
				jumpingCounter2 =0.01;
			}
			if(ground ==1){ //if player is hitting something, reset the jump mechanic and stop player falling
				if(hittingLava != 1){
					jump_allowed = true;
				}				
				jumpCounter = 0;
				gravityCounter = 0.01;
				jumpingCounter =0.01;
				if(!rot){
					rising = false;
				}
				//under1 = true;
			}
			if(!hasCoin){ //has coin is actually when the player collides x,y,z with the exit
				int CoinCounter = 0;
				for(int i = 0; i < 5; i++){
					if(Coin.coinsB[i]){ // if coin is found + of out 5
						CoinCounter++;
					}
				}
				//cout << CoinCounter << e
				if(CoinCounter == 5){
					hasCoin= coinCollisions(Player1, levelLoad);//check against finish when all 5 coins are found
				}
			}else{
				if(!online){ //dont change map unless server has told you to finish
					notLoading = false;
				}else{
					char fin[] = "Finished"; //let server know your client has "finished"
					client->sendMessage(fin);
					hasCoin = false;
				}
			}
			sf::Event Event;
			if(theStart ==1){ //start == 1 means in game loop
				float oldX;
				float oldX2;
				if(!rot && minimap ==0){
					if(ice){
						//decay ice 
						if(Player1.iceRSlowCounter > 0){
							Player1.iceRSlowCounter -= 0.005;
						}
						if(Player1.iceLSlowCounter > 0){
							Player1.iceLSlowCounter -= 0.005;
						}
						if(coop){
							if(iceRSlowCounter2 > 0){
							iceRSlowCounter2 -= 0.005;
							}
							if(iceLSlowCounter2 > 0){
								iceLSlowCounter2 -= 0.005;
							}
						}
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){ // n is a special power when the gravity can be changed
						if(boss){
							under1 = true;
						}
					}else{
						if(boss){
							under1 = false;
						}
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){ //o is used to skip the level
						notLoading = false;
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
						if(part >= 9){
							if(fireAllowed){
								onFire = true;
							}
						}
					}
					if(onFire){
						//cout << "on fire" << endl;
						if(fireCounter < 75){
							fireCounter++;
						}else{
							onFire = false;
							fireAllowed = false;
							fireCounter = 0;
						}
					}else{
						if(!fireAllowed){
							if(fireCoolDown < 150){
								fireCoolDown++;
							}else{
								fireCoolDown = 0;
								fireAllowed = true;
							}
						}
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ // a is left
						left = true;
						if(left_allowed){
							Player1.playerX -= speed;
							oldX = Player1.playerX;
							if(ice){//if ice the algorithm is to compare against traction of other direction, giving a smooth curve from direction to direction
								if(Player1.iceLSlowCounter > 0){
									Player1.iceLSlowCounter -= 0.06;
									Player1.iceRSlowCounter -= Player1.iceLSlowCounter;
								}
								Player1.playerX -= Player1.iceRSlowCounter;
								if(Player1.iceRSlowCounter < terminalIceSpeed && jump_allowed){
									Player1.iceRSlowCounter += 0.06;
								}
							}
						}
					}else{
						left = false; // left is not left unless the key is down

					}
					if(coop){ //mimic the player2 left mechanic and bind to Keyboard_left (we don't want to break anything)
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
							left2 = true; //player2 has it's own variables
							playerX2 -= speed2;
							oldX2 = playerX2;
							if(ice){
								if(iceLSlowCounter2 > 0){
									iceLSlowCounter2 -= 0.06;
									iceRSlowCounter2 -= iceLSlowCounter2;
								}
								playerX2 -= iceRSlowCounter2;
								if(iceRSlowCounter2 < terminalIceSpeed && jump_allowed2){
									iceRSlowCounter2 += 0.06;
								}
							}
						}else{
							left2 = false;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ //player2 is going to move right with keyboard bind (keyboard_right)
							right2 = true;
							playerX2 += speed2;
							oldX2 = playerX2;
							if(ice && !left2){
								//if(jump_allowed){
								if(iceRSlowCounter2 > 0){
									iceRSlowCounter2 -= 0.06;
									iceLSlowCounter2 -= iceRSlowCounter2;
								}
								//}
								playerX2 += iceLSlowCounter2;
								if(iceLSlowCounter2 < terminalIceSpeed && jump_allowed2){
									iceLSlowCounter2 += 0.06;
								}
							}
						}else{
							right2 = false;
						}	
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
						right = true;
						if(right_allowed){
							Player1.playerX += speed;
							oldX = Player1.playerX;
							if(ice){ //decay ice movement in the reverse way for a smooth curve from direction to direction
								//if(jump_allowed){
								if(Player1.iceRSlowCounter > 0){
									Player1.iceRSlowCounter -= 0.06;
									Player1.iceLSlowCounter -= Player1.iceRSlowCounter;
								}
								//}
								Player1.playerX += Player1.iceLSlowCounter; // add ice counter/s to generice movement variable
								if(Player1.iceLSlowCounter < terminalIceSpeed && jump_allowed){
									Player1.iceLSlowCounter += 0.06;
								}
							}
						}
					}else{
						right = false; //right is right when D is pressed down
					}
					if(ice){
						//Naturally decay ice without keyboard input to stop certain bugs and having low friction in a jmup (when not colliding)
						if(Player1.iceRSlowCounter > 0 && oldX > Player1.playerX){
							Player1.playerX -= Player1.iceRSlowCounter;
							Player1.iceRSlowCounter -= 0.01;
						}else if(Player1.iceLSlowCounter > 0 && oldX < Player1.playerX){
							Player1.playerX += Player1.iceLSlowCounter;
							Player1.iceLSlowCounter -= 0.01;
						}
						
						if(iceRSlowCounter2 > 0 && oldX2 > playerX2){
							playerX2 -= iceRSlowCounter2;
							iceRSlowCounter2 -= 0.01;
						}else if(iceLSlowCounter2 > 0 && oldX2 < playerX2){
							playerX2 += iceLSlowCounter2;
							iceLSlowCounter2 -= 0.01;
						}
					}
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){ //Keyboard M for mini map
				minimap = true; 
			}else{
				minimap = false;
			}
			if(titleTimer < 100 && theStart != 1){
				titleTimer++;
			}else{
				if(!onceShown){
					theStart = 0;
					titleTimer = 0;
					if(part ==9){
						char textC[] = "Images/Cutscenes/fire.png";
						texture2 = loadTexture(textC, 1);
						theStart = 0;
					}else if(part ==2){
						char textC[] = "Images/Cutscenes/coop.png";
						texture2 = loadTexture(textC, 1);
						theStart = 0;
					}else if(part ==3){
						char textC[] = "Images/Cutscenes/minimap.png";
						texture2 = loadTexture(textC, 1);
						theStart = 0;
					}else if(part ==1){
						char textC[] = "Images/Cutscenes/rotate.png";
						texture2 = loadTexture(textC, 1);
						theStart = 0;
					}else{
						char textC[] = "Images/Cutscenes/title2.png";
						texture2 = loadTexture(textC, 1);
						theStart = 0;
					}
					onceShown = true;
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //Keyboard Space for player1 to jump
				if(jump_allowed){
					jumping = true;	
				}
				if(theStart ==0){ //space is also used to start the game
						
					theStart = 1;
					char textA[] = "Images/Cutscenes/background.png";
					texture2 = loadTexture(textA, 1);
				}
			//	std:cout << Player1.playerY << std::endl;
			}else{// you are not jumping when the space bar is key upped
				jumping = false;
				jump_allowed = false;
				jumpingCounter = 0.01;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){ //c is used on the start menu to toggle cooperative or not
				//if(theStart ==0){
					collect.play();
					if(coop == 0){
						coop = 1;
					}else{
						coop = 0;
					}
				//}
			}
			if(coop){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //up is used to jump with player2 (coop player)
					if(jump_allowed2){
						jumping2 = true;
						
					}
				}else{
					jumping2 = false;
					jump_allowed2 = false;
					jumpingCounter2 = 0.01;
				}
			}
			if(trline){//if there is a trampoline in the map
				if(trampCollisions(Player1, levelLoad)){ //check if player is on trampoline
					ground = 1;
					jumping = true;
					if(ground ==1){ //set everything as is colliding with ground
						jump_allowed = true;	
						jumpCounter = 0;
						gravityCounter = 0.01;
						if(part ==7){
							jumpingCounter =-0.50; //increase the players jump height!
						}else{
							jumpingCounter = -0.25;
						}
						if(!rot){
							rising = false;
						}
					}
				}
				if(trampCollisions2(levelLoad)){ //check if player 2 is on trampoline
					ground2 = 1;
					jumping2 = true;
					if(ground2 ==1){
						jump_allowed2 = true;	
						jumpCounter2 = 0;
						gravityCounter2 = 0.01;
						if(part ==7){
							jumpingCounter2 =-0.50; //greatly increase the players' jump height
						}else{
							jumpingCounter2 = -0.25;
						}
						if(!rot){
							rising = false;
						}
					}
				}
			}
			if(jumping && !rising){
				if(!under1){ //normal jumping
					Player1.playerY -= (speed*3) - jumpingCounter; //to create a curve minus an increasing variable to the increase when jumping
					if(jumpCounter >= speed*150){
						//jump_allowed = false;	
						jumping = false;
					}
				}else{ //jumping when having the anti gravity mechanic (opposite)
					Player1.playerY += (speed*3) - jumpingCounter;
					if(jumpCounter >= speed*150){
						//jump_allowed = false;	
						jumping = false;
					}
				}
				jump_allowed = false; //player cannot jump again
				jumpCounter++; //the jump counters will increase while the player is in the air
				jumpingCounter += 0.02;
			}else if(ground ==0){
				if(!under1){
					Player1.playerY += speed + gravityCounter;
					if(gravityCounter < 0.35){
						gravityCounter += 0.01;
					}
				}else{
					Player1.playerY -= speed + gravityCounter;
					if(gravityCounter < 0.35){
						gravityCounter += 0.01;
					}
				}
			}
			if(coop){ //mimic jumping for player 2 the same as player 1, we don't want to break anything (using player 2 variables)
				if(jumping2){
					if(!under1){
						playerY2 -= ((speed2)*3) - (jumpingCounter2);
						if(jumpingCounter2 >= speed2*150){
							jumping2 = false;
						}
					}else{
						playerY2 += (speed2*3) - jumpingCounter2;
						if(jumpCounter2 >= speed2*150){
							//jump_allowed = false;	
							jumping2 = false;
						}
					}
					jump_allowed2 = false;
					jumpCounter2++;
					jumpingCounter2 +=0.02;
				}else if(ground2 ==0){
					if(!under1){
						playerY2 += speed2 + gravityCounter2;
						if(gravityCounter2 < 0.35){
							gravityCounter2 += 0.01;
						}
					}else{
						playerY2 -= speed2 + gravityCounter2;
						if(gravityCounter2 < 0.35){
							gravityCounter2 += 0.01;
						}
					}
					//cout << playerY2 << endl;
				}
				if(playerY2 > 10){ //10 is the lowest ground before dying, everything is higher than 10
					playerY2 = -3.5; //reset player2 
					gravityCounter2 = 0.01;
				}
			}
			if(Player1.playerY > 10){ //10 is the lowest ground before dying, everything is higher than 10
				dying = true;
				if(breaks){ //breakable objects should be reset
					std::string breakable = "Objects/break";
					breakable += std::to_string(part);
					breakable += ".obj";
					char * breakArray = (char*)breakable.c_str();
					breakCubes = loadBreakable(breakArray);
				}
				if(ice){
					//reset ice
					Player1.playerX -= Player1.iceLSlowCounter + 0.1;	Player1.iceLSlowCounter =0;
					Player1.playerX += Player1.iceRSlowCounter + 0.1;	Player1.iceRSlowCounter =0;
				}
				
				gravityCounter = 0.01;
			}
			while (App.pollEvent(Event)) //game loop!
			{
				// Close window : exit
				if (Event.type == sf::Event::Closed)
					App.close();

				// Escape key : exit
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
					App.close();

				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R)){ //R is to rotate the player
					
					if(online){
						if(rotateAllowed){
							rot= true;
							char rotateIt[] = "ROTATE";
							client->sendMessage(rotateIt); //send the message asking for a gloal rotation
							rotateAllowed = false;
							rotateCounter = 0;
						}
					//if(shadowBool){
					}else{
						rot = true;
					}
					mCounter = mapCollision(levelLoad, Player1); // get the counter of map as to where the player 1 is (helps with visual rotation)
					for(int i = 0; i < onlineCounter; i++){
						//onlineMCounter[i] = mapOnlineCollision(onlineX[i], onlineY[i]);
					}
					if(coop){
						mCounter2 = mapCollision2(levelLoad); // get the counter of map as to where the player 1 is (helps with rotation)
					}
					//std::cout << mCounter2 << std::endl;
					//}
					if(!rising){ //This helps to stop rising, for a infinite climb with rotation... Player is incremented up ONCE; to get off rails
						Player1.playerY -= speed;
						rising = true;
					}
				}
				

			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        //clear the buffer cache 
			//Prepare for drawing

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity(); // start a new matrix

			if(rot){ //rotation mechanic, visually 
				angle+= rotateSpeed; //increase rotation
				waitTillRotate = false; //wait till rotate means cant change from shadow to front until new rotation
				waitTillRotate2 = false;
				shadow = false;
				shadow2 = false;
					if((int)angle > 0 && (int) angle<= 90){ //when turning to 90
						if(mCounter != 1000 && mCounter != 1001){ //1001 and 1000 are empty counters, to show one has not been set
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									
									Player1.playerX = levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z; //visually set the player to it's counter
								}else{
									if(falling1M){ //visually set the player to it's counter on falling
										
										Player1.playerX = levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[0]-1]->z;
									}else if(falling2M){
										Player1.playerX = levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[0]-1]->z;
									}else if(falling3M){
										Player1.playerX = levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[0]-1]->z;
									}
								}
							}else{
								Player1.playerX = levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z; //visually set the player to it's counter
							}
						}
					}else if((int)angle > 90 && (int) angle <= 180){ //when turning to 180
						if(mCounter != 1000 && mCounter != 1001){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									Player1.playerX = -levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x;
								}else{
									if(falling1M){
										Player1.playerX = -levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[0]-1]->x;
									}else if(falling2M){
										Player1.playerX = -levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[0]-1]->x;
									}else if(falling3M){
										Player1.playerX = -levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[0]-1]->x;
									}
								}
							}else{	
								Player1.playerX = -levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x + 0.45;
							}
						}
					}else if((int) angle > 180 && (int) angle <= 270){ //when turning to 270
						if(mCounter != 1000 && mCounter != 1001){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									Player1.playerX = -levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z;
								}else{
									if(falling1M){
										Player1.playerX = -levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[0]-1]->z;
									}else if(falling2M){
										Player1.playerX = -levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[0]-1]->z;
									}else if(falling3M){
										Player1.playerX = -levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[0]-1]->z;
									}
								}
							}else{
								Player1.playerX = -levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z + 0.45;
							}
						
						}
					}else if((int)angle > 270 && (int) angle <=360){ //when turning to 360
						if(mCounter != 1000 && mCounter != 1001){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									Player1.playerX = levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x;
								}else{
									if(falling1M){
										Player1.playerX = levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[0]-1]->x;
									}else if(falling2M){
										Player1.playerX = levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[0]-1]->x;
									}else if(falling3M){
										Player1.playerX = levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[0]-1]->x;
									}
								}
							}else{
								Player1.playerX = levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x+ 0.45;
							}

						}
					}
					if(coop){ //do extactly the same to coop player 
						if((int)angle > 0 && (int) angle<= 90){
						if(mCounter2 != 1000){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									
									playerX2 = levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->z;
								}else{
									if(falling1M){
										
										playerX2 = levelLoad.fVert1[levelLoad.fFaces1[mCounter2]->faces[0]-1]->z;
									}else if(falling2M){
										playerX2 = levelLoad.fVert2[levelLoad.fFaces2[mCounter2]->faces[0]-1]->z;
									}else if(falling3M){
										playerX2 = levelLoad.fVert3[levelLoad.fFaces3[mCounter2]->faces[0]-1]->z;
									}
								}
							}else{
								playerX2 = levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->z;
							}
						}
					}else if((int)angle > 90 && (int) angle <= 180){
						if(mCounter2 != 1000){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									playerX2 = -levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->x;
								}else{
									if(falling1M){
										Player1.playerX = -levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[0]-1]->x;
									}else if(falling2M){
										playerX2 = -levelLoad.fVert2[levelLoad.fFaces2[mCounter2]->faces[0]-1]->x;
									}else if(falling3M){
										playerX2 = -levelLoad.fVert3[levelLoad.fFaces3[mCounter2]->faces[0]-1]->x;
									}
								}
							}else{	
								playerX2 = -levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->x + 0.45;
							}
						}
					}else if((int) angle > 180 && (int) angle <= 270){
						if(mCounter2 != 1000){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									playerX2 = -levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->z;
								}else{
									if(falling1M){
										playerX2 = -levelLoad.fVert1[levelLoad.fFaces1[mCounter2]->faces[0]-1]->z;
									}else if(falling2M){
										playerX2 = -levelLoad.fVert2[levelLoad.fFaces2[mCounter2]->faces[0]-1]->z;
									}else if(falling3M){
										playerX2 = -levelLoad.fVert3[levelLoad.fFaces3[mCounter2]->faces[0]-1]->z;
									}
								}
							}else{
								playerX2 = -levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->z + 0.45;
							}
						
						}
					}else if((int)angle > 270 && (int) angle <=360){
						if(mCounter2 != 1000){
							if(falling){
								if(!falling1M && !falling2M && !falling3M){
									playerX2 = levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->x;
								}else{
									if(falling1M){
										playerX2 = levelLoad.fVert1[levelLoad.fFaces1[mCounter2]->faces[0]-1]->x;
									}else if(falling2M){
										playerX2 = levelLoad.fVert2[levelLoad.fFaces2[mCounter2]->faces[0]-1]->x;
									}else if(falling3M){
										playerX2 = levelLoad.fVert3[levelLoad.fFaces3[mCounter2]->faces[0]-1]->x;
									}
								}
							}else{
								playerX2 = levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[0]-1]->x+ 0.45;
							}

						}
					}
					}
				int theAngle = (int) angle;
				if(theAngle % 90 ==0){ //stop the rotation every 90 degree turn
					rot = false;
				}
			}
			if(theStart ==0){ //if game isn't started
				
				glTranslatef(0,0,-7);
				
				glTranslatef(0,Player1.playerY,0); //get original player coordinates
				//std::cout << Player1.playerY << std::endl;
				glTranslatef(-Player1.playerX,0,0);
				glPushMatrix();

				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture2); //texture 2 is the title, print it
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-50.f, -50.f, -90.f);//close to the camera
				glTexCoord2f(0.0, 1.0); glVertex3f(-50.f,  50.f, -90.f);
				glTexCoord2f(1.0, 1.0); glVertex3f( 50.f,  50.f, -90.f);
				glTexCoord2f(1.0, 0.0); glVertex3f( 50.f, -50.f, -90.f);
				glEnd();
				glFlush();
				glDisable(GL_TEXTURE_2D);
				/*glBegin(GL_QUADS); 
					glColor3f(1, 1, 1);
					glVertex3f(20.0f, 20.0f, 0.0f); 
					glVertex3f(20.0f, -20.0f, 0.0f); 
					glVertex3f(-20.0f, -20.0f, 0.0f); 
					glVertex3f(-20.0f, 20.0f, 0.0f); 
				glEnd();*/ 

				// Finally, display rendered frame on screen

				App.display();
				
			}else if(theStart ==1){

				
				
				glColor4f(lightCounterR,lightCounterG,lightCounterB,1);
				if(!lightFlip){
					
					if(lightCounterR >= 0){
						lightCounterR -= 0.001;
					}else{
						rFlip = true;
					}
					if(lightCounterG >=0){
						lightCounterG -= 0.001;
					}else{
						gFlip = true;
					}
					if(lightCounterB >= 0){
						lightCounterB -= 0.001;
					}else{
						bFlip = true;
					}
					if(gFlip && rFlip && bFlip){
						lightFlip = true;
						bFlip = false;
						gFlip = false;
						rFlip = false;
						lightBl = (rand() % 100);// /100;
						lightRl = (rand() % 100);// /100;
						lightGl = (rand() % 100);// /100;
						cout << lightBl << " : " << lightGl << " : " << lightRl << endl;
						lightBl = lightBl /100;
						lightRl = lightRl /100;
						lightGl = lightGl /100;
						cout << lightBl << " : " << lightGl << " : " << lightRl << endl;
					}
				}else if(lightFlip){
						if(lightCounterR <= lightRl){
							lightCounterR += 0.001;
						}else{
							rFlip = true;
						}
						if(lightCounterG <=	lightGl){
							lightCounterG += 0.001;
						}else{
							gFlip = true;
						}
						if(lightCounterB <= lightBl){
							lightCounterB += 0.001;
						}else{
							bFlip = true;
						}
						if(gFlip && rFlip && bFlip){
							lightFlip = false;
							bFlip = false;
							gFlip = false;
							rFlip = false;
							//cout << "flip lol" << endl;
						}
					}
				
								
			glTranslatef(0,0,-5);
			glTranslatef(0,Player1.playerY,0);
			//std::cout << Player1.playerY << std::endl;
			glTranslatef(-Player1.playerX,0,0);
			
			if(boss && !rot){
				
				int mCount = mapCollision(levelLoad, Player1); //don't get the actuall counter, because this is a prediction
				if(mCount ==1001){
					dying = true;
					if(breaks){ //RESET breakable
						std::string breakable = "Objects/break";
						breakable += std::to_string(part);
						breakable += ".obj";
						char * breakArray = (char*)breakable.c_str();
						breakCubes = loadBreakable(breakArray);
					}
					if(ice){ //reset ice
						Player1.playerX -= Player1.iceLSlowCounter + 0.1;	Player1.iceLSlowCounter =0;
						Player1.playerX += Player1.iceRSlowCounter + 0.1;	Player1.iceRSlowCounter =0;
					}
					gravityCounter = 0.01;
					}
					if(coop){
						int mCount2 = mapCollision2(levelLoad);
						if(mCount2 ==1001){
							playerY2 = -3.5; //reset player	
							playerY2 =0;
							playerX2 = 0;
							if(ice){
								playerX2 -= iceLSlowCounter2 + 0.1;	iceLSlowCounter2 =0;
								playerX2 += iceRSlowCounter2 + 0.1;	iceRSlowCounter2 =0;
							}
							gravityCounter2 = 0.01;
						}
					}
				}
			

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture2); //texture 2 has changed to background
	
			glRotatef(180, 0.f, 0.f, 1.f);
			indent += 0.1; //indent adds movement to the background
				if(indent >= 100){
					indent = 0;
					
				}
				//print 3 background, the amount needed to change seemlessly to a "infinite background"
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(-50.f + indent, -50.f, -90.f);
				glTexCoord2f(0.0, 1.0); glVertex3f(-50.f + indent,  50.f, -90.f);
				glTexCoord2f(1.0, 1.0); glVertex3f( 50.f + indent,  50.f, -90.f);
				glTexCoord2f(1.0, 0.0);   glVertex3f( 50.f + indent, -50.f, -90.f);
				glEnd();
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(-150.f + indent, -50.f, -90.f);
				glTexCoord2f(0.0, 1.0); glVertex3f(-150.f + indent,  50.f, -90.f);
				glTexCoord2f(1.0, 1.0); glVertex3f( -50.f + indent,  50.f, -90.f);
				glTexCoord2f(1.0, 0.0);   glVertex3f( -50.f + indent, -50.f, -90.f);
				glEnd();
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(-250.f + indent, -50.f, -90.f);
				glTexCoord2f(0.0, 1.0); glVertex3f(-250.f + indent,  50.f, -90.f);
				glTexCoord2f(1.0, 1.0); glVertex3f( -150.f + indent,  50.f, -90.f);
				glTexCoord2f(1.0, 0.0);   glVertex3f( -150.f + indent, -50.f, -90.f);
				glEnd();
			glRotatef(-180, 0.f, 0.f, 1.f);	
			if(mCounter != 1000 && mCounter != 1001){
				if(!shadowBool){
					if(angle == 0 || angle ==180){
						glTranslatef(0,0, -levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z);
					}else{
						glTranslatef(0,0, (levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z));
					}
				}
			}
			glPushMatrix();

			//Draw a cube
			glEnable(GL_LIGHTING); //enable basic lighting on the objects
			glEnable(GL_LIGHT0);
			glPopMatrix();

			GLfloat	lightpos3[4] = { 0.f, 10.f, 0.f, 1.0 }; 
			glLightfv(GL_LIGHT0, GL_POSITION, lightpos3);
			//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		   
		   //evidence of the first test
		   /*
		   glBegin(GL_QUADS);//draw some squares
				glColor3f(0,1,1);
				glVertex3f(-50.f, -50.f, -50.f);
				glVertex3f(-50.f,  50.f, -50.f);
				glVertex3f( 50.f,  50.f, -50.f);
				glVertex3f( 50.f, -50.f, -50.f);

				glColor3f(0,0,1);
				glVertex3f(-50.f, -50.f, 50.f);
				glVertex3f(-50.f,  50.f, 50.f);
				glVertex3f( 50.f,  50.f, 50.f);
				glVertex3f( 50.f, -50.f, 50.f);

				glColor3f(1,0,1);
				glVertex3f(-50.f, -50.f, -50.f);
				glVertex3f(-50.f,  50.f, -50.f);
				glVertex3f(-50.f,  50.f,  50.f);
				glVertex3f(-50.f, -50.f,  50.f);

				glColor3f(0,1,0);
				glVertex3f(50.f, -50.f, -50.f);
				glVertex3f(50.f,  50.f, -50.f);
				glVertex3f(50.f,  50.f,  50.f);
				glVertex3f(50.f, -50.f,  50.f);

				glColor3f(1,1,0);
				glVertex3f(-50.f, -50.f,  50.f);
				glVertex3f(-50.f, -50.f, -50.f);
				glVertex3f( 50.f, -50.f, -50.f);
				glVertex3f( 50.f, -50.f,  50.f);

				glColor3f(1,0,0);
				glVertex3f(-50.f, 50.f,  50.f);
				glVertex3f(-50.f, 50.f, -50.f);
				glVertex3f( 50.f, 50.f, -50.f);
				glVertex3f( 50.f, 50.f,  50.f);
			glEnd();
			*/

			//glPushMatrix();
			//glRotatef(angle * 30, 0.f, 1.f, 0.f);
			glTranslatef(0,0,-10); // translate -10 on the Z coord
			
			if(minimap ==0){
					//if(mCounter < levelLoad.mFaces.size()-5){
					//	glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x,0,levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z -0.1);
					//}
					/*if((int)angle > 0 && (int) angle<= 90){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x,0,levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z);
						}
					}else if((int)angle > 90 && (int) angle <= 180){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z,0,levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x);
						}
					}else if((int) angle > 180 && (int) angle <= 270){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x,0,-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z);
						}
					}else if((int)angle > 270 && (int) angle <=360){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(-levelLoad.mVert[-levelLoad.mFaces[mCounter]->faces[0]-1]->z,0,-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x);
						}
					}*/
					glTranslatef(0, -.5f,-9);
					
					glRotatef(angle, 0.f, 1.f, 0.f);
					//set the matrix to appropriate coord for painting
					/*
					if((int)angle > 0 && (int) angle <= 90){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x,0,-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z);
						}
					}else if((int)angle > 90 && (int) angle <= 180){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z,0,-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x);
						}
					}else if((int) angle > 180 && (int) angle <= 270){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x,0,levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z);
						}
					}else if((int)angle > 270 && (int) angle <=360){
						if(mCounter < levelLoad.mFaces.size()-5){
							glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->z,0,levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[0]-1]->x);
						}
					}*/
				//}
			}else if(minimap ==1){ //see minimap
				glTranslatef(0.f, 0.f, -50.f); //-50 to fit everything in the scene
				glRotatef(90, 1.f, 0.f, 0.f); //rotate so it's top down
				
			}
			if(!rot && !shadow){
				if(shadowBool){
					mCounter = mapCollision(levelLoad, Player1);
					if(mCounter != 1000 && mCounter != 1001 && !shadowBool){
						//pz = levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->x;
					}
				}
			}
			if(!rot){
				for(int i = 0; i < onlineCounter; i++){
					//onlineMCounter[i] = mapOnlineCollision(onlineX[i], onlineY[i]);
				}
			}
			if(!rot && !shadow2){
				if(shadowBool){
					mCounter2 = mapCollision2(levelLoad);
					if(mCounter2 != 1000 && shadowBool){
						//pz = levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->x;
					}
				}
			}
			if(minimap ==0){ //if ingame
			//glBindTexture(GL_TEXTURE_2D, texture3);
				if(lava){
					for(int i=0;i<levelLoad.lFaces.size();i++){	
					
						if(levelLoad.lFaces[i]->four){	//if it's a quad draw a quad

								//char path[] = "Images/block3.png";
								//treeText1= loadTexture(path,3);
								glBindTexture(GL_TEXTURE_2D, lavaTexture);
								glBegin(GL_QUADS);
									//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
									//I subtract 1 because the index start from 0 in C++
									
									glNormal3f(levelLoad.lNormals[levelLoad.lFaces[i]->facenum-1]->x,levelLoad.lNormals[levelLoad.lFaces[i]->facenum-1]->y,levelLoad.lNormals[levelLoad.lFaces[i]->facenum-1]->z);
									//draw the faces
									glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[0]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[0]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[0]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[1]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[1]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[1]-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[2]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[2]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[2]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[3]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[3]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[3]-1]->z);
								glEnd();	
								//char path2[] = "Images/Plants/tree1.png";
								//treeText1 = loadTexture(path2, 3);
								glBindTexture(GL_TEXTURE_2D, lavaTexture);
							
						}else{
						//	std::cout << cVertex[levelLoad.lFaces[i]->faces[0]-1]->x << cVertex[levelLoad.lFaces[i]->faces[0]-1]->y << cVertex[levelLoad.lFaces[i]->faces[0]-1]->z << std::endl;
							//std::cout << vertex[levelLoad.lFaces[i]->faces[1]-1]->x << vertex[levelLoad.lFaces[i]->faces[1]-1]->y << vertex[levelLoad.lFaces[i]->faces[1]-1]->z << std::endl;
							//std::cout << vertex[levelLoad.lFaces[i]->faces[2]-1]->x << vertex[levelLoad.lFaces[i]->faces[2]-1]->y << vertex[levelLoad.lFaces[i]->faces[2]-1]->z << std::endl;
							glBegin(GL_TRIANGLES);
								glBindTexture(GL_TEXTURE_2D, lavaTexture);
								glNormal3f(levelLoad.lNormals[levelLoad.lFaces[i]->facenum-1]->x,levelLoad.lNormals[levelLoad.lFaces[i]->facenum-1]->y,levelLoad.lNormals[levelLoad.lFaces[i]->facenum-1]->z);
								glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[0]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[0]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[1]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[1]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[1]-1]->z);
								glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.lVert[levelLoad.lFaces[i]->faces[2]-1]->x,levelLoad.lVert[levelLoad.lFaces[i]->faces[2]-1]->y,levelLoad.lVert[levelLoad.lFaces[i]->faces[2]-1]->z);
							glEnd();
						}
					}
				}
				if(slime){
					for(int i=0;i<levelLoad.sFaces.size();i++){	
					
						if(levelLoad.sFaces[i]->four){	//if it's a quad draw a quad

								//char path[] = "Images/block3.png";
								//treeText1= loadTexture(path,3);
								glBindTexture(GL_TEXTURE_2D, slimeTexture);
								glBegin(GL_QUADS);
									//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
									//I subtract 1 because the index start from 0 in C++
									
									glNormal3f(levelLoad.sNormals[levelLoad.sFaces[i]->facenum-1]->x,levelLoad.sNormals[levelLoad.sFaces[i]->facenum-1]->y,levelLoad.sNormals[levelLoad.sFaces[i]->facenum-1]->z);
									//draw the faces
									glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[0]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[0]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[0]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[1]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[1]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[1]-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[2]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[2]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[2]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[3]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[3]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[3]-1]->z);
								glEnd();	
								//char path2[] = "Images/Plants/tree1.png";
								//treeText1 = loadTexture(path2, 3);
								glBindTexture(GL_TEXTURE_2D, slimeTexture);
							
						}else{
						//	std::cout << cVertex[levelLoad.sFaces[i]->faces[0]-1]->x << cVertex[levelLoad.sFaces[i]->faces[0]-1]->y << cVertex[levelLoad.sFaces[i]->faces[0]-1]->z << std::endl;
							//std::cout << vertex[levelLoad.sFaces[i]->faces[1]-1]->x << vertex[levelLoad.sFaces[i]->faces[1]-1]->y << vertex[levelLoad.sFaces[i]->faces[1]-1]->z << std::endl;
							//std::cout << vertex[levelLoad.sFaces[i]->faces[2]-1]->x << vertex[levelLoad.sFaces[i]->faces[2]-1]->y << vertex[levelLoad.sFaces[i]->faces[2]-1]->z << std::endl;
							glBegin(GL_TRIANGLES);
								glBindTexture(GL_TEXTURE_2D, slimeTexture);
								glNormal3f(levelLoad.sNormals[levelLoad.sFaces[i]->facenum-1]->x,levelLoad.sNormals[levelLoad.sFaces[i]->facenum-1]->y,levelLoad.sNormals[levelLoad.sFaces[i]->facenum-1]->z);
								glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[0]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[0]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[1]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[1]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[1]-1]->z);
								glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.sVert[levelLoad.sFaces[i]->faces[2]-1]->x,levelLoad.sVert[levelLoad.sFaces[i]->faces[2]-1]->y,levelLoad.sVert[levelLoad.sFaces[i]->faces[2]-1]->z);
							glEnd();
						}
					}
				}
				if(falling && !rot){ //if falling and not rotating
					
					if(!boss){
						fallingCountY += fallingSpeed;
						fallingCount2Y += falling2Speed;
						fallingCount3Y += falling3Speed; //add falling speed
						//std::cout << fallingSpeed << std::endl;
						for(int i = 0;i < falling1Count; i++){
							if(falling1Y[i] >= 0){
								falling1Y[i] -= fallingSpeed;
							}
						}
						for(int i = 0;i < falling2Count; i++){
							if(falling2Y[i] >= 0){
								falling2Y[i] -= falling2Speed;
							}
						}
						for(int i = 0;i < falling3Count; i++){
							if(falling3Y[i] >= 0){
								falling3Y[i] -= falling3Speed;
							}
						}
						if(fallingCountY >= highestFallingY){
						//	std::cout << "refreshing" << std::endl;
							resetFalling(1);
							fallingCountY =0;
						}else if(fallingCount2Y >=highestFalling2Y){
							resetFalling(2);
							fallingCount2Y =0;
						}else if(fallingCount3Y >=highestFalling3Y){
							resetFalling(3);
							fallingCount3Y = 0;
						}
					}else{
						fallingCountY += fallingSpeed;
						fallingCount2Y += falling2Speed;
						fallingCount3Y += falling3Speed;
						//std::cout << fallingCount2Y << std::endl;
						if(!bFallingFlip){
							for(int i = 0;i < falling1Count; i++){
								if(falling1Y[i] >= 5){
									falling1Y[i] -= fallingSpeed;
									//cout << falling1Y[i] << endl;
								}else{
									if(bFallingCounter != 1001){
										bFallingFlip = true;
										bFallingCounter = i;
									}
									//cout << "fucking come on" << endl;
								}
							}
							for(int i = 0;i < falling2Count; i++){
								if(falling2Y[i] >= 0){
									falling2Y[i] -= falling2Speed;
								}else{
									//bFallingFlip = false;
								}
							}
							for(int i = 0;i < falling3Count; i++){
								if(falling3Y[i] >= 0){
									falling3Y[i] -= falling3Speed;
								}else{
									//bFallingFlip = false;
								}
							}
						}else{
							for(int i = 0;i < falling1Count; i++){
								//if(falling1Y[i] <= 2){
								if(falling1Y[bFallingCounter] <= 6.5){
									falling1Y[i] += fallingSpeed;
								}else{
									bFallingFlip = false;
									bFallingCounter = 1001;
								}
								//cout << falling1Y[i] << endl;
								
								//}else{
								//	bFallingFlip = true;
								//}
							}
							for(int i = 0;i < falling2Count; i++){
								if(falling2Y[i] <= 6.5){
									falling2Y[i] += falling2Speed;
								}else{
									//bFallingFlip = true;
								}
							}
							for(int i = 0;i < falling3Count; i++){
								if(falling3Y[i] <= 6.5){
									falling3Y[i] += falling3Speed;
								}else{
									//bFallingFlip = true;
								}
							}
						}
						if(fallingCountY >= highestFallingY){
						//	std::cout << "refreshing" << std::endl;
							resetFalling(1);
							fallingCountY =0;
							bFallingCounter = 1000;
						}else if(fallingCount2Y >=highestFalling2Y){
							resetFalling(2);
							fallingCount2Y =0;
						}else if(fallingCount3Y >=highestFalling3Y){
							resetFalling(3);
							fallingCount3Y = 0;
						}
					}
				}
				glCallList(cube);
				
				if(breaks){
					glColor3f(1,1,1);
					glBindTexture(GL_TEXTURE_2D, levelLoad.blankTexture);
					for(int i=0;i<bFaces.size();i++){	
					
						if(bFaces[i]->four){	//if it's a quad draw a quad

								
								//char path[] = "Images/block3.png";
								//treeText1= loadTexture(path,3);
								//glBindTexture(GL_TEXTURE_2D, levelLoad.texture5);
								glBegin(GL_QUADS);
									//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
									//I subtract 1 because the index start from 0 in C++
									
									//glNormal3f(normals[bFaces[i]->facenum-1]->x,normals[bFaces[i]->facenum-1]->y ,normals[bFaces[i]->facenum-1]->z);
									//draw the faces
									glTexCoord2f(1.0, 1.0);glVertex3f(bVert[bFaces[i]->faces[0]-1]->x,bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[0]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(bVert[bFaces[i]->faces[1]-1]->x,bVert[bFaces[i]->faces[1]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[1]-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(bVert[bFaces[i]->faces[2]-1]->x,bVert[bFaces[i]->faces[2]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[2]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(bVert[bFaces[i]->faces[3]-1]->x,bVert[bFaces[i]->faces[3]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[3]-1]->z);
								glEnd();	
								//char path2[] = "Images/Plants/tree1.png";
								//treeText1 = loadTexture(path2, 3);
								//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
							
						}else{
						//	std::cout << cVertex[levelLoad.mFaces[i]->faces[0]-1]->x << cVertex[levelLoad.mFaces[i]->faces[0]-1]->y << cVertex[levelLoad.mFaces[i]->faces[0]-1]->z << std::endl;
							//std::cout << vertex[levelLoad.mFaces[i]->faces[1]-1]->x << vertex[levelLoad.mFaces[i]->faces[1]-1]->y << vertex[levelLoad.mFaces[i]->faces[1]-1]->z << std::endl;
							//std::cout << vertex[levelLoad.mFaces[i]->faces[2]-1]->x << vertex[levelLoad.mFaces[i]->faces[2]-1]->y << vertex[levelLoad.mFaces[i]->faces[2]-1]->z << std::endl;
							glBegin(GL_TRIANGLES);
								//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
								//glNormal3f(normals[bFaces[i]->facenum-1]->x,normals[bFaces[i]->facenum-1]->y ,normals[bFaces[i]->facenum-1]->z);
								glTexCoord2f(0.0, 0.0);glVertex3f(bVert[bFaces[i]->faces[0]-1]->x,bVert[bFaces[i]->faces[0]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(bVert[bFaces[i]->faces[1]-1]->x,bVert[bFaces[i]->faces[1]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[1]-1]->z);
								glTexCoord2f(0.0, 1.0);glVertex3f(bVert[bFaces[i]->faces[2]-1]->x,bVert[bFaces[i]->faces[2]-1]->y + breakIncrease[i],bVert[bFaces[i]->faces[2]-1]->z);
							glEnd();
						}
					}
				}
				glTranslatef(10.f,0,-25.f);
				//glDisable(GL_TEXTURE_2D);
				glCallList(cube2);
				//glEnable(GL_TEXTURE_2D);
				
				glTranslatef(-10.f,0,25.f);
				if(falling){
					
					if(boss){
						glBindTexture(GL_TEXTURE_2D, bossT);
					}else{
						glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
					}
					for(int v= 0; v < falling1Count; v++){
						for(int i=0;i<levelLoad.fFaces1.size();i++){	
							
							if(levelLoad.fFaces1[i]->four){	//if it's a quad draw a quad

								if((i+1) % 6 != 0 || part <3){
								//	std::cout << "here 1" << std::endl;
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[levelLoad.fFaces1[i]->facenum-1]->x,normals[levelLoad.fFaces1[i]->facenum-1]->y,normals[levelLoad.fFaces1[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[3]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[3]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[3]-1]->z);
									glEnd();
								}else{
									
									//char path[] = "Images/block3.png";
									//treeText1= loadTexture(path,3);
									if(boss){
										glBindTexture(GL_TEXTURE_2D, bossT);
									}else{
										glBindTexture(GL_TEXTURE_2D, levelLoad.texture5);
									}
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[levelLoad.fFaces1[i]->facenum-1]->x,normals[levelLoad.fFaces1[i]->facenum-1]->y,normals[levelLoad.fFaces1[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[3]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[3]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[3]-1]->z);
									glEnd();	
									//char path2[] = "Images/Plants/tree1.png";
									//treeText1 = loadTexture(path2, 3);
								//	glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
								}
							}else{
							//	std::cout << cVertex[levelLoad.fFaces1[i]->faces[0]-1]->x << cVertex[levelLoad.fFaces1[i]->faces[0]-1]->y << cVertex[levelLoad.fFaces1[i]->faces[0]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.fFaces1[i]->faces[1]-1]->x << vertex[levelLoad.fFaces1[i]->faces[1]-1]->y << vertex[levelLoad.fFaces1[i]->faces[1]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.fFaces1[i]->faces[2]-1]->x << vertex[levelLoad.fFaces1[i]->faces[2]-1]->y << vertex[levelLoad.fFaces1[i]->faces[2]-1]->z << std::endl;
								glBegin(GL_TRIANGLES);
									if(boss){
										glBindTexture(GL_TEXTURE_2D, bossT);
									}else{
										glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
									}
									//glNormal3f(normals[levelLoad.fFaces1[i]->facenum-1]->x,normals[levelLoad.fFaces1[i]->facenum-1]->y,normals[levelLoad.fFaces1[i]->facenum-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[0]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[1]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->x,levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->y + falling1Y[v],levelLoad.fVert1[levelLoad.fFaces1[i]->faces[2]-1]->z);
								glEnd();
							}
						}
					}
					for(int v = 0; v < falling2Count; v++){
						for(int i=0;i<levelLoad.fFaces2.size();i++){	
						
						
							if(levelLoad.fFaces2[i]->four){	//if it's a quad draw a quad
								if((i+1) % 6 != 0 || part <3){
								//	std::cout << "here 1" << std::endl;
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[levelLoad.fFaces2[i]->facenum-1]->x,normals[levelLoad.fFaces2[i]->facenum-1]->y,normals[levelLoad.fFaces2[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[3]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[3]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[3]-1]->z);
									glEnd();
								}else{
									
									//char path[] = "Images/block3.png";
									//treeText1= loadTexture(path,3);
									if(boss){
										glBindTexture(GL_TEXTURE_2D, bossT);
									}else{
										glBindTexture(GL_TEXTURE_2D, levelLoad.texture5);
									}
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[levelLoad.fFaces2[i]->facenum-1]->x,normals[levelLoad.fFaces2[i]->facenum-1]->y,normals[levelLoad.fFaces2[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[3]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[3]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[3]-1]->z);
									glEnd();	
									//char path2[] = "Images/Plants/tree1.png";
									//treeText1 = loadTexture(path2, 3);
									//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
								}
							}else{
							//	std::cout << cVertex[levelLoad.fFaces2[i]->faces[0]-1]->x << cVertex[levelLoad.fFaces2[i]->faces[0]-1]->y << cVertex[levelLoad.fFaces2[i]->faces[0]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.fFaces2[i]->faces[1]-1]->x << vertex[levelLoad.fFaces2[i]->faces[1]-1]->y << vertex[levelLoad.fFaces2[i]->faces[1]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.fFaces2[i]->faces[2]-1]->x << vertex[levelLoad.fFaces2[i]->faces[2]-1]->y << vertex[levelLoad.fFaces2[i]->faces[2]-1]->z << std::endl;
	
								glBegin(GL_TRIANGLES);
									if(boss){
										glBindTexture(GL_TEXTURE_2D, bossT);
									}else{
										glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
									}
									///\glNormal3f(normals[levelLoad.fFaces2[i]->facenum-1]->x,normals[levelLoad.fFaces2[i]->facenum-1]->y,normals[levelLoad.fFaces2[i]->facenum-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[0]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[1]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->x,levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->y + falling2Y[v],levelLoad.fVert2[levelLoad.fFaces2[i]->faces[2]-1]->z);
								glEnd();
							}
						}
					}
					for(int v =0; v < falling3Count; v++){
						for(int i=0;i<levelLoad.fFaces3.size();i++){	
							
						
							if(levelLoad.fFaces3[i]->four){	//if it's a quad draw a quad
								if((i+1) % 6 != 0 || part <3){
								//	std::cout << "here 1" << std::endl;
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[levelLoad.fFaces3[i]->facenum-1]->x,normals[levelLoad.fFaces3[i]->facenum-1]->y,normals[levelLoad.fFaces3[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[3]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[3]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[3]-1]->z);
									glEnd();
								}else{
									
									//char path[] = "Images/block3.png";
									//treeText1= loadTexture(path,3);
									if(boss){
										glBindTexture(GL_TEXTURE_2D, bossT);
									}else{
										glBindTexture(GL_TEXTURE_2D, levelLoad.texture5);
									}
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[levelLoad.fFaces3[i]->facenum-1]->x,normals[levelLoad.fFaces3[i]->facenum-1]->y,normals[levelLoad.fFaces3[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[3]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[3]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[3]-1]->z);
									glEnd();	
									//char path2[] = "Images/Plants/tree1.png";
									//treeText1 = loadTexture(path2, 3);
									//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
								}
							}else{
							//	std::cout << cVertex[levelLoad.fFaces3[i]->faces[0]-1]->x << cVertex[levelLoad.fFaces3[i]->faces[0]-1]->y << cVertex[levelLoad.fFaces3[i]->faces[0]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.fFaces3[i]->faces[1]-1]->x << vertex[levelLoad.fFaces3[i]->faces[1]-1]->y << vertex[levelLoad.fFaces3[i]->faces[1]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.fFaces3[i]->faces[2]-1]->x << vertex[levelLoad.fFaces3[i]->faces[2]-1]->y << vertex[levelLoad.fFaces3[i]->faces[2]-1]->z << std::endl;
								glBegin(GL_TRIANGLES);
									if(boss){
										glBindTexture(GL_TEXTURE_2D, bossT);
									}else{
										glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
									}
									///glNormal3f(normals[levelLoad.fFaces3[i]->facenum-1]->x,normals[levelLoad.fFaces3[i]->facenum-1]->y,normals[levelLoad.fFaces3[i]->facenum-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[0]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[1]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->x,levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->y + falling3Y[v],levelLoad.fVert3[levelLoad.fFaces3[i]->faces[2]-1]->z);
								glEnd();
							}
						}
					}
				}
				if(boss){
					if(boss){
						glBindTexture(GL_TEXTURE_2D, bossT);
					}
					if(bDirectionFlip){
						bossYSkew+= 0.01;
						if(bossYSkew > 1){
							bDirectionFlip = false;
						}
					}else{
						bossYSkew -= 0.01;
						if(bossYSkew < 0){
							bDirectionFlip = true;
						}
					}
					for(int i = 0; i < bossFaces.size(); i++){
						if(bossFaces[i]->four){
							glBegin(GL_QUADS);
								glNormal3f(bossNormals[bossFaces[i]->facenum-1]->x,bossNormals[bossFaces[i]->facenum-1]->y,bossNormals[bossFaces[i]->facenum-1]->z);
								glTexCoord2f(0.0, 0.0);glVertex3f(bossVert[bossFaces[i]->faces[0]-1]->x,bossVert[bossFaces[i]->faces[0]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(bossVert[bossFaces[i]->faces[1]-1]->x,bossVert[bossFaces[i]->faces[1]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[1]-1]->z);
								glTexCoord2f(1.0, 1.0);glVertex3f(bossVert[bossFaces[i]->faces[2]-1]->x,bossVert[bossFaces[i]->faces[2]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[2]-1]->z);
								glTexCoord2f(0.0, 1.0);glVertex3f(bossVert[bossFaces[i]->faces[3]-1]->x,bossVert[bossFaces[i]->faces[3]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[3]-1]->z);
							glEnd();
						}else{
							glBegin(GL_TRIANGLES);
								glNormal3f(bossNormals[bossFaces[i]->facenum-1]->x,bossNormals[bossFaces[i]->facenum-1]->y,bossNormals[bossFaces[i]->facenum-1]->z);
										
								glTexCoord2f(0.0, 0.0);glVertex3f(bossVert[bossFaces[i]->faces[0]-1]->x,bossVert[bossFaces[i]->faces[0]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(bossVert[bossFaces[i]->faces[1]-1]->x,bossVert[bossFaces[i]->faces[1]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[1]-1]->z);
								glTexCoord2f(1.0, 1.0);glVertex3f(bossVert[bossFaces[i]->faces[2]-1]->x,bossVert[bossFaces[i]->faces[2]-1]->y + bossYSkew,bossVert[bossFaces[i]->faces[2]-1]->z);
							//glTexCoord2f(0.0, 1.0);glVertex3f(bossVert[bossFaces[i]->faces[3]-1]->x,bossVert[bossFaces[i]->faces[3]-1]->y,bossVert[bossFaces[i]->faces[3]-1]->z);
							glEnd();
						}
					}
				}
					if(shadowBool){
						//if(rot){
							for(int i=0;i<levelLoad.dFaces.size();i++){	
								glBindTexture(GL_TEXTURE_2D, decImages[decStone[i]]);
								//glBindTexture(GL_TEXTURE_2D, decImages[decStone[i]]);
								if(levelLoad.dFaces[i]->four){	//if it's a quad draw a quad
							
								//	std::cout << "here 1" << std::endl;
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										glNormal3f(levelLoad.dNormals[levelLoad.dFaces[i]->facenum-1]->x,levelLoad.dNormals[levelLoad.dFaces[i]->facenum-1]->y,levelLoad.dNormals[levelLoad.dFaces[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[0]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[0]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[1]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[1]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[1]-1]->z);
										glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[2]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[2]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[2]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[3]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[3]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[3]-1]->z);
									glEnd();
								}else{
								//	std::cout << cVertex[levelLoad.mFaces[i]->faces[0]-1]->x << cVertex[levelLoad.mFaces[i]->faces[0]-1]->y << cVertex[levelLoad.mFaces[i]->faces[0]-1]->z << std::endl;
									//std::cout << vertex[levelLoad.mFaces[i]->faces[1]-1]->x << vertex[levelLoad.mFaces[i]->faces[1]-1]->y << vertex[levelLoad.mFaces[i]->faces[1]-1]->z << std::endl;
									//std::cout << vertex[levelLoad.mFaces[i]->faces[2]-1]->x << vertex[levelLoad.mFaces[i]->faces[2]-1]->y << vertex[levelLoad.mFaces[i]->faces[2]-1]->z << std::endl;
									glBegin(GL_TRIANGLES);
										glNormal3f(levelLoad.dNormals[levelLoad.dFaces[i]->facenum-1]->x,levelLoad.dNormals[levelLoad.dFaces[i]->facenum-1]->y,levelLoad.dNormals[levelLoad.dFaces[i]->facenum-1]->z);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[0]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[0]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[0]-1]->z);
										glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[1]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[1]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[1]-1]->z);
										glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.dVert[levelLoad.dFaces[i]->faces[2]-1]->x,levelLoad.dVert[levelLoad.dFaces[i]->faces[2]-1]->y,levelLoad.dVert[levelLoad.dFaces[i]->faces[2]-1]->z);
									glEnd();
								}
							}
						}	
				for(int v = 0; v < 5; v++){
					//glPopMatrix();
					if(!Coin.coinsB[v]){
						glPushMatrix();
						float Tz = levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z;
						float Ty = levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v];
						float Tx = levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x;
						glTranslatef(levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x, 0, levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
						glRotatef(coinR,0,1,0);
						glTranslatef(-levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x, 0, -levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
						for(int i=0;i<levelLoad.coinF.size();i++)	{
							
							if(levelLoad.coinF[i]->four){	//if it's a quad draw a quad
							//	std::cout << "here 1" << std::endl;
							glBindTexture(GL_TEXTURE_2D, coinT);
								glBegin(GL_QUADS);
								//glColor3f(1.0f,0.5f,0.0f);
									//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
									//I subtract 1 because the index start from 0 in C++
									glNormal3f(levelLoad.coinN[levelLoad.coinF[i]->facenum-1]->x,levelLoad.coinN[levelLoad.coinF[i]->facenum-1]->y,levelLoad.coinN[levelLoad.coinF[i]->facenum-1]->z);
									//glNormal3f(normals[levelLoad.coinF[i]->facenum-1]->x,normals[levelLoad.coinF[i]->facenum-1]->y,normals[levelLoad.coinF[i]->facenum-1]->z);
									//draw the faces
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[0]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[0]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[0]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[1]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[1]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[1]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[2]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[2]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[2]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
									glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[3]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[3]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[3]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
								glEnd();
							}else{
							//	std::cout << vertex[faces[i]->faces[0]-1]->x << vertex[faces[i]->faces[0]-1]->y << vertex[faces[i]->faces[0]-1]->z << std::endl;
								//std::cout << vertex[faces[i]->faces[1]-1]->x << vertex[faces[i]->faces[1]-1]->y << vertex[faces[i]->faces[1]-1]->z << std::endl;
								//std::cout << vertex[faces[i]->faces[2]-1]->x << vertex[faces[i]->faces[2]-1]->y << vertex[faces[i]->faces[2]-1]->z << std::endl;
								glBindTexture(GL_TEXTURE_2D, coinT);
								glBegin(GL_TRIANGLES);
									glNormal3f(levelLoad.coinN[levelLoad.coinF[i]->facenum-1]->x,levelLoad.coinN[levelLoad.coinF[i]->facenum-1]->y,levelLoad.coinN[levelLoad.coinF[i]->facenum-1]->z);
									//draw the faces
									glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[0]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[0]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[0]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
									glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[1]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[1]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[1]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
									glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.coinV[levelLoad.coinF[i]->faces[2]-1]->x + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->x,levelLoad.coinV[levelLoad.coinF[i]->faces[2]-1]->y + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->y + Coin.increaseC[v],levelLoad.coinV[levelLoad.coinF[i]->faces[2]-1]->z + levelLoad.mVert[levelLoad.mFaces[Coin.coins[v]]->faces[1]-1]->z);
								glEnd();
							}
						
						}
						glPopMatrix();
					}else if(Coin.coinsB[v]){
						if(!Coin.coinsPlayed[v]){
							Coin.coinsPlayed[v] = true;
							collect.play();
						}
					}
					//glPopMatrix();
				}
				if(trline){
					glBindTexture(GL_TEXTURE_2D, coinT);
					for(int i=0;i<tFaces.size();i++)	{
						if(tFaces[i]->four){	//if it's a quad draw a quad
						//	std::cout << "here 1" << std::endl;
								glBindTexture(GL_TEXTURE_2D, coinT);
								glBegin(GL_QUADS);
									//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
									//I subtract 1 because the index start from 0 in C++
									
								//glNormal3f(normals[tFaces[i]->facenum-1]->x,normals[tFaces[i]->facenum-1]->y,normals[tFaces[i]->facenum-1]->z);
									//draw the faces
								glTexCoord2f(1.0, 1.0);glVertex3f(tVert[tFaces[i]->faces[0]-1]->x,tVert[tFaces[i]->faces[0]-1]->y,tVert[tFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(tVert[tFaces[i]->faces[1]-1]->x,tVert[tFaces[i]->faces[1]-1]->y,tVert[tFaces[i]->faces[1]-1]->z);
								glTexCoord2f(0.0, 0.0);glVertex3f(tVert[tFaces[i]->faces[2]-1]->x,tVert[tFaces[i]->faces[2]-1]->y,tVert[tFaces[i]->faces[2]-1]->z);
								glTexCoord2f(0.0, 1.0);glVertex3f(tVert[tFaces[i]->faces[3]-1]->x,tVert[tFaces[i]->faces[3]-1]->y,tVert[tFaces[i]->faces[3]-1]->z);
									
									//glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->z);
									//	glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z);
									//	glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->z);
									//	glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[3]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[3]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[3]-1]->z);
							glEnd();
							
						}else{
						//	std::cout << tVert[tFaces[i]->faces[0]-1]->x << tVert[tFaces[i]->faces[0]-1]->y << tVert[tFaces[i]->faces[0]-1]->z << std::endl;
							//std::cout << tVert[tFaces[i]->faces[1]-1]->x << tVert[tFaces[i]->faces[1]-1]->y << tVert[tFaces[i]->faces[1]-1]->z << std::endl;
							//std::cout << tVert[tFaces[i]->faces[2]-1]->x << tVert[tFaces[i]->faces[2]-1]->y << tVert[tFaces[i]->faces[2]-1]->z << std::endl;
							glBegin(GL_TRIANGLES);
								glBindTexture(GL_TEXTURE_2D, coinT);
								//glNormal3f(normals[tFaces[i]->facenum-1]->x,normals[tFaces[i]->facenum-1]->y,normals[tFaces[i]->facenum-1]->z);
								glTexCoord2f(0.0, 0.0);glVertex3f(tVert[tFaces[i]->faces[0]-1]->x,tVert[tFaces[i]->faces[0]-1]->y,tVert[tFaces[i]->faces[0]-1]->z);
								glTexCoord2f(1.0, 0.0);glVertex3f(tVert[tFaces[i]->faces[1]-1]->x,tVert[tFaces[i]->faces[1]-1]->y,tVert[tFaces[i]->faces[1]-1]->z);
								glTexCoord2f(0.0, 1.0);glVertex3f(tVert[tFaces[i]->faces[2]-1]->x,tVert[tFaces[i]->faces[2]-1]->y,tVert[tFaces[i]->faces[2]-1]->z);
							glEnd();
						}
					}
				}
				if(enemies){
					glColor3f(1,1,1);
					glBindTexture(GL_TEXTURE_2D, levelLoad.blankTexture);
					
					for(int x = 0; x < sizeof(enemyX); x++){
						glPushMatrix();
						glTranslatef(eVert[eFaces[x]->faces[1]-1]->x + enemyX[x],eVert[eFaces[x]->faces[0]-1]->y + eSpawnY[x], eVert[eFaces[x]->faces[1]-1]->z + eSpawnZ[x]);
						glRotatef(eRotation,1,0,0);
						glTranslatef(-(eVert[eFaces[x]->faces[1]-1]->x +enemyX[x]), -(eVert[eFaces[x]->faces[0]-1]->y  + eSpawnY[x]), -(eVert[eFaces[x]->faces[1]-1]->z + eSpawnZ[x]));
						for(int i=0;i<eFaces.size();i++){	

							if(eFaces[i]->four){	//if it's a quad draw a quad

									
									//char path[] = "Images/block3.png";
									//treeText1= loadTexture(path,3);
									//glBindTexture(GL_TEXTURE_2D, levelLoad.texture5);
									glBegin(GL_QUADS);
										//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
										//I subtract 1 because the index start from 0 in C++
										
										//glNormal3f(normals[bFaces[i]->facenum-1]->x,normals[bFaces[i]->facenum-1]->y ,normals[bFaces[i]->facenum-1]->z);
										//draw the faces
										glTexCoord2f(1.0, 1.0);glVertex3f(eVert[eFaces[i]->faces[0]-1]->x + enemyX[x],eVert[eFaces[i]->faces[0]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[0]-1]->z+ eSpawnZ[x]);
										glTexCoord2f(1.0, 0.0);glVertex3f(eVert[eFaces[i]->faces[1]-1]->x + enemyX[x],eVert[eFaces[i]->faces[1]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[1]-1]->z+ eSpawnZ[x]);
										glTexCoord2f(0.0, 0.0);glVertex3f(eVert[eFaces[i]->faces[2]-1]->x + enemyX[x],eVert[eFaces[i]->faces[2]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[2]-1]->z+ eSpawnZ[x]);
										glTexCoord2f(0.0, 1.0);glVertex3f(eVert[eFaces[i]->faces[3]-1]->x + enemyX[x],eVert[eFaces[i]->faces[3]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[3]-1]->z+ eSpawnZ[x]);
									glEnd();	
									//char path2[] = "Images/Plants/tree1.png";
									//treeText1 = loadTexture(path2, 3);
									//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
								
							}else{
							//	std::cout << cVertex[levelLoad.mFaces[i]->faces[0]-1]->x << cVertex[levelLoad.mFaces[i]->faces[0]-1]->y << cVertex[levelLoad.mFaces[i]->faces[0]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.mFaces[i]->faces[1]-1]->x << vertex[levelLoad.mFaces[i]->faces[1]-1]->y << vertex[levelLoad.mFaces[i]->faces[1]-1]->z << std::endl;
								//std::cout << vertex[levelLoad.mFaces[i]->faces[2]-1]->x << vertex[levelLoad.mFaces[i]->faces[2]-1]->y << vertex[levelLoad.mFaces[i]->faces[2]-1]->z << std::endl;
								glBegin(GL_TRIANGLES);
									//glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
									//glNormal3f(normals[bFaces[i]->facenum-1]->x,normals[bFaces[i]->facenum-1]->y ,normals[bFaces[i]->facenum-1]->z);
									glTexCoord2f(0.0, 0.0);glVertex3f(eVert[eFaces[i]->faces[0]-1]->x + enemyX[x],eVert[eFaces[i]->faces[0]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[0]-1]->z+ eSpawnZ[x]);
									glTexCoord2f(1.0, 0.0);glVertex3f(eVert[eFaces[i]->faces[1]-1]->x+ enemyX[x],eVert[eFaces[i]->faces[1]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[1]-1]->z+ eSpawnZ[x]);
									glTexCoord2f(0.0, 1.0);glVertex3f(eVert[eFaces[i]->faces[2]-1]->x+ enemyX[x],eVert[eFaces[i]->faces[2]-1]->y + eSpawnY[x],eVert[eFaces[i]->faces[2]-1]->z+ eSpawnZ[x]);
								glEnd();
							}
						}
						glPopMatrix();
					}
				}
				
				//glPopMatrix();
				if(!hasCoin){
					glCallList(coinX);
				}
			}else if(minimap ==1 && part != 5){
				mCounter = mapCollision(levelLoad, Player1);
				if(coop){
					mCounter2 = mapCollision2(levelLoad);
				}
				for(int i = 0; i < onlineCounter; i++){
					//onlineMCounter[i] = mapOnlineCollision(onlineX[i], onlineY[i]);
				}
				glDisable(GL_TEXTURE_2D);
				if(!hasCoin){
					glCallList(coinX);
				}
				glEnable(GL_TEXTURE_2D);
				glDisable (GL_LIGHTING);
				glBindTexture(GL_TEXTURE_2D, levelLoad.texture3);
				glBegin(GL_QUADS);
				int furthestZ = -1000;
				for(int i  =0;i < levelLoad.mFaces.size(); i++){
					if(levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y < (Player1.playerY *-1)){
						glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->z + 0.1);
						glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z + 0.1);
						glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->z + 0.1);
						glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[i]->faces[3]-1]->x,levelLoad.mVert[levelLoad.mFaces[i]->faces[3]-1]->y,levelLoad.mVert[levelLoad.mFaces[i]->faces[3]-1]->z + 0.1);
					}
				}
				glEnd();
				
			/*	for(int v = 0; v < onlineCounter; v++){
					if(onlineMCounter[v] != 1000){
						glBindTexture(GL_TEXTURE_2D, texture4);
						glBegin(GL_QUADS);
						for(int i =0;i< 5;i++){
							if(i < levelLoad.mFaces.size() && onlineMCounter[v] < levelLoad.mFaces.size()-5){
								glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[0]-1]->x,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[0]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[0]-1]->z -0.1);
								glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[1]-1]->x,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[1]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[1]-1]->z -0.1);
								glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[2]-1]->x,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[2]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[2]-1]->z-0.1);
								glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[3]-1]->x,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[3]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[onlineMCounter[v] + i]->faces[3]-1]->z-0.1);
							}
						}
						glEnd();
					}
				}*/
				if(mCounter != 1000 && mCounter != 1001){
					glBindTexture(GL_TEXTURE_2D, texture4);
					glBegin(GL_QUADS);
					for(int i =0;i< 5;i++){
						if(i < levelLoad.mFaces.size() && mCounter < levelLoad.mFaces.size()-5){
							glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[0]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[0]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[0]-1]->z -0.1);
							glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[1]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[1]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[1]-1]->z -0.1);
							glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[2]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[2]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[2]-1]->z-0.1);
							glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[3]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[3]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter + i]->faces[3]-1]->z-0.1);
						}
					}
					glEnd();
				}
				if(coop){
					if(mCounter2 != 1000){
						glBindTexture(GL_TEXTURE_2D, texture4);
						glBegin(GL_QUADS);
						for(int i =0;i< 5;i++){
							if(i < levelLoad.mFaces.size() && mCounter2 < levelLoad.mFaces.size()-5){
								glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[0]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[0]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[0]-1]->z -0.1);
								glTexCoord2f(1.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[1]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[1]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[1]-1]->z -0.1);
								glTexCoord2f(0.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[2]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[2]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[2]-1]->z-0.1);
								glTexCoord2f(1.0, 1.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[3]-1]->x,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[3]-1]->y +0.5,levelLoad.mVert[levelLoad.mFaces[mCounter2 + i]->faces[3]-1]->z-0.1);
							}
						}
						glEnd();
					}
				}
				glEnable(GL_LIGHTING);
			}
		//	if(!coinCollisions()){
			

			glPopMatrix();

			glLoadIdentity();
			//glTranslatef(0, 0, 5);
			glDisable (GL_LIGHTING);
			
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			

			
			//if(minimap ==1){
			
				
			//}
			//glTranslatef(Player1.playerX, 0.f, 0.f);
			glTranslatef(0,0,-15);
			
			glTranslatef(0,Player1.playerY,0);
				//std::cout << Player1.playerY << std::endl;
			glTranslatef(-Player1.playerX,0,0);
			float zBuff = 0;
			if(minimap == 0){
				/*if(mCounter != 1000 && mCounter != 1001){
					glPushMatrix();
								glTranslatef(0,0,-10.f);
						//	float furthestZ = 1000;
								glRotatef(angle, 0.f, 1.f, 0.f);
								glColor4f(1,1,1,1);
								glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->x, levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->y, levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z);
								glRotatef(-angle, 0.f, 1.f, 0.f);
								glBindTexture(GL_TEXTURE_2D, texture);
								glRotatef(180, 0.f, 0.f, 1.f);
								glBegin(GL_QUADS);
								glTexCoord2f(0.0, 0.0);glVertex3f(-0.7f, -1.0f, 0);
								glTexCoord2f(0.0, 1.0); glVertex3f(-0.7f,  0.7f, 0);
								glTexCoord2f(1.0, 1.0); glVertex3f( 0.7f,  0.7f, 0);
								glTexCoord2f(1.0, 0.0);   glVertex3f( 0.7f, -1.0f, 0);
								glEnd();
								glPopMatrix();
				}*/
				glTranslatef(0,0,-10.f);
				if(mCounter != 1000 && mCounter != 1001){
					if(!shadowBool){
						if(angle == 0 || angle == 180){
							glTranslatef(0,0, -(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z));
						}else{
							glTranslatef(0,0, (levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z));
						}
					}
				}
				float furthestZ = 1000;
				glRotatef(angle, 0.f, 1.f, 0.f);
				glBindTexture(GL_TEXTURE_2D, treeText1);
				bool used = false;
				if((int)angle != 180 && (int)angle != 90 && (int) angle != 270){
					for(int i  =0;i < sizeof(trees); i++){
						
						if(trees[i] != 1000){
							if(mCounter != 1000 && mCounter != 1001){
							bool safe = false;
							if(part != 5){
								if(angle <90){
									if(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->x< levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x){
										safe = true;
									}
								}else if(angle < 180){
									if(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z< levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z){
										safe = true;
									}
								}else if(angle < 270){
									if(-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->x< -levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x){
										safe = true;
									}
								}else if(angle < 360){
									if(-levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z> -levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z){
										safe = true;
									}
								}
							}
							if(rot){
								if(safe || (!used && i == sizeof(trees)-1)){
								//if(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z< levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z){
									used = true;
									glPushMatrix();
										//glTranslatef(0,0,-10.f);
								//	float furthestZ = 1000;
										//glRotatef(angle, 0.f, 1.f, 0.f);
									glColor4f(1,1,1,1);
									if(falling && mCounter != 1000 && mCounter != 1001){
										if(!falling1M && !falling2M && !falling3M){
											if(mCounter < levelLoad.mFaces.size()-1){
												glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->x, levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->y, levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z);
											}
										}else{
											if(fallingNumber != -1){
												if(falling1M){
													glTranslatef(levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[1]-1]->x, levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[1]-1]->y + falling1Y[fallingNumber], levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[1]-1]->z);
												}else if(falling2M){
													glTranslatef(levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[1]-1]->x, levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[1]-1]->y + falling2Y[fallingNumber], levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[1]-1]->z);
												}else if(falling3M){
													glTranslatef(levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[1]-1]->x, levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[1]-1]->y + falling3Y[fallingNumber], levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[1]-1]->z);
												}
											}
										}
									}else{
										if(mCounter < levelLoad.mFaces.size()-1){
											glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->x, levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->y, levelLoad.mVert[levelLoad.mFaces[mCounter]->faces[1]-1]->z);
										}
									}
									glRotatef(-angle, 0.f, 1.f, 0.f);
									glBindTexture(GL_TEXTURE_2D, texture);
									glRotatef(180, 0.f, 0.f, 1.f);
									glBegin(GL_QUADS);
									glTexCoord2f(0.0, 0.0);glVertex3f(-0.7f, -1.0f, 0);
									glTexCoord2f(0.0, 1.0); glVertex3f(-0.7f,  0.7f, 0);
									glTexCoord2f(1.0, 1.0); glVertex3f( 0.7f,  0.7f, 0);
									glTexCoord2f(1.0, 0.0);   glVertex3f( 0.7f, -1.0f, 0);
									glEnd();
									glPopMatrix();
									if(coop){
										
										if(falling && mCounter2 != 1000){
											if(!falling1M && !falling2M && !falling3M){
												if(mCounter2 < levelLoad.mFaces.size()-1){
													glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->x, levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->y, levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->z);
													
												}
											}else{
												if(fallingNumber != -1){
													if(falling1M){
														glTranslatef(levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[1]-1]->x, levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[1]-1]->y + falling1Y[fallingNumber], levelLoad.fVert1[levelLoad.fFaces1[mCounter]->faces[1]-1]->z);
													}else if(falling2M){
														glTranslatef(levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[1]-1]->x, levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[1]-1]->y + falling2Y[fallingNumber], levelLoad.fVert2[levelLoad.fFaces2[mCounter]->faces[1]-1]->z);
													}else if(falling3M){
														glTranslatef(levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[1]-1]->x, levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[1]-1]->y + falling3Y[fallingNumber], levelLoad.fVert3[levelLoad.fFaces3[mCounter]->faces[1]-1]->z);
													}
												}
											}
										}else{
											if(mCounter2 < levelLoad.mFaces.size()-1){
												glTranslatef(levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->x, levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->y, levelLoad.mVert[levelLoad.mFaces[mCounter2]->faces[1]-1]->z);
												
											}
										}
										glRotatef(-angle, 0.f, 1.f, 0.f);
										glBindTexture(GL_TEXTURE_2D, player2T);
										glRotatef(180, 0.f, 0.f, 1.f);
										glBegin(GL_QUADS);
										glTexCoord2f(0.0, 0.0);glVertex3f(-0.7f, -1.0f, 0);
										glTexCoord2f(0.0, 1.0); glVertex3f(-0.7f,  0.7f, 0);
										glTexCoord2f(1.0, 1.0); glVertex3f( 0.7f,  0.7f, 0);
										glTexCoord2f(1.0, 0.0);   glVertex3f( 0.7f, -1.0f, 0);
										glEnd();
										
										glPopMatrix();
										glLoadIdentity();
									}
								}
							}
						}
							zBuff -= 0.005;
							glBindTexture(GL_TEXTURE_2D, treeText1);
							glBegin(GL_QUADS);
							
							glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x -0.4, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glTexCoord2f(0.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x - 0.4, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y -1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glTexCoord2f(1.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + 0.7, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y - 1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glTexCoord2f(1.0, 0.0);  glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + 0.7, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glEnd();
							
						}
					}
					
				}else if((int) angle == 270){
					float* xBuffer = (float *)malloc(sizeof(trees) * sizeof(float));
					for(int i = 0;i < sizeof(trees);i++){
						if(trees[i] != 1000){
							xBuffer[i] = levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x;
						}else{
							xBuffer[i] = 1000;	
						}
					}
					std::sort(xBuffer,xBuffer + sizeof(xBuffer));
					for(int i = 0;i < sizeof(trees); i++){
						//if(xBuffer[i] != 1000){
							for(int v = 0;v < sizeof(trees); v++){
								if(trees[v] != 1000){
									if(xBuffer[i] == levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x){	
										zBuff += 0.005;
										glBegin(GL_QUADS);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x +zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z -0.4 );
										glTexCoord2f(0.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y -1, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z -0.4);
										glTexCoord2f(1.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y - 1, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z + 0.7);
										glTexCoord2f(1.0, 0.0);  glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z + 0.7);
										glEnd();
									}
								}
							}
							
						//}
					}
					/*
					for(int i  =0;i < sizeof(trees); i++){
						if(trees[i] != 1000){
							zBuff += 0.005;
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x +zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z -0.4);
							glTexCoord2f(0.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y -1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z -0.4);
							glTexCoord2f(1.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y - 1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + 0.7);
							glTexCoord2f(1.0, 0.0);  glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + 0.7);
							glEnd();
							
						}
					}
					for(int i  = sizeof(trees) -1;i > sizeof(trees)/2; i--){
						if(trees[i] != 1000){
							zBuff += 0.005;
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x +zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z -0.4);
							glTexCoord2f(0.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y -1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z -0.4);
							glTexCoord2f(1.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y - 1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + 0.7);
							glTexCoord2f(1.0, 0.0);  glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + 0.7);
							glEnd();
							
						}
					}*/
				}else if((int) angle == 90){
					float* xBuffer = (float *)malloc(sizeof(trees) * sizeof(float));
					for(int i = 0;i < sizeof(trees);i++){
						if(trees[i] != 1000){
							xBuffer[i] = levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x;
						}else{
							xBuffer[i] = 1000;	
						}
					}
					std::sort(xBuffer,xBuffer + sizeof(xBuffer));
					for(int i  = sizeof(trees) -1;i > -1; i--){
						//if(xBuffer[i] != 1000){
							for(int v = 0;v < sizeof(trees); v++){
								if(trees[v] != 1000){
									if(xBuffer[i] == levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x){	
										zBuff -= 0.005;
										glBegin(GL_QUADS);
										glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x +zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z -0.4);
										glTexCoord2f(0.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y -1, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z -0.4);
										glTexCoord2f(1.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y - 1, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z + 0.7);
										glTexCoord2f(1.0, 0.0);  glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->x + zBuff, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[v]]->faces[1]-1]->z + 0.7);
										glEnd();
									}
								}
							}
							
						//}
					}
					free(xBuffer);
				}else if((int)angle == 180){
					for(int i = 0;i < sizeof(trees); i++){
						if(trees[i] != 1000){
							zBuff += 0.005;	
						}
					}
					for(int i  = sizeof(trees) -1;i > -1; i--){
						if(trees[i] != 1000){
							zBuff -= 0.005;							
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x -0.4, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glTexCoord2f(0.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x - 0.4, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y -1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glTexCoord2f(1.0, 1.0); glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + 0.7, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y - 1, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glTexCoord2f(1.0, 0.0);  glVertex3f(levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->x + 0.7, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->y + 3, levelLoad.mVert[levelLoad.mFaces[trees[i]]->faces[1]-1]->z + zBuff);
							glEnd();
						}
					}
				}
				
				
				if(!rot){
					glLoadIdentity();
					glTranslatef(-0.f, 0.5f,0);
					glTranslatef(0,0,-5.f);
				}else{
				//std::cout << Player1.playerY << std::endl;
					//glTranslatef(Player1.playerX,0,0);
					//glTranslatef(0,0,-10.f);
					glLoadIdentity();
					glTranslatef(-0.f, 0.5f,0);
					glTranslatef(0,0,-5.f);
					
					if(mCounter == 1000){
						if(shadow){
							glColor4f(0,0,0,1);
						}
						if(!right){
							if(onFire){
								glBindTexture(GL_TEXTURE_2D, fireSprite);
							}else{
								glBindTexture(GL_TEXTURE_2D, texture);
							}
							glRotatef(180, 0.f, 0.f, 1.f);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(-0.3f, -0.4f, -5.f);
							glTexCoord2f(0.0, 1.0); glVertex3f(-0.3f,  0.5f, -5.f);
							glTexCoord2f(1.0, 1.0); glVertex3f( 0.3f,  0.5f, -5.f);
							glTexCoord2f(1.0, 0.0);   glVertex3f( 0.3f, -0.4f, -5.f);
							glEnd();
							glLoadIdentity();
							glTranslatef(0,0,-15);
							glTranslatef(0,Player1.playerY,0);
							//std::cout << Player1.playerY << std::endl;
							glTranslatef(-Player1.playerX,0,0);
							//glRotatef(angle, 0.f, 1.f, 0.f);
						}else{
							if(onFire){
								glBindTexture(GL_TEXTURE_2D, fireSprite);
							}else{
								glBindTexture(GL_TEXTURE_2D, texture);
							}	
							glRotatef(180, 0.f, 0.f, 1.f);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(0.3f, -0.4f, -5.f);
							glTexCoord2f(0.0, 1.0); glVertex3f(0.3f,  0.5f, -5.f);
							glTexCoord2f(1.0, 1.0); glVertex3f( -0.3f,  0.5f, -5.f);
							glTexCoord2f(1.0, 0.0);   glVertex3f( -0.3f, -0.4f, -5.f);
							glEnd();
							glLoadIdentity();
							glTranslatef(0,0,-15);
							glTranslatef(0,Player1.playerY,0);
							//std::cout << Player1.playerY << std::endl;
							glTranslatef(-Player1.playerX,0,0);
							//glRotatef(angle, 0.f, 1.f, 0.f);
						}
						if(coop){
							
							if(!right2){
								glLoadIdentity();
								glTranslatef(0,0,-5);
								glTranslatef(playerX2 - Player1.playerX, 0, 0);
								glTranslatef(Player1.playerX/2, 0, 0);
																
								glTranslatef(0, playerY2/5, 0);
								glTranslatef(0,-2,0);
								//glTranslatef(0,-Player1.playerY/2, 0);
								//if(angle == 90 || 
								//glTranslatef(0,playerY2,0);
								//std::cout << Player1.playerY << std::endl;
								glTranslatef(playerX2,0,0);
								//glRotatef(angle, 0.f, 1.f, 0.f);
								glBindTexture(GL_TEXTURE_2D, player2T);
								glRotatef(180, 0.f, 0.f, 1.f);
								glBegin(GL_QUADS);
								glTexCoord2f(0.0, 0.0);glVertex3f(-0.3f, -0.4f, -5.f);
								glTexCoord2f(0.0, 1.0); glVertex3f(-0.3f,  0.5f, -5.f);
								glTexCoord2f(1.0, 1.0); glVertex3f( 0.3f,  0.5f, -5.f);
								glTexCoord2f(1.0, 0.0);   glVertex3f( 0.3f, -0.4f, -5.f);
								glEnd();
								
							}else{
								glLoadIdentity();
								glTranslatef(0,0,-5);
								glTranslatef(playerX2 - Player1.playerX, 0, 0);
								glTranslatef(Player1.playerX/2, 0, 0);
								glTranslatef(0, playerY2, 0);
								glTranslatef(0,-2,0);
								//glTranslatef(0, Player1.playerY - playerY2, 0);
								//glTranslatef(0,-Player1.playerY/2, 0);
								//std::cout << Player1.playerY << std::endl;
								glTranslatef(playerX2,0,0);
								//glRotatef(angle, 0.f, 1.f, 0.f);
								glBindTexture(GL_TEXTURE_2D, player2T);	
								glRotatef(180, 0.f, 0.f, 1.f);
								glBegin(GL_QUADS);
								glTexCoord2f(0.0, 0.0);glVertex3f(0.3f, -0.4f, -5.f);
								glTexCoord2f(0.0, 1.0); glVertex3f(0.3f,  0.5f, -5.f);
								glTexCoord2f(1.0, 1.0); glVertex3f( -0.3f,  0.5f, -5.f);
								glTexCoord2f(1.0, 0.0);   glVertex3f( -0.3f, -0.4f, -5.f);
								glEnd();
								
							}
						}
						if(shadow){
							glColor4f(1,1,1,1);
						}
					}
				}
				
				//glDisable(GL_LIGHTING);
				glColor4f(1,1,1,1);
				if(!rot){
					if(left || right){
						if(!switchBob){
							if(bobCounter < 0.03){
								bobCounter+= 0.01;
							}else{
								switchBob = true;
							}
						}else if(switchBob){
							if(bobCounter > -0.03){
								bobCounter -= 0.01;
							}else{
								switchBob = false;
							}
						}
					} 
					if(rotateCounter < 60 && rotateAllowed == false){
						rotateCounter++;
					}else if(rotateCounter > 58){
						rotateAllowed = true;
						rotateCounter = 0;
					}
					glTranslatef(0,bobCounter, 0);
					if(shadow){
						glColor4f(0,0,0,1);
					}
					if(!right){
						if(onFire){
							glBindTexture(GL_TEXTURE_2D, fireSprite);
						}else if(!under1){
							glBindTexture(GL_TEXTURE_2D, texture);
						}else{
							glBindTexture(GL_TEXTURE_2D, pU);
						}
						glRotatef(180, 0.f, 0.f, 1.f);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0, 0.0);glVertex3f((-0.3f), -0.4f, -(5.f + dieWidth));
						glTexCoord2f(0.0, 1.0); glVertex3f((-0.3f),  0.5f, -(5.f + dieWidth));
						glTexCoord2f(1.0, 1.0); glVertex3f( 0.3f,  0.5f, -(5.f + dieWidth));
						glTexCoord2f(1.0, 0.0);   glVertex3f( 0.3f, -0.4f, -(5.f + dieWidth));
						glEnd();
						glLoadIdentity();
						glTranslatef(0,0,-15);
						glTranslatef(0,Player1.playerY,0);
						//std::cout << Player1.playerY << std::endl;
						glTranslatef(-Player1.playerX,0,0);
						glRotatef(angle, 0.f, 1.f, 0.f);
					}else{
						if(onFire){
							glBindTexture(GL_TEXTURE_2D, fireSprite);
						}else if(!under1){
							glBindTexture(GL_TEXTURE_2D, texture);
						}else{
							glBindTexture(GL_TEXTURE_2D, pU);
						}	
						glRotatef(180, 0.f, 0.f, 1.f);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0, 0.0);glVertex3f(0.3f, -0.4f, -(5.f + dieWidth));
						glTexCoord2f(0.0, 1.0); glVertex3f(0.3f,  0.5f, -(5.f + dieWidth));
						glTexCoord2f(1.0, 1.0); glVertex3f( -0.3f,  0.5f, -(5.f + dieWidth));
						glTexCoord2f(1.0, 0.0);   glVertex3f( -0.3f, -0.4f, -(5.f + dieWidth));
						glEnd();
						glLoadIdentity();
						glTranslatef(0,0,-15);
						glTranslatef(0,Player1.playerY,0);
						//std::cout << Player1.playerY << std::endl;
						glTranslatef(-Player1.playerX,0,0);
						
					}
					if(shadow){
						glColor4f(1,1,1,1);
					}
					
					if(shadow2){
						glColor4f(0,0,0,1);
					}
					if(dying){
						die(Player1);
					}
					if(coop){
						if(left2 || right2){
							if(!switchBob2){
								if(bobCounter2 < 0.03){
									bobCounter2+= 0.01;
								}else{
									switchBob2 = true;
								}
							}else if(switchBob2){
								if(bobCounter2 > -0.03){
									bobCounter2 -= 0.01;
								}else{
									switchBob2 = false;
								}
							}
						}
						
						if(!right2){
							glLoadIdentity();
							glTranslatef(0,0,-4.9);
							glTranslatef(0,bobCounter2,0);
							//if(angle == 90 || angle == 270){
							//	glTranslatef(0,0,playerX2 - Player1.playerX);
							//	glTranslatef(0,0,Player1.playerX/2);
							//}else{
							//if(angle == 270 || angle == 90){
								glTranslatef((playerX2 - Player1.playerX)/5, 0, 0);
								glTranslatef(-Player1.playerX/5, 0, 0);
								
							//}else{
								//glTranslatef((playerX2 - Player1.playerX)/2, 0, 0);
							//	glTranslatef(playerX2, 0, 0);
							//}
							//}
						//	glTranslatef(0, Player1.playerY - playerY2, 0);
						//	glTranslatef(0,-Player1.playerY/2, 0);
							glTranslatef(0,-(playerY2 - Player1.playerY)/5, 0);
							glTranslatef(0,Player1.playerY/5, 0);
							glTranslatef(0,0.5,0);
							glTranslatef(0,-(playerY2/5),0);
							//glTranslatef(0,-playerY2,0);
							//glTranslatef(0, (Player1.playerY - playerY2)/2, 0);
							//glTranslatef(0,-(Player1.playerY), 0);
							//glTranslatef(0,playerY2,0);
							//std::cout << Player1.playerY << std::endl;
							glTranslatef(playerX2/5,0,0);
							//glRotatef(angle, 0.f, 1.f, 0.f);
							if(!under1){
								glBindTexture(GL_TEXTURE_2D, player2T);
							}else{
								glBindTexture(GL_TEXTURE_2D, pU2);
							}
							glRotatef(180, 0.f, 0.f, 1.f);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(-0.3f, -0.4f, -(5.f + dieWidth));
							glTexCoord2f(0.0, 1.0); glVertex3f(-0.3f,  0.5f, -(5.f + dieWidth));
							glTexCoord2f(1.0, 1.0); glVertex3f( 0.3f,  0.5f, -(5.f + dieWidth));
							glTexCoord2f(1.0, 0.0);   glVertex3f( 0.3f, -0.4f, -(5.f + dieWidth));
							glEnd();
							
						}else{
							glLoadIdentity();
							glTranslatef(0,0,-4.9);
							glTranslatef(0,bobCounter2,0);
							//if(angle == 90 || angle == 270){
							//	glTranslatef(0,0,playerX2 - Player1.playerX);
							//	glTranslatef(0,0,Player1.playerX/2);
							//}else{
						//	if(angle == 270 || angle == 90){
								glTranslatef((playerX2 - Player1.playerX)/5, 0, 0);
								glTranslatef(-Player1.playerX/5, 0, 0);
								
						//	}else{
								//glTranslatef(Player1.playerX - playerX2, 0, 0);
							//	glTranslatef(playerX2, 0, 0);
						//	}
							//}
							//glTranslatef(0, (Player1.playerY - playerY2)/2, 0);
							//glTranslatef(0,(-Player1.playerY), 0);
							//glTranslatef(0, Player1.playerY - playerY2, 0);
							//glTranslatef(0,-Player1.playerY/2, 0);
							glTranslatef(0,-(playerY2 - Player1.playerY)/5, 0);
							glTranslatef(0,Player1.playerY/5, 0);
							glTranslatef(0,-(playerY2/5),0);
							glTranslatef(0,0.5,0);
							//std::cout << Player1.playerY << std::endl;
							glTranslatef(playerX2/5,0,0);
							//glRotatef(angle, 0.f, 1.f, 0.f);
							if(!under1){
								glBindTexture(GL_TEXTURE_2D, player2T);
							}else{
								glBindTexture(GL_TEXTURE_2D, pU2);
							}
							glRotatef(180, 0.f, 0.f, 1.f);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(0.3f, -0.4f, -(5.f + dieWidth));
							glTexCoord2f(0.0, 1.0); glVertex3f(0.3f,  0.5f, -(5.f + dieWidth));
							glTexCoord2f(1.0, 1.0); glVertex3f( -0.3f,  0.5f, -(5.f + dieWidth));
							glTexCoord2f(1.0, 0.0);   glVertex3f( -0.3f, -0.4f, -(5.f + dieWidth));
							glEnd();
							
						}
					}
					if(shadow2){
						glColor4f(1,1,1,1);
					}
					for(int i = 0; i < onlineCounter; i++){
						//if(onlineX[i] != -1000){
							glLoadIdentity();
							glTranslatef(0,0,-(4.8 - (i*0.01)));
							glTranslatef((onlineX[i] - Player1.playerX)/5, 0, 0);
							//cout << onlineX[i] << endl;
							glTranslatef(-Player1.playerX/5, 0, 0);
							glTranslatef(0,-(onlineY[i] - Player1.playerY)/5, 0);
							glTranslatef(0,Player1.playerY/5, 0);
							glTranslatef(0,0.5,0);
							glTranslatef(0,-(onlineY[i]/5),0);
							glTranslatef(onlineX[i]/5,0,0);
							glBindTexture(GL_TEXTURE_2D, onlineP);
							glRotatef(180, 0.f, 0.f, 1.f);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0, 0.0);glVertex3f(-0.3f, -0.4f, -(5.f + dieWidth));
							glTexCoord2f(0.0, 1.0); glVertex3f(-0.3f,  0.5f, -(5.f + dieWidth));
							glTexCoord2f(1.0, 1.0); glVertex3f( 0.3f,  0.5f, -(5.f + dieWidth));
							glTexCoord2f(1.0, 0.0);   glVertex3f( 0.3f, -0.4f, -(5.f + dieWidth));
							glEnd();
						//}
					}
				}
				//glEnable(GL_LIGHTING);
			}
			/*if(theRand ==1){
				//glColor4f(1,1,0.1,1);
				lightCounterR = 1;
				lightCounterG = 1;
				lightCounterB = 0.1;
			}else if(theRand ==2){
				//glColor4f(0.5,0.2,0.5,1);
				lightCounterR = 0.5;
				lightCounterG = 0.2;
				lightCounterB = 0.5;
			}else if(theRand ==3){
				//glColor4f(0,0.5,1,1);
				lightCounterR = 0;
				lightCounterG = 0.5;
				lightCounterB = 1;
			}*/
			glFlush();
			glDisable(GL_TEXTURE_2D);
			/*glBegin(GL_QUADS); 
				glColor3f(1, 1, 1);
				glVertex3f(20.0f, 20.0f, 0.0f); 
				glVertex3f(20.0f, -20.0f, 0.0f); 
				glVertex3f(-20.0f, -20.0f, 0.0f); 
				glVertex3f(-20.0f, 20.0f, 0.0f); 
			glEnd();*/ 

			// Finally, display rendered frame on screen
			client->recieve();
			clientLine = client->line;
			try{
				//cout << "hello" << endl;
				deciferP(Coin);
				//cout << "world "<< endl;
			}catch (int e){
				cout << "An exception occurred. Exception Nr. " << e << '\n';
			}
			std::string coords = name;
			coords += ":";
			coords += std::to_string(Player1.playerX);
			coords += ":";
			coords += std::to_string(Player1.playerY);
			coords += ":";
			//coords += std::to_string(angle);
			coords += "/";
			char * coordsArray = (char*)coords.c_str();
			client->sendMessage(coordsArray);
			if(coop){
				std::string coords = cName;
				coords += ":";
				coords += std::to_string(playerX2);
				coords += ":";
				coords += std::to_string(playerY2);
				coords += ":";
				coords += "/";
				char * coordsArray = (char*)coords.c_str();
				client->sendMessage(coordsArray);
			}

			
			App.display();
			}
		}
		theRand = (rand() % 3) + 1;
		if(theRand==1){
			levelLoad.texture3 = loadTexture(text2,4);
			treeText1 = loadTexture(tree1, 3);
			levelLoad.texture5 = loadTexture(text2,5);
		}else if(theRand ==2){
			treeText1 = loadTexture(tree2, 3);
			levelLoad.texture3 = loadTexture(bText2, 4);
			levelLoad.texture5 = loadTexture(bText2, 5);
		}else if(theRand ==3){
			treeText1 = loadTexture(tree3, 3);
			levelLoad.texture3 = loadTexture(bText3, 4);
			levelLoad.texture5 = loadTexture(bText3, 5);
		}
		ice = false;
		if(theRand ==1){
				//glColor4f(1,1,0.1,1);
				lightCounterR = 1;
				lightCounterG = 1;
				lightCounterB = 0.1;
			}else if(theRand ==2){
				//glColor4f(0.5,0.2,0.5,1);
				lightCounterR = 0.5;
				lightCounterG = 0.2;
				lightCounterB = 0.5;
			}else if(theRand ==3){
				//glColor4f(0,0.5,1,1);
				lightCounterR = 0;
				lightCounterG = 0.5;
				lightCounterB = 1;
			}
		Player1.playerX = 0;
		Player1.playerY = 0;
		angle = 0;
		part++;
		levelLoad.partl++;
		if(part ==3 || part == 6 | part == 8){
			shadowBool = true;
			levelLoad.shadowBooll = true;
			//coinT = loadTexture(decStoneI, 2);
			levelLoad.texture3 = loadTexture(stone, 4);
			//treeText1 = loadTexture(bText3, 3);
			levelLoad.texture5 = loadTexture(bText3,5);
		}else{
			shadowBool = false;
			levelLoad.shadowBooll = false;
		}if(part ==5){
			falling = true;
			loadFalling(levelLoad);
		}else{
			falling = false;
		}
		if(part ==9){
			slime = true;
			std::string sMap = "Objects/misc/slime";
			sMap += std::to_string(part);
			sMap += ".obj";
			char * sArray = (char*)sMap.c_str();
			levelLoad.loadSlime(sArray);
		}else{
			slime = false;
		}
		if(part == 10){
			lava = true;
			std::string lMap = "Objects/misc/lava";
			lMap += std::to_string(part);
			lMap += ".obj";
			char * lArray = (char*)lMap.c_str();
			levelLoad.loadLava(lArray);
		}else{
			lava = false;
		}
		if(part ==6){
			ice = true;
			char ice[] = "Images/ice.png";
			levelLoad.texture3 = loadTexture(ice,4);
			levelLoad.texture5 = loadTexture(ice,5);
			treeText1 = loadTexture(tree3, 3);
		}else{
			ice = false;
		}
		std::string map = "Objects/part";
		map += std::to_string(part);
		map += ".obj";
		
		if(shadowBool){
			std::string decS = "Objects/decoration";
			decS += std::to_string(part);
			decS += ".obj";
			char * decArray = (char*)decS.c_str();
			decoration = levelLoad.loadDecoration(decArray);
			if(sizeof(decStone) >0){
				free(decStone);
			}
			decStone = (int*) malloc(levelLoad.dFaces.size() * sizeof(int));
			for(int i =0;i < levelLoad.dFaces.size(); i++){
				int random = rand() % 3;
				decStone[i]= random;
			}
		}
		/*if(part ==10){
			boss = true;
			std::string bossC = "Objects/Boss/boss";
			bossC += std::to_string(part);
			bossC += ".obj";
			char* bossArray = (char*)bossC.c_str();
			loadBoss(bossArray);
			falling = true;
			loadFalling(levelLoad);
		}else{
			boss = false;
			if(part!= 5){
				falling = false;
			}
		}*/
		if(part >= 6 && !boss){
			loadEnemies("Objects/Enemies/enemy.obj");
			enemyX = (float*)malloc(sizeof(float) * 3);
			eSpawnZ = (float*) malloc(sizeof(float)*3);
			eSpawnY = (float*) malloc(sizeof(float)*3);
			eSwitched = (bool*) malloc(sizeof(bool)*3);
			for(int i = 0; i < sizeof(enemyX); i++){
					int randCounter = rand() % levelLoad.mFaces.size();
					eSwitched[i] = false;
					eSpawnY[i] = levelLoad.mVert[levelLoad.mFaces[randCounter]->faces[0]-1]->y;
					enemyX[i] = levelLoad.mVert[levelLoad.mFaces[randCounter]->faces[0]-1]->x; 
					eSpawnZ[i] =levelLoad.mVert[levelLoad.mFaces[randCounter]->faces[0]-1]->z; 
			}
			enemies = true;
		}else{
			enemies = false;
		}
		char * mapArray = (char*)map.c_str();
		cube= levelLoad.loadMap(mapArray);
		
		std::string map2 = "Objects/part";
		int newPart = part+1;
		map2 += std::to_string(newPart);
		map2 += ".obj";
		char * mapArray2 = (char*)map2.c_str();
		cube2 = levelLoad.loadMap2(mapArray2);
		int SavePart = part - 1;
		xLoad->writeXml(SavePart);
		breaks = false;
		if(part ==7){
			breaks = true;
			std::string breakable = "Objects/break";
			breakable += std::to_string(part);
			breakable += ".obj";
			char * breakArray = (char*)breakable.c_str();
			breakCubes = loadBreakable(breakArray);
		}else{
			breaks = false;
		}
		
		if(part == 7){
			trline = true;
			std::string tr = "Objects/Misc/tr";
			tr += std::to_string(part);
			tr += ".obj";
			char * trampArray = (char*) tr.c_str();
			loadtrline(trampArray);
		}else{
			trline = false;
		}
		if(part ==9){
			char textC[] = "Images/Cutscenes/fire.png";
			texture2 = loadTexture(textC, 1);
			theStart = 0;
		}
		if(part ==2){
			char textC[] = "Images/Cutscenes/minimap.png";
			texture2 = loadTexture(textC, 1);
			theStart = 0;
		}
		if(part ==1){
			char textC[] = "Images/Cutscenes/rotate.png";
			texture2 = loadTexture(textC, 1);
			theStart = 0;
		}
		std::string coinS = "Objects/coin";
		coinS += std::to_string(part);
		coinS += ".obj";
		char * coinArray= (char *)coinS.c_str();
		coinX = loadCoin(coinArray);
		free(trees);
		free(Coin.coins);
		trees = (int *)malloc(levelLoad.mFaces.size() * sizeof(int));
		Coin.coins = (int *)malloc(5 * sizeof(int));
		//std::cout << sizeof(trees)<< std::endl;
		for(int i  =0;i < levelLoad.mFaces.size(); i++){
			trees[i] = 1000;
		}
		int furthestZ = -1000;
		for(int v = 0; v < 5; v++){
			Coin.increaseC[v] = 0;
			int random = rand() % levelLoad.mFaces.size();
			//std::cout << random << levelLoad.mFaces.size() << std::endl;
			bool found = true;
			while(random % 6 !=0){
				random = rand() % levelLoad.mFaces.size();
			}
			while(found){
				found = false;
				float width = 0.7;
				float height = 0.7;
				for(int i = 0; i < levelLoad.mFaces.size(); i++){	
					//if(i != random){

						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[0]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[0]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->x +width > levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x && levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->x  < (levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->x) + width){
							if(levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->y + Coin.increaseC[v] + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y && levelLoad.mVert[levelLoad.mFaces[random]->faces[2]-1]->y +Coin.increaseC[v]< levelLoad.mVert[levelLoad.mFaces[i]->faces[2]-1]->y +height){
								//if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z + height > levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z && levelLoad.mVert[levelLoad.mFaces[random]->faces[i]-1]->z < (levelLoad.mVert[levelLoad.mFaces[i]->faces[1]-1]->z+ width/4)  + (width/4*3)){
									found = true;
								//}
							}
						}
						if(found){
							i = levelLoad.mFaces.size()+1;
							Coin.increaseC[v] += 0.1;
							//std::cout << Coin.increaseC[v] << std::endl;
						}
					//}
				}
			}
			Coin.coins[v] = random;
		}
		for(int i = 0; i < 5; i++){
			Coin.coinsB[i] = false;
			Coin.coinsPlayed[i] = false;
		}
		coinM = levelLoad.loadCoins();
		treeCounter =0;
		for(int i  =0;i < levelLoad.mFaces.size(); i++){
			int random  =rand() % levelLoad.mFaces.size();
			if(random %6 ==0){
				if(levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z >= furthestZ){
					furthestZ = levelLoad.mVert[levelLoad.mFaces[random]->faces[1]-1]->z;
					trees[treeCounter] = random;
					treeCounter++;
				}
			}
		}
		if(shadowBool){
			treeCounter =0;
		}
		//std::string Coin.coins = "coin";
		//Coin.coins += std::to_string(part);
		//Coin.coins += ".obj";
		//char * coinArray= (char *)Coin.coins.c_str();
		//coin = loadCoin(coinArray);
		hasCoin = false;
		notLoading = true;
		
    }
	part -= 1;
	xLoad->writeXml(part);
	delete xLoad;
	delete client;

    return EXIT_SUCCESS;
}
////////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////


