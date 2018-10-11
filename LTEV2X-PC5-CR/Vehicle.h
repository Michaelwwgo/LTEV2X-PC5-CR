#pragma once
#include <iostream>
#include <list>
#include "Basic.h"
#include "BBlock.h"
#include "Radio.h"

class Vehicle
{
public:
	Vehicle();
	~Vehicle();
	/*���Ա����*/
	/*��õĻ�����Ϣ����*/
	const int& getId();
	const Pos& getPos();
	const Speed& getSpeed();
	const stateVehicle* getState();
	/*��������ģ��*/
	void rsuInitial(int idTemp, Radio* radioTemp);
	void vehicleInitial(int idTemp, BBlock* blockTemp, Radio* radioTemp);
	/*λ�ø���ģ��*/
	bool isNotInCross();
	bool isNotInsideBlock(BBlock* blockTemp);
	void blockAccess();
	void updateRelativeSpeed();
	void updateLocation();
	void reLocation(BBlock *blockTemp);
	void wrapAround();
	/*�ھ��ж�ģ��*/
	bool isNotNeighbor(Vehicle* vehicleTemp);
	void updateNeighbor();
	/*·����ļ���*/
	void updateDis();
	void updatePathLoss();
	void updateShadowLoss();
	void updateBigLoss();
	void updateMultiLoss(int tTemp);
	void updateRSRP();
	/*��ֵ����ģ��*/
	void updateResEnv();
	void updateCqi(int tTemp);
	void updateCycleData(int tTemp);
	/*��Դ����ģ��*/
	void scheduleRandom();
	/*��Ϣ������غ���*/
	void cycleClear();
	void dropClear();
private:
	//���������Ա����
	/*������Ϣ*/
	Pos pos;
	Speed speed;
	int id;
	Radio* radio = NULL;
	int blockID;
	BBlock* block;
	bool crossJudgeOrNot = false;
	/*·�������Ϣ*/
	double disCross[CROSS_NUM];
	double dis[VEHICLE_NUM + RSU_NUM];
	double pathLoss[VEHICLE_NUM + RSU_NUM];
	double shadowLoss[VEHICLE_NUM + RSU_NUM];
	double bigLoss[VEHICLE_NUM + RSU_NUM];
	double rsrp[VEHICLE_NUM + RSU_NUM];
	double rsrpM[VEHICLE_NUM + RSU_NUM];
	double relativeSpeed[VEHICLE_NUM + RSU_NUM];
	double multiLoss[VEHICLE_NUM + RSU_NUM];
	bool lossTypeNLOSorNot[VEHICLE_NUM + RSU_NUM];
	/*�ź���Ƶ����Ϣ*/
	Cqi cqi;
	std::list<int>neighborList;
	std::list<int>neighborTransCycle;
	int resourceWindow[CYCLE][RB_NUM];
	int resourceEnvironment[CYCLE][RB_NUM];
	int receiveID[CYCLE][RB_NUM];
	/*��Ϊ��Ϣ��ͳ����Ϣ*/
	stateVehicle Vehiclestate[CYCLE][RB_NUM];
	PrrData prrData;
	RecTransData rectransdata;
	std::vector<Pair>cumData;
	std::vector<int>recSucID;
};

Vehicle::Vehicle()
{
}

Vehicle::~Vehicle()
{
}