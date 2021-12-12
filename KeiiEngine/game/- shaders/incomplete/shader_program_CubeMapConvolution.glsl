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
	varying vec3 out_FragmentPosition;

	uniform samplerCube in_EnvironmentCubeMap;
	


	void main()
	{
		// 90% sure this is wrong?
		vec3 normal = normalize(out_FragmentPosition);
		vec3 irradiance = vec3(0);
		
		vec3 up = vec3(0.0, 1.0, 0.0);
		vec3 right = normalize(cross(up, normal));
		up = normalize(cross(normal, right)); 

		
		float stepCount = 50, stepDelta = 1.0 / stepCount; 
		float sampleCount = 0;
		for (float phi = 0; phi < 2 * PI; phi += stepDelta)
		{
			for (float theta = 0; theta < 0.5 * PI; theta += stepDelta)
			{
				vec3 sampleDirection = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
				vec3 alginedSampleDirection = sampleDirection.x * right + sampleDirection.y * up + sampleDirection.z * normal; 

				irradiance += texture(in_EnvironmentCubeMap, alginedSampleDirection).rgb * cos(theta) * sin(theta);
				sampleCount++;				
			}
		}
		
		irradiance = PI * irradiance * (1.0 / sampleCount);		

		gl_FragColor = vec4(irradiance, 1);
	}
#endif