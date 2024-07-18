#pragma once

#include <raylib.h>


#define MISS_SOUND 0
#define DICE_SELECT_SOUND 1
#define DICE_ROLL_SOUND 2
#define HEAL_SOUND 3
#define ATTACK_SOUND 4
#define HIT_SOUND 5
#define PICKUP_COIN_SOUND 6
#define DRAW_CARD_SOUND 7
#define SHUFFLE_CARD_SOUND 8
#define CLICK_SOUND 9
#define ENEMY_ENTRY_SOUND 10
#define HOVER_SOUND 11
#define SPEAK_SOUND 12

//music tracks
#define MENU_MUSIC1 0
#define GAME_MUSIC1 1


namespace audio {


    
    extern auto Init() -> void;
    extern auto Close() -> void;


    extern auto Update() -> void;

    extern auto PlaySoundOneShot(int soundId) -> void;

    extern auto SetMusic(int musicId) -> void;

        
    extern float gameMusicMultiplier;

    extern Sound sounds[13];
    extern Music musicTracks[2];
    extern Music currentMusicTrack;

    extern auto LoadSounds() -> void;
    extern auto LoadMusicTracks() -> void;

    extern auto UnloadSounds() -> void;
    extern auto UnloadMusicTracks() -> void;
}
