#pragma once

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
前方宣言
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
class I_VECTOR2;
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
クラス宣言
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

class VECTOR2 {	//float型を２つ保持するclass
public:
	float x;
	float y;

	VECTOR2();
	VECTOR2(float a, float b);
	VECTOR2 operator+(VECTOR2 vec);
	VECTOR2 operator-(VECTOR2 vec);
	VECTOR2 operator*(float value);
	VECTOR2 operator+(I_VECTOR2 vec);
};

class I_VECTOR2 {	//int型のVECTOR UV値の保持に使う
public:
	int u;
	int v;

	I_VECTOR2();
	I_VECTOR2(int a, int b);
	I_VECTOR2 operator+(I_VECTOR2 vec);
	I_VECTOR2 operator-(I_VECTOR2 vec);
};
