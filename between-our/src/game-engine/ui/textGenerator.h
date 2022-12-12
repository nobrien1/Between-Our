#pragma once

namespace gameEngine {
	namespace text {
		struct TextImage {
			unsigned char** buffer = new unsigned char* [0];
			Dimensioni size = Dimensioni(0, 0);
			TextImage() {}
			TextImage(unsigned char** buffer, Dimensioni size) : buffer(buffer), size(size) {}
			TextImage(unsigned char** buffer, int w, int h) : buffer(buffer), size(Dimensioni(w, h)) {}
		};

		void startFreetype();
		void stopFreetype();
		TextImage getTextImage(char* text, int fontSize, int dpi);
		TextImage getTextImage(char* text, int fontSize);
	}
}