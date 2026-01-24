#ifndef CLIENT_REPOSITORY_H
#define CLIENT_REPOSITORY_H

#include "Repository.h"
#include "Client.h"

class ClientRepository : public Repository<Client, int> {
protected:
    int getKey(const ClientPtr& item) const override {
        return item->getInternalId();
    }
};

#endif
