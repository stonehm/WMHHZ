#pragma once

#include "game.h"
#include "CSprite2d.h"
#include "../deps/func_wrapper/func_wrapper.hpp"

typedef unsigned __int16 CharType;

struct CFontSizes
{
	__int16 PropValues[209];
	__int16 UnpropValue;
};

class CFontRenderState
{
public:
	__int32 Useless;
	CVector2D Pos;
	CVector2D Scale;
	CRGBA Color;
	float JustifyWrap;
	float Slant;
	CVector2D SlantRefPoint;
	bool KeepColor;
	bool BaseCharset;
	bool Prop;
	__int16 FontStyle;
};
static_assert(sizeof(CFontRenderState) == 0x30, "CFontRenderState is wrong.");

struct FontBufferEntry
{
	CFontRenderState data;
	CharType text[1];
};

union FontBufferPointer
{
	CFontRenderState *pdata;
	CharType *ptext;
	unsigned __int32 addr;
};
static_assert(sizeof(FontBufferPointer) == 4, "FontBufferPointer is wrong.");

class CFontDetails
{
public:
	CRGBA Color;
	CVector2D Scale;
	float Slant;
	CVector2D SlantRefPoint;
	bool Justify;
	bool Centre;
	bool RightJustify;
	bool Background;
	bool BackGroundOnlyText;
	bool Prop;
	bool KeepColor;
	bool UselessFlag1;
	bool UselessFlag2;
	__int8 pad1[3];
	float AlphaFade;
	CRGBA BackgroundColor;
	float WrapX;
	float CentreSize;
	float RightJustifyWrap;
	__int16 FontStyle;
	bool BaseCharset;
	__int8 pad2[5];
	__int16 DropShadowPos;
	CRGBA DropColor;
	bool IsBlip;
	__int8 pad3;
	unsigned __int32 BlipStartTime;
	bool UselessFlag3;
	__int8 pad4[3];
	__int32 TextCount;
};
static_assert(sizeof(CFontDetails) == 0x54, "CFontDetails is wrong.");

class CFont
{
public:
	static const __int16 iMaxCharWidth;
	static const float fMaxCharWidth;

	static char fontPath[];
	static char textPath[];

	static CFontSizes *Size;

	static FontBufferPointer FontBuffer;
	static FontBufferPointer *FontBufferIter;
	static CFontRenderState *RenderState;

	static CSprite2d *Sprite;
	static CSprite2d ChsSprite;
	static CSprite2d ChsSlantSprite;

	static CFontDetails *Details;

	static cdecl_func_wrapper<CharType(CharType arg_char)>
		fpFindNewCharacter;

	static cdecl_func_wrapper<CharType *(CharType *)>
		fpParseTokenEPt;

	static cdecl_func_wrapper<CharType *(CharType *arg_text, CRGBA &result_color, bool &result_blip, bool &result_bold)>
		fpParseTokenEPtR5CRGBARbRb;

	static cdecl_func_wrapper<void(float arg_x, float arg_y, CharType arg_char)>
		fpPrintChar;

	static cdecl_func_wrapper<void(float arg_x, float arg_y, unsigned int useless, CharType *arg_strbeg, CharType *arg_strend, float justifywrap)>
		fpPrintStringPart;

	static float GetCharacterSize(CharType arg_char, __int16 nFontStyle, bool bBaseCharset, bool bProp, float fScaleX);
	static float GetCharacterSizeNormal(CharType arg_char);
	static float GetCharacterSizeDrawing(CharType arg_char);

	static float __cdecl GetStringWidth(CharType *arg_text, bool arg_getall);
	static CharType *GetNextSpace(CharType *arg_text);

	static __int16 __cdecl GetNumberLines(float arg_x, float arg_y, CharType *arg_text);
	static void GetTextRect(CRect *result, float arg_x, float arg_y, CharType *arg_text);

	static void __cdecl PrintString(float arg_x, float arg_y, CharType *arg_text);
	static void __cdecl RenderFontBuffer();
	static void PrintCHSChar(float arg_x, float arg_y, CharType arg_char);
	static void PrintCharDispatcher(float arg_x, float arg_y, CharType arg_char);

	template <unsigned i100xScale>
	static void __cdecl SetScaleHacked(float scalex, float scaley)
	{
		Details->Scale.x = scaley / i100xScale / 100;
		Details->Scale.y = scaley;
	}

	static void __cdecl DisableSlant(float slant);

	static void __cdecl LoadCHSFont();
	static void __cdecl UnloadCHSFont(int dummy);

	CFont();
};
