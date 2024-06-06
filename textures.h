#ifndef TEXTURES_H
#define TEXTURES_H

class textures{
	public:
		void preLoadTexture();
		int loadTexture(char filename[], int number);
	protected:
	private:
		unsigned int* textures;

};

#endif