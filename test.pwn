#include <test-boilerplate>

#include "actions.inc"

main() {}

new surrBlock;
new sitBlock;

public OnPlayerCommandText(playerid, cmdtext[]) {
    if(!strcmp(cmdtext, "/surrblock")) {
        surrBlock = true;
        return 1;
    }

    if(!strcmp(cmdtext, "/surrunblock")) {
        surrBlock = false;
        return 1;
    }

    if(!strcmp(cmdtext, "/sitblock")) {
        sitBlock = true;
        return 1;
    }

    if(!strcmp(cmdtext, "/situnblock")) {
        sitBlock = false;
        return 1;
    }

    if(!strcmp(cmdtext, "/cuff")) {
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
        return 1;
    }

    return 0;
}

public OnPlayerSurrender(playerid) {
    if(surrBlock) {
        return 1;
    }

    return 0;
}

public OnPlayerSitDown(playerid) {
    if(sitBlock) {
        return 1;
    }

    return 0;
}
