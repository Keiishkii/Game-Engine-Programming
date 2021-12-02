#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	
	uniform vec4 in_Colour; 

	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;
	
	varying vec4 out_Colour;
	varying vec3 out_TextureCoordinate;

	void main()
	{
		out_Colour = in_Colour;
		out_TextureCoordinate = vec3(in_Model * vec4(in_Position, 1.0));

		vec4 position = in_Projection * in_Veiwing * in_Model * vec4(in_Position, 1.0);
		gl_Position = position.xyww;
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform samplerCube in_Skybox;
	
	varying vec4 out_Colour;
	varying vec3 out_TextureCoordinate;

	void main()
	{		
		vec4 colour = out_Colour * texture(in_Skybox, out_TextureCoordinate);

		gl_FragColor = colour;
	}
#endif