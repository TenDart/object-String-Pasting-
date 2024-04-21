#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Windows.h>
#include <fstream>
using namespace geode::prelude;

class $modify(PasteBtnEditor, EditorUI) {
	bool init(LevelEditorLayer * editorLayer) {
		if (!EditorUI::init(editorLayer)) return false;
		auto buttonSprite = CircleButtonSprite::create(CCLabelBMFont::create("Paste", "bigFont.fnt"), CircleBaseColor::Blue, CircleBaseSize::Small);
		auto pasteBtn = CCMenuItemSpriteExtra::create(
			buttonSprite, this, menu_selector(PasteBtnEditor::onPasteBtn)
		);
		pasteBtn->setID("paste_button"_spr);	
		auto menu = getChildByID("undo-menu");

		if (menu != nullptr) {
			menu->addChild(pasteBtn);
			menu->updateLayout();
		}

		return true;
	}
	
	void onPasteBtn(cocos2d::CCObject* sender) {
		auto edLayer = LevelEditorLayer::get();
		if (IsClipboardFormatAvailable(CF_TEXT)) {
			OpenClipboard(0);
			HANDLE hData = GetClipboardData(CF_TEXT);
			auto text = (char*)GlobalLock(hData);
			GlobalUnlock(hData);
			CloseClipboard();
			edLayer->createObjectsFromString(text, 1, 1);
		}
		else
		{
			FLAlertLayer::create("Error!", "Your clipboard doesnt contain object string!", "OK")->show();
		}
	}
};