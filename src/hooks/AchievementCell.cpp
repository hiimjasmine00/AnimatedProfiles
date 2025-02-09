#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/AchievementCell.hpp>

using namespace geode::prelude;

class $modify(APIAchievementCell, AchievementCell) {
    struct Fields {
        ~Fields() {
            auto gameManager = GameManager::get();
            gameManager->setUserObject("original-scale"_spr, nullptr);
            gameManager->setUserObject("selected-child"_spr, nullptr);
            gameManager->setUserObject("touch-children"_spr, nullptr);
        }
    };

    void loadFromDict(CCDictionary* dict) {
        AchievementCell::loadFromDict(dict);

        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            auto touchChildren = CCArray::create();
            if (player->m_robotSprite) touchChildren->addObject(player->m_robotSprite);
            if (player->m_spiderSprite) touchChildren->addObject(player->m_spiderSprite);
            if (touchChildren->count() > 0) GameManager::get()->setUserObject("touch-children"_spr, touchChildren);
        }

        m_fields.self();
    }
};
