#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/GJUserCell.hpp>

using namespace geode::prelude;

class $modify(APIUserCell, GJUserCell) {
    struct Fields {
        ~Fields() {
            auto gameManager = GameManager::get();
            gameManager->setUserObject("original-scale"_spr, nullptr);
            gameManager->setUserObject("selected-child"_spr, nullptr);
            gameManager->setUserObject("touch-children"_spr, nullptr);
        }
    };

    void loadFromScore(GJUserScore* score) {
        GJUserCell::loadFromScore(score);

        auto touchChildren = CCArray::create();
        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            if (player->m_robotSprite) {
                player->m_robotSprite->runAnimation("idle01");
                player->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
                touchChildren->addObject(player->m_robotSprite);
            }
            if (player->m_spiderSprite) {
                player->m_spiderSprite->runAnimation("idle01");
                player->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
                touchChildren->addObject(player->m_spiderSprite);
            }
            if (touchChildren->count() > 0) GameManager::get()->setUserObject("touch-children"_spr, touchChildren);
        }

        m_fields.self();
    }
};
