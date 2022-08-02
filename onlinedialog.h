#ifndef ONLINEDIALOG_H
#define ONLINEDIALOG_H

#include <QDialog>
#include<QString>
#include"TcpClientMediator.h"
#include"packdef.h"
#include"MD5/md5.h"
class OnlineDialog;
namespace Ui {
class OnlineDialog;
}
typedef void(OnlineDialog::*PFUN)(uint sock,char *buf,int nlen);
class OnlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnlineDialog(QWidget *parent = nullptr);
    ~OnlineDialog();
signals:
    void SIG_rtmp(QString str);
    void  SIG_Process( int64_t , int64_t);
private slots:
    void on_pb_send_clicked();
    void slot_dealloginRs(uint sock,char *buf,int nlen);
    void slot_dealRegisRs(uint sock,char *buf,int nlen);
    void slot_dealblockRs(uint sock,char *buf,int nlen);
    void slot_dealrandRs(uint sock,char *buf,int nlen);
    void slot_dealhotRs(uint sock,char *buf,int nlen);
    void on_pb_zc_clicked();
    void slot_dealdata(uint,char*,int);
    void set();
    void on_pb_login_clicked();
    void slot_commit_file(QString c);

    void on_pb_tv_clicked();

    void on_pb_hot_clicked();

    void on_pushButton_clicked();

    void on_pb_get1_clicked();

    void on_pb_get2_clicked();

    void on_pb_get3_clicked();

private:
    Ui::OnlineDialog *ui;
     INetMediator *m_inet;
      PFUN m_netpackmap[DEF_PACK_COUNT];
      char arz[3][100];
      char arc[3][100];
     QString m_name ;
      int m_id;
};

#endif // ONLINEDIALOG_H
