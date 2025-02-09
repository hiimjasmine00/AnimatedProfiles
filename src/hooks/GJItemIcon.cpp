#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/binding/SpriteAnimationManager.hpp>
#include <Geode/modify/GJItemIcon.hpp>

using namespace geode::prelude;

class $modify(APIItemIcon, GJItemIcon) {
    bool init(UnlockType type, int id, ccColor3B color1, ccColor3B color2, bool dark, bool p5, bool noLabel, ccColor3B) {
        // Due to MSVC parameter optimization, merely using the last parameter will crash the game.
        if (!GJItemIcon::init(type, id, color1, color2, dark, p5, noLabel, {})) return false;

        if (type != UnlockType::Robot && type != UnlockType::Spider) return true;

        auto simplePlayer = static_cast<SimplePlayer*>(m_player);
        if (type == UnlockType::Robot && simplePlayer->m_robotSprite && !dark) {
            simplePlayer->m_robotSprite->runAnimation("idle01");
            simplePlayer->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
        }
        if (type == UnlockType::Spider && simplePlayer->m_spiderSprite && !dark) {
            simplePlayer->m_spiderSprite->runAnimation("idle01");
            simplePlayer->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
        }

        return true;
    }

    void changeToLockedState(float scale) {
        GJItemIcon::changeToLockedState(scale);

        if (m_unlockType != UnlockType::Robot && m_unlockType != UnlockType::Spider) return;

        auto simplePlayer = static_cast<SimplePlayer*>(m_player);
        if (m_unlockType == UnlockType::Robot && simplePlayer->m_robotSprite) simplePlayer->m_robotSprite->m_animationManager->stopAnimations();
        if (m_unlockType == UnlockType::Spider && simplePlayer->m_spiderSprite) simplePlayer->m_spiderSprite->m_animationManager->stopAnimations();
    }

    void darkenStoreItem(ccColor3B color) {
        GJItemIcon::darkenStoreItem(color);

        if (m_unlockType != UnlockType::Robot && m_unlockType != UnlockType::Spider) return;

        auto simplePlayer = static_cast<SimplePlayer*>(m_player);
        if (m_unlockType == UnlockType::Robot && simplePlayer->m_robotSprite) simplePlayer->m_robotSprite->m_animationManager->stopAnimations();
        if (m_unlockType == UnlockType::Spider && simplePlayer->m_spiderSprite) simplePlayer->m_spiderSprite->m_animationManager->stopAnimations();
    }
};
