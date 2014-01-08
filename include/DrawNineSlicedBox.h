/*
 * DrawNineSlicedBox.h
 *
 *  Created on: Nov 30, 2013
 *      Author: equa
 */

#ifndef DRAWNINESLICEDBOX_H_
#define DRAWNINESLICEDBOX_H_

#include <iostream>//debug

#include <math.h>
#include <vector>

#include "DrawAbstract.h"

struct point{
	int x;
	int y;
};

struct pointf{
	float x;
	float y;
};

class DrawNineSlicedBox : public DrawAbstract {
public:
	 DrawNineSlicedBox();
//	 DrawNineSlicedBox(int videoduration = 100,
//			 	 	  int screen_width = 800,
//			 	 	  int screen_height = 600,
//			 	 	  unsigned int x = 0,
//			 	 	  unsigned int y = 0,
//			 	 	  unsigned int lx = 100,
//			 	 	  unsigned int ly = 100,
//			 	 	  unsigned int r = 1,
//			 	 	  std::string storagedirectory = std::string("/home/equa/workspace/tmp/Sequence/images_tmp/"))
//	: DrawAbstract(videoduration,screen_width,screen_height,storagedirectory)
//	{
//		this->x = x;
//		this->y = y;
//		this->lx = lx;
//		this->ly = ly;
//		this->r = r;
//
//		init();
//	}
	virtual ~DrawNineSlicedBox();

	void render();
	void deprecatedInit(int f_frame, int a,int b,int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h,std::string i);

	struct boxstyle{
		drawstyle border;
		drawstyle background;
	};

private:
	void runMainLoop(int);

	bool getBorder(std::vector<pointf>*);

	bool getBorderTC(pointf*,pointf*);
	bool getBorderBC(pointf*,pointf*);
	bool getBorderML(pointf*,pointf*);
	bool getBorderMR(pointf*,pointf*);
	bool getBorderTL(std::vector<pointf>*);
	bool getBorderTR(std::vector<pointf>*);
	bool getBorderBR(std::vector<pointf>*);
	bool getBorderBL(std::vector<pointf>*);

	struct quad{
		bool roundcorner;
		pointf ankor;
		pointf size;
	}tl,tc,tr,ml,mc,mr,bl,bc,br;

	bool init();

	unsigned int x;
	unsigned int y;
	unsigned int lx;
	unsigned int ly;
	unsigned int r;
};

#endif /* DRAWNINESLICEDBOX_H_ */
