#include "http.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <string.h>
void HttpProcessor::parseHttpRequest(const std::string& str)
{
    state_ = R_START;
    size_t prev = 0;
    size_t next = str.find("\r\n", prev);
    std::string firstline = str.substr(prev,next);
    std::stringstream sstream(firstline);
    sstream >> request_.method;
    sstream >> request_.url;
    sstream >> request_.version;

    state_ = R_METHOD;
    prev = next + 2;
    while ((next = str.find("\r\n", prev)) != std::string::npos)
    {
        if(prev == next) break;
        size_t mid = str.find(':', prev);
        if(mid >= next)
        {
            state_ = R_ERROR;
            return;
        }
        std::string key = str.substr(prev, mid- prev);
        std::string value = str.substr(mid+2, next - mid - 2);
        request_.header[key] = value;
        prev = next + 2;
    }
    
    state_ = R_HEADER;
    parseResult_ = true;
    if(request_.header.find("Connection") != request_.header.end())
    {
        if(request_.header["Connection"] == "keep-alive")
            keepalive_ = true;
    }
    if(request_.version == "HTTP/1.1")
        keepalive_ = true;
}

void HttpProcessor::HttpProcess(std::string& responsecontext)
{
    if("GET" == request_.method)
    {
        ;
    }
    else if("HEAD" == request_.method)
    {
        ;
    }
    else
    {
        HttpError(501, std::string("NOT Implemented!"), responsecontext);
        return;
    }
    
    std::string responsebody;
    std::string path = request_.url;
    if(path == "/")
        path = "/index.html";
    path.insert(0, "/home/admin/git/testmuduo");
    FILE* fp = NULL;
    if((fp = fopen(path.c_str(), "rb")) == NULL)
    {
        HttpError(404, std::string("NOT FOUND"), responsecontext);
        return;
    }
    else
    {
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        while(fread(buffer, sizeof(buffer), 1, fp) == 1)//可以mmap内存映射优化
        {
            responsebody.append(buffer);
            memset(buffer, 0, sizeof(buffer));
        }
        if(feof(fp))
        {
            responsebody.append(buffer);
        }        
        else
        {
            std::cout << "error fread" << std::endl;
        }        	
        fclose(fp);
    }
    
    std::string filetype("text/html"); //暂时固定为html
    responsecontext += request_.version + " 200 OK\r\n";
    responsecontext += "Server: Yanshihao's webServer/0.1\r\n";
    responsecontext += "Content-Type: " + filetype + "; charset=utf-8\r\n";
    responsecontext += "Content-Length: " + std::to_string(responsebody.size()) + "\r\n";
    responsecontext += "\r\n";
    responsecontext += responsebody;    
}

void HttpProcessor::HttpError(const int err_num, const std::string& short_msg, 
                            std::string& responsecontext)
{
    std::string responsebody;
    responsebody += "<html><title>出错了</title>";
    responsebody += "<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head>";
    responsebody += "<style>body{background-color:#f;font-size:14px;}h1{font-size:60px;color:#eeetext-align:center;padding-top:30px;font-weight:normal;}</style>";
    responsebody += "<body bgcolor=\"ffffff\"><h1>";
    responsebody += std::to_string(err_num) + " " + short_msg;
    responsebody += "</h1><hr><em> Yanshihao's webServer</em>\n</body></html>";

    std::string httpversion;
    if(request_.version.empty())
    {
        httpversion = "HTTP/1.1";
    }
    else
    {
        httpversion = request_.version;
    }   
        
    responsecontext += httpversion + " " + std::to_string(err_num) + " " + short_msg + "\r\n";
    responsecontext += "Server: Yanshihao's webServer\r\n";
    responsecontext += "Content-Type: text/html\r\n";
    responsecontext += "Connection: Keep-Alive\r\n";
    responsecontext += "Content-Length: " + std::to_string(responsebody.size()) + "\r\n";
    responsecontext += "\r\n";
    responsecontext += responsebody;
}