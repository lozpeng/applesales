#ifndef _COLOR_DEFINE_H_
#define _COLOR_DEFINE_H_
namespace Display
{

class RGBColor
{
public:
	RGBColor():red(0),green(0),blue(0){}
	RGBColor(int r,int g,int b):red(r),green(g),blue(b){}
public:

public:
	int red;
	int green;
	int blue;
};

class HSVColor
{
public:
	HSVColor():Hue(0),Saturation(0),Value(0){}
	HSVColor(int h,int s,int v):Hue(h),Saturation(s),Value(v){}
public:

	void toRGBColor(RGBColor *outColor)
	{
		
	}

public:
	int Hue; //色调
	int Saturation; //饱和度
	int Value; //纯度
};

class HSLColor
{
public:
	HSLColor():Hue(0),Saturation(0),Light(0){}
	HSLColor(int h,int s,int l):Hue(h),Saturation(s),Light(l){}
public:

	void toRGBColor(RGBColor *outColor)
	{
		if(!outColor)
		{
			return;
		}
		float h = (float)Hue;                  // h must be [0, 360]
		float s = Saturation/100.f; // s must be [0, 1]
		float l = Light/100.f;      // l must be [0, 1]
		float R, G, B;
		if(Saturation == 0)
		{
			
			R = G = B = l*255.f;
		}
		else
		{
			float q = (l<0.5f)?(l * (1.0f+s)):(l+s - (l*s));
			float p = (2.0f * l) - q;
			float Hk = h/360.0f;
			float T[3];
			T[0] = Hk + 0.3333333f; // Tr   0.3333333f=1.0/3.0
			T[1] = Hk;              // Tb
			T[2] = Hk - 0.3333333f; // Tg
			for(int i=0; i<3; i++)
			{
				if(T[i] < 0) T[i] += 1.0f;
				if(T[i] > 1) T[i] -= 1.0f;
				if((T[i]*6) < 1)
				{
					T[i] = p + ((q-p)*6.0f*T[i]);
				}
				else if((T[i]*2.0f) < 1) //(1.0/6.0)<=T[i] && T[i]<0.5
				{
					T[i] = q;
				}
				else if((T[i]*3.0f) < 2) // 0.5<=T[i] && T[i]<(2.0/3.0)
				{
					T[i] = p + (q-p) * ((2.0f/3.0f) - T[i]) * 6.0f;
				}
				else T[i] = p;
			}
			R = T[0]*255.0f;
			G = T[1]*255.0f;
			B = T[2]*255.0f;
		}
		outColor->red = (BYTE)((R>255)? 255 : ((R<0)?0 : R));
		outColor->green = (BYTE)((G>255)? 255 : ((G<0)?0 : G));
		outColor->blue = (BYTE)((B>255)? 255 : ((B<0)?0 : B));
	}

public:
	int Hue; //色调 [0-360]
	int Saturation; //饱和度 [0-100]
	int Light; //亮度 [0-100]
};

}

#endif