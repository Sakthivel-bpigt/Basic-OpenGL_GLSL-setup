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
vec4 C_Plane_P = { -2.5, -1.75, 1, 1.75 };
vec4 C_Plane = C_Plane_P;
vec4 C_Plane_New;
vec4 mousePos;
float max_itr = 100;
GLuint cplane; // The location of the "cplane" shader uniform variable
GLuint maxitr; // The location of the "max_itr" shader uniform variable
bool leftMouseButtonDown = false;
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
	maxitr = glGetUniformLocation(program, "max_itr");
	
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}


//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window

	glBegin(GL_LINE_LOOP);
	glVertex2f(mousePos.x, mousePos.y);
	glVertex2f(mousePos.z, mousePos.y);
	glVertex2f(mousePos.z, mousePos.w);
	glVertex2f(mousePos.x, mousePos.w);
	glEnd();

	glUniform4fv(cplane, 1, C_Plane);
	glUniform1f(maxitr, max_itr);
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
	case 'r':
		C_Plane = C_Plane_P;
		break;
	case '+':
	case '=':
		max_itr++;
		std::cout << "max_itr: " << max_itr << std::endl;
		break;
    }
	glutPostRedisplay();
}

//----------------------------------------------------------------------------

void updateComplexPlane(float x, float y, int dir=1)
{
	float C_length = abs(C_Plane[2] - C_Plane[0]);
	float offset = C_length / nLength;
	std::cout << "C_length: " << C_length << ", offset: " << offset<<"\t";
	vec2 C_point = vec2(C_Plane[0] + x * offset, C_Plane[1] + (nLength-y) * offset);
	std::cout << "C_point " << C_point << std::endl;
	float C_Plane_Offset;
	if(dir > 0)
	{ 
		// Zoom in by 7/8 of fraction
		C_Plane_Offset = offset * nLength * 0.5 * 0.875;
	}
	else
	{
		// Zoom out by 8/7 of fraction
		C_Plane_Offset = offset * nLength * 0.5 * 1.142857;
	}
	std::cout << "C_Plane_Offset : " << C_Plane_Offset << std::endl;
	std::cout << "C_Plane (" << C_Plane[0] << ", " << C_Plane[1] << ") ";
	std::cout << " (" << C_Plane[2] << ", " << C_Plane[3] << ")\n " << std::endl;
	C_Plane[0] = C_point.x - C_Plane_Offset;
	C_Plane[1] = C_point.y - C_Plane_Offset;
	C_Plane[2] = C_point.x + C_Plane_Offset;
	C_Plane[3] = C_point.y + C_Plane_Offset;
	std::cout << "New C_Plane (" << C_Plane[0] << ", " << C_Plane[1] << ") ";
	std::cout << " (" << C_Plane[2] << ", " << C_Plane[3] << ")\n " << std::endl;
	glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
mouse(int button, int state, int x, int y)
{
	//*********************************************************************************************
	// Screen Offset problem
	// opengl display coordinate and windows coordinate has some issues, which has to be fixed
	//Temp solution: offset the windows X with +5 pixels and Y with -5 pixels
	x += 5;
	y -= 5;
	//*********************************************************************************************

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//update the complex plane
		//std::cout << "X: " << x<< " Y: " << y<< std::endl;
		updateComplexPlane(x, y);
		//leftMouseButtonDown = true;
		//float C_length = abs(C_Plane[2] - C_Plane[0]);
		//float offset = C_length / nLength;
		//std::cout << "C_length: " << C_length << ", offset: " << offset << std::endl;

		//vec2 C_point = vec2(C_Plane[0] + x * offset, C_Plane[1] + y * offset);
		//C_Plane_New = vec4(C_point.x, C_point.y, C_point.x, C_point.y);

		//std::cout << "C_Plane_LB (" << C_Plane_New[0] << ", " << C_Plane_New[1] << ") ";
		////std::cout << " C_Plane_TR (" << C_Plane_New[2] << ", " << C_Plane_New[3] << ") " << std::endl;

		//mousePos = vec4(x/ (float)nLength, y / (float)nLength, x / (float)nLength, y / (float)nLength);
	}
	//if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
	//	max_itr++;
	//	std::cout << "max_itr: " << max_itr << std::endl;
	//}
}

//----------------------------------------------------------------------

void mouseMotion(int x, int y)
{
	//*********************************************************************************************
	// Screen Offset problem
	// opengl display coordinate and windows coordinate has some issues, which has to be fixed
	//Temp solution: offset the windows X with +5 pixels and Y with -5 pixels
	x += 5;
	y -= 5;
	//*********************************************************************************************

	if (leftMouseButtonDown)
	{
		float C_length = abs(C_Plane[2] - C_Plane[0]);
		float offset = C_length / nLength;
		vec2 C_point = vec2(C_Plane[0] + x * offset, C_Plane[1] + y * offset);
		C_Plane_New.z = C_point.x;
		C_Plane_New.w = C_point.y;
		mousePos.z = x / (float)nLength;
		mousePos.w = y / (float)nLength;
	}
}

//----------------------------------------------------------------------

void passiveMouseMotion(int x, int y)
{
	//*********************************************************************************************
	// Screen Offset problem
	// opengl display coordinate and windows coordinate has some issues, which has to be fixed
	//Temp solution: offset the windows X with +5 pixels and Y with -5 pixels
	x += 5;
	y -= 5;
	//*********************************************************************************************

	//std::cout << "X: " << x << "Y: " << y << std::endl;
	//float C_length = abs(C_Plane[2] - C_Plane[0]);
	//float offset = C_length / nLength;
	//std::cout << "C_length: " << C_length << ", offset: " << offset << std::endl;
	//vec2 C_point = vec2(C_Plane[0] + x * offset, C_Plane[1] + y * offset);
	//std::cout << "X, Y " << C_point << std::endl;
	//float C_Plane_Offset = offset * nLength * 0.25;
	//std::cout << "C_Plane_Offset : " << C_Plane_Offset << std::endl;
	//vec4 C_Plane_tmp = { C_point.x - C_Plane_Offset, C_point.y - C_Plane_Offset,
	//					C_point.x + C_Plane_Offset, C_point.y + C_Plane_Offset };
	//std::cout << "C_Plane_LB (" << C_Plane_tmp[0] << ", " << C_Plane_tmp[1] << ") ";
	//std::cout << " C_Plane_TR (" << C_Plane_tmp[2] << ", " << C_Plane_tmp[3] << ") " << std::endl;
}

//----------------------------------------------------------------------
void mouseWheel(int button, int dir, int x, int y)
{
	//*********************************************************************************************
	// Screen Offset problem
	// opengl display coordinate and windows coordinate has some issues, which has to be fixed
	//Temp solution: offset the windows X with +5 pixels and Y with -5 pixels
	x += 5;
	y -= 5;
	//*********************************************************************************************

	if (dir > 0)
	{
		// Zoom in
		updateComplexPlane(x, y, dir);
	}
	else
	{
		// Zoom out
		updateComplexPlane(x, y, dir);
	}
}
//----------------------------------------------------------------------

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
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	
	// freeGLUT specific function
	glutMouseWheelFunc(mouseWheel);

    glutMainLoop();
    return 0;
}
