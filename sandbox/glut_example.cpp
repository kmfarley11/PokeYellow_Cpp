#include <IL/il.h>
#include <GL/glut.h>

// Example code / sandbox file to test openGL stuff. Note: as of first commit of the file, most source was obtained from:
// https://www.opengl.org/discussion_boards/showthread.php/181714-Does-opengl-help-in-the-display-of-an-existing-image
 
#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480
 
int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() 
{
    // Clear color and depth buffers
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
       glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix
 
    /* Draw a quad */
       glBegin(GL_QUADS);
           glTexCoord2i(0, 0); glVertex2i(0,   0);
           glTexCoord2i(0, 1); glVertex2i(0,   height);
           glTexCoord2i(1, 1); glVertex2i(width, height);
           glTexCoord2i(1, 0); glVertex2i(width, 0);
       glEnd();
 
    glutSwapBuffers();
} 
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei newwidth, GLsizei newheight) 
{  
    // Set the viewport to cover the new window
       glViewport(0, 0, width=newwidth, height=newheight);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
     glMatrixMode(GL_MODELVIEW);
 
    glutPostRedisplay();
}
 
 
/* Initialize OpenGL Graphics */
void initGL(int w, int h) 
{
     glViewport(0, 0, w, h); // use a screen size of WIDTH x HEIGHT
     glEnable(GL_TEXTURE_2D);     // Enable 2D texturing
 
    glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
     glLoadIdentity();
     glOrtho(0.0, w, h, 0.0, 0.0, 100.0);
 
     glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling
 
     glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
     glClearDepth(0.0f);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}
 
/* Load an image using DevIL and return the devIL handle (-1 if failure) */
int LoadImage(char *filename)
{
    ILboolean success; 
     ILuint image; 
 
    ilGenImages(1, &image); /* Generation of one image name */
     ilBindImage(image); /* Binding of image name */
     success = ilLoadImage(filename); /* Loading of the image filename by DevIL */
 
    if (success) /* If no error occured: */
    {
        /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
           success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
 
        if (!success)
           {
                 return -1;
           }
    }
    else
        return -1;
 
    return image;
}
 
int main(int argc, char **argv) 
{
 
    GLuint texid;
    int image;
 
    if ( argc < 1)
    {
        /* no image file to  display */
        return -1;
    }
 
    /* GLUT init */
    glutInit(&argc, argv);            // Initialize GLUT
       glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
       glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);   // Set the window's initial width & height
       glutCreateWindow(argv[0]);      // Create window with the name of the executable
       glutDisplayFunc(display);       // Register callback handler for window re-paint event
       glutReshapeFunc(reshape);       // Register callback handler for window re-size event
 
    /* OpenGL 2D generic init */
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);
 
    /* Initialization of DevIL */
     if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
     {
           printf("wrong DevIL version \n");
           return -1;
     }
     ilInit(); 
 
 
    /* load the file picture with DevIL */
    image = LoadImage(argv[1]);
    if ( image == -1 )
    {
        printf("Can't load picture file %s by DevIL \n", argv[1]);
        return -1;
    }
 
    /* OpenGL texture binding of the image loaded by DevIL  */
       glGenTextures(1, &texid); /* Texture name generation */
       glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
        0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
 
    /* Main loop */
    glutMainLoop();
 
    /* Delete used resources and quit */
     ilDeleteImages(1, (unsigned int*) &image); /* Because we have already copied image data into texture data we can release memory used by image. */
     glDeleteTextures(1, &texid);
 
     return 0;
}
