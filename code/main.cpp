#include <vector>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <cstring>
#include <algorithm>
#include <dirent.h>
#include <unistd.h>

#include "Vagrant/vagrant.h"
#include "Vagrant/server/Server.h"
#include "Classes/Login.h"

signed main() {
    Server server;
    server.addUrl(new Login());
    server.loop();

    return 0;
}