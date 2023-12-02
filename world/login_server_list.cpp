#include "../common/global_define.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include "../common/version.h"
#include "../common/servertalk.h"
#include "login_server.h"
#include "login_server_list.h"
#include "../common/eq_packet_structs.h"
#include "../common/packet_dump.h"
#include "zoneserver.h"
#include "worlddb.h"
#include "zonelist.h"
#include "clientlist.h"
#include "world_config.h"

extern ZSList zoneserver_list;
extern LoginServerList loginserverlist;
extern ClientList client_list;
extern uint32 numzones;
extern uint32 numplayers;
extern volatile bool RunLoops;

LoginServerList::LoginServerList() {}

LoginServerList::~LoginServerList() {}

void LoginServerList::Add(const char* iAddress, uint16 iPort, const char* Account, const char* Password, uint8 Type) {
    auto loginserver = new LoginServer(iAddress, iPort, Account, Password, Type);
    list.Insert(loginserver);
}

bool LoginServerList::Process() {
    LinkedListIterator<LoginServer*> iterator(list);

    iterator.Reset();
    while (iterator.MoreElements()) {
        iterator.GetData()->Process();
        iterator.Advance();
    }
    return true;
}

#ifdef _WINDOWS
void AutoInitLoginServer(void* tmp) {
#else
void* AutoInitLoginServer(void* tmp) {
#endif
    loginserverlist.InitLoginServer();
#ifndef WIN32
    return 0;
#endif
}

void LoginServerList::InitLoginServer() {
    LinkedListIterator<LoginServer*> iterator(list);

    iterator.Reset();
    while (iterator.MoreElements()) {
        iterator.GetData()->InitLoginServer();
        iterator.Advance();
    }
}

bool LoginServerList::CanUpdate() {
    LinkedListIterator<LoginServer*> iterator(list);

    iterator.Reset();
    while (iterator.MoreElements()) {
        if (iterator.GetData()->CanUpdate())
            return true;
        iterator.Advance();
    }
    return false;
}
