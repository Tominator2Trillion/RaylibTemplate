#include "audioManager.hpp"
#include <raylib.h>
#include "settings.hpp"


namespace audio {
    Sound sounds[13]{};
    Music musicTracks[2]{};
    Music currentMusicTrack{};

    float gameMusicMultiplier{1};


    auto Init() -> void
    {
        InitAudioDevice();
        LoadSounds();
        LoadMusicTracks();
    }

    auto Close() -> void
    {
        CloseAudioDevice();
        UnloadSounds();
        UnloadMusicTracks();
    }

    auto LoadSounds() -> void
    {   
        sounds[MISS_SOUND] = LoadSound("assets/sounds/missed.wav");
        sounds[DICE_SELECT_SOUND] = LoadSound("assets/sounds/diceSelect.wav");
        sounds[DICE_ROLL_SOUND] = LoadSound("assets/sounds/diceroll.wav");
        sounds[HEAL_SOUND] = LoadSound("assets/sounds/healsound.wav");
        sounds[ATTACK_SOUND] = LoadSound("assets/sounds/attackSound.wav");
        sounds[HIT_SOUND] = LoadSound("assets/sounds/hit.wav");
        sounds[PICKUP_COIN_SOUND] = LoadSound("assets/sounds/pickupCoin.wav");
        sounds[DRAW_CARD_SOUND] = LoadSound("assets/sounds/cards_draw.mp3");
        sounds[SHUFFLE_CARD_SOUND] = LoadSound("assets/sounds/cards_shuffle.mp3");
        sounds[CLICK_SOUND] = LoadSound("assets/sounds/click.ogg");
       // sounds[ENEMY_ENTRY_SOUND] = LoadSound("assets/sounds/enemy_entry.mp3");
        sounds[HOVER_SOUND] = LoadSound("assets/sounds/hover.ogg");
        sounds[SPEAK_SOUND] = LoadSound("assets/sounds/speak.ogg");

    }

    auto LoadMusicTracks() -> void
    {
        musicTracks[MENU_MUSIC1] = LoadMusicStream("assets/sounds/test_200crd.wav");
        musicTracks[GAME_MUSIC1] = LoadMusicStream("assets/sounds/game_music.ogg");
    }

    auto UnloadSounds() -> void
    {
        for (int i = 0; i < 1; i++)
        {
            UnloadSound(sounds[i]);
        }
    }

    auto UnloadMusicTracks() -> void
    {
        for (int i = 0; i < 1; i++)
        {
            UnloadMusicStream(musicTracks[i]);
        }
    }

    auto Update() -> void
    {
        SetMusicVolume(currentMusicTrack, settings::masterVolume * settings::musicVolume * gameMusicMultiplier);
        UpdateMusicStream(currentMusicTrack);
    }

    auto PlaySoundOneShot(int soundId) -> void
    {
        SetSoundVolume(sounds[soundId], settings::masterVolume * settings::sfxVolume);
        PlaySound(sounds[soundId]);
    }

    auto SetMusic(int musicId) -> void
    {
        currentMusicTrack = musicTracks[musicId];
        PlayMusicStream(currentMusicTrack);
    }
}



