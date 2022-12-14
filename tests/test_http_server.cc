#include "kiwi/http/http_server.h"
#include "kiwi/log.h"

static kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

#define XX(...) #__VA_ARGS__


kiwi::IOManager::ptr woker;
void run() {
    g_logger->setLevel(kiwi::LogLevel::INFO);
    //kiwi::http::HttpServer::ptr server(new kiwi::http::HttpServer(true, woker.get(), kiwi::IOManager::GetThis()));
    kiwi::http::HttpServer::ptr server(new kiwi::http::HttpServer(true));
    kiwi::Address::ptr addr = kiwi::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/kiwi/xx", [](kiwi::http::HttpRequest::ptr req
                ,kiwi::http::HttpResponse::ptr rsp
                ,kiwi::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/kiwi/*", [](kiwi::http::HttpRequest::ptr req
                ,kiwi::http::HttpResponse::ptr rsp
                ,kiwi::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/kiwix/*", [](kiwi::http::HttpRequest::ptr req
                ,kiwi::http::HttpResponse::ptr rsp
                ,kiwi::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv) {
    kiwi::IOManager iom(1, true, "main");
    woker.reset(new kiwi::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}
