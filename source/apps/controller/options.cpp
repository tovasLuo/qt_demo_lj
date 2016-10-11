#include "options.h"

#define  CONFIGNAME "channel.ini"
#define  CHANNELGROUP "ChannelOption"
#define  TRANSGROUP "DataTransOption"
#define  KEYCHANNELNUMBER "ChannelNumber"
#define  KEYTRANSFLAG "IsTransFlag"
#define  KEYTRANSIP "TransIP"
#define  KEYTRANSPORT "TransPort"

options::options() : m_nChannelNumber(0)
  ,m_bDataTransFlag(false)
  ,m_nDataTransPort(0)
{
    m_p_qsetting = new QSettings(CONFIGNAME,QSettings::IniFormat);
    ReadConfigIni();
}

options::~options()
{
    delete m_p_qsetting;
}

options* options::get_instance()
{
    static options instance;
    return &instance;
}

void options::SetChannelNumber(int number)
{
    m_nChannelNumber = number;
    m_p_qsetting->beginGroup(CHANNELGROUP);
    m_p_qsetting->setValue(KEYCHANNELNUMBER,m_nChannelNumber);
}

void options::SetDataTransFlag(bool bflag)
{
    m_bDataTransFlag = bflag;
    m_p_qsetting->beginGroup(TRANSGROUP);
    m_p_qsetting->setValue(KEYTRANSFLAG,m_bDataTransFlag);
}

void options::SetDataTransIP(const std::__cxx11::string &sIp)
{
    m_strDataTransIP = sIp;
    m_p_qsetting->beginGroup(TRANSGROUP);
    m_p_qsetting->setValue(KEYTRANSIP,m_strDataTransIP.c_str());
}


void options::SetDataTransPort(int nport)
{
    m_nDataTransPort = nport;
    m_p_qsetting->beginGroup(TRANSGROUP);
    m_p_qsetting->setValue(KEYTRANSPORT,m_nDataTransPort);
}

bool options::GetChannelInfo(int index, ChannelInfo &info)
{
    if((index - 1) < 0 || index > (int)m_vector_info.size()){
        return false;
    }
    info = m_vector_info[index - 1];
    return true;
}

void options::ReadConfigIni()
{
    //读取每个通道的信息
    m_p_qsetting->beginGroup(CHANNELGROUP);
    m_nChannelNumber = m_p_qsetting->value(KEYCHANNELNUMBER).toInt();
    for(int i=0;i<m_nChannelNumber;i++){
        ChannelInfo info;
        char sip[64] = {0};//ip
        char schannelVerifyMode[64] = {0};//模式
        char sgateState[64] = {0};//门状态
        char sexposionLevel[64] = {0};//曝光
        sprintf(sip,"ChannelIP_%d",i+1);
        sprintf(schannelVerifyMode,"VerifyMode_%d",i+1);
        sprintf(sgateState,"GateState_%d",i+1);
        sprintf(sexposionLevel,"ExLevel_%d",i+1);
        info.strchannelIP = m_p_qsetting->value(sip).toString().toStdString();
        info.bchannelVerifyMode = m_p_qsetting->value(schannelVerifyMode).toBool();
        info.bchannelGateState = m_p_qsetting->value(sgateState).toBool();
        info.nExposionLevel = m_p_qsetting->value(sexposionLevel).toInt();
        m_vector_info.push_back(info);
    }
    //读取上传数据的ip和端口
    m_p_qsetting->beginGroup(TRANSGROUP);
    m_bDataTransFlag = m_p_qsetting->value(KEYTRANSFLAG).toBool();
    m_strDataTransIP = m_p_qsetting->value(KEYTRANSIP).toString().toStdString();
    m_nDataTransPort = m_p_qsetting->value(KEYTRANSPORT).toInt();
}