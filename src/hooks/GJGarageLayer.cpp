#include "../AnimatedIcons.hpp"
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(APIGarageLayer, GJGarageLayer) {
    struct Fields {
        ~Fields() { AnimatedIcons::releaseTouchChildren(); }
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
        if (auto playerObject2 = static_cast<SimplePlayer*>(getChildByID("player2-icon"))) {
            if (!playerObject2->m_robotSprite) playerObject2->createRobotSprite(1);
            if (!playerObject2->m_spiderSprite) playerObject2->createSpiderSprite(1);

            if (playerObject2->m_robotSprite) {
                playerObject2->m_robotSprite->runAnimation("idle01");
                playerObject2->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
                touchChildren->addObject(playerObject2->m_robotSprite);
            }
            if (playerObject2->m_spiderSprite) {
                playerObject2->m_spiderSprite->runAnimation("idle01");
                playerObject2->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
                touchChildren->addObject(playerObject2->m_spiderSprite);
            }
        }
        AnimatedIcons::addTouchChildren(touchChildren);

        m_fields.self();

        return true;
    }
};
