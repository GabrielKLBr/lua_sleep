#include <windows.h>
#include <lmcons.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <lua.hpp>
#include <string>
#include <vector>

static std::vector<std::string> includes;

static int lua_includeheader(lua_State *L) {
    const char *header = luaL_checkstring(L, 1);
    includes.push_back(header);
    return 0;
}

static int lua_run(lua_State *L) {
    const char *code = luaL_checkstring(L, 1);
    const char* username = getenv("USERNAME");
    if (!username) {
        lua_pushstring(L, "Erro ao obter nome do usuário");
        lua_error(L);
    }
    
    std::string filepath = "C:\\Users\\" + std::string(username) + "\\temp.cpp";
    std::ofstream file(filepath);
    
    if (!file) {
        lua_pushstring(L, "Falha ao criar o arquivo temporário");
        lua_error(L);
    }
    
    for (const auto &inc : includes) {
        file << inc << "\n";
    }
    file << code;
    file.close();
    
    std::string command = "g++ " + filepath + " -o C:\\Users\\" + std::string(username) + "\\temp.exe && C:\\Users\\" + std::string(username) + "\\temp.exe";
    int status = std::system(command.c_str());
    
    if (status != 0) {
        lua_pushstring(L, "Erro ao compilar ou rodar código");
        lua_error(L);
    }
    
    return 0;
}

// Exportando a função corretamente para Lua
__declspec(dllexport) int luaopen_ffi(lua_State *L) {
    lua_newtable(L);
    lua_pushcfunction(L, lua_includeheader);
    lua_setfield(L, -2, "include");
    lua_pushcfunction(L, lua_run);
    lua_setfield(L, -2, "run");
    return 1;
}
