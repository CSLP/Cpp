#include "topic.h"
#include "ui_topic.h"
#include<QString>
#include<QDebug>
#include<vector>
#include<QGroupBox>
#include<QTextBrowser>
#include<QVBoxLayout>
#include"message.h"
#include"interface.h"
#include<QString>
#include<QPushButton>
#include<QLineEdit>
using std::vector;
Topic::Topic(Message msg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Topic)
{
    ui->setupUi(this);
    vector<Message>	comments=getCommentsByTopicId(msg.id);
    qDebug()<<comments.size();
    QVBoxLayout *layout=new QVBoxLayout;
    QString comTitle;
    vector<QWidget *> rps;
    vector<QPushButton *> shows;
    vector<QPushButton *> folds;

    for(int i=0;i<comments.size();++i)
    {
        QGroupBox *b=new QGroupBox;
        b->setMinimumHeight(800);
        QVBoxLayout*lay=new QVBoxLayout;
        QTextBrowser * comBrowser=new QTextBrowser;
        comBrowser->setText(comments[i].content);
        QHBoxLayout * layh=new QHBoxLayout;
        QPushButton * ShowReplyBtn=new QPushButton("ShowReply");
        ShowReplyBtn->setObjectName(tr("ShowReplyBtn%1").arg(i));
        QPushButton * FoldReplyBtn=new QPushButton("FoldReply");
        FoldReplyBtn->setObjectName(tr("FoldRePlyBtn%1").arg(i));
        shows.push_back(ShowReplyBtn);
        folds.push_back(FoldReplyBtn);
        layh->addWidget(ShowReplyBtn);
        layh->addWidget(FoldReplyBtn);
        QWidget * rp=new QWidget;
        rps.push_back(rp);
        QVBoxLayout * layv=new QVBoxLayout;
        QTextBrowser * repBrowser=new QTextBrowser;
        QHBoxLayout * layhh=new QHBoxLayout;
        QLineEdit  *edit=new QLineEdit;
        QPushButton *sendBtn=new QPushButton("Send");
        layhh->addWidget(edit);
        layhh->addWidget(sendBtn);
        layv->addWidget(repBrowser);
        layv->addLayout(layhh);
        rp->setLayout(layv);
        vector<Message> replys=getReplysByCommentId(comments[i].id);
        QString reply;
        for(int j=0;j<replys.size();++j)
        {
            reply=replys[j].author+"回复"+replys[j].sendTo+":"+replys[i].content+"               		                   "+replys[i].time;
            repBrowser->append(reply);
        }
        lay->addWidget(comBrowser);
        lay->addLayout(layh);
        lay->addWidget(rp);
        lay->setStretch(0,4);
        lay->setStretch(1,1);
        lay->setStretch(2,2);
        b->setLayout(lay);
        comTitle=comments[i].author+"                     "+comments[i].time;
        b->setTitle(comTitle);
        layout->addWidget(b);
    }
    ui->scrollArea->widget()->setLayout(layout);
    ui->scrollArea->hide();
    QString topicTitle=msg.author+":"+msg.content+"             "+msg.time;
    //qDebug()<<QString::fromStdString(msg.content);
    ui->label->setText(topicTitle);
}

Topic::~Topic()
{
    delete ui;
}

void Topic::setVis(bool v)
{
   ui->scrollArea->setVisible(v);
}
