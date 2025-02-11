#include "../AnimatedIcons.hpp"
#include <Geode/binding/GJItemIcon.hpp>
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/CommunityCreditsPage.hpp>

using namespace geode::prelude;

class $modify(APICommunityCreditsPage, CommunityCreditsPage) {
    struct Fields {
        ~Fields() { AnimatedIcons::releaseTouchChildren(); }
    };

    bool init() override {
        if (!CommunityCreditsPage::init()) return false;

        auto touchChildren = CCArray::create();
        for (auto [page, objects] : CCDictionaryExt<int, CCArray*>(m_pageObjects)) {
            if (page == m_pageObjects->count() - 1) continue;
            for (int i = 0; i < objects->count(); i += 2) {
                auto icon = static_cast<GJItemIcon*>(objects->objectAtIndex(i));
                if (icon->m_unlockType != UnlockType::Robot && icon->m_unlockType != UnlockType::Spider) continue;
                auto player = static_cast<SimplePlayer*>(icon->m_player);
                if (icon->m_unlockType == UnlockType::Robot && player->m_robotSprite) touchChildren->addObject(player->m_robotSprite);
                if (icon->m_unlockType == UnlockType::Spider && player->m_spiderSprite) touchChildren->addObject(player->m_spiderSprite);
            }
        }
        AnimatedIcons::addTouchChildren(touchChildren);

        m_fields.self();
        return true;
    }

    void goToPage(int page) {
        CommunityCreditsPage::goToPage(page);

        for (int i = 0; i < m_pageObjects->count() - 1; i++) {
            auto objects = static_cast<CCArray*>(m_pageObjects->objectForKey(i));
            for (int j = 0; j < objects->count(); j += 2) {
                auto icon = static_cast<GJItemIcon*>(objects->objectAtIndex(j));
                if (icon->m_unlockType != UnlockType::Robot && icon->m_unlockType != UnlockType::Spider) continue;
                auto player = static_cast<SimplePlayer*>(icon->m_player);
                if (icon->m_unlockType == UnlockType::Robot && player->m_robotSprite) player->m_robotSprite->setVisible(i == page);
                if (icon->m_unlockType == UnlockType::Spider && player->m_spiderSprite) player->m_spiderSprite->setVisible(i == page);
            }
        }
    }
};
