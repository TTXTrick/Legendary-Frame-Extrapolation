#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Global state to track positions and timing for interpolation
struct ExtrapolationState {
    CCPoint lastPosition;
    CCPoint currentPosition;
    float timeSinceLastTick = 0.0f;
    float tickRate = 1.0f / 240.0f; // Default GD 2.2 physics tick rate
};

static std::map<PlayerObject*, ExtrapolationState> s_playerStates;

class $modify(ExtrapolatedPlayer, PlayerObject) {
    void update(float dt) {
        PlayerObject::update(dt);

        // Check if our optional setting is toggled on
        if (!Mod::get()->getSettingValue<bool>("enable-extrapolation")) {
            return;
        }

        // Save the state immediately after the physics tick
        auto& state = s_playerStates[this];
        state.lastPosition = state.currentPosition;
        state.currentPosition = this->getPosition();
        
        // Reset the timer since a tick just happened
        state.timeSinceLastTick = 0.0f;
    }

    void visit() {
        if (!Mod::get()->getSettingValue<bool>("enable-extrapolation")) {
            PlayerObject::visit(); // Run normal rendering
            return;
        }

        auto& state = s_playerStates[this];
        
        // If the player moved an excessive amount in one tick (e.g., entered a portal),
        // we skip extrapolation this frame to prevent visual "sweeping" glitches.
        if (ccpDistance(state.lastPosition, state.currentPosition) > 50.0f) {
            PlayerObject::visit();
            return;
        }

        // Calculate interpolation factor (alpha)
        float alpha = state.timeSinceLastTick / state.tickRate;
        
        // Cap alpha to prevent over-extrapolating if lag occurs
        if (alpha > 1.0f) alpha = 1.0f;

        // Calculate the smooth extrapolated position
        CCPoint extrapolatedPos = ccp(
            state.lastPosition.x + (state.currentPosition.x - state.lastPosition.x) * alpha,
            state.lastPosition.y + (state.currentPosition.y - state.lastPosition.y) * alpha
        );

        // Temporarily set the position to the smoothed coordinates for rendering
        CCPoint realPos = this->getPosition();
        this->setPosition(extrapolatedPos);

        // Call the original rendering function
        PlayerObject::visit();

        // Restore the real physics position so the game logic doesn't break
        this->setPosition(realPos);
    }
};

class $modify(ExtrapolationPlayLayer, PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);
        
        if (Mod::get()->getSettingValue<bool>("enable-extrapolation")) {
            // Advance the visual timer for all active tracked players
            for (auto& [player, state] : s_playerStates) {
                state.timeSinceLastTick += dt;
            }
        }
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        
        // Clear old states when a new level is initialized
        s_playerStates.clear();
        
        if (m_player1) {
            s_playerStates[m_player1] = ExtrapolationState{m_player1->getPosition(), m_player1->getPosition(), 0.0f};
        }
        if (m_player2) {
            s_playerStates[m_player2] = ExtrapolationState{m_player2->getPosition(), m_player2->getPosition(), 0.0f};
        }
        
        return true;
    }
};
