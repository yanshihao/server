#pragma once
#include <string>
#include <map>

struct HttpRequest {     
    std::string method;    
    std::string url;    
    std::string version;    
    std::map<std::string, std::string> header;    
    std::string body;    
};
    
struct HttpResponse {    
    std::string version;    
    std::string statecode;                             
    std::string statemsg;    
    std::map<std::string, std::string> header;         
    std::string body;                        
};

enum State{R_START, R_METHOD, R_HEADER, R_ERROR};

class HttpProcessor
{
public:
    HttpProcessor(const std::string& str)
    :state_(R_START), parseResult_(false), keepalive_(false)
    {
        // request_ ,parseResult_, keepalive_
        parseHttpRequest(str);    
    }
    
    HttpProcessor(const HttpProcessor&) =delete;
    const HttpProcessor& operator=(const HttpProcessor&) = delete;
    
    bool parseResult() {return parseResult_;}
    bool keepalive()  {return keepalive_; }

    void HttpProcess(std::string & responsestr);

    void HttpError(const int, const std::string&, std::string& );
private:
    State state_; 
    State getMethod(const std::string::const_iterator iter1, 
                    const std::string::const_iterator iter2);
    State getHeader(const std::string::const_iterator iter1, 
                    const std::string::const_iterator iter2);
    void parseHttpRequest(const std::string& str);
    HttpRequest request_;
    bool parseResult_; 
    bool keepalive_;
};