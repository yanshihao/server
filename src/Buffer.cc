#include "Buffer.h"
#include <assert.h>
#include <sys/uio.h>
#include <errno.h>

void Buffer::append(const std::string& str)
{
    append(str.c_str(), str.size());
}

void Buffer::retrieve(size_t len)
{
    assert(readableBytes() >= len);
    readIndex_ += len;
    if(readIndex_ == writeIndex_)
    {
        readIndex_ = 0;
        writeIndex_ = 0;
    }    
}


void Buffer::retrieveUntil(const char* end)
{
    size_t len = end - begin();
    retrieve(len);
}

void Buffer::retrieveAll()
{
    readIndex_ = 0;
    writeIndex_ = 0;
}

std::string Buffer::retrieveAllAsString()
{
    std::string str(begin(), readableBytes());
    retrieveAll();
    return str;
}

void Buffer::append(const char* str, size_t len)
{
    // 首先腾出空间
    if(writableBytes() < len)
    {
        makeRoom(len);
    }

    // 然后复制
    std::copy(str,str+len, begin() + writeIndex_);

    // 然后修改index
    writeIndex_ += len;
}


void Buffer::makeRoom(size_t len)
{
    // 分两种情况讨论，一种是有足够空间当时在前面
    // 一种是没有足够空间
    if(writableBytes() + readIndex_ < len)
    {
        // 没有足够空间
        std::vector<char> newbuf(writeIndex_ + len);
        std::copy(begin() + readIndex_, begin()+ writeIndex_, &*newbuf.begin());
        std::swap(newbuf, buffer_);
        writeIndex_ -= readIndex_;
        readIndex_ = 0;
    }
    else
    {
        // 有足够空间
        std::copy(begin() + readIndex_, begin()+ writeIndex_, begin());
        writeIndex_ -= readIndex_;
        readIndex_ = 0;
    }
}

int Buffer::readFd(int fd, int* saveErrno)
{
    char extrabuf[65536];
    struct iovec vec[2];
    vec[0].iov_base = begin() + writeIndex_;
    vec[0].iov_len = writableBytes();

    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);

    int n = ::readv(fd, vec,2);
    if( n < 0 )
    {
        perror("readv");
        *saveErrno = errno;
    }
    else if(n == 0)
    {
        ;
    }
    else if( n <= writableBytes())
    {
        writeIndex_ += n;
    }
    else
    {
        size_t writable = writableBytes();
        writeIndex_ = buffer_.size();
        append(extrabuf,n - writable);
    }
    return n;
}