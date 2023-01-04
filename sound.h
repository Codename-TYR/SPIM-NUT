#ifndef SOUND_H
#define SOUND_H
#include <string>
#include <map>
#include <QVector3D>
#include <al.h>
#include <alc.h>

// https://stackoverflow.com/questions/23742286/computing-duration-of-a-wav-file
// kan gjøre mp3 til pcm også lese inn det?

struct wave;
class SoundComponent;
class Sound;
class soundManager;
class WavReader;

class Sound
{
public:
    Sound(std::string filePath);
    void Play(std::string name, std::string filePath);
    void Pause();
    void Stop();
    void exist(std::string name);
    std::vector<std::string> soundNames;

private:
    unsigned int mSound;
    bool existingSound = false;
};

class SoundComponent
{
public:
    SoundComponent(std::string name, bool loop = false, float gain = 1.0f);
    ~SoundComponent();

//    void ComponentTick(float deltaTime);

    void Play(std::string sound); //play sound
    void Pause(std::string sound); //pause sound
    void Stop(); //stop sound

    bool wavLoader(std::string filePath);

    void Create(std::string filePath, std::string name);

    void setPosition(QVector3D newPosition);
    QVector3D getPos()
    {
        return mPosition;
    };

    void setVelocity(QVector3D newVelocity);
    QVector3D getVelocity()
    {
        return mVelocity;
    }

private:
    std::map<std::string,Sound*> mSounds;
    std::string mName;
    unsigned int mSource;
    unsigned int mBuffer;
    QVector3D mPosition;
    QVector3D mVelocity;
    bool errorCheck(std::string name);
};

class soundManager
{
public:
    struct Listener
    {
        QVector3D position, velocity, direction, up;
        Listener()
        {
            position = QVector3D(0.f,0.f,0.f);
            velocity = QVector3D(0.f,0.f,0.f);
            direction = QVector3D(0.f,0.f,1.f);
            up = QVector3D(0.f,1.f,0.f); //finn ut hva som er opp
        }
    };

    static soundManager* getInstance() //singleton pointer
    {
        if (!mInstance)
        { mInstance = new soundManager();}
        return mInstance;
    }

    bool initialize();
    void clean();

    void updateListener(QVector3D position, QVector3D velocity, QVector3D direction, QVector3D up);
    SoundComponent* createSource(std::string name, QVector3D position, std::string filePath = "", bool loop = false, float gain = 1.0);
private:
    soundManager();
    static soundManager* mInstance; //singleton
    bool errorCheck(); //debuging

    ALCdevice* mDevice;
    ALCcontext* mContext;

    Listener mListener;
};

struct wave{
    unsigned int size;
    unsigned int chunkSize;
    unsigned int sampleRate;
    unsigned int avgBytesPerSec;
    unsigned int dataSize;
    short formatType;
    short channels;
    short bytesPerSample;
    short bitsPerSample;

    unsigned char* buffer;
    wave() : buffer(NULL) {}
};

class WavReader
{
public:
    static bool wavLoader(std::string filePath, wave* wave_ptr);

private:
    static bool checkForError(std::string errorMessage);
};

#endif // SOUND_H
