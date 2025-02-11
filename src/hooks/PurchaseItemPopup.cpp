#include "../AnimatedIcons.hpp"
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/GJStoreItem.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>

using namespace geode::prelude;

class $modify(APIPurchaseItemPopup, PurchaseItemPopup) {
    struct Fields {
        ~Fields() { AnimatedIcons::releaseTouchChildren(); }
    };

    bool init(GJStoreItem* item) {
        if (!PurchaseItemPopup::init(item)) return false;

        if (item->m_unlockType.value() != (int)UnlockType::Robot && item->m_unlockType.value() != (int)UnlockType::Spider) return true;

        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            auto touchChildren = CCArray::create();
            if (item->m_unlockType.value() == (int)UnlockType::Robot && player->m_robotSprite) touchChildren->addObject(player->m_robotSprite);
            if (item->m_unlockType.value() == (int)UnlockType::Spider && player->m_spiderSprite) touchChildren->addObject(player->m_spiderSprite);
            AnimatedIcons::addTouchChildren(touchChildren);
        }

        m_fields.self();
        return true;
    }
};
