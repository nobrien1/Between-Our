#include "uiHeader.h"

namespace gameEngine {
	namespace ui {
		void Nestable::addUiElement(UiElement* element, int zIndex) {
			//TODO: implement z indexes
			addUiElement(element);
		}

		void Nestable::addUiElement(UiElement* element) {
			//TODO: implement z indexes
			UiElement** newList = new UiElement * [childCount + 1];
			for (int i = 0; i < childCount; i++) {
				newList[i] = children[i];
			}
			newList[childCount] = element;
			childCount += 1;
			children = newList;
		}
	}
}