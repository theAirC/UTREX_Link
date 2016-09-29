
template <class T, size_t MaxCount>
struct Stack {
    T Data[MaxCount];
    size_t Count;

    size_t Length()
    {
        return MaxCount;
    }

    T& operator [](size_t i)
    {
        return Data[i];
    }

    T& Current()
    {
        return Data[Count - 1];
    }

    Stack()
    {
        Count = 0;
    }

    bool Add(T item)
    {
        if (Count >= MaxCount) return false;
        
        Data[Count++] = item;
        return true;
    }

    bool Remove()
    {
        if (Count == 0) return false;

        Count--;
        return true;
    }
};
