#include <windows.h>
#include <lauxlib.h>
#include <lua.h>

int lua_sleep(lua_State *L)
{
    int sec = (int)luaL_checknumber(L, -1);
    lua_pop(L, 1);
    Sleep(sec * 1000);
    return 0;
}

int lua_sleep_msec(lua_State *L)
{
    int msec = (int)luaL_checknumber(L, -1);
    lua_pop(L, 1);
    Sleep(msec);
    return 0;
}

__declspec(dllexport) int luaopen_sleep(lua_State *L) {
    lua_newtable(L);
    lua_pushcfunction(L, lua_sleep);
    lua_setfield(L, -2, "sleep");
    lua_pushcfunction(L, lua_sleep_msec);
    lua_setfield(L, -2, "sleepM");
    return 1;
}