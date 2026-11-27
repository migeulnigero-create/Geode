#pragma once
#include <Geode/Geode.hpp>
#include <unordered_set>

class TrajectoryNode : public cocos2d::CCNode
{
protected:
    static inline TrajectoryNode* s_instance = nullptr;
    static inline float s_step = 0.25f;                       // oyunun gercek fizik adimi
    static inline std::unordered_set<GameObject*> s_used;     // simulasyonda bir kez tetiklenen objeler

    GJBaseGameLayer* m_layer = nullptr;
    PlayerObject* m_sim = nullptr;
    cocos2d::CCDrawNode* m_draw = nullptr;
    bool m_simulating = false;

    ~TrajectoryNode() override;
    bool init(GJBaseGameLayer* layer);

    void update(float dt) override;
    void redraw();
    void simulate(PlayerObject* real, bool held, bool isP1);
    void copyState(PlayerObject* from, PlayerObject* to);

public:
    static TrajectoryNode* create(GJBaseGameLayer* layer);
    static TrajectoryNode* get() { return s_instance; }
    // true yalnizca simulasyon sirasinda
    static bool active() { return s_instance && s_instance->m_simulating; }

    // gercek oyuncunun PlayerObject::update(dt) degerini kaydet
    static void setStep(float dt) { if (dt > 0.05f && dt < 1.f) s_step = dt; }
    static float step() { return s_step; }
    // obje bu simulasyonda ilk kez mi tetikleniyor?
    static bool markUsed(GameObject* o) { return s_used.insert(o).second; }
};
