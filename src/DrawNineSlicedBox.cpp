/*
 * DrawNineSlicedBox.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: equa
 */

#include <DrawNineSlicedBox.h>
#define PI 3.14159265

//points for round corners
unsigned int max_points = 10;
unsigned int min_points = 3;
//int *textureid;

DrawNineSlicedBox::DrawNineSlicedBox(){

	std::cout << "WTFFFFFF" << std::endl;

	this->x = 0;
	this->y = 0;
	this->lx = 100;
	this->ly = 100;
	this->r = 1;

	//init();
}

//DrawNineSlicedBox::DrawNineSlicedBox(int videoduration,
//									 int screen_width,
//									 int screen_height,
//									 unsigned int x,
//									 unsigned int y,
//									 unsigned int lx,
//									 unsigned int ly,
//									 unsigned int r,
//									 std::string storagedirectory)
//: DrawAbstract(videoduration,screen_width,screen_height,storagedirectory)
//{
//	this->x = x;
//	this->y = y;
//	this->lx = lx;
//	this->ly = ly;
//	this->r = r;
//
//	init();
//}

DrawNineSlicedBox::~DrawNineSlicedBox() {
	// TODO Auto-generated destructor stub
}

void DrawNineSlicedBox::deprecatedInit(int first_frame,
					  int videoduration,
			 	 	  int screen_width,
			 	 	  int screen_height,
			 	 	  unsigned int x,
			 	 	  unsigned int y,
			 	 	  unsigned int lx,
			 	 	  unsigned int ly,
			 	 	  unsigned int r,
			 	 	  std::string storagedirectory){

	deprectedAbstractInit(first_frame,videoduration,screen_width,screen_height,storagedirectory);
	this->x = x;
	this->y = y;
	this->lx = lx;
	this->ly = ly;
	this->r = r;

	init();
}

void DrawNineSlicedBox::render(){

	//glGenTextures( videoduration, mTextureIDs );

	while(drawmanager()){

		std::cout << "Path:" << imagepath << std::endl;

		drawBackgroundTexture(imagepath);

		//standard modes
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0,0,screen_width,screen_height);

		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		//glClear( GL_COLOR_BUFFER_BIT );
		glTranslatef( 0.f, 0.f, 0.f );

		//adjustable stuff
		glLineWidth(4);
		glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);

		std::vector<pointf> p;

		glColor4d(1,0.4,0.7,0.4f);
		glBegin(GL_LINE_STRIP);
		p.clear();
		this->getBorder(&p);
		pointf first_one = p.back();
		while(p.size() > 0){
			pointf tmp = p.back();
			glVertex2f(tmp.x,tmp.y);
			p.pop_back();
		}
		glVertex2f(first_one.x,first_one.y);
		glEnd();

		glColor4d(1,1,1,0.65f);
		glBegin(GL_TRIANGLE_FAN);
		p.clear();
		this->getBorder(&p);
		pointf first = p.back();
		while(p.size() > 0){
			pointf tmp = p.back();
			glVertex2f(tmp.x,tmp.y);
			p.pop_back();
		}
		glVertex2f(first.x,first.y);
		glEnd();

		glutSwapBuffers();
		glutMainLoopEvent();
		usleep(1000/60);
		save(imagepath);
		glDeleteTextures(1, &mTextureID);
	}
}

void DrawNineSlicedBox::runMainLoop(int i){

}

bool DrawNineSlicedBox::init(){

	if(r == 0) r = 1;

	if(r != 0){
		//init with round corners
		tl.ankor.x = x;				tl.ankor.y = y;				tl.size.x = r;		tl.size.y = r;			tl.roundcorner = true;
		tc.ankor.x = x + r;			tc.ankor.y = y;				tc.size.x = lx-2*r;	tc.size.y = r;	    	tc.roundcorner = false;
		tr.ankor.x = x + lx - r;	tr.ankor.y = y;				tr.size.x = r;		tr.size.y = r;			tr.roundcorner = true;

		ml.ankor.x = x;				ml.ankor.y = y + r;			ml.size.x = r;		ml.size.y = ly - 2*r;	ml.roundcorner = false;
		mc.ankor.x = x + r;			mc.ankor.y = y + r;			mc.size.x = lx-2*r;	mc.size.y = ly - 2*r;	mc.roundcorner = false;
		mr.ankor.x = x + lx - r;	mr.ankor.y = y + r;			mr.size.x = r;		mr.size.y = ly - 2*r;	mr.roundcorner = false;

		bl.ankor.x = x;				bl.ankor.y = y + ly - r;	bl.size.x = r;		bl.size.y = r;		bl.roundcorner = true;
		bc.ankor.x = x + r;			bc.ankor.y = y + ly - r;	bc.size.x = lx-2*r;	bc.size.y = r;		bc.roundcorner = false;
		br.ankor.x = x + lx - r;	br.ankor.y = y + ly - r;	br.size.x = r;		br.size.y = r;		br.roundcorner = true;
	}

	if(max_points < min_points)
		max_points = min_points;

	return false;
}

bool DrawNineSlicedBox::getBorderTC(pointf* one,pointf *two){

	one->x = tc.ankor.x;
	one->y = tc.ankor.y;

	two->x = tc.ankor.x + tc.size.x;
	two->y = tc.ankor.y;

	return false;
}

bool DrawNineSlicedBox::getBorderBC(pointf* one,pointf *two){

	one->x = bc.ankor.x + bc.size.x;
	one->y = bc.ankor.y + bc.size.y;

	two->x = bc.ankor.x;
	two->y = bc.ankor.y + bc.size.y;

	return false;
}

bool DrawNineSlicedBox::getBorderML(pointf* one,pointf *two){

	one->x = ml.ankor.x;
	one->y = ml.ankor.y + ml.size.y;

	two->x = ml.ankor.x;
	two->y = ml.ankor.y;

	return false;
}

bool DrawNineSlicedBox::getBorderMR(pointf* one,pointf *two){

	one->x = mr.ankor.x + mr.size.x;
	one->y = mr.ankor.y;

	two->x = mr.ankor.x + mr.size.x;
	two->y = mr.ankor.y + mr.size.y;

	return false;
}

bool DrawNineSlicedBox::getBorderTL(std::vector<pointf> *p){

	std::vector<pointf> p_tmp;
	pointf center;

	center.x = tl.ankor.x + tl.size.x;
	center.y = tl.ankor.y + tl.size.y;

	for(unsigned int i = 0; i < max_points; i++){

		pointf tmp;
		double rad = i*(90/max_points)*PI/180;
		tmp.x = center.x - tl.size.x*sin(rad);
		tmp.y = center.y - tl.size.y*cos(rad);

		if(tmp.x == (center.x - tl.size.x) && tmp.y == center.y)
			continue;
		if(tmp.x == (center.x) && tmp.y == (center.y - tl.size.y))
			continue;

		bool insert = true;
		for(unsigned int j = 0; j < p_tmp.size(); j++){
			if(tmp.x == p_tmp.at(j).x || tmp.y == p_tmp.at(j).y){
				insert = false;
				break;
			}
		}

		if(insert)
			p_tmp.push_back(tmp);
	}

	for(unsigned int i = 0; i < p_tmp.size(); i++){
		p->push_back(p_tmp.at(i));
	}

	return false;
}

bool DrawNineSlicedBox::getBorderTR(std::vector<pointf> *p){

	std::vector<pointf> p_tmp;
	pointf center;

	center.x = tr.ankor.x;
	center.y = tr.ankor.y + tr.size.y;

	for(unsigned int i = 0; i < max_points; i++){

		pointf tmp;
		double rad = i*(90/max_points)*PI/180;
		tmp.x = center.x + tr.size.x*sin(rad);
		tmp.y = center.y - tr.size.y*cos(rad);

		if(tmp.x == (center.x + tr.size.x) && tmp.y == center.y)
			continue;
		if(tmp.x == (center.x) && tmp.y == (center.y - tr.size.y))
			continue;

		bool insert = true;
		for(unsigned int j = 0; j < p_tmp.size(); j++){
			if(tmp.x == p_tmp.at(j).x || tmp.y == p_tmp.at(j).y){
				insert = false;
				break;
			}
		}

		if(insert)
			p_tmp.push_back(tmp);
	}

	for(int i = p_tmp.size()-1; i >= 0; i--){
		p->push_back(p_tmp.at(i));
	}

	return false;
}


bool DrawNineSlicedBox::getBorderBR(std::vector<pointf> *p){

	std::vector<pointf> p_tmp;
	pointf center;

	center.x = br.ankor.x;
	center.y = br.ankor.y;

	for(unsigned int i = 0; i < max_points; i++){

		pointf tmp;
		double rad = i*(90/max_points)*PI/180;
		tmp.x = center.x + br.size.x*sin(rad);
		tmp.y = center.y + br.size.y*cos(rad);

		if(tmp.x == (center.x + br.size.x) && tmp.y == center.y)
			continue;
		if(tmp.x == (center.x) && tmp.y == (center.y + br.size.y))
			continue;

		bool insert = true;
		for(unsigned int j = 0; j < p_tmp.size(); j++){
			if(tmp.x == p_tmp.at(j).x || tmp.y == p_tmp.at(j).y){
				insert = false;
				break;
			}
		}

		if(insert)
			p_tmp.push_back(tmp);
	}

	for(unsigned int i = 0; i < p_tmp.size(); i++){
		p->push_back(p_tmp.at(i));
	}

	return false;
}

bool DrawNineSlicedBox::getBorderBL(std::vector<pointf> *p){

	std::vector<pointf> p_tmp;
	pointf center;

	center.x = bl.ankor.x + bl.size.x;
	center.y = bl.ankor.y;

	for(unsigned int i = 0; i < max_points; i++){

		pointf tmp;
		double rad = i*(90/max_points)*PI/180;
		tmp.x = center.x - bl.size.x*sin(rad);
		tmp.y = center.y + bl.size.y*cos(rad);

		if(tmp.x == (center.x - bl.size.x) && tmp.y == center.y)
			continue;
		if(tmp.x == (center.x) && tmp.y == (center.y + bl.size.y))
			continue;

		bool insert = true;
		for(unsigned int j = 0; j < p_tmp.size(); j++){
			if(tmp.x == p_tmp.at(j).x || tmp.y == p_tmp.at(j).y){
				insert = false;
				break;
			}
		}

		if(insert)
			p_tmp.push_back(tmp);
	}

	for(int i = p_tmp.size()-1; i >= 0; i--){
		p->push_back(p_tmp.at(i));
	}

	return false;
}

bool DrawNineSlicedBox::getBorder(std::vector<pointf> *p){

	pointf one,two;

	getBorderTL(p);

	getBorderML(&one,&two);
	p->push_back(two);
	p->push_back(one);

	getBorderBL(p);

	getBorderBC(&one,&two);
	p->push_back(two);
	p->push_back(one);

	getBorderBR(p);

	getBorderMR(&one,&two);
	p->push_back(two);
	p->push_back(one);

	getBorderTR(p);

	getBorderTC(&one,&two);
	p->push_back(two);
	p->push_back(one);

//	std::cout << "-------------------------" << std::endl;
//	for(int u = 0; u < p->size();u++){
//		std::cout << "x: " << p->at(u).x << " y: " << p->at(u).y << std::endl;
//	}

	return false;
}
