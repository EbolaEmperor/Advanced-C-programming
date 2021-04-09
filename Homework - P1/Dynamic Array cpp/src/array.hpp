class Array{
private:
    int t_size;
    int lastidx;
    int *content;
    void double_inflate();

public:
    Array();
    ~Array();
    int size();
    void resize(const int &length);
    void pushback(const int &element);
    int& operator [] (const int &index);
    Array operator = (const Array &origin);
};