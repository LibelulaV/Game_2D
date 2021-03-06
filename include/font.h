#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "types.h"
#include "image.h"
#include "array.h"
#include "glyph.h"

class Font : public Image {
public:
	Font(const String& filename);
	virtual uint16 GetSize() const;
	virtual uint32 GetTextWidth(const String& text) const;
	virtual uint32 GetTextHeight(const String& text) const;
	virtual void Render(const String& text, double x, double y) const;
	void RenderWithMeassures(const String & text, double x, double y, double scalex, double scaley) const;
private:
	Array<Glyph> glyphs;
};

#endif