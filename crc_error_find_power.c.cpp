#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // ȷ������ memcpy
#include <time.h>  // Ϊ��ʹ�� rand

// CRC-32 �㷨
unsigned int crc32(const unsigned char* data, size_t length) {
    unsigned int crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else {
                crc >>= 1;
            }
        }
    }
    return crc ^ 0xFFFFFFFF;
}

// ��תһ���ֽ��е�ĳ��λ
void flip_bit(unsigned char* data, size_t index, unsigned char bit) {
    data[index] ^= (1 << bit);
}

// ����CRC����������
void test_crc32_error_detection(const char* description, const unsigned char* data, size_t length, size_t error_index, unsigned char error_bit) {
    unsigned char* copy = (unsigned char*)malloc(length);  // ���ǿ������ת��
    memcpy(copy, data, length);  // ʹ�� memcpy ��������

    flip_bit(copy, error_index, error_bit);  // ���ܴ���

    unsigned int original_crc = crc32(data, length);
    unsigned int altered_crc = crc32(copy, length);

    printf("%s - ԭʼCRC: %08X, ����CRC: %08X\n", description, original_crc, altered_crc);

    free(copy);
}

int main() {
    unsigned char data[16];
    for (int i = 0; i < 16; i++) {
        data[i] = rand() % 256;  // ʹ�� rand �����������
    }

    // ���Ե���λ��ת
    test_crc32_error_detection("����λ��ת", data, sizeof(data), 5, 3);  // ��ת��6���ֽڵĵ�4��λ

    // ���Զ�λ��ת
    test_crc32_error_detection("��λ��ת - 1", data, sizeof(data), 3, 2);  // ��ת��4���ֽڵĵ�3��λ
    test_crc32_error_detection("��λ��ת - 2", data, sizeof(data), 7, 1);  // ��ת��8���ֽڵĵ�2��λ

    return 0;
}
