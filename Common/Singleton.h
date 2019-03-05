#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * 单例模板
 */

template <class T>
class Singleton
{
public:
    static T* getInstance()
    {
        static T instance;
        return &instance;
    }
};

#endif // SINGLETON_H
