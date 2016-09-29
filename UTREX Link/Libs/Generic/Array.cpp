// Note: Templates (like the following) are only available when the file is #included not compiled.
//       This is not a problem when doing a unity build.

template <class T>
struct Array {
    const size_t Length;
    T* const Data;

    T& operator [](size_t i)
    {
        return Data[i];
    }

    bool operator ==(Array<T> &OtherArray)
    {
        size_t minLen = MIN(Length, OtherArray.Length);
        for (size_t i = 0; i < minLen; i++) {
            if (Data[i] != OtherArray.Data[i]) return false;
        }
        return true;
    }

    Array(size_t Size, T Data[])
        : Length(Size), Data(Data)
    {}

    Array(size_t Size)
        : Array(Size, new T[Size])
    {}

    void Fill(T value)
    {
        for (size_t i = 0; i < Length; i++) Data[i] = value;
    }
};
