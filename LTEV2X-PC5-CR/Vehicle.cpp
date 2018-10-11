#include <iostream>
#include "Vehicle.h"
#include "BBlock.h"
#include "Radio.h"
#include "Random.h"

/*ΪOBU���������Ϣ��λ����Ϣ����Դ������Ϣ
 ID���տ����Ӷ�����������ָ��Ͷ���ID;������OBU�����Ӧ������vehiclelist��
*/
void Vehicle::vehicleInitial(int idTemp, BBlock* blockTemp, Radio* radioTemp)
{
	if (idTemp < VEHICLE_NUM)
	{
		id = idTemp;
		radio = radioTemp;
		block = blockTemp;
		blockID = block->getId();
		block->blockAccept(this);
		int k1;
		k1 = Random::random() % 8;
		/*����ͼ5-3�����ˣ�����������ʽ�OBU��λ�������ʼ���ڽ�����8��������ĳһ��������ĳ��λ���ϣ�������˳ʱ����г�����ȷ��OBU���ٶ���Ϣ��
		���磺��k1 = 0, OBU��λ�ó�ʼ���ڽ����Ҳ��һ��������ĳ��λ���ϣ������ٶȾ���ֵΪ����٣�����Ϊ�·���*/
		switch (k1) 
		{
		case 0:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_DOWN;
			pos.x = blockTemp->getPos().x + (ROAD_WIDTH / 2) - LANE_WIDTH - LANE_WIDTH / 2.0;
			pos.y = blockTemp->getPos().y + Random::Uniform(-ROAD_LENGTH / 2, ROAD_LENGTH / 2);
			break;
		}
		case 1:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_DOWN;
			pos.x = blockTemp->getPos().x + (ROAD_WIDTH / 2) - LANE_WIDTH / 2.0;
			pos.y = blockTemp->getPos().y + Random::Uniform(-ROAD_LENGTH / 2, ROAD_LENGTH / 2);
			break;
		}
		case 2:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_RIGHT;
			pos.y = blockTemp->getPos().y + (ROAD_LENGTH / 2) - LANE_WIDTH - LANE_WIDTH / 2.0;
			pos.x = blockTemp->getPos().x + Random::Uniform(-ROAD_WIDTH / 2, ROAD_WIDTH / 2);
			break;
		}
		case 3:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_RIGHT;
			pos.y = blockTemp->getPos().y + (ROAD_LENGTH / 2) - LANE_WIDTH / 2.0;
			pos.x = blockTemp->getPos().x + Random::Uniform(-ROAD_WIDTH / 2, ROAD_WIDTH / 2);
			break;
		}
		case 4:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_UP;
			pos.x = blockTemp->getPos().x - (ROAD_WIDTH / 2) + LANE_WIDTH + LANE_WIDTH / 2.0;
			pos.y = blockTemp->getPos().y + Random::Uniform(-ROAD_LENGTH / 2, ROAD_LENGTH / 2);
			break;
		}
		case 5:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_UP;
			pos.x = blockTemp->getPos().x - (ROAD_WIDTH / 2) + LANE_WIDTH / 2.0;
			pos.y = blockTemp->getPos().y + Random::Uniform(-ROAD_LENGTH / 2, ROAD_LENGTH / 2);
			break;
		}
		case 6:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_LEFT;
			pos.y = blockTemp->getPos().y - (ROAD_LENGTH / 2) + LANE_WIDTH + LANE_WIDTH / 2.0;
			pos.x = blockTemp->getPos().x + Random::Uniform(-ROAD_WIDTH / 2, ROAD_WIDTH / 2);
			break;
		}
		case 7:
		{
			speed.value = SPEED_MAX;
			speed.direction = VEHICLE_DIRECTION_LEFT;
			pos.y = blockTemp->getPos().y - (ROAD_LENGTH / 2) + LANE_WIDTH / 2.0;
			pos.x = blockTemp->getPos().x + Random::Uniform(-ROAD_WIDTH / 2, ROAD_WIDTH / 2);
			break;
		}
		default:break;
		}
	}
	/*���������ʽ��ʼ����OBUռ����Դ����������
	������ռ��4ms��ÿ1msռ��10RB��Ƶ����Դ��
	���磺����Ϊ��50��100�е���Դ��������Ϊ125�ݣ�����k2,k3ȡֵ��OBUռ�����е�һ����Դ*/
	int k2, k3;
	k2 = Random::random() % (CYCLE / SLOT_PER_PACKET);
	k3 = Random::random() % (RB_NUM / RB_PER_PACKET);
	for (int i = 0; i < CYCLE; i++)
	{
		for (int j = 0; j < RB_NUM; j++)
		{
			if (((i >= k2 * SLOT_PER_PACKET) && (i < (k2 + 1)*SLOT_PER_PACKET)) && ((j >= k3 * RB_PER_PACKET) && (j < (k3 + 1)*RB_PER_PACKET)))
			{
				resourceWindow[i][j] = 1;
			}
			else
			{
				resourceWindow[i][j] = 0;
			}
		}
	}
}

/*
ΪRSU���������Ϣ��λ����Ϣ����Դ������Ϣ
*/
void Vehicle::rsuInitial(int idTemp, Radio* radioTemp)
{
	/* ��ʼ��������Ϣ������: ID;�տ����Ӷ����ٶ�Ĭ��Ϊ0��
	��������ָ��Ͷ���ID;������ OBU�����Ӧ������vehiclelist �С����У�RSU Ĭ������0�Ž���*/
	id = idTemp;
	radio = radioTemp;
	speed.value = 0.0;
	block = &(radio->blocks[0]);
	blockID = block->getId();
	block->blockAccept(this);
	/* ��RSU��λ�ð���id�̶��ڶ�Ӧʮ��·�ڵ�����λ��*/
	int column = (id - VEHICLE_NUM) % 4;
	int row = (id - VEHICLE_NUM) / 4;
	pos.x = column * ROAD_WIDTH;
	pos.y = row * ROAD_LENGTH;

	/*��OBU������Դ����ķ�ʽ��ͬ*/
	int k1, k2;
	k1 = Random::random() % (CYCLE / SLOT_PER_PACKET);
	k2 = Random::random() % (RB_NUM / RB_PER_PACKET);
	for (int i = 0; i < CYCLE; i++)
	{
		for (int j = 0; j < RB_NUM; j++)
		{
			if (((i >= k1 * SLOT_PER_PACKET) && (i < (k1 + 1)*SLOT_PER_PACKET)) && ((j >= k2 * RB_PER_PACKET) && (j < (k2 + 1)*RB_PER_PACKET)))
			{
				resourceWindow[i][j] = 1;
			}
			else
			{
				resourceWindow[i][j] = 0;
			}
		}
	}
}

/*����ͼ5-33 ��ʽ 5-4 ����OBUλ������*/
void Vehicle::updateLocation()
{
	if (id < VEHICLE_NUM)
	{
		pos.x = pos.x + speed.value / (1000.0 / CHANNEL_UPDATE_INTERVAL)*cos(speed.direction);
		pos.y = pos.y + speed.value / (1000.0 / CHANNEL_UPDATE_INTERVAL)*sin(speed.direction);
		bool resultBlock = isNotInsideBlock(block);
		if (!resultBlock)
		{
			double distemp = 0.0;
			int k1;
			k1 = Random::random() % 4;
			switch (k1)
			{
			case(0):break;
			case(1):break;
			case(2):
			{
				if (speed.direction == VEHICLE_DIRECTION_UP)
				{
					distemp = abs(pos.y - (block->getPos().y + ROAD_LENGTH / 2.0));
					if (abs(pos.x - block->getPos().x)==ROAD_WIDTH/2-LANE_WIDTH/2)
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 - distemp;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 + LANE_WIDTH / 2.0;
						speed.direction = VEHICLE_DIRECTION_LEFT;
					}
					else
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 - distemp;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 + LANE_WIDTH * 1.5;
						speed.direction = VEHICLE_DIRECTION_LEFT;
					}
				}
				else if (speed.direction == VEHICLE_DIRECTION_DOWN)
				{
					distemp = abs(pos.y - (block->getPos().y - ROAD_LENGTH / 2.0));
					if (abs(pos.x - block->getPos().x) == ROAD_WIDTH / 2 - LANE_WIDTH / 2)
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 + distemp;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 - LANE_WIDTH / 2.0;
						speed.direction = VEHICLE_DIRECTION_RIGHT;
					}
					else
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 + distemp;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 - LANE_WIDTH * 1.5;
						speed.direction = VEHICLE_DIRECTION_RIGHT;
					}
				}
				else if (speed.direction == VEHICLE_DIRECTION_LEFT)
				{
					distemp = abs(pos.x - (block->getPos().x - ROAD_WIDTH / 2.0));
					if (abs(pos.y - block->getPos().y) == ROAD_LENGTH / 2 - LANE_WIDTH / 2)
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 - LANE_WIDTH / 2.0;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 - distemp;
						speed.direction = VEHICLE_DIRECTION_DOWN;
					}
					else
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 - 1.5*LANE_WIDTH / 2.0;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 - distemp;
						speed.direction = VEHICLE_DIRECTION_DOWN;
					}
				}
				else
				{
					distemp = abs(pos.x - (block->getPos().x + ROAD_WIDTH / 2.0));
					if (abs(pos.y - block->getPos().y) == ROAD_LENGTH / 2 - LANE_WIDTH / 2)
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 + LANE_WIDTH / 2.0;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 + distemp;
						speed.direction = VEHICLE_DIRECTION_UP;
					}
					else
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 + 1.5*LANE_WIDTH / 2.0;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 + distemp;
						speed.direction = VEHICLE_DIRECTION_UP;
					}
				}
				break;
			}
			case(3):
			{
				if (speed.direction == VEHICLE_DIRECTION_UP)
				{
					distemp = abs(pos.y - (block->getPos().y + ROAD_LENGTH / 2.0));
					if (abs(pos.x - block->getPos().x) == ROAD_WIDTH / 2.0 - LANE_WIDTH / 2.0)
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 - distemp;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 - LANE_WIDTH / 2.0;
						speed.direction = VEHICLE_DIRECTION_RIGHT;
					}
					else
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 - distemp;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 - LANE_WIDTH * 1.5;
						speed.direction = VEHICLE_DIRECTION_RIGHT;
					}
				}
				else if (speed.direction == VEHICLE_DIRECTION_DOWN)
				{
					distemp = abs(pos.y - (block->getPos().y - ROAD_LENGTH / 2.0));
					if (abs(pos.x - block->getPos().x) == ROAD_WIDTH / 2 - LANE_WIDTH / 2)
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 + distemp;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 + LANE_WIDTH / 2.0;
						speed.direction = VEHICLE_DIRECTION_LEFT;
					}
					else
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 + distemp;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 + 1.5*LANE_WIDTH / 2.0;
						speed.direction = VEHICLE_DIRECTION_LEFT;
					}
				}
				else if (speed.direction == VEHICLE_DIRECTION_LEFT)
				{
					distemp = abs(pos.x - (block->getPos().x - ROAD_WIDTH / 2.0));
					if (abs(pos.y - block->getPos().y) == ROAD_LENGTH / 2 - LANE_WIDTH / 2)
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 + LANE_WIDTH / 2.0;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 - distemp;
						speed.direction = VEHICLE_DIRECTION_UP;
					}
					else
					{
						pos.x = block->getPos().x - ROAD_WIDTH / 2.0 + 1.5*LANE_WIDTH / 2.0;
						pos.y = block->getPos().y - ROAD_LENGTH / 2.0 - distemp;
						speed.direction = VEHICLE_DIRECTION_UP;
					}
				}
				else
				{
					distemp = abs(pos.x - (block->getPos().x + ROAD_WIDTH / 2.0));
					if (abs(pos.y - block->getPos().y) == ROAD_LENGTH / 2 - LANE_WIDTH / 2)
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 - LANE_WIDTH / 2.0;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 + distemp;
						speed.direction = VEHICLE_DIRECTION_DOWN;
					}
					else
					{
						pos.x = block->getPos().x + ROAD_WIDTH / 2.0 - 1.5*LANE_WIDTH / 2.0;
						pos.y = block->getPos().y + ROAD_LENGTH / 2.0 + distemp;
						speed.direction = VEHICLE_DIRECTION_DOWN;
					}
				}
				break;
			}
			default:
				break;
			}
		}
		resultBlock = isNotInsideBlock(block);
		if (!resultBlock)
		{
			if (pos.x <= 0 || pos.x >= 3 * ROAD_WIDTH || pos.y <= 0 || pos.y >= 3 * ROAD_LENGTH)
			{
				this->wrapAround();
			}
			else
			{
				block->blockKick(this);
				int whichBlock = -1;
				for (int i = 0; i < BLOCK_NUM; i++)
				{
					if (this->isNotInsideBlock(&(radio->blocks[i])))
					{
						whichBlock = i;
						break;
					}
				}
				block = &(radio->blocks[whichBlock]);
				blockID = block->getId();
				block->blockAccept(this);
			}
		}
	}
}

/*�뿪���˺�ʹ��Wrap-around �����������˹�����Vehicle::wrapAround()����ʵ��*/
void Vehicle::wrapAround()
{
	if (pos.x < 0 && pos.y < 0)
	{
		pos.x += 3 * ROAD_WIDTH;
		pos.y += 3 * ROAD_LENGTH;
	}
	else if (pos.x < 0 && (pos.y > 3 * ROAD_LENGTH))
	{
		pos.x += 3 * ROAD_WIDTH;
		pos.y -= 3 * ROAD_LENGTH;
	}
	else if ((pos.x > 3 * ROAD_WIDTH) && (pos.y > 3 * ROAD_LENGTH))
	{
		pos.x -= 3 * ROAD_WIDTH;
		pos.y -= 3 * ROAD_LENGTH;
	}
	else if ((pos.x > 3 * ROAD_WIDTH) && pos.y < 0)
	{
		pos.x -= 3 * ROAD_WIDTH;
		pos.y += 3 * ROAD_LENGTH;
	}
	else if ((pos.x>3*ROAD_WIDTH)&&(pos.y>0)&&(pos.y<3*ROAD_LENGTH))
	{
		pos.x -= 3 * ROAD_WIDTH;
	}
	else if ((pos.x <0 )&& (pos.y>0)&&(pos.y<3*ROAD_LENGTH))
	{
		pos.x += 3 * ROAD_WIDTH;
	}
	else if ((pos.y > 3 * ROAD_LENGTH) && (pos.x > 0) && (pos.x < 3 * ROAD_WIDTH))
	{
		pos.y -= 3 * ROAD_LENGTH;
	}
	else if ((pos.y < 0) &&(pos.x>0)&& (pos.x < 3 * ROAD_WIDTH))
	{
		pos.y += 3 * ROAD_LENGTH;
	}
	else
	{
		pos.x = ROAD_WIDTH - LANE_WIDTH / 2.0;
		pos.y = ROAD_LENGTH - LANE_WIDTH / 2.0;
	}
	block->blockKick(this);
	int blockIdTemp = -1;
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		if (this->isNotInsideBlock(&(radio->blocks[i])))
		{
			blockIdTemp = i;
			break;
		}
	}
	block = &(radio->blocks[blockIdTemp]);
	blockID = block->getId();
	block->blockAccept(this);
}

/*���������жϹ��� */
bool Vehicle::isNotInsideBlock(BBlock* blockTemp)
{

}