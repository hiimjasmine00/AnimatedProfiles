#include <Geode/modify/CCAnimatedSprite.hpp>

using namespace geode::prelude;

class $modify (APIAnimatedSprite, CCAnimatedSprite) {
    void animationFinished(const char* animation) override {
        CCAnimatedSprite::animationFinished(animation);
        if (auto reset = static_cast<CCBool*>(getUserObject("reset"_spr)); reset && reset->getValue()) runAnimation("idle01");
    }
};
