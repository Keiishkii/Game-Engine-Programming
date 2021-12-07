#define MAX_LIGHTS 10

#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec3 in_Normal;
	attribute vec2 in_TextureUV;

	uniform vec4 in_Colour; 
	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;

	uniform float in_LightCount;
	uniform vec3 in_LightPositions[MAX_LIGHTS];
	uniform vec3 in_LightColours[MAX_LIGHTS];
	uniform float in_LightIntensitys[MAX_LIGHTS];
	

	varying vec3 out_Normal;
	varying vec4 out_Colour;
	varying vec2 out_TextureUV;
	
	varying vec3 out_FragmentPosition;

	varying float out_LightCount;
	varying vec3 out_LightPositions[MAX_LIGHTS];
	varying vec3 out_LightColours[MAX_LIGHTS];
	varying float out_LightIntensitys[MAX_LIGHTS];

	void main()
	{
		out_Normal = in_Normal;
		out_Colour = in_Colour;
		out_TextureUV = in_TextureUV;

		out_FragmentPosition = vec3(in_Model * vec4(in_Position, 1.0));

		out_LightCount = in_LightCount;
		out_LightPositions = in_LightPositions;
		out_LightColours = in_LightColours;
		out_LightIntensitys = in_LightIntensitys;

		gl_Position = in_Projection * in_Veiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform sampler2D in_AlbedoMap;

	varying vec3 out_Normal;
	varying vec4 out_Colour;
	varying vec2 out_TextureUV;
	
	varying vec3 out_FragmentPosition;

	varying float out_LightCount;
	varying vec3 out_LightPositions[MAX_LIGHTS];
	varying vec3 out_LightColours[MAX_LIGHTS];
	varying float out_LightIntensitys[MAX_LIGHTS];

	void main()
	{		
		vec4 textureColour = texture2D(in_AlbedoMap, vec2(out_TextureUV.x, 1 - out_TextureUV.y));
		
		vec3 normal = normalize(out_Normal);
		vec3 lightDirection = normalize(out_LightPositions[0] - out_FragmentPosition);  
		float diffuse = max(dot(normal, lightDirection), 0.0);

		vec4 colour = textureColour * out_Colour;
		gl_FragColor = vec4(colour.xyz * diffuse, colour.w);
	}
#endif