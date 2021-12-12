#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec3 in_Normal;
	attribute vec2 in_TextureUV;
	
	uniform vec4 in_Colour; 

	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;
	
	varying vec4 out_Colour;
	varying vec2 out_TextureUV;



	void main()
	{
		out_Colour = in_Colour;
		out_TextureUV = in_TextureUV;

		gl_Position = in_Projection * in_Veiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform sampler2D in_AlbedoMap;
	
	varying vec4 out_Colour;
	varying vec2 out_TextureUV;



	void main()
	{
		vec4 textureColour = texture2D(in_AlbedoMap, vec2(out_TextureUV.x, 1 - out_TextureUV.y));
		vec4 finalColour = textureColour * out_Colour;
		
		// Discard fragment if sample is transparent
		if (finalColour.a < 0.1)
			discard;

		gl_FragColor = finalColour;
	}
#endif