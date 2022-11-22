#include "sound.h"
#include <QVector3D>
#include <iostream>
#include <iterator>
#include <sstream>

Sound::Sound(std::string filePath)
{
    //push inn i map?
    //mExplosionSound = SoundManager::getInstance()->createSource(navn, this.xyz,
    //filePath,false,1.0f);
}

void SoundComponent::Create(std::string filePath, std::string name)
{
    Sound* sound = new Sound(filePath);
    mSounds[name] = sound;
}

void Sound::Play(std::string name, std::string filePath)
{
    //slett lyd hvis navnet du kjører har blitt kjørt allerede
    if (soundManager::getInstance())
    {
    soundManager::getInstance()->clean();
    }
    soundManager::getInstance()->initialize();

    SoundComponent* sound{nullptr};
    sound = soundManager::getInstance()->createSource(name, QVector3D(10.0f,0.0f,0.0f),
                                                            filePath, false,1.0f);
    sound->SoundComponent::Play(filePath);
}

void Sound::Pause()
{
    alSourcePause(mSound);
}

void Sound::Stop()
{
    alSourceStop(mSound);
}

SoundComponent::SoundComponent(std::string name, bool loop, float gain) :
    mName(name), mSource(0), mBuffer(0),
    mPosition(0.f,0.f,0.f), mVelocity(0.f,0.f,0.f)
{
    alGetError();
    alGenBuffers(1, &mBuffer);
    errorCheck("alGenBuffers");
    alGenSources(1, &mSource);
    errorCheck("alGenSOurces");
    alSourcef(mSource, AL_PITCH, 1.f);
    alSourcef(mSource, AL_GAIN, gain);

    float tempPos[3] = {mPosition.x(), mPosition.y(), mPosition.z()};
    alSourcefv(mSource, AL_POSITION, tempPos);
    float tempVel[3] = {mVelocity.x(), mVelocity.y(), mVelocity.z()};
    alSourcefv(mSource, AL_VELOCITY, tempVel);

    alSourcei(mSource, AL_LOOPING, loop);
}

SoundComponent::~SoundComponent()
{
    std::cout << "destroying soundcomponent " << mName;
    Stop();
    alGetError();
    alSourcei(mSource, AL_BUFFER, 0);
    errorCheck("alSourcei");
    alDeleteSources(1, &mSource);
    errorCheck("alDeleteSources");
    alDeleteBuffers(1, &mBuffer);
    errorCheck("alDeleteBuffers");
}

bool SoundComponent::wavLoader(std::string filePath)
{
    std::cout << "Loading wave file\n";
    unsigned int frequency{};
    int format{};
    wave* waveData = new wave();
    if(!WavReader::wavLoader(filePath, waveData))
    {
        std::cout << "Error: loading wav file\n";
        return false;
    }

    frequency = waveData->sampleRate;

    switch (waveData->bitsPerSample)
    {
    case 8:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO8;
        {
        std::cout << "8bit mono\n";
        break;
        }
        case 2: format = AL_FORMAT_STEREO8;
        {
        std::cout << "8bit stereo\n";
        break;
        }
        default: break;
        }
        break;
    case 16:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO16;
        {
            std::cout << "16bit mono\n";
            break;
        }
        case 2: format = AL_FORMAT_STEREO16;
        {
            std::cout << "16bit stereo\n";
            break;
        }
        default: break;
        }
        break;
    default:break;
    }

    if (waveData->buffer == NULL)
    {
        std::cout << "No wav data\n";
    }

    std::ostringstream t;
    t << waveData->dataSize;
    std::cout << "Data size: " << t.str() << " bytes\n";

    alGetError();
    alBufferData(mBuffer, format, waveData->buffer, waveData->dataSize, frequency);
    errorCheck("alBufferData");
    alSourcei(mSource, AL_BUFFER, mBuffer);
    errorCheck("alSourcei(wavLoader)");

    std::cout << "loading complete\n";
    if(waveData->buffer)
    {delete waveData->buffer;}
    if (waveData)
    {delete waveData;}
    return true;
}

void SoundComponent::Play(std::string sound)
{
    //mSounds[sound]; //må sjekke at sound finnes i mappet?
    alSourcePlay(mSource);
}

void SoundComponent::Pause(std::string sound)
{
    alSourcePause(mSource);
}

void SoundComponent::Stop()
{
    alSourceStop(mSource);
}

void SoundComponent::setPosition(QVector3D newPosition)
{
    mPosition = newPosition;
    float tempPos[3] = {mPosition.x(),mPosition.y(),mPosition.z()};
    alSourcefv(mSource, AL_POSITION, tempPos);
}

void SoundComponent::setVelocity(QVector3D newVelocity)
{
    mVelocity = newVelocity;
    float tempVel[3] = {mVelocity.x(),mVelocity.y(),mVelocity.z()};
    alSourcefv(mSource, AL_POSITION, tempVel);
}

bool SoundComponent::errorCheck(std::string name)
{
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        std::cout << "invalid name\n";
        return false;
    case AL_INVALID_ENUM:
        std::cout << "invalid enum\n";
        return false;
    case AL_INVALID_VALUE:
        std::cout << "invalid value\n";
        return false;
    case AL_INVALID_OPERATION:
        std::cout << "invalid operation\n";
        return false;
    case AL_OUT_OF_MEMORY:
        std::cout << "out of memory\n";
        return false;
    default: break;
    }
    return true;
}

soundManager* soundManager::mInstance = NULL;

soundManager::soundManager()
    : mDevice(NULL), mContext(NULL)
{

}

bool soundManager::initialize()
{
    std::cout << "OpenAL initializing\n";
    mDevice = alcOpenDevice(NULL);
    if (mDevice)
    {
        mContext = alcCreateContext(mDevice, NULL);
        alcMakeContextCurrent(mContext);
    }

    alGetError();

    if(!mDevice)
    {
        std::cout << "Device not found\n";
    }
    else
    {
        std::cout << "OpenAl init complete\n";
    }

    return true;
}

void soundManager::clean()
{
    mContext = alcGetCurrentContext();
    mDevice = alcGetContextsDevice(mContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(mContext);
    alcCloseDevice(mDevice);
}

bool soundManager::errorCheck()
{
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        std::cout << "Invalid name\n";
        return false;
    case AL_INVALID_ENUM:
        std::cout << "Invalid enum\n";
        return false;
    case AL_INVALID_VALUE:
        std::cout << "Invalid value\n";
        return false;
    case AL_INVALID_OPERATION:
        std::cout << "Invalid operation\n";
        return false;
    case AL_OUT_OF_MEMORY:
        std::cout << "Out of memory\n";
        return false;
    default: break;
    }
    return true;
}

SoundComponent* soundManager::createSource(std::string name, QVector3D position, std::string filePath, bool loop, float gain)
{
    SoundComponent* temp_ptr = new SoundComponent(name, loop, gain);
    temp_ptr->setPosition(position);
    if (filePath != "")
    {
        temp_ptr->wavLoader(filePath);
    }
    return temp_ptr;
}

void soundManager::updateListener(QVector3D position, QVector3D velocity, QVector3D direction, QVector3D up)
{
    float positionVector[3];
    float velocityVector[3];
    float orientationVector[6];
    positionVector[0] = position.x();
    positionVector[1] = position.y();
    positionVector[2] = position.z();
    velocityVector[0] = velocity.x();
    velocityVector[1] = velocity.y();
    velocityVector[2] = velocity.z();
    orientationVector[0] = direction.x();
    orientationVector[1] = direction.y();
    orientationVector[2] = direction.z();
    orientationVector[3] = up.x();
    orientationVector[4] = up.y();
    orientationVector[5] = up.z();
    alListenerfv(AL_POSITION, positionVector);
    alListenerfv(AL_VELOCITY, velocityVector);
    alListenerfv(AL_ORIENTATION, orientationVector);
}

bool WavReader::wavLoader(std::string filePath, wave *wave_ptr)
{
    std::cout << "Loading: " << filePath << " from disk" << std::endl;
    FILE* f = NULL;
    f = std::fopen(filePath.c_str(), "rb");
    if (f == NULL)
    {
        return checkForError("Error: File not found\n");
    }

    char type[4];

    std::fread(type, sizeof(char), 4, f);
    if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
    {
        return checkForError("Error: RIFF header missing/invalid\n");
    }

    std::fread(&wave_ptr->size,sizeof(unsigned int), 1, f);
    std::fread(type, sizeof(char), 4, f);
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
    {
        return checkForError("Error: WAVE header missing/invalid\n");
    }

    std::fread(type, sizeof(char), 4, f);
    if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
    {
        return checkForError("Error: fmt header missing/invalid\n");
    }

    std::fread(&wave_ptr->chunkSize,       sizeof(unsigned int), 1, f);
    std::fread(&wave_ptr->formatType,      sizeof(short), 1, f);
    std::fread(&wave_ptr->channels,        sizeof(short), 1, f);
    std::fread(&wave_ptr->sampleRate,      sizeof(unsigned int), 1, f);
    std::fread(&wave_ptr->avgBytesPerSec,  sizeof(unsigned int), 1, f);
    std::fread(&wave_ptr->bytesPerSample,  sizeof(short), 1, f);
    std::fread(&wave_ptr->bitsPerSample,   sizeof(short), 1, f);
    std::fread(type, sizeof(char), 4, f);
    if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
    {
        return checkForError("Error: data header missing/invalid\n");
    }

    std::fread(&wave_ptr->dataSize, sizeof(unsigned int), 1, f);

    wave_ptr->buffer = new unsigned char[wave_ptr->dataSize];
    unsigned int result = std::fread(wave_ptr->buffer, sizeof(char), wave_ptr->dataSize, f);
    if (result != wave_ptr->dataSize)
    {
        return checkForError("Error: fread result not correct\n");
    }

    if (ferror(f))
    {
        return checkForError("Error: fstream error");
    }

    if (wave_ptr->buffer == NULL)
    {
        return checkForError("Error: wave data pointer = NULL\n");
    }

    std::fclose(f);
    std::cout << filePath << " succesfully loaded\n";
    return true;
}

bool WavReader::checkForError(std::string errorMessage)
{
    std::cout << errorMessage;
    return false;
}
