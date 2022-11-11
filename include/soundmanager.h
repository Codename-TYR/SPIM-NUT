#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#ifdef _WIN32
#include <al.h>
#include <alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <string>
#include <vector>
#include "soundsource.h"
#include "crapvectors.h"

/// Class handling OpenAL setup and management of sound sources.
/**
    Singleton class that creates and destroys sound sources.
**/
class SoundManager
{
public:
    struct SoundListener
    {
        CrapVector3 pos;
        CrapVector3 vel;
        CrapVector3 dir;
        CrapVector3 up;
        SoundListener()
        {
            pos = CrapVector3(0.0f, 0.0f, 0.0f);
            vel = CrapVector3(0.0f, 0.0f, 0.0f);
            dir = CrapVector3(0.0f, 0.0f, 1.0f);
            up = CrapVector3(0.0f, 1.0f, 0.0f);
            //Could be something like this, if CrapVector3-class had support support:
            //pos = CrapVector3::ZERO;
            //vel = CrapVector3::ZERO;
            //dir = CrapVector3::UNIT_Z;
            //up = CrapVector3::UNIT_Y;
        }
    };

    static SoundManager* getInstance()          ///< Get pointer to singleton instance.
    {
        if (!mInstance)
            mInstance = new SoundManager();
        return mInstance;
    }

    /// Initialises OpenAL.
    bool init();
    /// Cleans up and shuts down OpenAl.
    void cleanUp();

    /// Creates a new SoundSource with the given parameters.
    /**
        \param The name of the sound. (Not in use.)
        \param The source position as CrapVector3.
        \param File path relative to execution directory.
        \param Boolean to see if sound should loop or not.
    **/
    SoundSource* createSource(std::string name, CrapVector3 pos, std::string filePath = "", bool loop = false, float gain = 1.0);
    void updateListener(CrapVector3 pos, CrapVector3 vel, CrapVector3 dir, CrapVector3 up);

private:
    SoundManager();                         ///< Private constructor.
    SoundManager(SoundManager const&);      ///< Private copy constructor.
    void operator=(SoundManager const&);    ///< Private class assignment operator.
    static SoundManager* mInstance;         ///< Singleton instance pointer.
    /// Debug function.
    /**
        Checks for and outputs OpenAL errors.
    **/
    bool checkError();

    ALCdevice* mDevice;                 ///< Pointer to the ALC Device.
    ALCcontext* mContext;               ///< Pointer to the ALC Context.

    SoundListener mListener;               ///< The listener data structure. (Temporary)
};

#endif
