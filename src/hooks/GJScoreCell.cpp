#include "../AnimatedIcons.hpp"
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/GJScoreCell.hpp>

using namespace geode::prelude;

class $modify(APIScoreCell, GJScoreCell) {
    struct Fields {
        ~Fields() { AnimatedIcons::releaseTouchChildren(); }
    };

    static void onModify(ModifyBase<ModifyDerive<APIScoreCell, GJScoreCell>>& self) {
        (void)self.setHookPriorityAfterPost("GJScoreCell::loadFromScore", "cvolton.betterinfo");
    }

    void loadFromScore(GJUserScore* score) {
        GJScoreCell::loadFromScore(score);

        auto touchChildren = CCArray::create();
        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            auto addToTouch = !Loader::get()->isModLoaded("cvolton.betterinfo");
            if (player->m_robotSprite) {
                player->m_robotSprite->runAnimation("idle01");
                player->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
                if (addToTouch) touchChildren->addObject(player->m_robotSprite);
            }
            if (player->m_spiderSprite) {
                player->m_spiderSprite->runAnimation("idle01");
                player->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
                if (addToTouch) touchChildren->addObject(player->m_spiderSprite);
            }
            AnimatedIcons::addTouchChildren(touchChildren);
        }

        m_fields.self();
    }
};
