	#extension GL_EXT_gpu_shader4 : enable

	varying float LightIntensity;

	void main()
	{
		vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
		vec3 lightDir = normalize(vec3(gl_LightSource[0].position));
		vec3 halfVector = normalize(gl_LightSource[0].halfVector.xyz);
		float NdotL = max(dot(lightDir, normal), 0.0);
		LightIntensity = gl_LightSource[0].diffuse*NdotL + gl_LightSource[0].ambient;
		gl_TexCoord[0]     = gl_MultiTexCoord0;
		gl_Position     = ftransform();
	}