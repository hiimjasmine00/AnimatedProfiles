#include "../AnimatedIcons.hpp"
#include <Geode/binding/CCAnimatedSprite.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>

using namespace geode::prelude;

class $modify(APITouchDispatcher, CCTouchDispatcher) {
    void touches(CCSet* touches, CCEvent* event, unsigned int uIndex) {
        CCTouchDispatcher::touches(touches, event, uIndex);

        switch ((ccTouchType)uIndex) {
            case CCTOUCHBEGAN: {
                if (!AnimatedIcons::touchChildren || AnimatedIcons::touchChildren->count() == 0) return;
                auto touchLocation = static_cast<CCTouch*>(touches->anyObject())->getLocation();
                for (auto child : CCArrayExt<CCAnimatedSprite*>(AnimatedIcons::touchChildren)) {
                    if (!child->isVisible()) continue;
                    if (child->boundingBox().containsPoint(child->getParent()->convertToNodeSpace(touchLocation))) {
                        selectChild(child);
                        break;
                    }
                }
                break;
            }
            case CCTOUCHMOVED: {
                if (!AnimatedIcons::touchChildren || AnimatedIcons::touchChildren->count() == 0) return;
                auto touchLocation = static_cast<CCTouch*>(touches->anyObject())->getLocation();
                CCAnimatedSprite* selectedChild = nullptr;
                for (auto child : CCArrayExt<CCAnimatedSprite*>(AnimatedIcons::touchChildren)) {
                    if (!child->isVisible()) continue;
                    if (child->boundingBox().containsPoint(child->getParent()->convertToNodeSpace(touchLocation))) {
                        selectedChild = child;
                        break;
                    }
                }
                if (selectedChild != AnimatedIcons::selectedChild) {
                    deselectChild();
                    selectChild(selectedChild);
                }
                break;
            }
            case CCTOUCHENDED: {
                if (!AnimatedIcons::selectedChild) return;
                auto selectedChild = AnimatedIcons::selectedChild;
                auto retainCount = AnimatedIcons::selectedChild->retainCount();
                auto originalScale = AnimatedIcons::originalScale;
                deselectChild();
                if (retainCount > 1) {
                    selectedChild->stopActionByTag(0);
                    selectedChild->setScale(originalScale);
                    selectedChild->runAnimationForced("idle02");
                }
                break;
            }
            case CCTOUCHCANCELLED:
                deselectChild();
                break;
            default:
                break;
        }
    }

    void selectChild(CCAnimatedSprite* child) {
        if (!child) return;

        AnimatedIcons::originalScale = child->getScale();
        auto scaleAction = CCEaseBounceOut::create(CCScaleTo::create(0.3f, child->getScale() * 1.26f));
        scaleAction->setTag(0);
        child->runAction(scaleAction);
        AnimatedIcons::selectedChild = child;
        child->retain();
    }

    void deselectChild() {
        if (!AnimatedIcons::selectedChild) return;

        AnimatedIcons::selectedChild->stopActionByTag(0);
        if (AnimatedIcons::selectedChild->retainCount() > 1) {
            auto scaleAction = CCEaseBounceOut::create(CCScaleTo::create(0.4f, AnimatedIcons::originalScale));
            scaleAction->setTag(0);
            AnimatedIcons::selectedChild->runAction(scaleAction);
        }
        AnimatedIcons::selectedChild->release();
        AnimatedIcons::selectedChild = nullptr;
        AnimatedIcons::originalScale = 1.0f;
    }
};
