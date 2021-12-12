#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	
	uniform vec4 in_Colour; 

	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	
	varying vec4 out_Colour;
	varying vec3 out_TextureDirection;

	void main()
	{
		out_Colour = in_Colour;
		out_TextureDirection = in_Position;

		mat4 viewingRotationMatrix = mat4(mat3(in_Veiwing));
		vec4 position = in_Projection * viewingRotationMatrix * vec4(in_Position, 1.0);
		gl_Position = position.xyww;
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform samplerCube in_Albedo;
	
	varying vec4 out_Colour;
	varying vec3 out_TextureDirection;

	void main()
	{		
		vec3 colour = (out_Colour * texture(in_Albedo, out_TextureDirection)).rgb;

		gl_FragColor = vec4(colour, 1);
	}
#endif