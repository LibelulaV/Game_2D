#include "../include/renderer.h"
#include "../include/font.h"
#include "../include/glinclude.h"
#include "../include/image.h"
#include "../include/math.h"

#include <math.h>

#define ELLIPSEPOINTS 32

Renderer* Renderer::renderer = NULL;

void Renderer::SetBlendMode(BlendMode blendMode) const { // src_factor * src_color + dst_factor * dst_color
    switch ( blendMode ) {
	case SOLID:
		// Implementar solid blending: rgb_origen
		glBlendFunc(GL_ONE, GL_ZERO); 
		break;
	case ALPHA:
		// Implementar alpha blending: rgba_origen + rgb_destino * (1 - alpha_origen)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case MULTIPLICATIVE:
		// Implementar multiplicative blending: rgb_origen * rgb_destino
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		break;
	case ADDITIVE:
		// Implementar additive blending: rgba_origen + rgb_destino
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	}
}

void Renderer::SetColor(uint8 r, uint8 g, uint8 b, uint8 a) const {
	glColor4ub(r, g, b, a);
}

void Renderer::SetOrigin(double x, double y) const {
	// Configurar matriz de modelado
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-x, -y, 0); 
}

void Renderer::Clear(uint8 r, uint8 g, uint8 b) const {
	// Limpiar el backbuffer
	glClearColor(r, g, b, 0); 
	glClear(GL_COLOR_BUFFER_BIT); 
}

void Renderer::DrawPoint(double x, double y) const {
	GLdouble vertices[] = {x, y};
	GLdouble texCoords[] = {0, 0};
	glBindTexture(GL_TEXTURE_2D, 0);
	glVertexPointer(2, GL_DOUBLE, 0, vertices);
	glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	glDrawArrays(GL_POINTS, 0, 1);
}

void Renderer::DrawTriangle(double x, double y, double width, double height) const {
	GLdouble vertices[] = { x, y, x, y + height, x + width, y + height / 2};
	GLdouble texCoords[] = { 0, 0, 0, 0, 0, 0 };
	glBindTexture(GL_TEXTURE_2D, 0);
	glVertexPointer(2, GL_DOUBLE, 0, vertices);
	glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}

void Renderer::DrawLine(double x1, double y1, double x2, double y2) const {
	GLdouble vertices[] = {x1, y1, x2, y2};
	GLdouble texCoords[] = {0, 0, 0, 0};
	glBindTexture(GL_TEXTURE_2D, 0);
	glVertexPointer(2, GL_DOUBLE, 0, vertices);
	glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	glDrawArrays(GL_LINES, 0, 2);
}

void Renderer::DrawRect(double x, double y, double width, double height) const {
	GLdouble vertices[] = {x, y, x+width, y, x, y+height, x+width, y+height};
	GLdouble texCoords[] = {0, 0, 0, 0, 0, 0, 0, 0};
	glBindTexture(GL_TEXTURE_2D, 0);
	glVertexPointer(2, GL_DOUBLE, 0, vertices);
	glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Renderer::DrawEllipse(double x, double y, double xradius, double yradius) const {
	GLdouble vertices[ELLIPSEPOINTS*2];
	for ( uint32 i = 0; i < ELLIPSEPOINTS; i++ ) {
		vertices[i*2] = x + (DegCos(i * 360.0 / ELLIPSEPOINTS) * xradius);
		vertices[i*2+1] = y + (DegSin(i * 360.0 / ELLIPSEPOINTS) * yradius);
	}

	GLdouble texCoords[ELLIPSEPOINTS*2];
	memset(texCoords, 0, ELLIPSEPOINTS*2*sizeof(GLdouble));

	glBindTexture(GL_TEXTURE_2D, 0);
	glVertexPointer(2, GL_DOUBLE, 0, vertices);
	glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSEPOINTS);
}

/*
 *	Acordarse de que hay par�metros que se pueden cambiar. 
 */
uint32 Renderer::GenImage(uint8 * buffer, uint16 width, uint16 height) const
{
	uint32 gltex; // o GLuint
	glGenTextures(1, &gltex); // Generaci�n textura
	glBindTexture(GL_TEXTURE_2D, gltex); // Activaci�n textura. Tambi�n vale: Renderer::BindImage(gltex); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Par�metros REDUCCI�N textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Par�metros AMPLIACI�N textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	return gltex;
}

void Renderer::UpdateImage(uint8 * buffer, uint16 width, uint16 height) const
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}

void Renderer::BindImage(uint32 glhandle) const
{
	glBindTexture(GL_TEXTURE_2D, glhandle);
}

void Renderer::DeleteImage(uint32 glhandle) const
{
	glDeleteTextures(1, &glhandle);
}

void Renderer::DrawImage(const Image* image, double x, double y, uint32 frame, double width, double height, double ang) const {

	if ( width == 0  ||  height == 0 ) {
        width = image->GetWidth();
        height = image->GetHeight();
    }

    uint32 row = (uint32)floor(frame * 1.0 / uint32(image->GetHFrames()));
    uint32 column = frame % image->GetHFrames();
    GLdouble handlexscale = width / image->GetWidth();
    GLdouble handleyscale = height / image->GetHeight();
    GLdouble ustep = image->GetLastU() / image->GetHFrames();
    GLdouble vstep = image->GetLastV() / image->GetVFrames();
    GLdouble ubegin = ustep*column;
    GLdouble vbegin = vstep*row;
    GLdouble uend = ubegin + ustep;
    GLdouble vend = vbegin + vstep;
    GLdouble x0 = -(image->GetHandleX()*handlexscale);
    GLdouble y0 = -(image->GetHandleY()*handleyscale);
    GLdouble x1 = -(image->GetHandleX()*handlexscale) + width;
    GLdouble y1 = -(image->GetHandleY()*handleyscale) + height;
    GLdouble vertices[] = {x0, y0, x1, y0, x0, y1, x1, y1};
    GLdouble texCoords[] = {ubegin, vbegin, uend, vbegin, ubegin, vend, uend, vend};

    glPushMatrix();
    glTranslated(x, y, 0);
    glRotated(ang, 0, 0, -1);
    image->Bind();
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glPopMatrix();
}

void Renderer::DrawTiledImage(const Image* image, double x, double y, double width, double height, double offsetx, double offsety) const {
	GLdouble ubegin = offsetx / image->GetWidth();
	GLdouble vbegin = offsety / image->GetHeight();
	GLdouble uend = (offsetx + width) / image->GetWidth();
	GLdouble vend = (offsety + height) / image->GetHeight();
	GLdouble vertices[] = {0, 0, width, 0, 0, height, width, height};
	GLdouble texCoords[] = { ubegin, vbegin,  uend, vbegin,  ubegin, vend,  uend, vend };
	
	glPushMatrix();
	glTranslated(x, y, 0);
	image->Bind();
	glVertexPointer(2, GL_DOUBLE, 0, vertices);
	glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glPopMatrix();
}

void Renderer::PushMatrix() const {
	glPushMatrix(); 
}

void Renderer::PopMatrix() const {
	glPopMatrix(); 
}

void Renderer::TranslateMatrix(double x, double y, double z) const {
	glTranslated(x, y, z);
}

void Renderer::RotateMatrix(double angle, double x, double y, double z) const {
	glRotated(angle, x, y, z);
}

void Renderer::DrawText(const Font* font, const String &text, double x, double y) const {
	font->Render(text, x, y);
}

void Renderer::DrawTexWithMeassures(const Font* font, const String &text, double x, double y, double w, double h) const {
	font->RenderWithMeassures(text, x, y, w, h);
}

void Renderer::GetTextImage(void * const buffer) const {
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}
