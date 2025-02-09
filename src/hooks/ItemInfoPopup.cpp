#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>

using namespace geode::prelude;

class $modify(APIItemInfoPopup, ItemInfoPopup) {
    struct Fields {
        ~Fields() {
            auto gameManager = GameManager::get();
            gameManager->setUserObject("original-scale"_spr, nullptr);
            gameManager->setUserObject("selected-child"_spr, nullptr);
            gameManager->setUserObject("touch-children"_spr, nullptr);
        }
    };

    bool init(int id, UnlockType type) {
        if (!ItemInfoPopup::init(id, type)) return false;

        if (type != UnlockType::Robot && type != UnlockType::Spider) return true;

        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            auto touchChildren = CCArray::create();
            if (type == UnlockType::Robot && player->m_robotSprite) touchChildren->addObject(player->m_robotSprite);
            if (type == UnlockType::Spider && player->m_spiderSprite) touchChildren->addObject(player->m_spiderSprite);
            if (touchChildren->count() > 0) GameManager::get()->setUserObject("touch-children"_spr, touchChildren);
        }

        m_fields.self();
        return true;
    }
};
