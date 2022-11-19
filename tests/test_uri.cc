#include "kiwi/uri.h"
#include <iostream>

int main(int argc, char** argv) {
    //kiwi::Uri::ptr uri = kiwi::Uri::Create("http://www.kiwi.top/test/uri?id=100&name=kiwi#frg");
    //kiwi::Uri::ptr uri = kiwi::Uri::Create("http://admin@www.kiwi.top/test/中文/uri?id=100&name=kiwi&vv=中文#frg中文");
    kiwi::Uri::ptr uri = kiwi::Uri::Create("http://admin@www.kiwi.top");
    //kiwi::Uri::ptr uri = kiwi::Uri::Create("http://www.kiwi.top/test/uri");
    std::cout << uri->toString() << std::endl;
    auto addr = uri->createAddress();
    std::cout << *addr << std::endl;
    return 0;
}
