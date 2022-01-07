#define MAX_LIGHTS 13
#define PI 3.1415926538

#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec3 in_Normal;
	attribute vec2 in_TextureUV;
	
	uniform vec4 in_Colour; 
	uniform float in_SpecularStrength; 
	uniform float in_Shininess;

	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;

	uniform vec3 in_ViewPosition;

	uniform float in_LightCount;
	uniform vec3 in_LightPositions[MAX_LIGHTS];
	uniform vec3 in_LightColours[MAX_LIGHTS];
	uniform float in_LightIntensitys[MAX_LIGHTS];
	
	varying vec4 out_Colour;
	varying float out_SpecularStrength; 
	varying float out_Shininess;

	varying vec3 out_Normal;
	varying vec2 out_TextureUV;
	
	varying vec3 out_FragmentPosition;
	varying vec3 out_ViewPosition;

	varying float out_LightCount;
	varying vec3 out_LightPositions[MAX_LIGHTS];
	varying vec3 out_LightColours[MAX_LIGHTS];
	varying float out_LightIntensitys[MAX_LIGHTS];



	void main()
	{
		out_Colour = in_Colour;
		out_SpecularStrength = in_SpecularStrength;
		out_Shininess = in_Shininess;
		
		out_Normal = normalize(mat3(transpose(inverse(in_Model))) * in_Normal);  
		out_TextureUV = in_TextureUV;

		out_FragmentPosition = vec3(in_Model * vec4(in_Position, 1.0));
		out_ViewPosition = out_ViewPosition;

		out_LightCount = in_LightCount;
		out_LightPositions = in_LightPositions;
		out_LightColours = in_LightColours;
		out_LightIntensitys = in_LightIntensitys;

		gl_Position = in_Projection * in_Veiwing * in_Model * vec4(in_Position, 1.0);
	}
#endif

#ifdef FRAGMENT_SHADER
	uniform sampler2D in_Albedo;
	
	varying vec4 out_Colour;
	varying float out_SpecularStrength; 
	varying float out_Shininess;

	varying vec3 out_Normal;
	varying vec2 out_TextureUV;
	
	varying vec3 out_FragmentPosition;
	varying vec3 out_ViewPosition;

	varying float out_LightCount;
	varying vec3 out_LightPositions[MAX_LIGHTS];
	varying vec3 out_LightColours[MAX_LIGHTS];
	varying float out_LightIntensitys[MAX_LIGHTS];
	


	vec3 AmbiantLight(vec3 colour);
	vec3 DiffuseLight(vec3 colour, vec3 lightColour, float dot_LightNormal);
	vec3 SpecularLight(vec3 colour, vec3 lightColour, vec3 viewDirection, vec3 reflectedDirection);



	void main()
	{
		vec4 textureColour = texture2D(in_Albedo, vec2(out_TextureUV.x, 1 - out_TextureUV.y));
		vec3 colour = out_Colour.rgb * textureColour.rgb;
		
		vec3 viewDirection = normalize(out_ViewPosition - out_FragmentPosition);

		vec3 combinedLighting = vec3(0.0);
		
		for (int lightIndex = 0; lightIndex < out_LightCount; lightIndex++)
		{
			vec3 lightDirection = normalize(out_LightPositions[lightIndex] - out_FragmentPosition);
			vec3 reflectedDirection = reflect(-lightDirection, out_Normal);
			float dot_LightNormal = max(dot(out_Normal, lightDirection), 0.0);	
			
			combinedLighting += DiffuseLight(colour, out_LightColours[lightIndex], dot_LightNormal) + SpecularLight(colour, out_LightColours[lightIndex], viewDirection, reflectedDirection);
		}
		
		vec3 finalColor = AmbiantLight(colour) + combinedLighting;
		finalColor = clamp(finalColor, vec3(0.0), vec3(1.0));

		gl_FragColor = vec4(finalColor.xyz, 1);
	}

	
	vec3 AmbiantLight(vec3 colour)
	{		
		vec3 ambientLighting = vec3(0.125) * colour;
		
		return ambientLighting;
	}
	

	
	vec3 DiffuseLight(vec3 colour, vec3 lightColour, float dot_LightNormal)
	{		
		vec3 diffuseLighting = colour * lightColour * dot_LightNormal;
		
		return diffuseLighting;
	}

	vec3 SpecularLight(vec3 colour, vec3 lightColour, vec3 viewDirection, vec3 reflectedDirection)
	{		
		float specularEffect	= pow(max(dot(viewDirection, reflectedDirection), 0.0), out_Shininess);
		vec3 specularLighting	= out_SpecularStrength * specularEffect * colour * lightColour; 
		
		return specularLighting;
	}
	
#endif