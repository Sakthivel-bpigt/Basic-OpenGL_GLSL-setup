// Two-Dimensional Sierpinski Gasket       
// Generated using randomly selected vertices and bisection

#include "Angel.h"

const int NumPoints = 100;

//----------------------------------------------------------------------------
//*********************************
const int nLength = 1000;
const int nPoints = nLength * nLength;
vec2 pointsArr[nPoints];

// mandelbrot ranges from (-2.5, -1.75) to (1, 1.75) in complex plane for our program
GLfloat C_Plane[4] = { -2.5, -1.75, 1, 1.75 };
GLuint cplane; // The location of the "cplane" shader uniform variable

//----------------------------------------------------------------------------
void makePointsArray(vec2 BL, vec2 TR)
{
	vec2 point = BL;
	float offset = 2.0 / nLength;
	for (size_t i = 0; i < nLength; i++)
	{
		point.y = BL.y + i * offset;
		for (size_t j = 0; j < nLength; j++)
		{
			point.x = BL.x + j * offset;
			pointsArr[i*nLength + j] = point;
		}

	}
}


void init1(void)
{
	makePointsArray(vec2(-1, -1), vec2(1, 1));
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointsArr), pointsArr, GL_STATIC_DRAW);

	// Load shaders and use the resulting shader program
	//GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
	GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
	glUseProgram(program);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	cplane = glGetUniformLocation(program, "Cplane");
	glUniform4fv(cplane, 1, C_Plane);
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}


//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
	glPointSize(10.0);
    glDrawArrays( GL_POINTS, 0, nPoints);    // draw the points
    glFlush();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{    
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 1000, 1000 );
	    
    glutCreateWindow( "Sierpinski Gasket" );

	glewInit();
    
    init1();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
