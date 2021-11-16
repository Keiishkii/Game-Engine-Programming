#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec3 in_Normal;

	uniform mat4 in_InverseVeiwing;
	uniform mat4 in_Projection;
	uniform mat4 in_Model;



	void main()
	{
		gl_Position = in_Projection * in_InverseVeiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	void main()
	{
		vec3 colour = vec3(1, 1, 1);
		
		gl_FragColor = vec4(colour, 1.0);
	}
#endif