#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(APIGarageLayer, GJGarageLayer) {
    struct Fields {
        ~Fields() {
            auto gameManager = GameManager::get();
            gameManager->setUserObject("original-scale"_spr, nullptr);
            gameManager->setUserObject("selected-child"_spr, nullptr);
            gameManager->setUserObject("touch-children"_spr, nullptr);
        }
    };

    bool init() override {
        if (!GJGarageLayer::init()) return false;

        auto touchChildren = CCArray::create();
        if (m_playerObject->m_robotSprite) {
            m_playerObject->m_robotSprite->runAnimation("idle01");
            m_playerObject->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
            touchChildren->addObject(m_playerObject->m_robotSprite);
        }
        if (m_playerObject->m_spiderSprite) {
            m_playerObject->m_spiderSprite->runAnimation("idle01");
            m_playerObject->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
            touchChildren->addObject(m_playerObject->m_spiderSprite);
        }
        if (touchChildren->count() > 0) GameManager::get()->setUserObject("touch-children"_spr, touchChildren);

        m_fields.self();

        return true;
    }
};
