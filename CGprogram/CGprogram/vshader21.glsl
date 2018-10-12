#version 330

in vec4 vPosition;
out vec4 vColor;
void
main()
{
	gl_Position = vPosition;
	vColor = vPosition;
}
