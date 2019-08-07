/************************************************************************/
/*
@author:  junliang
@brief:   
@time:    2018/11/14
*/
/************************************************************************/
#pragma once


#include "freetype/config/ftheader.h"
#include FT_FREETYPE_H

#include "GlyphData.h"
#include "GlyphAtlas.h"

NS_MN_BEGIN
struct Character {
	uint32     TextureID;
	MN::Vec2f Size;
	MN::Vec2f Bearing;    // baseline offset
	uint32     Advance;    // distance between current origin text to next origin text
};


class Font
{
public:
	Font(unsigned int fontSize, FT_Face* face, MN::ObjectMgr* pObjMgr);
	FT_Face *face() const;
	void setFace(FT_Face *face);
	unsigned int getCharIndex(unsigned long c);
	GlyphData getGlyphDataFromChar(unsigned long c);
	void generateAsciiMap();
	unsigned int getFontSize() const;
	bool isUnvisibleChar(unsigned long c);
	unsigned int getSpecialAdvance(unsigned long c, unsigned int baseAdvance);
	GlyphAtlas *getGlyphAtlas() const;
	void setGlyphAtlas(GlyphAtlas *glyphAtlas);
private:
	void initAsciiData(MN::ObjectMgr* pObjMgr);
	unsigned int m_fontSize;
	FT_Face * m_face;
	GlyphAtlas * m_glyphAtlas;
	//std::map<unsigned char, Character> Characters;

};

NS_MN_END