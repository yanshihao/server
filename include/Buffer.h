#pragma once
#include <vector>
#include <string>

class Buffer
{
public:
    static const size_t KInitialSize = 1024;
    Buffer()
    :buffer_(KInitialSize), readIndex_(0),writeIndex_(0){}

    size_t readableBytes() const
    {
        return writeIndex_ - readIndex_;
    }

    size_t writableBytes() const
    {
        return buffer_.size() - writeIndex_;
    }

    size_t readFd(int fd, int* saveErron);

    void append(const std::string& str);

    void append(const char* str, size_t len);

    void retrieve(size_t len);

    void retrieveUntil(const char* end);

    void retrieveAll();

    std::string retrieveAllAsString();

    const char* peek() const
    {
        return begin() + readIndex_;
    }

    const char* find() const;

private:

    const char* begin() const
    {
        return &(*buffer_.begin());
    }

    char* begin() 
    {
        return &*buffer_.begin();
    }

    void makeRoom(size_t len);

    std::vector<char>  buffer_;
    size_t  readIndex_;
    size_t  writeIndex_;
};