#include "onlinedialog.h"
#include "ui_onlinedialog.h"
#include<QMessageBox>
#define NetPackmap(a) m_netpackmap[a-DEF_PACK_BASE]
OnlineDialog::OnlineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineDialog)
{
    ui->setupUi(this);
    m_inet=new TcpClientMediator;

    m_inet->OpenNet(_DEF_SERVERIP,_DEF_TCP_PORT);
     connect(m_inet,SIGNAL(SIG_ReadyData(uint,char*,int)),this,SLOT(slot_dealdata(uint,char*,int)));
     memset(arz,0,sizeof(arz));

     set();
}

OnlineDialog::~OnlineDialog()
{
    delete ui;
    delete m_inet;
}
#include <QApplication>
#include"QDebug"
void OnlineDialog::on_pb_send_clicked()
{
    QString str=ui->le_rtmp->text();
    if(!str.isEmpty())
    {
        Q_EMIT SIG_rtmp(str);
    }
    this->close();
}

void OnlineDialog::slot_dealloginRs(uint sock, char *buf, int nlen)
{
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;
    //根据返回结果, 得到不同信息
    switch( rs->m_lResult )
    {
      case userid_no_exist:
        QMessageBox::about(this,"提示","用户不存在，登陆失败");
        break;
      case password_error:
        QMessageBox::about(this,"提示","密码错误，登录失败");
        break;
       case 10:
        {
        QMessageBox::about(this,"提示","有人异地登录");
           //slot_destory();
        }
      case login_sucess:
      {
        m_id=rs->m_userID;

        m_name=QString::fromStdString(rs->m_szName);
        QMessageBox::about(this,"提示","登录成功");
    }
   }
}

void OnlineDialog::slot_dealRegisRs(uint sock, char *buf, int nlen)
{
    STRU_REGISTER_RS *rsrs=(STRU_REGISTER_RS *)buf;
    switch(rsrs->m_lResult)
    {
     case userid_is_exist:
        QMessageBox::about(this,"提示","用户电话已经存在");
        break;
     case register_sucess:
         QMessageBox::about(this,"提示","注册成功");
        break;
     case name_is_exist:

         QMessageBox::about(this,"提示","昵称已存在");

        break;
    default:
        break;
    }
}

void OnlineDialog::slot_dealblockRs(uint sock, char *buf, int nlen)
{
    STRU_FILEBLOCK_RS *p=(STRU_FILEBLOCK_RS*)buf;
    if(p->m_result==1)
        QMessageBox::about(this,"提示","文件上传成功");
}

void OnlineDialog::slot_dealrandRs(uint sock, char *buf, int nlen)
{
     qDebug()<< "aoligan";
    STRU_DEF_PACK_GetRandrs *rs=(STRU_DEF_PACK_GetRandrs *)buf;
    string c1(rs->arr[0]);

     strcpy(arz[0],rs->ark[0]);
    ui->label_3->setText(QString::fromStdString( c1));

    string c2(rs->arr[2]);
    strcpy(arz[1],rs->ark[1]);
     strcpy(arc[1],rs->arr[1]);
    strcpy(arc[0],rs->arr[0]);
     strcpy(arc[2],rs->arr[2]);
     ui->label_4->setText(QString::fromStdString( c2));
     string c3(rs->arr[2]);
      strcpy(arz[2],rs->ark[2]);
      ui->label_5->setText(QString::fromStdString( c3));
}

void OnlineDialog::slot_dealhotRs(uint sock, char *buf, int nlen)
{
    STRU_DEF_PACK_GetHotrs *rs=(STRU_DEF_PACK_GetHotrs *)buf;
   //缓存热点视频
    string c1(rs->arr[0]);
     strcpy(arz[0],rs->ark[0]);
    ui->label_3->setText(QString::fromStdString( c1));

    string c2(rs->arr[1]);
    strcpy(arz[1],rs->ark[1]);
     ui->label_4->setText(QString::fromStdString( c2));
     string c3(rs->arr[2]);
     strcpy(arc[1],rs->arr[1]);
    strcpy(arc[0],rs->arr[0]);
     strcpy(arc[2],rs->arr[2]);
      strcpy(arz[2],rs->ark[2]);
      ui->label_5->setText(QString::fromStdString( c3));
}

static std::string GetMD5STRING(QString ctr)
{
    QString str=QString("%1_%2").arg(ctr).arg(1234);
    std::string strsrc=str.toStdString();
    MD5 md5(strsrc);
    return md5.toString();
}
void OnlineDialog::on_pb_zc_clicked()
{
    QString strtel=ui->tel_edit_zh->text();
    QString strpassword=ui->tel_edit_pass->text();
    //校验 1.手机号  正则表达式 清掉空格后不能是空字符串2.密码 长度不过20  （非空校验）
    QString tmptel=strtel, tmppassword=strpassword;
    if(tmptel.remove(" ").isEmpty()||tmppassword.remove(" ").isEmpty())
    {
      QMessageBox::about(this,"提示","手机密码不能为空");//调用静态方法来提示
      return;
    }

    QRegExp reg("^1[3-8][0-9]\{6,9\}$");
    bool res=reg.exactMatch(tmptel);
    if(!res)
    {
        QMessageBox::about(this,"提示","手机号格式错误");//调用静态方法来提示
        return;

    }
    if(tmppassword.length()>20)
    {
        QMessageBox::about(this,"提示","密码过长");//调用静态方法来提示
        return;
    }
    std::string strtelc=strtel.toStdString();
    int i=sizeof(STRU_LOGIN_RQ)+sizeof(STRU_REGISTER_RQ)+sizeof(int);

    STRU_REGISTER_RQ rq;
    strcpy(rq.m_tel,strtelc.c_str());



    std::string md5pass=GetMD5STRING(strpassword);
    strcpy(rq.m_Password,md5pass.c_str());



    m_inet->SendData(0,(char *)&rq,sizeof(rq));




}

void OnlineDialog::slot_dealdata(uint sock, char *buf, int nlen)
{

    int type = *(int*)buf;
    qDebug()<<type;
     if( (type >= DEF_PACK_BASE) && ( type < DEF_PACK_BASE + DEF_PACK_COUNT) )
       {
             PFUN pf = NetPackmap( type );
             if( pf )
             {
                 //(this->*pf)
                 (this->*pf)( sock, buf , nlen);
             }
     }
     delete []buf;
}

void OnlineDialog::set()
{
    memset(m_netpackmap,0,sizeof(m_netpackmap));
    NetPackmap(DEF_PACK_LOGIN_RS)=&OnlineDialog::slot_dealloginRs;
    NetPackmap(DEF_PACK_REGISTER_RS)=&OnlineDialog::slot_dealRegisRs;
    NetPackmap(DEF_PACK_FILEBLOCK_RS)=&OnlineDialog::slot_dealblockRs;
    NetPackmap(DEF_PACK_GetRandrs)=&OnlineDialog::slot_dealrandRs;
    NetPackmap(DEF_PACK_GetHotrs)=&OnlineDialog::slot_dealhotRs;
}


void OnlineDialog::on_pb_login_clicked()
{
    QString strtel=ui->tel_edit_zh->text();
    QString strpassword=ui->tel_edit_pass->text();
    //校验 1.手机号  正则表达式 清掉空格后不能是空字符串2.密码 长度不过20  （非空校验）
    QString tmptel=strtel, tmppassword=strpassword;
    if(tmptel.remove(" ").isEmpty()||tmppassword.remove(" ").isEmpty())
    {
      QMessageBox::about(this,"提示","手机密码不能为空");//调用静态方法来提示
      return;
    }

    QRegExp reg("^1[3-8][0-9]\{6,9\}$");
    bool res=reg.exactMatch(tmptel);
    if(!res)
    {
        QMessageBox::about(this,"提示","手机号格式错误");//调用静态方法来提示
        return;

    }
    if(tmppassword.length()>20)
    {
        QMessageBox::about(this,"提示","密码过长");//调用静态方法来提示
        return;
    }
    std::string strtelc=strtel.toStdString();



    STRU_LOGIN_RQ rq;
    strcpy(rq.m_tel,strtelc.c_str());


    std::string md5pass=GetMD5STRING(strpassword);
    strcpy(rq.m_szPassword,md5pass.c_str());






    m_inet->SendData(0,(char *)&rq,sizeof(rq));
}
#include<QFileInfo>
void OnlineDialog::slot_commit_file(QString filealePath)
{
    QFileInfo info(filealePath);
    QString filealeName = info.fileName();
    std::string strName = filealeName.toStdString();
    const char* fileale_name = strName.c_str();


    STRU_UPLOAD_RQ rq;
    char szbuf[60];
    strcpy(szbuf,GetMD5STRING("33_11").c_str());
    rq.m_nFileId=atoi(szbuf);
    rq.m_nFileSize = info.size();
    strcpy_s( rq.m_szFileName , MAX_PATH , fileale_name );



    rq.m_UserId = m_id;
   m_inet->SendData( 0,(char*)&rq , sizeof( rq ));
    FileInfo  fil;
    fil.fileId = rq.m_nFileId;
    fil.fileName = filealeName;
    fil.filePath = filealePath;
    fil.filePos = 0;
    fil.fileSize = rq.m_nFileSize;
    fil.pFile = new QFile(filealePath);

    if( fil.pFile->open(QIODevice::ReadOnly))
    {
        while(1)
        {
              STRU_FILEBLOCK_RQ blockrq;

             int64_t res = fil.pFile->read( blockrq.m_szFileContent , MAX_CONTENT_LEN);
             fil.filePos += res;
             blockrq.m_nBlockLen = res ;
             blockrq.m_nFileId = rq.m_nFileId;
             blockrq.m_nUserId = m_id;

             m_inet->SendData(0,(char *)&blockrq,sizeof(blockrq));
             emit SIG_Process( fil.filePos , fil.fileSize);

             if( fil.filePos >= fil.fileSize )
             {
                 fil.pFile->close();
                 delete fil.pFile;
                 fil.pFile = NULL;
                 break;;

             }
        }
    }

}


void OnlineDialog::on_pb_tv_clicked()
{

       Q_EMIT SIG_rtmp( "http://39.134.115.163:8080/PLTV/88888910/224/3221225633/index.m3u8");

    this->close();
}


void OnlineDialog::on_pb_hot_clicked()
{

    STRU_DEF_PACK_GetHotrq rq;
    m_inet->SendData(0,(char*)&rq,sizeof(rq));
}


void OnlineDialog::on_pushButton_clicked()
{
    STRU_DEF_PACK_GetRandrq rq;
     m_inet->SendData(0,(char*)&rq,sizeof(rq));
}


void OnlineDialog::on_pb_get1_clicked()
{
    string c(arz[0]);
    STRU_Hot_rs rs;
    strcpy(rs.ark,arc[0]);
     m_inet->SendData(0,(char*)&rs,sizeof(rs));
     Q_EMIT SIG_rtmp(QString::fromStdString( c));

}


void OnlineDialog::on_pb_get2_clicked()
{
    string c(arc[1]);
    STRU_Hot_rs rs;
    strcpy(rs.ark,arc[1]);
     m_inet->SendData(0,(char*)&rs,sizeof(rs));
     Q_EMIT SIG_rtmp(QString::fromStdString( c));

}


void OnlineDialog::on_pb_get3_clicked()
{
    string c(arz[2]);
    STRU_Hot_rs rs;
    strcpy(rs.ark,arc[2]);
     m_inet->SendData(0,(char*)&rs,sizeof(rs));
     Q_EMIT SIG_rtmp(QString::fromStdString( c));

}

