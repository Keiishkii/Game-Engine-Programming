#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec2 in_Normal;
	attribute vec2 in_TextureUV;
	
	varying vec2 out_TextureUV;

	uniform vec4 in_Colour; 
	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;

	void main()
	{
		out_TextureUV = in_TextureUV;
		gl_Position = in_Projection * in_Veiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform sampler2D in_GizmoTexture;

	varying vec2 out_TextureUV;

	void main()
	{	
		vec4 colour = texture(in_GizmoTexture, out_TextureUV);	
		if(colour.a < 0.05)
        		discard;
		
		gl_FragColor = colour;
	}
#endif