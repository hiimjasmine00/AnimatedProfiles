#include <cocos2d.h>
#include <Geode/GeneratedPredeclare.hpp>

class AnimatedIcons {
public:
    inline static CCAnimatedSprite* selectedChild = nullptr;
    inline static cocos2d::CCArray* touchChildren = nullptr;
    inline static float originalScale = 1.0f;

    static void addTouchChildren(cocos2d::CCArray*);
    static void releaseTouchChildren();
};
