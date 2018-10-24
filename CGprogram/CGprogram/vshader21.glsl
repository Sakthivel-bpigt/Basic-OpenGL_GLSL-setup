#version 150
#define DEBUG 0
in vec4 vPosition;
out vec4 vColor;

uniform vec4 Cplane;
uniform float max_itr;

float cal_man(float maxItr ) {
	float count = 0;
	vec2 z = vec2(0.0,0.0);
	
	//vec2 C_origin = vec2(-2.5,-1.75);
	vec2 C_origin = Cplane.xy;
	// so mandelbrot length is 3.5 in complex plane
	// our vertices range from (-1, -1) to (1,1)
	// in case if we have 1000 vertices each vertex is 0.002 unit apart from each other
	// so we have to scale the complex plane into our geometric plane 
	float offset = (Cplane.z - Cplane.x) * 0.5; // by the above mentioned scale we calculated this offset
	// reset vertices from origin
	vec2 newVPos = vec2(vPosition.x+1, vPosition.y+1);
	// Scale vertex to complex plane by multiplying offset
	newVPos *= offset;
	// Scale vertex to complex plane by changing origin
	newVPos += C_origin;
	float len2, temp;
	//z.x = z.y = 0.0;
	do {
			/* rl part */
			temp = z.x*z.x - z.y*z.y + newVPos.x;

			/* iginary part */
			z.y = 2.0*z.x*z.y + newVPos.y;
			
			z.x = temp;
			
			/* length */
			len2 = z.x*z.x + z.y*z.y;

			if (len2 > 4) 
				break;
			count++;
		} while (count < maxItr);
	return count;
}


void main()
{
    gl_Position = vPosition;
	float mandle = cal_man(max_itr);
    vec3 mcolor = vec3(	mod(mandle*10,max_itr), mod(mandle*10,max_itr), mod(mandle*10,max_itr)
					//	0,0
					//	max_itr - mod(mandle*10,max_itr), 
					//	mod((mandle*10-(max_itr/2)), max_itr)
					);
	vColor = vec4(mcolor/max_itr, 1);
	if(DEBUG!=0 && (vPosition.x==0 || vPosition.y==0 ))
		vColor = vec4(1,1,1, 1);
}
