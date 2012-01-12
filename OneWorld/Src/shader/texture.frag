	#extension GL_EXT_gpu_shader4 : enable
	uniform sampler2DArray tex;
	varying float LightIntensity;

	void main()
	{
		vec4 texCoord = (vec4(gl_TexCoord[0].st, floor(gl_TexCoord[0].r), gl_TexCoord[0].q));
		vec4 mixcolor = gl_Color;

		vec4 color7 = texture2DArray(tex, vec3(texCoord.st, 7));
		vec3 tcolor3_7 = mix(mixcolor.rgb,color7.rgb*LightIntensity,color7.a);
		mixcolor = vec4(tcolor3_7,mixcolor.a);

		vec4 color6 = texture2DArray(tex, vec3(texCoord.st, 6));
		vec3 tcolor3_6 = mix(mixcolor.rgb,color6.rgb*LightIntensity,color6.a);
		mixcolor = vec4(tcolor3_6,mixcolor.a);

		vec4 color5 = texture2DArray(tex, vec3(texCoord.st, 5));
		vec3 tcolor3_5 = mix(mixcolor.rgb,color5.rgb*LightIntensity,color5.a);
		mixcolor = vec4(tcolor3_5,mixcolor.a);

		vec4 color4 = texture2DArray(tex, vec3(texCoord.st, 4));
		vec3 tcolor3_4 = mix(mixcolor.rgb,color4.rgb*LightIntensity,color4.a);
		mixcolor = vec4(tcolor3_4,mixcolor.a);

		vec4 color3 = texture2DArray(tex, vec3(texCoord.st, 3));
		vec3 tcolor3_3 = mix(mixcolor.rgb,color3.rgb*LightIntensity,color3.a);
		mixcolor = vec4(tcolor3_3,mixcolor.a);

		vec4 color2 = texture2DArray(tex, vec3(texCoord.st, 2));
		vec3 tcolor3_2 = mix(mixcolor.rgb,color2.rgb*LightIntensity,color2.a);
		mixcolor = vec4(tcolor3_2,mixcolor.a);

		vec4 color1 = texture2DArray(tex, vec3(texCoord.st, 1));
		vec3 tcolor3_1 = mix(mixcolor.rgb,color1.rgb*LightIntensity,color1.a);
		mixcolor = vec4(tcolor3_1,mixcolor.a);

		vec4 color0 = texture2DArray(tex, vec3(texCoord.st, 0));
		vec3 tcolor3_0 = mix(mixcolor.rgb,color0.rgb*LightIntensity,color0.a);
		mixcolor = vec4(tcolor3_0,mixcolor.a);

		gl_FragColor=mixcolor;
	}