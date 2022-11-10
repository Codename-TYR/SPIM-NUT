#ifndef WORLD_H
#define WORLD_H
#include <map>

class NUTObject;

class World
{
public:
    static World* GetWorld()          ///< Get pointer to singleton instance.
    {
        if (!mInstance)
            mInstance = new World();
        return mInstance;
    }

    void InsertObject(NUTObject* obj) {
        while (mObjects[id] != nullptr) {
            id++;
        }
        mObjects[id] = obj;
        id++;
    }
private:
    World();
    ~World()
    {
        for (auto p : mObjects) {
            delete p.second;
        }
    }
    World(World const&);
    void operator=(World const&);
    static inline World* mInstance{nullptr};
    static inline unsigned long long id{0};

    std::map<unsigned long long, NUTObject*> mObjects;


};

#endif // WORLD_H
