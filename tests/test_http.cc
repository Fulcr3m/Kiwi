#include "kiwi/http/http.h"
#include "kiwi/log.h"

void test_request() {
    kiwi::http::HttpRequest::ptr req(new kiwi::http::HttpRequest);
    req->setHeader("host" , "www.kiwi.top");
    req->setBody("hello kiwi");
    req->dump(std::cout) << std::endl;
}

void test_response() {
    kiwi::http::HttpResponse::ptr rsp(new kiwi::http::HttpResponse);
    rsp->setHeader("X-X", "kiwi");
    rsp->setBody("hello kiwi");
    rsp->setStatus((kiwi::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}

int main(int argc, char** argv) {
    test_request();
    test_response();
    return 0;
}
