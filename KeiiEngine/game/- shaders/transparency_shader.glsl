#define MAX_LIGHTS 10
#define PI 3.1415926538

#ifdef VERTEX_SHADER
	attribute vec3 in_Position;
	attribute vec3 in_Normal;
	attribute vec2 in_TextureUV;
	
	uniform vec4 in_Colour; 
	uniform float in_Roughness;
	uniform float in_Metallic;

	uniform mat4 in_Veiwing; 
	uniform mat4 in_Projection;
	uniform mat4 in_Model;

	uniform vec3 in_ViewPosition;

	uniform float in_LightCount;
	uniform vec3 in_LightPositions[MAX_LIGHTS];
	uniform vec3 in_LightColours[MAX_LIGHTS];
	uniform float in_LightIntensitys[MAX_LIGHTS];
	
	varying vec4 out_Colour;
	varying float out_Roughness;
	varying float out_Metallic;

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
		out_Roughness = in_Roughness;
		out_Metallic = in_Metallic;
		
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
	uniform sampler2D in_AlbedoMap;
	
	varying vec4 out_Colour;
	varying float out_Roughness;
	varying float out_Metallic;

	varying vec3 out_Normal;
	varying vec2 out_TextureUV;
	
	varying vec3 out_FragmentPosition;
	varying vec3 out_ViewPosition;

	varying float out_LightCount;
	varying vec3 out_LightPositions[MAX_LIGHTS];
	varying vec3 out_LightColours[MAX_LIGHTS];
	varying float out_LightIntensitys[MAX_LIGHTS];



	vec3 LightRadiance(int lightIndex);
	vec3 BRDF(vec3 colour, float dot_LightNormal, float dot_ViewNormal, float dot_MidNormal, float dot_MidView);
	
	vec3 DiffuseLambert(vec3 colour);
	vec3 SpecularLambert(vec3 colour, float dot_LightNormal, float dot_ViewNormal, float dot_MidNormal, float dot_MidView);
	
	float Distribution(float dot_MidNormal);
	float Geomertry(float dot_LightNormal, float dot_ViewNormal);
	float SubGeomertry(float dotValue, float kValue);
	vec3 FresnelSchlick(vec3 colour, float dot_MidView);

	float ReflectionWeight(float dot_LightNormal);


	void main()
	{
		vec4 textureColour = texture2D(in_AlbedoMap, vec2(out_TextureUV.x, 1 - out_TextureUV.y));
		
		// Discard fragment if sample is transparent
		if(textureColour.a < 0.1)
			discard;


		vec3 colour = out_Colour.rgb * textureColour.rgb;

		vec3 viewDirection = normalize(out_ViewPosition - out_FragmentPosition);
		float dot_ViewNormal = max(dot(out_Normal, viewDirection), 0.0);	

		vec3 viewRadiance = vec3(0.0);
		for (int lightIndex = 0; lightIndex < out_LightCount; lightIndex++)
		{
			vec3 lightDirection = normalize(out_LightPositions[lightIndex] - out_FragmentPosition);
			vec3 midDirection = normalize(lightDirection + viewDirection);
			float dot_LightNormal = max(dot(out_Normal, lightDirection), 0.0);	
			float dot_MidNormal = max(dot(out_Normal, midDirection), 0.0);	
			float dot_MidView = max(dot(midDirection, viewDirection), 0.0);	

			vec3 BRDF = BRDF(colour, dot_LightNormal, dot_ViewNormal, dot_MidNormal, dot_MidView);

			viewRadiance += BRDF * LightRadiance(lightIndex) * dot_LightNormal;
		}

		
		// Learn OpenGL's ambient lighting code.
		vec3 ambientLighting = vec3(0.125) * colour;
		vec3 finalColor = ambientLighting + viewRadiance;

		finalColor = clamp(finalColor, vec3(0.0), vec3(1.0));
		gl_FragColor = vec4(finalColor, 1);
	}
	




	// Applies inverse square law to light colour.
	vec3 LightRadiance(int lightIndex)
	{
		float distance = distance(out_LightPositions[lightIndex], out_FragmentPosition);
		float attenuation = 1.0 / pow(distance, 2);

		return out_LightColours[lightIndex] * out_LightIntensitys[lightIndex] * attenuation;
	}

	
	// Applies colour based on the material properties of the fragment.
	vec3 BRDF(vec3 colour, float dot_LightNormal, float dot_ViewNormal, float dot_MidNormal, float dot_MidView)
	{
		vec3 specularWeight = FresnelSchlick(colour, dot_MidView);
		vec3 diffuseWeight = 1.0 - specularWeight;
		diffuseWeight *= 1.0 - out_Metallic;

		return (diffuseWeight * DiffuseLambert(colour)) + (SpecularLambert(colour, dot_LightNormal, dot_ViewNormal, dot_MidNormal, dot_MidView));
	}
	




	vec3 DiffuseLambert(vec3 colour)
	{
		return colour / PI;
	}
	
	vec3 SpecularLambert(vec3 colour, float dot_LightNormal, float dot_ViewNormal, float dot_MidNormal, float dot_MidView)
	{
		vec3 numerator = Distribution(dot_MidNormal) * Geomertry(dot_LightNormal, dot_ViewNormal) * FresnelSchlick(colour, dot_MidView);
		float denominator = 4 * dot_ViewNormal * dot_LightNormal + 0.0001;

		return numerator / denominator;
	}





	float Distribution(float dot_MidNormal)
	{
		float numerator = pow(out_Roughness, 2);
		float denominator = PI * pow((pow(dot_MidNormal, 2) * (pow(out_Roughness, 2) - 1) + 1), 2);

		return numerator / denominator;
	}

	float Geomertry(float dot_LightNormal, float dot_ViewNormal)
	{
		float kValue = pow((out_Roughness + 1), 2) / 8;

		return SubGeomertry(dot_LightNormal, kValue) * SubGeomertry(dot_ViewNormal, kValue);
	}

	float SubGeomertry(float dotValue, float kValue)
	{
		float numerator = dotValue;
		float denominator = dotValue * (1 - kValue) + kValue;

		return numerator / denominator;
	}

	vec3 FresnelSchlick(vec3 colour, float dot_MidView)
	{
		vec3 baseReflectivity = mix(vec3(0.04), colour, out_Metallic);

		return baseReflectivity + (1 - baseReflectivity) * pow(1 - dot_MidView, 5);
	}
#endif