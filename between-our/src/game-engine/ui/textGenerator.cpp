#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "uiHeader.h"
#include "textGenerator.h"

const char* FONT_PATH = "./assets/fonts/font.ttf";

namespace gameEngine {
	FT_Library library;
	FT_Face face;

	namespace text {
		void startFreetype() {
			FT_Error error;

			error = FT_Init_FreeType(&library); //initialize library
			if (error) std::cout << "Error @ initialize lib. Code: " << error << std::endl;

			error = FT_New_Face(library, FONT_PATH, 0, &face); //create face obj
			if (error) std::cout << "Error @ create face. Code: " << error << std::endl;
		}

		void stopFreetype() {
			FT_Done_Face(face);
			FT_Done_FreeType(library);
		}

		text::TextImage getTextImage(char* text, int fontSize, int dpi) {
			startFreetype();

			FT_Error error;
			FT_GlyphSlot slot;
			FT_Matrix matrix;                 /* transformation matrix */
			FT_Vector pen;
			
			const int imageHeight = (fontSize * 2);
			int imageWidth = 0;

			unsigned char** image = new unsigned char*[imageHeight];

			error = FT_Set_Char_Size(face, fontSize * 64, 0, dpi, 0); //set char size
			if (error) std::cout << "Error @ set char size. Code: " << error << std::endl;

			slot = face->glyph;

			matrix.xx = (FT_Fixed)(cos(0) * 0x10000L);
			matrix.xy = (FT_Fixed)(-sin(0) * 0x10000L);
			matrix.yx = (FT_Fixed)(sin(0) * 0x10000L);
			matrix.yy = (FT_Fixed)(cos(0) * 0x10000L);

			pen.x = 0;
			pen.y = (imageHeight * 0.25) * 64;

			for (int n = 0; n < strlen(text); n++) {
				FT_Set_Transform(face, &matrix, &pen); /* set transformation */

				error = FT_Load_Char(face, text[n], FT_LOAD_RENDER); /* load glyph image into the slot (erase previous one) */
				if (error) {
					std::cout << "Error @ load char. Code: " << error << std::endl;
					continue;
				}              

				/* now, draw to our target surface (convert position) */
				FT_Bitmap* bitmap = &slot->bitmap;
				FT_Int x = slot->bitmap_left;
				FT_Int y = imageHeight - slot->bitmap_top;
				FT_Int  xMax = slot->bitmap_left + (&slot->bitmap)->width;
				FT_Int  yMax = imageHeight - slot->bitmap_top + (&slot->bitmap)->rows;

				//expand width of image array
				for (int i = 0; i < imageHeight; i++) {
					unsigned char* newRow = new unsigned char[xMax];
					for (int j = 0; j < imageWidth; j++) {
						newRow[j] = image[i][j];
					}
					for (int k = imageWidth; k < xMax; k++) {
						newRow[k] = 0;
					}
					image[i] = newRow;
				}
				imageWidth = xMax;
				
				for (int i = x, p = 0; i < xMax; i++, p++) {
					for (int j = y, q = 0; j < yMax; j++, q++) {
						if (i < 0 || j < 0 || i >= imageWidth ||  j >= imageHeight) continue;

						image[j][i] |= bitmap->buffer[q * bitmap->width + p];
					}
				}

				/* increment pen position */
				pen.x += slot->advance.x;
				pen.y += slot->advance.y;
			}
			stopFreetype();
			return text::TextImage(image, imageWidth, imageHeight);
		}

		text::TextImage getTextImage(char* text, int fontSize) {
			return getTextImage(text, fontSize, 100);
		}
	}
}