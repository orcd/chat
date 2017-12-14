
#include "global.h"

User* users = NULL;

// 保存用户信息
static void change_name(char* userid, char* name)
{
    addUser(userid, name);
}

void read_udp(box_channel* c)
{
    char buf[8192];
    int ret = read(c->sock, buf, sizeof(buf));
    buf[ret ] = 0;

    printf("recv buf: %s\n", buf);

    if(myuserid == NULL)
    {
        printf("my userid is null\n");
        return;
    }

    // 判断是否自己发的消息
    char* cmd = strtok(buf, "|");
    char* userid_from = strtok(NULL,  "|");
    if(strcmp(userid_from, myuserid) == 0)
    {
        printf("recv broadcast from self\n");
        return;
    }

    // 如果是改名
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "|");
        change_name(userid_from, name);

        char buf[8192];
        // 回应
        sprintf(buf, "nameack|%s|%s", myuserid, myname);
        printf("send nameack --> %s\n", userid_from);
        sendUdp(buf, userid_from);
    }
    if(strcmp(cmd, "nameack") == 0)
    {
        char* name = strtok(NULL, "|");
        change_name(userid_from, name);
    }
    if(strcmp(cmd, "msg") == 0)
    {
        // msg|userid|content
        char* content = strtok(NULL, "|");
        User* user = findUser(userid_from);
        printf("%s(%s)说: %s\n", user->username, userid_from, content);
    }

}
