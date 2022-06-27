#include<iostream>
#include<fstream>
#include <string>
#include <cstring>
using namespace std;

#define PATH_SIZE  50
#define MAX_MSG_NUM 10
#define MAX_DATACONFIG_FILE  10
#define MAX_FILE_NAME 20



struct Config
{
    char cOutfilepath[PATH_SIZE];               //生成文件的路径最好和配置文件在同一个路径 没有做缺省处理
    int iSingOrTwo;                             //资源管理文件和逻辑处理文件是在一个文件夹还是分开写 1
    char cFileName[MAX_FILE_NAME];              //生成的文件前缀名 最终会在这个文件名字后加上 ResMgr.h/cpp 或 Mgr.h/cpp
    char cProtoFileName[MAX_FILE_NAME];         //proto文件的命名

    int iMsgNum;                              //proto文件中cs协议的个数 
    char apMsgName[MAX_MSG_NUM][30];         //proto文件中具体的消息名称

    int iDataConfigFileNum;                     //dataconfig文件个数
    char apConfigDataName[MAX_DATACONFIG_FILE][30]; //具体dataconfig文件的名字(表名字)

    void ShowDetailConfig()
    {
        printf(" outfilepath: %s \n iSingOrTwo: %d \n cFileName: %s\n cProtoFile: %s\n", cOutfilepath, iSingOrTwo, cFileName, cProtoFileName);

        printf("iMsgNum: %d\n", iMsgNum);
        for (int i = 0 ;i < iMsgNum; i++)
        {
            printf("    csfilename: %s",apMsgName[i]);
        }
        printf("\n");

        printf("iDataConfigFileNum: %d \n",iDataConfigFileNum);
        for (int i = 0; i < iDataConfigFileNum; ++i)
        {
            printf("    Dataconfigfilname: %s",apConfigDataName[i]);
        }
        printf("\n");
    }
};

int FillConfig(struct Config* pConfig, char *pszConfigPath)
{
    if (pConfig == NULL)
    {
        printf("wrong configpath\n");
        return  -1;
    }

    //以读模式打开文件
    ifstream infile;
    infile.open(pszConfigPath);

    int iTemp1 = 0;
    int iTemp2 = 0;

    int i = 0;
    int iHelp = 0;

    //i  代表当前行
    //while(infile.peek() != EOF) 这个也无法判断是否到达了末尾 编译器版本问题?
    //while(!infile.eof()) 这么写也无法判断是否到达了文件末尾 
    //绝望 只能下面这么做的
    while (iHelp++ != 50)
    {  
        if (i == 0)
        {
            infile >> pConfig->cOutfilepath;
            i++;
        }
        else if( i == 1)
        { 
            char cSingOrTwo;
            infile >>cSingOrTwo;
            pConfig->iSingOrTwo = cSingOrTwo - 48;//这里直接用字符减去48转成整型
            //校验下配置的正确性
            if (pConfig->iSingOrTwo != 1 && pConfig->iSingOrTwo != 2)
            {
                printf("wrong iSingOrTwo config: %d\n", pConfig->iSingOrTwo);
                return -1;
            }
            i++;
        }
        else if (i == 2)
        {
            infile >> pConfig->cFileName;
            i++;
        }
        else if (i == 3)
        {
            infile >> pConfig->cProtoFileName;   
            i++;   
        }
        else if (i == 4)
        {
            char cCsProNum;
            infile >> cCsProNum;
            pConfig->iMsgNum = cCsProNum - 48;
            if (pConfig->iMsgNum < 0 || pConfig->iMsgNum > MAX_MSG_NUM)
            {
                printf("wrong iMsgNum config: %d\n",pConfig->iMsgNum);
                return -1;
            }
            i++;
        }
        else if(i == 5)
        {
            iTemp1 = i;
            //读取cs协议名字       
            for (; i < iTemp1 + pConfig->iMsgNum ; i++)
            {
                infile >> pConfig->apMsgName[i - iTemp1];
            }

        }
        else if(i == iTemp1 + pConfig->iMsgNum)
        {
            //读取dataconfig文件
            char iDataConfigFileNum ;
            infile >> iDataConfigFileNum;
            pConfig->iDataConfigFileNum = iDataConfigFileNum - 48;
            if (pConfig->iDataConfigFileNum < 0 || pConfig->iDataConfigFileNum > MAX_DATACONFIG_FILE)
            {
                printf("wrong iDataConfigFileNum config: %d\n", pConfig->iDataConfigFileNum);
                return -1;
            }
            i++;
        }
        else if(i == iTemp1 + pConfig->iMsgNum + 1)
        {
            iTemp2 = i;
            for (; i < iTemp2 + pConfig->iDataConfigFileNum; ++i)
            {  
                infile >>  pConfig->apConfigDataName[i - iTemp2];
            }
        }
    }
    infile.close();
    return 0;
}   

char * ToLower(char *tempOutbuf, char * str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        tempOutbuf[i] = tolower(str[i]);
    }
    return tempOutbuf;
}

//ResMgr.h文件主体
void MakeResMgrHeadBody(ofstream &outfile ,struct Config &stConfig)
{
    for (int i = 0 ; i < stConfig.iDataConfigFileNum; ++i)
    {
        char tempbuf[100]={'0'};
        outfile << "#include \"dataconfig_" <<ToLower(tempbuf, stConfig.apConfigDataName[i])<<".pb.h\"\n";   
    }

    outfile <<"\n\n\n";

    for (int i = 0 ; i < stConfig.iDataConfigFileNum; ++i)
    {
        outfile << "typedef dataconfig::" <<stConfig.apConfigDataName[i]<<" "<<"PB"<<stConfig.apConfigDataName[i]<<";\n";
        outfile << "typedef dataconfig::" <<stConfig.apConfigDataName[i]<<"Array"<<" "<<"PB"<<stConfig.apConfigDataName[i]<<"Array" <<";\n";
        outfile <<"\n";

        outfile <<"class CPB"<<stConfig.apConfigDataName[i]<<"Holder"<<":"<<"public"<<" "<<"CPBResDataLoader<uint32_t, "<<"PB"<<stConfig.apConfigDataName[i]<<"Array, "<<"PB"<<stConfig.apConfigDataName[i]<<">\n";
        outfile <<"{\n";
        outfile <<"public:\n";
        outfile <<"      virtual uint32_t GetKey(const PB"<<stConfig.apConfigDataName[i]<<"&"<<" pb"<<stConfig.apConfigDataName[i]<<")\n";
        outfile <<"      {\n";
        outfile <<"         //TODO :这里要修改策划具体配的表key是什么 文件生成后就改成什么\n";
        outfile <<"         //return pb"<<stConfig.apConfigDataName[i]<<".id();\n";
        outfile <<"         return 0;\n";
        outfile <<"      }\n";
        outfile <<"};\n";
    }

    outfile << "class C"<<stConfig.cFileName<<"ResMgr : public CSington<C" <<stConfig.cFileName<<"ResMgr>\n";
    outfile << "{\n";
    outfile << "public:\n";
    outfile << "    int Init();\n";
    for (int i = 0; i <  stConfig.iDataConfigFileNum; ++i)
    {
        outfile <<"    CPB"<<stConfig.apConfigDataName[i]<<"Holder"<<" "<<"m_PB"<<stConfig.apConfigDataName[i]<<"Holder"<<";\n";
        outfile <<"     //获取单条资源数数据,参数使用什么可以自己修改\n";
        outfile <<"    const PB"<<stConfig.apConfigDataName[i]<<"*"<<" Get" << stConfig.apConfigDataName[i]<<"Data(uint32_t dwID);" <<"//这里也是要做修改\n";
        outfile <<"    const PB"<<stConfig.apConfigDataName[i]<<"Array"<<"*"<<" GetAll"<<stConfig.apConfigDataName[i]<<"Data();\n"; 
        outfile <<"\n\n";
    }
    outfile <<"};\n\n";
}
//ResMgr.cpp文件主体
void MakeMgrHeadBody( ofstream &outfile ,struct Config &stConfig)
{
    outfile <<"namespace cs\n";
    outfile <<"{\n";
    outfile <<"     class CSPkgHead;\n";
    for (int i =0 ; i < stConfig.iMsgNum; ++i)
    {
        outfile <<"     class "<<stConfig.apMsgName[i]<<";\n";
    }
    outfile <<"}\n";

    outfile <<"enum Enum"<<stConfig.cFileName<<"ErrorCode\n";
    outfile <<"{\n";
    outfile <<"\n\n";
    outfile <<"};\n";

    outfile <<"class CPlayer;\n\n";
    outfile <<"class C"<<stConfig.cFileName<<"Mgr: "<<"public CSington<C" <<stConfig.cFileName<<"Mgr>,public CEventListener\n";
    outfile <<"{\n";

    outfile <<"public:\n";
    outfile <<"     int Init();\n";
    outfile <<"     int OnEvent(int iEventType, EventData* pParam);\n";
    for (int i =0 ; i< stConfig.iMsgNum; ++i)
    {
        outfile <<"     int Proc"<<stConfig.apMsgName[i]<<"(CPlayer *pPlayer, const cs::CSPkgHead& stCSPkgHead, const cs::"<<stConfig.apMsgName[i]<<"& stReq);\n";
        outfile <<"\n";
    }
    outfile <<"};\n";

}
void MakeResMgrSourceBody(ofstream &outfile ,struct Config &stConfig)
{
    char tempbuf[100]={'0'}; 
    outfile << "#include \"" <<ToLower(tempbuf, stConfig.cProtoFileName)<<".pb.h\"\n";   

    outfile <<"\n\n\n";

    for (int i = 0 ; i < stConfig.iDataConfigFileNum; ++i)
    {
        char tempbuf[100]={'0'};
        outfile << "const char * g_"<<stConfig.apConfigDataName[i]<<"filepath = "<<"\"dataconfig_" <<ToLower(tempbuf, stConfig.apConfigDataName[i])<<".data\";\n";   
    }


    outfile <<"\n\n\n";
    outfile <<"int C"<<stConfig.cFileName<<"ResMgr::Init()\n";
    outfile <<"{\n";

    for (int  i = 0;i < stConfig.iDataConfigFileNum; ++i)
    {
        outfile <<"     if (0 != "<<"m_PB"<<stConfig.apConfigDataName[i]<<"Holder.LoadResData(RedirectConfigDataFile(g_"<<stConfig.apConfigDataName[i]<<"filepath"<<")))\n";
        outfile <<"     {\n";
        outfile <<"         LOG_ERR(\"write yourself\");\n";
        outfile <<"         return -1;\n";
        outfile <<"     }\n";
    }
    outfile <<"     return 0;\n";
    outfile <<"}\n";

    outfile <<"\n";
    for (int i =0 ;  i < stConfig.iDataConfigFileNum ;++i)
    {
        outfile <<"//TODO 具体表的key获取方式可以修改\n";
        outfile << "const PB"<<stConfig.apConfigDataName[i]<<"*"<<" C"<<stConfig.cFileName<<"ResMgr::Get" << stConfig.apConfigDataName[i]<<"Data(uint32_t dwID)\n";
        outfile <<"{\n";
        outfile <<"     return m_PB"<<stConfig.apConfigDataName[i]<<"Holder.GetResByKey(dwID);\n";
        outfile <<"}\n";

        outfile << "const PB"<<stConfig.apConfigDataName[i]<<"Array"<<"*"<<" C"<<stConfig.cFileName<<"ResMgr::"<<"GetAll"<<stConfig.apConfigDataName[i]<<"Data()\n"; 
        outfile <<"{\n";
        outfile <<"     return m_PB"<<stConfig.apConfigDataName[i]<<"Holder.GetAllResData();\n";
        outfile <<"}\n\n";

    }
    return ;
}

void MakeMgrSourceBody(ofstream &outfile ,struct Config &stConfig)
{
    outfile <<"int C"<<stConfig.cFileName<<"Mgr::Init()\n";
    outfile <<"{\n";

    outfile <<"     int iRet = C"<<stConfig.cFileName<<"ResMgr::Instance()->Init();\n";
    outfile <<"         if (iRet != 0 )\n";
    outfile <<"         {\n";
    outfile <<"             return iRet;\n";
    outfile <<"         }\n";
    outfile <<"     return 0;\n";
    outfile <<"}\n\n";


    outfile <<"int C"<<stConfig.cFileName<<"Mgr::OnEvent(int iEventType, EventData* pParam)\n";
    outfile <<"{\n";
    outfile <<"     CHECK_IF_NULL_RET(pParam, -1);\n";
    outfile <<"     return 0;\n";
    outfile <<"}\n";

    outfile <<"\n\n";
    for (int i = 0 ; i < stConfig.iMsgNum; ++i)
    {
        outfile <<"int C"<<stConfig.cFileName<<"Mgr::Proc"<<stConfig.apMsgName[i]<<"(CPlayer *pPlayer, const cs::CSPkgHead& stCSPkgHead, const cs::"<<stConfig.apMsgName[i]<<"&"<<" stReq)\n";
        outfile <<"{\n";
        outfile <<"     CHECK_IF_NULL_RET(pPlayer, -1); \n";
        outfile <<"     const int iMsgSeqID = stCSPkgHead.msgseqid();\n";

        outfile <<"     //CZoneMsgMgr::Send2Client( , iMsgSeqID, (const void *)&stRes, pPlayer);\n";
        outfile <<"     return 0;\n";
        outfile <<"}\n\n";
    }

    return ;
}





//ResMgr 和 Mgr在一个文件内
void MakeMgrAndResMgrHeadFile(ofstream &outfile ,struct Config &stConfig)
{
    outfile << "/**\n";
    outfile << "* Dear Programer:\n";
    outfile << "*       hope you have a good day\n";
    outfile << "**/ \n";

    outfile << "#pragma once \n";
    outfile << "#include \"Sington.h\"\n";
    outfile << "#include \"PBResDataLoader.hpp\"\n";
    outfile << "#include \"EventMgr.h\"\n";

    MakeResMgrHeadBody(outfile, stConfig); 
    MakeMgrHeadBody(outfile , stConfig);
    return ;
}
void MakeMgrAndResMgrSourceFile(ofstream &outfile ,struct Config &stConfig)
{
    outfile << "#include \""<<stConfig.cFileName<<"Mgr.h\"\n";
    outfile << "#include \"BaseLog.h\"\n";
    outfile << "#include \"EventMgr.h\"\n";
    outfile << "#include \"Player.h\"\n";
    outfile << "#include \"LoaderMgr.h\"\n";
    outfile << "#include \"ZoneMsgMgr.h\"\n";

    MakeResMgrSourceBody(outfile, stConfig);
    MakeMgrSourceBody(outfile, stConfig);
    return;
}


//ResMgr和 Mgr不在一个文件内
void MakeMgrHeadFile(ofstream & outfile, struct Config &stConfig)
{
    outfile << "/**\n";
    outfile << "* Dear Programer:\n";
    outfile << "*       hope you have a good day\n";
    outfile << "**/ \n";

    outfile << "#pragma once \n";
    outfile << "#include \"Sington.h\"\n";
    outfile << "#include \"EventMgr.h\"\n";

    outfile <<"\n\n\n";

    MakeMgrHeadBody(outfile, stConfig);
    return ;
}

void MakeMgrSourceFile(ofstream & outfile, struct Config &stConfig)
{
    outfile << "#include \""<<stConfig.cFileName<<"ResMgr.h\"\n";
    outfile << "#include \""<<stConfig.cFileName<<"Mgr.h\"\n";
    outfile << "#include \"BaseLog.h\"\n";
    outfile << "#include \"EventMgr.h\"\n";
    outfile << "#include \"Player.h\"\n";
    outfile << "#include \"ZoneMsgMgr.h\"\n";

    outfile <<"\n\n\n";

    MakeMgrSourceBody(outfile, stConfig);
    return ;
}

void MakeResMgrHeadFile(ofstream & outfile, struct Config &stConfig)
{
    outfile << "/**\n";
    outfile << "* Dear Programer:\n";
    outfile << "*       hope you have a good day\n";
    outfile << "**/ \n";

    outfile << "#pragma once \n";
    outfile << "#include \"Sington.h\"\n";
    outfile << "#include \"PBResDataLoader.hpp\"\n";

    MakeResMgrHeadBody(outfile, stConfig);
    return ;
}
void MakeResMgrSourceFile(ofstream & outfile, struct Config &  stConfig)
{
    outfile << "#include \""<<stConfig.cFileName<<"ResMgr.h\"\n";
    outfile << "#include \"BaseLog.h\"\n";
    outfile << "#include \"LoaderMgr.h\"\n";

    MakeResMgrSourceBody(outfile, stConfig);
    return ;
}


//制作app头文件
void MakeAppHeadFile(ofstream & outfile, struct Config &  stConfig)
{
    outfile <<"#pragma once\n";
    outfile <<"#include<BaseApp.h>\n";
    outfile <<"class CPlayer;\n";
    outfile <<"class C"<<stConfig.cFileName<<"App : public CBaseApp\n";
    outfile <<"{\n";
    
    outfile <<"     virtual int Init();\n\n"
            <<"     virtual int Reload();\n\n"
            <<"     virtual int Fini();\n\n"
            <<"     virtual int Tick1S();\n\n"
            <<"     virtual int HandleMsg(const CBaseMsg& Msg);\n\n"
            <<"     virtual int HandleCSMsg(const CBaseMsg& Msg);\n\n"
            <<"     virtual int HandleSSMsg(const CBaseMsg& Msg);\n\n";
    outfile <<"};\n";
    return ;
}

//制作app源文件
void MakeAppSourceFile(ofstream & outfile, struct Config &  stConfig)
{
    outfile <<"#include \""<<stConfig.cProtoFileName<<".pb.h\"\n";
    outfile <<"#include \""<<stConfig.cFileName<<"App.h\"\n";
    outfile <<"#include \""<<stConfig.cFileName<<"Mgr.h\"\n";
    outfile <<"#include \"ss_message.pb.h\"\n";
    outfile <<"#include \"cs_message.pb.h\"\n";
    outfile <<"#include \"common_enum.pb.h\"\n";
    outfile <<"#include \"Player.h\"\n";
    outfile <<"#include \"PlayerMgr.h\"\n";


    outfile <<"int C"<<stConfig.cFileName<<"App::Init()\n"
        <<"{\n";

    outfile <<"//TODO 协议号自己修改哈\n";
    for (int i = 0; i < stConfig.iMsgNum; ++i)
    {       
        outfile <<"     RegCmdID<cs::"<<stConfig.apMsgName[i]<<">(123);\n";
    }
    outfile<<"      return 0;\n";
    outfile<<"}\n\n";

    outfile <<"int C"<<stConfig.cFileName <<"App::Reload()\n"
        <<"{\n"
        <<"     return 0;\n"
        <<"}\n";
    outfile <<"int C"<<stConfig.cFileName <<"App::Fini()\n"
        <<"{\n"
        <<"     return 0;\n"
        <<"}\n";
    outfile <<"int C"<<stConfig.cFileName <<"App::Tick1S()\n"
        <<"{\n"
        <<"     return 0;\n"
        <<"}\n";

    outfile <<"int C"<<stConfig.cFileName<<"App::HandleMsg(const CBaseMsg &Msg)\n"
        <<"{\n"
        <<"     int iRet = 0;\n"
        <<"     const int iCmdID = Msg.GetCmdID(); \n"
        <<"     const uint32_t dwBusID = Msg.GetDstAddr(); \n"
        <<"     LOG_DBG(\"Got Msg, CmdID[%d], BusID[%u]\", iCmdID, dwBusID); \n\n"
        <<"     const bool bCltFlag = Msg.IsClientMsg(); \n"
        <<"     if (iCmdID >= SERVER_CMD_ID_SS_MIN && bCltFlag) \n"
        <<"     {\n"
        <<"         LOG_ERR(\"client send ss message. CmdID: %d\", iCmdID);\n"
        <<"         return -1;\n"
        <<"     }\n\n"
        <<"     if (bCltFlag)\n"
        <<"     {\n"
        <<"         iRet = HandleCSMsg(Msg);"
        <<"     }\n"
        <<"     else\n"
        <<"     {\n"
        <<"         iRet = HandleSSMsg(Msg);\n"
        <<"     }\n\n"
        <<"     return iRet;\n\n"
        <<"}\n\n";

    outfile <<"int C"<<stConfig.cFileName<<"App::HandleCSMsg(const CBaseMsg &Msg)\n"
        <<"{\n"
        <<"     int iRet = 0;\n"
        <<"     const int iCmdID = Msg.GetCmdID(); \n"
        <<"     LOG_DBG(\"Got Msg, CmdID[%d]\", Msg.GetCmdID());\n\n "
        <<"     uint64_t ullTransmitID = Msg.GetTransmitID(); \n"
        <<"     CPlayer *pPlayer = CPlayerMgr::Instance()->GetPlayerByTransmitID(ullTransmitID); \n"
        <<"     if (NULL == pPlayer) \n"
        <<"     {\n"
        <<"         LOG_ERR(\"Handler client message not found player. CmdID: %d, TransmitID: %\" PRIu64, Msg.GetCmdID(),ullTransmitID);\n"
        <<"         return -1;\n"
        <<"     }\n\n"
        <<"     const cs::CSPkgHead &stCSPkgHead = *(const cs::CSPkgHead *) Msg.GetMsgHead(); \n"
        <<"     const char *pBody = Msg.GetMsgBody(); \n"
        <<"     if (NULL == pBody) \n"
        <<"     {\n"
        <<"         LOG_ERR(\"%s|CmdID: %d not body message\", pPlayer->GetLogInfo(), iCmdID); \n"
        <<"         return -1;\n"
        <<"     }\n\n"
        <<"     switch (iCmdID)\n"
        <<"     {\n";

    outfile<<"      //TODO 协议号自己写哈\n";
    for (int i = 0 ; i < stConfig.iMsgNum; ++i)
    {
        outfile <<"         case "<<"123"<<i<<":\n"
                <<"             iRet = C"<<stConfig.cFileName<<"Mgr::Instance()->Proc"<<stConfig.apMsgName[i]<<"(pPlayer, stCSPkgHead, *(const cs::"<<stConfig.apMsgName[i]<<"*)"<<" pBody);\n"
                <<"         break;\n\n";
    }

         outfile<<"         default:\n"
                <<"             LOG_ERR(\"CmdID[%d] Has No Handle Function\", iCmdID);\n"
                <<"         break;\n"
        <<"     }\n\n"<<"   return iRet;\n"<<"}\n";
        
    outfile <<"int C"<<stConfig.cFileName<<"App::HandleSSMsg(const CBaseMsg &Msg)\n"
        <<"{\n"
        <<"     int iRet = 0;\n"
        <<"     const int iCmdID = Msg.GetCmdID(); \n"
        <<"     LOG_DBG(\"Got Msg, CmdID[%d]\", Msg.GetCmdID());\n\n "
        <<"     const char *pHead = Msg.GetMsgHead();\n"
        <<"     const char *pBody = Msg.GetMsgBody();\n"
        <<"     if (NULL == pHead || NULL == pBody)\n"
        <<"     {\n"
        <<"         LOG_ERR(\"CmdID: %d not message body\", iCmdID);\n"
        <<"         return -1;\n"
        <<"     }\n\n"
        <<"     uint64_t ullTransmitID = Msg.GetTransmitID(); \n"
        <<"     CPlayer *pPlayer = CPlayerMgr::Instance()->GetPlayerByTransmitID(ullTransmitID); \n"
        <<"     if (NULL == pPlayer) \n"
        <<"     {\n"
        <<"         LOG_ERR(\"Handler client message not found player. TransmitID: %\" PRIu64, ullTransmitID);\n"
        <<"         return -1;\n"
        <<"     }\n\n"
        <<"     const ss::SSPkgHead &stSSPkgHead = *(const ss::SSPkgHead *) pHead; \n"
        <<"     switch (iCmdID)\n"
        <<"     {\n"
        <<"         default:\n"
        <<"             LOG_ERR(\"CmdID[%d] Has No Handle Function\", iCmdID);\n"
        <<"         break;\n"
        <<"     }\n"
        <<"     return iRet;\n"
        <<"}\n";
    return ;
}



int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("need config file: xxx.ini default in current path\n");
        return -1;
    }

    struct Config stConfig;
    if (0 != FillConfig(&stConfig, argv[1]))
    {
        printf("fill config failed, check you config file\n");
        return -1;
    }

#ifdef DEBUG
    stConfig.ShowDetailConfig();
#endif

    //ResMgr和Mgr代码在同一个文件内
    if (stConfig.iSingOrTwo == 1)
    {
        //制作头文件
        ofstream outHeadfile;
        int flen = strlen(stConfig.cFileName);
        int outlen = strlen(stConfig.cOutfilepath);
        char tempath[100]={'0'};

        memcpy(tempath, stConfig.cOutfilepath, outlen);
        memcpy(tempath+outlen, stConfig.cFileName, flen);
        memcpy(tempath+strlen(tempath),"Mgr.h",5);

#ifdef DEBUG
        printf("outfilepath: %s\n",tempath);
#endif
        outHeadfile.open(tempath);
        if (!outHeadfile)
        {
            printf("%s outfilepath wrong: %s\n",tempath);
            return -1;
        }
        MakeMgrAndResMgrHeadFile(outHeadfile, stConfig);
        outHeadfile.close();

        // 制作源文件
        ofstream outSourfile;
        char tempath1[100]={'0'};
        memcpy(tempath1, stConfig.cOutfilepath, outlen);
        memcpy(tempath1+outlen, stConfig.cFileName, flen);
        memcpy(tempath1+strlen(tempath1),"Mgr.cpp",7);

#ifdef DEBUG
        printf("outfilepath: %s\n",tempath1);
#endif
        outSourfile.open(tempath1);
        if (!outSourfile)
        {
            printf("%s outfilepath wrong: %s\n",tempath1);
            return -1;
        }
        MakeMgrAndResMgrSourceFile(outSourfile,stConfig);
        outSourfile.close();
    }
    else if(stConfig.iSingOrTwo == 2)//ResMgr和Mgr分两个文件
    {
        //制作Mgr头文件
        ofstream outHeadfile;
        int flen = strlen(stConfig.cFileName);
        int outlen = strlen(stConfig.cOutfilepath);
        char tempath[100]={'0'};

        memcpy(tempath, stConfig.cOutfilepath, outlen);
        memcpy(tempath+outlen, stConfig.cFileName, flen);
        memcpy(tempath+strlen(tempath),"Mgr.h",5);

        outHeadfile.open(tempath);
        if (!outHeadfile)
        {
            printf("outheadfule path wrong:%s\n", tempath);
            return -1;
        }
        MakeMgrHeadFile(outHeadfile,stConfig);
        outHeadfile.close();



        //制作Mgr源文件
        ofstream outSourcefile;
        flen = strlen(stConfig.cFileName);
        outlen = strlen(stConfig.cOutfilepath);
        char tempath1[100]={'0'};

        memcpy(tempath1, stConfig.cOutfilepath, outlen);
        memcpy(tempath1+outlen, stConfig.cFileName, flen);
        memcpy(tempath1+strlen(tempath1),"Mgr.cpp",7);

        outSourcefile.open(tempath1);
        if (!outSourcefile)
        {
            printf("outheadfule path wrong:%s\n", tempath1);
            return -1;
        }

        MakeMgrSourceFile(outSourcefile , stConfig);
        outSourcefile.close();



        //制作ResMgr头文件
        ofstream outHeadfile2;
        flen = strlen(stConfig.cFileName);
        outlen = strlen(stConfig.cOutfilepath);
        char tempath2[100]={'0'};

        memcpy(tempath2, stConfig.cOutfilepath, outlen);
        memcpy(tempath2+outlen, stConfig.cFileName, flen);
        memcpy(tempath2+strlen(tempath2),"ResMgr.h",8);

        outHeadfile2.open(tempath2);
        if (!outHeadfile2)
        {
            printf("outheadfule path wrong:%s\n", tempath2);
            return -1;
        }

        MakeResMgrHeadFile(outHeadfile2, stConfig);
        outHeadfile2.close();




        //制作ResMgr的源文件
        ofstream outSourcefile2;
        flen = strlen(stConfig.cFileName);
        outlen = strlen(stConfig.cOutfilepath);
        char tempath3[100]={'0'};

        memcpy(tempath3, stConfig.cOutfilepath, outlen);
        memcpy(tempath3+outlen, stConfig.cFileName, flen);
        memcpy(tempath3+strlen(tempath3),"ResMgr.cpp",10);

        outSourcefile2.open(tempath3);
        if (!outSourcefile2)
        {
            printf("outheadfile path wrong:%s\n", tempath3);
            return -1;
        }
        MakeResMgrSourceFile(outSourcefile2,stConfig);
        outSourcefile2.close();
    }
    else 
    {
        printf("System Wrong\n");
        return -1;
    }
    //制作app头文件
    ofstream outHeadfile;
    int flen = strlen(stConfig.cFileName);
    int outlen = strlen(stConfig.cOutfilepath);
    char tempath[100]={'0'};

    memcpy(tempath, stConfig.cOutfilepath, outlen);
    memcpy(tempath+outlen, stConfig.cFileName, flen);
    memcpy(tempath+strlen(tempath),"App.h",5);

    outHeadfile.open(tempath);
    if (!outHeadfile)
    {
        printf("%s outfilepath wrong: %s\n",tempath);
        return -1;
    }
    MakeAppHeadFile(outHeadfile, stConfig);
    outHeadfile.close();

    // 制作app源文件
    ofstream outSourfile;
    char tempath1[100]={'0'};
    memcpy(tempath1, stConfig.cOutfilepath, outlen);
    memcpy(tempath1+outlen, stConfig.cFileName, flen);
    memcpy(tempath1+strlen(tempath1),"App.cpp",7);
    outSourfile.open(tempath1);
    if (!outSourfile)
    {
        printf("%s outfilepath wrong: %s\n",tempath1);
        return -1;
    }
    MakeAppSourceFile(outSourfile, stConfig);
    outSourfile.close();

    return 0;
}

