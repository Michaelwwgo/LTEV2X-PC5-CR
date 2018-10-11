#pragma once

#include <iostream>
#include <vector>
#include <math.h>
/* ��Ȼ�����ͽ�������
*/
#define PI 3.14159265358979323846
const double LANE_WIDTH = 3.5; //��λ��m,��·���
const double SIDEWALK_WIDTH = 3.0;//��λm,���е����
const double STREET_WIDTH = 20.0;//��λm,�ֵ����
const double ROAD_LENGTH = 433.0;//��λm,��������
const double ROAD_WIDTH = 250.0;//��λm,�������
const double NUM_LANE_UNI = 2;//���������
const int NUM_LANE_DOU = NUM_LANE_UNI * 2;//˫���ĳ���
const int RSU_NUM = 16;//RSU����
const int CROSS_NUM = 16;//ʮ��·������
const int BLOCK_NUM = 9;//��������
const double ROAD_ALL_LENGTH = (ROAD_LENGTH * BLOCK_NUM + ROAD_WIDTH * BLOCK_NUM) * NUM_LANE_DOU ;//���˳����ܳ���

/* ��Ƶ�Ϳտڲ���*/
const double PENETRATION_LOSS = 0;//dB,�������
const double NOISE_FIGURE_V = 9;//dB������ϵ��
const double MAX_TX_PWOER = 23;//dBm,����书��
const double ANTENNA_GAIN_V = 3;//dB,OBU��������
const double ANTENNA_GAIN_R = 3;//dB,RSU��������
const double ANTENNA_HEIGHT_V = 1.5;//OBU���߸߶�
const double ANTENNA_HEIGHT_R = 5;//RSU���߸߶�
const double FREQUENCY_CW = 5905;//MHz,�ز�Ƶ��
const double LAMDA = 3e8 / FREQUENCY_CW / 1000000;//����,m
const double CENTER_FREQ = 2 * PI * FREQUENCY_CW / 1e3;//�ز���Ƶ��,��λΪ����(rad)
const int RB_NUM = 50;//RB������10MHz
const double BAND_WIDTH = 10;// MHz, ����
const double SUM_BAND_WIDTH = 0.18;//RBƵ�ʿ�ȣ�MHz
const double N0 = SUM_BAND_WIDTH * 1E6 * pow(10.0, (-174.0 / 10.0)) * pow(10.0, (NOISE_FIGURE_V / 10.0)); //��RB������������λΪmW

/*�����˶�����*/
const double VEHICLE_DIRECTION_RIGHT = 0.0 / 360.0 * 2 * PI;//rad,���������
const double VEHICLE_DIRECTION_UP = 90.0 / 360.0 * 2 * PI;// ���������
const double VEHICLE_DIRECTION_LEFT = 180.0 / 360.0 * 2 * PI;//���������
const double VEHICLE_DIRECTION_DOWN = 270.0 / 360.0 * 2 * PI;//���������
const double P_TURN_RIGHT = 0.25;//ʮ��·����ת����
const double P_TURN_LEFT = 0.25;//ʮ��·����ת����
const double P_TURN_STRAIGHT = 0.5;//ʮ��·��ֱ�и���
const double SPEED_MAX = 60.0 * 1000 / 60 / 60;//����٣�m/s
const double VEHICLE_SPACING = 2.5 * SPEED_MAX;//���㳵��ƽ������
const double MIN_VEHICLE_SPACE = 1 * SPEED_MAX;//������С�������
/*·�������ز���*/
const double SHADOW_LOSS_DEV_NLOS = 4;//NLOS����µ���Ӱ˥���׼����
const double SHADOW_LOSS_DEV_LOS = 3;//LOS����µ���Ӱ˥���׼����
const double LOS_Threshold_Horizon = ROAD_WIDTH;//LOS�����ж����� ˮƽ����
const double LOS_Threshold_Vertical = ROAD_LENGTH;//LOS�����ж����� ��ֱ����
const int NP = 9;//�ྶ����еĴ���
const int MSP = 20;//�ྶ����е�ÿ���ص��Ӿ���
const double PARTH_DELAY[NP] = { 0, 30, 150, 310, 370, 710, 1090, 1730, 2510 };//ÿ���صĵ���ʱ��
const double PATH_POWER[NP] = { 0.2412, 0.1708, 0.1747, 0.1053, 0.2101, 0.0297, 0.0481, 0.0152, 0.0049 };//ÿ����Ĺ�һ����������
const double COS_ALPHA[MSP] = { 1.000, 0.9511, 0.8090, 0.5878,
								0.3090, 0.0000, -0.3090, -0.5878,
								-0.8090, -0.9511, -1.0000, -0.9511,
								-0.8090, -0.5878, -0.3090, -0.0000,
								0.3090, 0.5878, 0.8090, 0.9511 };//ÿ���ص�ÿ���Ӿ��ﵽ�Ƕȵ�����ֵ
/*����������·��ӿڲ���*/
const int VEHICLE_NUM = 585;//ʵ�ʼ��㷽ʽΪint(floor(ROAD_ALL_LENGTH/VEHICLE_SPACING)).������Ҫ������ƽ��������9�����������Դ���ӦΪ9�ı���
const int vehicleNumPerBlock = VEHICLE_NUM / BLOCK_NUM;//����ʱÿ�������ĳ�����
const double maxRange = 50;//�ھ��жϷ�Χ
const double MCL = 130;//��·�������������������ȷ�������µ����������
const double SINR_REQUIRED = MCL - 10 * log10(pow(10, (MAX_TX_PWOER / 10.0)) / RB_NUM) - ANTENNA_GAIN_V - ANTENNA_GAIN_V + 10 * log10(N0);//MCL����ز����Ƶ��ó�����ȷ�������������SINR
const double MESSAGE_SIZE = 300;//Ĭ�Ϸ���300bytes�����ݷ���
const int SLOT_PER_PACKET = 4;//ÿ�����ݷ�������Ҫ��TTI��
const int RB_PER_PACKET = 10;//ÿ�����ݷ�����ÿ��TTI�������ĵ�RB��

/*��������*/
const int CYCLE = 100; //ms,

/*�����ṹ�͹�����*/
// λ�ýṹ�壬X,Y����
struct Pos
{
	double x;
	double y;
};
// �ٶȽṹ�壬�ٶȾ���ֵ�������
struct Speed
{
	double value;
	double direction;
};
// ��¼�ɹ����շ��ͷ��������ݵ�RB�����������ͷ���ID�ͳɹ��������ݵ�RB��
struct Pair
{
	int id;
	int times;
};
// ������ʵ�����鲿
struct Complex
{
	double real;
	double virt;
};
// �ŵ�����ָʾ����������������������RB����������ź������ܺ͡����ź�������SINR
struct Cqi
{
	double all[CYCLE][RB_NUM];
	double main[CYCLE][RB_NUM];
	double SINR[CYCLE][RB_NUM];
};

/*
����ͳ����Ϣ�� ������ 
1. �����ڴ������ݷ�����
2. �����ڽ������ݷ�����
3. �ۼƴ������ݷ�����
4. �ۼƽ������ݷ�����
5. �����ڷ��������
6. ���������ڷ��������
*/
struct PrrData
{
	unsigned int transCycle;
	unsigned int receCycle;
	unsigned int transAccu;
	unsigned int receAccu;
	double prrPerCycle;
	double prrPerDrop;
};

/*
��Ϊ�ͽ������ͳ�ƣ�����:
1. ������ÿ��RB�����ź���Դ�ڵ�ID;
2. ������ÿ��RB�Ƿ�ɹ���������
3. ������ÿ��RB�Ƿ�������ݣ�
4. ������ÿ��RB�Ƿ�������
5. ������ÿ��RB�Ƿ�Ĭ
*/
struct RecTransData
{
	int receiveid[CYCLE][RB_NUM];
	bool receiveSucOrNot[CYCLE][RB_NUM];
	bool receiveOrNot[CYCLE][RB_NUM];
	bool transOrNot[CYCLE][RB_NUM];
	bool listenOrNot[CYCLE][RB_NUM];
};

/*
	��Ϊ��
	1. ����
	2. ����
	3. ��Ĭ
*/
typedef enum
{
	receive,
	transmit,
	listen
}stateVehicle;

/*
V2V��·/V2I��·���ŵ�������
1. LOS
2. NLOS
3.���̫Զ���Բ�����
*/
typedef enum
{
	LOS,
	NLOS,
	notConcern
}lossType;

/*
�����࣬������������������vector�����У�����find_if����Ѱ��ָ�����ͷ��ĳɹ��������ݵ�RB��Ŀ
*/
class vector_finder
{
public:
	vector_finder(const int a) :m_i_a(a) {};
	bool operator()(const std::vector<Pair>::value_type &value)
	{
		return value.id == m_i_a;
	}
private:
	int m_i_a;
};
