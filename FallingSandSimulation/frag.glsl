#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D currentTexture;
uniform vec2 resolution;

void main( void ) {	
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			vec2 pixel_off = vec2(float(x), float(y));
			vec2 neighborLocation = gl_FragCoord.xy + pixel_off;
			if (neighborLocation.x < 0 || neighborLocation.y < 0 || neighborLocation.x > resolution.x || neighborLocation.y > resolution.y) {
				continue;
			}
			vec4 tex_color = texture(currentTexture, gl_FragCoord.xy + pixel_off);
			r += tex_color.r;
			g += tex_color.g;
			b += tex_color.b;
		}
	}
	vec4 final_color = vec4(r/9.0, g/9.0, b/9.0, 1.0);
	gl_FragColor = final_color;
	
}