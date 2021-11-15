#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute float in_MaterialGroupIndex;

	uniform mat4 in_InverseVeiwing;
	uniform mat4 in_Projection;
	uniform mat4 in_Model;
	
	varying vec3 out_MaterialGroupIndex;


	void main()
	{
		out_MaterialGroupIndex = in_MaterialGroupIndex;

		gl_Position = in_Projection * in_InverseVeiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	varying vec3 out_MaterialGroupIndex;


	void main()
	{
		vec3 colour = vec3(1, 1, 1) * out_MaterialGroupIndex;
		
		gl_FragColor = vec4(colour, 1.0);
	}
#endif