#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec3 in_Normal;
	attribute vec2 in_TextureUV;

	uniform vec4 in_Colour; 
	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;

	varying vec3 out_Normal;
	varying vec4 out_Colour;
	varying vec2 out_TextureUV;

	void main()
	{
		out_Normal = in_Normal;
		out_Colour = in_Colour;
		out_TextureUV = in_TextureUV;

		gl_Position = in_Projection * in_Veiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform sampler2D in_Texture;

	varying vec3 out_Normal;
	varying vec4 out_Colour;
	varying vec2 out_TextureUV;

	void main()
	{		
		vec4 textureColour = texture2D(in_Texture, vec2(out_TextureUV.x, 1 - out_TextureUV.y));

		//gl_FragColor = vec4(out_TextureUV, 1, 1);
		gl_FragColor = textureColour;
	}
#endif