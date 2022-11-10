#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#ifdef _WIN32
#include <al.h>
#include <alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <string>
#include <QVector3D>

/// One sound source.
/**
    Contains one source and one buffer.
    Intended to play a single clip.
    Does not support streaming audio (yet).
**/
class SoundSource
{
public:
    /// Constructor.
    /**
        Takes two arguments, initialises some variables.
        \param The name of the sound source. Not used.
        \param A boolean to check if sound should loop.
    **/
    SoundSource(std::string name, bool loop = false, float gain = 1.0);
    ~SoundSource();

    /// Plays the sound source from the current position.
    void play();
    /// Pauses the sound source at the current position.
    void pause();
    /// Stops the sound source and rewinds to start.
    void stop();

    /// Loads one given WAVE file.
    /**
        Calls the wave loader from the FileHandler class, parses the wave data and buffers it.
        \param The file path relative to execution directory.
    **/
    bool loadWave(std::string filePath);

    void setPosition(QVector3D newPos);             ///< Sets source position from QVector3D.
    QVector3D getPosition() {return mPosition;}     ///< Returns source position as QVector3D.
    void setVelocity(QVector3D newVel);             ///< Sets source velocity from QVector3D.
    QVector3D getVelocity() {return mVelocity;}     ///< Returns source velocity as QVector3D.

private:
    std::string mName;          ///< The name of the sound source (Not used).
    ALuint mSource;             ///< The sound source.
    ALuint mBuffer;             ///< The data buffer.
    QVector3D mPosition;    ///< Vector containing source position.
    QVector3D mVelocity;    ///< Vector containing source velocity.
    bool checkError(std::string name);
};

#endif