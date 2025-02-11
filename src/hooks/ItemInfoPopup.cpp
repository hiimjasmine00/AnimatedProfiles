#include "../AnimatedIcons.hpp"
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>

using namespace geode::prelude;

class $modify(APIItemInfoPopup, ItemInfoPopup) {
    struct Fields {
        ~Fields() { AnimatedIcons::releaseTouchChildren(); }
    };

    bool init(int id, UnlockType type) {
        if (!ItemInfoPopup::init(id, type)) return false;

        if (type != UnlockType::Robot && type != UnlockType::Spider) return true;

        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            auto touchChildren = CCArray::create();
            if (type == UnlockType::Robot && player->m_robotSprite) touchChildren->addObject(player->m_robotSprite);
            if (type == UnlockType::Spider && player->m_spiderSprite) touchChildren->addObject(player->m_spiderSprite);
            AnimatedIcons::addTouchChildren(touchChildren);
        }

        m_fields.self();
        return true;
    }
};
