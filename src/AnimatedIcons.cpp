#include "AnimatedIcons.hpp"
#include <Geode/binding/CCAnimatedSprite.hpp>

void AnimatedIcons::addTouchChildren(cocos2d::CCArray* children) {
    if (!children || children->count() == 0) return;
    CC_SAFE_RELEASE(touchChildren);
    touchChildren = children;
    touchChildren->retain();
}

void AnimatedIcons::releaseTouchChildren() {
    CC_SAFE_RELEASE(touchChildren);
    touchChildren = nullptr;
    CC_SAFE_RELEASE(selectedChild);
    selectedChild = nullptr;
    originalScale = 1.0f;
}
