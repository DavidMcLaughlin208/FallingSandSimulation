#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D currentTexture;
uniform vec2 resolution;


void main( void ) {	
	float weight = 10.0;
	vec2 p = gl_FragCoord.xy / resolution.xy;
	vec4 final_color = texture(currentTexture, p) * weight;
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			vec2 pixel_off = vec2(float(x), float(y));
			vec2 neighborLocation = (gl_FragCoord.xy + pixel_off * 6) / resolution.xy;
			final_color += texture(currentTexture, neighborLocation);
		}
	}
	
	gl_FragColor = final_color/(9.0 + weight);
}