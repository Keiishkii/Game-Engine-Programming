#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec2 in_Normal;
	attribute vec2 in_TextureUV;
	
	varying vec2 out_TextureUV;

	void main()
	{
		out_TextureUV = in_TextureUV;
		gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform sampler2D in_ScreenTexture;

	varying vec2 out_TextureUV;

	void main()
	{				
		vec4 colour = texture(in_ScreenTexture, out_TextureUV);
		gl_FragColor = colour;
	}
#endif