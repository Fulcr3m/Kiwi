#include <iostream>
#include "kiwi/http/http_connection.h"
#include "kiwi/log.h"
#include "kiwi/iomanager.h"
#include <fstream>

static kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

void test_pool() {
    kiwi::http::HttpConnectionPool::ptr pool(new kiwi::http::HttpConnectionPool(
                "www.kiwi.top", "", 80, 10, 1000 * 30, 5));

    kiwi::IOManager::GetThis()->addTimer(1000, [pool](){
            auto r = pool->doGet("/", 300);
            KIWI_LOG_INFO(g_logger) << r->toString();
    }, true);
}

void run() {
    kiwi::Address::ptr addr = kiwi::Address::LookupAnyIPAddress("www.kiwi.top:80");
    if(!addr) {
        KIWI_LOG_INFO(g_logger) << "get addr error";
        return;
    }

    kiwi::Socket::ptr sock = kiwi::Socket::CreateTCP(addr);
    bool rt = sock->connect(addr);
    if(!rt) {
        KIWI_LOG_INFO(g_logger) << "connect " << *addr << " failed";
        return;
    }

    kiwi::http::HttpConnection::ptr conn(new kiwi::http::HttpConnection(sock));
    kiwi::http::HttpRequest::ptr req(new kiwi::http::HttpRequest);
    req->setPath("/blog/");
    req->setHeader("host", "www.kiwi.top");
    KIWI_LOG_INFO(g_logger) << "req:" << std::endl
        << *req;

    conn->sendRequest(req);
    auto rsp = conn->recvResponse();

    if(!rsp) {
        KIWI_LOG_INFO(g_logger) << "recv response error";
        return;
    }
    KIWI_LOG_INFO(g_logger) << "rsp:" << std::endl
        << *rsp;

    std::ofstream ofs("rsp.dat");
    ofs << *rsp;

    KIWI_LOG_INFO(g_logger) << "=========================";

    auto r = kiwi::http::HttpConnection::DoGet("http://www.kiwi.top/blog/", 300);
    KIWI_LOG_INFO(g_logger) << "result=" << r->result
        << " error=" << r->error
        << " rsp=" << (r->response ? r->response->toString() : "");

    KIWI_LOG_INFO(g_logger) << "=========================";
    test_pool();
}

int main(int argc, char** argv) {
    kiwi::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
