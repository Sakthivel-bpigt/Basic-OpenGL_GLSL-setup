#version 150

in vec4 vPosition;
out vec4 vColor;

float max_itr = 200;
float cal_man(float maxItr ) {
	float count = 0;
	vec2 z;
	float len2, temp;
	z.x = z.y = 0.0;
	do {
			/* rl part */
			temp = z.x*z.x - z.y*z.y - 0.5 + vPosition.x*1.50;

			/* iginary part */
			z.y = 2.0*z.x*z.y + vPosition.y*1.50;
			
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
}
