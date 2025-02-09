#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJComment.hpp>
#include <Geode/binding/GJUserScore.hpp>
#include <Geode/binding/GJSpiderSprite.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/CommentCell.hpp>

using namespace geode::prelude;

class $modify(APICommentCell, CommentCell) {
    struct Fields {
        ~Fields() {
            auto gameManager = GameManager::get();
            gameManager->setUserObject("original-scale"_spr, nullptr);
            gameManager->setUserObject("selected-child"_spr, nullptr);
            gameManager->setUserObject("touch-children"_spr, nullptr);
        }
    };

    void loadFromComment(GJComment* comment) {
        CommentCell::loadFromComment(comment);

        if (!comment->m_userScore || (comment->m_userScore->m_iconType != IconType::Robot && comment->m_userScore->m_iconType != IconType::Spider)) return;

        if (auto player = findFirstChildRecursive<SimplePlayer>(m_mainLayer, [](auto) { return true; })) {
            auto touchChildren = CCArray::create();
            if (comment->m_userScore->m_iconType == IconType::Robot && player->m_robotSprite) {
                player->m_robotSprite->runAnimation("idle01");
                player->m_robotSprite->setUserObject("reset"_spr, CCBool::create(true));
                touchChildren->addObject(player->m_robotSprite);
            }
            if (comment->m_userScore->m_iconType == IconType::Spider && player->m_spiderSprite) {
                player->m_spiderSprite->runAnimation("idle01");
                player->m_spiderSprite->setUserObject("reset"_spr, CCBool::create(true));
                touchChildren->addObject(player->m_spiderSprite);
            }
            if (touchChildren->count() > 0) GameManager::get()->setUserObject("touch-children"_spr, touchChildren);
        }

        m_fields.self();
    }
};
