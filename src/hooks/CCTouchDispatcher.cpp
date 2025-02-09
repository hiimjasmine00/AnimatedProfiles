#include <Geode/binding/CCAnimatedSprite.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>

using namespace geode::prelude;

class $modify(CCTouchDispatcher) {
    void selectChild(CCNode* child) {
        auto gameManager = GameManager::get();
        gameManager->setUserObject("original-scale"_spr, CCFloat::create(child->getScale()));
        auto scaleAction = CCEaseBounceOut::create(CCScaleTo::create(0.3f, child->getScale() * 1.26f));
        scaleAction->setTag(0);
        child->runAction(scaleAction);
        gameManager->setUserObject("selected-child"_spr, child);
    }

    void deselectChild() {
        auto gameManager = GameManager::get();
        auto selectedChild = static_cast<CCNode*>(gameManager->getUserObject("selected-child"_spr));
        if (!selectedChild) return;

        selectedChild->stopActionByTag(0);
        if (selectedChild->retainCount() > 1) {
            auto originalScale = static_cast<CCFloat*>(gameManager->getUserObject("original-scale"_spr));
            auto scaleAction = CCEaseBounceOut::create(CCScaleTo::create(0.4f, originalScale ? originalScale->getValue() : 1.0f));
            scaleAction->setTag(0);
            selectedChild->runAction(scaleAction);
        }
        gameManager->setUserObject("selected-child"_spr, nullptr);
        gameManager->setUserObject("original-scale"_spr, nullptr);
    }

    void touches(CCSet* touches, CCEvent* event, unsigned int uIndex) {
        CCTouchDispatcher::touches(touches, event, uIndex);

        switch ((ccTouchType)uIndex) {
            case CCTOUCHBEGAN:
                onTouchesBegan(touches, event);
                break;
            case CCTOUCHMOVED:
                onTouchesMoved(touches, event);
                break;
            case CCTOUCHENDED:
                onTouchesEnded(touches, event);
                break;
            case CCTOUCHCANCELLED:
                onTouchesCancelled(touches, event);
                break;
            default:
                break;
        }
    }

    void onTouchesBegan(CCSet* touches, CCEvent* event) {
        auto touch = static_cast<CCTouch*>(touches->anyObject());
        auto touchLocation = touch->getLocation();
        auto touchChildren = static_cast<CCArray*>(GameManager::get()->getUserObject("touch-children"_spr));
        if (!touchChildren || touchChildren->count() == 0) return;

        for (auto child : CCArrayExt<CCNode*>(touchChildren)) {
            if (!child->isVisible()) continue;
            if (child->boundingBox().containsPoint(child->getParent()->convertToNodeSpace(touchLocation))) {
                selectChild(child);
                break;
            }
        }
    }

    void onTouchesMoved(CCSet* touches, CCEvent* event) {
        auto touch = static_cast<CCTouch*>(touches->anyObject());
        auto touchLocation = touch->getLocation();
        auto gameManager = GameManager::get();
        auto touchChildren = static_cast<CCArray*>(gameManager->getUserObject("touch-children"_spr));
        if (!touchChildren || touchChildren->count() == 0) return;

        CCNode* selectedChild = nullptr;
        for (auto child : CCArrayExt<CCNode*>(touchChildren)) {
            if (!child->isVisible()) continue;
            if (child->boundingBox().containsPoint(child->getParent()->convertToNodeSpace(touchLocation))) {
                selectedChild = child;
                break;
            }
        }

        if (selectedChild != static_cast<CCNode*>(gameManager->getUserObject("selected-child"_spr))) {
            deselectChild();
            if (selectedChild) selectChild(selectedChild);
        }
    }

    void onTouchesEnded(CCSet* touches, CCEvent* event) {
        auto gameManager = GameManager::get();
        auto selectedChild = static_cast<CCNode*>(gameManager->getUserObject("selected-child"_spr));
        if (!selectedChild) return;

        auto retainCount = selectedChild->retainCount();
        auto originalScale = static_cast<CCFloat*>(gameManager->getUserObject("original-scale"_spr));
        deselectChild();
        if (selectedChild && retainCount > 1) {
            selectedChild->stopActionByTag(0);
            selectedChild->setScale(originalScale ? originalScale->getValue() : 1.0f);
            static_cast<CCAnimatedSprite*>(selectedChild)->runAnimationForced("idle02");
        }
    }

    void onTouchesCancelled(CCSet* touches, CCEvent* event) {
        deselectChild();
    }
};
