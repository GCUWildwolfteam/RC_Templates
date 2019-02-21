#ifndef  PROTOCOL_H_
#define  PROTOCOL_H_

#include <stdint.h>

/**
  *@brief:����֡���ݰ�
  */
typedef struct
{
	#define MAX_FRAME_LENGTH (256+6)		//����峤��
	#define MIN_FRAME_LENGTH  5			//��С֡����
	uint8_t Device_Address;				//�豸��ַ
	uint8_t Function_Type;				//֡����
	uint8_t Sequence;                   //֡����
	uint8_t Data_Length;				    //��Ч���ݳ���
	uint8_t *Data;						//����
	uint16_t Checksum;					//У��ֵ
}TransportProtocol_Typedef;


/**
  *@brief:������ 
  */
typedef enum
{
	FRAME_FORMAT_ERR = 1,			//֡��ʽ����
	CHECK_FORMAR_ERR = 2,			//У��ֵ��ʽ����
    CHECK_ERR = 3,					//У��ֵ��λ
	UPACKED_SUCCESS = 4             //����ɹ�
}TransportProtocol_Result;


/**
  *@brief:Э�������
  */
typedef struct
{	
	TransportProtocol_Typedef * TransportProtocol;  	//����֡
	uint32_t  RecieveByteCount;						//���յ��ֽ���
	uint8_t* Buf; 									//�����建��
	uint16_t FrameTotalLength;						//֡�ܳ���
	TransportProtocol_Result (*Unpacked)(void);     //�������
	void (*Packed)(void);							//�������
	uint16_t (*Check)(uint8_t *,uint16_t len);      //У�麯��
}TransportProtocol_Manager_Typedef;


/*��ʼ������Э��*/
void  TransportProtocol_Init(TransportProtocol_Typedef *TransportProtocol,\
	                      uint8_t *buf,uint16_t (*check)(uint8_t *,uint16_t len));

/*�ⲿ����Э�������*/
extern TransportProtocol_Manager_Typedef TransportProtocol_Manager;

#endif


