/*
 * DrawAbstract.h
 *
 *  Created on: Nov 30, 2013
 *      Author: equa
 */

#ifndef DRAWABSTRACT_H_
#define DRAWABSTRACT_H_

#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <string.h>
#include <iostream>//debug

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//DevIL
#include <IL/il.h>
#include <IL/ilu.h>

#define DRAWSTYLE_NEGMULT = 0;

class DrawAbstract {
public:
	DrawAbstract();
//	DrawAbstract(int videoduration = 100,
//				 	 	  int sw = 800,
//				 	 	  int sh = 600,
//				 	 	  std::string storagedirectory = std::string("/home/equa/tmp/"))
//	: videoduration(videoduration), screen_width(sw), screen_height(sh),storagedirectory(storagedirectory)
//	{
//		processedframe = 0;
//		mTextureID = 1;
//	}
	virtual ~DrawAbstract();

	virtual void render() = 0;
	virtual bool drawmanager();
	void deprectedAbstractInit(int,int,int,int,std::string);

protected:
	int screen_width;
	int screen_height;
	int videoduration;
	int processedframe;

	std::string storagedirectory;
	std::string imagepath;



	//loading background texture
	GLuint mTextureID;
	GLuint *mTextureIDs;
	bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height);
	bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height, int count);
	bool loadImage(std::string);
	bool loadImages();
	bool drawBackgroundTexture(std::string);
	bool generateImagePath(char **path, int frame);

	bool save(std::string);

	struct point{
		int x;
		int y;
	};

	struct pointf{
		float x;
		float y;
	};

	struct color4uc{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

	};

	struct drawstyle{
		color4uc color;
	};


private:
	bool initgl();
};

#endif /* DRAWABSTRACT_H_ */
