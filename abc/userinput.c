#include <box/box.h>
#include "global.h"

char* myuserid = NULL;
char* myname = NULL;

static void change_name(char* name)
{
    // 其实要发送广播
    //"name|userid-from|username"

    if(myuserid == NULL)
    {
        create_userid();
    }

    myname = strdup(name);

    char buf[8192];
    sprintf(buf, "name|%s|%s", myuserid, name);


    // 发送
    broadcast(buf);
//    struct
//    sendto(udp_socket, buf, strlen(buf), 0, 广播地址);
}

void read_stdin(box_channel* c)
{
    char buf[8192];
    fgets(buf, sizeof(buf), stdin); // 不会阻塞
    buf[strlen(buf)-1] = 0;

    if(strlen(buf)  == 0)
    {
        printf("不要乱敲\n");
        return;
    }

    char* cmd = strtok(buf, "|");
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "\0");
        change_name(name);
    }
    // 显示用户列表
    else if(strcmp(cmd, "list") == 0)
    {
        User* user  = users;
        printf("user list:\n");
        while(user)
        {
            printf("  %s\t%s\n", user->userid, user->username);
            user = user->next;
        }
    }
    else if(strcmp(cmd, "msg") == 0)
    {
        char* userid = strtok(NULL, "|");
        char* content = strtok(NULL, "|");

        char buf[8192];
        sprintf(buf, "msg|%s|%s", myuserid, content);
        sendUdp(buf, userid);
    }
    else if(strcmp(cmd, "msg-all") == 0)
    {

    }
    else if(strcmp(cmd, "file") == 0)
    {

    }
    else if(strcmp(cmd, "dir") == 0)
    {

    }
    else if(strcmp(cmd, "file-all") == 0)
    {

    }

    else if(strcmp(cmd, "dir-all") == 0)
    {

    }
    else
    {
        printf("unknown cmd\n");
        return;
    }


}

