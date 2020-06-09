#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
class TcpConnection;
class InetAddr;
class Buffer;
class Timestamp;
typedef std::function <void ()>  Callback;
typedef std::shared_ptr<TcpConnection>  TcpConnectionPtr;


/**************************************************/
// 这些函数接口都是给应用的，写应用程序时应该遵守这些函数的调用方式
// 所以外层封装需要提供这几个函数的设置接口

// 建立连接和断开连接时调用的回调函数，主要用于信息显示
typedef std::function<void (const TcpConnectionPtr&)>  ConnectionCallback;

// 当有消息到来时的回调函数，主要用来处理信息
typedef std::function<void (const TcpConnectionPtr&, Buffer*, Timestamp)> MessageCallback;

// 当发送完毕时的回调函数，主要用来显示消息或者进一步动作
typedef std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;

class Channel;
typedef std::vector<Channel*>  ChannelList;
typedef std::unordered_map<int, Channel*> ChannelMap;

typedef std::function<void (int, const InetAddr&)>  AcceptorCallback;

typedef std::function<void (TcpConnectionPtr) >  RemoveConnectionCallback;