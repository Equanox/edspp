/*
 * DrawAbstract.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: equa
 */

#include <DrawAbstract.h>

DrawAbstract::DrawAbstract() {
	screen_width = 800;
	screen_height = 600;
	videoduration = 100;
	storagedirectory = std::string("/home/equa/tmp/");
	processedframe = 0;
//	/initgl();
}

//DrawAbstract::DrawAbstract(int videoduration,int sw,int sh, std::string storagedirectory) {
//	screen_width = sw;
//	screen_height = sh;
//	this->videoduration = videoduration;
//	this->storagedirectory = storagedirectory;
//	processedframe = 0;
//
//	initgl();
//}

DrawAbstract::~DrawAbstract() {
	// TODO Auto-generated destructor stub
}

void DrawAbstract::deprectedAbstractInit(int first_frame, int videoduration,int sw,int sh, std::string storagedirectory){
		screen_width = sw;
		screen_height = sh;
		this->videoduration = first_frame + videoduration;
		this->storagedirectory = storagedirectory;
		processedframe = first_frame;

		mTextureIDs = new GLuint[videoduration];
		initgl();
}

bool DrawAbstract::initgl(){

	putenv("LIBGL_ALWAYS_SOFTWARE=1");

	//Initialize FreeGLUT
	int myargc = 0;
	glutInit( &myargc, NULL);

	//Create OpenGL 2.1 context
//	glutInitContextVersion( 2, 1 );

	//Create Double Buffered Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize( screen_width, screen_height );
	glutCreateWindow( "OpenGL" );


	//Set main loop
	//glutTimerFunc( 1000 / 60, runMainLoop, 0 );

	//Register keyboard
	//glutKeyboardFunc( keyboard );


    //Initialize GLEW
    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
    {
        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
        return false;
    }
    glViewport( 0.f, 0.f, screen_width, screen_height );

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, screen_width, screen_height, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color30
    glClearColor( 0.f, 0.f, 0.f, 0.f );

    //Enable texturing
    glEnable( GL_TEXTURE_2D );

    //Set blending
    glEnable( GL_BLEND );
    glDisable( GL_DEPTH_TEST );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    //Initialize DevIL
    ilInit();
    iluInit();
    ilClearColour( 255, 255, 255, 000 );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

//    if(!loadImage("/home/equa/workspace/tmp/Sequence/images_tmp/1.png")){
//    	printf( "Error loading Image \n");
//    }

//    if(!loadImages()){
//    	printf( "Error loading Image \n");
//    }

	return true;
}

bool DrawAbstract::drawBackgroundTexture(std::string path){

	if(!loadImage(path)){
    	printf( "Error loading Image \n");
    }

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,0,screen_width,screen_height);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glClear( GL_COLOR_BUFFER_BIT );
    //Move to rendering point
    glTranslatef( 0.f, 0.f, 0.f );
    glColor4f(1.00,0,0,1.00);

    //Set texture ID
    glBindTexture( GL_TEXTURE_2D, mTextureID );

    glColor4d(1,1,1,1.f);
    glBegin( GL_QUADS );
        glTexCoord2f( 0.f, 0.f ); glVertex2f(           0.f,            0.f );
        glTexCoord2f( 1.f, 0.f ); glVertex2f( screen_width,            0.f );
        glTexCoord2f( 1.f, 1.f ); glVertex2f( screen_width, screen_height );
        glTexCoord2f( 0.f, 1.f ); glVertex2f(           0.f, screen_height );
    glEnd();

    glBindTexture( GL_TEXTURE_2D, NULL );

    return true;
}

bool DrawAbstract::loadImages(){

    //Generate and set current image ID
    ILuint *imgID = new ILuint[videoduration];
    ilGenImages( videoduration, imgID );

    mTextureIDs = new GLuint[videoduration];
    glGenTextures( videoduration, mTextureIDs );

    for(int i = 0; i < videoduration; i++){
    	ilBindImage( imgID[i] );

        //Load image
        char *path;
        generateImagePath(&path,i+1);//array from 0, images on hdd from 1
        std::cout << "Path:" << path << std::endl;
        ILboolean success = ilLoadImage( path );
        //delete path;
        std::cout << "bla" << success <<  std::endl;

        //Image loaded successfully
        if( success == IL_TRUE )
        {
            success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
            if( success == IL_TRUE )
            {
                //Create texture from file pixels
                loadTextureFromPixels32( (GLuint*)ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ),i);
            }
        }

     }

    return true;
}

bool DrawAbstract::loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height, int count ){



	//Bind texture ID
	glBindTexture( GL_TEXTURE_2D, mTextureIDs[count] );

	//Generate texture
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

	//Set texture parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	//Unbind texture
	glBindTexture( GL_TEXTURE_2D, NULL );

	//Check for error
	GLenum error = glGetError();
	if( error != GL_NO_ERROR )
	{
		printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
		return false;
	}

	return true;
}

bool DrawAbstract::loadImage(std::string path){

    //Generate and set current image ID
    ILuint imgID;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );

    //Load image
    char path_tmp[1024];
    strcpy(path_tmp,path.c_str());
    ILboolean success = ilLoadImage( path_tmp );

    //Image loaded successfully
    if( success == IL_TRUE )
    {
        success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
        if( success == IL_TRUE )
        {
            //Create texture from file pixels
            loadTextureFromPixels32( (GLuint*)ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ) );
        }
    }
	return true;
}

bool DrawAbstract::loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height )
{

    //Generate texture ID = std::string("/home/equa/workspace/tmp/Sequence/images_tmp/")
    glGenTextures( 1, &mTextureID );

    //Bind texture ID
    glBindTexture( GL_TEXTURE_2D, mTextureID  );

    //Generate texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

    //Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    //Unbind texture
    glBindTexture( GL_TEXTURE_2D, NULL );


    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return false;
    }

    return true;
}

bool DrawAbstract::save(std::string path){

	unsigned char *data = new unsigned char[4*screen_width*screen_height];
	glReadBuffer(GL_BACK);
	glReadPixels(0,0,screen_width,screen_height,GL_RGBA, GL_UNSIGNED_BYTE,data);
	ilTexImage(screen_width,screen_height,1,4,IL_RGBA, IL_UNSIGNED_BYTE,data);
	ilEnable(IL_FILE_OVERWRITE);

	ilSaveImage(path.c_str());

	delete data;
	return true;
}

bool DrawAbstract::drawmanager(){

	if(processedframe < videoduration){

		processedframe++;

		char *path;
		generateImagePath(&path,processedframe);
		imagepath = std::string(path);

		delete path;
		return true;
	}

	return false;
}

bool DrawAbstract::generateImagePath(char **path, int frame){

	*path = (char*) malloc(sizeof( char ) * 1024);
	for(unsigned int h = 0; h < 1024;h++)
		(*path)[h] = '\n';

	char tmp2[1024];
	strcpy(*path,storagedirectory.c_str());
	sprintf(tmp2,"%d.png",frame);
	strcat(*path,tmp2);

	return true;
}
