#include "../AnimatedIcons.hpp"
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(APIProfilePage, ProfilePage) {
    struct Fields {
        ~Fields() { AnimatedIcons::releaseTouchChildren(); }
    };

    static void onModify(ModifyBase<ModifyDerive<APIProfilePage, ProfilePage>>& self) {
        (void)self.setHookPriorityAfterPost("ProfilePage::loadPageFromUserInfo", "rynat.better_unlock_info");
    }

    void loadPageFromUserInfo(GJUserScore* score) {
        ProfilePage::loadPageFromUserInfo(score);

        auto touchChildren = CCArray::create();
        auto addToTouch = !Loader::get()->isModLoaded("rynat.better_unlock_info");
        if (auto playerRobot = m_mainLayer->getChildByIDRecursive("player-robot")) {
            if (auto player = findFirstChildRecursive<SimplePlayer>(playerRobot, [](auto) { return true; })) {
                if (player->m_robotSprite) {
                    player->m_robotSprite->runAnimation("idle01");
                    player->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
                    if (addToTouch) touchChildren->addObject(player->m_robotSprite);
                }
            }
        }
        if (auto playerSpider = m_mainLayer->getChildByIDRecursive("player-spider")) {
            if (auto player = findFirstChildRecursive<SimplePlayer>(playerSpider, [](auto) { return true; })) {
                if (player->m_spiderSprite) {
                    player->m_spiderSprite->runAnimation("idle01");
                    player->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
                    if (addToTouch) touchChildren->addObject(player->m_spiderSprite);
                }
            }
        }
        AnimatedIcons::addTouchChildren(touchChildren);

        m_fields.self();
    }
};
