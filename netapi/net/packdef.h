#pragma once

#include <QCoreApplication>
#include<QTime>
#include<QByteArray>
#include"QFile"
#define _DEF_BUFFER  ( 4096 )
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE	(40)
//#define _DEF_PORT 8000
//#define _DEF_SERVERIP "192.168.0.100"  //TODO
//自定义协议   先写协议头 再写协议结构
//登录 注册 获取好友信息 添加好友 聊天 发文件 下线请求
#define _DEF_PROTOCOL_BASE	(10000)
#define _DEF_PROTOCOL_COUNT (100)
#define DEF_PACK_BASE  (10000)
#define DEF_PACK_COUNT  (100)
#define _DEF_SERVERIP "192.168.0.103"


//注册
#define  DEF_PACK_REGISTER_RQ    (DEF_PACK_BASE + 0)
#define  DEF_PACK_REGISTER_RS    (DEF_PACK_BASE + 1)
//登录
#define  DEF_PACK_LOGIN_RQ    (DEF_PACK_BASE + 2)
#define  DEF_PACK_LOGIN_RS    (DEF_PACK_BASE + 3)

#define  DEF_PACK_UPLOAD_RQ  (DEF_PACK_BASE + 4)
#define DEF_PACK_UPLOAD_RS  (DEF_PACK_BASE + 5)
#define DEF_PACK_FILEBLOCK_RQ (DEF_PACK_BASE + 6)
#define DEF_PACK_FILEBLOCK_RS (DEF_PACK_BASE + 7)
#define DEF_PACK_GetRandrq  (DEF_PACK_BASE + 8)
#define DEF_PACK_GetRandrs (DEF_PACK_BASE + 9)
#define DEF_PACK_GetHotrq  (DEF_PACK_BASE + 10)
#define DEF_PACK_GetHotrs  (DEF_PACK_BASE + 11)
#define DEF_Hotrs  (DEF_PACK_BASE + 12)


typedef int PackType;
//注册请求结果
#define userid_is_exist      0
#define register_sucess      1
#define name_is_exist        2
//登录请求结果
#define userid_no_exist      0
#define password_error       1
#define login_sucess         2
//#define user_online          3



#define MAX_PATH            (260 )
#define MAX_SIZE            (60  )

#define MAX_CONTENT_LEN     (4096 )
enum Status { Wolf=1, prophet=2, villager=3, witch=4, hunter=5 };


//协议结构
//注册
//登录请求
typedef struct STRU_LOGIN_RQ
{
    STRU_LOGIN_RQ()
    {
        m_nType = DEF_PACK_LOGIN_RQ;
        memset(m_tel,0,MAX_SIZE);
        memset(m_szPassword,0,MAX_SIZE);
    }

    PackType m_nType;   //包类型
    char     m_tel[MAX_SIZE] ; //用户ID
    char     m_szPassword[MAX_SIZE];  //密码
} STRU_LOGIN_RQ;




//登录回复
typedef struct STRU_LOGIN_RS
{
    STRU_LOGIN_RS()
    {
        m_nType= DEF_PACK_LOGIN_RS;
        m_userID = 0;
        m_lResult = 0;
         memset(m_szName,0,MAX_SIZE);
    }
    PackType m_nType;   //包类型
    int  m_userID;
    int  m_lResult ; //注册结果
    char m_szName[MAX_SIZE];
} STRU_LOGIN_RS;
//注册请求
typedef struct STRU_REGISTER_RQ
{
    STRU_REGISTER_RQ()
    {
        m_nType = DEF_PACK_REGISTER_RQ;
        memset(m_tel,0,MAX_SIZE);
        memset(m_Password,0,MAX_SIZE);
        memset(m_name,0,MAX_SIZE);
    }

    PackType m_nType;   //包类型
    char     m_tel[MAX_SIZE] ; //用户名
    char     m_Password[MAX_SIZE];  //密码
    char      m_name[MAX_SIZE];

} STRU_REGISTER_RQ;

//注册回复
typedef struct STRU_REGISTER_RS
{
    STRU_REGISTER_RS()
    {
        m_nType= DEF_PACK_REGISTER_RS;
        m_lResult = 0;
    }
    PackType m_nType;   //包类型
    int  m_lResult ; //注册结果

} STRU_REGISTER_RS;

typedef struct STRU_UPLOAD_RQ
{
    STRU_UPLOAD_RQ()
    {
        m_nType = DEF_PACK_UPLOAD_RQ;
        m_nFileId = 0;
        m_UserId = 0;
        m_nFileSize = 0;

        memset(m_szFileName , 0 ,MAX_PATH);

    }
    PackType m_nType; //包类型
    int m_UserId; //用于查数据库, 获取用户名字, 拼接路径
    int m_nFileId; //区分不同文件
    int64_t m_nFileSize; //文件大小, 用于文件传输结束
    char m_szFileName[MAX_PATH]; //文件名, 用于存储文件

}STRU_UPLOAD_RQ;

//上传文件请求回复
typedef struct STRU_UPLOAD_RS
{
    STRU_UPLOAD_RS()
    {
        m_nType = DEF_PACK_UPLOAD_RS;
        m_nResult = 0;
    }
    PackType m_nType; //包类型
    int m_nResult;
}STRU_UPLOAD_RS;
struct FileInfo
{
    int fileId;
    int videoId;
    int64_t filePos;
    int64_t fileSize;
    QString filePath;
    QString fileName;
    QString rtmpUrl;
    QFile *pFile;
};

typedef struct STRU_FILEBLOCK_RQ
{
    STRU_FILEBLOCK_RQ()
    {
        m_nType = DEF_PACK_FILEBLOCK_RQ;
        m_nUserId = 0;
        m_nFileId =0;
        m_nBlockLen =0;
        memset(m_szFileContent,0,MAX_CONTENT_LEN);
    }
    PackType m_nType; //包类型
    int m_nUserId; //用户 ID
    int m_nFileId; //文件 id 用于区分文件
    int m_nBlockLen; //文件写入大小
    char m_szFileContent[MAX_CONTENT_LEN];
}STRU_FILEBLOCK_RQ;

typedef struct STRU_FILEBLOCK_RS
{
    STRU_FILEBLOCK_RS()
    {
        m_nType = DEF_PACK_FILEBLOCK_RS;
        m_result=0;

    }
    PackType m_nType; //包类型
    int m_result;

}STRU_FILEBLOCK_RS;
typedef struct STRU_DEF_PACK_GetRandrq
{
    STRU_DEF_PACK_GetRandrq()
    {
        m_nType = DEF_PACK_GetRandrq;


    }
    PackType m_nType; //包类型


}STRU_DEF_PACK_GetRandrq;
typedef struct STRU_DEF_PACK_GetRandrs
{
    STRU_DEF_PACK_GetRandrs()
    {
        m_nType = DEF_PACK_GetRandrs;
        memset(arr,0,sizeof(arr));
        memset(ark,0,sizeof(ark));

    }
    PackType m_nType; //包类型
    char arr[3][40];
    char ark[3][40];

}STRU_DEF_PACK_GetRandrs;

typedef struct STRU_DEF_PACK_GetHotrq
{
    STRU_DEF_PACK_GetHotrq()
    {
        m_nType = DEF_PACK_GetHotrq;
   }
    PackType m_nType; //包类型


}STRU_DEF_PACK_GetHotrq;
typedef struct STRU_DEF_PACK_GetHotrs
{
    STRU_DEF_PACK_GetHotrs()
    {
        m_nType = DEF_PACK_GetHotrs;
        memset(arr,0,sizeof(arr));
        memset(ark,0,sizeof(ark));
   }
    PackType m_nType; //包类型
    char arr[3][40];
    char ark[3][40];

}STRU_DEF_PACK_GetHotrs;
typedef struct STRU_Hot_rs
{
    STRU_Hot_rs()
    {
        m_nType = DEF_Hotrs;

        memset(ark,0,sizeof(ark));
   }
    PackType m_nType; //包类型

    char ark[20];

}STRU_Hot_rs;
// 数据库
/*
	表1 用户表 id->唯一标识 tel  password  name  iconid   feeling 也可以写成两张表 登录和用户信息
	列:  id  tel password  name  iconid  feeling

	表2 好友  idA  idB
	列 idA  idB  
	操作: 好友关系是双向关系  关注是单向关系  , 添加好友时 , 需要写入两行 即 A->B B->A 方便查询
	(添加好友 查找一般比插入多)

//	表3 离线消息
	
	用户数据表t_user
	create table t_user ( id bigint unsigned  AUTO_INCREMENT primary key, tel varchar (260) , 
	password varchar(260)  , name varchar (260) , icon int , feeling varchar(260));

	可以添加测试数据 
	insert into t_user ( tel,password , name , icon , feeling  ) 
	values ('12345','test', '12345' ,1,'比较懒,什么也没写')

	好友表 t_friend
	create table t_friend ( idA bigint unsigned  , idB bigint unsigned);
    create table t_music ( id bigint unsigned  AUTO_INCREMENT primary key, tel varchar (260) ,
    rtmpaddress varchar(260)  , hot int, label varchar(260));

*/








