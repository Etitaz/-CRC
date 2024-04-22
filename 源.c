#include<stdio.h>


#define POLY 0x04c11db7 
#define INIT 0xffffffff 
#define XOROUT 0xffffffff 


/*
�����������λ����
*/
unsigned int reverse(unsigned int input)
{
	unsigned int output = 0;
	for (unsigned int i = 1; i != 0; i <<= 1)//ע��i��input����һ�£���֤��ȷ��ѭ������
	{
		output <<= 1;//��output����ʹ��һ��ѭ����ȷ����λ��Ϊ��λ��ͬʱ�ڱ���ѭ����ȷ��LSB
		if (input & 1)//���ݵ�ǰinput��LSBȷ����ǰoutput��LSB
		{
			output |= 1;
		}
		input >>= 1;//��input�����Ա�����һ��ѭ���л�ȡ��һ����λ
	}
	return output;
}


/*
����CRC-32/ISO-HDLC�㷨ģ�ͼ���CRC��
*/
unsigned int crc32(unsigned char* addr, unsigned int num)
{
	unsigned int crc = INIT;
	while (num-- > 0)//�����������ݵ��������μ���
	{
		crc ^= reverse(*addr++);//��refinΪ�棬�ʽ���������
		for (int i = 0; i < 8; i++)//��ÿ������İ�λ�����м���
		{
			if (crc & 0x80000000)//����λ��1��������Ʋ������ʽ�����������
			{
				crc = (crc << 1) ^ POLY;
			}
			else//�����������
			{
				crc <<= 1;
			}
		}
		crc &= 0xffffffff;//ȷ��ÿ�μ�������Ϊ32λ��ֵ
	}
	return reverse(crc ^ XOROUT);//��refoutΪ�棬�ʽ��������
}


int main()
{
	unsigned char input[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	printf("check=0x%08x\n", crc32(input, sizeof(input)));
}
